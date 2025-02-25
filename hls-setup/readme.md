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




