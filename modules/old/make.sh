make clean 
rm -f ringbuffor.ko
rm ioctl_user
clear
gcc -Wall ioctl_user.c -o ioctl_user
make

