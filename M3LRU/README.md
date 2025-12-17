# Milestone 3: Least Recently Used (LRU) Policy

## Overview

This milestone implements the Least Recently Used (LRU) page replacement policy, moving beyond simple approaches to optimize memory management through usage history tracking.

## Core Concept

Modern programs demonstrate "locality of reference"—they frequently access a specific set of pages during execution. LRU capitalizes on this pattern by:

- **Retaining frequently accessed pages** in memory
- **Evicting pages that haven't been used recently**, as they are unlikely to be needed again soon

## Technical Implementation

### 1. Global Logical Clock

A simulation clock (`Global_clock`) tracks the timeline of all memory requests, providing precise ordering of events.

### 2. Enhanced Memory Frame Structure

The `MemoryFrame` structure now includes temporal metadata:

```cpp
struct MemoryFrame {
    int VPN;
    bool is_valid;
    int timestamp;  // Records last access time
};
```

### 3. Algorithm Logic

- **On Cache Hit**: Update the page's timestamp to the current `Global_clock` value, marking it as recently used
- **On Eviction**: Scan all frames to identify and evict the page with the oldest timestamp

## Visualization and Logging

The simulator includes diagnostic tools to verify LRU behavior:

**Console Output:**
```
REQ:  8 -> HIT  
  VPNS: [  2 | 44 |  8 |  9 | .. ]
  TIME: [ 26 | 27 | 95 | 28 | .. ]
```

**File Logging:**  
Complete execution history is written to `visualizer_log.txt` for detailed analysis.

## Performance Results

Testing against a workload of 1,000 requests with 80% locality:

| Metric    | Random Policy (M2) | LRU Policy (M3) | Improvement |
|-----------|-------------------|-----------------|-------------|
| Hit Rate  | ~76.0%           | 84.0%          | +8.0%      |
| Misses    | ~240             | 160            | -80 faults |

## Conclusion

LRU successfully identifies and protects frequently accessed pages, delivering an 8% improvement in hit rate over random replacement. By tracking usage history, the policy ensures that active pages remain in memory while inactive pages are evicted efficiently.
