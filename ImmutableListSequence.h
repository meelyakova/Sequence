#pragma once
#include "ListSequence.h"

template <class T>
class ImmutableListSequence : public ListSequence<T>
{
public:
    using ListSequence<T>::ListSequence;

    Sequence<T> *Instance() override
    {
        return this->Clone();
    }

    Sequence<T> *Clone() const override
    {
        return new ImmutableListSequence<T>(*this);
    }
};