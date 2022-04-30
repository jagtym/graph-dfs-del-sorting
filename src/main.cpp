#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <list>
#include <deque>
#include <stack>
#include <fstream>
#include <chrono>

#include "./graph-implementations/GraphLoader.h"
#include "./graph-implementations/GraphSorter.h"
#include "./graph-implementations/GraphMatrix.h"

#include "debug_mode.h"
#include "manual_mode.h"

int main(int argc, char* argv[]) 
{
    if (argc != 2)
    {
        std::cout << "usage: GraphSorting <mode>" << std::endl;
        return 1;
    }
    else if (std::string(argv[1]) == "debug")
    {
        debug_mode(false);
    }
    else if (std::string(argv[1]) == "file")
    {
        debug_mode(true);
    }
}