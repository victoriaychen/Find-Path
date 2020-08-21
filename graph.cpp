/*
graph.cpp
Description: Implementation of the public and private function for
              graph class. This .cpp contains functions read in from
              the .vdat file, processes commands, add vertex to the graph,
              list and print out the all of the cities, calculate the
             distance between two cities, and find and print paths between
             two cities.
*/
#include <iostream>
#include <cstdlib>
#include <iomanip>
#include "graph.h"
using namespace std;

// Constructor
// Parameters: none
// Returns: none
// Does: Initializes the private variables
Graph::Graph(){
        num_found = 0;
        find_path = false;
        valid_city = false;
}

// Destructor
// Parameters: none
// Returns: none
// Does: Deletes the dynamically allocated memory
Graph::~Graph(){
        for (unsigned int i = 0; i < cities.size(); i++){
                delete[] edge[i];
        }
        delete[] edge;
}

// process_command()
// Parameters: istream input
// Returns: none
// Does: Take command from istream and call different function based on the
//       input command
void Graph::process_command(istream &input){
        string command;
        string city1;
        string city2;
        int maxpaths;
        while (input >> command){
                if (command == "list"){
                        list();
                }else if (command == "dist"){
                        input >> city1;
                        input >> city2;
                        dist (city1, city2);
                }else if (command == "quit" ){
                        exit(0);
                }else if (command == "path"){
                        input >> city1;
                        input >> city2;
                        input >> maxpaths;
                        path (city1, city2, maxpaths);
                }else{
                        cout << "-EOT-" << endl;
                }
        }
}

// populate_graph_from_file()
// Parameters: char *vdat, char *adat, Graph &g
// Returns: none
// Does: Add cities and edge to graph, initiize edges
void Graph::populate_graph_from_file(char *vdat, char *adat, Graph &g){
        read_vdat(vdat, g);
        initiize_edge();
        read_adat(adat, g);
}

// read_vdat()
// Parameters: char *vdat, Graph &g
// Returns: none
// Does: Add cities to cities vector
void Graph::read_vdat(char *vdat, Graph &g){
        ifstream infile;
        infile.open(vdat);
        if (!infile.is_open()) {
            cerr << "Unable to open " << vdat << endl;
            exit(1);
        }

        string line_info;
        string name;
        Location location;
        int la_deg, la_min, lo_deg, lo_min;

        getline(infile, line_info);
        while (!infile.eof()){
                istringstream input (line_info);
                input >> name;
                input >> la_deg;
                input >> la_min;
                input >> lo_deg;
                input >> lo_min;
                g.add_vertex(name, la_deg, la_min, lo_deg, lo_min);
                getline(infile, line_info);
        }
        infile.close();
}

// read_adat()
// Parameters: char *adat, Graph &g
// Returns: none
// Does: Add edges to the 2D array
void Graph::read_adat(char *adat, Graph &g){
        ifstream infile;
        infile.open(adat);
        if (!infile.is_open()) {
            cerr << "Unable to open " << adat << endl;
            exit(1);
        }

        string line_info;
        string city1;
        string city2;

        getline(infile, line_info);
        while (!infile.eof()){
                istringstream input (line_info);
                input >> city1;
                input >> city2;
                g.add_edge(city1, city2);
                getline(infile, line_info);
        }
        infile.close();
}
// add_vertex()
// Parameters: string name, int la_deg, int la_min, int lo_deg, int lo_min
// Returns: none
// Does: Add each city's name and location to vector
void Graph::add_vertex(string name, int la_deg, int la_min, int lo_deg, int lo_min){
        City c;
        double latitude, longtitude;
        //Edge Case: if the degree is neg (south and west), min should not be neg
        if (la_deg < 0){
                latitude = (double)la_deg - (double)la_min/60;
        }else {
                latitude = (double)la_deg + (double)la_min/60;
        }

        if (lo_deg < 0){
                longtitude = (double)lo_deg - (double)lo_min/60;
        }else{
                longtitude = (double)lo_deg + (double)lo_min/60;
        }

        Location location (latitude, longtitude);
        c.name = name;
        c.location = location;
        cities.push_back(c);
}

// add_edge()
// Parameters: string city, string city
// Returns: none
// Does: Add edges to adjacency matrix
void Graph::add_edge(string city1, string city2){
        int row;
        int column;
        for (unsigned int i = 0; i < cities.size(); i++){
                if (city1 == cities[i].name){
                        row = i;
                }
                if (city2 == cities[i].name){
                        column = i;
                }
        }
        edge[row][column] = true;
}

// initiize_edge()
// Parameters: none
// Returns: none
// Does: Add edges to adjacency matrix
void Graph::initiize_edge(){
        edge = new bool *[cities.size()];
        for (int i = 0; i < cities.size(); i++ ){
                edge[i] = new bool [cities.size()];
                for (int j = 0; j < cities.size(); j++ ){
                        edge[i][j] = false;
                }
        }
}

