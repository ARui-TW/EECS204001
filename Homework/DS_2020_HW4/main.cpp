#include <iostream>
#include <string>

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
	}

	void add(int, int, int, int);
	int request(int, int, int);
	void del(int, int, int);

private:
	int nodeNum;
	Node **city;
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
			int scr, dst, w;

			cin >> scr >> dst >> w;
			cout << gr.request(scr, dst, w) << endl;
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

int Graph::request(int, int, int)
{
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