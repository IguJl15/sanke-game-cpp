#include <stdlib.h>
#include "node.hpp"

template <typename T>
class Queue
{
private:
    int maxCapacity;

public:
    int count;
    Node<T> *rear = nullptr;
    Node<T> *front = nullptr;

    Queue();
    Queue(int length);
    ~Queue();

    void enQueue(T item);
    T deQueue();

    bool isFull();
    bool isEmpty();
};

template <typename T>
Queue<T>::Queue()
{
    maxCapacity = 0;
}

template <typename T>
Queue<T>::~Queue()
{
    for (int i = 0; i < count; i++)
    {
        deQueue();
    }
}
template <typename T>
Queue<T>::Queue(int length)
{
    maxCapacity = length;
}

template <typename T>
void Queue<T>::enQueue(T item)
{
    if (isFull())
    {
        throw;
    }

    Node<T> *newItem = (Node<T> *)malloc(sizeof(Node<T>));
    newItem->value = item;

    count++;

    if (front == nullptr || rear == nullptr)
    {
        front = newItem;
        rear = newItem;
        return;
    }

    rear->next = newItem;
    rear = newItem;

    return;
}

template <typename T>
T Queue<T>::deQueue()
{
    if (isEmpty())
    {
        throw;
    }

    count--;

    // Persist current front attributes
    T value = front->value;

    if (isEmpty())
    {
        rear = nullptr;
        front = nullptr;
    }
    else
    {
        front->next != nullptr;
        Node<T> *newFront = front->next;
        // Free current front Node
        free(front);
        // Use the next Node as front
        front = newFront;
    }

    return value;
}

template <typename T>
bool Queue<T>::isFull()
{
    return count == maxCapacity;
}

template <typename T>
bool Queue<T>::isEmpty()
{
    return count == 0;
}