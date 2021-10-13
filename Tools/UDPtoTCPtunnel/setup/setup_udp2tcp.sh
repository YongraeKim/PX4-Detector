#! /bin/bash

cd ..
printf "Change udp2tcp's user mod to 755\n"
sudo chmod 755 udp2tcp
printf "move udp2tcp to /usr/local/bin\n"
sudo cp udp2tcp /usr/local/bin
cd setup
sudo chmod 755 udp2tcp_service.service
sudo cp udp2tcp_service.service /etc/systemd/system/
systemctl daemon-reload
systemctl enable udp2tcp_service.service
systemctl start udp2tcp_service.service
