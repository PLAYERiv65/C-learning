#include<iostream>
#include<string>
using namespace std;

template <class T>
struct Node {
    T data;
    Node<T>* prior;
    Node<T>* next;
    Node(){
        prior = NULL;
        next = NULL;
    }
};

template <class T>
class list{
private:
    Node<T>* head;
    Node<T>* tail;
public:
    list();
    ~list();
    void append(T data);
    void insert(T data, int index);
    void remove(int index);
    void reverse_s();//single list
    void reverse_b();//bidirectional list
    void show();
};

template <class T>
list<T>::list(){
    head = new Node<T>;
    tail = new Node<T>;
    head->next = tail;
    tail->prior = head;
}

template <class T>
list<T>::~list(){
    Node<T>* p = head;
    Node<T>* q;
    while(p != NULL){
        q = p->next;
        delete p;
        p = q;
    } 
}

template <class T>
void list<T>::append(T data){
    Node<T>* p = new Node<T>;
    p->data = data;
    p->next = tail;
    p->prior = tail->prior;
    tail->prior->next = p;
    tail->prior = p;
}

template <class T>
void list<T>::insert(T data, int index){
    Node<T>* p = head;
    for(int i = 0; i < index; i++){
        p = p->next;
        if(p == tail){
            cout << "out of range" << endl;
            return;
        }
    }
    Node<T>* q = new Node<T>;
    q->data = data;
    q->next = p->next;
    q->prior = p;
    p->next->prior = q;
    p->next = q;
}

template <class T>
void list<T>::remove(int index){
    Node<T>* p = head;
    for(int i = 0; i < index; i++){
        p = p->next;
        if(p == tail){
            cout << "out of range" << endl;
            return;
        }
    }
    p->next->prior = p->prior;
    p->prior->next = p->next;
    delete p;
}

template <class T>
void list<T>::reverse_s(){//use next only
    Node<T>* p = head;
    Node<T>* q = head->next;
    Node<T>* temp;
    while(p != tail)
    {
        temp = q->next;
        q->next = p;
        p = q;
        q = temp;
    }
    swap(head, tail);
    //reset prior
    p = head;
    while(p != tail){
        p->next->prior = p;
        p = p->next;
    }
    head->prior = NULL;
    tail->next = NULL;
}

template <class T>
void list<T>::reverse_b(){//use prior and next
    Node<T>* p = head;
    while(p != NULL){
        swap(p->prior, p->next);
        p = p->prior;
    }
    swap(head, tail);
}

template <class T>
void list<T>::show(){
    Node<T>* p = head->next;
    while(p != tail){
        cout << p->data << "->";
        p = p->next;
    }
    cout << endl;
}

int main()
{
    list<int> l;
    for(int i = 0; i < 10; i++){
        l.append(i);
    }
    l.show();
    l.reverse_s();
    l.show();
    l.reverse_b();
    l.show();
    return 0;
}