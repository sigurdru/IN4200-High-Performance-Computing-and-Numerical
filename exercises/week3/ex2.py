import numpy as np

""" 
The loop in question:
double s = 0;
for (int i = 0; i<N; i++) 
    s = s + A[i]*B[i]
"""

# a) What is the expected performance for this loop kernel without data prefetching
""" 
Repeat this N/4 times:
    Repeat this 4 times:
        1: Load one cache line (100 cycles)
        2: Load data into cpu (1 cycles)
        3: Perform 2 FLOPS (2 cycles)
        4: Store data (1 cycles)
Total: 104*N Cycles
"""
# a) Assume the CPU is capable of prefetching, what is the required number of outstanding prefetches
# the CPU has to sustain in order to make this code bandwith-limited, instead of latency limited.
bandwith = 3.2*10**9 #[B/s]
double = 8 #[B]
num_double_per_sec = bandwith/double
# print(num_double_per_sec) 
# 4*10^8 doubles loaded per second
"""
Bandwith can deliver 4*10^8 floats per second. Since one bandwith can store 4 floats we need
more than 10^8 prefetches per second for the code to be bandwidth limited.
""" 
# c) How would this numer change if the cache line were twice or four times as long.
"""
Then we would need two or four times fewer prefetches respectively to make the code
bandwidth limited.
"""
# d)
""" 
If prefetching hides all latency we will need an initial 100 cycles to fetch the first data
then 3*N cycles to do all operations. That is approximatly 34 times faster if N is large. 
"""