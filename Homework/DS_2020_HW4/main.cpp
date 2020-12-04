#include <iostream>
#include <string>

using namespace std;

class node
{
	friend class Graph;

public:
	node();

private:
	int nextCity;
	int airline;
	int price;
};

class Graph
{
public:
	Graph(int n) : nodeNum(n) {
		city = new node*[n];
	}

	void add(int, int, int, int);
	int request(int, int, int);
	void del(int, int, int);

private:
	int nodeNum;
	node **city;
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
}

int Graph::request(int, int, int)
{
}

void Graph::del(int, int, int)
{
}

// By ARui