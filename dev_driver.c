#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/fs.h>
#include <linux/uaccess.h>

#define BUFFER_SIZE 1024
#define MAJOR_SERIAL 123

static int open_count = 0;
static char message[BUFFER_SIZE];

static int dev_dr_open(struct inode *inode, struct file *file)
{
    open_count++;
    printk(KERN_INFO "dev_driver: device opened %d time(s)\n", open_count);
    return 0;
}

static ssize_t dev_dr_read(struct file *file, char __user *buf, size_t count, loff_t *offset)
{
    int bytes_to_read;
    if (count > BUFFER_SIZE)
        bytes_to_read = BUFFER_SIZE;
    else
        bytes_to_read = count;

    if (copy_to_user(buf, message, bytes_to_read))
        return -EFAULT;

    // int i;
    // printk("HERE!!!!!!!!!");
    // for(i = 0; i < bytes_to_read; i++)
    // {
    //     buf[i] = message[i];
    //     printk("THERE!!!!!!!!!");

    // }
    // buf[0]='$';

    return bytes_to_read;
}

// static ssize_t dev_dr_write(struct file *file, const char __user *buf, size_t count, loff_t *offset)
// {
//     int bytes_to_write;
//     if (count > BUFFER_SIZE)
//         bytes_to_write = BUFFER_SIZE;
//     else
//         bytes_to_write = count;

//     printk("out");
//     if (copy_from_user(message, buf, bytes_to_write))
//     {
//         printk("in");
//         return -EFAULT; // ################################################
//     }
//     printk("back");
//     printk("%s\n",message);
//     return bytes_to_write;
// }
static ssize_t dev_dr_write(struct file *filp, const char *buffer, size_t length, loff_t *offset)
{
    if (length > BUFFER_SIZE)
        length = BUFFER_SIZE;
    if (copy_from_user(message, buffer, length))
        return -EFAULT;
    // message_size = length;
    printk(KERN_INFO "Received message: %s\n", message);
    return length;
}

static int dev_dr_release(struct inode *inode, struct file *file)
{
    printk(KERN_INFO "dev_driver: device closed\n");
    return 0;
}

static struct file_operations dev_dr_fops = {
    .owner = THIS_MODULE,
    .open = dev_dr_open,
    .read = dev_dr_read,
    .write = dev_dr_write,
    .release = dev_dr_release,
};

static int __init dev_dr_init(void)
{
    printk(KERN_INFO "dev_driver: loading module\n");
    memset(message, 0, BUFFER_SIZE);
    strncpy(message, "Hello from dev_driver module\n", BUFFER_SIZE-1);

    // printk("BUSY  :%d\n",-EBUSY);
    // printk("EINVAL:%d\n",-EINVAL);
    // printk("ENOMEM:%d\n",-ENOMEM);

    return register_chrdev(MAJOR_SERIAL, "dev_driver", &dev_dr_fops);
}

static void __exit dev_dr_exit(void)
{
    printk(KERN_INFO "dev_driver: unloading module\n");
    unregister_chrdev(MAJOR_SERIAL, "dev_driver");
}

module_init(dev_dr_init);
module_exit(dev_dr_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("SGG");
MODULE_DESCRIPTION("A dev_driver kernel module");
