#include <iostream>
#include <vector>
#include "heap.h"

using namespace std;


class PriorityQueue
{
    BinaryHeap<int> bh;
public:
    void push(int el);
    int top() const;
    void pop();
    int size();
    bool empty() const;
    void print()
    {
        cout<<"Queue: "<<endl<<bh<<endl;
    }
    void destroy();
};

void PriorityQueue::push(int el)
{
    bh.push(el);
}

int PriorityQueue::top() const
{
    BinaryHeap<int> temp = bh;
    for(int i = 0; i<temp.size(); i++)
    {
        temp.pop();
    }
    return temp.peek();
}

void PriorityQueue::pop()
{
    BinaryHeap<int> temp = bh;
    bh.clearHeap();
    for(int i = 0; i<temp.size(); i++)
    {
        bh.push(temp.peek());
        temp.pop();
    }
}

int PriorityQueue::size()
{
    return bh.size()+1;
}

bool PriorityQueue::empty() const
{
    return bh.isEmpty();
}

void PriorityQueue::destroy()
{
    while(!empty())
    {
        pop();
    }
}
