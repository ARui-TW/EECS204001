#include <iostream>
#include <string>
#include <algorithm>
#include <limits.h>

using namespace std;

class Node
{
	friend class Graph;

public:
	Node();
	Node(int d, int p, int a) : dest(d), airline(a), price(p) {}

private:
	int dest;
	int airline;
	int price;
	Node *nxt;
};

class Graph
{
public:
	Graph(int n) : nodeNum(n) {
		city = new Node*[n];

		for (int i = 0; i < n; i++)
			city[i] = NULL;

		visited = new bool[n];
	}

	void add(int, int, int, int);
	int request(int, int, int, int);
	void setBool();
	void del(int, int, int);

private:
	int nodeNum;
	Node **city;
	bool *visited;
};

int main(int argc, char *argv[])
{
	int n;
	string command;
	cin >> n;
	Graph gr(n);

	while (cin >> command)
	{
		if (command == "Add")
		{
			int scr, dst, w, a;

			cin >> scr >> dst >> w >> a;
			gr.add(scr, dst, w, a);
		}
		else if (command == "Request")
		{
			int scr, dst, w, ans;

			cin >> scr >> dst >> w;

			gr.setBool();
			ans = gr.request(scr, dst, w, -1);
			ans = (ans == INT_MAX)? -1 : ans;
			cout << ans << endl;
		}
		else if (command == "Delete")
		{
			int u, v, a;

			cin >> u >> v >> a;
			gr.del(u, v, a);
		}
		else cout << "error: invalid command\n";
	}


	return 0;
}

void Graph::add(int srt, int dest, int price, int airline)
{
	Node *node = new Node(dest, price, airline);

	node->nxt = city[srt];
	city[srt] = node;
}

void Graph::setBool()
{
	fill(visited, visited + nodeNum, false);
}

int Graph::request(int start, int dist, int budget, int lastAirline)
{
	if (start == dist)
		return 0;

	Node *cur = city[start];
	int price = INT_MAX, temp;
	int curPrice;

	visited[start] = true;

	while (cur)
	{
		curPrice = (lastAirline == cur->airline || lastAirline == -1)? cur->price : cur->price + 5;

		if (!visited[cur->dest] && (budget - curPrice) >= 0)
		{
			temp = request(cur->dest, dist, budget - curPrice, cur->airline);
			temp = (temp == INT_MAX)? temp : temp + curPrice;
			price = min(temp, price);
		}

		cur = cur->nxt;
	}

	visited[start] = false;

	return price;
}

void Graph::del(int start, int dest, int airline)
{
	Node *cur = city[start], *pre = NULL;

	while (cur)
	{
		if (cur->dest == dest && cur->airline == airline)
		{
			if (pre)
				pre->nxt = cur->nxt;
			else
				city[start] = cur->nxt;

			delete cur;
			cur = pre;
		}
		pre = cur;
		cur = (cur)? cur->nxt : city[start];
	}
}

// By ARui