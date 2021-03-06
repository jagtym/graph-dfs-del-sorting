class GraphMatrix {
    int vertices_count = 0;
    int edges_count = 0;

    std::vector<std::vector<int>> graph_edges;
    std::vector<std::vector<int>> matrix;
    std::list<int> *alt_edges;
    std::vector<std::vector<int>> nexts;
    std::vector<std::vector<int>> prevs;
    std::vector<std::vector<int>> ninc;

    GraphLoader *loader;
    GraphSorter *sorter;

    void loadNexts(int vertices_number) {
        for (int i = 0; i < vertices_number; i++) {
            std::vector<int> cnext;
            for (auto edge: graph_edges) {
                if (edge[0] == i + 1) {
                    cnext.push_back(edge[1]);
                }
            }
            std::sort(cnext.begin(), cnext.end());
            nexts.push_back(cnext);
        }
    }

    void loadPrevs(int vertices_number) {
        for (int i = 0; i < vertices_number; i++) {
            std::vector<int> cprev;
            for (auto edge: graph_edges) {
                if (edge[1] == i + 1) {
                    cprev.push_back(edge[0]);
                }
            }
            std::sort(cprev.begin(), cprev.end());
            prevs.push_back(cprev);
        }
    }

    void loadNonInc(int vertices_number) {
        for (int i = 0; i < vertices_number; i++) {
            std::vector<int> cnonint;
            for (int j = 1; j <= vertices_number; j++) {
                if (std::count(prevs[i].begin(), prevs[i].end(), j) <= 0) {
                    if (std::count(nexts[i].begin(), nexts[i].end(), j) <= 0) {
                        cnonint.push_back(j);
                    }
                }
            }
            std::sort(cnonint.begin(), cnonint.end());
            ninc.push_back(cnonint);
        }
    }

    void initializeMatrix(int vertices_number) {
        for (int i = 0; i < vertices_number; i++) {
            std::vector<int> row;
            for (int j = 0; j < vertices_number + 3; j++) {
                row.push_back(0);
            }
            matrix.push_back(row);
        }
    }

    void loadFirst() {
        for (int i = 0; i < vertices_count; i++) {
            if (!nexts[i].empty()) {
                matrix[i][vertices_count] = nexts[i][0];
            } else {
                matrix[i][vertices_count] = 0;
            }
        }
        for (auto edge: graph_edges) {
            matrix[edge[0] - 1][edge[1] - 1] = nexts[edge[0] - 1].back();
        }
    }

    void loadSecond() {
        for (int i = 0; i < vertices_count; i++) {
            if (!prevs[i].empty()) {
                matrix[i][vertices_count + 1] = prevs[i][0];
            } else {
                matrix[i][vertices_count + 1] = 0;
            }
        }
        for (auto edge: graph_edges) {
            matrix[edge[1] - 1][edge[0] - 1] = prevs[edge[1] - 1].back() + vertices_count;
        }
    }

    bool edgeExists(int i, int j) {
        for (auto edge: graph_edges) {
            if (edge[0] == i && edge[1] == j) {
                return true;
            }
            if (edge[0] == j && edge[1] == i) {
                return true;
            }
        }
        return false;
    }

    void loadThird() {
        for (int i = 0; i < vertices_count; i++) {
            if (!ninc[i].empty()) {
                matrix[i][vertices_count + 2] = ninc[i][0];
            } else {
                matrix[i][vertices_count + 2] = 0;
            }
        }
        for (int i = 0; i < vertices_count; i++) {
            for (int j = 0; j < vertices_count; j++) {
                if (!edgeExists(i + 1, j + 1)) {
                    matrix[i][j] = -ninc[i].back();
                }
            }
        }
    }

    bool cycle(int v, bool visited[], bool stack[]) {

        if (!visited[v]) {
            visited[v] = true;
            stack[v] = true;
        }

        std::list<int>::iterator i;
        for (i = alt_edges[v].begin(); i != alt_edges[v].end(); ++i) {
            if (!visited[*i] && cycle(*i, visited, stack)) {
                return true;
            } else if (stack[*i]) {
                return true;
            }
        }
        stack[v] = false;
        return false;
    }

    bool hasCycle() {
        bool visited[vertices_count];
        bool stack[vertices_count];
        for (int i = 0; i < vertices_count; i++) {
            visited[i] = false;
            stack[i] = false;
        }

        for (int i = 0; i < vertices_count; i++) {
            if (visited[i] == false && cycle(i, visited, stack)) {
                return true;
            }
        }
        return false;
    }

public:

    GraphMatrix(bool file) {
        loader = new GraphLoader(vertices_count, edges_count, graph_edges, file);
        sorter = new GraphSorter(vertices_count, nexts, matrix, alt_edges);
        loader -> loadGraph();
        alt_edges = loader -> getAlternativeEdges();

        initializeMatrix(vertices_count);
        loadNexts(vertices_count);
        loadPrevs(vertices_count);
        // loadNonInc(vertices_count);
        loadFirst();
        // loadSecond();
        // loadThird();
        // loadNumbers(vertices_count);
        if (false) {
            std::cout << "Matrix has cycle!";
        }
    }

    void printEdges() {
        std::cout << std::endl << "graph_edges: " << std::endl;
        for (auto edge: graph_edges) {
            std::cout << edge[0] << " " << edge[1] << std::endl;
        }
    }

    void printNexts() {
        std::cout << std::endl << "nexts: " << std::endl;
        for (int i = 0; i < nexts.size(); i++) {
            std::cout << i + 1 << ": ";
            for (auto x: nexts[i]) {
                std::cout << x << " ";
            }
            std::cout << std::endl;
        }
    }

    void printPrevs() {
        std::cout << std::endl << "prevs: " << std::endl;
        for (int i = 0; i < prevs.size(); i++) {
            std::cout << i + 1 << ": ";
            for (auto x: prevs[i]) {
                std::cout << x << " ";
            }
            std::cout << std::endl;
        }
    }

    void printNonInc() {
        std::cout << std::endl << "non inc: " << std::endl;
        for (int i = 0; i < ninc.size(); i++) {
            std::cout << i + 1 << ": ";
            for (auto x: ninc[i]) {
                std::cout << x << " ";
            }
            std::cout << std::endl;
        }
    }

    void printMatrix() {
        std::cout << std::endl << "matrix: " << std::endl;
        for (auto row: matrix) {
            for (auto x: row) {
                std::cout << x << " ";
            }
            std::cout << std::endl;
        }
    }

    // void printSorted() {
    //     for (auto x: kanh_sorted) {
    //         std::cout << x << " ";
    //     }
    //     std::cout << std::endl;
    // }

    void sort_DFS() {
        if (true) {
            std::cout << "dfs: " << std::endl;
            auto start = std::chrono::high_resolution_clock::now();
            sorter -> dfsSort();
            auto stop = std::chrono::high_resolution_clock::now();
            auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
            std::cout << "time: " << duration.count() << std::endl;
        } else {
            std::cout << "Graf ma cykl - sortowanie niemo??liwe";
        }
    }

    void sort_DEL() {
        if (true) {
            std::cout << "del: " << std::endl;
            auto start = std::chrono::high_resolution_clock::now();
            sorter -> delSort();
            auto stop = std::chrono::high_resolution_clock::now();
            auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
            std::cout << "time: " << duration.count() << std::endl;
        } else {
            std::cout << "Graf ma cykl - sortowanie niemo??liwe";
        }
    }
};