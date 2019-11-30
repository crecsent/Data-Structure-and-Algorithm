#include<iostream>
#include"minHeap.h"
#include"set.h"
using namespace std;

class Node {
	friend class Graph;
	Node(int v = -1, Node * l = nullptr) :vertice(v), link(l) {}
private:
	int vertice;
	Node * link;
};

class Edge {
	friend ostream & operator<<(ostream & out, const Edge &edge);
	friend class Graph;
public:
	Edge(int w = -1, int f = -1, int t = -1) :weight(w), from(f), to(t) {}
	bool operator>(const Edge & edge)
	{
		return this->weight > edge.weight;
	}
	bool operator>=(const Edge & edge)
	{
		return this->weight >= edge.weight;
	}

private:
	int weight;
	int from;
	int to;
};
ostream & operator<<(ostream & out, const Edge &edge)
{
	out << edge.from << "->" << edge.to << ": " << edge.weight;
	return out;
}
class Graph {
public:
	Graph() : vertex(0), edge(0) { build(); }
	void build()
	{
		cout << "Enter the number of vertex:" << endl;
		cin >> vertex;
		cout << "Enter the number of edge:" << endl;
		cin >> edge;
		int f, t, weight;
		cout << "Enter the two end points of a certain edge and its weight or -1 to quit." << endl;
		cin >> f >> t >> weight;
		while (f != -1)
		{
			edges.push(*(new Edge(weight, f, t)));
			cout << "Enter the two end points of a certain edge and its weight or -1 to quit." << endl;
			cin >> f >> t >> weight;
		}
	}


	void minCostTreeByKruskal()
	{
		cout << "finding the minmum cost tree..." << endl;
		MinHeap<Edge> nextEdges(edges);
		Sets components(vertex);
		Edge leastWeight;
		int totalCost = 0;
		int f, t;
		int fp, tp;
		while (!nextEdges.isEmpty())
		{
			leastWeight = nextEdges.top();
			nextEdges.pop();
			f = leastWeight.from; fp = components.collapsingFind(f);
			t = leastWeight.to; tp = components.collapsingFind(t);

			if (fp == tp && fp >= 0)//该边的两个顶点属于同一连通分量，则加边会形成环。跳过该边
				continue;
			else
			{
				totalCost += leastWeight.weight;
				components.weightedUnion(f, t);
				cout << f << "-" << t << endl;
			}
		}
		cout << "Find the minimum cost tree? " << (components.getSetNumber() == 1) << endl;
		cout << "total cost:" << totalCost << endl;
	}
private:
	MinHeap<Edge> edges;
	int vertex;
	int edge;
};

int main()
{
	Graph g;
	g.minCostTreeByKruskal();
	system("pause");
}