// list()
// Parameters: char *filename, Graph &g
// Returns: none
// Does: Print out all cities from the vector
void Graph::list(){
        for (unsigned int i = 0; i < cities.size(); i++){
                cout << cities[i].name << endl;
        }
        cout << "-EOT-" << endl;
}

// dist()
// Parameters: string city1, string city2
// Returns: double
// Does: Calculate the distance between two cities
double Graph::dist(string city1, string city2){
        double result;
        bool valid_cities = false;
        Location *to;
        Location *from;
        for (unsigned int i = 0; i < cities.size(); i++){
                if (city1 == cities[i].name){
                        from = &cities[i].location;
                        valid_cities = true;
                }

                if (city2 == cities[i].name){
                        to = &cities[i].location;
                        valid_cities = true;
                }
        }
        if (valid_cities == true){
                result = from->distance_to(to);
                cout << result << endl;
        }else{
                result = -1.00;
                cout << setprecision(2) << fixed << result  << endl;
        }
        cout << "-EOT-" << endl;
        return result;
}

// index_is()
// Parameters: string city
// Returns: int
// Does: find index from a string
int Graph::index_is (string city){
        int index;
        for (unsigned int i = 0; i < cities.size(); i++){
                if (city == cities[i].name){
                        index = i;
                        valid_city = true;
                }
        }
        return index;
}

// index_is_from_City()
// Parameters: City city
// Returns: int
// Does: find index from a City
int Graph::index_is_from_City (City city){
        int index;
        for (unsigned int i = 0; i < cities.size(); i++){
                if (city.name == cities[i].name){
                        index = i;
                }
        }
        return index;
}

// path()
// Parameters: string, string, int
// Returns: void
// Does: find paths from one city to another city
void Graph::path(string city1, string city2, int maxpaths){
        for (unsigned int i = 0; i < cities.size(); i++){
                cities[i].visited = false;
        }

        int start_index = index_is (city1);
        int end_index = index_is (city2);
        if (valid_city == false){
                cout << "ERROR: unknown city" << endl;
        }

        cities[start_index].visited = true;
        DFS(cities[start_index], cities[end_index], maxpaths);
        s.clear();
        if (find_path == false){
                cout << "ERROR: no-path-possible" << endl;
        }

        find_path = false;
        valid_city = false;
        num_found = 0;

        cout << "-EOT-" << endl;
}

// DFS()
// Parameters: City, City, int
// Returns: void
// Does: search through all of the cities to find possible paths recursively
void Graph::DFS(City current, City destination, int maxpaths){
        s.push_back(current);
        int index = index_is_from_City (current);
        if (num_found == maxpaths){
                return;
        }
        if (current.name == destination.name){
                num_found++;
                find_path = true;
                if (valid_city == true){
                        print_path();
                }
        }else{
                for (unsigned int i = 0; i < cities.size(); i++){
                        if (edge[index][i] == true && cities[i].visited == false){
                                cities[i].visited = true;
                                 DFS (cities[i], destination, maxpaths);
                                 cities[i].visited = false;
                         }
                }
        }
       s.pop_back();
}

// print_path()
// Parameters: none
// Returns: void
// Does: print out a path
void Graph::print_path(){
        cout << "PATH " << num_found << " :: 0 ";
        cout << s[0].name << " ";
        cout << s[0].location.to_string() << " ";
        for (unsigned int i = 1; i < s.size(); i++){

                cout << int (dist_in_path(s[i-1], s[i])) << " ";
                cout << s[i].name << " ";
                cout << s[i].location.to_string() << " ";
        }
        cout << endl;
}

// dist_in_path()
// Parameters: City, City
// Returns: double
// Does: Calculate the distance between two cities, it is called in path()
double Graph::dist_in_path(City city1, City city2){
        double result;
        Location *to;
        Location *from;
        for (unsigned int i = 0; i < cities.size(); i++){
                if (city1.name == cities[i].name){
                        from = &cities[i].location;
                }

                if (city2.name == cities[i].name){
                        to = &cities[i].location;
                }
        }
        result = from->distance_to(to);
        return result;
}

// test_edge()
// Parameters: string, string
// Returns: none
// Does: testing add_edge()
void Graph::test_edge(string city1, string city2){
        int row;
        int column;
        for (unsigned int i = 0; i < cities.size(); i++){
                if (city1 == cities[i].name){
                        row = i;
                }
                if (city2 == cities[i].name){
                        column = i;
                }
        }
        cout << edge[row][column] << endl;
}

// testing()
// Parameters: string, string
// Returns: none
// Does: Take in command to test edge functions
void Graph::testing(istream &input){
        string command;
        string city1;
        string city2;

        while (input >> command){
                if (command == "test"){
                        input >> city1;
                        input >> city2;
                        test_edge(city1, city2);
                }
        }
}
