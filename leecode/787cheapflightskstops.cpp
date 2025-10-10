

#include "../leetcode-debug/header.h"

using namespace std;
const int inf = 0x3f3f3f3f;
class Solution_ref {
private:
    #define N 110
    int h[N], e[N * (N - 1) / 2], w[N * (N - 1) / 2], ne[N * (N - 1) / 2], idx;
    struct Node {
        int dist, dep, x;
        bool operator < (const Node &rhs) const {
            return dist < rhs.dist;
        };
    };
public:
    void add(int a, int b, int c) {
        ++idx;
        e[idx] = b, w[idx] = c, ne[idx] = h[a], h[a] = idx;
    }
    int findCheapestPrice(int n, vector<vector<int>>& flights, int src, int dst, int k) {
        for (auto flight : flights) add(flight[0], flight[1], flight[2]);
        priority_queue<Node> pq; 
        // dist[x][d]：从 src 出发，飞了 d 次，到达城市 x 的最小花费
        // k+2 是因为：最多 k+1 次飞行（k 次转机），索引从 0 开始
        vector<vector<int>> dist(n, vector<int>(k + 2, inf)); 
        // 是否已经确定了“经过 d 次飞行到达城市 x”的最短距离？
        vector<vector<int>> st(n, vector<int>(k + 2, false));
        dist[src][0] = 0; 
        pq.push({-dist[src][0], 0, src});
        while (pq.size()) {
            int x = pq.top().x, d = pq.top().dep; 
            pq.pop();
            if (st[x][d]) continue;
            st[x][d] = true;
            if (d > k) continue;
            for (int i = h[x]; i; i = ne[i]) {
                int y = e[i];
                if (dist[y][d + 1] > dist[x][d] + w[i]) {
                    dist[y][d + 1] = dist[x][d] + w[i];
                    pq.push({-dist[y][d + 1], d + 1, y});
                }
            }
        }
        int res = inf;
        for (int i = 0; i <= k + 1; ++i) res = min(res, dist[dst][i]);
        if (res == inf) return -1;
        return res;
    }
};
class Solution {
public:
    int findCheapestPrice(int n, vector<vector<int>>& flights, int src, int dst, int k) {
        vector<vector<pair<int,int>>> adj(n);
        for(auto &fl:flights)
            adj[fl[0]].push_back(pair(fl[1],fl[2]));
        /// 总路径、节点编号、当前queue头的depth
        priority_queue<tuple<int,int,int>, vector<tuple<int,int,int>>, greater<tuple<int,int,int>>> pathQfrom_s;
        
        // dist[x][d]：从 src 出发，飞了 d 次，到达城市 x 的最小花费
        // k+2 是因为：最多 k+1 次飞行（k 次转机），索引从 0 开始
        vector<vector<int>> min_distfrom_s(n, vector<int>(k + 2, INT_MAX/2)); 
        // 是否已经确定了“经过 d 次飞行到达城市 x”的最短距离？
        vector<vector<int>> st(n, vector<int>(k + 2, false));
        min_distfrom_s[src][0]=0;
        pathQfrom_s.push(std::make_tuple(0,src,0));
        while(!pathQfrom_s.empty()){
            // 获得最近节点
            int current_dist = std::get<0>(pathQfrom_s.top());//.first;
            int i = std::get<1>(pathQfrom_s.top());//.second, 
            int depth = std::get<2>(pathQfrom_s.top());
            pathQfrom_s.pop();
            
            if(st[i][depth])continue;
            st[i][depth]=true;
            if(depth>k)continue;

            // 查找这个节点的子节点所对应的最短子路径
            for(pair<int,int> edge_j: adj[i]){
                int wij=edge_j.second, j=edge_j.first;
                if(wij+current_dist < min_distfrom_s[j][depth+1]){
                    min_distfrom_s[j][depth+1]=wij+current_dist;
                    pathQfrom_s.push(std::make_tuple(min_distfrom_s[j][depth+1],j,depth+1));
                }
            }
        }
        int cost=INT_MAX/2;
        for (int i = 0; i <= k + 1; ++i) cost = min(cost, min_distfrom_s[dst][i]);
        if(cost ==INT_MAX/2)cost=-1;
        return cost;
    }
};
#define REGISTER(func) exc.registerMemberFunction(#func, &Solution::func);

int main() {
    // Excecutor的第一个模板参数为类名，第二个模板参数为false；
    Excecutor<Solution, true> exc("../in.txt");
    exc.instance = exc.createInstance<void>();

    REGISTER(findCheapestPrice)
    exc.run();
}