#include<iostream>
#include<algorithm>
using namespace std;

class Node
{
	friend class WeightedDiGraph;
public:
	Node(int v = -1, int w = 0, Node * l = nullptr) :vertice(v), weight(w), link(l) {}

private:
	int vertice;
	int weight;
	Node * link;
};

class WeightedDiGraph {
public:
	WeightedDiGraph() :vertex(0), adjMatrix(nullptr) { build(); }
	void build() {
		cout << "Enter the number of vertice: " << endl;
		cin >> vertex;

		adjMatrix = new int *[vertex];
		for (int i = 0; i < vertex; i++)
		{
			adjMatrix[i] = new int[vertex];
			for (int j = 0; j < vertex; j++)
				adjMatrix[i][j] = (i != j ? max : 0);
		}

		int f, t, w;
		cout << "Enter the start point and end point and the weight of an edge or -1 to quit." << endl;
		cin >> f >> t >> w;
		while (f != -1)
		{
			adjMatrix[f][t] = w;
			cout << "Enter the start point and end point and the weight of an edge or -1 to quit." << endl;
			cin >> f >> t >> w;
		}
	}
	void print() const
	{
		cout << "The adjMatrix of this graph:" << endl;
		for (int i = 0; i < vertex; i++)
		{
			for (int j = 0; j < vertex; j++)
				cout << adjMatrix[i][j] << " ";
			cout << "\n\n";
		}
	}
	void AllSPTFloyd()
	{
		int ** pathLength = new int *[vertex];
		for (int i = 0; i < vertex; i++)
		{
			pathLength[i] = new int[vertex];
			for (int j = 0; j < vertex; j++)
				pathLength[i][j] = adjMatrix[i][j];
		}
		for (int k = 0; k < vertex; k++)
			for (int i = 0; i < vertex; i++)
				for (int j = 0; j < vertex; j++)
					if (pathLength[i][j] > pathLength[i][k] + pathLength[k][j])
						pathLength[i][j] = pathLength[i][k] + pathLength[k][j];

		for (int i = 0; i < vertex; i++)
		{
			cout << "Vertice " << i << " 's all shortest path: ";
			for (int j = 0; j < vertex; j++)
				cout << pathLength[i][j] << " ";
			cout << "\n\n";
		}
		for (int i = 0; i < vertex; i++)
		{
			delete [] pathLength[i];
		}
		delete[] pathLength;
	}

private:
	const static int max = 99999;
	int vertex;
	int ** adjMatrix;
};

int main()
{
	WeightedDiGraph g;
	g.print();
	g.AllSPTFloyd();
	system("pause");
}