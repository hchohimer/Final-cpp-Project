// Star Wars Rebel Locator.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <istream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <queue>
using namespace std;

struct node {
	node *parent = nullptr;
	node *child = nullptr;
	string key;
	string count;
};


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
	bool solved = false;
	bool active = true;
	int distance = 0;
	vertex *parent = nullptr;
	node *storage = nullptr;
};

//Graph Class and initalizer
class Graph {
private:
	vector <vertex> vertices;
	vertex search(string value);
	void has_item(string planet, string value, int count);
public:
	Graph();
	void insertVertex(string value);
	void insertEdge(string start, string end, int weight);
	void deleteVertex(string value);
	void deleteEdge(string start, string end);
	void printGraph();
	void Dijkstra(string start, string end);
	void Find_Resource();
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
	insertEdge("Corasant", "Dantooine", 35);
	insertEdge("Dantooine", "Mustafar", 30);
	insertEdge("Naboo", "Mustafar", 36);
	insertEdge("Naboo", "Alderaan", 32);
	insertEdge("Naboo", "Kysheek", 11);
	insertEdge("Kysheek", "Alderaan", 77);
	insertEdge("Tatooine", "Mustafar", 230);
	insertEdge("Tatooine", "Dantooine", 205);
	printGraph();
	//Shortest_Course("Kysheek", "Mustafar");
	has_item("Tatooine", "Blasters", 31);
	has_item("Tatooine", "Turbo-Lasers", 11);
	has_item("Tatooine", "Medical-Supplies", 100);
	has_item("Corasant", "Blasters", 5);
	has_item("Corasant", "Fuel", 545);
	has_item("Corasant", "Medical-Supplies", 1000);
	has_item("Naboo", "Fuel", 80);
	has_item("Naboo", "Food", 128);
	has_item("Naboo", "Turbo-Lasers", 50);
	has_item("Dantooine", "Medical-Supplies", 181);
	has_item("Dantooine", "Food", 119);
	has_item("Dantooine", "Blasters", 41);
	has_item("Kysheek", "Food", 503);
	has_item("Kysheek", "Blasters", 505);
	has_item("Kysheek", "Fuel", 500);
	has_item("Mustafar", "Turbo-Lasers", 600);
	has_item("Mustafar", "Fuel", 95);
	has_item("Mustafar", "Medical-Supplies", 15);
	has_item("Alderaan", "Turbo-Lasers", 12);
	has_item("Alderaan", "Blasters", 86);
	has_item("Alderaan", "Food", 200);

}

//search to return vertex of string
vertex Graph::search(string value) {
	for (int x = 0; x < vertices.size(); x++) {
		if (vertices[x].key == value) {
			return vertices[x];
		}//end of if
	}//end of for

}

//initalizing the items a planet has
void Graph::has_item(string planet, string value, int count) {
	vertex found;
	for (int x = 0; x < vertices.size(); x++) {
		if (vertices[x].key == planet) {
			node *temp = new node;
			temp->key = value;
			temp->count = count;
			node *walker;
			if (vertices[x].storage == nullptr) {
				vertices[x].storage = temp;
			}
			else {
				walker = vertices[x].storage;
				while (walker->child != nullptr) {
					walker = walker->child;
				}//end of while
				temp->parent = walker;
				walker->child = temp;
			}//end of else

		}//end of if
	}//end of for
	return;
}


//---------------------------------------------------
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
			int temp = vertices[x].adjacent.size();
			for (int y = temp - 1; y >= 0; y--) {
				//deletes every edge first
				deleteEdge(vertices[x].key, vertices[x].adjacent[y].v->key);
			}//end of for y
			 //then deletes the full vertex
			 //vertices.erase(vertices.begin() + x);
			vertices[x].active = false;
		}//end of if
	}//end of for x
}

//print Graph
void Graph::printGraph() {
	for (int x = 0; x < vertices.size(); x++) {
		if (vertices[x].active)
			cout << vertices[x].key << endl;
		for (int y = 0; y < vertices[x].adjacent.size(); y++) {
			string placeholder = vertices[x].adjacent[y].v->key;
			//int placeholder2 = vertices[x].adjacent[y].weight
			cout << " - " << placeholder << endl;
		}
	}
}


