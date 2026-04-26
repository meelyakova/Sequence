#pragma once
#include <stdexcept>

template <class T>
class DynamicArray
{
private:
    T *data;
    int size;

public:
    DynamicArray(int size)
    {
        if (size < 0)
            throw std::out_of_range("Size cannot be negative");

        this->size = size;
        data = new T[size];
    }

    DynamicArray(const T *items, int count)
    {
        if (count < 0)
            throw std::out_of_range("Count cannot be negative");

        size = count;
        data = new T[size];

        for (int i = 0; i < size; i++)
        {
            data[i] = items[i];
        }
    }

    DynamicArray(const DynamicArray<T> &other)
    {
        size = other.size;
        data = new T[size];

        for (int i = 0; i < size; i++)
        {
            data[i] = other.data[i];
        }
    }

    ~DynamicArray()
    {
        delete[] data;
    }

    T Get(int index)
    {
        if (index < 0 || index >= size)
            throw std::out_of_range("Index out of range");

        return data[index];
    }

    int GetSize() const
    {
        return size;
    }

    void Set(int index, T value)
    {
        if (index < 0 || index >= size)
            throw std::out_of_range("Index out of range");

        data[index] = value;
    }

    void Resize(int newSize)
    {
        if (newSize < 0)
            throw std::out_of_range("New size cannot be negative");

        T *newData = new T[newSize];
        int minSize = (newSize < size) ? newSize : size;

        for (int i = 0; i < minSize; i++)
        {
            newData[i] = data[i];
        }

        delete[] data;
        data = newData;
        size = newSize;
    }
};