#include <iostream>

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

int find_insert (Node *root, int num)
{
    int ans = 0;
    Node *cur = root;
    Node *pre = root;
    Node *node = new Node(num);

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
            if (cur->left)
            {
                ans += cur->left->child;
                ans++;
            }
            ans++;
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

void clear (Node *root)
{
    if (root->left)
        clear(root->left);
    if (root->right)
        clear(root->right);

    delete root;
}

int main()
{
    int n;
    while (cin >> n)
    {
        int *list = new int[n];
        int count = 0;

        for (int i = 0; i < n; i++)
            cin >> list[i];

        Node *root = new Node(list[n - 1]);
        list[n - 1] = 0;

        for (int i = n - 2; i >= 0; i--)
        {
            // cout << i << endl;
            list[i] =  find_insert(root, list[i]);
        }

        for (int i = 0; i < n; i++)
            cout << list[i] << " ";

        cout << endl;

        delete list;
        
        clear(root);
    }
    
    return 0;
}
