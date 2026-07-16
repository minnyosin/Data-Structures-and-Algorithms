#include <iostream>

using namespace std;
class Queue
{
    char* list;
    int maxQueueSize;
    int queueFront;
    int queueRear;

public:
    Queue(int maxSize)
    {
        maxQueueSize = maxSize;
        queueFront = 0;
        queueRear = -1;
        list = new char[maxQueueSize];

    }
    ~Queue()
    {
        delete[] list;
    }
    void Enqueue(char n)
    {
        if (queueRear < maxQueueSize - 1)
        {
            queueRear++;
            list[queueRear] = n;
        }
        
    }
    char Dequeue()
    {
        if (queueRear >= queueFront)
        {
  
            return list[queueFront++];

        }
    }
    bool isEmpty()
    {
        return queueRear < queueFront;
    }
    int getSize()
    {
        return queueRear - queueFront + 1;
    }
    void Display()
    {
        if (queueRear > queueFront)
        {
            for (int i = queueFront; i <= queueRear; i++)
            {
                cout << list[i] << endl;
            }
        }
    }
};
void CA1()
{
    int size;
    char input;

    cout << "How many elements in a queue? : ";
    cin >> size;
    Queue* queue1 = new Queue(size);
    cout << "Adding elements to a queue... " << endl;
    for (int i = 0; i < size; i++)
    {
        cout << "Enter element " << i + 1 << ": ";
        cin >> input;
        queue1->Enqueue(input);
    }
    cout << "How many elements to be removed from the queue? : ";
    cin >> size;

    cout << "Removing from the queue : " << endl;
    for (int i = 0; i < size; i++)
    {
        cout << queue1->Dequeue() << endl;
    }
    if (queue1->isEmpty())
    {
        cout << "Queue is empty!" << endl;
    }
    else
    {
        cout << "Queue has " << queue1->getSize() << " elements." << endl;
        cout << "Displaying the Queue..." << endl;
        queue1->Display();
    }

    
    delete queue1;
}
int main()
{
    CA1();


    return 0;
}

