#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <cstdlib>
#include <ctime>
#include <cstdint>
#include <climits> // Added for INT32_MAX

using namespace std;
typedef uint64_t u64;

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
    //timestamp
    int Timestamp;
};

// --- Globals ---
MemoryFrame memory_table[Memory_size];
Stats stats;
int Globel_clock = 0;

// --- Helper Functions ---

void init_list() {
    for (int i = 0; i < Memory_size; ++i) {
        memory_table[i].is_valid = false;
        memory_table[i].VPN = 0;
    }
}

int get_indx();

// The Manager: Handles Hits, Misses, and Placements
int get_frame(int VPN) {
    stats.accesses++;
    Globel_clock++;

    // 1. Search for HIT
    for (int i = 0; i < Memory_size; ++i) {
        if (memory_table[i].is_valid && memory_table[i].VPN == VPN) {
            stats.hits++;
            memory_table[i].Timestamp = Globel_clock;
            return i; // HIT
        }
    }

    // --- Handling MISS ---
    stats.misses++;

    // 2. Try to find an Empty Slot (Compulsory Miss)
    int target_index = -1;
    for (int i = 0; i < Memory_size; ++i) {
        if (!memory_table[i].is_valid) {
            target_index = i;
            stats.compulsory_misses++;
            break;
        }
    }

    // 3. If No Empty Slot -> Must EVICT (Capacity Miss)
    if (target_index == -1) {
        target_index = get_indx();
    }

    // 4. Place the Page
    if (target_index != -1) {
        memory_table[target_index].VPN = VPN;
        memory_table[target_index].is_valid = true;
        memory_table[target_index].Timestamp = Globel_clock;
        return target_index;
    }

    return -1;
}

int get_indx(){
    // return index that we will over write on it
    int min_time = INT32_MAX;
    int idx = -1;

    for (int i = 0; i < Memory_size; ++i) {
        if (memory_table[i].is_valid && memory_table[i].Timestamp < min_time){
            min_time = memory_table[i].Timestamp;
            idx = i;
        }
    }
    return idx;
}

// Visualizer function

// Trace Generator
void generate_heavy_trace() {
    FILE *f = fopen("input.txt", "w");
    if (!f) { perror("Error"); exit(1); }

    int num_requests = 1000;

    printf("Generating 1000 requests (80%% Hot Set 0-9)...\n");

    // Generate 1000 requests
    for (int i = 0; i < num_requests; i++) {
        int vpn;
        int chance = rand() % 100;

        // 80% chance: Access "Hot" pages (0-9)
        if (chance < 80) {
            vpn = rand() % 10;
        }
            // 20% chance: Access "Cold" pages (10-49)
        else {
            vpn = 10 + (rand() % 40);
        }
        fprintf(f, "%d ", vpn);
    }
    fclose(f);
}
// --- Updated Visualizer Function ---
void visualize_memory(int current_vpn, bool is_hit, FILE* log_file, bool show_screen) {
    // 1. Screen Output (ANSI Colors)
    if (show_screen) {
        printf("  VPNS: [");
        for (int i = 0; i < Memory_size; i++) {
            if (memory_table[i].is_valid) {
                if (memory_table[i].VPN == current_vpn) {
                    if (is_hit) printf("\033[1;32m%3d \033[0m|", memory_table[i].VPN);
                    else        printf("\033[1;31m%3d \033[0m|", memory_table[i].VPN);
                } else {
                    printf("%3d |", memory_table[i].VPN);
                }
            } else {
                printf(" .  |");
            }
        }
        printf("]\n");

        printf("  TIME: [");
        for (int i = 0; i < Memory_size; i++) {
            if (memory_table[i].is_valid) {
                if (memory_table[i].VPN == current_vpn)
                    printf("\033[1;33m%3d \033[0m|", memory_table[i].Timestamp);
                else printf("%3d |", memory_table[i].Timestamp);
            } else {
                printf(" .  |");
            }
        }
        printf("] (Current Clock: %d)\n", Globel_clock);
        printf("------------------------------------------------------------\n");
    }

    // 2. File Output (Plain Text)
    if (log_file != NULL) {
        fprintf(log_file, "  VPNS: [");
        for (int i = 0; i < Memory_size; i++) {
            if (memory_table[i].is_valid) fprintf(log_file, "%3d |", memory_table[i].VPN);
            else fprintf(log_file, " .  |");
        }
        fprintf(log_file, "]\n");

        fprintf(log_file, "  TIME: [");
        for (int i = 0; i < Memory_size; i++) {
            if (memory_table[i].is_valid) fprintf(log_file, "%3d |", memory_table[i].Timestamp);
            else fprintf(log_file, " .  |");
        }
        fprintf(log_file, "] (Current Clock: %d)\n", Globel_clock);
        fprintf(log_file, "------------------------------------------------------------\n");
    }
}

// --- Updated Main Function ---
int main() {
    srand(time(NULL));
    generate_heavy_trace();
    init_list();

    FILE *f = fopen("input.txt", "r");
    if (!f) { perror("Failed to open input.txt"); return 1; }

    FILE *log_file = fopen("visualizer_log.txt", "w");
    if (!log_file) { perror("Failed to open log file"); }

    int vpn;
    printf("\n--- LRU Simulation ---\n");

    while (fscanf(f, "%d", &vpn) == 1) {
        int old_hits = stats.hits;

        get_frame(vpn);

        bool is_hit = (stats.hits > old_hits);
        bool show_screen = (stats.accesses <= 30);

        // Print request status to Screen
        if (show_screen) {
            printf("REQ: %2d -> %s ", vpn, is_hit ? "HIT " : "MISS");
        }

        // Print request status to File
        if (log_file) {
            fprintf(log_file, "REQ: %2d -> %s\n", vpn, is_hit ? "HIT " : "MISS");
        }

        // Call Visualizer for both
        visualize_memory(vpn, is_hit, log_file, show_screen);
    }

    fclose(f);
    if (log_file) fclose(log_file);

    printf("\n... (Simulation continued for %d requests) ...\n", stats.accesses);
    printf("\n=== Final Results ===\n");
    printf("Total Accesses:    %d\n", stats.accesses);
    printf("Hits:              %d\n", stats.hits);
    printf("Misses:            %d\n", stats.misses);
    printf("Compulsory Misses: %d\n", stats.compulsory_misses);
    printf("-------------------------\n");
    printf("HIT RATE:          %.2f%%\n", (float)stats.hits / stats.accesses * 100.0);

    return 0;
}