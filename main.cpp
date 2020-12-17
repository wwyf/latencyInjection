#include <iostream>
#include <immintrin.h>
#include <x86intrin.h>
#include <emmintrin.h>
#include <chrono>



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

static inline uint64_t inject_cycle(uint64_t inject_cycle_num){
    uint64_t start_c, end_c;
    uint64_t temp_c;

    start_c = _rdtsc();
    temp_c = start_c + inject_cycle_num;
    while((end_c = _rdtsc()) < temp_c) cpu_pause();
    return end_c-start_c;
}

int main(){
    uint64_t cpu_freq_mhz = 2300;
    // int repeat_count = 1;
    int repeat_count = 10000;
    uint64_t inject_count = 500;
    uint64_t inject_latencys[500];
    uint64_t inject_cycles[500];
    for (int i = 0 ;i < inject_count; i++){
	inject_latencys[i] = i;
        inject_cycles[i] = inject_latencys[i]*cpu_freq_mhz/1000;
    }

    // for (int i = 0; i < inject_count; i++){
    //     {
    //         // inject_cycles[i]
    //         uint64_t cycles_sum = 0;
    //         for (int j = 0; j < repeat_count; j++){
    //             // volatile uint64_t start_c, end_c;
    //             // volatile uint64_t temp_c;
    //             uint64_t start_c, end_c;
    //             uint64_t temp_c;

    //             // inject here !!
    //             start_c = _rdtsc();
    //             temp_c = start_c + inject_cycles[i];
    //             while((end_c = _rdtsc()) < temp_c) _mm_pause();
    //             cycles_sum += end_c - start_c;
    //         }
    //         std::cout << inject_latencys[i] << "," << inject_cycles[i] << "," << cycles_sum/repeat_count << std::endl;
    //     }
    // }

    for (int i = 0; i < inject_count; i++){
        {
            // inject_cycles[i]
            uint64_t cycles_sum = 0;
            for (int j = 0; j < repeat_count; j++){
                // volatile uint64_t start_c, end_c;
                // volatile uint64_t temp_c;
                uint64_t start_c, end_c;
                uint64_t temp_c;

                // inject here !!
                start_c = _rdtsc();
                temp_c = start_c + inject_cycles[i];
                while((end_c = _rdtsc()) < temp_c) cpu_pause();
                cycles_sum += end_c - start_c;
            }
            std::cout << inject_latencys[i] << "," << inject_cycles[i] << "," << cycles_sum/repeat_count << std::endl;
        }
    }

    // for (int i = 0; i < inject_count; i++){
    //     {
    //         // inject_cycles[i]
    //         uint64_t cycles_sum = 0;
    //         for (int j = 0; j < repeat_count; j++){
    //             uint64_t start_c, end_c;
    //             uint64_t temp_c;

    //             // inject here !!
    //             start_c = read_tsc();
    //             temp_c = start_c + inject_cycles[i];
    //             while((end_c = read_tsc()) < temp_c) cpu_pause();
    //             cycles_sum += end_c - start_c;
    //         }
    //         std::cout << inject_latencys[i] << "," << inject_cycles[i] << "," << cycles_sum/repeat_count << std::endl;
    //     }
    // }

    // for (int i = 0; i < inject_count; i++){
    //     {
    //         // inject_cycles[i]
    //         uint64_t cycles_sum = 0;
    //         for (int j = 0; j < repeat_count; j++){
    //             // inject here !!
    //             // a little slower than before
    //             uint64_t actual_cycle_num = inject_cycle(inject_cycles[i]);
    //             cycles_sum += actual_cycle_num;
    //         }
    //         std::cout << inject_latencys[i] << "," << inject_cycles[i] << "," << cycles_sum/repeat_count << std::endl;
    //     }
    // }
}
