
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
