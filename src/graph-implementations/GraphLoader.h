class GraphLoader {
    bool fromFile_;
    std::string fileName_ = "dane.txt";

    int &verticesCount_;
    int &edgesCount_;
    
    std::vector<std::vector<int>> &graphEdges_;
    std::list<int> *alternativeEdges_;

    void loadFromFile() {
        std::ifstream file;
        file.open(fileName_);

        if (!file.is_open()) {
            std::cout << "File not found!" << std::endl;
            return;
        }

        file >> verticesCount_ >> edgesCount_;
        alternativeEdges_ = new std::list<int>[verticesCount_ + 1];

        int from, to;
        while (file >> from >> to) {
            std::vector<int> edge = {from, to};
            graphEdges_.push_back(edge);
            alternativeEdges_[from].push_back(to);
        }

        file.close();
    }

    void loadFromUI() {
        std::cout << "Enter vertices count: ";
        std::cin >> verticesCount_;

        std::cout << "Enter edges count: ";
        std::cin >> edgesCount_;

        alternativeEdges_ = new std::list<int>[verticesCount_ + 1];

        for (int i = 0; i < edgesCount_; i++) {
            int from, to;
            std::cin >> from >> to;
            std::vector<int> edge = {from, to};
            graphEdges_.push_back(edge);
            alternativeEdges_[from].push_back(to);
        }

    }

    public:
        GraphLoader(int &verticesCount, int &edgesCount, std::vector<std::vector<int>> &graphEdges, bool fromFile) 
        : graphEdges_(graphEdges),
          verticesCount_(verticesCount),
          edgesCount_(edgesCount)
        {
            fromFile_ = fromFile;
        }

        void loadGraph() {
            if (fromFile_) {
                loadFromFile();
            } else {
                loadFromUI();
            }
        }

        std::list<int>* getAlternativeEdges() {
            return alternativeEdges_;
        }
};