#ifndef queue_H
#define queue_H

template<class T>
class queue
{

    struct Node
    {
        T data;
        Node *next;
    };

private:
    struct Node* r;
    struct Node* f;
    int sz = 0;

public:
    queue()
    {
        r = NULL;
        f  = NULL;
    }

    void push(T value)
    {
        ++sz;
        Node *temp = new Node;
        temp->data = value;
        temp->next = NULL;
        if(r!=NULL)r->next = temp;
        r = temp;
        if(sz == 1)
        {
            f = r;
        }
    }

    void pop()
    {
        --sz;
        Node* temp;
        temp= f;
        f = f->next;
        temp->next = NULL;
        delete temp;
    }

    T front()
    {
        return (f->data);
    }

    T rear()
    {
        return (r->data);
    }

    T size()
    {
        return sz;
    }

    bool empty()
    {
        return (sz == 0);
    }
};

#endif