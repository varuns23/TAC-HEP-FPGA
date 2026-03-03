# Instruction to setup Vitis/Vivado HLS

To use vitis GUI, we will be using Remote Desktop Protocol (RDP) which is faster than X11 forwarding. 

## Connect to login machine:
  - First connect to login machine: 
     - `ssh -L 3389:127.0.0.1:3389 <username>@login05.hep.wisc.edu`

## Remote Desktop Protocol client
- Use Micrsofts RDP client, its free app on MacOS and Windows and goes by the name `Windows App`
- **Setup:** Download `Windows App`, Open the app and click the + icon, then select `Add PC`
- **Configure:** Enter the IP address: `localhost` or `127.0.0.1:3389`
- **Connect:** Double-click the PC icon, enter your UW computing **<username>** and **<password>**, and click **Connect**

## Connect to cmstrigger02 machine via login
- After successful login, Open a `terminal`
- Connect to cmstrigger02:
  - `ssh -XY cmstrigger02`
  - ``mkdir /scratch/`whoami` ``
  - `` cd /scratch/`whoami` ``
  
## Set environment for Vivado/Vitis HLS
- Open terminal
  - **For Vitis HLS:**
    - `Source /opt/Xilinx/Vitis/2020.1/settings64.sh`
    - ``cd /scratch/`whoami` `` 
    - `vitis_hls`
  - **For Vivado HLS:** 
    - `Source /opt/Xilinx/Vivado/2020.1/settings64.sh`
    - ``cd /scratch/`whoami` `` 
    - `vivado_hls`
  
