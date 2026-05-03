# Real-time particle track reconstruction from simulated detector hits

The project aims to implement a real-time particle track reconstruction pipeline inspired by the CMS or ATLAS experiment or any other experiment involving tracker. I am assuming the tracker to be of CMS experiment. You are free to choose one of your favorite experiment but do describe some details of the tracker you have used like what it is made of, how may layer it has etc. The input to the project would consists of simulated detector hits generated from charged particles passing through multiple tracker layers in a magnetic field. Each hit contains spatial coordinates (x,y,z), detector layer information, timestamps, and optionally signal or particle metadata. The project is expected to process these raw hits in real time by first clustering nearby hits, then spatially and temporally sorting them, forming initial track seeds, and finally applying a Kalman filter–based tracking algorithm to estimate the trajectories and momenta of particles. The output of the system should be a list of reconstructed track candidates containing parameters such as transverse momentum (pT), trajectory direction (eta, phi), charge, number of associated hits, fit quality and timing information. 
The implementation should be designed with hardware acceleration in mind, making it suitable for FPGA or AMD Vitis HLS deployment using streaming and pipelined architectures for low-latency high-throughput processing.

Some of the steps could be:
1. Input raw hits from detector simulator (you can use input file provide one here or make one of yours based on tracker)
  - Input file "trackerInputs_events.csv" assumes detector have four tracker layers, Inputs are event number, hit information (x, y, z, time) for each layer. 
2. Cluster the hits, group together nearby hits, sorting 
3. Find the seed hit, initial track hypothesis
4. Finally use the Kalman-Filter to get the track parameters
5. Send the track parameters as output 
  - pT, eta, phi, charge, nhits, chi square,   


