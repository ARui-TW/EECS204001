#include <iostream>
#include <string>
#include <algorithm>
#include <limits.h>
#include <stack>

using namespace std;

class Node
{
	friend class Graph;

public:
	Node();
	Node(int w, int d) : weight(w), dest(d){}

private:
	int weight, dest;
	Node *nxt;
};

class Graph
{
public:
	Graph(int n) : verNum(n), updated(false) {
		ver = new Node*[n];

		for (int i = 0; i < n; i++)
			ver[i] = NULL;
        
        arr = new double*[n];
        length = new int*[n];

        for (int i = 0; i < n; i++)
        {
            arr[i] = new double[n]; 
            length[i] = new int[n]; 
            for (int j = 0; j < n; j++)
            {
                length[i][j] = INT_MAX / 2;
                arr[i][j] = INT_MAX / 2;
            }
            length[i][i] = 0;
            arr[i][i] = 0;
        }

	}

	void add(int, int, int);
	void del(int, int);
    void AC();
    bool connected();
    void SOSPD();
    bool updated;
    int ACver1;
    int ACver2;
    double ecc;

private:
	int verNum;
	Node **ver;
    double **arr;
    int **length;
    int **r;
    double tempm;
    double tempn;
};

int main(int argc, char *argv[])
{
    int n, v1, v2, weight;
    string input;

    cin >> n;

    Graph gr(n);

    while (cin >> input)
    {
        if (input == "Add")
        {
            gr.updated = false;
            cin >> v1 >> v2 >> weight;
            gr.add(v1, v2, weight);
        }
        else if (input == "Delete")
        {
            gr.updated = false;
            cin >> v1 >> v2;
            gr.del(v1, v2);
        }
        else if (input == "AC")
        {
            if (n == 1)
                cout << 0 << endl;
            else
            {
                if (!gr.connected())
                {
                    cout << "Not connected graph\n";
                    continue;
                }
                if (!gr.updated)
                    gr.AC();
                
                gr.updated = true;
                if (gr.ACver2 == -1)
                    cout << gr.ACver1 << endl;
                else
                    cout << gr.ACver1 << " " << gr.ACver2 << endl;
            }
        }
        else if (input == "Diameter")
        {            
            if (n == 1)
            {
                cout << 0 << endl;
                continue;
            }
            if (!gr.connected())
            {
                cout << "Not connected graph\n";
                continue;
            }

            if (!gr.updated)
                gr.AC();
            
            gr.updated = true;

            cout << gr.ecc * 2 << endl;
        }
        else if (input == "SOSPD")
        { 
            if (n == 1)
            {
                cout << 0 << endl;
                continue;
            }

            if (!gr.connected())
            {
                cout << "Not connected graph\n";
                continue;
            }

            if (!gr.updated)
                gr.AC();
            
            gr.updated = true;

            gr.SOSPD();
        }
        else
            cout << "Error command\n";
    }
    
    return 0;
}

void Graph::add(int v1, int v2, int weight)
{
	Node *cur = ver[v1];

	while (cur)
    {
        if (cur->dest == v2)
            break;

		cur = cur->nxt;
    }

    if (cur)
        cur->weight = weight;
    else
    {
        Node *node = new Node(weight, v2);
        node->nxt = ver[v1];
        ver[v1] = node;
    }

    cur = ver[v2];

	while (cur)
    {
        if (cur->dest == v1)
            break;

		cur = cur->nxt;
    }

    if (cur)
        cur->weight = weight;
    else
    {
        Node *node = new Node(weight, v1);
        node->nxt = ver[v2];
        ver[v2] = node;
    }

    length[v1][v2] = weight;
    length[v2][v1] = weight;
}

void Graph::del(int v1, int v2)
{
	Node *cur = ver[v1], *pre = NULL;

	while (cur)
	{
		if (cur->dest == v2)    // find to delte
		{
			if (pre)            // not first
				pre->nxt = cur->nxt;
			else                // is first
				ver[v1] = cur->nxt;

			delete cur;
            break;
		}
		pre = cur;
		cur = cur->nxt;
	}

    cur = ver[v2], pre = NULL;

	while (cur)
	{
		if (cur->dest == v1)    // find to delte
		{
			if (pre)            // not first
				pre->nxt = cur->nxt;
			else                // is first
				ver[v2] = cur->nxt;

			delete cur;
            break;
		}
		pre = cur;
		cur = cur->nxt;
	}

    length[v1][v2] = INT_MAX / 2;
    length[v2][v1] = INT_MAX / 2;
}

