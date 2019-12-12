#pragma once
#include<iostream>
#include<algorithm>
using namespace std;

class Node
{
	friend class WeightedUndiGraph;
public:
	Node(int v = -1, int w = 0, Node * l = nullptr) :vertice(v), weight(w), link(l) {}
private:
	int vertice;
	int weight;
	Node * link;
};
class WeightedUndiGraph
{
public:
	WeightedUndiGraph() :vertex(0), edge(0), adjList(nullptr) { build(); }
	void build() {
		cout << "Enter the number of vertice: " << endl;
		cin >> vertex;
		cout << "Enter the number of edge: " << endl;
		cin >> edge;
		adjList = new Node[vertex];
		for (int i = 0; i < vertex; i++)
			adjList[i].vertice = i;
		int a, b, w;
		cout << "Enter the two end points and the weight of an edge or -1 to quit." << endl;
		cin >> a >> b >> w;
		while (a != -1)
		{
			adjList[a].link = new Node(b, w, adjList[a].link);
			adjList[b].link = new Node(a, w, adjList[b].link);
			cout << "Enter the two end points and the weight of an edge or -1 to quit." << endl;
			cin >> a >> b >> w;
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
	void MSTPrim()
	{
		int * preVertice = new int[vertex];
		fill(preVertice, preVertice + vertex, -1);

		int minimumWeight = INT_MAX, minWeightVertice = -1, minWeightPreVertice = -1, totalWeight = 0;
		bool hasMST = true;
		Node * node;

		preVertice[0] = 0;
		node = adjList[0].link;

		for (int j = 1; j < vertex; j++)//每一轮都确定下来一个新标记的节点及它与某个已标记节点之间的最小权重的边
		{
			minWeightVertice = -1;
			minimumWeight = INT_MAX;

			for (int i = 0; i < vertex; i++)
			{
				if (preVertice[i] >= 0)
				{
					//遍历该节点的所有未被标记的节点，寻找权重最小的边和对应节点
					node = adjList[i].link;
					while (node)
					{
						if (preVertice[node->vertice] < 0 && node->weight < minimumWeight)
						{
							minWeightVertice = node->vertice;
							minWeightPreVertice = i;
							minimumWeight = node->weight;
						}
						node = node->link;
					}
				}
			}
			if (minWeightVertice < 0)//原图非连通
			{
				hasMST = false;
				break;
			}
			else
			{
				preVertice[minWeightVertice] = minWeightPreVertice;
				totalWeight += minimumWeight;
			}
		}
		if (hasMST)
		{
			cout << "Has found the minimum spanning tree. Here are the edges of the MST:" << endl;
			for (int i = 1; i < vertex; i++)
				cout << i << "——" << preVertice[i] << endl;
			cout << "The total weight is: " << totalWeight << endl;
		}
		else
			cout << "This graph doesn't have mst." << endl;

		delete[] preVertice;
	}
private:
	int vertex;
	int edge;
	Node * adjList;
};
int main()
{
	WeightedUndiGraph g;
	g.print();
	g.MSTPrim();
	system("pause");
}