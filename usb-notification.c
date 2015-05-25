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

/*Step -III Register and unregister with usb core*/

int init_module(void)
{
	printk(KERN_INFO "INIT USB simple subscriber \n");
/*Register with usb core to get notification on any addition or removal of usb devices*/
	usb_register_notify(&usb_simple_nb);
	return 0;
}
void cleanup_module(void)
{
	/*Remove the notifier*/
	usb_unregister_notify(&usb_simple_nb);
	printk(KERN_INFO "Remove USB simple subscriber \n");
}
MODULE_LICENSE ("GPL");


