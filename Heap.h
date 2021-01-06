#ifndef Heap_H
#define Heap_H

#include "Darray.h"

template<class T>
class Heap
{
    public:

        Heap<T> (bool (*comp)(T obj1, T obj2));

        bool isEmpty();

        void push(T obj);

        void pop();

        T top();
    private:

        bool (*compare)(T obj1, T obj2);

        Darray<T> heap;
        void UpnUp(int idx);
        void DownnDown(int idx);

        int leftChild(int i)
        {
            return 2*i + 1;
        }
        int rightChild(int i)
        {
            return 2*i + 2;
        }
        int parent(int i)
        {
            return (i-1)/2;
        }
};
template<class T> Heap<T>::Heap(bool (*comp)(T obj1, T obj2))
{
    this -> compare = comp;
}

template<class T> bool Heap<T>::isEmpty()
{
    return heap.empty();
}

template<class T> void Heap<T>::push(T obj)
{
    heap.push_back(obj);
    UpnUp(heap.size()-1);
}

template<class T> void Heap<T>::pop()
{
    if(!isEmpty())
    {
       std::swap(heap[0], heap[heap.size()-1]);
       heap.pop_back();
       if(!isEmpty())
          DownnDown(0);
    }

    else
    {
        throw std::invalid_argument( "heap is empty" );
    }
}

template<class T> T Heap<T>::top()
{
    if(!isEmpty())
    {
       return heap[0];
    }

    else
    {
        throw std::invalid_argument( "heap is empty" );
    }
    // return throw invalid_argument( "heap is empty" );
}

template<class T> void Heap<T>::DownnDown(int idx)
{
    int largeIdx = idx;
    int leftChildIdx = leftChild(idx), rightChildIdx = rightChild(idx);
    if(leftChildIdx < heap.size())
    {
       if(compare(heap[largeIdx], heap[leftChildIdx]))
            largeIdx = leftChildIdx;
    }
    if(rightChildIdx < heap.size())
    {
       if(compare(heap[largeIdx], heap[rightChildIdx]))
            largeIdx = rightChildIdx;
    }

    if(largeIdx != idx)
    {
       std::swap(heap[largeIdx], heap[idx]);
       DownnDown(largeIdx);
    }
}

template<class T> void Heap<T>::UpnUp(int idx)
{
    int parentIdx = parent(idx);
    if(parentIdx < 0)
            return;
    if(compare(heap[parentIdx], heap[idx]))
    {
        std::swap(heap[parentIdx], heap[idx]);
        UpnUp(parentIdx);
    }
}

#endif