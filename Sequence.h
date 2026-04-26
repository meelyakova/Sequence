#pragma once
#include <stdexcept>

template <class T>
class Sequence
{
public:
    virtual ~Sequence() {}

    // основные методы
    virtual T Get(int index) const = 0;
    virtual T GetFirst() const = 0;
    virtual T GetLast() const = 0;
    virtual int GetLength() const = 0;

    virtual Sequence<T> *Append(T item) = 0;
    virtual Sequence<T> *Prepend(T item) = 0;
    virtual Sequence<T> *InsertAt(T item, int index) = 0;

    virtual Sequence<T> *Concat(const Sequence<T> *list) = 0;
    virtual Sequence<T> *GetSubSequence(int start, int end) const = 0;
    virtual Sequence<T> *Clone() const = 0;

    virtual Sequence<T> *Instance() = 0;

    // перегрузки операторов
    T operator[](int index)
    {
        return Get(index);
    }

    Sequence<T> *operator+(Sequence<T> &other)
    {
        return Concat(&other);
    }

    // map, where, reduce
    template <class T2>
    Sequence<T2> *Map(T2 (*func)(T))
    {
        Sequence<T2> *result = this->Instance()->Clone();

        for (int i = 0; i < GetLength(); i++)
        {
            result = result->Append(func(Get(i)));
        }
        return result;
    }

    Sequence<T> *Where(bool (*predicate)(T))
    {
        Sequence<T> *result = this->Instance()->Clone();

        for (int i = 0; i < GetLength(); i++)
        {
            if (predicate(Get(i)))
            {
                result = result->Append(Get(i));
            }
        }
        return result;
    }

    template <class T2>
    T2 Reduce(T2 (*func)(T2, T), T2 start)
    {
        T2 result = start;

        for (int i = 0; i < GetLength(); i++)
        {
            result = func(result, Get(i));
        }
        return result;
    }
};