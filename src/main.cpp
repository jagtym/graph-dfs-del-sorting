#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <list>

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

    if (std::string(argv[1]) == "manual") 
    {
        manual_mode();
    } 
    else if (std::string(argv[1]) == "debug")
    {
        debug_mode();
    }
}