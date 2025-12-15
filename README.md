# Virtual Memory Swaping-Simulator Simulator

**A learning-first simulator to understand virtual memory, page replacement, and caching policies.**

---

## 📌 Project Goal

This project simulates how an operating system manages **virtual memory** and **page replacement**.

**You will learn to:**

* Track pages in RAM
* Measure **hits** and **misses**
* Implement classic **page replacement algorithms**
* Visualize the behavior of different policies under various workloads

This project is **educational**, not kernel-level code. Everything runs in user space.

---

## 🗺️ Milestones

### **Milestone 0 – Foundations**

**Goal:** Set up the simulator skeleton.

**Tasks:**

* Define **MemoryFrame** structure (`VPN`, `valid bit`)
* Initialize memory
* Implement **page access logic** (check if page is in memory)
* Track **accesses, hits, misses, compulsory misses**
* Test with a **small, manual access list**

**Learning outcome:** Understand memory lookup and tracking **before implementing replacement policies**.

---

### **Milestone 1 – FIFO Replacement**

**Goal:** Implement **First-In, First-Out** eviction.

**Tasks:**

* Add **eviction logic** when memory is full
* Track **cold misses vs capacity misses**
* Understand how FIFO ignores locality

**Learning outcome:** Learn why naive eviction can cause poor performance.

---

### **Milestone 2 – Random Replacement**

**Goal:** Compare with a stateless policy.

**Tasks:**

* Randomly evict a page when memory is full
* Control **random seed** for repeatability
* Compare hit/miss statistics with FIFO

**Learning outcome:** Observe the performance difference between deterministic and random eviction.

---

### **Milestone 3 – Optimal (Belady’s MIN)**

**Goal:** Implement an **offline oracle**.

**Tasks:**

* Use **future knowledge** of page accesses
* Evict the page that will be used **farthest in the future**

**Learning outcome:** Establish an **upper bound** for replacement policy performance.

---

### **Milestone 4 – Perfect LRU**

**Goal:** Implement **Least Recently Used (perfect)**.

**Tasks:**

* Maintain **access timestamp** for each page
* Evict the **oldest page**
* Compare with FIFO and Random

**Learning outcome:** Understand **true LRU behavior** and its cost.

---

### **Milestone 5 – Clock (Approximate LRU)**

**Goal:** Simulate an **OS-realistic LRU approximation**.

**Tasks:**

* Use **reference bits**
* Implement **clock hand pointer** logic
* Compare results with perfect LRU

**Learning outcome:** Learn how OSes implement LRU efficiently.

---
