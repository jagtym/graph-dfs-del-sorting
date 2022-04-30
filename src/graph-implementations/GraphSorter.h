class GraphSorter {

    std::vector<int> delSorted_;
    std::vector<int> dfsSorted_;

    std::list<int> *alternativeEdges_;
    std::vector<std::vector<int>> graphMatrix_;
    std::vector<std::vector<int>> nexts_;
    int verticesCount_;

    void visit_dfs(int vertex, bool visited[], std::stack<int> &Stack) {
        visited[vertex] = true;
        std::list<int>::iterator i;
        for (i = alternativeEdges_[vertex].begin(); i != alternativeEdges_[vertex].end(); ++i) {
            if (!visited[*i]) {
                visit_dfs(*i, visited, Stack);
            }
        }
        if (vertex != 0) {
            Stack.push(vertex);
        }
    }

    void dfs() {
        std::stack<int> Stack;

        bool *visited = new bool[verticesCount_ + 1];
        for (int i = 1; i <= verticesCount_; i++) {
            visited[i] = false;
        }
        for (int i = 1; i <= verticesCount_; i++) {
            if (!visited[i]) {
                visit_dfs(i, visited, Stack);
            }
        }

        while (!Stack.empty()) {
            // std::cout << Stack.top() << " ";
            Stack.pop();
        }
        // std::cout << std::endl;
    }

    void del() {
        std::vector<int> in_degree(verticesCount_);
        for (int i = 0; i < verticesCount_; i++) {
            for (int j = 0; j < verticesCount_; j++) {
                if (1 + verticesCount_ <= graphMatrix_[i][j]) {
                    in_degree[i] += 1;
                }
            }
        }
        std::deque<int> queue;
        for (int i = 0; i < verticesCount_; i++) {
            if (in_degree[i] == 0) {
                queue.push_front(i + 1);
            }
        }

        while (!queue.empty()) {
            int num = queue.back();
            queue.pop_back();
            delSorted_.push_back(num);
            for (auto n: nexts_[num - 1]) {
                in_degree[n - 1] -= 1;
                if (in_degree[n - 1] == 0) {
                    queue.push_front(n);
                }
            }
        }
    }

    public: 
        GraphSorter(int verticesCount, 
        std::vector<std::vector<int>> &nexts, 
        std::vector<std::vector<int>> &graphMatrix,
        std::list<int> *alternativeEdges ) 
        : nexts_(nexts),
          graphMatrix_(graphMatrix)
        {
            verticesCount_ = verticesCount;
            alternativeEdges_ = alternativeEdges;
        }

        void dfsSort() {
            dfs();
        }

        void delSort() {
            del();
        }
};