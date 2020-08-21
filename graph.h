/*
graph.h
Description:Class that Implementation of graph class. This files contains
            function declaration of the graph.cpp. The struct stores the name
            and location of the city. In the private section, the graph class
            contains two vectors: one stores the cities and one is for printing
            path. a 2D array is used for store edge in adjacency matrix.
*/
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <fstream>
#include <stack>
#include "Location.h"

#ifndef GRAPH_H_
#define GRAPH_H_

using namespace std;

struct City{
        string name;
        Location location;
        bool visited;
};

class Graph
{
public:
    Graph();
    ~Graph();

    void populate_graph_from_file(char *vdat, char *adat, Graph &g);
    void process_command(istream &input);
    void list();
    double dist(string city1, string city2);
    void path(string city1, string city2, int maxpaths);

private:
        vector <City> cities;
        bool **edge;
        vector <City> s;
        int num_found;
        bool find_path;
        bool valid_city;

        void read_vdat(char *vdat, Graph &g);
        void read_adat(char *adat, Graph &g);
        void add_vertex(string name, int la_deg, int la_min, int lo_deg, int lo_min);
        void add_edge(string city1, string city2);
        void initiize_edge();
        int index_is (string city);
        int index_is_from_City (City city);
        void DFS(City city1, City city2, int maxpaths);
        void print_path();
        double dist_in_path(City city1, City city2);

        //Testing function
        void testing(istream &input);
        void test_edge(string city1, string city2);
};

#endif
