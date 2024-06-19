#include <stdio.h>
#include <stdlib.h>

// SRP: Process struct only handles process data
struct Process {
    int pid;                // Process ID
    int arrival_time;       // Arrival time of the process
    int burst_time;         // Burst time required for the process
    int priority;           // Priority of the process
    int remaining_time;     // Remaining time needed for the process to complete
};

// Function to initialize a process
void create_process(struct Process *p, int pid, int arrival_time, int burst_time, int priority) {
    p->pid = pid;
    p->arrival_time = arrival_time;
    p->burst_time = burst_time;
    p->priority = priority;
    p->remaining_time = burst_time;
}

// OCP, LSP, DIP: Scheduler struct handles different scheduling algorithms and logging
typedef void (*SchedulingFunction)(struct Scheduler *);
typedef void (*LogFunction)(const char *message);

struct Scheduler {
    struct Process *process_list;   // Array of processes
    int num_processes;              // Number of processes in the list
    SchedulingFunction schedule;    // Function pointer for scheduling algorithm
    LogFunction log;                // Function pointer for logging
};

// FIFO Scheduling Algorithm
void fifo_scheduling(struct Scheduler *scheduler) {
    scheduler->log("Running FIFO Scheduling...");
    // FIFO scheduling logic
}

// Round Robin Scheduling Algorithm
void round_robin_scheduling(struct Scheduler *scheduler) {
    scheduler->log("Running Round Robin Scheduling...");
    // Round Robin scheduling logic
}

// Function to log messages to the console
void console_log(const char *message) {
    printf("%s\n", message);
}

// Function to simulate the scheduler
void simulate_scheduler(struct Scheduler *scheduler) {
    scheduler->log("Starting simulation...");
    scheduler->schedule(scheduler);     // Execute the selected scheduling algorithm
    scheduler->log("Simulation finished.");
}

int main() {
    // Create an array of processes
    struct Process processes[2];
    create_process(&processes[0], 1, 0, 10, 1);   // Initialize process 1
    create_process(&processes[1], 2, 0, 5, 2);    // Initialize process 2

    // Initialize the scheduler
    struct Scheduler scheduler;
    scheduler.process_list = processes;          // Assign the array of processes to the scheduler
    scheduler.num_processes = 2;                  // Set the number of processes
    scheduler.log = console_log;                 // Assign the console_log function to log
    scheduler.schedule = fifo_scheduling;        // Assign FIFO scheduling algorithm (or round_robin_scheduling)

    // Simulate the scheduler
    simulate_scheduler(&scheduler);

    return 0;
}


