#include <vector>
#include <iterator>

template <typename T>
class BinaryHeap
{
    static const unsigned top = 0;
    std::vector<T> heap;
    void siftUp(int index);
    void siftDown(int index);
    static int getParent(int index)
    {
        return (index-1) /2;
    }
    static int getLeftChild(int index)
    {
        return 2*index + 1;
    }
    static int getRightChild(int index)
    {
        return 2 * (index + 1);
    }
public:
    BinaryHeap();
    int size() const;
    void push(const T&);
    void pop();
    T peek() const;
    bool isEmpty() const;
    void makeHeap(const std::vector<T>);
    void heapSort(std::vector<T>);
    void clearHeap()
    {
        heap.clear();
    }
    typename std::vector<T>::iterator begin() {return heap.begin();}
typename std::vector<T>::iterator end() {return heap.end();}
};

template<typename T>
std::ostream& operator<<(std::ostream& out, BinaryHeap<T> heap)
{
    if (heap.isEmpty())
    {
        out << "[]";
        return out;
    }
    typename std::vector<T>::const_iterator iter = heap.begin();
    out << "[";
    for (; iter != heap.end() - 1; ++iter)
    {
        out << *iter << ", ";
    }
    out << *(heap.end() - 1) << "]";
}

template <typename T>
BinaryHeap<T>::BinaryHeap() : heap() {}

template <typename T>
int BinaryHeap<T>::size() const
{
    return heap.size() - 1;
}

template <typename T>
void BinaryHeap<T>::push(const T& data)
{
    heap.push_back(data);
    siftUp(size());
}

template <typename T>
void BinaryHeap<T>::pop()
{
    std::swap(heap[top], heap[size()]);
    heap.pop_back();
    siftDown(top);
}

template <typename T>
T BinaryHeap<T>::peek() const
{
    return heap[top];
}

template <typename T>
bool BinaryHeap<T>::isEmpty() const
{
    return heap.empty();
}

template <typename T>
void BinaryHeap<T>::makeHeap(const std::vector<T> els)
{
    heap.assign(els.begin(), els.end());
    //get the parent of the last element
    int current = getParent(heap.size());
    //while not on top => push the current element down, sorting the heap
    while(current >= 0)
    {
        siftDown(current);
        current--;
    }
}

template <typename T>
void BinaryHeap<T>::heapSort(std::vector<T> els)
{
    makeHeap(els);
    els.clear();
    while(!heap.empty())
    {
        T el = heap.peek();
        els.push_back(el);
        pop();
    }
}

template <typename T>
void BinaryHeap<T>::siftUp(int index)
{
    int current = index;
    int parent = getParent(current);
    while(current >= top && heap.at(current) > heap.at(parent))
    {
        std::swap(heap.at(current), heap.at(parent));
        current = parent;
        parent = getParent(current);
    }
}

template <typename T>
void BinaryHeap<T>::siftDown(int index)
{
    int current = index;
    int leftChild = getLeftChild(current);
    int rightChild = getRightChild(current);

    while((leftChild <= size() && heap[current] < heap[leftChild]) ||
            (rightChild <= size() && heap[current] < heap[rightChild]))
    {
        if(leftChild <= size() && rightChild <= size())
        {
            if(heap[leftChild] < heap[rightChild])
            {
                std::swap(heap[current], heap[rightChild]);
                current = rightChild;
                leftChild = getLeftChild(current);
                rightChild = getRightChild(current);
            }
            else
            {
                std::swap(heap[current], heap[leftChild]);
                current = leftChild;
                leftChild = getLeftChild(current);
                rightChild = getRightChild(current);
            }
        }
        else if(rightChild <= size())
        {
            std::swap(heap[current], heap[rightChild]);
            current = rightChild;
            leftChild = getLeftChild(current);
            rightChild = getRightChild(current);
        }
        else if(leftChild <= size())
        {
            std::swap(heap[current], heap[leftChild]);
            current = leftChild;
            leftChild = getLeftChild(current);
            rightChild = getRightChild(current);
        }
    }
}
