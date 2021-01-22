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
int coreness[MaxVertices + 1];
int vertexColor[MaxVertices + 1];
vector<int> index(MaxVertices);
vector<int> bestClique;
int Max = -1;
int MaxColor = 0;

void signalHandler(int);
void FindKCore(int);
void FindClique();
void chooseVertex(int, vector<int>, bool*, bool*);
bool isLinkAll(int, size_t, bool*);
void coloring();
bool myCompare(int a, int b) { return coreness[a] > coreness[b]; }

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

	FindKCore(K);
	FindClique();

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
	vector<int> cur;
	bool inCur[MaxVertices] = {false};
	bool usedColor[MaxVertices] = {false};
	coloring();

	chooseVertex(0, cur, inCur, usedColor);

	ofstream fout("clique.txt");
	if (!fout)
	{
		cout << "fail\n";
		exit(1);
	}

	sort(bestClique.begin(), bestClique.end());

	for (auto i : bestClique)
		fout << i << endl;

	fout.close();
}

void chooseVertex(int inx, vector<int> cur, bool *inCur, bool *usedColor)
{
	if ((int)bestClique.size() == coreness[index[0]] + 1 || inx >= Max + 1)
		return;

	if (usedColor[vertexColor[index[inx]]] == false && isLinkAll(index[inx], cur.size(), inCur))
	{
		cur.push_back(index[inx]);
		inCur[index[inx]] = true;
		usedColor[vertexColor[index[inx]]] = true;
		if (cur.size() > bestClique.size())
			bestClique = cur;

		chooseVertex(inx + 1, cur, inCur, usedColor);
		cur.pop_back();
		inCur[index[inx]] = false;
		usedColor[vertexColor[index[inx]]] = false;
		chooseVertex(inx + 1, cur, inCur, usedColor);
	}
	else
		chooseVertex(inx + 1, cur, inCur, usedColor);

}

bool isLinkAll(int vertex, size_t size, bool *inCur)
{
	size_t count = 0;

	if (size == 0)
		return true;

	for (auto i : graph[vertex])
		if (inCur[i])
			if (++count == size)
				return true;

	return false;
}

void coloring()
{
	bool available[MaxVertices + 1];

	iota(index.begin(), index.end(), 0);

	sort(index.begin(), index.begin() + Max, myCompare);


	for (int i = 0; i <= Max; i++)
	{
		vertexColor[i] = -1;
		available[i] = false;
	}
	
	vertexColor[index[0]] = 0;

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

		vertexColor[index[i]] = cr;
		MaxColor = max(cr, MaxColor);
		
		for (it = graph[index[i]].begin(); it < graph[index[i]].end(); ++it)
			if (vertexColor[*it] != -1)
				available[vertexColor[*it]] = false;
	}
}


void signalHandler(int signum) {
// In the signal handler, we output the current best clique that we found.

	ofstream fout("clique.txt");
	if (!fout)
	{
		cout << "fail\n";
		exit(1);
	}

	vector<int> temp = bestClique;

	sort(temp.begin(), temp.end());

	for (auto i : temp)
		fout << i << endl;

	fout.close();	exit(signum);
}

// By ARui
