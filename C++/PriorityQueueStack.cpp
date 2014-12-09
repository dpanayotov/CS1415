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

//pri poveche ot 5 el => na noviq red

class PriorityStack
{
    vector<PriorityQueue> stackQueue;
public:
    void push(int el);
    void pushQueue(PriorityQueue q);
    void pop();
    void popQueue();
    PriorityQueue& topQueue();
    int topElement();
    int queueCount();
    int elementCount();
    bool empty();
    void print();
};

bool PriorityStack::empty()
{
    return stackQueue.empty();
}

void PriorityStack::push(int el)
{
    //if topQueue size is >=5 => new Queue => newQueue.push(el)
    if(topQueue().size()>=5)
    {
        PriorityQueue newQueue;
        newQueue.push(el);
        stackQueue.push_back(newQueue);
    }
    else
    {
        topQueue().push(el);
    }
}

void PriorityStack::pop()
{
    if(!empty())
    {
        topQueue().pop();
        //if topQueue.size() + nextTopQueue.size() <=5 => combine
    }
}

void PriorityStack::popQueue()
{
    vector<PriorityQueue> temp = stackQueue;
    PriorityQueue last = temp.at(temp.size()-1);
    while(!last.empty())
    {
        last.pop();
    }
    stackQueue = temp;
}

PriorityQueue& PriorityStack::topQueue()
{
    if(empty())
        stackQueue.reserve(1);

    return stackQueue.at(stackQueue.size()-1);
}

void PriorityStack::pushQueue(PriorityQueue pq)
{
    if(empty())
    {
        stackQueue.reserve(1);
    }
    stackQueue.push_back(pq);
}

void PriorityStack::print()
{
    vector<PriorityQueue> temp = stackQueue;
    for(int i = temp.size()-1; i>=0; i--)
    {
        temp.at(i).print();
        cout<<"popped"<<' ';
        temp.at(i).pop();
    }
}

int PriorityStack::topElement()
{
    return topQueue().top();
}

int PriorityStack::queueCount()
{
    vector<PriorityQueue> temp = stackQueue;
    int elements = 0;
    for(int i = 0; i<temp.size(); i++)
    {
        PriorityQueue current = temp.at(i);
        for(int i = 0; i<current.size(); i++)
        {
            current.pop();
        }
        elements++;
    }

    return elements;
}

int PriorityStack::elementCount()
{
    PriorityQueue temp;
    int elementCnt = 0;
    for(int i = 0; i<queueCount(); i++)
    {
        elementCnt += stackQueue.at(i).size();
    }
    return elementCnt;
}

int main()
{
    PriorityQueue pq;
    pq.push(4);
    pq.push(5);
    pq.push(6);
    pq.push(7);

    PriorityQueue pq1;
    pq1.push(4);
    pq1.push(5);
    pq1.push(6);
    pq1.push(7);
    pq1.push(8);
  /*  cout<<"Top: "<<pq.top()<<endl;
    pq.print();
    cout<<"size: "<<pq.size()<<endl;
    pq.pop();
    cout<<"Popped, size: "<<pq.size()<<endl;
    pq.print();
    cout<<"Empty? "<<pq.empty()<<endl;
    pq.pop();
    cout<<"Popped, size: "<<pq.size()<<endl;
    pq.print();
    cout<<"Empty? "<<pq.empty()<<endl;
    */
    PriorityStack pStack;
    pStack.pushQueue(pq);
    pStack.pushQueue(pq1);
    pStack.push(7);
    cout<<"<<<<<<Stack Begin>>>>>>"<<endl;
    pStack.print();
    cout<<"<<<<<<Stack End>>>>>>"<<endl;
    cout<<"Queue Count: "<<pStack.queueCount()<<endl;
    cout<<"Elements Count: "<<pStack.elementCount()<<endl;
    return 0;
}
