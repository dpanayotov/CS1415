#include <iostream>

using namespace std;

template <typename T>
struct Node
{
    T data;
    Node<T>* next;
};

template <typename T>
class CyclicList
{
    Node<T>* end;
    void copy(const CyclicList&);
    void del();


public:
    CyclicList();
    CyclicList(const CyclicList&);
    CyclicList& operator=(const CyclicList&);
    ~CyclicList();
    void insertAtStart(const T&);
    void insertAtEnd(const T&);
    T removeFromStart();
    T removeFromEnd();
    bool remove(T&);
    int isMember(const T&) const;
    template <typename U>
    friend ostream& operator<<(ostream&, const CyclicList<U>& );

    class iterator
    {
    public:
        iterator begin()
        {
            return end->next;
        }

        iterator end()
        {
            return end;
        }
    };
};

template <typename T>
void CyclicList<T>::copy(const CyclicList& other)
{
    Node<T>* temp = new Node<T>;
    end = other.end;
    temp = other.end->next;
    while(temp->next != other.end)
    {
        insertAtStart(temp->data);
        temp = temp->next;
        end->next = temp;
    }
}

template <typename T>
CyclicList<T>& CyclicList<T>::operator=(const CyclicList& other)
{
    del();
    copy(other);
    return *this;
}

template <typename T>
void CyclicList<T>::del()
{
    T data;
    while(remove(data))
    {
        cout<<"data deleted: "<<data<<endl;
    }
}

template <typename T>
CyclicList<T>::CyclicList()
{
    end = NULL;
}

template <typename T>
CyclicList<T>::CyclicList(const CyclicList& other)
{
    end = new Node<T>;
    copy(other);
}

template <typename T>
bool CyclicList<T>::remove(T& what)
{
    if(end != NULL)
    {
        Node<T>* temp = new Node<T>;
        temp = end->next;

        end->next = temp->next;
        what = temp->data;

        if(end == temp)
        {
            end = NULL;
            return 1;
        }
        delete[] temp;
        return 1;
    }
    return 0;
}

template <typename T>
T CyclicList<T>::removeFromStart()
{
    if(end != NULL)
    {
        T toReturn;
        Node<T>* temp = new Node<T>;
        temp = end->next;

        end->next = temp->next;
        toReturn = temp->data;
        if(end == temp)
        {
            end = NULL;
        }

        delete[] temp;

        return toReturn;
    }
}

template <typename T>
T CyclicList<T>::removeFromEnd()
{
    if(end != NULL)
    {
        T toReturn;
        Node<T>* temp = new Node<T>;
        Node<T>* last = new Node<T>;
        temp = end->next;
        while(temp->next != end)
        {
            temp = temp->next;
        }
        last = temp->next;
        toReturn = last->data;
        temp->next = end->next;
        end = temp;

        delete[] last;

        return toReturn;
    }
}

template <typename T>
int CyclicList<T>::isMember(const T& what) const
{
    Node<T>* temp = end->next;
    do
    {
        if(temp->data == what)
        {
            return true;
        }
        temp = temp->next;
    }
    while(temp != end->next);
    return false;
}

template <typename T>
ostream& operator<<(ostream& out, const CyclicList<T>& list)
{
    Node<T>* temp = new Node<T>;
    temp = list.end->next;
    while(temp != list.end)
    {
        cout<<temp->data<<' ';
        temp = temp->next;
    }
    cout<<list.end->data;
}

template <typename T>
void CyclicList<T>::insertAtStart(const T& element)
{
    if(end == NULL)
    {
        end = new Node<T>;
        end->data = element;
        end->next = end;
    }
    else
    {
        Node<T>* newNode = new Node<T>;
        newNode->data = element;
        newNode->next = end->next;
        end->next = newNode;
    }
}

template <typename T>
void CyclicList<T>::insertAtEnd(const T& element)
{
    if(end == NULL)
    {
        end = new Node<T>;
        end->data = element;
        end->next = end;
    }
    else
    {
        Node<T>* newNode = new Node<T>;
        newNode->data = element;
        Node<T>* temp = new Node<T>;
        temp = end->next;
        while(temp != end)
        {
            temp = temp->next;
        }
        newNode->next = temp->next;
        end->next = newNode;
        end = newNode;

    }
}


template <typename T>
CyclicList<T>::~CyclicList()
{
    del();
}

int main()
{
    CyclicList<int> a;
    a.insertAtStart(2);
    a.insertAtStart(9);
    a.insertAtStart(8);
    a.insertAtEnd(3);
    a.insertAtStart(4);
    a.insertAtEnd(5);
    cout<<"Element removed from the start: "<<a.removeFromStart()<<endl;
    cout<<"Element removed from the end: "<<a.removeFromEnd()<<endl;
    cout<<"Using ostream: "<<endl;
    cout<<a;
    cout<<endl;
}

