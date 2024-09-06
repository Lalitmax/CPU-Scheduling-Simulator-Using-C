Here's an updated version of your **CPU Scheduling Simulator** documentation, including guidelines for other contributors and how they can run their test cases:

---

# CPU Scheduling Simulator

## Overview

The **CPU Scheduling Simulator** is a C-based project designed to demonstrate various CPU scheduling algorithms and their performance. The simulator includes implementations of several key scheduling techniques, such as:

- **First-Come, First-Served (FCFS)**: Executes jobs in the order they arrive.
- **Shortest Job First (SJF)**: Executes jobs with the shortest execution time first.
- **Round-Robin (RR)**: Cycles through jobs with a fixed time slice (quantum).
- **Priority Scheduling**: Executes jobs based on priority levels.

The project allows users to input job data, select scheduling algorithms, and view the scheduling results.

## Features

- **FCFS Scheduling**: Executes jobs in the order they arrive.
- **SJF Scheduling**: Executes jobs with the shortest execution time first.
- **RR Scheduling**: Cycles through jobs with a fixed time slice.
- **Priority Scheduling**: Executes jobs based on priority levels.
- **File Input Support**: Allows scheduling input via `.txt` files for easy testing and simulation.

## Requirements

- **Language**: C
- **Compiler**: GCC (or any standard C compiler)
- **Development Platform**: Linux (Kali, Ubuntu) or macOS (or any POSIX-compliant system)

## Installation

1. Clone the repository:
   ```bash
   git clone https://github.com/your-repo/CPUSchedulingSimulator.git
   ```

2. Compile the project:
   ```bash
   gcc -o test_output main.c -L. cpu_scheduling_algo.a
   ```


## Running the Simulator

Once compiled, you can run the simulator by providing test case files as input:

```bash
./test_output
```

### Input File Structure In Test Cases folder

Each test case file should have the following format:
```
AlgorithmName.txt  here you can add your which algo you want to perform
```
Example Like

```
AlgorithmName = PriorityScheduling

```
And This is particular Algo Details Like

Example
FirstComeFirstServe.txt Have

```
NoOfProcess = 4
ArrivalTime = 0 1 5 6 <list of arrival times>
BurstTime = 2 2 3 4 <list of burst times>


```

RoundRobin.txt Have

```
NoOfProcess = 4
ArrivalTime = 0 1 2 4  
BurstTime = 5 4 2 1  
QuantumTime = 2 <timeSlice> (only for RR)

```
ShortestJobFirst have

```
Mode = Preemptive
NoOfProcess = 6
ArrivalTime = 0 1 2 3 4 5
BurstTime = 8 4 2 1 3 2

```
And PriorityScheduling have

```
NoOfProcess = 4
Priority = 10 20 30 40 <list of priorities> (only for Priority Scheduling)
ArrivalTime = 0 1 2 4
BurstTime = 5 4 2 1

```

## How to Contribute

We welcome contributions from developers! To contribute to the project, follow the steps below:

### 1. Fork the repository:
   Fork the repository on GitHub to start working on your own copy.

### 2. Clone your fork:
   Clone your forked repository to your local machine:
   ```bash
   git clone https://github.com/your-username/CPUSchedulingSimulator.git
   ```

### 3. Create a new branch:
   Create a new branch for your changes:
   ```bash
   git checkout -b feature/scheduling-algorithm
   ```

### 4. Make your changes:
   Implement your improvements, fixes, or features, such as adding new scheduling algorithms, optimizing existing ones, or improving the UI/UX of the simulation.

### 5. Run Tests:
   Ensure your code works correctly by running the simulator with different test cases.

   - Place your test cases in the `Test Cases/` folder.
   - Each test case should follow the **Input File Structure** mentioned earlier.
   - ` AlgorithmName.txt` here you have to specify which algo you want to perform
   - `Ex. FirstComeFirstServe.txt have  ,  AlgorithmName = FirstComeFirstServe`
   
   You can run tests like this:

   Compile code
   ```bash
      gcc -o test_output main.c -L. cpu_scheduling_algo.a
   ```
   Run Code
    ```bash
      ./test_output
   ```

### 6. Commit and push:
   Commit your changes and push them to your fork:
   ```bash
   git add .
   git commit -m "Added feature for <your-feature>"
   git push -u origin  main
   ```

### 7. Create a pull request:
   Open a pull request (PR) on GitHub with a description of your changes and the problem it solves.

### 8. Code Review:
   The maintainers will review your PR and, once approved, it will be merged into the main branch.

## Testing Guidelines

To ensure the simulator works as expected, you can create test cases using the format outlined in the **Input File Structure** section. Test cases can be created to simulate different job arrival times, burst times, and scheduling algorithms.

Sample test case files are located in the `TestCases/` directory. You can also write your own test cases and run the simulator using them. For example:

```bash
./test_output
```


Feel free to contribute and enhance this project by adding more scheduling algorithms, optimizing existing ones, or improving the UI and performance. 
<------------------------------------------------❤️---------------------------------------------------->
