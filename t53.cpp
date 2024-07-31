#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

namespace S1 {
// 207. 课程表
// 有向图，判断是否存在回路，根据入度来判断
class Solution {
public:
    bool canFinish(int numCourses, vector<vector<int>>& prerequisites) {
        // prerequisites : j <-- i
        vector<int> in_degrees(numCourses);  // index, in_degree
        queue<int> zero_in_degree_node;
        int zero_number = 0;
        for (const vector<int>& edge : prerequisites) {
            in_degrees[edge[0]]++;  // 统计所有顶点的入度
        }
        for (int i = 0; i < numCourses; i++) {
            if (in_degrees[i] == 0) {
                zero_in_degree_node.push(i);  // 度为 0 的顶点入队
                zero_number++;
            }
        }
        sort(prerequisites.begin(), prerequisites.end(), [](const vector<int>& a, const vector<int>& b) {
            return a[1] < b[1];    // 按照源顶点排序，以方便查找某个源顶点所指向的目标顶点
        });
        while (!zero_in_degree_node.empty() && zero_number != numCourses) {
            int source_node = zero_in_degree_node.front(); zero_in_degree_node.pop();
            vector<vector<int>>::iterator iter = find_if(
                prerequisites.begin(), prerequisites.end(),
                [&source_node](const vector<int>& val) { return val[1] == source_node; }
            );
            // 找到第一个 source_node，下面将其所指向的目标顶点，入度减一
            while (iter < prerequisites.end() && (*iter)[1] == source_node) {
                int end_node = (*iter)[0];
                in_degrees[end_node]--;
                if (in_degrees[end_node] == 0) {
                    zero_in_degree_node.push(end_node);  // 如果入度减为 0，则加入队列
                    zero_number++;
                }
                iter++;
            }
        }
        if (zero_number == numCourses) {
            return true;
        } else {
            return false;
        }
    }
};
}

namespace S2 {
// 207. 课程表
// 有向图，判断是否存在回路，根据入度来判断，从前向后排列，广度优先遍历
class Solution {
public:
    bool canFinish(int numCourses, vector<vector<int>>& prerequisites) {
        vector<vector<int>> edge_lists(numCourses);  // 使用邻接表存储边的信息
        vector<int> in_degrees(numCourses);          // 各个节点的入度
        queue<int> zero_queue;                       // 入度为 0 的顶点的队列
        int zero_count = 0;                          // 入度为 0 的顶点的数目
        for (const vector<int>& pre : prerequisites) {
            int source = pre[1], end = pre[0];
            edge_lists[source].push_back(end);
            in_degrees[end]++;
        }
        for (int i = 0; i < numCourses; i++) {
            if (in_degrees[i] == 0) {
                zero_queue.push(i);
                zero_count++;
            }
        }
        while (!zero_queue.empty()) {
            int source = zero_queue.front(); zero_queue.pop();
            for (const int& end : edge_lists[source]) {
                if (--in_degrees[end] == 0) {
                    zero_queue.push(end);
                    zero_count++;
                }
            }
        }
        return zero_count == numCourses;
    }
};
}

namespace S3 {
// 207. 课程表
// 有向图，判断是否存在回路，根据出度来判断，从后向前排列（回溯），深度优先遍历
class Solution {
public:
    enum NodeType { NONE, VISITING, DONE };
    void DFS(const vector<vector<int>>& edge_lists, vector<NodeType>& nodes_type, int source) {
        nodes_type[source] = VISITING;
        for (const int& end : edge_lists[source]) {
            if (nodes_type[end] == NONE) {
                DFS(edge_lists, nodes_type, end);
            }
        }
        int done_count = 0;
        for (const int& end : edge_lists[source]) {
            if (nodes_type[end] == DONE) {
                done_count++;
            }
        }
        nodes_type[source] = done_count == edge_lists[source].size() ? DONE : VISITING;
    }
    bool canFinish(int numCourses, vector<vector<int>>& prerequisites) {
        vector<NodeType> nodes_type(numCourses, NONE);  // 存储各个顶点的遍历信息
        vector<vector<int>> edge_lists(numCourses);     // 使用邻接表存储边的信息
        for (const vector<int>& pre : prerequisites) {
            int source = pre[1], end = pre[0];
            edge_lists[source].push_back(end);
        }
        for (int i = 0; i < numCourses; i++) {
            if (nodes_type[i] == NONE) {
                DFS(edge_lists, nodes_type, i);
            }
        }
        for (int i = 0; i < numCourses; i++) {
            if (nodes_type[i] != DONE) return false;
        }
        return true;
    }
};
}