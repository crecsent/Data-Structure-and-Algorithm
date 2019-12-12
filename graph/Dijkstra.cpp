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
	WeightedDiGraph() :vertex(0), edge(0), adjList(nullptr) { build(); }
	void build() {
		cout << "Enter the number of vertice: " << endl;
		cin >> vertex;
		cout << "Enter the number of edge: " << endl;
		cin >> edge;
		adjList = new Node[vertex];
		for (int i = 0; i < vertex; i++)
			adjList[i].vertice = i;
		int f, t, w;
		cout << "Enter the start point and end point and the weight of an edge or -1 to quit." << endl;
		cin >> f >> t >> w;
		while (f != -1)
		{
			adjList[f].link = new Node(t, w, adjList[f].link);
			cout << "Enter the start point and end point and the weight of an edge or -1 to quit." << endl;
			cin >> f >> t >> w;
		}
	}
	void print() const
	{
		cout << "The adjList of this graph:" << endl;
		Node * current;
		for (int i = 0; i < vertex; i++)
		{
			cout << adjList[i].vertice << ": ";
			current = adjList[i].link;
			while (current)
			{
				cout << current->vertice << " ";
				current = current->link;
			}
			cout << endl;
		}
		cout << endl;
	}

	void SPTDijkstra(int source)
	{
		int * preVertice = new int[vertex];//存放每个节点到指定点的最短路径上的第一个前驱节点
		int * pathLength = new int[vertex];//每个节点到指定点的现有的最短路径长度
		bool * visited = new bool[vertex] {};//判断各节点是否已找到到指定点的最短路径

		fill(preVertice, preVertice + vertex, -1);
		fill(pathLength, pathLength + vertex, INT_MAX);
		pathLength[source] = 0;

		int currentVertice = source;//存放每一轮确定下来的新最短路径的目标节点
		Node * currentNode;//目标节点的邻接节点

		while (currentVertice != -1)
		{
			visited[currentVertice] = true;
			currentNode = adjList[currentVertice].link;
			//访问当前目标节点的所有邻接节点，判断它们到指定起点的路径是否还能更短
			while (currentNode)
			{
				if (!visited[currentNode->vertice] &&
					pathLength[currentVertice] + currentNode->weight <= pathLength[currentNode->vertice])
				{
					preVertice[currentNode->vertice] = currentVertice;
					pathLength[currentNode->vertice] = pathLength[currentVertice] + currentNode->weight;
				}
				currentNode = currentNode->link;
			}
			currentVertice = getNextVertice(visited, pathLength);//得到最短路径仍未确定的所有节点中路径长度最短的那个节点
		}

		cout << "Have finished the finding of shortest pathes to vertice " << source << endl;
		for (int i = 0; i < vertex; i++)
		{
			int v = i;
			while (preVertice[v] != -1)
			{
				cout << v << "->";
				v = preVertice[v];
			}
			cout << source << "=" << pathLength[i] << endl;
		}

		delete[] preVertice;
		delete[] pathLength;
		delete[] visited;
	}

private:
	//返回最短路径仍未确定（即visited为false）的所有节点中路径长度最短的那个节点的序号，否则返回-1
	int getNextVertice(bool * visited, int * pathLength)
	{
		int index = -1, shortestLength = INT_MAX;
		for (int i = 0; i < vertex; i++)
		{
			if (!visited[i] && pathLength[i] < shortestLength)
			{
				index = i;
				shortestLength = pathLength[i];
			}
		}
		return index;
	}
	int vertex;
	int edge;
	Node * adjList;
};

int main()
{
	WeightedDiGraph g;
	g.print();
	g.SPTDijkstra(0);
	system("pause");
}