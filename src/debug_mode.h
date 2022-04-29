void debug_mode(bool file)
{
    GraphMatrix matrix = GraphMatrix(file);
    
    // matrix.printEdges();
    // matrix.printMatrix();
    // matrix.printNexts();
    // matrix.printPrevs();
    // matrix.printNonInc();

    matrix.sort_DFS();
    matrix.sort_DEL();
}