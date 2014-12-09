#include <iostream>

template<typename T>
struct Node
{
    T data;
    Node* left;
    Node* right;

    Node(T _data)
    {
        left = NULL;
        right = NULL;
        data = _data;
    }
};

template <typename T>
class BST
{
    Node<T>* root;
    void copy(Node<T>* what, Node<T>*& where);
    void destroy(Node<T>* what);
    void addElement(Node<T>* where, const T& element);
    T findMin(Node<T>* where) const;
    T findMax(Node<T>* where) const;
    bool isElement(Node<T>* where, T element) const;
    std::ostream& print(std::ostream& out, Node<T>* what) const;
public:
    BST()
    {
        root = NULL;
    }
    BST(const BST& other)
    {
        copy(other);
    }
    BST& operator=(const BST& other);
    bool isEmpty() const
    {
        return root == NULL;
    }
    void addElement(const T& element)
    {
        addElement(root, element);
    }
    T findMin() const
    {
        return findMin(root);
    }
    T findMax() const
    {
        return findMax(root);
    }
    bool isElement(T& element) const
    {
        return isElement(root, element);
    }
    std::ostream& print(std::ostream& out) const
    {
        return print(out, root);
    }
};

template <typename T>
void BST<T>::copy(Node<T>* what, Node<T>*& where)
{
    if(what == NULL)
    {
        return;
    }
    where = new Node<T>(what->data);
    if(what->left != NULL)
    {
        copy(what->left, where->left);
    }
    if(what->right != NULL)
    {
        copy(what->right, where->right);
    }
}

template <typename T>
void BST<T>::destroy(Node<T>* what)
{
    if(what->left == NULL && what->right == NULL)
    {
        delete what;
        return;
    }

    if(what->left != NULL)
    {
        destroy(what->left);
    }

    if(what->right != NULL)
    {
        destroy(what->right);
    }

    delete what;
}

template <typename T>
void BST<T>::addElement(Node<T>* where, const T& element)
{
    if(where == NULL)
    {
        where = new Node<T>(element);
        return;
    }

    if(element > where->data)
    {
        addElement(where->right, element);
    }

    addElement(where->left, element);
}

template <typename T>
T BST<T>::findMin(Node<T>* where) const
{
    if(where->left == NULL)
    {
        return where->data;
    }

    findMin(where->left);
}

template <typename T>
T BST<T>::findMax(Node<T>* where) const
{
    if(where->right == NULL)
    {
        return where->data;
    }

    findMax(where->right);
}

template <typename T>
bool BST<T>::isElement(Node<T>* where, T element) const
{
    if(where == NULL)
    {
        return false;
    }

    if(element > where->data)
    {
        return isElement(where->right, element);
    }

    return isElement(where->left, element);
}

template<typename T>
std::ostream& operator<<(std::ostream& out, const BST<T>& bst)
{
    bst.print(out);
    return out;
}

template<typename T>
std::ostream& BST<T>::print(std::ostream& out, Node<T>* what) const
{
    if (what == NULL)
    {
        return out;
    }
    out << "[";
    print(out, what->left) << " ";
    out << what->data << " ";
    print(out, what->right);
    out << "]";
    return out;
}
