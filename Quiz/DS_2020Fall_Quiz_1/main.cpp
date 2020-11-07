#include <iostream>
#include <string>
using namespace std;

class LinkedList;

class ListNode{
public:
    ListNode():data(' '), next(0), pre(0){};
    ListNode(char c):data(c), next(0), pre(0){};

    friend class LinkedList;

private:
    char data;
    ListNode *next;
    ListNode *pre;
};

class LinkedList{
public:
    LinkedList() {
        head = new ListNode();
        cursor = head;
    }
    void add_node(char c);
    void move_right(int p);
    void move_left(int p);
    void backspace();
    void print();

private:
    ListNode *head;
    ListNode *cursor;

};

void LinkedList::backspace(){
    if (cursor != head) {
        ListNode *cur = cursor;
        ListNode *nxt = cursor->next;
        ListNode *prev = cursor->pre;

        if (nxt != 0)
            nxt->pre = prev;

        prev->next = nxt;

        delete cur;
        cursor = prev;
    }

}

void LinkedList::print(){
    ListNode *cur = this->head->next;

    while (cur != 0) {
        cout << cur->data;
        cur = cur->next;
    }
    cout << endl;

}

void LinkedList::add_node(char c){
    ListNode *node = new ListNode(c);

    if (this->head->next == 0) {
        this->head->next = node;
        node->pre = head;
        this->cursor = node;
    }
    else {
        ListNode *next = this->cursor->next;

        this->cursor->next = node;
        node->next = next;
        if (next != 0)
            next->pre = node;
        node->pre = cursor;

        this->cursor = node;
    }
}

void LinkedList::move_right(int p){
    while (p-- && cursor->next != 0) {
        cursor = cursor->next;
    }
}
void LinkedList::move_left(int p){
    int not_p = p * (-1);
    while (not_p-- && cursor->pre != 0) {
        cursor = cursor->pre;
    }
}


int main(){
    LinkedList list;
    string command;
    string input;
    int p;
    while(cin>>command){
        if(command == "Type"){
            cin >> input;
            if(input.empty()){
                continue;
            }else{
                for(int i=0; i<input.length(); i++){
                    list.add_node(input[i]);
                }
            }
        }else if(command == "Move"){
            cin >> p;
            if(p>0){
                list.move_right(p);
            }else if(p<0){
                list.move_left(p);
            }else{
                continue;
            }
        }else if(command == "Backspace"){
            list.backspace();
        }else if(command == "Print"){
            list.print();
        }else{
            continue;
        }
    }
    return 0;
}
