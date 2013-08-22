clear
echo "Loading..."
insmod ringbuffor.ko
dmesg | tail -n 5
echo "Reading..."
cat /dev/ringbuffor
echo "Writing..."
echo 1234567890 > /dev/ringbuffor
dmesg | tail -n 5
echo "Reading..."
cat /dev/ringbuffor
echo
dmesg | tail -n 5
echo "Removing..."
rmmod ringbuffor
dmesg | tail -n 5
