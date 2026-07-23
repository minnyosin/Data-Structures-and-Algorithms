#include <iostream>

using namespace std;

template <class T>
class NodeType
{
public:
    T info;
    NodeType<T>* next;
};

template <class T>
class LinkedListQueue
{
public:
    NodeType<T>* head;
    NodeType<T>* tail;
    int size = 0;

    LinkedListQueue()
    {
        this->head = nullptr;
        this->tail = nullptr;
        this->size = 0;
    }
    ~LinkedListQueue()
    {
        
        while (head != nullptr)
        {
            NodeType<T>* current = head;
            head = head->next;
            delete current;
            
        }
        tail = nullptr;
        size = 0;
    }
    void Enqueue(T value)
    {
        NodeType<T>* newNode = new NodeType<T>;
        newNode->info = value;
        newNode->next = nullptr;

        if (head == nullptr)
        {
            head = tail = newNode;
        }
        else
        {
            tail->next = newNode;
            tail = newNode;
        }
        size++;
    }
    void Dequeue()
    {
        if (size <= 0)
        {
            cout << "The Queue is Empty!" << endl;
        }
        else
        {
            NodeType<T>* toDelete = head;
            head = head->next;
            delete toDelete;
            size--;
            if (head == nullptr)
            {
                head = tail = nullptr;
            }
        }
    }
    bool isEmpty()
    {
        return size <= 0;
    }
    int getSize()
    {
        return size;
    }
    void Display()
    {
        if (size > 0)
        {
            NodeType<T>* current = head;
            for (int i = 0; i < size; i++)
            {
                cout << current->info << endl;
                current = current->next;
            }
        }
    }
};

class ArrayQueue
{
    char* list;
    int maxQueueSize;
    int queueFront;
    int queueRear;

public:
    ArrayQueue(int maxSize)
    {
        maxQueueSize = maxSize;
        queueFront = 0;
        queueRear = -1;
        list = new char[maxQueueSize];

    }
    ~ArrayQueue()
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
        return NULL;
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
        if (queueRear >= queueFront)
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
    ArrayQueue* queue1 = new ArrayQueue(size);
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
void CA2()
{
    LinkedListQueue<string>* TP = new LinkedListQueue<string>;
    
    TP->Enqueue("TP01");
    TP->Enqueue("TP02");
    TP->Enqueue("TP03");
    TP->Dequeue();
    TP->Enqueue("TP04");
    TP->Enqueue("TP05");
    TP->Dequeue();
    TP->Enqueue("TP02");

    TP->Display();
    
    delete TP;

}
int main()
{
    //CA1();
    CA2();


    return 0;
}

