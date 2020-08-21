/*
findpath.cpp
Description:This file contains a main() that makes an instance of the graph
              object and run the program.
*/
#include <iostream>
#include "graph.h"
using namespace std;

int main(int argc, char *argv[])
{
        if (argc != 3) {
                cerr << "Usage: findpath vertex_data edge _data" << endl;
                exit(1);
            return 1;
        }

    Graph g;
    g.populate_graph_from_file(argv[1],argv[2],g);
    g.process_command(cin);

    return 0;
}