bool Graph::connected()
{
    bool *visited = new bool[verNum];
    fill(visited, visited + verNum, false);
    
    stack<int> s;
    int v;
    Node *cur;

    s.push(0);

    while (!s.empty())
    {
        v = s.top(); s.pop();
        if (!visited[v])
        {
            visited[v] = true;
            cur = ver[v];
            while (cur)
            {
                if (!visited[cur->dest]) s.push(cur->dest);
                cur = cur->nxt;
            }
        }
    }

    for (int i = 0; i < verNum; i++)
        if (visited[i] == false) return false;
    
    return true;
}

void Graph::AC()
{
    int tempi, tempj;
    for (int i = 0; i < verNum; i++)
        for (int j = 0; j < verNum; j++) 
            arr[i][j]= length[i][j];   

    // path with top vertex index k
    for (int k= 0; k < verNum; k++)
    // all other possible vertices
        for (int i = 0; i < verNum; i++)
            for (int j = 0; j < verNum; j++)
            if ((arr[i][k] + arr[k][j]) < arr[i][j]) {
                arr[i][j] = arr[i][k] + arr[k][j]; 
            }
    
    r = new int*[verNum];

    for (int i = 0; i < verNum; i++)
    {
        r[i] = new int[verNum]; 
        for (int j = 0; j < verNum; j++)
            r[i][j] = j;
    }
    
    for (int i = 0; i < verNum; i++)
    {
        int n = verNum;
        while (n > 1)
        {
            n--;
            for (int j  = 0; j < n; j++)
                if (arr[i][r[i][j]] < arr[i][r[i][j + 1]])
                    swap(r[i][j], r[i][j + 1]);
        }
    }

    ecc = 1.7976931348623158e+308;

    for (int i = 0; i < verNum; i++)
    {
        for (int j = 0; j < verNum; j++)
            for (int a = 0, b = 1; b < verNum; b++)
            {
                if (arr[j][r[i][b]] > arr[j][r[i][a]])
                {
                    if (ecc > (arr[i][r[i][b]] + arr[j][r[i][a]] + length[i][j]) / 2.0)
                    {
                        tempi = i;
                        tempj = j;
                        ecc = (arr[i][r[i][b]] + arr[j][r[i][a]] + length[i][j]) / 2.0;
                        tempm = ecc - arr[i][r[i][b]];
                        tempn = ecc - arr[j][r[i][a]];
                    }
                    a = b;
                }
            }
    }

    bool flag;

    if (arr[tempi][r[tempi][0]] == ecc)
    {
        ACver1 = tempi;
        ACver2 = -1;
    }
    else
    {
        ACver1 = tempi;
        ACver2 = tempj;
        if (ACver1 > ACver2)
            swap(ACver1, ACver2);
    }

    /*
    for (int i = 0; i < verNum; i++)
    {
        for (int j = 0; j < verNum; j++)
            cout << r[i][j] << " ";
        cout << endl;
    }
    */
}

void Graph::SOSPD()
{ 
    bool *visited = new bool[verNum];
    double *dist = new double[verNum];
    int a = 0;

    for (int i = 0; i < verNum; i++)
    {
        visited[i] = false;
        dist[i] = INT_MAX / 2;
    }
    
    if (ACver2 == -1)
    {
        dist[ACver1] = 0;
        visited[ACver1] = true;
        a = 1;
    }
    else
    {
        dist[ACver1] = tempm;
        dist[ACver2] = tempn;
        a = 0;
    }

    for (int i = 0; i < verNum - a; i++)
    {
        int u = 0, temp = INT_MAX / 2;
        for(int j = 0; j < verNum; j++)
            if (temp > dist[j] && visited[j] == false)
            {
                temp = dist[j];
                u = j;
            }
        
        // cout << dist[u] << endl;
        
        visited[u] = true;

        for (int w = 0; w < verNum; w++)
        {
            if (!visited[w] && dist[u] + length[u][w] < dist[w])
                dist[w] = dist[u] + length[u][w];
        }
    }

    double sum = 0;

    for (int i = 0; i < verNum; i++)
        sum += dist[i];
        // cout << dist[i] << " ";

    
    cout << sum << endl;
    
    
}


// By ARui
