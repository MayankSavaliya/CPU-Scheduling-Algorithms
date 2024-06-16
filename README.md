# CPU-Scheduling-Algorithms


This repository contains implementations of various CPU scheduling algorithms in C++. The algorithms implemented are:

- Round Robin (RR)
- First-Come-First-Serve (FCFS)
- Shortest-Job-First (SJF)
- Shortest-Remaining-Time-First (SRTF)

## Introduction

CPU scheduling is a fundamental concept in operating systems where the scheduler decides which of the processes in the ready queue is to be allocated the CPU. The goal of CPU scheduling is to make the system efficient, fast, and fair.

## Implemented Algorithms

### Round Robin (RR)
Round Robin is a preemptive scheduling algorithm where each process is assigned a fixed time slice or quantum. When a process's time quantum expires, the next process in the ready queue is given the CPU.

### First-Come-First-Serve (FCFS)
FCFS is the simplest CPU scheduling algorithm that schedules according to the arrival times of various processes. The process that arrives first is scheduled first.

### Shortest-Job-First (SJF)
SJF is a non-preemptive scheduling algorithm where the process with the shortest burst time is scheduled next. It can reduce the average waiting time for other processes.

### Shortest-Remaining-Time-First (SRTF)
SRTF is a preemptive version of SJF. In this algorithm, the process with the smallest amount of time remaining until completion is selected to execute next.

## Usage

To compile and run the program, follow these steps:

1. Clone the repository:
    ```sh
    git clone https://github.com/yourusername/CPU-Scheduling-Algorithms.git
    ```

2. Navigate to the project directory:
    ```sh
    cd CPU-Scheduling-Algorithms
    ```

3. Compile the program using a C++ compiler, e.g., `g++`:
    ```sh
    g++ -std=c++17 -o scheduling scheduling.cpp
    ```

4. Run the executable:
    ```sh
    ./scheduling
    ```

5. Follow the prompts to enter the number of processes, their arrival times, and burst times. For Round Robin, you will also need to enter the time quantum.

