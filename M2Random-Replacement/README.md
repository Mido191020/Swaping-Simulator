# 🧠 Virtual Memory Replacement Policy Simulator

> **A high-performance, trace-driven simulator to analyze and visualize Operating System memory management policies.**

[![C++](https://img.shields.io/badge/C++-00599C?style=flat&logo=c%2B%2B&logoColor=white)](https://isocpp.org/) [![License](https://img.shields.io/badge/License-MIT-yellow.svg)](https://claude.ai/chat/LICENSE) [![Status](https://img.shields.io/badge/Status-Active-success)](https://github.com/)

---

## 🚀 Project Overview

This project is an educational yet robust simulation engine designed to replicate how an Operating System manages physical memory frames. It implements various **Page Replacement Algorithms** to measure Hit Rates, Miss Rates, and Compulsory Misses under different workload pressures.

### 🌟 Key Features

Unlike standard textbook implementations, this simulator features:

- **🎲 Custom Random Number Generation:** Implements a Linear Congruential Generator (LCG) from scratch to ensure deterministic debugging and high-quality randomness
- **📺 Real-Time Terminal Visualizer:** Live visualization of page faults and evictions as they happen
- **📈 Scalable Trace Generation:** Capable of simulating thousands of memory requests with configurable "Locality of Reference" (Hot/Cold sets)
- **📄 Persistent Output:** Generates beautifully formatted  [`output.md`] files for post-simulation analysis

---

## 🎲 Milestone 2: Random Replacement Policy

### 💡 Core Concept

The **Random Replacement Policy** (aka "Lottery Approach") evicts a page randomly when memory is full, rather than tracking page age or access history.

**Why Random?**

- ✅ **Stateless:** No memory overhead for tracking metadata
- ✅ **Robust:** Avoids pathological worst-case scenarios (e.g., Belady's Anomaly in FIFO)
- ✅ **Simple:** Easy to implement and debug
- ✅ **Fair:** Every page has an equal chance of eviction

### 🛠️ Technical Deep Dive: Custom RNG Engine

To maintain the "from scratch" philosophy of this project, we implemented a custom **Linear Congruential Generator (LCG)** without relying on standard library random functions.

**Algorithm:** Park-Miller LCG based on the Mersenne prime $(2^{31}-1)$

```
X_{n+1} = (a · X_n) mod m
where:
  a = 48271 (multiplier)
  m = 2^31 - 1 (modulus, a Mersenne prime)
```

**Seeding Strategy:**

```cpp
seed = time(NULL) ^ clock()
```

This XOR combination ensures unique seeds even during rapid-fire testing, preventing predictable patterns.

### 📐 Algorithm Workflow

1. **Page Request arrives** → Check if page exists in memory
2. **If HIT** → Page found, increment hit counter
3. **If MISS:**
    - If memory has space → Load page into next available frame
    - If memory is full → **Randomly select a victim frame [0, N-1]** and replace it

---

## 📊 Performance Analysis

We subjected the Random Policy to a **"Heavy Workload"** simulation designed to mimic real-world program behavior.

### 🧪 Test Configuration

|Parameter|Value|Description|
|---|---|---|
|**Total Requests**|1,000|Memory access operations|
|**Memory Size**|20 Frames|Physical memory capacity|
|**Locality Model**|80/20 Rule|80% requests target 20% of pages (Hot Set)|
|**Page Range**|0-49|50 unique virtual pages|

### 📈 Simulation Results

Despite the stochastic nature of random eviction, the strong locality of reference allowed the "Hot Set" to remain resident in RAM, resulting in impressive performance:

```text
╔═══════════════════════════════════════╗
║      RANDOM POLICY PERFORMANCE        ║
╠═══════════════════════════════════════╣
║  Total Accesses:      1,000           ║
║  Hits:                  761           ║
║  Misses:                239           ║
║  Compulsory Misses:      20           ║
║                                       ║
║  HIT RATE:           76.10%           ║
╚═══════════════════════════════════════╝
```

**Key Insights:**

- 🎯 **76.10% Hit Rate:** Strong performance under realistic workload
- 🆕 **20 Compulsory Misses:** Only 20 unique pages in Hot Set (2% of accesses)
- 🔄 **219 Capacity Misses:** Remaining misses due to limited frame capacity
- 📊 **80/20 Distribution:** Random policy successfully maintained Hot Set in memory

---

## 💻 Visualizer & Output

### Real-Time Terminal Output

The simulator provides live feedback as requests are processed:

```text
REQ:  5 -> HIT    [ 5|20| 9| 2|42| 6|..|..|..|..|..|..|..|..|..|..|..|..|..|..]
REQ: 47 -> MISS   [ 5|20| 9| 2|42|47|..|..|..|..|..|..|..|..|..|..|..|..|..|..]
🎲 Random Eviction! Victim Index: 3 (VPN: 2)
REQ: 33 -> MISS   [ 5|20| 9|33|42|47|..|..|..|..|..|..|..|..|..|..|..|..|..|..]
```

### 📄 Persistent Output File (`output.md`)



---

## 🛠️ How to Build & Run

### Prerequisites

- **GCC/G++** (C++11 or later)
- **Linux/Unix/WSL** environment (for terminal colors)

### Compilation

```bash
g++ main.cpp -o vm_sim -std=c++11
```

### Execution

```bash
./vm_sim
```

The program will automatically:

1. ✅ Generate `input.txt` (1,000 memory requests with 80/20 locality)
2. ✅ Run the simulation with real-time visualization
3. ✅ Display final performance statistics
4. ✅ Create `output.md` for detailed analysis

---

## 🏗️ Architecture & Milestones

### ✅ Milestone 0: Simulator Skeleton

- Core memory management data structures
- Request trace file parsing
- Basic hit/miss tracking

### ✅ Milestone 1: FIFO (First-In, First-Out)

- **Concept:** "Grocery Line" approach - oldest page evicted first
- **Implementation:** `std::queue` for arrival order tracking
- **Limitation:** Susceptible to Belady's Anomaly

### ✅ Milestone 2: Random Replacement (Current)

- **Concept:** "Lottery" approach - random victim selection
- **Innovation:** Custom LCG implementation from scratch
- **Advantage:** Stateless, memory-efficient, robust

## 📚 References & Study Material

This project was built with deep research into systems programming and random number generation:

1. **Random Number Generation:**  
    _"Random Number Generator: How Do Computers Generate Random Numbers?"_  
    [FreeCodeCamp](https://www.freecodecamp.org/news/random-number-generator/)
    
2. **LCG Implementation:**  
    _"Custom Implementation of Random Number Generator"_  
    [GitHub: igor-240340](https://github.com/igor-240340/RandomNumberGeneration)
    
3. **Technical Deep Dive:**  
    _"Understanding Linear Congruential Generator"_  
    [Hashnode: MidoXMax](https://midoxmax.hashnode.dev/understanding-linear-congruential-generator)
    
4. **Operating Systems Concepts:**  
    _"Operating System Concepts"_ by Silberschatz, Galvin, and Gagne
    

---

## 📁 Project Structure

```
Virtual-Memory-Simulator/
│
├── main.cpp              # Main simulation engine
├── input.txt             # Auto-generated trace file (1000 requests)
├── output.md             # Detailed simulation report
├── README.md             # This file
└── vm_sim                # Compiled executable
```

---

