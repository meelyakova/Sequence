#pragma once
#include "ArraySequence.h"

template <class T>
class MutableArraySequence : public ArraySequence<T>
{
public:
    using ArraySequence<T>::ArraySequence;

    Sequence<T> *Clone() const override
    {
        return new MutableArraySequence<T>(*this);
    }

    Sequence<T> *Instance() override
    {
        return this;
    }
};