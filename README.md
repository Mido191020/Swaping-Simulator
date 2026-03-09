# Swapping & Page Replacement Simulator

<div align="center">
  <img src="https://img.shields.io/badge/Language-C++-00599C?style=for-the-badge&logo=c%2B%2B&logoColor=white" />
  <img src="https://img.shields.io/badge/Concept-Operating_Systems-4D4D4D?style=for-the-badge&logo=linux&logoColor=white" />
  <img src="https://img.shields.io/badge/Pattern-Memory_Simulation-00A98F?style=for-the-badge" />
</div>

<br/>

## 📌 Project Overview

The **Swapping & Page Replacement Simulator** is a dedicated Operating Systems memory management project built in generic C++. It explicitly models the mathematical and structural behavior of a Virtual Memory system when an operating system encounters a **Page Fault** and must arbitrate which pages to swap between main memory (RAM) and secondary storage (Disk Swap Space).

This simulator visualizes how Capacity Misses and Compulsory Misses happen over time in a fixed memory constraint, comparing the efficiency of fundamental replacement policies.

---

## ⚙️ OS Concepts & Algorithms Modeled

Through the `M1`, `M2`, and `M3` modules, this project demonstrates three major Page Replacement Algorithms in action on a constrained 20-frame RAM simulation:

### 1️⃣ First-In, First-Out (FIFO)

- **Module:** `M1/main.cpp`
- **Mechanism:** Maintains a queue of Virtual Page Numbers (VPNs) mapped into RAM.
- **Eviction:** When a Capacity Miss occurs, the oldest loaded page at the front of the queue is swapped out.

### 2️⃣ Random Replacement

- **Module:** `M2Random-Replacement/main.cpp`
- **Mechanism:** Implements a Park-Miller Linear Congruential Generator (LCG) to select an eviction victim entirely by pseudo-random chance.
- **Eviction:** Drops a purely random loaded page to fetch the incoming page fault.

### 3️⃣ Least Recently Used (LRU)

- **Module:** `M3LRU/main.cpp`
- **Mechanism:** Utilizes a global timestamp clock incremented on every memory reference, saving the access time of hits and newly loaded pages.
- **Eviction:** When memory fills up, the system scans the RAM array for the minimum timestamp and evicts the historically least accessed frame.

---

## 🏗️ Architecture & Model Design

- **Main Memory Layout:** RAM is modeled strictly as a 20-slot block using structural primitives `MemoryFrame memory_table[20]`.
- **Secondary Storage:** Handled implicitly. When a page is absent from the `memory_table`, it triggers an OS-level fetch from disk.
- **Process Trace Generation:** The system models a heavy single-process execution stream (up to 1,000 memory requests) generated programmatically with varying temporal locality (80% hot-pages, 20% cold-pages distribution in `M3`).

---

## 🚀 Execution Flow & Features

During runtime, the simulator evaluates the stream of Virtual Page Numbers:

1. **Search Phase:** The MMU translates the reference, checking RAM for `vpn`.
2. **Page Hit!:** If found, the hit statistics index correctly. (LRU updates the access clock).
3. **Compulsory Miss:** The page isn't anywhere in RAM, but frames happen to be empty. It automatically occupies an empty spot.
4. **Capacity Miss (Swap Operation):** The page isn't in RAM, *and* all 20 frames are full. The OS triggers an Eviction Algorithm to mathematically represent a Swap-Out to disk to open up a free frame for the Swap-In.

### 🎨 Live Graphical Terminal Visualization

The simulator provides vivid, color-coded ANSI terminal outputs out-of-the-box dynamically charting RAM state:

- **`Green` Slots:** Indicates a registered Hit.
- **`Red` Slots:** Indicates a localized Miss and recent swap-in event.
- Real-time logging output is saved continuously into an automated artifact `visualizer_log.txt`.

### 📊 End-Of-Run Statistics

Accurate readouts of hit-rate efficiencies are calculated upon conclusion:

- **Total Accesses**
- **Hits** / **Misses**
- **Compulsory Misses vs Capacity Misses**
- Final **Hit Rate %** based on the generated reference trace.

---

## 🛠️ Build & Installation Guide

You will need a standard **C++ Builder** environment (GCC/Clang) and **CMake**.

```bash
# 1. Clone the repository
git clone https://github.com/Mido191020/Swaping-Simulator.git
cd Swaping-Simulator

# 2. Enter into one of the 3 specific Page Replacement modules
cd M3LRU 

# 3. Setup CMake context
mkdir build
cd build
cmake ..
make

# 4. Run the simulator trace
./swaping_simulator
# Observe the colored GUI logic terminal render!
```

---

<div align="center">
   <i>Demonstrating foundational Systems Programming logic & Memory Hierarchy optimization strategies.</i>
</div>