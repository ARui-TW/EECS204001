#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

template<class T>
class Stack
{
public:
    Stack();
    void pop();
    void push(T);
    T top();
    bool empty();
    ~Stack() {delete[] array;}

private:
    T* array;
    int first;
    int capacity;
};

template<class T>
class Node
{
    friend class Tree;

public:
    Node ();
    Node (T data) : weight(data), tower(false){}
    ~Node() {};

private:
    T weight;
    bool tower;
    Node *left, *right;
};

class Tree
{
public:
    Tree (string);
    void printPreorder();
    void printInorder();
    void printPostorder();
    int Height(Node<int> *parent);
    void Height();
    void WeightSum();
    int MaximumPathSum(Node<int> *parent = NULL);
    void BinaryTower();
    int BinaryTower(Node<int> *parent);
    void DeleteLeaf();
    void Foldable();
    void deleteTree(Node<int> *parent = NULL);
    ~Tree() {deleteTree(root);}

private:
    Node<int> *root;
};

int main(int argc, char *argv[])
{
    string input;
    cin >> input;

    Tree *tree = new Tree(input);

    while (cin >> input)
    {
        if (input == "Traverse")
        {
            tree->printPreorder();
            tree->printInorder();
            tree->printPostorder();
        }
        else if (input == "Height")
            tree->Height();
        else if (input == "WeightSum")
            tree->WeightSum();
        else if (input == "MaximumPathSum")
            tree->MaximumPathSum();
        else if (input == "BinaryTower")
            tree->BinaryTower();
        else if (input == "DeleteLeaf")
            tree->DeleteLeaf();
        else if (input == "Foldable")
            tree->Foldable();
        else if (input == "End")
        {
            if (cin >> input)
            {
                delete tree;
                tree = new Tree(input);
            }
            else
                break;
        }
        else
            cout << "Error Command\n";
    }

    return 0;
}

Tree::Tree (string input)
{
    int i = 0, length = input.length();
    string store_num;
    Stack<Node<int> **> st;
    Node<int> **cur, *node;

    st.push(&root);

    while (!st.empty())
    {
        while (input[i] == ')')
            i++;
        
        if (input[++i] == ')')
            node = NULL;
        else
        {
            store_num += input[i];
            
            while(input[i + 1] != '(')
                store_num += input[++i];
            
            node = new Node<int>(stoi(store_num));

            store_num.clear();
        }

        cur = st.top();
        st.pop();
        *cur = node;

        if (node)
        {
            st.push(&(node->right));
            st.push(&(node->left));
        }

        i++;
    }
}

void Tree::printPreorder()
{
    if (root == NULL) 
    {
        cout << endl;
        return;
    }

    Stack<Node<int>*> st;
    Node<int> *node;
    
    st.push(root);

    while (!st.empty())
    {
        node = st.top();
        st.pop();
        cout << node->weight << " ";
        if (node->right) st.push(node->right);
        if (node->left) st.push(node->left);
    }

    cout << endl;
}

void Tree::printInorder()
{
    Stack<Node<int>*> st;
    Node<int> *node = root;

    while (!st.empty() || node)
    {
        if (node)
        {
            st.push(node);
            node = node->left;
        }
        else
        {
            node = st.top();
            st.pop();
            cout << node->weight << " ";
            node = node->right;
        }
    }

    cout << endl;
}

void Tree::printPostorder()
{
    Stack<Node<int>*> st;
    Node<int> *node = root, *nxtNode, *lastNodeVisited;

    while (!st.empty() || node)
    {
        if (node)
        {
            st.push(node);
            node = node->left;
        }
        else
        {
            nxtNode = st.top();
            if (nxtNode->right && lastNodeVisited != nxtNode->right)
                node = nxtNode->right;
            else
            {
                cout << nxtNode->weight << " ";
                lastNodeVisited = st.top();
                st.pop();
            }
        }
    }
    cout << endl;
}

int Tree::Height(Node<int> *parent)
{
    if (!parent)
        return 0;
    
    return max(Height(parent->left), Height(parent->right)) + 1;
}

void Tree::Height()
{
    cout << Height(root) << endl;
}

void Tree::WeightSum()
{
    if (root == NULL)
    {
        cout << 0 << endl;
        return;
    }

    Stack<Node<int>*> st;
    Node<int> *node;
    long long int ans = 0;
    
    st.push(root);

    while (!st.empty())
    {
        node = st.top();
        st.pop();
        ans += node->weight;
        if (node->right) st.push(node->right);
        if (node->left) st.push(node->left);
    }

    cout << ans << endl;
}

