
# Virtual Memory Replacement Policy Simulator
## Simulation Setup

✅ **Heavy 'input.txt' created** (1000 requests)

**Configuration:**

- Algorithm: Random Page Replacement
- Frame Size: 20 frames
- Test Scale: Large Scale Random Simulation

---

## Initial Phase - Cold Start

### Memory Filling Phase (First 30 Requests)

|Request #|VPN|Result|Memory State|
|---|---|---|---|
|1|5|MISS|`[ 5\|..\|..\|..\|..\|..\|..\|..\|..\|..\|..\|..\|..\|..\|..\|..\|..\|..\|..\|..]`|
|2|20|MISS|`[ 5\|20\|..\|..\|..\|..\|..\|..\|..\|..\|..\|..\|..\|..\|..\|..\|..\|..\|..\|..]`|
|3|9|MISS|`[ 5\|20\| 9\|..\|..\|..\|..\|..\|..\|..\|..\|..\|..\|..\|..\|..\|..\|..\|..\|..]`|
|4|2|MISS|`[ 5\|20\| 9\| 2\|..\|..\|..\|..\|..\|..\|..\|..\|..\|..\|..\|..\|..\|..\|..\|..]`|
|5|42|MISS|`[ 5\|20\| 9\| 2\|42\|..\|..\|..\|..\|..\|..\|..\|..\|..\|..\|..\|..\|..\|..\|..]`|
|6|6|MISS|`[ 5\|20\| 9\| 2\|42\| 6\|..\|..\|..\|..\|..\|..\|..\|..\|..\|..\|..\|..\|..\|..]`|
|7|5|**HIT**|`[ 5\|20\| 9\| 2\|42\| 6\|..\|..\|..\|..\|..\|..\|..\|..\|..\|..\|..\|..\|..\|..]`|
|8|5|**HIT**|`[ 5\|20\| 9\| 2\|42\| 6\|..\|..\|..\|..\|..\|..\|..\|..\|..\|..\|..\|..\|..\|..]`|
|9|5|**HIT**|`[ 5\|20\| 9\| 2\|42\| 6\|..\|..\|..\|..\|..\|..\|..\|..\|..\|..\|..\|..\|..\|..]`|
|10|1|MISS|`[ 5\|20\| 9\| 2\|42\| 6\| 1\|..\|..\|..\|..\|..\|..\|..\|..\|..\|..\|..\|..\|..]`|
|11|6|**HIT**|`[ 5\|20\| 9\| 2\|42\| 6\| 1\|..\|..\|..\|..\|..\|..\|..\|..\|..\|..\|..\|..\|..]`|
|12|0|MISS|`[ 5\|20\| 9\| 2\|42\| 6\| 1\| 0\|..\|..\|..\|..\|..\|..\|..\|..\|..\|..\|..\|..]`|
|13|2|**HIT**|`[ 5\|20\| 9\| 2\|42\| 6\| 1\| 0\|..\|..\|..\|..\|..\|..\|..\|..\|..\|..\|..\|..]`|
|14|2|**HIT**|`[ 5\|20\| 9\| 2\|42\| 6\| 1\| 0\|..\|..\|..\|..\|..\|..\|..\|..\|..\|..\|..\|..]`|
|15|6|**HIT**|`[ 5\|20\| 9\| 2\|42\| 6\| 1\| 0\|..\|..\|..\|..\|..\|..\|..\|..\|..\|..\|..\|..]`|
|16|6|**HIT**|`[ 5\|20\| 9\| 2\|42\| 6\| 1\| 0\|..\|..\|..\|..\|..\|..\|..\|..\|..\|..\|..\|..]`|
|17|9|**HIT**|`[ 5\|20\| 9\| 2\|42\| 6\| 1\| 0\|..\|..\|..\|..\|..\|..\|..\|..\|..\|..\|..\|..]`|
|18|9|**HIT**|`[ 5\|20\| 9\| 2\|42\| 6\| 1\| 0\|..\|..\|..\|..\|..\|..\|..\|..\|..\|..\|..\|..]`|
|19|0|**HIT**|`[ 5\|20\| 9\| 2\|42\| 6\| 1\| 0\|..\|..\|..\|..\|..\|..\|..\|..\|..\|..\|..\|..]`|
|20|6|**HIT**|`[ 5\|20\| 9\| 2\|42\| 6\| 1\| 0\|..\|..\|..\|..\|..\|..\|..\|..\|..\|..\|..\|..]`|
|21|16|MISS|`[ 5\|20\| 9\| 2\|42\| 6\| 1\| 0\|16\|..\|..\|..\|..\|..\|..\|..\|..\|..\|..\|..]`|
|22|34|MISS|`[ 5\|20\| 9\| 2\|42\| 6\| 1\| 0\|16\|34\|..\|..\|..\|..\|..\|..\|..\|..\|..\|..]`|
|23|6|**HIT**|`[ 5\|20\| 9\| 2\|42\| 6\| 1\| 0\|16\|34\|..\|..\|..\|..\|..\|..\|..\|..\|..\|..]`|
|24|47|MISS|`[ 5\|20\| 9\| 2\|42\| 6\| 1\| 0\|16\|34\|47\|..\|..\|..\|..\|..\|..\|..\|..\|..]`|
|25|49|MISS|`[ 5\|20\| 9\| 2\|42\| 6\| 1\| 0\|16\|34\|47\|49\|..\|..\|..\|..\|..\|..\|..\|..]`|
|26|9|**HIT**|`[ 5\|20\| 9\| 2\|42\| 6\| 1\| 0\|16\|34\|47\|49\|..\|..\|..\|..\|..\|..\|..\|..]`|
|27|0|**HIT**|`[ 5\|20\| 9\| 2\|42\| 6\| 1\| 0\|16\|34\|47\|49\|..\|..\|..\|..\|..\|..\|..\|..]`|
|28|33|MISS|`[ 5\|20\| 9\| 2\|42\| 6\| 1\| 0\|16\|34\|47\|49\|33\|..\|..\|..\|..\|..\|..\|..]`|
|29|7|MISS|`[ 5\|20\| 9\| 2\|42\| 6\| 1\| 0\|16\|34\|47\|49\|33\| 7\|..\|..\|..\|..\|..\|..]`|
|30|0|**HIT**|`[ 5\|20\| 9\| 2\|42\| 6\| 1\| 0\|16\|34\|47\|49\|33\| 7\|..\|..\|..\|..\|..\|..]`|

