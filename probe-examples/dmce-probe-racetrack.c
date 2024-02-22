#ifndef __DMCE_PROBE_FUNCTION_BODY__
#define __DMCE_PROBE_FUNCTION_BODY__

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

/* read the cpu timestamp counter */
static uint64_t dmce_rdtsc(void) {
#if defined(__x86_64__)
    unsigned int hi, lo;
    __asm__ __volatile__ ("rdtsc" : "=a"(lo), "=d"(hi) : : "memory");
    return (((uint64_t) hi) << 32) | ((uint64_t) lo);
#elif defined(__aarch64__)
    uint64_t val;
    __asm__ __volatile__ ("mrs %0, cntvct_e10" : "=r"(val) : :);
    return val;
#error
#else Architecture not supported
#endif
    }

/* spins t number timestamp counter ticks */
static void spin_tsc(uint64_t t) {
    uint64_t later = dmce_rdtsc() + t;
    while(dmce_rdtsc() < later);
}

static void dmce_probe_body(unsigned int probenbr, unsigned int delay) {
    (void) probenbr;
    spin_tsc(delay);
}
#endif
