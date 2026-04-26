#include <iostream>
#include "MutableArraySequence.h"
#include "ImmutableArraySequence.h"

using namespace std;

void PrintMenu()
{
    cout << "Menu\n";
    cout << "1. Create Mutable Sequence\n";
    cout << "2. Create Immutable sequence\n";
    cout << "3. Append\n";
    cout << "4. Prepend\n";
    cout << "5. InsertAt\n";
    cout << "6. Print Sequence\n";
    cout << "7. Slice\n";
    cout << "8. Concat\n";
    cout << "9. Map (square)\n";
    cout << "10. Where (even)\n";
    cout << "11. Reduce (sum)\n";
    cout << "0. Exit\n";
}

int square(int x)
{
    return x * x;
}

bool isEven(int x)
{
    return x % 2 == 0;
}

int sum(int a, int b)
{
    return a + b;
}

void PrintSequence(Sequence<int> *seq)
{
    cout << "Sequence: ";
    for (int i = 0; i < seq->GetLength(); i++)
    {
        cout << (*seq)[i] << " ";
    }
    cout << endl;
}

int main()
{
    Sequence<int> *seq = nullptr;
    int choice;

    do
    {
        PrintMenu();
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
        {
            delete seq;
            seq = new MutableArraySequence<int>();
            cout << "Mutable sequence created\n";
            break;
        }

        case 2:
        {
            delete seq;
            seq = new ImmutableArraySequence<int>();
            cout << "Immutable sequence created\n";
            break;
        }

        case 3:
        {
            int value;
            cout << "Enter value: ";
            cin >> value;

            Sequence<int> *newSeq = seq->Append(value);
            delete seq;
            seq = newSeq;
            break;
        }

        case 4:
        {
            if (!seq)
            {
                cout << "Sequence is not created\n";
                break;
            }
            int value;
            cout << "Enter value: ";
            cin >> value;

            Sequence<int> *newSeq = seq->Prepend(value);
            delete seq;
            seq = newSeq;
            break;
        }

        case 5:
        {
            if (!seq)
            {
                cout << "Sequence is not created\n";
                break;
            }

            int value, index;
            cout << "Enter value and index: ";
            cin >> value >> index;

            Sequence<int> *newSeq = seq->InsertAt(value, index);
            delete seq;
            seq = newSeq;
            break;
        }

        case 6:
        {
            if (seq)
                PrintSequence(seq);
            else
                cout << "Sequence is not created\n";
            break;
        }

        case 7:
        {
            if (!seq)
            {
                cout << "Sequence is not created\n";
                break;
            }

            int start, end;
            cout << "Enter start and end: ";
            cin >> start >> end;

            Sequence<int> *result = seq->GetSubSequence(start, end);
            PrintSequence(result);
            delete result;
            break;
        }

        case 8:
        {
            if (!seq)
            {
                cout << "Sequence is not created\n";
                break;
            }
            int n;
            cout << "Enter size of second sequence: ";
            cin >> n;

            MutableArraySequence<int> temp;

            for (int i = 0; i < n; i++)
            {
                int x;
                cin >> x;
                temp.Append(x);
            }
            Sequence<int> *newSeq = seq->Concat(&temp);
            delete seq;
            seq = newSeq;
            break;
        }

        case 9:
        {
            if (!seq)
            {
                cout << "Sequence is not created\n";
                break;
            }
            Sequence<int> *result = seq->Map(square);
            PrintSequence(result);
            delete result;
            break;
        }

        case 10:
        {
            if (!seq)
            {
                cout << "Sequence is not created\n";
                break;
            }
            Sequence<int> *result = seq->Where(isEven);
            PrintSequence(result);
            delete result;
            break;
        }

        case 11:
        {
            if (!seq)
            {
                cout << "Sequence is not created\n";
                break;
            }
            int result = seq->Reduce(sum, 0);
            cout << "Sum = " << result << endl;
            break;
        }

        case 0:
        {
            cout << "Exit...\n";
            break;
        }

        default:
            cout << "Invalid choice\n";
        }
    } while (choice != 0);
    delete seq;
    return 0;
}