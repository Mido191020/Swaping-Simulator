## 🧱 Milestone 1: FIFO Replacement Policy

In this milestone, we implemented the **First-In, First-Out (FIFO)** algorithm. This is the simplest baseline for page replacement.

### 🧠 The Logic

* **Concept:** Treat physical memory like a line at a grocery store. The first page to arrive is the first one to leave when space is needed.
* **Data Structure:** We use a C++ `std::queue<int>` alongside our physical memory array.
    * **On Miss (Placement):** The new VPN is pushed to the back of the queue.
    * **On Eviction:** We `pop` the VPN from the front of the queue (the oldest) and invalidate that specific slot in the memory array.
* **Hit Handling:** FIFO ignores hits. Accessing a page that is already in memory **does not** move it to the back of the line.

### 🧪 Validation Scenario

We verify correctness using a deterministic test case:

1.  **Fill Phase:** Load pages `1` through `20`. Memory is now full.
    * *Queue State:* `[Front: 1, ..., Back: 20]`
2.  **Hit Phase:** Access `1`, `10`, `15`.
    * *Result:* **HITS**. The queue order remains unchanged (Page 1 is still the "victim").
3.  **Eviction Phase:** Access Page `21`.
    * *Action:* Memory is full. The algorithm identifies Page `1` as the oldest.
    * *Result:* Page `1` is evicted. Page `21` takes its slot.
4.  **Verification Phase:** Access Page `1` again.
    * *Result:* **MISS**. This proves Page 1 was successfully removed.

### 💻 How to Run
```bash
# Compile
g++ main.cpp -o vm_sim

# Run (Generates input.txt automatically)
./vm_sim
```

### Expected Output
```
...
Request: 21 ... MISS  <-- Eviction triggered (1 removed)
Request: 1 ... MISS   <-- Verification successful (1 is gone)

=== Final Results ===
Hits:              3
Misses:            22
Compulsory Misses: 20
```
