#pragma once
#include "ListSequence.h"

template <class T>
class MutableListSequence : public ListSequence<T>
{
public:
    using ListSequence<T>::ListSequence;

    Sequence<T> *Instance() override
    {
        return this;
    }

    Sequence<T> *Clone() const override
    {
        return new MutableListSequence<T>(*this);
    }
};