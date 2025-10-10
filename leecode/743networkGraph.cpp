

#include "../leetcode-debug/header.h"

using namespace std;

class Solution0 {
private:

/**
 * @brief Function that add edge between two nodes or vertices of graph
 *
 * @param u any node or vertex of graph
 * @param v any node or vertex of graph
 */
void addEdge(std::vector<std::vector<std::pair<int, int>>> *adj, int u, int v,
             int w) {
    (*adj)[u - 1].push_back(std::make_pair(v - 1, w));
    // (*adj)[v - 1].push_back(std::make_pair(u - 1, w));
}

/**
 * @brief Function runs the dijkstra algorithm for some source vertex and
 * target vertex in the graph and returns the shortest distance of target
 * from the source.
 *
 * @param adj input graph
 * @param s source vertex
 * @param t target vertex
 *
 * @return shortest distance if target is reachable from source else -1 in
 * case if target is not reachable from source.
 */
int dijkstra(std::vector<std::vector<std::pair<int, int>>> *adj, int s) {
    /// n denotes the number of vertices in graph
    int n = adj->size();
constexpr int INF = std::numeric_limits<int>::max();
    /// setting all the distances initially to INF
    std::vector<int> dist(n, INF);

    /// creating a min heap using priority queue
    /// first element of pair contains the distance
    /// second element of pair contains the vertex
    std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>,
                        std::greater<std::pair<int, int>>>
        pq;

    /// pushing the source vertex 's' with 0 distance in min heap
    pq.push(std::make_pair(0, s));

    /// marking the distance of source as 0
    dist[s] = 0;

    while (!pq.empty()) {
        /// second element of pair denotes the node / vertex
        int currentNode = pq.top().second;

        /// first element of pair denotes the distance
        int currentDist = pq.top().first;

        pq.pop();

        /// for all the reachable vertex from the currently exploring vertex
        /// we will try to minimize the distance
        for (std::pair<int, int> edge : (*adj)[currentNode]) {
            /// minimizing distances
            if (currentDist + edge.second < dist[edge.first]) {
                dist[edge.first] = currentDist + edge.second;
                pq.push(std::make_pair(dist[edge.first], edge.first));
            }
        }
    }
    int max_time=-1;
    for(int t=0;t<n;t++){
        if(dist[t] == INF) {
            return -1;
        }
        max_time=std::max(dist[t],max_time);
    }
    return max_time;
}

public:
// 有 n 个网络节点，标记为 1 到 n。
// 给你一个列表 times，表示信号经过 有向 边的传递时间。 
// times[i] = (ui, vi, wi)，其中 ui 是源节点，vi 是目标节点， wi 是一个信号从源节点传递到目标节点的时间。
// 从某个节点 K 发出一个信号。需要多久才能使所有节点都收到信号？
    int networkDelayTime(vector<vector<int>>& times, int n, int k) {
        int total=-1;
        vector<vector<pair<int, int>>> adj(n, vector<pair<int, int>>());
        for(auto uvw : times){
            addEdge(&adj, uvw[0],uvw[1],uvw[2]);
        }
        total=dijkstra(&adj,k-1);
        return total;
    }

};
class Solution {
public:
    int networkDelayTime(vector<vector<int>>& times, int n, int k) {
        // 构造矩阵
        int inf = INT_MAX / 2;
        vector<vector<int>> g(n, vector<int>(n, inf));
        for (auto& time : times) {
            g[time[0] - 1][time[1] - 1] = time[2];
        }

        vector<int> dist(n, inf);
        dist[k - 1] = 0;
        vector<bool> used(n, false);

        // 循环 n 次，每次确定一个节点  
        for (int i = 0; i < n; i += 1) {
            // 确定本次更新的节点（距离最近）
            int x = -1;
            for (int y = 0; y < n; y += 1) {
                if (!used[y] && (x == -1 || dist[y] < dist[x])) {
                    x = y;
                }
            }
            used[x] = true;
            
            // 更新到其他节点最小的距离
            for (int y = 0; y < n; y += 1) {
                dist[y] = min(dist[y], g[x][y] + dist[x]);
            }
        }

        int ans = *max_element(dist.begin(), dist.end());
        return ans == inf ? -1 : ans;
    }
};
#define REGISTER(func) exc.registerMemberFunction(#func, &Solution::func);

int main() {
    // Excecutor的第一个模板参数为类名，第二个模板参数为false；
    Excecutor<Solution, true> exc("../in.txt");
    exc.instance = exc.createInstance<void>();

    REGISTER(networkDelayTime)
    exc.run();
}