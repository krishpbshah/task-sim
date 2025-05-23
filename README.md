# Multicore Task Scheduling Simulator (C++)

This project simulates a multi-core CPU task scheduling environment using custom-built circular deques. It models task execution, redistribution, and load balancing across cores, simulating how modern operating systems handle dynamic workloads.

Each CPU core maintains its own dynamically resizable circular deque, allowing push and pop operations from both ends with O(1) amortized time. The simulation supports task assignment, execution, and stealing based on the core's workload.

A central CPU class manages all cores and their interactions. Supported operations include:
- SPAWN(P_ID): Assigns task P_ID to the least-busy core
- RUN(C_ID): Executes the front task of core C_ID
- SLEEP(C_ID): Redistributes tasks from sleeping core C_ID to others
- PUSH(C_ID): Helper used by RUN to steal tasks from the busiest core
- SHUTDOWN(): Deletes all remaining tasks in every core
- SIZE/CAPACITY: Displays current queue size or buffer capacity for a given core

Internally, the project uses a dynamic array of Deque objects where each Deque is a custom circular buffer that grows as needed. Memory management is handled manually to ensure proper allocation and deallocation.

Example system architecture:
Core 0 <--> Core 1 <--> Core 2 ... (each with its own task queue)

### Sample Commands
ON 4                  # Initialize system with 4 cores  
SPAWN 100             # Spawn task 100 → assigned to least-busy core  
RUN 1                 # Run task from core 1  
SLEEP 2               # Redistribute tasks from sleeping core 2  
SIZE 0                # Print task count in core 0  
CAPACITY 0            # Print buffer capacity in core 0  
SHUTDOWN              # Remove all tasks  
EXIT                  # Terminate simulation  

### Build & Run

Requirements:  
- g++ or any C++ compiler

To build:
make

To run:
./main < input.txt

Replace input.txt with a file containing command sequences or use terminal input directly.

### Output Example
success  
core 0 assigned task 100  
core 1 is running task 200  
task 300 assigned to core 2 task 400 assigned to core 3  
size is 2  
capacity is 4  
deleting task 100 from core 0 deleting task 200 from core 1  

### Concepts Demonstrated
- Custom dynamic circular deque implementation  
- Load balancing and task stealing simulation  
- Manual memory management in C++  
- Object-oriented system modeling  
- Command-based task scheduling and parsing  

### Author
Krish Shah  
*Generative AI was used for debugging and explanation assistance.*
