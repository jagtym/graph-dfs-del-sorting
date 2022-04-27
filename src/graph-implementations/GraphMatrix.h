class GraphMatrix
{
    int vertices_count = 0;
    int edges_count = 0; 
    bool has_cycle = false;

    std::vector<std::vector<int>> edges;
    std::vector<std::vector<int>> matrix;
    std::list<int> *alt_edges;
    std::vector<std::vector<int>> nexts;
    std::vector<std::vector<int>> prevs;
    std::vector<std::vector<int>> ninc;
    std::vector<int> numbers;
    std::vector<int> ex;

    std::vector<int> kanh_sorted;
    std::vector<int> dfs_sorted;

    void visit_dfs(int v, bool visited[], std::stack<int>& Stack)
    {
        visited[v] = true;
        std::list<int>::iterator i;
        for (i = alt_edges[v].begin(); i != alt_edges[v].end(); ++i) 
        {
            if (!visited[*i])
            {
                visit_dfs(*i, visited, Stack);
            }
        }
        Stack.push(v);
    }
    
    void dfs()
    {
        std::stack<int> Stack;

        bool* visited = new bool[vertices_count];
        for (int i = 0; i < vertices_count; i++)
            visited[i] = false;

        for (int i = 0; i < vertices_count; i++)
            if (!visited[i])
                visit_dfs(i, visited, Stack);

        while (!Stack.empty()) {
            std::cout << Stack.top() << " ";
            Stack.pop();
        }
    }

    void del()
    {
        int in_degree[vertices_count];
        for (int i = 0; i < vertices_count; i++){
            for (int j = 0; j < vertices_count; j++) {
                if (1 + vertices_count <= matrix[i][j]) {
                    in_degree[i] += 1;
                }
            }
        }
        std::deque<int> queue;
        for (int i = 0; i < vertices_count; i++) {
            if (in_degree[i] == 0) {
                queue.push_front(i);
            }
        }

        while (queue.size()) {
            int num = queue.back();
            queue.pop_back();
            kanh_sorted.push_back(num);
            for (auto n: nexts[num]) {
                in_degree[n] -= 1;
                if (in_degree[n] == 0)
                {
                    queue.push_front(n);
                }
            }
        }
    }


    void loadNumbers(int vertices_number)
    {
        for (int i = 1; i <= vertices_number; i++)
        {
            numbers.push_back(i);
        }
    }

    void loadEdges(int edges_number)
    {
        alt_edges = new std::list<int>[vertices_count + 1];
        for (int i = 0; i < edges_number; i++)
        {
            int from, to;
            std::cin >> from >> to;
            std::vector<int> edge = {from, to};
            edges.push_back(edge);
            alt_edges[from].push_back(to);
        }
    }

    void loadNexts(int vertices_number)
    {
        for (int i = 0; i < vertices_number; i++)
        {
            std::vector<int> cnext;
            for (auto edge: edges)
            {
                if (edge[0] == i + 1)
                {
                    cnext.push_back(edge[1]);
                }
            }
            std::sort(cnext.begin(), cnext.end());
            nexts.push_back(cnext);
        }
    }
    
    void loadPrevs(int vertices_number)
    {
        for (int i = 0; i < vertices_number; i++)
        {
            std::vector<int> cprev;
            for (auto edge: edges)
            {
                if (edge[1] == i + 1)
                {
                    cprev.push_back(edge[0]);
                }
            }
            std::sort(cprev.begin(), cprev.end());
            prevs.push_back(cprev);
        }
    }

    void loadNonInc(int vertices_number) 
    {
        for (int i = 0; i < vertices_number; i++)
        {
            std::vector<int> cnonint;
            for (int j = 1; j <= vertices_number; j++)
            {
                if (std::count(prevs[i].begin(), prevs[i].end(), j) <= 0) 
                {
                    if (std::count(nexts[i].begin(), nexts[i].end(), j) <= 0)
                    {
                        cnonint.push_back(j);
                    }
                }
            }
            std::sort(cnonint.begin(), cnonint.end());
            ninc.push_back(cnonint); 
        }
    }

    void initializeMatrix(int vertices_number)
    {
        for (int i = 0; i < vertices_number; i++)
        {
            std::vector<int> row;
            for (int j = 0; j < vertices_number + 3; j++)
            {
                row.push_back(0);
            }
            matrix.push_back(row);
        }
    }

    void loadFirst()
    {
        for (int i = 0; i < vertices_count; i++)
        {
            if (nexts[i].size())
            {
                matrix[i][vertices_count] = nexts[i][0];
            }
            else
            {
                matrix[i][vertices_count] = 0;
            }
        }
        for (auto edge: edges) {
            matrix[edge[0] - 1][edge[1] - 1] = nexts[edge[0] - 1].back();
        }
    }

    void loadSecond()
    {
        for (int i = 0; i < vertices_count; i++)
        {
            if (prevs[i].size())
            {
                matrix[i][vertices_count + 1] = prevs[i][0];
            }
            else
            {
                matrix[i][vertices_count + 1] = 0;
            }
        }
        for (auto edge: edges) {
            matrix[edge[1] - 1][edge[0] - 1] = prevs[edge[1] - 1].back() + vertices_count;
        }
    }

    bool edgeExists(int i, int j) 
    {
        for (auto edge: edges) 
        {
            if (edge[0] == i && edge[1] == j) 
            {
                return true;
            }
            if (edge[0] == j && edge[1] == i) 
            {
                return true;
            }
        }
        return false;
    }

    void loadThird()
    {
        for (int i = 0; i < vertices_count; i++)
        {
            if (ninc[i].size())
            {
                matrix[i][vertices_count + 2] = ninc[i][0];
            }
            else
            {
                matrix[i][vertices_count + 2] = 0;
            }
        }
        for (int i = 0; i < vertices_count; i++)
        {
            for (int j = 0; j < vertices_count; j++)
            {
                if (!edgeExists(i + 1, j + 1))
                {
                    matrix[i][j] = -ninc[i].back();
                }
            }
        }
    }

    bool cycle(int v, bool visited[], bool stack[])
    {

        if (!visited[v])
        {
            visited[v] = true;
            stack[v] = true;
        }

        std::list<int>::iterator i;
        for (i = alt_edges[v].begin(); i != alt_edges[v].end(); ++i)
        {
            if (!visited[*i] && cycle(*i, visited, stack))
            {
                return true;
            }
            else if (stack[*i]) 
            {
                return true;
            }
        }
        stack[v] = false;
        return false;
    }

    bool hasCycle()
    {
        bool visited[vertices_count];
        bool stack[vertices_count];
        for (int i = 0; i < vertices_count; i++)
        {
            visited[i] = false;
            stack[i] = false;
        }

        for (int i = 0; i < vertices_count; i++)
        {
            if (visited[i] == false && cycle(i, visited, stack)) {
                return true;
            }
        }
        return false;
    }

    public:
        GraphMatrix()
        {
            std::cout << "Enter vertices count: ";
            std::cin >> vertices_count;
            std::cout << "Enter edges count: ";
            std::cin >> edges_count;
            loadEdges(edges_count);
            initializeMatrix(vertices_count);
            loadNexts(vertices_count);
            loadPrevs(vertices_count);
            loadNonInc(vertices_count);
            loadFirst();
            loadSecond();
            loadThird();
            loadNumbers(vertices_count);
            if (hasCycle())
            {
                std::cout << "Matrix has cycle!";
                has_cycle = true;
            }
        }
        
        void printEdges()
        {
            std::cout << std::endl << "edges: " << std::endl;
            for (auto edge: edges)
            {
                std::cout << edge[0] << " " << edge[1] << std::endl;
            }
        }

        void printNexts()
        {
            std::cout << std::endl << "nexts: " << std::endl;
            for (int i = 0; i < nexts.size(); i++)
            {
                std::cout << i + 1 << ": ";
                for (auto x: nexts[i])
                {
                    std::cout << x << " ";
                }
                std::cout << std::endl;
            }
        }

        void printPrevs()
        {
            std::cout << std::endl << "prevs: " << std::endl;
            for (int i = 0; i < prevs.size(); i++)
            {
                std::cout << i + 1 << ": ";
                for (auto x: prevs[i])
                {
                    std::cout << x << " ";
                }
                std::cout << std::endl;
            }
        }

        void printNonInc()
        {
            std::cout << std::endl << "non inc: " << std::endl;
            for (int i = 0; i < ninc.size(); i++)
            {
                std::cout << i + 1 << ": ";
                for (auto x: ninc[i])
                {
                    std::cout << x << " ";
                }
                std::cout << std::endl;
            }
        }

        void printMatrix()
        {
            std::cout << std::endl << "matrix: " << std::endl;
            for (auto row: matrix)
            {
                for (auto x: row)
                {
                    std::cout << x << " ";
                }
                std::cout << std::endl;
            }
        }

        void printSorted()
        {
            for (auto x: kanh_sorted) {
                std::cout << x << " ";
            }
            std::cout << std::endl;
        }

        void sort_DFS()
        {
            if (!hasCycle()) 
            {
                dfs();
            }
            else
            {
                std::cout << "Graf ma cykl - sortowanie niemożliwe";
            }
        }

        void sort_DEL()
        {
            if (!hasCycle())
            {
                del();
                printSorted();
            }
            else
            {
                std::cout << "Graf ma cykl - sortowanie niemożliwe";
            }
        }
};