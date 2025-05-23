#include <iostream>
using namespace std;
#include "myheader.hpp"
// AI was used in this project for general confusions and debugging
CPU::CPU()
{
    cores = nullptr; // set cores to nullptr
    num_cores = 0;   // num of cores to 0
}

CPU::~CPU()
{
    if (cores != nullptr)
    {
        delete[] cores; // deallocate the memory of the cores if not nullptr
    }
}

void CPU::ON(int N)
{
    if (cores != nullptr || N <= 1) // if not nullptr or numbers of cores less than 1 set to fail
    {                               // Check for valid parameter
        cout << "failure" << endl;
        return;
    }
    num_cores = N;
    cores = new Deque[N]; // Dynamically allocate N deques for N cores
    cout << "success" << endl;
}

void CPU::SPAWN(int P_ID)
{
    if (cores == nullptr || P_ID <= 0)
    {
        cout << "failure" << endl;
        return;
    }

    int index = 0; // set index to 0 for the cores with the least amount of tasks
    for (int i = 1; i < num_cores; i++)
    {
        if (cores[i].size < cores[index].size ||
            (cores[i].size == cores[index].size && i < index)) // comparing the sizes of the cores to find the one with the least amount of wokr
        {
            index = i; // Update to the least busy core
        }
    }

    cores[index].push_rear(P_ID); // pushes the task to the least busy core
    cout << "core " << index << " assigned task " << P_ID << endl;
}

void CPU::RUN(int C_ID)
{
    if (C_ID < 0 || C_ID >= num_cores)
    {
        cout << "failure" << endl;
        return;
    }

    if (cores[C_ID].size == 0) // if the core is empty
    {
        cout << "core " << C_ID << " has no tasks to run" << endl;

        PUSH(C_ID); // use the PUSH function to find the core with the most amount of tasks and push it last tasks into the empty core

        return;
    }

    int task = cores[C_ID].pop_front(); // Get the task to run
    cout << "core " << C_ID << " is running task " << task << endl;

    if (cores[C_ID].size == 0)
    {
        PUSH(C_ID);
    }
}

void CPU::PUSH(int C_ID)
{

    int index = -1; // set index to -1
    for (int i{0}; i < num_cores; ++i)
    {
        if (i != C_ID && (index == -1 || cores[i].size > cores[index].size)) // ensure the index is not equal to the core index or the length of the indexed core isnt greater than the i core itself
        {
            index = i; // set the new index to i if it has a greater size
        }
    }
    if (index != -1 && !(cores[index].size == 0)) // ensure the index is not -1 and the length is not 0, so no empty list
    {
        int pop = cores[index].pop_rear(); // removing the last value from the core with the most tasks

        if (pop != -1) // ensure its value is not negative one
        {
            cores[C_ID].push_rear(pop); // push the value to the core C_ID
        }
    }
}

void CPU::SLEEP(int C_ID)
{
    if (C_ID < 0 || C_ID >= num_cores)
    {
        cout << "failure" << endl;
        return;
    }

    if (cores[C_ID].size == 0) // empty core
    {
        cout << "core " << C_ID << " has no tasks to assign" << endl;
        return;
    }

    // Give tasks to the other cores
    while (cores[C_ID].size > 0)
    {
        int task = cores[C_ID].pop_rear(); // Remove tasks from the current core
        int least_busy = -1;               // Set to -1 to find the least busy core
        for (int i = 0; i < num_cores; i++)
        {
            if (i != C_ID && (least_busy == -1 || cores[i].size < cores[least_busy].size)) // ensure not equal to current core value and less than the i index core size
            {
                least_busy = i; // Find least busy core
            }
        }
        // Ensure valid core assignment
        if (least_busy != -1)
        {
            cores[least_busy].push_rear(task); // Assign the task
            cout << "task " << task << " assigned to core " << least_busy << " ";
        }
    }
    cout << endl;
}

void CPU::SHUTDOWN()
{
    bool tasks_removed = false;
    for (int i = 0; i < num_cores; ++i)
    {
        while (cores[i].size > 0)
        {
            int task = cores[i].pop_front(); // Remove the task from the front
            cout << "deleting task " << task << " from core " << i << " ";
            tasks_removed = true;
        }
    }
    if (!tasks_removed)
    {
        cout << "no tasks to remove\n"; // Consistent message output
    }
    else
    {
        cout << "\n"; // New line for better formatting
    }
}

void CPU::SIZE(int C_ID)
{
    if (C_ID < 0 || C_ID >= num_cores)
    {
        cout << "failure" << endl;
        return;
    }
    cout << "size is " << cores[C_ID].size << endl; // Direct access to size
}

void CPU::CAPACITY(int C_ID)
{
    if (C_ID < 0 || C_ID >= num_cores)
    {
        cout << "failure" << endl;
        return;
    }
    cout << "capacity is " << cores[C_ID].capacity << endl; // Direct access to capacity
}
