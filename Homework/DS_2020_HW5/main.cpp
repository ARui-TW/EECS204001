#include <iostream>
#include <string>

using namespace std;

class Node
{
public:
    Node(int a) : num(a)
    {
        child = 0;
        left = NULL;
        right = NULL;
    }

    int num;
    int child;
    Node *left, *right;
};

Node* insert (Node*, int);
int search (Node*, double);
int K_Largest (Node*, int);

void clear (Node *root)
{
    if (root->left)
        clear(root->left);
    if (root->right)
        clear(root->right);

    delete root;
}

int main(int argc, char *argv[])
{
    int n, op;
    int QQ_count;
    Node *searchFrom;
    while (cin >> n >> op)
    {
        QQ_count = 0;
        int *list = new int[n];

        for (int i = 0; i < n; i++)
            cin >> list[i];

        Node *root = new Node(list[n - 1]);

        for (int i = n - 2; i >= 0; i--)
        {
            // cout << i << endl;
            searchFrom = insert(root, list[i]);

            if (!op)
                QQ_count += search(searchFrom, (double)(list[i] / 2.0));

        }

        if (op)
            cout << K_Largest(root, op) << endl;
        else
            cout << QQ_count << endl;

        delete list;
        
        clear(root);
    }

    return 0;
}

Node* insert (Node *root, int num)
{
    Node *ans = NULL;
    Node *cur = root;
    Node *pre = root;
    Node *node = new Node(num);
    bool first = true;

    while (cur)
    {
        // cout << cur->num << " ";
        if (cur->num >= num)
        {
            cur->child++;    
            pre = cur;
            cur = cur->left;
        }
        else // cur->num < num
        {
            if (first)
                ans = cur;
            
            first = false;
            cur->child++;
            pre = cur;
            cur = cur->right;
        }
    }
    // cout << ">" <<endl;
    // cout << pre->num << endl;
    if (pre->num > num)
        pre->left = node;
    else
        pre->right = node;

    return ans;
}

int search(Node* root, double num)
{
    Node *cur = root;
    int ans = 0;

    while (cur)
    {
        if (cur->num >= num)
            cur = cur->left;
        else // cur->num < num
        {
            if (cur->left)
            {
                ans += cur->left->child;
                ans++;
            }
            ans++;

            cur = cur->right;
        }
    }
    // cout << ">" <<endl;
    // cout << pre->num << endl;

    return ans;
}

int K_Largest(Node* root, int K)
{
    Node *cur = root;
    int cur_Kth;
    int count = 0;

    while (cur)
    {
        if (cur->right)
            cur_Kth = cur->right->child + 2 + count;
        else
            cur_Kth = 1 + count;

        // cout << cur_Kth << " " << cur->num << endl;
        
        if (K > cur_Kth)
        {
            cur = cur->left;
            count = cur_Kth;
        }
        else if (K < cur_Kth)
        {
            cur = cur->right;
        }
        else
            return cur->num;
    }

    return -1;
}

// By ARui
