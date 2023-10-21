# kernel-module

This is a project for my OS course at 2nd year.

Function: 
- load a simple kernel module(device driver) on linux.

The driver:
- open device
- read/write device

To run it:
- run.sh to make dev_driver.o and load kernel module. It will also commpile the 2 test codes so that you can run them to do some tests on device such as read/write.
- end.sh to uninstall module and clear message.
