#include <iostream>
#include <immintrin.h>
#include <x86intrin.h>
#include <chrono>


//static uint64_t write_latency = 1000000000;
//static uint64_t write_latency = 10;
static uint32_t write_latency = 100;
static uint32_t CPU_FREQ_MHZ = 2300;
static uint32_t latency_cycles = (uint32_t)(write_latency*CPU_FREQ_MHZ/1000);
static inline void cpu_pause()
{
    __asm__ volatile ("pause" ::: "memory");
}

static inline uint32_t read_tsc_lo(void)
{
    uint32_t hi, lo;

    asm volatile ("rdtsc" : "=a" (lo), "=d" (hi));

    return lo;
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
    auto end_time = std::chrono::high_resolution_clock::now();
    uint64_t start_c, end_c;
    uint64_t temp_c;
    std::cout << "latency :" << write_latency << std::endl;
    std::cout << "latency_cycle :" << latency_cycles << std::endl;
    start_time = std::chrono::high_resolution_clock::now();
    start_c = _rdtsc();
    temp_c = _rdtsc() + latency_cycles;
    while((end_c = _rdtsc()) < temp_c) cpu_pause();
    //end_c = _rdtsc();
//    uint32_t etsc = read_tsc_lo() + latency_cycles;
//    while(read_tsc_lo() < etsc) cpu_pause();
    end_time = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(end_time - start_time).count();
    std::cout << end_c - start_c << std::endl;
    std::cout << duration << std::endl;

    std::cout << "hello, world" << std::endl;
}
