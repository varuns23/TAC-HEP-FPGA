# Vitis/Vivado HLS Setup Guide (via RDP)

To use the Vitis/Vivado GUI efficiently, we connect using Remote Desktop Protocol (RDP). This is significantly faster and more stable than X11 forwarding.

## Configure SSH Tunneling to cmstrigger02 (via login node)
- Edit the SSH configuration file on your local machine (laptop/desktop), add the following:
```
Host *                                  
  ControlPath ~/.ssh/control/%C         
  ControlMaster auto  

Host cmstrigger02-via-login
    User <username>  
    HostName cmstrigger02.hep.wisc.edu
    ProxyCommand ssh login05.hep.wisc.edu nc %h %p

Host *.wisc.edu  
    User <username>
```
- If configured correctly, you will be prompted for your password (possibly twice) and logged into `cmstrigger02` using following command:
  - `ssh cmstrigger02-via-login`


## Setup Port Forwarding for RDP
  - From your local machine, run: 
     - `ssh -L 3389:127.0.0.1:3389 cmstrigger02-via-login`
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
  - **For Vitis HLS:**
    - `Source /opt/Xilinx/Vitis/2020.1/settings64.sh`
    - ``cd /scratch/`whoami` `` 
    - `vitis_hls`
  - **For Vivado HLS:** 
    - `Source /opt/Xilinx/Vivado/2020.1/settings64.sh`
    - ``cd /scratch/`whoami` `` 
    - `vivado_hls`
  
