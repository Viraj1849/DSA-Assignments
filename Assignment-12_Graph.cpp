#include <iostream>
#include <vector>
#include <list>
#include <queue>
#include <algorithm>
using namespace std;

// Structure for an Edge
struct Edge {
    int src;
    int dest;
    int weight;

    Edge() {
        src = dest = weight = 0;
    }

    Edge(int from, int to, int cost) {
        src = from;
        dest = to;
        weight = cost;
    }
};

// Disjoint Set (Union-Find)
class DisjointSet {
public:
    vector<int> parent;
    vector<int> rankArr;

    DisjointSet(int nodeCount) {
        parent.resize(nodeCount + 1);
        rankArr.resize(nodeCount + 1);
        for (int idx = 0; idx <= nodeCount; idx++) {
            parent[idx] = idx;
            rankArr[idx] = 0;
        }
    }

    int findParent(int node) {
        if (parent[node] == node)
            return node;
        parent[node] = findParent(parent[node]);
        return parent[node];
    }

    void unite(int nodeA, int nodeB) {
        int rootA = findParent(nodeA);
        int rootB = findParent(nodeB);
        if (rootA == rootB)
            return;
        if (rankArr[rootA] < rankArr[rootB]) {
            parent[rootA] = rootB;
        } else if (rankArr[rootB] < rankArr[rootA]) {
            parent[rootB] = rootA;
        } else {
            parent[rootB] = rootA;
            rankArr[rootA]++;
        }
    }
};

// Graph Class
class Graph {
public:
    int nodeCount; // number of vertices
    vector<vector<int>> adjMatrix;
    vector<list<pair<int, int>>> adjList;
    vector<Edge> edgeList;

    Graph(int vertices = 0) {
        nodeCount = vertices;
        adjMatrix.resize(nodeCount + 1, vector<int>(nodeCount + 1, 0));
        adjList.resize(nodeCount + 1);
    }

    void init(int vertices) {
        nodeCount = vertices;
        adjMatrix.assign(nodeCount + 1, vector<int>(nodeCount + 1, 0));
        adjList.assign(nodeCount + 1, list<pair<int, int>>());
        edgeList.clear();
    }

    void addEdge(int from, int to, int cost) {
        if (from < 1 || from > nodeCount || to < 1 || to > nodeCount)
            return;

        adjMatrix[from][to] = cost;
        adjMatrix[to][from] = cost;
        adjList[from].push_back(make_pair(to, cost));
        adjList[to].push_back(make_pair(from, cost));
        edgeList.push_back(Edge(from, to, cost));
    }

    // Display Adjacency Matrix
    void displayMatrix() {
        cout << "\nAdjacency Matrix (0 means no direct pipeline):\n";
        cout << "   ";
        for (int col = 1; col <= nodeCount; col++)
            cout << col << " ";
        cout << "\n";

        for (int row = 1; row <= nodeCount; row++) {
            cout << row << ": ";
            for (int col = 1; col <= nodeCount; col++) {
                cout << adjMatrix[row][col] << " ";
            }
            cout << "\n";
        }
    }

    // Display Adjacency List
    void displayList() {
        cout << "\nAdjacency List (neighbor : cost):\n";
        for (int node = 1; node <= nodeCount; node++) {
            cout << node << " -> ";
            if (adjList[node].empty()) {
                cout << "None";
            } else {
                for (auto neighbor = adjList[node].begin(); neighbor != adjList[node].end(); ++neighbor) {
                    cout << "(" << neighbor->first << " : " << neighbor->second << ") ";
                }
            }
            cout << "\n";
        }
    }

    // BFS Traversal
    void BFS(int startNode) {
        vector<int> visited(nodeCount + 1, 0);
        queue<int> nodeQueue;

        visited[startNode] = 1;
        nodeQueue.push(startNode);

        cout << "\nBFS order starting from house " << startNode << ": ";

        while (!nodeQueue.empty()) {
            int current = nodeQueue.front();
            nodeQueue.pop();
            cout << current << " ";

            for (auto neighbor = adjList[current].begin(); neighbor != adjList[current].end(); ++neighbor) {
                int nextNode = neighbor->first;
                if (!visited[nextNode]) {
                    visited[nextNode] = 1;
                    nodeQueue.push(nextNode);
                }
            }
        }
        cout << "\n";
    }

    // DFS Traversal Helper
    void DFSHelper(int currentNode, vector<int>& visited) {
        visited[currentNode] = 1;
        cout << currentNode << " ";
        for (auto neighbor = adjList[currentNode].begin(); neighbor != adjList[currentNode].end(); ++neighbor) {
            int nextNode = neighbor->first;
            if (!visited[nextNode])
                DFSHelper(nextNode, visited);
        }
    }

    void DFS(int startNode) {
        vector<int> visited(nodeCount + 1, 0);
        cout << "\nDFS order starting from house " << startNode << ": ";
        DFSHelper(startNode, visited);
        cout << "\n";
    }

    // Kruskal's Minimum Spanning Tree
    void kruskalMST() {
        sort(edgeList.begin(), edgeList.end(), compareEdge);

        DisjointSet disjointSet(nodeCount);
        vector<Edge> mstEdges;
        int totalCost = 0;

        for (int idx = 0; idx < (int)edgeList.size(); idx++) {
            int from = edgeList[idx].src;
            int to = edgeList[idx].dest;
            int cost = edgeList[idx].weight;

            int rootFrom = disjointSet.findParent(from);
            int rootTo = disjointSet.findParent(to);

            if (rootFrom != rootTo) {
                disjointSet.unite(rootFrom, rootTo);
                mstEdges.push_back(edgeList[idx]);
                totalCost += cost;
            }
        }

        cout << "\nMinimum Spanning Tree (Pipelines to lay):\n";
        for (int idx = 0; idx < (int)mstEdges.size(); idx++) {
            cout << mstEdges[idx].src << " - " << mstEdges[idx].dest
                 << " : cost = " << mstEdges[idx].weight << "\n";
        }
        cout << "Total minimum cost = " << totalCost << "\n";
    }

    static bool compareEdge(const Edge& a, const Edge& b) {
        return a.weight < b.weight;
    }
};

// MAIN FUNCTION
int main() {
    int houseCount, pipeCount;
    cout << "Enter number of houses and number of possible pipelines: ";
    cin >> houseCount >> pipeCount;

    Graph g;
    g.init(houseCount);

    cout << "Enter each possible pipeline as: house1 house2 cost\n";
    for (int i = 0; i < pipeCount; i++) {
        int houseA, houseB, costVal;
        cin >> houseA >> houseB >> costVal;
        g.addEdge(houseA, houseB, costVal);
    }

    g.displayMatrix();
    g.displayList();

    int startHouse;
    cout << "\nEnter starting house for BFS and DFS: ";
    cin >> startHouse;

    g.BFS(startHouse);
    g.DFS(startHouse);
    g.kruskalMST();

    return 0;
}
