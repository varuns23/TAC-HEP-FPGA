# Instruction to setup Vitis/Vivado HLS

## Connect to cmstrigger02 machine via login machine:
  - First connect to login machine: 
     - `ssh -X -Y <username>@login.hep.wisc.edu`
  - Connect to cmstrigger02 machine now:
     - `ssh cmstrigger02`
     - ``mkdir /scratch/`whoami` ``
     - `` cd /scratch/`whoami` ``


## VNC Server Setup
- Log into `cmstrigger02` machine
- Set your VNC password using the linux command: `vncpasswd`
   - **Do NOT use an important password here**, as it is NOT secure 
   - Follow this instruction at http://red.ht/1fSVIUc to set up your X-Windows session
   - Namely, you need to create a file `~/.vnc/xstartup` with content
   ```
   #!/bin/sh
   # Uncomment the following two lines for normal desktop:
   # unset SESSION_MANAGER
   # exec /etc/X11/xinit/xinitrc 
   [ -x /etc/vnc/xstartup ] && exec /etc/vnc/xstartup 
   [ -r $HOME/.Xresources ] && xrdb $HOME/.Xresources 
   #xsetroot -solid grey 
   #vncconfig -iconic & 
   #xterm -geometry 80x24+10+10 -ls -title "$VNCDESKTOP Desktop" & 
   #twm & 
   if test -z "$DBUS_SESSION_BUS_ADDRESS" ; then 
        eval `dbus-launch --sh-syntax ?exit-with-session` 
        echo "D-BUS per-session daemon address is: \ 
        $DBUS_SESSION_BUS_ADDRESS" 
   fi 
   exec gnome-session
   
   ```
- You need to set execute permission for the startup file
   - `chmod +x ~/.vnc/xstartup`


## Setting direct tunneling
- Add to your (laptop or computer) `~/.ssh/config` file following lines:
```
Host *                                  
  ControlPath ~/.ssh/control/%C         
  ControlMaster auto  

Host cmstrigger02-via-login
    User <username>  
    HostName cmstrigger02.hep.wisc.edu
    ProxyCommand ssh login.hep.wisc.edu nc %h %p

Host *.wisc.edu  
    User <username>
```
- If all is done correctly, following command should directly take you to `cmstrigger02` machine (enter passwd twice)
  - `ssh cmstrigger02-via-login`


## IP Port forwarding

- Start the VNC server: do this command after you stopped `vncserver` by hand or otherwise, 
  - `vncserver -localhost -geometry 1024x768`
  - This command, `vncserver`, tells you the number of your X-Windows Display, 
    - Example `cmstrigger02.hep.wisc.edu:2`, where :2 is your display

- We use an IP forwarding tunnel to `cmstrigger02.hep.wisc.edu` to see your `cmstrigger02` display on your laptop/desktop. 
- The command to make that magic is:
  - `ssh varuns@cmstrigger02-via-login -L5902:localhost:5902` [In separate terminal tab]
  - Make sure you change ”varuns" to **your user name**, and **"5902" to (5900 + your display number)**, say 5903, if vncserver told you 3!

- You can kill your VNC server (:2) using the command:
  - `vncserver –kill :2`
- Check active servers (and kill unnecessary ones):
  - `vncserver –list` 


## Remote Desktop client
- Download VNC viewer: https://www.realvnc.com/en/connect/download/viewer/ 
- You can choose any other remote desktop client but this is one of the stable one that I have used


## Summary
- Execute: `ssh varuns@cmstrigger02-via-login -L5901:localhost:5901` 
  - Or whatever :1 display number
  - Sometimes you may need to run `vncserver -localhost -geometry 1024x768` again to start new vnc server
- Connect to VNC server (remote desktop) client
- Open terminal
  - For Vivado HLS: 
    - `Source /opt/Xilinx/Vivado/2020.1/settings64.sh`
    - `vivado_hls`
  - For Vitis HLS:
    - `Source /opt/Xilinx/Vitis/2020.1/settings64.sh`
    - `vitis_hls`
