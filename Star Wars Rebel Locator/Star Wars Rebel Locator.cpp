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
	void deleteVertex(string value);
	void deleteEdge(string start, string end);
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
	insertEdge("Corasant", "Naboo", 58);
	insertEdge("Corasant", "Alderaan", 103);
	insertEdge("Corasant", "Dantooine", 30);
	insertEdge("Naboo", "Mustafar", 36);
	insertEdge("Naboo", "Alderaan", 32);
	insertEdge("Naboo", "Kysheek", 11);
	insertEdge("Kysheek", "Alderaan", 77);
	//insertEdge("Tatooine", "Mustafar", 230);
	insertEdge("Tatooine", "Dantooine", 205);
}

//insert vertex
void Graph::insertVertex(string value) {
	bool found = false;
	for (int x = 0; x < Graph::vertices.size(); x++) {
		if (vertices[x].key == value) {
			found = true;
			break;
		}//end if
	}//end for loop
	if (found == false) {
		vertex new_vertex;
		new_vertex.key = value;
		vertices.push_back(new_vertex);
	}

}//end of insert Vertex

 //insert edge
void Graph::insertEdge(string start, string end, int weight) {
	adjVertex adjacent;
	for (int x = 0; x < vertices.size(); x++) {
		if (vertices[x].key == start) {
			for (int y = 0; y < vertices.size(); y++) {
				if (vertices[y].key == end && x != y) {
					adjacent.v = &vertices[y];
					adjacent.weight = weight;
					vertices[x].adjacent.push_back(adjacent);
					adjacent.v = &vertices[x];
					vertices[y].adjacent.push_back(adjacent);
				}
			}//end of for statement
		}//end of if statement
	}//for loop end
}//func end

//Delete edge
void Graph::deleteEdge(string start, string end) {
	for (int x = 0; x < vertices.size(); x++) {
		if (vertices[x].key == start) {
			for (int y = 0; y < vertices.size(); y++) {
				if (vertices[y].key == end && x != y) {
//------------------------Deleting the edges here---------------------
					for (int a = 0; a < vertices[x].adjacent.size(); a++) {
						if (vertices[x].adjacent[a].v->key == end) {
							vertices[x].adjacent.erase(vertices[x].adjacent.begin() + a);
						}//end of deleting x side of edge
					}//end of for a
					for (int a = 0; a < vertices[y].adjacent.size(); a++) {
						if (vertices[y].adjacent[a].v->key == start) {
							vertices[y].adjacent.erase(vertices[y].adjacent.begin() + a);
						}//end of deleting y side of edge
					}//end of for a redux
//---------------------------------------------------------------------
				}//end of if 
			}//end of for statement
		}//end of if statement
	}//for loop end
}//func end

//Delete Vertex
void Graph::deleteVertex(string value) {
	for (int x = 0; x < vertices.size(); x++) {
		if (vertices[x].key == value) {
			for (int y = 0; y < vertices[x].adjacent.size(); y++) {
				//deletes every edge first
				deleteEdge(vertices[x].key, vertices[x].adjacent[y].v->key);

			}//end of for y
			//then deletes the full vertex
			vertices.erase(vertices.begin() + x);
		}//end of if
		else {
			cout << "could not find world" << endl;
		}
	}//end of for x
}

 //print Graph
void Graph::printGraph() {
	for (int x = 0; x < vertices.size(); x++) {
		cout << vertices[x].key << endl;
		for (int y = 0; y < vertices[x].adjacent.size(); y++) {
			string placeholder = vertices[x].adjacent[y].v->key;
			cout << " - " << placeholder << endl;
		}
	}
}

//menu
void display_menu() {
	string querry1 = " ";
	string querry2 = " ";
	int querry3 = 0;
	int querry4 = 1;

	cout << "======Main Menu======" << endl;
	cout << "1. Print Galactic Map" << endl;
	cout << "2. Update Galactic Map - Base Compromised" << endl;
	cout << "3. Update Galactic Map - New Outpost Established" << endl;
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
		cout << "Update the Galactic Map: " << endl;
		cout << "Which world has been comprimised?:" << endl;
		cin >> querry1;
		Galaxy.deleteVertex(querry1);
		break;
	case 3:
		cout << "Update the Galactic Map: " << endl;
		cout << "Whats the name of the new rebel held world?:" << endl;
		cin >> querry1;
		Galaxy.insertVertex(querry1);
		cout << "How many secure Hyperlane connections does it have?:" << endl;
		cin >> querry3;
		for (int x = 0; x < querry3; x++) {
			cout << "List a connected plannet and a distance:" << endl;
			cin >> querry2;
			cin >> querry4;
			Galaxy.insertEdge(querry1, querry2, querry4);
		}

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
		return;
	}
	display_menu();
}

int main()
{
	display_menu();


	cin.get();
    return 0;
}

