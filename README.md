# PX4 Simulation for OJT

This repo is generated on the job training for intership program.
As It's considered to execute PX4 SITL simulation with WSL1(Windows Subsystem for Linux1)
some posix code has been modified specially. And communication between PX4 SITL and GCS will be changed from UDP to TCP that it would be used for developing web based ground control system

# How to install this

Follow the instructions below.
This instruction is only valid in WSL1.

1. Clone this repository
>git clone https://github.com/YongraeKim/PX4-Swon.git --recursive

2. Change user authentication
>sudo usermod -a -G dialout $(whoami)
>> or sudo usermod -a -G dialout $USER

3. Change folder's authentication
>sudo chmod -r 777 PX4-Swon

4. Go to the folder as shown below
>cd PX4-Swon/Tools/setup

5. Start the script
>source wsl.sh

6. Move to the origin folder
>cd ~/PX4-Swon

7. build PX4 with
>make px4_sitl_default gazebo_iris
>>if this doesn't work,
>>>sudo make px4_sitl_default gazebo_iris
