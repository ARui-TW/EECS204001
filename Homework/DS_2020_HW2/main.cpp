#include <iostream>
#include <string>

using namespace std;

template<class T>
class Queue
{
public:
    Queue(string);
    string getData();
    // TODO:
    void pop();
    void push(T);
    T top();
    bool empty();

private:
    T *array;
    int capacity;
    int first, end;
};

template<class T>
class Stack
{
public:
    Stack();
    void pop();
    void push(T);
    T top();
    bool empty();

private:
    T* array;
    int first;
    int capacity;
};

string infixToPostfix(string);
// TODO:
int postfixToAns(string);
bool valid(string);

int main(int argc, char *argv[])
{
    int N;
    char E;
    string initial, infix, postfix, in;

    cin >> initial;
    Queue<char> qu(initial);

    while (cin >> in)
    {
        if (in == "Dequeue")
        {
            cin >> N;
            while (N--)
                qu.pop();
        }
        else if (in == "Enqueue")
        {
            cin >> E;
            // TODO:
        }
        else if (in == "Print")
        {
            infix = qu.getData();
            cout << infix << endl;
            if (valid(infix))
                cout << "Invalid";
            else
            {
                postfix = infixToPostfix(infix);
                cout << postfix << endl << postfixToAns(postfix);
            }

            if (cin.peek() != EOF)
                cout << endl;
        }
        else
            cout << "error command\n";
    }

    return 0;
}

template<class T>
Queue<T>::Queue(string ini)
{
    capacity = ini.length() * 2;
    array = new T[capacity]();
    first = 0;
    end = ini.length();

    for (int i = 1; i <= ini.length(); i++)
        array[i] = ini[i - 1];
}

template<class T>
string Queue<T>::getData()
{
    string ans;
    if (end < first)
    {
        for (int i = first + 1; i < capacity; i++)
            ans += array[i];
        
        for (int i = 0; i <= end; i++)
            ans += array[i];
    } else
    {
        for (int i = first + 1; i <= end; i++)
            ans += array[i];
    }

    return ans;
}

string infixToPostfix(string infix)
{
    Stack<char> sta;

    for (int i = 0; i < infix.length(); i++)
    {
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
    if (first == -1)
        throw "Stack is empty, cannot pop";
    
    array[first--].~T();
}

template<class T>
void Stack<T>::push(T a)
{
    if (first == capacity - 1)
    {
        T* newArray = new T[capacity * 2];
        for (int i = 0; i <= top; i++)
            newArray[i] = array[i];
        
        array = newArray;
        capacity = capacity * 2;
    }

    array[++first] = a;
}

template<class T>
T Stack<T>::top()
{
    if (first == -1)
        throw "Stack is empty, cannot find top";
    
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