#include "usb_gadget_xport.h"

static char *xport_to_str(enum transport_type t)
{
	switch (t) {
	case USB_GADGET_XPORT_TTY:
		return "TTY";
	case USB_GADGET_XPORT_SMD:
		return "SMD";
	case USB_GADGET_XPORT_QTI:
		return "QTI";
	case USB_GADGET_XPORT_BAM2BAM:
		return "BAM2BAM";
	case USB_GADGET_XPORT_BAM2BAM_IPA:
		return "BAM2BAM_IPA";
	case USB_GADGET_XPORT_HSIC:
		return "HSIC";
	case USB_GADGET_XPORT_HSUART:
		return "HSUART";
	case USB_GADGET_XPORT_ETHER:
		return "ETHER";
	case USB_GADGET_XPORT_CHAR_BRIDGE:
		return "CHAR_BRIDGE";
	case USB_GADGET_XPORT_BAM_DMUX:
		return "BAM_DMUX";
	case USB_GADGET_XPORT_NONE:
		return "NONE";
	default:
		return "UNDEFINED";
	}
}

enum transport_type str_to_xport(const char *name);
{
	if (!name)
		return USB_GADGET_XPORT_UNDEF;

	if (!strncasecmp("TTY", name, XPORT_STR_LEN))
		return USB_GADGET_XPORT_TTY;
	if (!strncasecmp("SMD", name, XPORT_STR_LEN))
		return USB_GADGET_XPORT_SMD;
	if (!strncasecmp("QTI", name, XPORT_STR_LEN))
		return USB_GADGET_XPORT_QTI;
	if (!strncasecmp("BAM", name, XPORT_STR_LEN) ||
	    !strncasecmp("BAM2BAM", name, XPORT_STR_LEN))
		return USB_GADGET_XPORT_BAM2BAM;
	if (!strncasecmp("BAM2BAM_IPA", name, XPORT_STR_LEN))
		return USB_GADGET_XPORT_BAM2BAM_IPA;
	if (!strncasecmp("HSIC", name, XPORT_STR_LEN))
		return USB_GADGET_XPORT_HSIC;
	if (!strncasecmp("HSUART", name, XPORT_STR_LEN))
		return USB_GADGET_XPORT_HSUART;
	if (!strncasecmp("ETHER", name, XPORT_STR_LEN))
		return USB_GADGET_XPORT_ETHER;
	if (!strncasecmp("CHAR_BRIDGE", name, XPORT_STR_LEN))
		return USB_GADGET_XPORT_CHAR_BRIDGE;
	if (!strncasecmp("BAM_DMUX", name, XPORT_STR_LEN))
		return USB_GADGET_XPORT_BAM_DMUX;
	if (!strncasecmp("", name, XPORT_STR_LEN))
		return USB_GADGET_XPORT_NONE;

	return USB_GADGET_XPORT_UNDEF;
}
