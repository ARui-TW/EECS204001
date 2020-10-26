#include <iostream>
#include <string>

using namespace std;

class Node
{
    friend class linkedList;

public:
    Node(int data = 0)
    {
        this->data = data;
        this->nxt = NULL;
    }

private:
    int data;
    Node *nxt;
};

class linkedList
{
public:
    linkedList() { head = NULL; }
    void InsertFront(int a);
    void InsertBack(int a);
    void InsertBefore(int K, int a);
    void InsertAfter(int K, int a);
    void Delete(int K);
    void DeleteFront(void);
    void DeleteBack(void);
    void Reverse(int K, int J);
    void Clear(void);
    void Print(void);

private:
    Node *head;
};

int main(int argc, char *argv[])
{
    string command;
    linkedList ll;

    while (cin >> command)
    {
        int a, K;

        if (command == "InsertFront")
        {
            cin >> a;
            ll.InsertFront(a);
        }
        else if (command == "InsertBack")
        {
            cin >> a;
            ll.InsertBack(a);
        }
        else if (command == "InsertBefore")
        {
            cin >> K >> a;
            ll.InsertBefore(K, a);
        }
        else if (command == "InsertAfter")
        {
            cin >> K >> a;
            ll.InsertAfter(K, a);
        }
        else if (command == "Delete")
        {
            cin >> K;
            ll.Delete(K);
        }
        else if (command == "DeleteFront")
            ll.DeleteFront();
        else if (command == "DeleteBack")
            ll.DeleteBack();
        else if (command == "Reverse")
        {
            cin >> a >> K;
            ll.Reverse(a, K);
        }
        else if (command == "Clear")
            ll.Clear();
        else if (command == "Print")
            ll.Print();
        else
            cout << "No such command\n";
    }

    return 0;
}

void linkedList::InsertFront(int a)
{
    Node *node = new Node(a);

    if (head)
    {
        node->nxt = head;
        head = node;
    }
    else
        head = node;
}

void linkedList::InsertBack(int a)
{
    Node *cur = head;

    if (cur)
    {
        while (cur->nxt != NULL)
            cur = cur->nxt;

        cur->nxt = new Node(a);
    }
    else
        head = new Node(a);
}
void linkedList::InsertBefore(int K, int a)
{
    Node *cur = head;

    if (cur)
    {
        if (cur->data != K)
        {
            if (cur->nxt)
            {
                while (cur->nxt->data != K)
                {
                    cur = cur->nxt;
                    if (cur->nxt == NULL)
                        break;
                }

                if (cur->nxt)
                {
                    Node *node = new Node(a);
                    node->nxt = cur->nxt;
                    cur->nxt = node;
                }
            }
        }
        else // head is K
        {
            Node *node = new Node(a);
            node->nxt = head;
            head = node;
        }
    }
}
void linkedList::InsertAfter(int K, int a)
{
    Node *cur = head;

    if (head)
    {
        while (cur->data != K)
        {
            cur = cur->nxt;

            if (cur == NULL)
                break;
        }

        if (cur)
        {
            Node *node = new Node(a);
            node->nxt = cur->nxt;
            cur->nxt = node;
        }
    }
}
void linkedList::Delete(int K)
{
    Node *cur = head;

    if (cur)
    {
        if (cur->data != K)
        {
            if (cur->nxt)
            {
                while (cur->nxt->data != K)
                {
                    cur = cur->nxt;
                    if (cur->nxt == NULL)
                        break;
                }

                if (cur->nxt)
                {
                    Node *del = cur->nxt;
                    cur->nxt = cur->nxt->nxt;
                    delete del;
                }
            }
        }
        else // head is K
        {
            Node *del = head;
            head = head->nxt;
            delete del;
        }
    }
}
void linkedList::DeleteFront(void)
{
    if (head)
    {
        Node *del = head;
        head = head->nxt;
        delete del;
    }
}
void linkedList::DeleteBack(void)
{
    Node *cur = head;

    if (cur)
    {
        if (cur->nxt)
        {
            while (cur->nxt->nxt)
                cur = cur->nxt;

            Node *del = cur->nxt;
            cur->nxt = NULL;
            delete del;
        }
        else // head is only one
        {
            Node *del = head;
            head = NULL;
            delete del;
        }
    }
}
void linkedList::Reverse(int K, int J)
{
    Node *nodeK, *K_prev, *nodeJ, *J_next, *prev, *cur, *next;
    bool headIsK = false, tailIsJ = false;

    if (!head)
        return;

    // Find K
    if (head->data != K)
    {
        K_prev = head;
        nodeK = head->nxt;
        while (nodeK && nodeK->data != K) // It won't test nodeK->data if nodeK doesn't exist
        {
            nodeK = nodeK->nxt;
            K_prev = K_prev->nxt;
        }

        if (!nodeK)
            return;
    }
    else // head is K
    {
        nodeK = head;
        headIsK = true;
    }

    // Find J
    nodeJ = head;
    J_next = head->nxt;
    while (J_next && nodeJ->data != J) // J_next DNE or find J => jump out
    {
        nodeJ = nodeJ->nxt;
        J_next = J_next->nxt;
    }

    if (!J_next && nodeJ->data == J)
        tailIsJ = true;
    else if (!J_next && nodeJ->data != J)
        return;

    // set cur
    prev = nodeK;
    cur = nodeK->nxt;
    next = cur->nxt;

    // reverse
    while (prev != nodeJ)
    {
        cur->nxt = prev;
        prev = cur;
        cur = next;
        if (next)
            next = next->nxt;
    }

    // set K, J
    if (headIsK)
        head = nodeJ;
    else
        K_prev->nxt = nodeJ;

    if (tailIsJ)
        nodeK->nxt = NULL;
    else
        nodeK->nxt = J_next;
}
void linkedList::Clear(void)
{
    Node *cur = head, *del;

    if (cur)
    {
        while (cur->nxt)
        {
            del = cur;
            cur = cur->nxt;
            delete del;
        }

        delete cur;
    }

    head = NULL;
}
void linkedList::Print(void)
{
    Node *cur = head;

    while (cur)
    {
        cout << cur->data << " ";
        cur = cur->nxt;
    }
    cout << endl;
}

// By ARui