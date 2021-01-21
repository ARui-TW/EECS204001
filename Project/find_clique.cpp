#include <iostream>
#include <string>
#include <cstring>
#include <fstream>
#include <assert.h>
#include <csignal>
#include <vector>
#include <algorithm>
#include <stdlib.h>
#include <numeric>

#define MaxVertices 82168

using namespace std;

vector<vector<int>> graph(MaxVertices);
vector<int> graph_rank(MaxVertices);
int vertexColor[MaxVertices + 1];
vector<vector<int>> colorVertex(MaxVertices);
int Max = -1;

void signalHandler(int);
void FindKCore(int);
void FindClique();
void coloring();
bool myCompare(int a, int b) { return graph_rank[a] > graph_rank[b]; }

int main(int argc, char *argv[])
{
	signal(SIGINT, signalHandler);
	assert(argc == 3);

	int u, v, K = stoi(argv[2]);

	ifstream fin(argv[1]);

	if (!fin)
	{
		cout << "fail\n" << argv[1];
		return 1;
	}

	while (fin >> u >> v)
	{
		Max = max(u, max(Max, v));
		graph[u].push_back(v);
		graph[v].push_back(u);
		graph_rank[u]++;
		graph_rank[v]++;
	}

	fin.close();

	// FindKCore(K);
	FindClique();

/*
	cout << Max - 1 << graph_rank[Max - 1];
*/

	return 0;
}

void FindKCore(int K)
{
	ofstream fout("kcore.txt");
	if (!fout)
	{
		cout << "fail\n";
		exit(1);
	}
	
	vector<int> rank_modified(graph_rank);
	bool exist[MaxVertices + 1];
	int coreness[MaxVertices + 1];
	int modified_K = K;
	bool to_stop;
	
	for (int i = 0; i <= MaxVertices; i++)
	{
		exist[i] = true;
		coreness[i] = -1;
	}

	do {
		int count = 0;
		while (count <= Max)
		{
			if (rank_modified[count] < modified_K && exist[count] == true)
			{
				if (rank_modified[count] > 0)
					for (auto j : graph[count])
						rank_modified[j]--;

				exist[count] = false;
				coreness[count] = modified_K - 1;
				count = -1;
			}
			count++;
		}

		to_stop = true;
		for (int i = 0; i <= Max; i++)
			if (exist[i] == true) to_stop = false;

		modified_K++;
	} while (!to_stop);

	for (int i = 0; i <= Max; i++)
	{
		if (coreness[i] >= K)
			fout << i << " " << coreness[i] << endl;
	}

	fout.close();
}

void FindClique()
{
	coloring();



	ofstream fout("clique.txt");
	if (!fout)
	{
		cout << "fail\n";
		exit(1);
	}

	// output...

	fout.close();
}

void coloring()
{
	vector<int> index(Max + 1);
	int MaxColor = 0;
	bool available[MaxVertices + 1];

	iota(index.begin(), index.end(), 0);

	sort(index.begin(), index.end(), myCompare);


	for (int i = 0; i <= Max; i++)
	{
		vertexColor[i] = -1;
		available[i] = false;
	}
	
	vertexColor[index[0]] = 0;
	colorVertex[0].push_back(index[0]);

	for (int i = 1; i <= Max; i++)
	{
		vector<int>::iterator it;

		for (it = graph[index[i]].begin(); it < graph[index[i]].end(); ++it)
			if (vertexColor[*it] != -1)
				available[vertexColor[*it]] = true;

		int cr;
		for (cr = 0; cr < Max; cr++)
			if (available[cr] == false)
				break;

		colorVertex[cr].push_back(index[i]);

		vertexColor[index[i]] = cr;
		MaxColor = max(cr, MaxColor);
		
		for (it = graph[index[i]].begin(); it < graph[index[i]].end(); ++it)
			if (vertexColor[*it] != -1)
				available[vertexColor[*it]] = false;
	}

/*
	for (int i = 0; i <= Max; i++)
	{
		// cout << i << " " << vertexColor[i] << endl;
	}

	ofstream fout("test.txt");
	if (!fout)
	{
		cout << "fail\n";
		exit(1);
	}

	// output...
	for (int i = 0; i <= MaxColor; i++)
	{
		fout << i << ": ";
		for (auto it : colorVertex[i])
			fout << it << " ";
		fout << endl;
	}

	fout.close();
*/
}


void signalHandler(int signum) {

// In the signal handler, we output the current best clique that we found.

	// fstream out("clique.txt");

	// output best...

	exit(signum);
}

// By ARui
