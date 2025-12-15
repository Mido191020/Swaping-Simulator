#include <iostream>
using namespace std;
#define UNIMPLEMENTED \
    do { \
        fprintf(stderr, "%s:%d: TODO: %s is not implemented yet\n", \
                __FILE__, __LINE__, __func__); \
        abort(); \
    } while (0)



const int Memory_size=20;
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
MemoryFrame memory_table[Memory_size];
Stats stats;
void init_list(){
    for (int i = 0; i < Memory_size; ++i) {
        memory_table[i].is_valid = false; // empty initially
        memory_table[i].VPN = 0;
    }

}
bool check_Page(int VPN){
    //TODO:loop on pages
    stats.accesses++;
    for (int i = 0; i < Memory_size; ++i) {
        if (memory_table[i].VPN==VPN&&memory_table[i].is_valid){
            stats.hits++;
            return true;
        }
    }
    //handel Miss
    stats.misses++;
    for (int i = 0; i < Memory_size; ++i) {
        //page miss>? get page
        //page vaild
        //add it's VPN
        //incrment comp
        //use page from the array or what
        //how we will do somthing like that
        if (memory_table[i].is_valid== false){
            memory_table[i].VPN=VPN;
            memory_table[i].is_valid= true;
            stats.compulsory_misses++;
            return false;
        }
    }
    if (stats.compulsory_misses==Memory_size)
        return false;
    return false;
}

int main() {
    int Accesses[] = {1, 2, 3, 2, 1};
    int n = 5;

    init_list();

    for (int i = 0; i < n; ++i) {
        bool hit = check_Page(Accesses[i]);

        if (hit)
            cout << "Access " << Accesses[i] << " -> HIT\n";
        else
            cout << "Access " << Accesses[i] << " -> MISS\n";
    }

    cout << "\n--- Stats ---\n";
    cout << "Accesses: " << stats.accesses << '\n';
    cout << "Hits: " << stats.hits << '\n';
    cout << "Misses: " << stats.misses << '\n';
    cout << "Compulsory Misses: " << stats.compulsory_misses << '\n';

    return 0;
}
