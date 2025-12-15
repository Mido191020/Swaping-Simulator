#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <queue>

using namespace std;

// --- Constants & Structures ---
const int Memory_size = 20;

struct Stats {
    int accesses = 0;
    int hits = 0;
    int misses = 0;
    int compulsory_misses = 0;
};

struct MemoryFrame {
    int VPN = 0;       // Virtual Page Number
    bool is_valid = false;
};

// --- Globals ---
MemoryFrame memory_table[Memory_size];
queue<int> MemoryQueue; // Stores VPNs in arrival order
Stats stats;

// --- Helper Functions ---

void init_list() {
    for (int i = 0; i < Memory_size; ++i) {
        memory_table[i].is_valid = false; // Mark all slots empty
        memory_table[i].VPN = 0;
    }
}

// The Evictor: Removes the oldest page and returns the freed slot index
int free_frame() {
    if (MemoryQueue.empty()) return -1; // Safety check

    // 1. Get the oldest VPN from the Queue
    int vpnToFree = MemoryQueue.front();
    MemoryQueue.pop();

    // 2. Find that VPN in the Hardware (Array)
    for (int i = 0; i < Memory_size; ++i) {
        if (memory_table[i].VPN == vpnToFree && memory_table[i].is_valid) {
            // Found it! Kill it.
            memory_table[i].is_valid = false;
            return i; // Return the empty chair index so we can reuse it
        }
    }
    return -1; // Should never happen if Queue and Table are synced
}

// The Manager: Handles Hits, Misses, and Placements
int get_frame(int VPN) {
    stats.accesses++;

    // 1. Search for HIT
    for (int i = 0; i < Memory_size; ++i) {
        if (memory_table[i].is_valid && memory_table[i].VPN == VPN) {
            stats.hits++;
            return i; // HIT! Return the index where we found it
        }
    }

    // --- Handling MISS ---
    stats.misses++;

    // 2. Try to find an Empty Slot (Compulsory Miss)
    int target_index = -1;
    for (int i = 0; i < Memory_size; ++i) {
        if (!memory_table[i].is_valid) {
            target_index = i; // Found a free chair
            stats.compulsory_misses++;
            break;
        }
    }

    // 3. If No Empty Slot -> Must EVICT (Capacity Miss)
    if (target_index == -1) {
        target_index = free_frame(); // Kick the oldest one out
    }

    // 4. Place the Page
    if (target_index != -1) {
        memory_table[target_index].VPN = VPN;
        memory_table[target_index].is_valid = true;

        // IMPORTANT: Add to Queue only on placement (Miss)
        MemoryQueue.push(VPN);
        return target_index;
    }

    return -1; // Should not be reached
}

void generate_test_file() {
    FILE *f = fopen("input.txt", "w");
    if (f == NULL) {
        perror("Error creating input.txt");
        exit(1);
    }

    // Phase 1: Fill Memory (1..20)
    for (int i = 1; i <= 20; i++) {
        fprintf(f, "%d ", i);
    }
    // Phase 2: Hits (1, 10, 15)
    fprintf(f, "1 10 15 ");
    // Phase 3: Eviction (21 kills 1)
    fprintf(f, "21 ");
    // Phase 4: Miss Check (1 is gone, so 1 kills 2)
    fprintf(f, "1 ");

    fclose(f);
    printf("✅ input.txt created.\n");
}

int main() {
    // 1. Setup
    generate_test_file();
    init_list();

    // 2. Open File
    FILE *f = fopen("input.txt", "r");
    if (!f) { perror("Failed to open input.txt"); return 1; }

    int vpn;
    printf("\n--- Starting Simulation ---\n");

    // 3. Run Simulation Loop
    while (fscanf(f, "%d", &vpn) == 1) {
        printf("Request: %d ... ", vpn);

        int old_misses = stats.misses;
        get_frame(vpn);

        if (stats.misses > old_misses) {
            printf("MISS\n");
        } else {
            printf("HIT\n");
        }
    }

    fclose(f);

    // 4. Final Stats
    printf("\n=== Final Results ===\n");
    printf("Total Accesses:    %d\n", stats.accesses);
    printf("Hits:              %d\n", stats.hits);
    printf("Misses:            %d\n", stats.misses);
    printf("Compulsory Misses: %d\n", stats.compulsory_misses);

    return 0;
}