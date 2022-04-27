void debug_mode()
{
    std::cout << "Debug mode running." << std::endl;

    GraphMatrix matrix = GraphMatrix();
    
    matrix.printEdges();
    matrix.printMatrix();
    matrix.printNexts();
    matrix.printPrevs();
    matrix.printNonInc();

    matrix.sort_DFS();
    matrix.sort_DEL();
}