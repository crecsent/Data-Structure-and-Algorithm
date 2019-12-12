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
		int * preVertice = new int[vertex];//���ÿ���ڵ㵽ָ��������·���ϵĵ�һ��ǰ���ڵ�
		int * pathLength = new int[vertex];//ÿ���ڵ㵽ָ��������е����·������
		bool * visited = new bool[vertex] {};//�жϸ��ڵ��Ƿ����ҵ���ָ��������·��

		fill(preVertice, preVertice + vertex, -1);
		fill(pathLength, pathLength + vertex, INT_MAX);
		pathLength[source] = 0;

		int currentVertice = source;//���ÿһ��ȷ�������������·����Ŀ��ڵ�
		Node * currentNode;//Ŀ��ڵ���ڽӽڵ�

		while (currentVertice != -1)
		{
			visited[currentVertice] = true;
			currentNode = adjList[currentVertice].link;
			//���ʵ�ǰĿ��ڵ�������ڽӽڵ㣬�ж����ǵ�ָ������·���Ƿ��ܸ���
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
			currentVertice = getNextVertice(visited, pathLength);//�õ����·����δȷ�������нڵ���·��������̵��Ǹ��ڵ�
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
	//�������·����δȷ������visitedΪfalse�������нڵ���·��������̵��Ǹ��ڵ����ţ����򷵻�-1
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