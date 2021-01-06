#ifndef stack_H
#define stack_H

template<class T>
class stack
{

    struct Node
    {
        int data;
        Node *next;
    };

private:
    struct Node* head;
    int sz = 0;

public:
    stack()
    {
        head=NULL;
    }
    void push(int value)
    {
        ++sz;
        Node *temp = new Node;
        temp -> data = value;
        temp->next = head;
        head = temp;
    }

    void pop()
    {
        --sz;
        Node* temp;
        temp= head;
        head=head->next;
        temp->next = NULL;
        delete temp;
    }

    int top()
    {
        return head->data;
    }

    int size()
    {
        return sz;
    }

    bool empty()
    {
        return (sz == 0);
    }
};

#endif