#include <iostream>
#include <string>
#include <math.h>

using namespace std;

string infixToPostfix(string infix);
int getAns(string);

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


int main()
{
    int one = 0;
    string ini, postfix;

    while (cin >> ini)
    {
        if (one)
            cout << endl;
        else
            one++;

        cout << ini << endl;

        postfix = infixToPostfix(ini);
        cout << postfix << endl;

        cout << getAns(postfix);
    }

    return 0;
}

string infixToPostfix(string infix)
{
    string ans;
    Stack<char> sta;

    for (int i = 0; i < infix.length(); i++)
    {
        if (infix[i] >= '0' && infix[i] <= '9')
            ans += infix[i];
        else if (infix[i] == '+' || infix[i] == '-')
        {
            while (sta.top() == '*' || sta.top() == '/' || sta.top() == '+' || sta.top() == '-' || sta.top() == '^')
            {
                ans += sta.top();
                sta.pop();
            }
            sta.push(infix[i]);
        }
        else if (infix[i] == '*' || infix[i] == '/')
        {
            while (sta.top() == '*' || sta.top() == '/' || sta.top() == '^')
            {
                ans += sta.top();
                sta.pop();
            }
            sta.push(infix[i]);
        }
        else if (infix[i] == '^')
        {
            sta.push(infix[i]);
        }
        else
            throw "error: In function infixToPostfix";
    }

    while (!sta.empty())
    {
        ans += sta.top();
        sta.pop();
    }

    return ans;
}

int getAns(string post)
{
    int a, b;
    Stack<long long int> sta;

    for(int i = 0; i < post.length(); i++)
    {
        if (post[i] >= '0' && post[i] <= '9')
        {
            sta.push(post[i] - '0');
        }
        else
        {
            b = sta.top();
            sta.pop();
            a = sta.top();
            sta.pop();

            switch (post[i])
            {
            case '+':
                sta.push(a + b);
                break;
            case '-':
                sta.push(a - b);
                break;
            case '*':
                sta.push(a * b);
                break;
            case '/':
                sta.push(a / b);
                break;
            case '^':
                sta.push(pow(a, b));
                break;
            }
        }
    }
    return sta.top();
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
        return '\0';
    
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