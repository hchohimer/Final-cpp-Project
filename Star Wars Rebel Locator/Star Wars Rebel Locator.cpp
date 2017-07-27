// Star Wars Rebel Locator.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <istream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
using namespace std;

struct vertex;
//Adjacent Struct
struct adjVertex {
	vertex *v;
	int weight;
};

//vertex struct
struct vertex {
	string key;
	vector<adjVertex> adjacent;
	bool solved;
	int distance;
	vertex *parent;
};

//Graph Class and initalizer
class Graph {
private:
	vector <vertex> vertices;
	void initalizeGraph();
public:
	Graph();
	void insertVertex(string value);
	void insertEdge(string start, string end, int weight);
	void deleteVertex(vertex value);
	void deleteEdge(vertex start, vertex end);
	void printGraph();
	vertex search(vertex value);
};
Graph Galaxy;

//initializer
Graph::Graph() {
	insertVertex("Corasant");
	insertVertex("Tatooine");
	insertVertex("Dantooine");
	insertVertex("Naboo");
	insertVertex("Mustafar");
	insertVertex("Alderaan");
	insertVertex("Kysheek");
	insertEdge("Corasant", "Naboo", 30);
	insertEdge("Corasant", "Alderaan", 30);
	insertEdge("Corasant", "Dantooine", 30);
	insertEdge("Naboo", "Mustafar", 30);
	insertEdge("Naboo", "Alderaan", 30);
	insertEdge("Naboo", "Kysheek", 30);
	insertEdge("Kysheek", "Alderaan", 30);
	insertEdge("Tatooine", "Mustafar", 30);
	insertEdge("Tatooine", "Dantooine", 30);
}

//insert vertex
void Graph::insertVertex(string value) {
	bool found = false;
	for (int x = 0; x < Graph::vertices.size(); x++) {
		if (vertices[x].key == value) {
			found = true;
			break;
		}//end if
		if (found == false) {
			vertex new_vertex;
			new_vertex.key = value;
			vertices.push_back(new_vertex);
		}
	}//end for loop
}//end of insert Vertex

//insert edge
void Graph::insertEdge(string start, string end, int weight ){
	adjVertex adjacent;
	for (int x = 0; x < vertices.size(); x++) {
		if (vertices[x].key == start) {
			for (int y = 0; y < vertices.size(); y++) {
				if (vertices[y].key == end && x != y) {
					adjacent.v = &vertices[y] ;
					adjacent.weight = weight; 
					vertices[x].adjacent.push_back(adjacent);
				}
			}//end of for statement
		}//end of if statement
	}//for loop end
}//func end

//print Graph
void Graph::printGraph() {
	for (int x = 0; x < vertices.size(); x++) {
		cout << vertices[x].key << endl;
		for (int y = 0; y < vertices[x].adjacent.size(); y++) {
			string placeholder = vertices[x].adjacent[y].v->key;
			cout << placeholder << endl;
		}
	}
}

//menu
void display_menu() {

	cout << "======Main Menu======" << endl;
	cout << "1. Print Graph" << endl;
	cout << "2. unassigned" << endl;
	cout << "3. unassigned" << endl;
	cout << "4. unassigned" << endl;
	cout << "5. unassigned" << endl;
	cout << "6. Quit" << endl;

	int switch_value = 0;
	cin >> switch_value;
	switch (switch_value)
	{
	case 1:
		Galaxy.printGraph();
		break;
	case 2:

		break;
	case 3:

		break;
	case 4:

		break;
	case 5:

		break;
	case 6:
		cout << "Goodbye!" << endl;

		return;
	default:
		cout << endl;
		cout << "that was not a valid request" << endl;
		cout << endl;
		break;
	}
	display_menu();
}

int main()
{
	display_menu();


	cin.get();
    return 0;
}

