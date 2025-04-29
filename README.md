
# CS 3502 Project 2 - CPU Scheduling and Deadlock Management

## Overview
This project implements two CPU scheduling algorithms:
- **Shortest Remaining Time First (SRTF)** — Preemptive scheduling
- **Highest Response Ratio Next (HRRN)** — Non-preemptive scheduling

The project tracks performance metrics including:
- Average Waiting Time
- Average Turnaround Time
- CPU Utilization
- Throughput

## Files Included
- `cpu_scheduler.cpp` — C++ source code implementing SRTF and HRRN
- `CS_3502_Project_2_Technical_Documentation.pdf` — Full project report
- `Screenshots/` — Captured execution outputs for both algorithms

## How to Compile and Run
```bash
g++ -o cpu_scheduler cpu_scheduler.cpp
./cpu_scheduler
## How to Test the Scheduler
1. Compile and run the program.
2. Enter the number of processes (example: 3).
3. Enter arrival time and burst time for each process.
4. Choose a scheduling algorithm:
   - 1 for Shortest Remaining Time First (SRTF)
   - 2 for Highest Response Ratio Next (HRRN)
5. Review the Gantt chart and performance metrics displayed in the console.
