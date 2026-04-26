#pragma once
#include "Sequence.h"
#include "DynamicArray.h"

template <class T>
class MutableArraySequence;

template <class T>
class ArraySequence : public Sequence<T>
{
protected:
    DynamicArray<T> *items;

public:
    ArraySequence()
    {
        items = new DynamicArray<T>(0);
    }

    ArraySequence(T *arr, int count)
    {
        items = new DynamicArray<T>(arr, count);
    }

    ArraySequence(const ArraySequence<T> &other)
    {
        items = new DynamicArray<T>(*other.items);
    }

    virtual ~ArraySequence()
    {
        delete items;
    }

    T Get(int index) const override
    {
        return items->Get(index);
    }

    T GetFirst() const override
    {
        if (GetLength() == 0)
            throw std::out_of_range("Sequence is empty");

        return items->Get(0);
    }

    T GetLast() const override
    {
        if (GetLength() == 0)
            throw std::out_of_range("Sequence is empty");

        return items->Get(items->GetSize() - 1);
    }

    int GetLength() const override
    {
        return items->GetSize();
    }

    Sequence<T> *Append(T item) override
    {
        Sequence<T> *result = this->Instance();

        auto *arr = dynamic_cast<ArraySequence<T> *>(result);

        arr->items->Resize(arr->items->GetSize() + 1);
        arr->items->Set(arr->items->GetSize() - 1, item);

        return result;
    }

    Sequence<T> *Prepend(T item) override
    {
        Sequence<T> *result = this->Instance();
        auto *arr = dynamic_cast<ArraySequence<T> *>(result);

        int size = arr->items->GetSize();
        arr->items->Resize(size + 1);

        for (int i = size; i > 0; i--)
        {
            arr->items->Set(i, arr->items->Get(i - 1));
        }

        arr->items->Set(0, item);
        return result;
    }

    Sequence<T> *InsertAt(T item, int index) override
    {
        if (index < 0 || index > this->GetLength())
            throw std::out_of_range("Index out of range");

        Sequence<T> *result = this->Instance();
        auto *arr = dynamic_cast<ArraySequence<T> *>(result);

        int size = arr->items->GetSize();
        arr->items->Resize(size + 1);

        for (int i = size; i > index; i--)
        {
            arr->items->Set(i, arr->items->Get(i - 1));
        }

        arr->items->Set(index, item);
        return result;
    }

    Sequence<T> *Concat(const Sequence<T> *list) override
    {
        Sequence<T> *result = this->Instance();

        for (int i = 0; i < list->GetLength(); i++)
        {
            result = result->Append(list->Get(i));
        }

        return result;
    }

    Sequence<T> *GetSubSequence(int start, int end) const override
    {
        if (start < 0 || end >= GetLength() || start > end)
            throw std::out_of_range("Invalid indices");

        Sequence<T> *result = new MutableArraySequence<T>();

        for (int i = start; i <= end; i++)
        {
            result = result->Append(Get(i));
        }
        return result;
    }
};
