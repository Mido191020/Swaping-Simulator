#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <cstdlib> // Required for rand() and srand()
#include <ctime>   // Required for time()
#include <cstdint> // Required for uint32_t
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



//M2 random

#define PM_A 16807u                 // Park–Miller multiplier
#define PM_M 2147483647u            // 2^31 - 1 (prime modulus)
typedef struct {
    uint32_t state;
} LCG;

static LCG global_rng;         // Static global RNG instance
static int seeded = 0; // Flag to seed only once


void lcg_srand(LCG* local_rng, uint32_t seed){
    if (seed==0)seed=1;
  local_rng->state=seed;
}
// Park-Miller LCG: X_{n+1} = (a * X_n) % m
static uint32_t lcg_rand_int(LCG* local_rng){
  // rng->state=
    uint64_t product=(uint64_t)local_rng->state *PM_A;
    product=product+0;
    local_rng->state=(uint32_t)(product%PM_M);
    return local_rng->state;
}
int random(int range){
    if (!seeded){
        // Mix time(NULL) with clock() to get unique seeds every microsecond
        uint32_t new_seeded= (uint32_t)time(NULL) ^ (uint32_t)clock();
        lcg_srand(&global_rng, new_seeded);
        seeded=1;
    }
    return lcg_rand_int(&global_rng)%(range+1);
}




// --- Globals ---
MemoryFrame memory_table[Memory_size];
// NO QUEUE NEEDED FOR RANDOM!
Stats stats;

// --- Helper Functions ---

void init_list() {
    for (int i = 0; i < Memory_size; ++i) {
        memory_table[i].is_valid = false; // Mark all slots empty
        memory_table[i].VPN = 0;
    }
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
        // 🎲 RANDOM REPLACEMENT Logic
        target_index = random(Memory_size - 1); // 0..19
// --- ADD THIS DEBUG LINE ---
        printf("🎲 Random Eviction! Victim Index: %d (VPN: %d)\n",
               target_index, memory_table[target_index].VPN);
    }

    // 4. Place the Page
    if (target_index != -1) {
        memory_table[target_index].VPN = VPN;
        memory_table[target_index].is_valid = true;
        // No queue push needed here
        return target_index;
    }

    return -1; // Should not be reached
}

// --- VISUALIZER FUNCTION 🎨 ---
void visualize_memory(int current_vpn, bool is_hit) {
    printf("  [");
    for (int i = 0; i < Memory_size; i++) {
        if (memory_table[i].is_valid) {
            if (memory_table[i].VPN == current_vpn) {
                // Color Code: Green for Hit, Red for Miss (New Load)
                if (is_hit) printf("\033[1;32m%2d\033[0m|", memory_table[i].VPN);
                else        printf("\033[1;31m%2d\033[0m|", memory_table[i].VPN);
            } else {
                printf("%2d|", memory_table[i].VPN);
            }
        } else {
            printf("..|");
        }
    }
    printf("]\n");
}
// --- SCALED UP TRACE GENERATOR 🏋️ ---
void generate_heavy_trace() {
    FILE *f = fopen("input.txt", "w");
    if (!f) { perror("Error"); exit(1); }

    int num_requests = 1000;

    // Generate 1000 requests
    for (int i = 0; i < num_requests; i++) {
        int vpn;
        int chance = random(99);

        // 80% chance: Access "Hot" pages (0-9)
        if (chance < 80) {
            vpn = random(9);
        }
            // 20% chance: Access "Cold" pages (10-49)
        else {
            vpn = 10 + random(39);
        }
        fprintf(f, "%d ", vpn);
    }
    fclose(f);
    printf("✅ Heavy 'input.txt' created (1000 requests).\n");
}

int main() {
    // Setup
    generate_heavy_trace();
    init_list();

    FILE *f = fopen("input.txt", "r");
    if (!f) { perror("Failed to open"); return 1; }

    int vpn;
    printf("\n--- Large Scale Random Simulation ---\n");

    // Loop
    while (fscanf(f, "%d", &vpn) == 1) {
        int old_hits = stats.hits;

        get_frame(vpn);

        bool is_hit = (stats.hits > old_hits);

        // Show the movie for the first 30 frames only (to keep terminal clean)
        if (stats.accesses <= 30) {
            printf("REQ: %2d -> %s ", vpn, is_hit ? "HIT " : "MISS");
            visualize_memory(vpn, is_hit);
        }
    }

    fclose(f);

    printf("\n... (Simulation continued for %d requests) ...\n", stats.accesses);
    printf("\n=== Final Results ===\n");
    printf("Total Accesses:    %d\n", stats.accesses);
    printf("Hits:              %d\n", stats.hits);
    printf("Misses:            %d\n", stats.misses);
    printf("Compulsory Misses: %d\n", stats.compulsory_misses);
    printf("-------------------------\n");
    // Calculate Hit Rate
    printf("HIT RATE:          %.2f%%\n", (float)stats.hits / stats.accesses * 100.0);

    return 0;
}