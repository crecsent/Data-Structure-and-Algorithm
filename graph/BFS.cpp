#include<iostream>
#include<queue>
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
		for (int i = 0; i < vertex; i++)
			adjList[i].vertice = i;
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
	void printAdjList()
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
	void BFS(int index)
	{
		if (!(index >= vertex || vertex == 0))
		{
			cout << "�Ӷ��� " << index << " �����пɴﶥ��Ϊ:" << endl;
			visited = new bool[vertex] {0};
			visited[index] = true;
			toVisit.push(index);
			Node * current;
			while (!toVisit.empty())
			{
				current = &adjList[toVisit.front()];
				toVisit.pop();
				cout << current->vertice << " ";
				current = current->link;
				while (current)//�ҵ���ǰ�ڵ������δ���ʹ����ڽӽڵ㣬�����������������
				{
					if (!visited[current->vertice])
					{
						toVisit.push(current->vertice);
						visited[current->vertice] = true;
					}
					current = current->link;
				}
			}
			cout << endl;
			delete[]visited;
		}
	}

private:
	Node * adjList;//����ڽӱ�
	queue<int> toVisit;
	bool * visited;
	int vertex;
	int edge;
};

int main()
{
	cout << "����ȫ��ͨͼ��" << endl;
	Graph g1;
	cout << "�ڽӱ�" << endl;
	g1.printAdjList();
	g1.BFS(0);
	g1.BFS(3);
	cout << "������2����ͨ�����ķ���ͨͼ��" << endl;
	Graph g2;
	cout << "�ڽӱ�" << endl;
	g2.printAdjList();
	g2.BFS(0);
	g2.BFS(3);
	cout << "�������ж��㻥����ͨ��ͼ��" << endl;
	Graph g3;
	cout << "�ڽӱ�" << endl;
	g3.printAdjList();
	g3.BFS(0);
	g3.BFS(3);

	system("pause");
}