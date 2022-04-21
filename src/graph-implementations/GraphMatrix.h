class GraphMatrix
{
    int vertices_count = 0;
    int edges_count = 0; 

    std::vector<std::vector<int>> edges;

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

    public:
        GraphMatrix()
        {
            std::cout << "Enter vertices count: ";
            std::cin >> vertices_count;
            std::cout << "Enter edges count: ";
            std::cin >> edges_count;
            loadEdges(edges_count);
        }
        
        void printEdges()
        {
            std::cout << "Edges: " << std::endl;
            for (auto edge: edges)
            {
                std::cout << edge[0] << " " << edge[1] << std::endl;
            }
        }
};