//Dijkstra Search for shortest route
void Graph::Dijkstra(string start, string end) {

	// Initialization
	vertex startV = search(start);
	vertex endV = search(end);
	vertex s;

	int minDistance;
	int dist;
	bool inGraph;


	// Set Initial Planet Conditions
	startV.solved = true;
	startV.distance = 0;


	vector<vertex> solved = { startV };
	vertex *lastStored = nullptr;
	int storedIndex;
	vertex placeholder;

	// Run this until we reach the end planet
	while (!endV.solved)
	{
		vertex solvedV;
		vertex parent;

		minDistance = 20000;

		// For every planet solved run the following
		for (int x = 0; x < solved.size(); x++)
		{
			minDistance = 20000;
			s = solved[x];
			//cout << "New Origin Planet - " << s.key << "\n";

			//Check all adjacent planets for distance and pick shortest
			for (int y = 0; y < s.adjacent.size(); y++)
			{

				// For each adjacent planet check if the vertex is our goal
				// we also need to make sure not to go backwards
				if (!s.adjacent[y].v->solved)
				{

					//cout << "Adjacent Planet Scan - " << s.key << " TO " << s.adjacent[y].v->key << "\n";

					inGraph = false;
					for (int q = 0; q < solved.size(); q++) {
						if (solved[q].key == s.adjacent[y].v->key) {
							inGraph = true;
						}
					}//end of for

					if (s.adjacent[y].v->key == endV.key)
					{
						minDistance = 10000;
						dist = s.distance + s.adjacent[y].weight;
						solvedV = *s.adjacent[y].v;
						minDistance = dist;
						parent = s;
						break;
					}

					if (!inGraph)
					{
						dist = s.distance + s.adjacent[y].weight;
						//cout << "Distance - " << s.key << " TO " << s.adjacent[y].v->key << " - " << dist << "\n";

						// If this distance is the shortest based off minDist (which is set high to set minDistance to first node for evalaution across the other adjacent edges)

						if (dist < minDistance)
						{
							//cout << "Distance is Smaller:" << dist << " MIN: " << minDistance << "\n";
							solvedV = *s.adjacent[y].v;
							minDistance = dist;
							parent = s;
						}
					}
				}
			}
		}

		// Search solved for current and disregard if already solved
		inGraph = false;
		for (int f = 0; f < solved.size(); f++) {
			if (solved[f].key == solvedV.key) {
				inGraph = true;
			}
		}//end of for

		if (!inGraph)
		{
			//cout << "Adding Planet to Solved - " << solvedV.key << "\n";
			solvedV.distance = minDistance;
			solvedV.parent = &parent;
			solvedV.solved = true;
			solved.push_back(solvedV);
			placeholder = solvedV;
			lastStored = &placeholder;
			storedIndex = solved.size() - 1;

			if (endV.key == solvedV.key)
			{
				endV.solved = true;
			}

		}
	}
	cout << "----------------------" << endl;
	cout << "Shortest Distance: " << dist << "\n";
	cout << "Route is as Follows:\n";
	for (int q = 0; q < solved.size(); q++) {
		cout << "--" << solved[q].key << " \n";
	}//end of for




}//end of func

 //Find Resource
void Graph::Find_Resource() {
	string resource;
	string location;
	string destination;
	cout << " - Blasters" << endl << " - Food" << endl << " - Turbo-Lasers" << endl << " - Medical-Supplies" << endl << " - Fuel" << endl;
	cout << "What Resource are you looking for?:" << endl;
	cin >> resource;
	cout << "Where are you now?: " << endl;
	cin >> location;
	cout << "You can recieve that at these locations: " << endl;
	for (int x = 0; x < vertices.size(); x++) {
		node *walker = vertices[x].storage;
		while (walker != nullptr) {
			if (walker->key == resource) {
				cout << vertices[x].key << endl;
			}//end of if
			walker = walker->child;
		}//end of while
	}//x loop done
	cout << "Where do you want to go?" << endl;
	cin >> destination;
	Dijkstra(location, destination);

}//func end




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
	cout << "4. Plot Shortest Course" << endl;
	cout << "5. Search for Vital Resources" << endl;
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
		cout << "Where are you currently?" << endl;
		cin >> querry1;
		cout << "Where would you like to calculate a course to?" << endl;
		cin >> querry2;
		Galaxy.Dijkstra(querry1, querry2);
		break;
	case 5:
		Galaxy.Find_Resource();
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
