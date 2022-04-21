void debug_mode()
{
    std::cout << "Debug mode running." << std::endl;

    GraphMatrix matrix = GraphMatrix();
    
    std::cout << std::endl;
    matrix.printEdges();
}