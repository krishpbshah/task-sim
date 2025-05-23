#ifndef CPU_H
#define CPU_H

class Deque
{

public:
    int *queue;
    int front;
    int rear;
    int capacity;
    int size;

    // Resizes the queue dynamically based on size

    // Constructor
    Deque() : queue(new int[4]), front(-1), rear(-1), capacity(4), size(0) {}

    // Destructor
    ~Deque()
    {
        delete[] queue;
    }

    // Pushes a task to the front of the deque
    void push_front(int task_id)
    {
        if (size == capacity)
        {
            resize();
        }
        if (front == -1)
        {
            front = rear = 0;
        }
        else if (front == 0)
        {
            front = capacity - 1;
        }
        else
        {
            front--;
        }
        queue[front] = task_id;
        size++;
    }

    // Pushes a task to the rear of the deque
    void push_rear(int task_id)
    {
        if (size == capacity)
        {
            resize();
        }
        if (rear == -1)
        {
            front = rear = 0;
        }
        else
        {
            rear = (rear + 1) % capacity;
        }
        queue[rear] = task_id;
        size++;
    }

    // Pops a task from the front of the deque
    int pop_front()
    {
        if (size == 0)
        {
            return -1;
        }
        int value = queue[front];
        if (size == 1)
        {
            front = rear = -1;
        }
        else
        {
            front = (front + 1) % capacity;
        }
        size--;
        if (size <= capacity / 4 && capacity > 2)
        {
            resize();
        }
        return value;
    }

    // Pops a task from the rear of the deque
    int pop_rear()
    {
        if (size == 0)
        {
            return -1;
        }
        int value = queue[rear];
        if (size == 1)
        {
            front = rear = -1;
        }
        else if (rear == 0)
        {
            rear = capacity - 1;
        }
        else
        {
            rear--;
        }
        size--;
        if (size <= capacity / 4 && capacity > 2)
        {
            resize();
        }
        return value;
    }

    void resize()
    {
        int newCapacity;
        if (size == capacity)
        {
            newCapacity = capacity * 2;
        }
        else if (size <= capacity / 4 && capacity > 2)
        {
            newCapacity = capacity / 2;
        }
        else
        {
            return;
        }

        int *newQueue = new int[newCapacity];
        for (int i = 0; i < size; i++)
        {
            newQueue[i] = queue[(front + i) % capacity];
        }

        delete[] queue;
        queue = newQueue;
        capacity = newCapacity;
        front = 0;
        rear = size - 1;
    }
};

class CPU
{
private:
    Deque *cores; // Array of deques for cores
    int num_cores;

public:
    CPU();
    ~CPU();

    void ON(int N);
    void SPAWN(int P_ID);
    void RUN(int C_ID);
    void SLEEP(int C_ID);
    void SHUTDOWN();
    void SIZE(int C_ID);
    void CAPACITY(int C_ID);
    void PUSH(int C_ID);
};

#endif
