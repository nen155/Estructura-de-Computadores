// rdtsc.h

#include <cstdint> // uint64_t
#if defined(__i386__)

static __inline__ unsigned long long rdtsc(void)
{
	unsigned long long int x;
	__asm__ volatile (".byte 0x0f, 0x31" : "=A" (x));
	return x;
}

#elif defined(__x86_64__)

static __inline__ unsigned long long rdtsc(void)
{
	unsigned hi, lo;
	__asm__ __volatile__ ("rdtsc" : "=a"(lo), "=d"(hi));
	return ( (unsigned long long)lo)|( ((unsigned long long)hi)<<32 );
}

#endif

//uint64_t rdtsc()
//{
//#ifdef __i386__
//	uint64_t x;
//	asm volatile
//	(
//		"cpuid     \n"
//		"rdtsc     \n"
//		: "=A" (x)
//		: "a" (0)
//		: "ebx", "ecx"
//	);
//	return x;
//#elif defined __X86_64__
//	uint64_t hi, lo;
//	asm volatile
//	(
//		"pusha     \n"
//		"cpuid     \n"
//		"rdtsc     \n"
//		"popa      \n"
//		: "=a" (lo), "=d" (hi)
//		: "a" (0)
//		: "ebx", "ecx"
//	);
//	return (hi << 32) | lo;
//#endif
//}

//static inline uint64_t rdtscp()
//{
//#ifdef __i386__
//	uint64_t x;
//	asm volatile ( "rdtscp\n" : "=A" (x) : : "ecx");
//	return x;
//#elif defined __X86_64__
//	uint64_t rax,rdx;
//	asm volatile ( "rdtscp\n" : "=a" (rax), "=d" (rdx) : : "rcx");
//	return (rdx << 32) + rax;
//#endif
//}

//static inline uint64_t rdtscp(uint32_t& aux)
//{
//#ifdef __i386__
//	uint64_t x;
//	asm volatile ( "rdtscp\n" : "=A" (x), "=c" (aux) : : "ecx");
//	return x;
//#elif defined __X86_64__
//	uint64_t rax,rdx;
//	asm volatile ( "rdtscp\n" : "=a" (rax), "=d" (rdx), "=c" (aux) : : "rcx");
//	return (rdx << 32) + rax;
//#endif
//}