int Tree::MaximumPathSum(Node<int>* parent)
{
    if (!parent)
    {
        if (root)
            cout << MaximumPathSum(root) << endl;
        else
            cout << 0 << endl;
        return 0;
    }
    else
    {
        if (!parent->left && !parent->right)
            return parent->weight;
        else if (parent->left && !parent->right)
            return MaximumPathSum(parent->left) + parent->weight;
        else if (!parent->left && parent->right)
            return MaximumPathSum(parent->right) + parent->weight;
        else
            return max(MaximumPathSum(parent->left), MaximumPathSum(parent->right)) + parent->weight;
    }
}

int Tree::BinaryTower(Node<int> *parent)
{
    int i = 0, ans = 0, t = 1;

    if (parent->left || parent->right)
    {
        if (parent->left && parent->right)
            ans = BinaryTower(parent->right) + BinaryTower(parent->left);
        else if (parent->left)
            ans = BinaryTower(parent->left);
        else
            ans = BinaryTower(parent->right);

        if ((parent->right && !parent->right->tower) || (parent->left && !parent->left->tower))
        {
            i = 1;
            parent->tower = true;

            if (parent == root)
            {
                if (!root->right->tower)
                {
                    if (root->right->left && root->right->left->tower)
                        t = 0;
                    else if (root->right->right && root->right->right->tower)
                        t = 0;
                }
                else t = 0;

                if (!root->left->tower)
                {
                    if (root->left->left && root->left->left->tower)
                        i = 0;
                    else if (root->left->right && root->left->right->tower)
                        i = 0;
                }
                else i = 0;

                if ((t || i) || (!root->left->tower && !root->right->tower))
                    i = 1;
            }
        }

        return ans + i;
    }
    else
        return 0;
}

void Tree::BinaryTower()
{
    if (!root)
    {
        cout << 0 << endl;
        return;
    }
    else if (!root->left && !root->right)
    {
        cout << 1 << endl;
        return;
    }
    else 
        cout << BinaryTower(root) << endl;

    Stack<Node<int>*> st;
    Node<int> *node;
    
    st.push(root);

    while (!st.empty())
    {
        node = st.top();
        st.pop();
        node->tower = false;
        if (node->right) st.push(node->right);
        if (node->left) st.push(node->left);
    }
}

void Tree::DeleteLeaf()
{
    if (!root)
        return;
    
    Stack<Node<int>*> st, parent_st;
    Node<int> *node = root, *parent_node;

    if (!root->left && !root->right)
    {
        root = NULL;
        delete node;
    }
    else
    {
        if (node->right) 
        {
            st.push(node->right);
            parent_st.push(root);
        }
        if (node->left)
        {
            st.push(node->left);
            parent_st.push(root);
        }
    }

    while (!st.empty())
    {
        node = st.top();
        st.pop();
        parent_node = parent_st.top();
        parent_st.pop();

        if (node->right) 
        {
            st.push(node->right);
            parent_st.push(node);
        }
        if (node->left)
        {
            st.push(node->left);
            parent_st.push(node);
        }

        if (!node->left && !node->right)
        {
            (parent_node->left == node)? parent_node->left = NULL : parent_node->right = NULL;
            delete node;
        }
    }
}

void Tree::Foldable()
{
    if (!root)
    {
        cout << "Yes\n";
        return;
    }

    Node<int> *right = root->right, *left = root->left;
    Stack<Node<int>*> st_right, st_left;

    if (!right && !left)
    {
        cout << "Yes\n";
        return;
    }
    else if (!right && left || right && !left)
    {
        cout << "No\n";
        return;
    }

    st_right.push(right);
    st_left.push(left);

    while (!st_right.empty() && !st_left.empty())
    {
        right = st_right.top();
        left = st_left.top();

        st_right.pop();
        st_left.pop();

        if (!right && left || right && !left)
        {
            cout << "No\n";
            return;
        }

        if (right && left)
        {
            st_right.push(right->right);
            st_right.push(right->left);

            st_left.push(left->left);
            st_left.push(left->right);
        }
    }

    if (!st_left.empty() || !st_right.empty())
        cout << "No\n";
    else
        cout << "Yes\n";
}

void Tree::deleteTree(Node<int> *parent)
{
    if (parent)
    {
        deleteTree(parent->right);
        deleteTree(parent->left);
        delete parent;
    }
}

template<class T>
Stack<T>::Stack()
{
    capacity = 10;
    first = -1;
    array = new T[capacity];
}

template<class T>
void Stack<T>::pop()
{
    if (first != -1)
        array[first--].~T();
}

template<class T>
void Stack<T>::push(T a)
{
    if (first == capacity - 1)
    {
        T* newArray = new T[capacity * 2];
        for (int i = 0; i <= first; i++)
            newArray[i] = array[i];
        
        T* del = array;
        array = newArray;
        delete[] del;
        capacity = capacity * 2;
    }

    array[++first] = a;
}

template<class T>
T Stack<T>::top()
{
    if (first == -1)
        return NULL;
    
    return array[first];
}

template<class T>
bool Stack<T>::empty()
{
    if (first == -1)
        return true;
    else
        return false;
}

// By ARui