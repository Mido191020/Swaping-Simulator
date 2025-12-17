# Virtual Memory Swapping Simulator

A trace-driven simulator built to analyze and visualize operating system memory management policies.

## Project Overview

This project simulates how an operating system manages physical memory frames under pressure. It was developed to understand and visualize the logic behind classic page replacement algorithms.

The simulator runs in user space, allowing for detailed inspection of algorithmic behavior, hit/miss statistics, and real-time visualization of memory states.

**Learning Outcomes:**

- **Memory Virtualization:** Understanding the mapping between Virtual Page Numbers (VPN) and Physical Frames
- **Locality of Reference:** Simulating realistic workload patterns to test algorithm effectiveness
- **Algorithmic Efficiency:** Comparing different replacement policies and their trade-offs

## Project Architecture

The project evolved through three stages, each implementing a progressively more sophisticated algorithm.

### Milestone 1: FIFO (First-In, First-Out)

**Location:** `M1/`

**Approach:** The oldest page loaded into memory is the first one evicted, similar to a queue structure.

**Result:** Simple to implement but suffers from Belady's Anomaly, where adding more memory can paradoxically increase miss rates.

### Milestone 2: Random Replacement

**Location:** `M2Random-Replacement/`

**Approach:** When memory is full, a random frame is selected for eviction.

**Implementation:** Uses a custom Linear Congruential Generator (Park-Miller algorithm) for robust, high-speed randomness without external dependencies.

**Result:** Better than FIFO in worst-case scenarios, but unpredictable since it ignores page usage patterns.

### Milestone 3: Least Recently Used (LRU)

**Location:** `M3LRU/` and `main.cpp`

**Approach:** Tracks temporal locality by assuming recently accessed pages will likely be accessed again soon.

**Implementation:**
- Global Logical Clock that increments on every memory request
- Timestamping system where each frame stores its last access time
- Eviction mechanism that selects the frame with the oldest timestamp

**Result:** Most efficient policy for typical workloads, successfully protecting frequently accessed pages from eviction.

## Performance Comparison

Testing was performed using a workload of 1,000 requests with 80% locality (80% of requests target 20% of pages).

| Algorithm | Hit Rate | Misses | Analysis |
|-----------|----------|--------|----------|
| Random (M2) | ~76.0% | ~240 | Solid performance, but occasionally evicts popular pages |
| LRU (M3) | 84.0% | 160 | Superior performance by identifying and protecting frequently accessed pages |

## Features

### Memory State Visualization

The simulator includes a real-time terminal visualizer showing both the contents of memory and their recency information:

```
REQ:  8 -> HIT  
  VPNS: [  2 | 44 |  8 | .. ] 
  TIME: [ 26 | 27 | 95 | .. ] (Clock: 95)
```

### Execution Logging

Complete execution history is written to `visualizer_log.txt` for detailed analysis and debugging.

## Directory Structure

- `M1/` - FIFO implementation
- `M2Random-Replacement/` - Random policy implementation
- `M3LRU/` - LRU implementation with detailed documentation
- `main.cpp` - Final production build with complete LRU engine and visualization
- `visualizer_log.txt` - Generated execution log

## How to Run

**Compile:**
```bash
g++ main.cpp -o vm_sim
```

**Execute:**
```bash
./vm_sim
```

The program automatically generates a workload trace and runs the simulation.

## Technical References

- Random Number Generation: GeeksForGeeks - "Random Number Generator: How Do Computers Generate Random Numbers?"
- Linear Congruential Generators: MidoXMax Hashnode - "Understanding LCG"
- OS Concepts: Silberschatz, Galvin, and Gagne - "Operating System Concepts"

## Author

Built as an educational project to explore operating systems concepts and memory management algorithms.

December 2025
