/* mychardev.c - Simple Character Device Driver */
#include <linux/module.h>
#include <linux/fs.h>
#include <linux/uaccess.h>

#define DEVICE_NAME "mychardev"
#define BUFFER_SIZE 1024

static char device_buffer[BUFFER_SIZE];
static int open_count = 0;
static int major_number;

// Open Function
static int mychardev_open(struct inode *inode, struct file *file) {
    open_count++;
    printk(KERN_INFO "mychardev: Device opened %d times\n", open_count);
    return 0;
}

// Read Function
static ssize_t mychardev_read(struct file *file, char __user *user_buffer, size_t len, loff_t *offset) {
    size_t bytes_read = simple_read_from_buffer(user_buffer, len, offset, device_buffer, BUFFER_SIZE);
    printk(KERN_INFO "mychardev: Read %zu bytes\n", bytes_read);
    return bytes_read;
}

// Write Function
static ssize_t mychardev_write(struct file *file, const char __user *user_buffer, size_t len, loff_t *offset) {
    size_t bytes_written = simple_write_to_buffer(device_buffer, BUFFER_SIZE, offset, user_buffer, len);
    printk(KERN_INFO "mychardev: Written %zu bytes\n", bytes_written);
    return bytes_written;
}

// Close Function
static int mychardev_release(struct inode *inode, struct file *file) {
    printk(KERN_INFO "mychardev: Device closed\n");
    return 0;
}

// File Operations
static struct file_operations fops = {
    .owner = THIS_MODULE,
    .open = mychardev_open,
    .read = mychardev_read,
    .write = mychardev_write,
    .release = mychardev_release,
};

// Module Initialization
static int __init mychardev_init(void) {
    major_number = register_chrdev(0, DEVICE_NAME, &fops);
    if (major_number < 0) {
        printk(KERN_ALERT "mychardev: Failed to register a major number\n");
        return major_number;
    }
    printk(KERN_INFO "mychardev: Registered with major number %d\n", major_number);
    return 0;
}

// Module Exit
static void __exit mychardev_exit(void) {
    unregister_chrdev(major_number, DEVICE_NAME);
    printk(KERN_INFO "mychardev: Unregistered device\n");
}

module_init(mychardev_init);
module_exit(mychardev_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Your Name");
MODULE_DESCRIPTION("Simple Character Device Driver");
MODULE_VERSION("1.0");
