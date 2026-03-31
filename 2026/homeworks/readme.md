# Homeworks for TAC HEP FPGA module 2026

For all homework assignments, in addition to the required outputs, you must report at least the following:
- Resource utilization (e.g., LUTs, FFs, DSPs, BRAM)
- Timing estimates
 
Parameters to be used for all cases:
- Target device: `xcvu13p-fsga2577-2-e`
- Clock period: `25ns`

You can choose to use different parameters but do mention in your results if you have done so. 

## Homework # 1(lecture 4)

Q1. Develop C/C++ programs to implement the following operations:
  a. Vector addition 
  b. Vector multiplication
  c. Matrix addition 
  d. Matrix multiplication

You may use the templates provided in the lecture04 directory as a starting point. Use Vitis/Vivado HLS to perform `C Simulation (C-Sim)` and `C Synthesis (C-Synth)`. Use at least 10 elements for each of above case. 

For each of the four implementations:
- Finally, compare the results across all four categories and discuss your observations.


## Homework # 2 (lecture 6)
Q2. Develop a C/C++ program to sort an array of 16 elements. You may choose any sorting algorithm (e.g., bubble sort, selection sort, insertion sort, or merge sort or write your own sorter). Use Vitis/Vivado HLS to perform `C Simulation (C-Sim)` and `C Synthesis (C-Synth)` and report the results.


Q3. Develop multiple versions of a simple computation kernel (e.g., vector addition, multiplication)  between corresponding elements of two arrays of size > 10. Implement using 
  - standard c/c++ data types (int, long, long long)
  - Arbitrary data types: (ap_int<M>, ap_unit<M>, ap_fixed<M>)
  - Compare the resource utilization between standard and arbitrary data types and ap_int and ap_unit, how much it changes and justify the change. 


## Homework # 3 (lecture 7)

Q4. Use the programs developed in Q1 (vector multiplication and matrix multiplication) with input sizes of at least 10 elements (for vectors) and 6x6 matrices. Enhance your implementations by applying `HLS interface` pragmas and `array partitioning` pragmas.

Perform the following experiments:
- Apply appropriate HLS interface pragmas for input and output ports.
- For matrix multiplication, implement and compare the following array partitioning strategies:
   - Partition both dimensions
   - Partition only one dimension
(Optional for vectors) Apply array partitioning where relevant.
- a) Compare the results obtained from different partitioning strategies
- b) Discuss your observations, focusing on: Performance improvements,   Resource trade-offs, When full vs partial partitioning is beneficial


## Homework # 4 (lecture 8)

Q5. Design and optimize an HLS kernel that performs element-wise arithmetic operations on two input arrays and produces multiple outputs. Given two input arrays A[N] and B[N] (N ≥ 64), compute:
 - C[i] = A[i] + B[i]
 - D[i] = A[i] * B[i]
 - E[i] = (A[i] + B[i]) * (A[i] - B[i])
-  a) Implement a simple version using a single loop. Use standard arrays (no pragmas). Measure latency and resource utilization  after synthesis.
-  b) Apply HLS Interface Pragmas: How does interface selection impact throughput and memory access?
-  c) Apply loop pipelining (II=1): Report latency before and after pipelining
-  d) Compare: No partitioning,  Complete partitioning,  Cyclic/block partitioning, reshape



## Homework # 5 (lecture 9)
Q6. Explain the difference between Pragma Pipeline and Dataflow with example? 
Q7. How do you think Latency contraint affect scheduling?
Q8. Use the example hw5_ex1.cpp to evaluate the initial resource utilization and timing estimates. Then, progressively apply HLS pragmas to minimize resource usage while preserving performance. Use an effective combination of the following pragmas, ensuring that no conflicts are introduced: ARRAY_PARTITION, ARRAY_RESHAPE, PIPELINE, DATAFLOW, LATENCY, ALLOCATION, INLINE, and STABLE.
