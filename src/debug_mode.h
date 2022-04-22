void debug_mode()
{
    std::cout << "Debug mode running." << std::endl;

    GraphMatrix matrix = GraphMatrix();
    
    matrix.printEdges();
    matrix.printMatrix();
}