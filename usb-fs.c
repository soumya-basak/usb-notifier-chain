#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/usb.h>
static int usb_notify_subscriber(struct notifier_block *self, unsigned long action, void *dev) /*the callback function, receive to the "struct notifier block,"object that was used when subscribing the notification framework, unsigned long= info about the framework, void pointer= struct usb_dev or usb_bus*/
{
	printk(KERN_INFO "usb_notify_subscriber \n");
	switch(action) {
	case USB_DEVICE_ADD :
		printk(KERN_INFO "usb_notify_subscriber:USB device added \n");
		break;
	case USB_DEVICE_REMOVE :
		printk(KERN_INFO "usb_notify_subscriber:USB device removed \n");
		break;
	case USB_BUS_ADD :
		printk(KERN_INFO "usb_notify_subscriber:USB bus added \n");
		break;
	case USB_BUS_REMOVE :
		printk(KERN_INFO "usb_notify_subscriber:USB bus removed \n");
		
}
return NOTIFY_OK;
}
/*Step -II declare a struct notifier_block type variable say usb_nb, Initialize "notifier_call" member variable of usb_nb with the handler function */

static struct notifier_block usb_simple_nb = {
.notifier_call = usb_notify_subscriber,
};

/*creating usbfs*/
static struct file_system_type usb_fs_type = {
	.owner =	THIS_MODULE,
	.name = 	"usbfs",
	.get_sb = 	usb_get_sb,
	.kill_sb =	kill_litter_super,
};

/*Step -III Register and unregister with usb core*/

int init_module(void)
{
	printk(KERN_INFO "INIT USB simple subscriber \n");
/*Register with usb core to get notification on any addition or removal of usb devices*/
	usb_register_notify(&usb_simple_nb);
	return 0;
}
/*Register usbfs*/
int__init usbfs_init(void)
{
	int retval;
	retval = register_filesystem(&usb_fs_type);
	if (retval)
	return retval;
}
/*two superblock callback function defined as part of the file system structure*/
/*Defining the 'usb_get_sb' handler function, which trigger the creation of the superblock with usbfs specific information*/
static int usb_get_sb(struct file_system_type *fs_type, int flags, const char *dev_name, void *data, struct vfsmount *mnt)
{
	return get_sb_single(fs_type, flag, data, usbfs_fill_supper, mnt);
}
/*struct superblock operation specific to the usbfs file system*/
static const struct super_operations usbfs_ops = {
	.statfs =	simple_statfs,
	.drop_inode =	generic_delete_inode,
	.remount_fs =	remount,
	.show_options =	usbfs_show_options,
};
/*usbfs's super block is assign with a magic number*/
#define USBDEVICE_SUPER_MAGIC 0x9fa2
static int usbfs_fill_super(struct super_block *sb, void *data, int silent)
{
	sb -> s_blocksize = PAGE_CACHE_SIZE;
	sb -> s_blocksize_bits = PAGE_CACHE_SHIFT;
	sb -> s_magic = USBDEVICE_SUPER_MAGIC;
	sb -> s_op =&usbfs_ops;
	sb -> s_time_gran = 1;
	inode = usbfs_get_inode(sb,S_IFDIR | 07555, 0)
	root = d_alloc_root(inode);
	sb -> s_root = root;
}
static int create_special_files (void)
{
	parent = usbfs_mount -> mnt_sb -> s_root;
	devices_usbfs_dentry = fs_create_file ("devices", listmode | S_FREG, parent, NULL, &usbfs_devices_fops, listuid, listgid);
}
const struct file_operations usbfs_devices_fops = {
	.llseek =	usb_device_lseek,
	.read =		usb_device_read,
	.poll = 	usb_device_poll,
};
}
void cleanup_module(void)
{
	/*Remove the notifier*/
	usb_unregister_notify(&usb_simple_nb);
	printk(KERN_INFO "Remove USB simple subscriber \n");
}
MODULE_LICENSE ("GPL");


