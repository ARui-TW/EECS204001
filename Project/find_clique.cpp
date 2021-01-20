#include <iostream>
#include <string>
#include <cstring>
#include <fstream>
#include <assert.h>
#include <csignal>
#include <vector>
#include <algorithm>
#include <stdlib.h>

#define MaxVertices 82168

using namespace std;

vector<vector<int>> graph(MaxVertices);
vector<int> graph_rank(MaxVertices);
int Max = -1;

void signalHandler(int);
void FindKCore(int);

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

/*
	for (int i = 0; i <= Max; i++)
	{
		for (auto j : graph[i])
		{
			fout << i << " " << j << endl;
		}
	}
*/
	
	vector<int> rank_modified(graph_rank);
	// bool *exist = new bool(MaxVertices + 1);
	// int *coreness = new int(MaxVertices +1);

	bool exist[MaxVertices + 1];
	int coreness[MaxVertices + 1];

	cout << "ONe\n";
	
	for (int i = 0; i <= MaxVertices; i++)
	{
		// cout << i << endl;
		exist[i] = true;
		coreness[i] = -1;
		
	}
	 
	int modified_K = K;

	cout << "Twi\n";
	bool to_stop;

	do {
		int count = 0;
		while (count <= Max)
		{
			if (rank_modified[count] < modified_K && exist[count] == true)
			{
				if (rank_modified[count] > 0)
					for (auto j : graph[count])
						rank_modified[j]--;

				cout << "THere:" << count << endl;
				exist[count] = false;
				coreness[count] = modified_K - 1;
				count = -1;
			}
			count++;
			// cout << "Here:" << count << endl;
		}

		to_stop = true;
		for (int i = 0; i <= Max; i++)
			if (exist[i] == true) to_stop = false;

		modified_K++;
		cout << "K: " << modified_K << endl;
	} while (!to_stop);
/*
	while (1)
	{
		bool to_break = true;
		for (int i = 0; i <= Max; i++)
			if (exist[i] == true) to_break = false;

		if (to_break) break;
		else K++;

		int count = 0;
		auto i = rank_modified.begin();
		while (i != rank_modified.end())
		{
			if (*i < K && exist[count] == true)
			{
				for (auto j : graph[count])
					rank_modified[j]--;

				if (rank_modified[1] < K) cout << count << endl;
				exist[count] = false;
				coreness[count] = K - 1;
				i = rank_modified.begin();
				count = -1;
			}
			if (count != -1) i++;
			count++;
		}
	}
*/

	fout << "====\n";
	cout << K;

	for (int i = 0; i <= Max; i++)
	{
		if (coreness[i] >= K)
			fout << i << " " << coreness[i] << endl;
	}

	fout.close();
	cout << "Done\n";
	exit(0);
}

void signalHandler(int signum) {

// In the signal handler, we output the current best clique that we found.

	// fstream out("clique.txt");

	// output best...

	exit(signum);
}

// By ARui
