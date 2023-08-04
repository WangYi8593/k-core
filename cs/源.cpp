#include <iostream>
#include <vector>
#include <queue>
using namespace std;
// 计算连通分量函数
void findConnectedComponents(const vector<vector<int>>& adjacencyMatrix, vector<int>& componentCounts, vector<vector<int>>& componentNodes)
{
    int numNodes = adjacencyMatrix.size();

    vector<bool> visited(numNodes, false);

    for (int i = 0; i < numNodes; ++i) {
        if (!visited[i]) {
            queue<int> queue;
            queue.push(i);
            visited[i] = true;

            int componentCount = 0;
            vector<int> component;

            while (!queue.empty()) {
                int node = queue.front();
                queue.pop();
                componentCount++;
                component.push_back(node);

                for (int j = 0; j < numNodes; ++j) {
                    if (adjacencyMatrix[node][j] == 1 && !visited[j]) {
                        queue.push(j);
                        visited[j] = true;
                    }
                }
            }

            componentCounts.push_back(componentCount);
            componentNodes.push_back(component);
        }
    }
}

vector<vector<int>> k_core_subgraph(int K, vector<vector<int>> graph)
{
    //vector<vector<int>> graph = graph1;

    while (true) {
        vector<int> degree(graph.size(), 0);
        vector<pair<int, int>> temdegree;
        vector<bool> valid(graph.size(), true);

        for (int i = 0; i < graph.size(); i++) {
            for (int j = 0; j < graph.size(); j++) {
                degree[i] += graph[i][j];
            }
            pair<int, int> p(degree[i], i);
            temdegree.push_back(p);
        }

        for (int i = 0; i < graph.size(); i++) {
            if (degree[i] < K) {
                valid[i] = false;
            }
        }

        vector<vector<int>> newGraph;
        for (int i = 0; i < graph.size(); i++) {
            if (valid[i]) {
                newGraph.push_back({});
                for (int j = 0; j < graph.size(); j++) {
                    if (valid[j]) {
                        newGraph.back().push_back(graph[i][j]);
                    }
                }
            }
        }

        if (newGraph.size() == graph.size()) {

            return newGraph;
            break;
        }

        graph = newGraph;

    }

}


int main() {

    int K = 2;

    vector<vector<int>> graph = {
      {0, 1, 0, 0, 0, 0, 0, 0, 0},
      {1, 0, 0, 0, 1, 0, 0, 0, 0},
      {0, 0, 0, 1, 1, 0, 0, 0, 0},
      {0, 0, 1, 0, 1, 0, 0, 0, 0},
      {0, 1, 1, 1, 0, 0, 0, 0, 0},
      {0, 0, 0, 0, 0, 0, 1, 1, 0},
      {0, 0, 0, 0, 0, 1, 0, 1, 1},
      {0, 0, 0, 0, 0, 1, 1, 0, 0},
      {0, 0, 0, 0, 0, 0, 1, 0, 0}
    };




    vector<vector<int>> sub_graph = k_core_subgraph(K, graph);

    vector<int> componentCounts;

    vector<vector<int>> componentNodes;

    findConnectedComponents(sub_graph, componentCounts, componentNodes);

    cout << "Number of connected components: " << componentCounts.size() << endl;

    return 0;
}