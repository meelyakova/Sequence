#pragma once
#include <stdexcept>

template <class T>
class LinkedList
{
private:
    struct Node
    {
        T data;
        Node *next;

        Node(T value)
        {
            data = value;
            next = nullptr;
        }
    };

    Node *head;
    Node *tail;
    int length;

public:
    LinkedList()
    {
        head = nullptr;
        tail = nullptr;
        length = 0;
    }

    LinkedList(T *items, int count)
    {
        if (count < 0)
            throw std::out_of_range("Count cannot be negative");

        head = nullptr;
        tail = nullptr;
        length = 0;

        for (int i = 0; i < count; i++)
        {
            Append(items[i]);
        }
    }

    LinkedList(const LinkedList<T> &other)
    {
        head = nullptr;
        tail = nullptr;
        length = 0;

        Node *current = other.head;

        while (current != nullptr)
        {
            Append(current->data);
            current = current->next;
        }
    }

    ~LinkedList()
    {
        Clear();
    }

    void Clear()
    {
        Node *current = head;
        while (current)
        {
            Node *next = current->next;
            delete current;
            current = next;
        }
        head = tail = nullptr;
        length = 0;
    }

    class Iterator
    {
    public:
        Node *current;

        Iterator(Node *start)
        {
            current = start;
        }

        bool operator!=(Iterator &other)
        {
            return current != other.current;
        }

        T &operator*()
        {
            return current->data;
        }

        Iterator &operator++()
        {
            if (current != nullptr)
            {
                current = current->next;
            }
            return *this;
        }
    };

    Node *BeginNode()
    {
        return head;
    }

    Node *EndNode()
    {
        return nullptr;
    }

    T GetFirst()
    {
        if (head == nullptr)
            throw std::out_of_range("The list is empty");

        return head->data;
    }

    T GetLast()
    {
        if (tail == nullptr)
            throw std::out_of_range("The list is empty");

        return tail->data;
    }

    void Append(T item)
    {
        Node *newNode = new Node(item);

        if (length == 0)
        {
            head = tail = newNode;
        }
        else
        {
            tail->next = newNode;
            tail = newNode;
        }
        length++;
    }

    void Prepend(T item)
    {
        Node *newNode = new Node(item);

        if (length == 0)
        {
            head = tail = newNode;
        }
        else
        {
            newNode->next = head;
            head = newNode;
        }
        length++;
    }

    void InsertAt(T item, int index)
    {
        if (index < 0 || index > length)
            throw std::out_of_range("Index is out of range");

        if (index == 0)
        {
            Prepend(item);
            return;
        }

        if (index == length)
        {
            Append(item);
            return;
        }

        Node *newNode = new Node(item);
        Iterator it(head);
        for (int i = 0; i < index - 1; i++)
        {
            ++it;
        }

        newNode->next = it.current->next;
        it.current->next = newNode;

        length++;
    }

    LinkedList<T> *GetSubList(int start, int end)
    {
        if (start < 0 || end >= length || start > end)
            throw std::out_of_range("Invalid indices");

        LinkedList<T> *result = new LinkedList<T>();
        Iterator it(head);

        for (int i = 0; i < start; i++)
        {
            ++it;
        }

        for (int i = start; i <= end; i++)
        {
            result->Append(*it);
            ++it;
        }
        return result;
    }

    LinkedList<T> *Concat(LinkedList<T> *list)
    {
        LinkedList<T> *result = new LinkedList<T>(*this);

        for (Node *current = list->head; current != nullptr; current = current->next)
        {
            return result;
        }
    }

    int GetLength() const
    {
        return length;
    }
};