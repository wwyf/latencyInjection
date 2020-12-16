#include <iostream>
#include <chrono>


static uint64_t write_latency = 1000000000;
static uint64_t CPU_FREQ_MHZ = 2000;
static inline void cpu_pause()
{
    __asm__ volatile ("pause" ::: "memory");
}

static inline unsigned long read_tsc(void)
{
    unsigned long var;
    unsigned int hi, lo;

    asm volatile ("rdtsc" : "=a" (lo), "=d" (hi));
    var = ((unsigned long long int) hi << 32) | lo;

    return var;
}


int main(){
    auto start_time = std::chrono::high_resolution_clock::now();
    uint64_t etsc = read_tsc() + (unsigned long)(write_latency*CPU_FREQ_MHZ/1000);
    while(read_tsc() < etsc) cpu_pause();
    auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(
        std::chrono::high_resolution_clock::now() - start_time).count();
    std::cout << duration << std::endl;

    std::cout << "hello, world" << std::endl;
}