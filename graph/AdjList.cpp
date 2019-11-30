#include<iostream>
using namespace std;

class Node {
	friend class Graph;
	Node(int v = -1, Node * l = nullptr) :vertice(v), link(l) {}
private:
	int vertice;
	Node * link;
};

class Graph {
public:
	Graph() :adjList(nullptr), vertex(0), edge(0) { build(); }
	void build()
	{
		cout << "Enter the number of vertex:" << endl;
		cin >> vertex;
		adjList = new Node[vertex];
		cout << "Enter the number of edge:" << endl;
		cin >> edge;
		int f, t;
		cout << "Enter the two end points of a certain edge or -1 to quit." << endl;
		cin >> f >> t;
		while (f != -1)
		{
			adjList[f].link = new Node(t, adjList[f].link);
			adjList[t].link = new Node(f, adjList[t].link);
			cout << "Enter the two end points of a certain edgeor -1 to quit." << endl;
			cin >> f >> t;
		}
	}
	void print()
	{
		Node * current;
		for (int i = 0; i < vertex; i++)
		{
			current = adjList[i].link;
			cout << i;
			while (current)
			{
				cout << "->" << current->vertice;
				current = current->link;
			}
			cout << endl;
		}
	}
private:
	Node * adjList;//´æ·ÅÁÚ½Ó±í
	int vertex;
	int edge;
};
int main()
{
	Graph g;
	g.print();
	system("pause");
}