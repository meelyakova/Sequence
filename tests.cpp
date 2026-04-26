#include <iostream>
#include <cassert>

#include "MutableArraySequence.h"
#include "ImmutableArraySequence.h"
#include "MutableListSequence.h"
#include "ImmutableListSequence.h"

using namespace std;

int square(int x) { return x * x; }
bool isEven(int x) { return x % 2 == 0; }
int sum(int a, int b) { return a + b; }

// Array
void TestArrayBasic()
{
    MutableArraySequence<int> seq;
    seq.Append(1)->Append(2)->Append(3);

    assert(seq.GetLength() == 3);
    assert(seq[0] == 1);
    assert(seq[2] == 3);
}

void TestArrayInsert()
{
    MutableArraySequence<int> seq;
    seq.Append(1)->Append(3);
    seq.InsertAt(2, 1);

    assert(seq[1] == 2);
}

void TestArrayConcat()
{
    MutableArraySequence<int> a;
    a.Append(1)->Append(2);

    MutableArraySequence<int> b;
    b.Append(3);

    Sequence<int> *c = a.Concat(&b);

    assert(c->GetLength() == 3);
    assert((*c)[2] == 3);

    delete c;
}

void TestArraySlice()
{
    MutableArraySequence<int> seq;
    seq.Append(1)->Append(2)->Append(3)->Append(4);

    Sequence<int> *sub = seq.Slice(1, 2);

    assert(sub->GetLength() == 2);
    assert((*sub)[0] == 2);
    assert((*sub)[1] == 3);

    delete sub;
}

// List
void TestListBasic()
{
    MutableListSequence<int> seq;
    seq.Append(1)->Append(2);

    assert(seq.GetLength() == 2);
    assert(seq[1] == 2);
}

void TestListInsert()
{
    MutableListSequence<int> seq;
    seq.Append(1)->Append(3);
    seq.InsertAt(2, 1);

    assert(seq[1] == 2);
}

void TestListConcat()
{
    MutableListSequence<int> a;
    a.Append(1);

    MutableListSequence<int> b;
    b.Append(2);

    Sequence<int> *c = a.Concat(&b);

    assert(c->GetLength() == 2);
    assert((*c)[1] == 2);

    delete c;
}

void TestMap()
{
    MutableArraySequence<int> seq;
    seq.Append(1)->Append(2)->Append(3);

    Sequence<int> *result = seq.Map(square);

    assert((*result)[0] == 1);
    assert((*result)[1] == 4);
    assert((*result)[2] == 9);

    delete result;
}

void TestWhere()
{
    MutableArraySequence<int> seq;
    seq.Append(1)->Append(2)->Append(3)->Append(4);

    Sequence<int> *result = seq.Where(isEven);

    assert(result->GetLength() == 2);
    assert((*result)[0] == 2);
    assert((*result)[1] == 4);

    delete result;
}

void TestReduce()
{
    MutableArraySequence<int> seq;
    seq.Append(1)->Append(2)->Append(3);

    int result = seq.Reduce(sum, 0);

    assert(result == 6);
}

// Immutable
void TestImmutableArray()
{
    ImmutableArraySequence<int> seq;
    seq.Append(1)->Append(2);

    Sequence<int> *newSeq = seq.Append(3);

    assert(seq.GetLength() == 2);
    assert(newSeq->GetLength() == 3);

    delete newSeq;
}

void TestImmutableList()
{
    ImmutableListSequence<int> seq;
    seq.Append(1);

    Sequence<int> *newSeq = seq.Append(2);

    assert(seq.GetLength() == 1);
    assert(newSeq->GetLength() == 2);

    delete newSeq;
}

// Edge
void TestOutOfRange()
{
    MutableArraySequence<int> seq;
    seq.Append(1);

    try
    {
        seq.Get(5);
        assert(false);
    }
    catch (...)
    {
        assert(true);
    }
}

void TestEmpty()
{
    MutableArraySequence<int> seq;

    assert(seq.GetLength() == 0);

    Sequence<int> *result = seq.Where(isEven);

    assert(result == nullptr || result->GetLength() == 0);

    delete result;
}

void TestConcatEmpty()
{
    MutableArraySequence<int> a;
    a.Append(1);

    MutableArraySequence<int> b;

    Sequence<int> *c = a.Concat(&b);

    assert(c->GetLength() == 1);

    delete c;
}

void TestSliceEdges()
{
    MutableArraySequence<int> seq;
    seq.Append(1)->Append(2)->Append(3);

    Sequence<int> *sub = seq.Slice(0, 2);

    assert(sub->GetLength() == 3);

    delete sub;
}

void TestOperationIndex()
{
    MutableArraySequence<int> seq;
    seq.Append(1)->Append(2);
    assert(seq[0] == 1);
    assert(seq[1] == 2);
}

int main()
{
    TestArrayBasic();
    TestArrayInsert();
    TestArrayConcat();
    TestArraySlice();

    TestListBasic();
    TestListInsert();
    TestListConcat();

    TestMap();
    TestWhere();
    TestReduce();

    TestImmutableArray();
    TestImmutableList();

    TestOutOfRange();
    TestEmpty();
    TestOperationIndex();
    TestConcatEmpty();
    TestSliceEdges();

    cout << "All tests passed seccessfully" << endl;
    return 0;
}