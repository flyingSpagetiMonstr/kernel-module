sudo rmmod dev_driver.ko

make clean
make


sudo insmod dev_driver.ko
sudo mknod /dev/dev_driver c 123 0

gcc writetest.c -o writetest
gcc test.c -o test