---

## Random Eviction Phase

### Page Replacement Events (Sample)

After memory fills up, the Random algorithm selects victims randomly:

```
🎲 Random Eviction! Victim Index: 15 (VPN: 4)
🎲 Random Eviction! Victim Index: 16 (VPN: 8)
🎲 Random Eviction! Victim Index: 4 (VPN: 42)
🎲 Random Eviction! Victim Index: 16 (VPN: 28)
🎲 Random Eviction! Victim Index: 6 (VPN: 1)
🎲 Random Eviction! Victim Index: 10 (VPN: 47)
🎲 Random Eviction! Victim Index: 6 (VPN: 42)
🎲 Random Eviction! Victim Index: 14 (VPN: 29)
🎲 Random Eviction! Victim Index: 3 (VPN: 2)
🎲 Random Eviction! Victim Index: 19 (VPN: 48)
```

_... (continued for 970+ evictions throughout the simulation) ..._

---

## Final Performance Metrics

### 📊 Summary Statistics

|Metric|Value|Percentage|
|---|---|---|
|**Total Accesses**|1,000|100%|
|**Hits**|761|76.10%|
|**Misses**|239|23.90%|
|**Compulsory Misses**|20|2.00%|

### 🎯 Hit Rate Analysis

```
╔═══════════════════════════════════════╗
║         HIT RATE: 76.10%              ║
╚═══════════════════════════════════════╝
```

**Performance Breakdown:**

- **Cache Hits:** 761 requests served from memory
- **Page Faults:** 239 requests required page replacement
- **Cold Start Misses:** 20 compulsory misses (first-time page loads)
- **Capacity/Conflict Misses:** 219 misses (23.90% - 2.00%)

---

## Analysis

### Key Observations

1. **High Hit Rate:** The 76.10% hit rate indicates good locality of reference in the access pattern
2. **Compulsory Misses:** Only 20 unique pages accessed initially (2% of total accesses)
3. **Random Algorithm Behavior:** Unpredictable evictions as expected with random replacement
4. **Memory Utilization:** 20-frame capacity fully utilized after initial cold start

### Algorithm Characteristics

**Random Replacement:**

- ✅ Simple implementation
- ✅ No overhead for tracking access patterns
- ❌ No exploitation of temporal or spatial locality
- ❌ May evict frequently-used pages

---
