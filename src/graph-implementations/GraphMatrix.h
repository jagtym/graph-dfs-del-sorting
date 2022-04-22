class GraphMatrix
{
    int vertices_count = 0;
    int edges_count = 0; 

    std::vector<std::vector<int>> edges;
    std::vector<std::vector<int>> matrix;

    void loadEdges(int edges_number)
    {
        for (int i = 0; i < edges_number; i++)
        {
            int from, to;
            std::cin >> from >> to;
            std::vector<int> edge = {from, to};
            edges.push_back(edge);
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

    public:
        GraphMatrix()
        {
            std::cout << "Enter vertices count: ";
            std::cin >> vertices_count;
            std::cout << "Enter edges count: ";
            std::cin >> edges_count;
            loadEdges(edges_count);
            initializeMatrix(vertices_count);
        }
        
        void printEdges()
        {
            std::cout << std::endl << "edges: " << std::endl;
            for (auto edge: edges)
            {
                std::cout << edge[0] << " " << edge[1] << std::endl;
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
};