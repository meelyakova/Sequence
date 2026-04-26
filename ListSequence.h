#pragma once
#include "Sequence.h"
#include "LinkedList.h"

template <class T>
class MutableListSequence;

template <class T>
class ListSequence : public Sequence<T>
{
protected:
    LinkedList<T> items;

public:
    ListSequence() {}

    ListSequence(T *arr, int count)
    {
        items(arr, count);
    }

    ListSequence(const ListSequence<T> &other)
    {
        items(other.items);
    }

    virtual ~ListSequence() {}

    T Get(int index) const override
    {
        if (index < 0 || index >= GetLength())
        {
            throw std::out_of_range("Index is out of range");
        }

        typename LinkedList<T>::Iterator it(items.BeginNode());

        int i = 0;
        while (i < index)
        {
            ++it;
            i++;
        }
        return *it;
    }

    T GetFirst() const override
    {
        return items.GetFirst();
    }

    T GetLast() const override
    {
        return items.GetLast();
    }

    int GetLength() const override
    {
        return items.GetLength();
    }

    Sequence<T> *Append(T item) override
    {
        Sequence<T> *result = this->Instance();
        auto *list = dynamic_cast<ListSequence<T> *>(result);

        list->items.Append(item);
        return result;
    }

    Sequence<T> *Prepend(T item) override
    {
        Sequence<T> *result = this->Instance();
        auto *list = dynamic_cast<ListSequence<T> *>(result);

        list->items.Prepend(item);
        return result;
    }

    Sequence<T> *InsertAt(T item, int index) override
    {
        if (index < 0 || index > GetLength())
        {
            throw std::out_of_range("Index is out of range");
        }

        Sequence<T> *result = this->Instance();
        auto *list = dynamic_cast<ListSequence<T> *>(result);

        list->items.InsertAt(item, index);
        return result;
    }

    Sequence<T> *Concat(const Sequence<T> *list) override
    {
        Sequence<T> *result = this->Instance();

        int i = 0;
        while (i < list->GetLength())
        {
            result = result->Append(list->Get(i));
            i++;
        }
        return result;
    }

    Sequence<T> *GetSubSequence(int start, int end) const override
    {
        if (start < 0 || end >= GetLength() || start > end)
        {
            throw std::out_of_range("Invalid indices");
        }

        Sequence<T> *result = new MutableListSequence<T>();

        typename LinkedList<T>::Iterator it(items.BeginNode());

        for (int i = 0; i < start; i++)
        {
            ++it;
        }

        for (int i = start; i <= end; i++)
        {
            result = result->Append(*it);
            ++it;
        }
        return result;
    }
};