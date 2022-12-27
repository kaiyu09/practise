#!/bin/bash
ip_hostname="$(ifconfig | grep -B1 "10.42.0.2" | grep ":" | awk '{print $1}')"
my_hostname="$(echo $ip_hostname | cut -d ':' -f1)"
echo hostname = $my_hostname

eth_hostname="$(ifconfig | grep -B1 "10.110" | grep "e" |grep ":" | awk '{print $1}')"
my_eth_hostname="$(echo $eth_hostname | cut -d ':' -f1)"
echo eth_hostname = $my_eth_hostname

ip_info="$(ip addr show "$my_eth_hostname" | grep "inet\b"|awk '{print $2}')"
myip="$(echo $ip_info | cut -d '/' -f1)"
echo ip = $myip

for vlan_index in 1 2 3 4 5
do
    sudo ip link add link $my_hostname name eth1.${vlan_index}0 type vlan id ${vlan_index}0
    sudo ip addr add 172.20.${vlan_index}.31/24 brd 172.20.1.255 dev eth1.${vlan_index}0
    sudo ip link set dev eth1.${vlan_index}0 up
done
sudo sed -i 's/#net.ipv4.ip_forward=1/net.ipv4.ip_forward=1/g' /etc/sysctl.conf
sudo iptables -t nat -F

sudo iptables -t nat -A PREROUTING -d $myip -p tcp --dport 1001 -j  DNAT --to-destination 10.42.0.21:22
sudo iptables -t nat -A PREROUTING -d $myip -p tcp --dport 1002 -j  DNAT --to-destination 10.42.0.22:22
sudo iptables -t nat -A PREROUTING -d $myip -p tcp --dport 1003 -j  DNAT --to-destination 10.42.0.23:22
sudo iptables -t nat -A PREROUTING -d $myip -p tcp --dport 1004 -j  DNAT --to-destination 10.42.0.24:22
sudo iptables -t nat -A PREROUTING -d $myip -p tcp --dport 13400 -j  DNAT --to-destination 10.42.0.21:13400
sudo iptables -t nat -A PREROUTING -d $myip -p udp --dport 13400 -j  DNAT --to-destination 10.42.0.21:13400

sudo iptables -t nat -A POSTROUTING -p tcp --dport 22 -d 10.42.0.21 -j SNAT --to-source 10.42.0.2
sudo iptables -t nat -A POSTROUTING -p tcp --dport 22 -d 10.42.0.22 -j SNAT --to-source 10.42.0.2
sudo iptables -t nat -A POSTROUTING -p tcp --dport 22 -d 10.42.0.23 -j SNAT --to-source 10.42.0.2
sudo iptables -t nat -A POSTROUTING -p tcp --dport 22 -d 10.42.0.24 -j SNAT --to-source 10.42.0.2
sudo iptables -t nat -A POSTROUTING -p tcp --dport 13400 -d 10.42.0.21 -j SNAT --to-source 10.42.0.2
sudo iptables -t nat -A POSTROUTING -p udp --dport 13400 -d 10.42.0.21 -j SNAT --to-source 10.42.0.2

sudo iptables -t nat -A POSTROUTING -s 10.42.0.21 -j SNAT --to $myip
sudo iptables -t nat -A POSTROUTING -s 10.42.0.22 -j SNAT --to $myip
sudo iptables -t nat -A POSTROUTING -s 10.42.0.23 -j SNAT --to $myip
sudo iptables -t nat -A POSTROUTING -s 10.42.0.24 -j SNAT --to $myip

for soc_index in 1 2 3 4
do
  sudo iptables -t nat -A POSTROUTING -s 172.20.3.2${soc_index} -j SNAT --to $myip
  sudo iptables -t nat -A POSTROUTING -s 172.20.4.2${soc_index} -j SNAT --to $myip
done

sudo iptables -t nat -L -n -v
