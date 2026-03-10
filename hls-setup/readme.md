# Vitis/Vivado HLS Setup Guide (via RDP)

To use the Vitis/Vivado GUI efficiently, we connect using Remote Desktop Protocol (RDP). This is significantly faster and more stable than X11 forwarding.

## Setup Port Forwarding for RDP
  - From your local machine, run: 
     - ` ssh -L 3389:localhost:3389 -J <username>@login.hep.wisc.edu <username>@cmstrigger02.hep.wisc.edu`
   - Keep this terminal open - it maintains the RDP tunnel

## Connect Using Remote Desktop (RDP Client)
- Use Microsoft’s RDP client (called `Windows App `) available for macOS and Windows.
- **Setup:** Download & install the `Windows App`, Open the app and click the **+** icon, then select `Add PC`
- **Configure:** Enter the IP address: `localhost:3389` or `127.0.0.1:3389`
- **Connect:** Double-click the PC icon, enter your UW computing **<username>** and **<password>**, and click **Connect**
- You should now see the remote desktop of `cmstrigger02`
  
## Setup workign Directory
After logging in via RDP, open a terminal inside the remote desktop
- ``mkdir -p /scratch/`whoami` `` (if not there already)
- `` cd /scratch/`whoami` ``
  - **For Vitis HLS 2024.1:**
    - `Source /opt/Xilinx/Vitis/2024.1/settings64.sh`
    - ``cd /scratch/`whoami` `` 
    - `vitis_hls`
  - **For Vitis HLS 2022.1:**
    - `Source /opt/Xilinx/Vitis/2022.1/settings64.sh`
    - ``cd /scratch/`whoami` `` 
    - `vitis_hls`
  - **For Vitis HLS 2021.1:**
    - `Source /opt/Xilinx/Vitis/2021.1/settings64.sh`
    - ``cd /scratch/`whoami` `` 
    - `vitis_hls`
  - **For Vivado HLS:** 
    - `Source /opt/Xilinx/Vivado/2020.1/settings64.sh`
    - ``cd /scratch/`whoami` `` 
    - `vivado_hls`
  
