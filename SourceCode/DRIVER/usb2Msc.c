/* usb2Msc.c - USB Mass Storage Class Driver Core and USBD Interface Module */

/*
 * Copyright (c) 2008-2011 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

/*
modification history
--------------------
01n,18aug11,ghs  Release driver mutex when adding device fail (WIND00293692)
01m,12aug10,m_y  Init uConfigIndex in routine usb2MscDeviceAdd (WIND00223473)
01l,24may10,m_y  Add parameter valid check for usb robustness (WIND00183499 WIND00310775)
01k,05mar10,y_l  Remove too more hDriverMutex mutext protect (WIND00201277)
01j,18jan10,y_l  Change to dynamic timouts (WIND00190842)
01i,29oct09,ghs  Change default debug level(WIND00188349)
01h,21oct09,w_x  Modifications for Kernel API references (WIND00187268)
01g,17sep09,w_x  Avoid allocating endpoint status from stack (WIND00182242)
01f,27aug09,w_x  Unify log mechanism and variable naming with some compiler
                 warning removal in USB GEN2 class drivers (WIND00178936)
01e,17jun09,w_x  correct some error log with correct parameter (WIND00168950)
01d,14apr09,w_x  coding convention changes
01c,25feb09,w_x  call usb2MscDeviceUnmount with driver mutex taken
01b,19jan09,w_x  clean up for first check in
01a,29oct08,w_x  written
*/

/*
DESCRIPTION

This module is the USBD interface module of the USB Mass Storage Class
driver based on WRS USB 2.x API. This module works as a main/central point
of the whole USB Mass Storage Class driver.

The class driver is a client of the Universal Serial Bus Driver (USBD).
All interaction with the USB buses and devices is handled through the USBD.
The driver is designed to be of two architectural features:

Modular, each module is contained in one source file, and everything is
loosely coupled with each other; Implemented with object oriented constructs.

Layered, low level USB I/O is isolated from filesystem interface code; Use
command and data request information structures to do dispatch the transport
requests.

The chart below is a simplified architecture of the whole driver:

\cs
  |------------------------------------------------------------------|
  |                User Interface provided by                        |
  |                either filesystem or iosLib                       |
  |------|-----------------|-----------------|----------------|------|
         |                 |                 |                |
  |------|------|  |-------|-------|  |------|------|  |------|------|
  | XBD         |  | CBIO/BLK_DEV  |  |   Direct    |  |  Compliance |
  | based       |  | wrapper based |  |   Access    |  |    Test     |
  | filesystem  |  | filesystem    |  |   module    |  |   module    |
  | interface   |  | interface     |  |  (optional) |  |  (optional) |
  |------|------|  |-------|-------|  |------|------|  |--|-----||
         |                 |                 |            |     |
  |------|-----------------|-----------------|------------|-|   |
  |     Command Set Handling Module translating             |   |
  |     filesystem access and formating commands            |   |
  |---------------------------|-----------------------------|   |
                              |                                 |
  |---------------------------|---------------------------------|----|
  |           Transport Dispatch Layer (and Core)                    |
  | routing transport requests to specific transport handling module |
  |-----------------|------------------------------|---------------|-|
                    |                              |               |
  |-----------------|-----------|  |---------------|------------|  |P
  |  Bulk-Only Transport        |  | CB[I] Transport            |  |n
  |  module calling out to USBD |  | module calling out to USBD |  |P
  |-----------------|-----------|  |---------------|------------|  |
                    |                              |               |
  |-----------------|------------------------------|---------------|-|
  |                             USBD                                 |
  |   (along with Hub class driver Bus Manager to handle device PnP) |
  |------------------------------------------------------------------|
\ce

Both Bulk-Only transport and Control/Bulk/Interrupt (CBI) transport of
the USB Mass Storage Class specification are supported. For Bulk-Only
devices, transport of command, data and status occurs solely via bulk
endpoints. The default control pipe is only used to set configuration,
clear STALL condition on endpoints and to issue class-specific requests.
For CBI devices, transport of command, data and status occurs via control,
bulk and interrupt endpoints respectively. Interrupt endpoint is used to
signal command completion. This driver provides seperate transport handling
module that performs the command, data, and status transport with respect
to the protocol code reported by the device. This module works as a central
point in that it dispatches the transport requests from the command set
handling module (described below).

Although most USB storage devices use SCSI transparent command set, this
driver is designed to support almost all possible command sets that may be
reported by a device in the interface sublcass code. The driver provides
a seperate command set handling module to translate filesystem requrements
into native Command Descriptor Blocks (CDBs) of the command set in use. The
command set handling module, in turn, calls out to the central transport
routine to do the required command, data and status transport. This design
choice is to provide a way to support more device types that the old GEN1
storage class drivers didn't support natively. For example, USB CDROM
devices may be supported. However, as of this writing, support for USB
CDROM is not fully tested due to time limit (One flash based Autorun Disk
is mouted successfully as cdromFs). More command handling routines may need
to be added to support all the functionlity of USB CDROM devices. Normal
devices with PERIPHERAL DEVICE TYPE of 0 (USB2_MSC_SCSI_DEV_TYPE_DIRECT_ACCESS)
using SCSI transparent command set are fully tested. In short, this driver
provides an expandable way to allow new device types to be supported,
although it may need a bit expansion work.

This driver provides an expandable mechanism that can support various of
vxWorks filesystem interfaces across from 5.x to 6.x (including CBIO, XBD,
and BLK_DEV Wrapper). Customer can even easily add their own filesystem
interface module/layer. For vxWorks 5.x up through vxWorks 6.2, the
CBIO/BLK_DEV model is used; For vxWorks 6.3 and above, XBD mechannism
is used; To keep backward compability, there is an XBD BLK_DEV wrapper
that exposes similar interface as the CBIO/BLK_DEV model using XBD model.
This drivers provides seperate filesystem interface modules to work with
all of these filesystem interfaces. The CBIO/BLK_DEV model interface module
has very small differences with the XBD BLK_DEV wrapper model, so they exist
in the same module, with a complie time selection of which to support.
Basically, any filesystem interface module just needs to call out to the
command set handing module to translate the sector read/write requests into
CDBs of the command set supported by the device.

As a feedback for the old GEN1 mass storage class drivers, users may want
to send customized commands to the device, or perform any other operations
that can not be directly supported from the filesystem layer. For this purpose,
this driver provides a Direct Access module, which can be used to read/write
raw sector data, issue user supplied commands, and can be expanded for other
purposes. This also provides a customer feature innovation point. Please read
the Direct Access module reference entry for how to interact with it.

Device side compability is a big pain for all USB storage class drivers on
various operating systems, except the one that has the right to control or
guide device side behaviour. Everyone knows there is a USB mass storage class
specification that all devices should obey, but the problem is that not all
device manufacturers/integrators comform to the specification. They may only
test their devices under certain systems. These devices may violate the
specification in various ways, that a system like ours can not always know.
There is a USBCV compliance test program on USB-IF web site, which contains
an informational USB mass storage compability test module. This program is
intended to be used by all the devices to test to see if they meet the very
basic requirements that need to name the device as "compatible". But, again,
not all devices do the tests, and they may easily fail the tests (in various
of ways) if we do it. That program needs to be installed on Windows, so it
may not be always handy. To help the user of this driver to locate the possible
problem quickly, this driver provides a handy vxWorks version of the USB mass
storage class compliance test module. This module implements almost all the test
decriptions of the "USB Mass Storage Class - Compliance Test Specification",
and try to generate the same style of test output as the USBCV on USB-IF web
site. This compliance test module can be used to identify how the device
violates the specification just under vxWorks itself. However, this module
doesn't intend to be the replacement of the program on USB-IF, the specification
tend to change in time. It only serves as a handy way. Besides, some limits
are still in this module, in that it doesn't re-enumerate the bus when a device
fails a test item. Some device may stop responding to any commands after it
fails some commands, and will not turn to alive unless a re-enumeration happens.
For such devices, the test may stop at where the devices fails. This module is
mainly to be used for devices that use Bulk-Only transport, which is the same
as the USB-IF version.

This driver also provides a quirky device handling mechanism, by which some of
the spec-violation devices can have a workaround to work with vxWors. The
mechansim is based on device ID matching to handle quirky devices. Typically,
if a quirky device is found that may need some workaround, an quirky device
information entry can be filled in the user configuration module of this
driver (usrUsb2MscInit.c), specifying the VID/PID/REV range of the device,
along with any bitwise ORed flags that can describe the required workaround.
This driver has pre-defined several quirky flags in accordence with some user
feedbacks based on the old GEN1 USB storage class drivers. It is lucky (or
unlucky) that several dozens of testing devices currently owned by WRS don't
expose these behaviours. So right now the quirky device information array has
only one entry, which desribes one really quirky device, where it reports
VID/PID/REV all as zero. Luckily enough, that device can work with this driver
without any quirky flags. So that entry is just filled for demostration purpose.
Since the USB mass storage market will continue to grow, more and more devices
will come into market, and they may violate the various requirements enforced
from both the set of USB mass storage class specifications and the set of
possible command set specifications, it is totally out of WRS control. The
mission of this driver is to provide users with a tested software stack that
can work with all compatible devices, and try its best to work with devices
that are not fully compatible. For this reason, we value any customer report
about a "not working device", we will work closely to make that work under
vxWorks.

As an performance and user experience improvement to the old GEN1 USB mass
storage class drivers, this GEN2 mass storage class driver introduces a new
machanism for detecting medium presense. It is based on an obeservation of the
old GEN1 drivers which detects medium presense by testing medium ready every
time when any I/O is required, which may take some time slice that can be used
for meaningfull data transfers. Basically, XBD drivers will test/check everytime
a R/W (in the strategy routine) is issued to check if the medium is removed or
inserted; A test has shown that it may significantly reduce the USB storage
performance. The XBD media test mechanism also exhibits one situation (bad user
experience): if the medium is inserted/removed after the device is attached to
the system, it will only be mounted or unmounted when there is any IO activity
triggered by the user, such as an user issues "ls" from the shell (because if
there is no IO, then the driver has no way to report medium removal/insertion
event). The user will experience some delay before the files are listed or see
"Can't open..."; A new mechanism is introduced to do the medium presence check
by using "free bandwidth" of the XBD service task, which takes no data bandwidth.
When there is no BIO issued from filesystem, the semTake timeout, then we issue
a Test Unit Ready, if the medium is removed, the TUR will fail, and the auto
sense data will tell us the medium change event, and then we raise removal
event to unmount the medium (to be rawFs)... new medium insertion goes the same
way. In this approach, the medium presence check will not take time slice during
normal data R/W, it is just busy with its normal jobs. And if a medium removal
happens just during the data transfer, then the transfer will certainly fail as
expected. And an event will also be raised in next "free bandwidth" medium
hotplug check. With this new approach, the same performance as vxWorks 5.x is
achieved but doesn't lose any medium hotplug event, which is the valuable added
fucntionlity in 6.x XBD drivers (but with some perfomance penalty). Also, with
the new approch, the medium is mounted/unmounted on the fly (doesn't need any
user action to trigger any I/O to report the medium removal/insertion), the user
can experience the same behaviour as on some other popular operating systems.

INITIALIZATION

The class driver must be initialized with usb2MscDrvInit() with a string
passed in as the base name used for Direct Access module of the USB mass
storage class driver. It is assumed that USBD is already initialized and
attached to at least one USB Host Controller. usb2MscDrvInit() registers
the class driver as a client module with USBD. If direct access module is
enabled by the user, the usb2MscDrvInit() will try to initialize the direct
access module by calling usb2MscDirectAccessDeviceAdd(). It also registers
callback routines to get notified whenever a USB Mass storage device is
attached or removed from the system. The device add callback routine creates
a USB2_MSC_DEVICE structure to represent the USB device attached. It also
sets device configuration, interface settings and creates pipes for BULK IN
and BULK OUT transfers (if the device attached supports CBI transport protocol,
with command completion interrupt endpoint, then the INTERRUPT IN pipe will
be created). When the basic device information is retrived from the device,
the driver tries to call usrUsb2MscLookupQuirkyInfo() with the VID/PID/REV
combination of the device as parameters, which returns a pointer to a quirky
device entry, or NULL if the entry is not found. The device add routine will
then try to get the total number of Logical Units that can be supported by
the device, and creates seperate USB2_MSC_LUN_DEVICE structures for each of
the LUN, then, it tries to mount the LUN based on a user selected filesystem
interface module. The driver will try to add a device entry into the ios system
if Direct Access module is enabled by the user.

DATA STRUCTURES

usb2MscDeviceCreate() is the entry point to create a structure USB2_MSC_DEVICE
that represents the USB device attached. usb2MscLunDeviceCreate() is the entry
point to create a USB2_MSC_LUN_DEVICE structure that represents a logical unit
of the device. USB2_MSC_DEVICE has an array "hLunDevice[USB2_MSC_MAX_LUN]",
which is an array of pointers to all it's possible LUNs. The USB2_MSC_LUN_DEVICE
pointer created by usb2MscLunDeviceCreate() will be assigned to one of the array
element, based on which LUN it reprensents. USB2_MSC_LUN_DEVICE has an element
"pFileSystemHook", which stores a pointer to a filesystem interface dependant
data structure that reprensents this LUN in filesystem level aspects. For XBD
model based filesystem interface, the filesystem interface dependant structure
is USB2_MSC_XBD_LUN; For CBIO and BLK_DEV wrapper based filesystem interface,
the filesystem interface dependant structure is USB2_MSC_BLK_DEV_LUN; Based on
the user selection, the routine usb2MscDeviceMount() will call either
usb2MscXbdMount() or usb2MscBlkDevMount() for each of the LUN, which in turn
will create the USB2_MSC_XBD_LUN structure or USB2_MSC_BLK_DEV_LUN structure,
and mount the LUN block device. USB2_MSC_XBD_LUN or USB2_MSC_BLK_DEV_LUN both
maintain a pointer to USB2_MSC_LUN_DEVICE, to which they are associated. So,
we can easily locate any of these structures by lun number or by refelction. For
example, to locate a USB2_MSC_XBD_LUN of a LUN from USB2_MSC_DEVICE structure,
use USB2_MSC_DEVICE::hLunDevice[lun] and do a cast; To locate pointer to the
USB2_MSC_LUN_DEVICE from USB2_MSC_BLK_DEV_LUN, use the maintained pointer
USB2_MSC_BLK_DEV_LUN::pMscLunDevice directly; USB2_MSC_XBD_LUN has XBD element
as the first element, so it is easy to cast an XBD pointer to USB2_MSC_XBD_LUN
pointer, and vise versa; USB2_MSC_BLK_DEV_LUN has the same relationship with
its first element BLK_DEV.

MEMORY USAGE

All device specific memory is allocated at device attach time and dealloated
when device is dettached;

For each device attached, we will create a USB2_MSC_DEVICE to represent the
device; Each device will have a short workspace buffer (defined 64 bytes)
that can be used during transport of the commands, such as CBW and CSW for
Bulk-Only transport. The workspace will be used to store INTERRUPT IN status
data during status transport for CBI devices. Each endpoint of the device will
have a synchronization binary semaphore used for data transfer completion
notification and synchronization.

For each LUN in the device, we will create a USB2_MSC_LUN_DEVICE to represent
the logical unit. Each USB2_MSC_LUN_DEVICE will have a mutex to protect the lun
against concurent access; and each will have a command buffer, a short data
buffer, and a sense data buffer. The command buffer is used to store formated
CDBs; and the short data buffer can be used to do short data transfers internal
in the driver, such as SCSI INQUIRY response data; If any of the command
transport fails, an auto sense is performed, where the sense data buffer is
used to store the latest sense data reported by the LUN of the device.

The memory for USB2_MSC_DIRECT_ACCESS and USB2_MSC_COMPLIANCE is allocated when
the specific module is enabled and the device is added to that module. The Direct
Access module needs one USB2_MSC_DIRECT_ACCESS structure for one device; Each
USB2_MSC_DIRECT_ACCESS will need a short workspace to provide SCSI coomand pass
through, in which the workspace buffer is used to copy the user provided CDBs
to keep it DMA safe. The compliance test module needs one USB2_MSC_COMPLIANCE for
one device too, and it is only alloacted when the test is started by an ioctl()
call to the Direct Access module. Each USB2_MSC_COMPLIANCE will have
seperate workspace for CBW and CSW buffer, and two copies of 64KB big sector
buffers that can be used to perform the various test descriptions in the USB
mass storage compliance specification; One copy is used to do read tests, where
it can contain random values and do not care what it receives; Another copy is
used to save the first 64KB sector data from the device before the compliance
test is started, so it can be used for latter write tests, to not corrupt the
device sectors; This is an improvement to the USB-IF provided USBCV mass storage
test module, which may destroy the sector contents of the device under test.

TASK ENVIRONMENT

The usb2MscDeviceAdd() and corresponding usb2MscDeviceRemove() routines are
always called in the BusM task, which is the Bus Management task of the hub
class driver (although it is a class driver, it is part of USBD);

When mounting the device logical unit based on XBD filesystem interface, each
logical unit will get one XBD service task. In that service task, it waits for
bioReadySem binary semphore, which indicates some BIOs have been issued from
the filesystem, and it continues to perform the BIO requests by calling
usb2MscXbdGetNextBio() and  usb2MscXbdRunBio(); The mentioned medium hotplug
check is done in this service task, when the semTake for bioReadySem times out,
which indicates an idle time is reached.

When working with BLK_DEV wrapper based filesystem interface, the XBD BLK
wrapper (which is part of the filesystem component) will also spawn a service
task quite smimilar to the service task above, for each of the LUN it works for.

When triggered by the ioctl call in Direct Access module for a compliance test,
the driver will spawn a task for each of the LUN under test; The test task is
a run once task, when the tests are done, it will exit automatically.

DATA FLOW

For each USB MSC device detected, the device add callback routine creates
a USB2_MSC_DEVICE structure to represent the USB device attached. It also
sets device configuration, interface settings and creates pipes for BULK IN
and BULK OUT transfers (if the device attached supports CBI transport protocol,
with command completion interrupt endpoint, then the INTERRUPT IN pipe will
be created). The mounting routines will call routines in command set handling
module to format the device requests; In turnm the command set handling routines
will call usb2MscTransport() to dispatch the formated command and data requests
into transports for seperate command and data transfers. The specific tranport
modules, either Bulk-Only (also known as BBB) or CBI will do the low level
command and data transfers. For Bulk-Only transport, all commands are
encapsulated within a Command Block Wrapper (CBW) and transferred across the
BULK OUT endpoint; If the transport has data phase, the a data transfer phase
follows, either through BULK IN or BULK OUT endpoint, depending on the direction
bit in the CBW. After the data phase, the device shall send Command Status
Wrapper (CSW) via BULK IN endpoint. This will indicate the success or failure
of the CBW.  For CBI transport, the command pahse goes out through the default
control endpoint, by ADSC class specific requests. The data phase can be through
BULK IN or BULK OUT endpoint, also depending on wheter the command being
transported requires a DATA IN or DATA OUT; If the device implements an interrupt
endpint for command status reporting, then status transfer happens on the
INTERRUPT IN endpoint.

USER CALLBACKS

As a basic framework for all the GEN2 USB class drivers, we provide a way
to notify the user code by calling usb2AppAddCallback with a pointer to
USB2_CLASS_DEVICE structure, which is generated when device is attached:

\cs
    /@
     * If the status return code is not OK, then the device will not
     * be added to the driver; If the return code is OK, then the device
     * will continue to be added to the driver.
     @/
STATUS usb2AppAddCallback
    (
    USB2_CLASS_DEVICE * pClassDevice  /@ Pointer to class device @/
    );
\ce

As a customer feature request, user callback mechanism for medium change event
is now added to the driver. The user can override the default callback routine
usrUsb2MscDefaultMediumChangeCallback in the user coonfigure module of this
driver (usrUsb2MscInit.c) or use the Direct Access module ioctl code to
override the device with a customized callback. The callback is defined as :

\cs
   /@
    * The BOOL return value indicates if the driver
    * can continue handle medium hotplug events normally.
    @/

typedef BOOL (*USB2_MSC_MEDIUM_CHANGE_FUNCPTR)
    (
    UINT32 hDevice,          /@ Device handle for the device      @/
    UINT8  lun,              /@ LUN of the medium change          @/
    BOOL   mediumInsert      /@ Is this a medium insert or remove @/
    );
\ce

Note that the above medium change callback mechanism is currently only implented
in the XBD based filesystem interface module.

USER CONFIGURE OPTIONS

The user configuration module of this driver provides various of configurable
options that can be selected by users to during vxWorks system image generate
time. Some of these options are for naming mechanism which can be decided by
users, but normally you can just use the default naming convention provided
by WRS. Some of the options, provide vital functionlity differences which may
affect driver behaviour:

\is
\i USB2_MSC_FS_INTERFACE_NAME
A string parameter that can be set to "XBD" or "BLK_DEV", to select either
XBD based filesystem interface module or CBIO/BLK_DEV wrapper based filesystem
interface. "XBD" can be only used in vxWorks version newer than 6.3 (included);
"BLK_DEV" can be used in all versions of vxWorks, but it has some limitation in
that it can not handle medium hotplug in vxWorks 5.x or pre-6.3 systems (due to
filesystem limitations). In vxWorks 6.3 or above, "BLK_DEV" actually uses XBD
mechanism, the filesystem just prvides a wrapper around it. So to use "BLK_DEV"
option in post-6.3 systems, you need to add INCLUDE_XBD_BLK_DEV, along with
normal INCLUDE_XBD.

\i USB2_MSC_STATUS_CHECK_ENABLE
A boolean parameter that can be set to TRUE or FALSE; Only when this option is
TRUE, can the  two opinons below take effect. So this is a switch that enables
or disables the medium hotplug check and medium write protect status check.
This option defaults to be TRUE, which enables the status checks below.

\i USB2_MSC_MEDIUM_HOTPLUG_CHECK_ENABLE
A boolean parameter that can be set to TRUE or FALSE; Along with boolean option
value above, they control if the "free bandwidth" medium hotplug check is
enabled or disabled. Note that this option currently only apply to "XBD"
filesystem interface module. If USB2_MSC_STATUS_CHECK_ENABLE is set to TRUE, but
USB2_MSC_MEDIUM_HOTPLUG_CHECK_ENABLE set to FALSE, they driver will choose to
use the old medium presence check mechansim that was used in old GEN1 XBD
storage class drivers. The default vaule of USB2_MSC_MEDIUM_HOTPLUG_CHECK_ENABLE
is TRUE, with the default USB2_MSC_STATUS_CHECK_ENABLE as TRUE, enabling "free
bandwidth" medium hotplug check.

\i USB2_MSC_WRITE_PROTECTION_CHECK_ENABLE
A boolean parameter that can be set to TRUE or FALSE; If set to TRUE, the driver
will try to check if the medium is write protected or not, along with the medium
hotplug check; The write protection check is done by issuing Mode Sense command
to the devcie, and checking the WP bit of the Mode Sense response; However, this
is an optional comand according to the SPC specification, thus not all devices
implement this comand. The worst case is that one such a Mode Sense command is
received by the device, the device may behave very strange, even not responding
to any latter requests, until a reset or re-attach. So, we do not enable this
option by default. Luckily, most devices do not have medium write protection, so
we can be safe enough to use this optiom as FALSE. The fact is, even we do not
do the write protection check, and a true write protected medium is encountered,
it is considered also safe to issue write requests to the device, the write
should be failed by the device, without altering the medium content.

\i USB2_MSC_DIRECT_ACCESS_ENABLE
A Boolean parameter that can be set to TRUE or FALSE; If set to TRUE, when a
device is attached, the driver will add a device entry into the ios system; The
user then can use standard open(), read(), write(), ioctl() to access the device;
Raw sector access is provided by read() and write(), with one limitation that
the requested transfer size should be multiple of sector size, and after each
read() or write(), the internal offset is automatically adjusted. The offset
is reset to 0 when open is called, and can be set to a specified value by ioctl()
calls. The ioctl() can also be used to start or stop compliance test for the
device. Besides, SCSI command pass through is supported by this interface; This
is intended for users to exercise customized commands. Note that the Direct
Access module is always an expansion point, meaning that its functionality are
not limited by WRS, customers are encouraged to add new features. We are also
evaluating new functionality to be added.

\i USB2_MSC_COMPLIANCE_ENABLE
A boolean parameter that can be set to TRUE or FALSE; This enables the
informational USB mass storage compliance test module built into vxWorks
system. This is not intended to be a replacement of the USB-IF version of
USBCV, but just aims to be a fisrt time reference. When this module is enabled,
use the Direct Access ioctl() to start or stop the test.

\i USB2_MSC_COMPLIANCE_LOG_FILE_BASE_NAME
A string parameter that can be set to "stdout" or any other string, as the
name of compliance test log file. If the user fills "stdout" in configuration
facility, then we will map the file to stdout, thus the compliance test log
is output to stdout;  If the user fills other string, we will use the string
as a base to generate a random file name starting with that base; Then open
that file and use the FILE pointer in the compliance test module to output
test logs. This option is defaulted to be "stdout", so that users can see the
test output directly on a shell.
\ie

INCLUDE FILES: vxWorks.h usb2/usb2Msc.h usb2MscP.h
*/

/* includes */

#include <vxWorks.h>
#include <usb2/usb2Msc.h>
#include "usb2MscP.h"

/* defines */

/* typedefs */

/* globals */
/* 该信号量在usb2Msc.c文件中被使用，当插入U盘时会释放该信号量，用户层获取该信号量检测到U盘插入  */
#if 0
SEM_ID g_MscHaveMountedSemId = NULL;
#endif
MSG_Q_ID g_MscHaveMountedMsgID = NULL;

/*
 * Pointer to the Data used to register to
 * the USBD and some driver info
 */

USB2_CLASS_DRIVER *pUsb2MscDriver = NULL;

/* Use to enable/disable debug message */

UINT32  usb2MscDebug = USB2_CLASS_NONE_DEBUG;

/* locals */

/* forward declarations */

/*******************************************************************************
*
* usb2MscFixupAsciiString - fixup ASCII string
*
* This routine is to fixup the string which should be ASCII characters
* according to SCSI specifcation requirement, such as the SCSI INQUIRY
* response VID/PID/REV field.
*
* RETURNS: N/A
*
* ERRNO: N/A
*
* \NOMANUAL
*/

void usb2MscFixupAsciiString
(
    char   *string,
    int     length
)
{
    int index;

    /*
     * Start from last byte and forword, replace none
     * ASCII characters with space
     */

    for (index = length; index > 0; index--)
    {
        if ((string[index] == 0) ||
                (string[index] < 0x20) ||
                (string[index] > 0x7e))
            string[index] = ' ';
    }

    /* The last byte fixup to be terminator */

    string[length] = '\0';
}

/***************************************************************************
*
* usb2MscUrbCompleteCallback - callback called when a URB transfer is done
*
* This routine is called by the USB stack on when the URB is given back by
* stack. The semaphore is called to signal the completion of the URB.
*
* RETURNS: USBHST_SUCCESS
*
* ERRNO: N/A
*
* \NOMANUAL
*/

LOCAL USBHST_STATUS usb2MscUrbCompleteCallback
(
    pUSBHST_URB pUrb    /* Pointer to Urb Structure that has completed */
)
{
    SEM_ID syncSem;

    if ((NULL == pUrb) || (NULL == pUrb->pContext))
    {
        USB2_MSC_ERR("Invalid parameter\n", 1, 2, 3, 4, 5, 6);
        return USBHST_INVALID_PARAMETER;
    }

    syncSem = (SEM_ID) pUrb->pContext;

    semGive(syncSem);

    if (pUrb->nStatus != USBHST_SUCCESS)
    {
        USB2_MSC_ERR("URB returned with result %d\n",
                     (int)pUrb->nStatus, 2, 3, 4, 5, 6);
    }
    else
    {
        USB2_MSC_VDBG("URB returned with result %d\n",
                      (int)pUrb->nStatus, 2, 3, 4, 5, 6);
    }

    return USBHST_SUCCESS;
}

/*******************************************************************************
*
* usb2MscBulkTransfer - issue bulk transfer to mass storage device
*
* This routine is to issue bulk data transfer request to the USB mass storage
* device.
*
* RETURNS: USBHST_STATUS of the transfer result.
*
* ERRNO:
* \is
* \i EIO
* URB submition failed
* \ie
*
* \NOMANUAL
*/

USBHST_STATUS usb2MscBulkTransfer
(
    UINT32          hDevice,
    UINT8           bEpAddr,
    USBHST_URB     *pUrb,
    UINT32          transferFlags,
    SEM_ID          syncSem,
    UINT32          timeout,
    UCHAR          *pTransferBuffer,
    UINT32          requestLentgh,
    UINT32         *pActualLength
)
{
    USBHST_STATUS hstStatus;
    /* Set the transfered length as 0 */

    *pActualLength = 0;

    /* Fill the URB */

    USBHST_FILL_BULK_URB (pUrb,
                          hDevice,
                          bEpAddr,
                          pTransferBuffer,
                          requestLentgh,
                          transferFlags,
                          usb2MscUrbCompleteCallback,
                          (void *)syncSem,
                          USBHST_SUCCESS
                         );

    /* Submit it for transfer */

    if (usbHstURBSubmit(pUrb) != USBHST_SUCCESS)
    {
        USB2_MSC_ERR("Submit URB failed with status %d\n",
                     pUrb->nStatus, 2, 3, 4, 5, 6);

        errnoSet (EIO);

        /* Return with failure */

        return USBHST_FAILURE;
    }

    /* Reset the errno */

    errnoSet (OK);

    /*
     * Try to wait until the callback is called
     * to release syncSem and check if there is
     * any failure
     */

    if (semTake(syncSem, OS_CONVERT_MILLISECONDS_TO_WAIT_VALUE (timeout)) != OK)
    {
        USB2_MSC_ERR("syncSem ERROR for BULK EP %p\n",
                     bEpAddr, 2, 3, 4, 5, 6);

        /* As we timeout, cancel the URB */

        if (S_objLib_OBJ_TIMEOUT == errnoGet())
        {
            USB2_MSC_ERR("S_objLib_OBJ_TIMEOUT\n",
                         1, 2, 3, 4, 5, 6);

            hstStatus = usbHstURBCancel(pUrb);

            /* Now the stack may call the callback, wait for it */

            if (hstStatus == USBHST_SUCCESS)
                semTake (syncSem, OS_CONVERT_MILLISECONDS_TO_WAIT_VALUE (timeout));

            /* Return with timeout */

            return USBHST_TIMEOUT;
        }

        /* Return with failure */

        return USBHST_FAILURE;
    }

    USB2_MSC_VDBG("BULK EP %p done [%d bytes, status %d]\n",
                  bEpAddr, pUrb->uTransferLength, pUrb->nStatus, 4, 5, 6);

    /* Update the actual transfer length */

    *pActualLength = pUrb->uTransferLength;

    return pUrb->nStatus;
}

/*******************************************************************************
*
* usb2MscBulkOutTransfer - issue bulk out transfer to mass storage device
*
* This routine is to issue bulk out data transfer request to the USB mass
* storage device by calling the helper bulk transfer routine.
*
* RETURNS: USBHST_STATUS of the transfer result.
*
* ERRNO: N/A
*
* \NOMANUAL
*/

USBHST_STATUS usb2MscBulkOutTransfer
(
    USB2_MSC_DEVICE    *pMscDevice,
    UINT8              *pTransferBuffer,
    UINT32              uRequestedLentgh,
    UINT32             *pActualLength,
    int                 timeout
)
{
    /* Use the bulk out resources to issue transfer */

    return usb2MscBulkTransfer(pMscDevice->pClassDevice->hDevice,
                               pMscDevice->bBulkOutEndPointAddr,
                               &(pMscDevice->bulkOutUrb),
                               USBHST_SHORT_TRANSFER_OK,
                               pMscDevice->bulkOutSem,
                               timeout,
                               (UCHAR *)pTransferBuffer,
                               uRequestedLentgh,
                               pActualLength);
}

/*******************************************************************************
*
* usb2MscBulkInTransfer - issue bulk in transfer to mass storage device
*
* This routine is to issue bulk in data transfer request to the USB mass
* storage device by calling the helper bulk transfer routine.
*
* RETURNS: USBHST_STATUS of the transfer result.
*
* ERRNO: N/A
*
* \NOMANUAL
*/

USBHST_STATUS usb2MscBulkInTransfer
(
    USB2_MSC_DEVICE    *pMscDevice,
    UINT8              *pTransferBuffer,
    UINT32              uRequestedLentgh,
    UINT32             *pActualLength,
    int                 timeout
)
{
    /* Use the bulk in resources to issue transfer */

    return usb2MscBulkTransfer(pMscDevice->pClassDevice->hDevice,
                               pMscDevice->bBulkInEndPointAddr,
                               &(pMscDevice->bulkInUrb),
                               USBHST_SHORT_TRANSFER_OK,
                               pMscDevice->bulkInSem,
                               timeout,
                               (UCHAR *)pTransferBuffer,
                               uRequestedLentgh,
                               pActualLength);
}

/*******************************************************************************
*
* usb2MscInterruptInTransfer - issue interrupt transfer to mass storage device
*
* This routine is to issue interrupt in data transfer request to the USB mass
* storage device.
*
* RETURNS: USBHST_STATUS of the transfer result.
*
* ERRNO:
* \is
* \i EIO
* URB submition failed
* \ie
*
* \NOMANUAL
*/

USBHST_STATUS usb2MscInterruptInTransfer
(
    USB2_MSC_DEVICE    *pMscDevice,
    UINT8              *pTransferBuffer,
    UINT32              uRequestedLentgh,
    UINT32             *pActualLength,
    int                 timeout
)
{
    USBHST_STATUS hstStatus;
    USBHST_URB *pUrb = &(pMscDevice->intInUrb);

    /* Set the transfered length as 0 */

    *pActualLength = 0;

    /* Fill the URB */

    USBHST_FILL_INTERRUPT_URB ( pUrb,
                                pMscDevice->pClassDevice->hDevice,
                                pMscDevice->bIntInEndPointAddr,
                                pTransferBuffer,
                                uRequestedLentgh,
                                USBHST_SHORT_TRANSFER_OK,
                                usb2MscUrbCompleteCallback,
                                (void *)pMscDevice->intInSem,
                                USBHST_SUCCESS
                              );

    /* Submit it for transfer */

    if (usbHstURBSubmit(pUrb) != USBHST_SUCCESS)
    {
        USB2_MSC_ERR("Submit URB failed with status %d\n",
                     pUrb->nStatus, 2, 3, 4, 5, 6);

        errnoSet (EIO);

        /* Return with failure */

        return USBHST_FAILURE;
    }

    /* Reset the errno */

    errnoSet (OK);

    /*
     * Try to wait until the callback is called
     * to release syncSem and check if there is
     * any failure
     */

    if (semTake(pMscDevice->intInSem, OS_CONVERT_MILLISECONDS_TO_WAIT_VALUE (timeout)) != OK)
    {
        USB2_MSC_ERR("syncSem ERROR for INT EP %p\n",
                     pMscDevice->bIntInEndPointAddr, 2, 3, 4, 5, 6);

        /* As we timeout, cancel the URB */

        if (S_objLib_OBJ_TIMEOUT == errnoGet())
        {
            USB2_MSC_ERR("S_objLib_OBJ_TIMEOUT for intInSem\n",
                         1, 2, 3, 4, 5, 6);

            hstStatus = usbHstURBCancel(pUrb);

            /* Now the stack shall call the callback, wait for it */
            if (hstStatus == USBHST_SUCCESS)
                semTake (pMscDevice->intInSem,
                         OS_CONVERT_MILLISECONDS_TO_WAIT_VALUE (timeout));

            /* Return with timeout */

            return USBHST_TIMEOUT;
        }

        /* Return with failure */

        return USBHST_FAILURE;
    }

    USB2_MSC_VDBG("INT EP %p done [%d bytes, status %d]\n",
                  pMscDevice->bIntInEndPointAddr,
                  pUrb->uTransferLength,
                  pUrb->nStatus, 4, 5, 6);

    /* Update the actual transfer length */

    *pActualLength = pUrb->uTransferLength;

    return OK;
}

/*******************************************************************************
*
* usb2MscIsEndpointHalted - check endpoint halt status of mass storage device
*
* This routine is to issue get endpoint status request to the USB mass storage
* device and check if the endpoint is halted.
*
* RETURNS: TRUE if endpoint is halted, or FALSE if endpoint is not halted.
*
* ERRNO: N/A
*
* \NOMANUAL
*/

BOOL usb2MscIsEndpointHalted
(
    USB2_MSC_DEVICE    *pMscDevice,
    UINT8               bEndpointAddr
)
{
    USBHST_STATUS hstStatus;

    hstStatus = usbHstGetStatus(pMscDevice->pClassDevice->hDevice,
                                USBHST_RECIPIENT_ENDPOINT,
                                bEndpointAddr,
                                (UCHAR *)(&pMscDevice->endpointStatus));

    if (hstStatus == USBHST_SUCCESS)
    {
        return (pMscDevice->endpointStatus & 0x01) ? TRUE : FALSE;
    }
    else
        return TRUE;
}

/*******************************************************************************
*
* usb2MscResetEndpoint - reset an endpoint for mass storage device
*
* This routine is to issue clear endpoint halt feature request to the USB mass
* storage device.
*
* RETURNS: OK, or ERROR if there is any failure.
*
* ERRNO: N/A
*
* \NOMANUAL
*/

STATUS usb2MscResetEndpoint
(
    USB2_MSC_DEVICE    *pMscDevice,
    UINT8               bEndpointAddr
)
{
    USBHST_STATUS hstStatus;

    /* If it is halted, clear the endpoint halt feature */

    hstStatus = usbHstClearFeature(pMscDevice->pClassDevice->hDevice,
                                   USBHST_RECIPIENT_ENDPOINT,
                                   bEndpointAddr,
                                   USBHST_FEATURE_ENDPOINT_HALT);

    return (hstStatus == USBHST_SUCCESS) ? OK : ERROR;
}

/*******************************************************************************
*
* usb2MscResetDevice - issue device reset to mass storage device
*
* This routine is to issue device reset to mass storage device
*
* RETURNS: OK, or ERROR if there is any failure.
*
* ERRNO: N/A
*
* \NOMANUAL
*/

STATUS usb2MscResetDevice
(
    USB2_MSC_DEVICE    *pMscDevice
)
{
    USBHST_STATUS hstStatus;

    /* Reset the device port */

    hstStatus = usbHstResetDevice(pMscDevice->pClassDevice->hDevice);

    return (hstStatus == USBHST_SUCCESS) ? OK : ERROR;
}

/*******************************************************************************
*
* usb2MscGetTotalLun - get total number of logical units of mass storage device
*
* This routine is to get total number of logical units of mass storage
* device. For Bulk-Only device, it adds one to the result of the 'Get Max LUN'
* class specific request; For CB[I] devices, it always return 1.
*
* RETURNS: total number logical units, or 0xFF if there is any failure.
*
* ERRNO: N/A
*
* \NOMANUAL
*/

UINT8 usb2MscGetTotalLun
(
    USB2_MSC_DEVICE    *pMscDevice
)
{
    if (pMscDevice->protocolCode == USB2_MSC_PROTOCOL_BBB)
    {
        return usb2MscBulkOnlyGetMaxLun(pMscDevice);
    }
    else
    {
        return 1;
    }
}

/*******************************************************************************
*
* usb2MscTransport - perform transport protocol for mass storage device
*
* This routine is the single entry point to perform transport protocol of the
* USB mass storage device; The transport requirements are encapsulated in the
* 'pCmdInfo' and 'pDataInfo' infomation parameters;
*
* RETURNS: USB2_MSC_TRANSPORT_STATUS of the transport result.
*
* ERRNO:
* \is
* \i EINVAL
* Any parameter is invalid.
*
* \i EACCES
* Can not allow IO.
* \ie
*
* \NOMANUAL
*/

USB2_MSC_TRANSPORT_STATUS usb2MscTransport
(
    USB2_MSC_DEVICE                *pMscDevice,
    USB2_MSC_SCSI_COMMAND_INFO     *pCmdInfo,
    USB2_MSC_DATA_TRANSFER_INFO    *pDataInfo
)
{
    USB2_MSC_TRANSPORT_STATUS transportStatus;

    /* If we are not allowed to do IO, do not try more */

    if (!USB2_MSC_ALLOW_IO(pMscDevice))
    {
        USB2_MSC_ERR("Can not allow IO \n",
                     1, 2, 3, 4, 5, 6);

        errnoSet(EACCES);

        return USB2_MSC_TRANSPORT_ERROR;
    }

    /* Validity Check for command */

    if (!pCmdInfo ||
            !pCmdInfo->pCmdBuffer ||
            pCmdInfo->uCmdLen > USB2_MSC_CMDSET_MAX_CDB_SIZE)
    {
        USB2_MSC_ERR("Invalid cmd info \n",
                     1, 2, 3, 4, 5, 6);

        errnoSet(EINVAL);

        return USB2_MSC_TRANSPORT_ERROR;
    }

    /*
     * Validity Check for data info
     * if data info not NULL, then the buffer must be valid
     */

    if (pDataInfo &&
            (!pDataInfo->pDataBuffer))
    {
        USB2_MSC_ERR("Invalid cmd info \n",
                     1, 2, 3, 4, 5, 6);

        errnoSet(EINVAL);

        return USB2_MSC_TRANSPORT_ERROR;
    }

    /* Check if there is data transfer phase */

    if (pDataInfo)
    {
        /* Clear the actual bytes transfered */

        pDataInfo->uActualLength = 0;
    }

    /* Call out to the low level transport routine */

    switch (pMscDevice->protocolCode)
    {
    case USB2_MSC_PROTOCOL_BBB : /* Most often the case */

        USB2_MSC_VDBG("USB2_MSC_PROTOCOL_BBB\n",
                      1, 2, 3, 4, 5, 6);

        transportStatus = usb2MscBulkOnlyTransport(pMscDevice,
                          pCmdInfo, pDataInfo);

        break;
    case USB2_MSC_PROTOCOL_CBI : /* 2nd possible case */

        USB2_MSC_VDBG("USB2_MSC_PROTOCOL_CBI\n",
                      1, 2, 3, 4, 5, 6);

        transportStatus = usb2MscCBITransport(pMscDevice,
                                              pCmdInfo, pDataInfo);

        break;
    case USB2_MSC_PROTOCOL_CB :  /* Last possible case */

        USB2_MSC_VDBG("USB2_MSC_PROTOCOL_CB\n",
                      1, 2, 3, 4, 5, 6);

        transportStatus = usb2MscCBITransport(pMscDevice,
                                              pCmdInfo, pDataInfo);

        break;
    default:

        USB2_MSC_VDBG("Invalid protocol 0x%x\n",
                      pMscDevice->protocolCode, 2, 3, 4, 5, 6);

        errnoSet(EINVAL);

        transportStatus = USB2_MSC_TRANSPORT_ERROR;

        break;
    }

    return transportStatus;
}

/*******************************************************************************
*
* usb2MscLunDeviceDelete - delete logical unit structure of mass storage device
*
* This routine is to delete logical unit structure that represents the LUN of
* the USB mass storage device;
*
* RETURNS: OK, or ERROR if there is any failure.
*
* ERRNO: N/A
*
* \NOMANUAL
*/

LOCAL STATUS usb2MscLunDeviceDelete
(
    USB2_MSC_LUN_DEVICE    *pMscLunDevice
)
{
    if (!pMscLunDevice)
    {
        USB2_MSC_ERR("Lun device is NULL\n",
                     1, 2, 3, 4, 5, 6);
        return OK;
    }

    /* File system hook should be deleted before us */

    if (pMscLunDevice->pFileSystemHook)
    {
        USB2_MSC_ERR("File system hook still NOT NULL\n",
                     1, 2, 3, 4, 5, 6);
        return ERROR;
    }

    if (pMscLunDevice->lunMutex)
    {
        /* Mutex should be taken before delete */

        semTake(pMscLunDevice->lunMutex, WAIT_FOREVER);

        /* Delete the mutex */

        semDelete(pMscLunDevice->lunMutex);

        /* Set it to NULL */

        pMscLunDevice->lunMutex = NULL;
    }

    if (pMscLunDevice->pCmdBuffer)
    {
        /* Free the cmd buffer */

        OSS_FREE(pMscLunDevice->pCmdBuffer);

        /* Set the cmd buffer pointer to NULL */

        pMscLunDevice->pCmdBuffer = NULL;
    }

    if (pMscLunDevice->pDataBuffer)
    {
        /* Free the data buffer */

        OSS_FREE(pMscLunDevice->pDataBuffer);

        /* Set the data buffer pointer to NULL */

        pMscLunDevice->pDataBuffer = NULL;
    }

    if (pMscLunDevice->pSenseBuffer)
    {
        /* Free the sense buffer */

        OSS_FREE(pMscLunDevice->pSenseBuffer);

        /* Set the sense buffer pointer to NULL */

        pMscLunDevice->pSenseBuffer = NULL;
    }

    /* Free the LUN device */

    OSS_FREE(pMscLunDevice);

    return OK;
}

/*******************************************************************************
*
* usb2MscLunDeviceCreate - create logical unit structure of mass storage device
*
* This routine is to create logical unit structure that represents the LUN of
* the USB mass storage device;
*
* RETURNS: pointer to logical unit strcuture, or NULL if there is any failure.
*
* ERRNO: N/A
*
* \NOMANUAL
*/

LOCAL USB2_MSC_LUN_DEVICE *usb2MscLunDeviceCreate
(
    USB2_MSC_DEVICE        *pMscDevice,
    UINT8                   lun
)
{
    USB2_MSC_LUN_DEVICE    *pMscLunDevice;

    /* Try to allocate LUN device structure */

    pMscLunDevice = OSS_CALLOC(sizeof(USB2_MSC_LUN_DEVICE));

    if (!pMscLunDevice)
    {
        USB2_MSC_ERR("No memory for LUN %d\n",
                     lun, 2, 3, 4, 5, 6);

        /* Don't try more, just return NULL */

        return NULL;
    }

    /* Save the LUN device pointer */

    pMscDevice->hLunDevice[lun] = (UINT32)pMscLunDevice;

    /* Save our parent pointer */

    pMscLunDevice->pMscDevice = pMscDevice;

    /* Set the lun value */

    pMscLunDevice->lun = lun;

    /* Create the per LUN mutex */

    pMscLunDevice->lunMutex = semMCreate (SEM_Q_PRIORITY |
                                          SEM_INVERSION_SAFE | SEM_DELETE_SAFE);

    /* Check if the mutex created OK */

    if (pMscLunDevice->lunMutex == NULL)
    {
        USB2_MSC_ERR("Failed to create lun mutex for lun %d\n",
                     lun, 2, 3, 4, 5, 6);

        /* Delete the lun device structure */

        usb2MscLunDeviceDelete(pMscLunDevice);

        pMscDevice->hLunDevice[lun] = (ULONG)NULL;

        return NULL;
    }

    /* Allcaote the cmd buffer */

    pMscLunDevice->pCmdBuffer =
        OSS_CALLOC(USB2_MSC_MAX_LUN_CMD_BUFFER_LENGTH);

    if (!pMscLunDevice->pCmdBuffer)
    {
        USB2_MSC_ERR("Failed to allocate cmd buffer for lun %d\n",
                     lun, 2, 3, 4, 5, 6);

        /* Delete the lun device structure */

        usb2MscLunDeviceDelete(pMscLunDevice);

        /* Set the LUN device handle to NULL */

        pMscDevice->hLunDevice[lun] = (ULONG)NULL;

        return NULL;
    }

    /* Allocate the data buffer */

    pMscLunDevice->pDataBuffer =
        OSS_CALLOC(USB2_MSC_MAX_LUN_DATA_BUFFER_LENGTH);

    if (!pMscLunDevice->pDataBuffer)
    {
        USB2_MSC_ERR("Failed to allocate data buffer for lun %d\n",
                     lun, 2, 3, 4, 5, 6);

        /* Delete the lun device structure */

        usb2MscLunDeviceDelete(pMscLunDevice);

        /* Set the LUN device handle to NULL */

        pMscDevice->hLunDevice[lun] = (ULONG)NULL;

        return NULL;
    }

    pMscLunDevice->pSenseBuffer =
        OSS_CALLOC(USB2_MSC_SCSI_REQ_SENSE_ALLOC_LEN);
    if (!pMscLunDevice->pSenseBuffer)
    {
        USB2_MSC_ERR("Failed to allocate data buffer for lun %d\n",
                     lun, 2, 3, 4, 5, 6);

        /* Delete the lun device structure */

        usb2MscLunDeviceDelete(pMscLunDevice);

        /* Set the LUN device handle to NULL */

        pMscDevice->hLunDevice[lun] = (ULONG)NULL;

        return NULL;
    }

    /* Set the various timeout values */

    pMscLunDevice->readSectorTimeout = USB2_MSC_SCSI_READ_SECTOR_TIMEOUT;
    pMscLunDevice->writeSectorTimeout = USB2_MSC_SCSI_WRITE_SECTOR_TIMEOUT;
    pMscLunDevice->scsiCommandTimeout = USB2_MSC_SCSI_COMMAND_TIMEOUT;

    return pMscLunDevice;
}

/*******************************************************************************
*
* usb2MscDeviceMount - mount mass storage device
*
* This routine is to mount all the logical units of the USB mass storage device.
*
* RETURNS: OK, or ERROR if there is any failure.
*
* ERRNO: N/A
*
* \NOMANUAL
*/

LOCAL STATUS usb2MscDeviceMount
(
    USB2_MSC_DEVICE    *pMscDevice
)
{
    UINT8                   index;
    USB2_MSC_LUN_DEVICE    *pMscLunDevice;
    STATUS                  status;
    UINT8                   maxLun;

    maxLun = usb2MscGetTotalLun(pMscDevice);

    /* Check if the value is valid */

    if (maxLun == 0xFF)
    {
        USB2_MSC_ERR("Wrong max lun %d\n",
                     maxLun, 2, 3, 4, 5, 6);
    }

    USB2_MSC_VDBG("Device has %d LUN\n",
                  maxLun, 2, 3, 4, 5, 6);

    /* Save the max LUN */

    pMscDevice->maxLun = maxLun;


    /* Loop to mount each LUN */

    for (index = 0; index < pMscDevice->maxLun; index++)
    {
        /* Try to create LUN device structure */

        pMscLunDevice = usb2MscLunDeviceCreate(pMscDevice, index);
        if (pMscLunDevice)
        {
            USB2_MSC_VDBG("Try to mount LUN %d\n",
                          index, 2, 3, 4, 5, 6);

            /* Mount the LUN */

            if (usrUsb2MscFilesystemInterfaceGet() ==
                    USB2_MSC_FS_INTERFACE_XBD)
            {
                status = usb2MscXbdMount(pMscLunDevice);
            }
            else
            {
                status = usb2MscBlkDevMount(pMscLunDevice);
            }

            if (status != OK)
            {
                USB2_MSC_ERR("Failed to mount LUN %d\n",
                             index, 2, 3, 4, 5, 6);

                /* Delete lun device structure and try other lun */

                usb2MscLunDeviceDelete(pMscLunDevice);

                /* Clear the lun device handle */

                pMscDevice->hLunDevice[index] = (UINT32)NULL;
            }
        }
        else
        {
            USB2_MSC_ERR("No memory for LUN %d\n",
                         index, 2, 3, 4, 5, 6);

            /* Don't try more, just return failure */

            return ERROR;
        }
    }

    return OK;
}

/*******************************************************************************
*
* usb2MscDeviceUnmount - unmount mass storage device
*
* This routine is to unmount all logical units of the USB mass storage device.
*
* RETURNS: OK, or ERROR if there is any failure.
*
* ERRNO: N/A
*
* \NOMANUAL
*/

LOCAL STATUS usb2MscDeviceUnmount
(
    USB2_MSC_DEVICE        *pMscDevice
)
{
    UINT8                   index;
    STATUS                  status;
    USB2_MSC_LUN_DEVICE    *pMscLunDevice;

    /* Loop to mount each LUN */

    for (index = 0; index < pMscDevice->maxLun; index++)
    {
        /* Try to create LUN device structure */

        pMscLunDevice = (USB2_MSC_LUN_DEVICE *)pMscDevice->hLunDevice[index];

        if (!pMscLunDevice)
        {
            USB2_MSC_ERR("No memory for LUN %d\n",
                         index, 2, 3, 4, 5, 6);

            /* Don't try more, just return failure */

            return ERROR;
        }

        USB2_MSC_VDBG("Try to unmount LUN %d\n",
                      index, 2, 3, 4, 5, 6);

        /* Mount the LUN */

        if (usrUsb2MscFilesystemInterfaceGet() == USB2_MSC_FS_INTERFACE_XBD)
        {
            status = usb2MscXbdUnmount(pMscLunDevice);
        }
        else
        {
            status = usb2MscBlkDevUnmount(pMscLunDevice);
        }

        if (status != OK)
        {
            USB2_MSC_ERR("Failed to unmount LUN %d\n",
                         index, 2, 3, 4, 5, 6);
        }

        /* Delete lun device structure and try other lun */

        usb2MscLunDeviceDelete(pMscLunDevice);

        /* Clear the lun device handle */

        pMscDevice->hLunDevice[index] = (UINT32)NULL;
    }

    return OK;
}

/*******************************************************************************
*
* usb2MscDeviceDelete - delete mass storage device structure
*
* This routine is to delete the device strcuture that represets the USB mass
* storage device.
*
* RETURNS: OK, or ERROR if failed to delete the device structure.
*
* ERRNO: N/A
*
* \NOMANUAL
*/

LOCAL STATUS usb2MscDeviceDelete
(
    USB2_MSC_DEVICE    *pMscDevice
)
{
    /* Check if it is NULL */

    if (!pMscDevice)
    {
        USB2_MSC_ERR("Invalid parameter (NULL)\n",
                     1, 2, 3, 4, 5, 6);
        return ERROR;
    }

    /* Set the flag to stop any further IO during the deletion */

    pMscDevice->ioReady = FALSE;

    /* Free CBI workspace if allocated */

    if (pMscDevice->pWorkspace)
    {
        OSS_FREE(pMscDevice->pWorkspace);

        pMscDevice->pWorkspace = NULL;
    }

    /* Free extention point if allocated */

    if (pMscDevice->pFurtherExt)
    {
        OSS_FREE(pMscDevice->pFurtherExt);

        pMscDevice->pFurtherExt = NULL;
    }

    /* Delete Bulk In semaphore if created */

    if (pMscDevice->bulkInSem)
    {
        semDelete(pMscDevice->bulkInSem);

        pMscDevice->bulkInSem = NULL;
    }

    /* Delete Bulk Out semaphore if created */

    if (pMscDevice->bulkOutSem)
    {
        semDelete(pMscDevice->bulkOutSem);

        pMscDevice->bulkOutSem = NULL;
    }

    /* Delete Int In semaphore if created */

    if (pMscDevice->intInSem)
    {
        semDelete(pMscDevice->intInSem);

        pMscDevice->intInSem = NULL;
    }

    /* Delete class device structure */

    usb2ClassDeviceDelete(pMscDevice->pClassDevice);

    /* Free memory allcated */

    OSS_FREE(pMscDevice);

    USB2_MSC_DBG("All resources allocated are freed\n",
                 1, 2, 3, 4, 5, 6);

    return OK;
}

/*******************************************************************************
*
* usb2MscDeviceCreate - create mass storage device structure
*
* This routine is to create the device strcuture that represets the USB mass
* storage device.
*
* RETURNS: Pointer to the device structure, or NULL if creation failed.
*
* ERRNO: N/A
*
* \NOMANUAL
*/

LOCAL  USB2_MSC_DEVICE *usb2MscDeviceCreate
(
    UINT8 interfaceNum,
    UINT8 altSetting,
    UINT8 subClassCode,
    UINT8 protocol,
    UINT8 bulkInEpAddr,
    UINT8 bulkOutEpAddr,
    UINT8 intInEpAddr
)
{
    USB2_MSC_DEVICE *pMscDevice;

    /* Allocate the structure to handle this device */

    pMscDevice = OSS_CALLOC(sizeof(USB2_MSC_DEVICE));

    /* Check if we failed getting memory */

    if (pMscDevice == NULL)
    {
        USB2_MSC_ERR("No enough memory for USB2_MSC_DEVICE\n",
                     1, 2, 3, 4, 5, 6);

        return NULL;
    }

    USB2_MSC_VDBG("subclass %p protocol %p bulkin %p bulkout %p intin %p\n",
                  subClassCode,
                  protocol,
                  bulkInEpAddr,
                  bulkOutEpAddr,
                  intInEpAddr,
                  0);

    pMscDevice->bBulkInEndPointAddr = bulkInEpAddr;

    pMscDevice->bBulkOutEndPointAddr = bulkOutEpAddr;

    pMscDevice->bIntInEndPointAddr = intInEpAddr;

    /* Record interface info into driver device info */

    pMscDevice->interfaceNum = interfaceNum;
    pMscDevice->curAltSetting = altSetting;
    pMscDevice->subClassCode = subClassCode;
    pMscDevice->protocolCode = protocol;
    pMscDevice->ioReady = FALSE;
    pMscDevice->deviceRemoved = FALSE;
    pMscDevice->dynamicFlags = 0;
    pMscDevice->staticFlags = 0;
    pMscDevice->maxLun = 0;

    /* Watch out for devices that report invalid dCSWSignature */

    pMscDevice->dCSWSignatureCompare = USB2_MSC_CSW_SIGNATURE;
    pMscDevice->commandTimeout = usrUsb2MscCommandTimeoutGet(); /* MS */
    pMscDevice->resetTimeout = usrUsb2MscResetTimeoutGet(); /* MS */
    pMscDevice->statusTimeout = usrUsb2MscStatusTimeoutGet(); /* MS */
    pMscDevice->mediumChangeCallback =
        (FUNCPTR)usrUsb2MscDefaultMediumChangeCallback;

    /*
     * Check if we failed to find the required endpoint
     * All transports need Bulk In and Bulk Out, and
     * CBI Transport 3.4.3: *shall* support the interrupt endpoint
     */

    if ((pMscDevice->bBulkInEndPointAddr == 0) ||
            (pMscDevice->bBulkOutEndPointAddr == 0) ||
            ((pMscDevice->protocolCode == USB2_MSC_PROTOCOL_CBI) &&
             (pMscDevice->bIntInEndPointAddr == 0)))
    {
        USB2_MSC_ERR("No enough pipes found "\
                     "(epin 0x%x,epout 0x%x, epint 0x%x)\n",
                     pMscDevice->bBulkInEndPointAddr,
                     pMscDevice->bBulkOutEndPointAddr,
                     pMscDevice->bIntInEndPointAddr,
                     4, 5, 6);

        /* Delete the device structure */

        usb2MscDeviceDelete(pMscDevice);

        return NULL;
    }

    pMscDevice->pWorkspace = OSS_CALLOC(USB2_MSC_MAX_WORKSPACE_LENGTH);
    if (!pMscDevice->pWorkspace)
    {
        USB2_MSC_ERR("No enough memory for work space\n",
                     1, 2, 3, 4, 5, 6);

        /* Delete the device structure */

        usb2MscDeviceDelete(pMscDevice);

        return NULL;
    }

    if (pMscDevice->bBulkInEndPointAddr)
    {
        pMscDevice->bulkInSem = semBCreate(SEM_Q_FIFO, SEM_EMPTY);
        if (!pMscDevice->bulkInSem)
        {
            USB2_MSC_ERR("Can not create bulkInSem\n",
                         1, 2, 3, 4, 5, 6);

            /* Delete the device structure */

            usb2MscDeviceDelete(pMscDevice);

            return NULL;

        }
    }

    if (pMscDevice->bBulkOutEndPointAddr)
    {
        pMscDevice->bulkOutSem = semBCreate(SEM_Q_FIFO, SEM_EMPTY);
        if (!pMscDevice->bulkOutSem)
        {
            USB2_MSC_ERR("Can not create bulkOutSem\n",
                         1, 2, 3, 4, 5, 6);

            /* Delete the device structure */

            usb2MscDeviceDelete(pMscDevice);

            return NULL;
        }
    }

    if (pMscDevice->bIntInEndPointAddr)
    {
        pMscDevice->intInSem = semBCreate(SEM_Q_FIFO, SEM_EMPTY);
        if (!pMscDevice->intInSem)
        {
            USB2_MSC_ERR("Can not create intInSem\n",
                         1, 2, 3, 4, 5, 6);

            /* Delete the device structure */

            usb2MscDeviceDelete(pMscDevice);

            return NULL;
        }
    }

    return pMscDevice;
}

/*******************************************************************************
*
* usb2MscCheckOptimalInterface - check optimal interface of mass storage device
*
* This routine is to scan the array of alternate settings to find an optimal
* interface of mass storage device to work with.
*
* RETURNS: Pointer to the interface descriptor found, or NULL if failed to find.
*
* ERRNO: N/A
*
* \NOMANUAL
*/

USBHST_INTERFACE_DESCRIPTOR *usb2MscCheckOptimalInterface
(
    UINT32  pAltInterfaces[],       /* Array of alternate seetings */
    UINT8   uNumAltSettings         /* Array size */
)
{
    pUSBHST_INTERFACE_DESCRIPTOR    pInterfaceDesc = NULL;
    pUSBHST_INTERFACE_DESCRIPTOR    pOptimalInterfaceDesc = NULL;
    UINT8                           uAltCount = 0;

    /*
     * If there is no alternate setting (must be wrong somewhere),
     * we return NULL;
     */

    if (uNumAltSettings == 0) return NULL;

    /*
     * Scan through all alternate settings found with the same interface number
     */

    for (uAltCount = 0; uAltCount < uNumAltSettings; uAltCount++)
    {
        /* Get the alternate setting interface descr */

        pInterfaceDesc = (pUSBHST_INTERFACE_DESCRIPTOR)(pAltInterfaces[uAltCount]);

        /* If no interface pointer in this element, continue to next one */

        if (!pInterfaceDesc)
        {
            continue;
        }

        USB2_MSC_VDBG("Check Interface %d (%p %p %p) at %p\n",
                      pInterfaceDesc->bInterfaceNumber,
                      pInterfaceDesc->bInterfaceClass,
                      pInterfaceDesc->bInterfaceSubClass,
                      pInterfaceDesc->bInterfaceProtocol,
                      (int)pInterfaceDesc, 6);

        /* It must be of USB mass storage class */

        if (pInterfaceDesc->bInterfaceClass == USB2_MSC_CLASS_MASS_STORAGE)
        {
            /*
             * The subclass must indicates valid command set, or can be 0xFF
             * for reserved (some special device may use this)
             */

            if (((pInterfaceDesc->bInterfaceSubClass >= USB2_MSC_SUBCLASS_RBC) &&
                    (pInterfaceDesc->bInterfaceSubClass <= USB2_MSC_SUBCLASS_SCSI)) ||
                    (pInterfaceDesc->bInterfaceSubClass == USB2_MSC_SUBCLASS_RESERVED))
            {
                /* The transport protocol must be one of CBI/CB/BOT */

                if ((pInterfaceDesc->bInterfaceProtocol == USB2_MSC_PROTOCOL_CBI) ||
                        (pInterfaceDesc->bInterfaceProtocol == USB2_MSC_PROTOCOL_CB) ||
                        (pInterfaceDesc->bInterfaceProtocol == USB2_MSC_PROTOCOL_BBB))
                {
                    /*
                     * According to the USB mass storage spec, the Bulk Only
                     * transport is the recomended transport, we take it as the
                     * optimal transport;
                     *
                     * If we have not found an optimal alternate setting, or
                     * previous found alternate setting is not Bulk Only
                     */

                    if ((pOptimalInterfaceDesc == NULL) ||
                            (pOptimalInterfaceDesc->bInterfaceProtocol !=
                             USB2_MSC_PROTOCOL_BBB))
                    {
                        /* Save the optimal one to the pointer */

                        pOptimalInterfaceDesc = pInterfaceDesc;

                        USB2_MSC_VDBG("Found (%p %p %p) at %p\n",
                                      pOptimalInterfaceDesc->bInterfaceClass,
                                      pOptimalInterfaceDesc->bInterfaceSubClass,
                                      pOptimalInterfaceDesc->bInterfaceProtocol,
                                      (int)pOptimalInterfaceDesc, 5, 6);
                    }
                }
            }
        }
    }

    if (pOptimalInterfaceDesc)
    {
        USB2_MSC_VDBG("Finally found (%p %p %p) at %p\n",
                      pOptimalInterfaceDesc->bInterfaceClass,
                      pOptimalInterfaceDesc->bInterfaceSubClass,
                      pOptimalInterfaceDesc->bInterfaceProtocol,
                      (int)pOptimalInterfaceDesc, 5, 6);
    }

    return pOptimalInterfaceDesc;
}

/*******************************************************************************
*
* usb2MscFindOptimalInterface - find optimal interface of mass storage device
*
* This routine is to find optimal interface of mass storage device in the
* interface number passed in by 'uInterfaceNum'.
*
* RETURNS: Pointer to the interface descriptor found, or NULL if failed to find.
*
* ERRNO: N/A
*
* \NOMANUAL
*/

USBHST_INTERFACE_DESCRIPTOR *usb2MscFindOptimalInterface
(
    pUSBD_DEVICE_INFO   pDeviceInfo,    /* Device Information      */
    UINT16              uInterfaceNum   /* Interface number        */
)
{
    pUSBHST_DESCRIPTOR_HEADER       pHeader;
    pUSBHST_CONFIG_DESCRIPTOR       pCurConfigDescr;
    pUSBHST_INTERFACE_DESCRIPTOR    pInterfaceDesc;
    UINT8                          *pConfigBuffer;
    UINT16                          uTotalLength;
    UINT16                          uLength;
    UINT8                           uAltCount;
    UINT32                          altInterfaces[USB2_MAX_ALTSETTING];

    /* Get the current configuration buffer pointer */

    pConfigBuffer = pDeviceInfo->pCurrentConfiguration;

    /* Cast to configuration descr */

    pCurConfigDescr = (pUSBHST_CONFIG_DESCRIPTOR)
                      pDeviceInfo->pCurrentConfiguration;

    /* Get the total length of configuration with CPU endian conversion */

    uTotalLength = OS_UINT16_LE_TO_CPU(pCurConfigDescr->wTotalLength);

    /* Move the pointer to the interface */

    uLength = pCurConfigDescr->bLength;

    /* Reset the alternate setting count to 0 */

    uAltCount = 0;

    /* Clear the alternate setting array */

    OS_MEMSET(altInterfaces, 0, USB2_MAX_ALTSETTING * sizeof (UINT32));

    USB2_MSC_VDBG("Parse configuration buffer at %p.\n",
                  (int)pCurConfigDescr, 2, 3, 4, 5, 6);

    /*
     * This loop search the entire configuration descriptor for the
     * given interface number and the given alternate setting number
     */

    while (uLength <= uTotalLength)
    {
        /* Copy the descriptor header from the buffer */

        pHeader = (pUSBHST_DESCRIPTOR_HEADER)(pConfigBuffer + uLength);

        /*
         * This loop skips the descriptors until it finds the interface
         * descriptor
         */

        while (pHeader->uDescriptorType != USBHST_INTERFACE_DESC)
        {
            /* Move the pointer to read the next descriptor */

            uLength = uLength +  pHeader->uLength;

            /*
             * Check if whole interface descriptor buffer is read
             */

            if (uLength >= uTotalLength)
            {
                USB2_MSC_VDBG("Whole configuration buffer pasred.\n",
                              1, 2, 3, 4, 5, 6);

                break;
            }/* END if whole interface descriptor buffer is read...*/

            /* Copy the next descriptor header from the buffer */

            pHeader = (pUSBHST_DESCRIPTOR_HEADER)(pConfigBuffer + uLength);
        }

        /* Copy the interface info from the buffer */

        pInterfaceDesc = (pUSBHST_INTERFACE_DESCRIPTOR)(pHeader);

        /*
         *  If this interface's bInterfaceNumber is  uInterfaceNum
         */

        if (uInterfaceNum == pInterfaceDesc->bInterfaceNumber)
        {
            /* Save the pointers to the alternate interface settings */

            altInterfaces[uAltCount++] = (UINT32)pInterfaceDesc;

            USB2_MSC_VDBG("Interface %d (%p %p %p) at %p\n",
                          pInterfaceDesc->bInterfaceNumber,
                          pInterfaceDesc->bInterfaceClass,
                          pInterfaceDesc->bInterfaceSubClass,
                          pInterfaceDesc->bInterfaceProtocol,
                          (int)pInterfaceDesc, 6);
        }

        /* Skip the size of interface desc size */

        uLength = uLength + sizeof(USBHST_INTERFACE_DESCRIPTOR);

    } /*End of while loop*/

    USB2_MSC_VDBG("Found %d possible interfaces\n",
                  uAltCount, 2, 3, 4, 5, 6);

    /* Check for optimal interface among the alternate settings */

    return usb2MscCheckOptimalInterface(altInterfaces, uAltCount);
}


/*******************************************************************************
*
* usb2MscDeviceAdd - device add method of USBD interface
*
* This routine is called by the USBD each time a new USB mass storage device
* is attached to the system. This routine is responsible for identifying the
* device, configuring it and creating the device structure that enables use
* of the device. According to device characters and user configrations,
* appropiate device mount routine will be called.
*
* RETURNS: USBHST_SUCCESS, or USBHST_FAILURE if there is any failure.
*
* ERRNO: N/A
*
* \NOMANUAL
*/

LOCAL USBHST_STATUS usb2MscDeviceAdd
(
    UINT32      hDevice,
    UINT8       uInterfaceNum,
    UINT8       uSpeed,
    void      **ppDriverData
)
{
    STATUS                          status;
    USBHST_STATUS                   hstStatus;
    pUSBD_INTERFACE_INFO            pInterfaceInfo;
    pUSBD_DEVICE_INFO               pDeviceInfo;
    pUSBHST_CONFIG_DESCRIPTOR       pCurrentConfiguration;
    pUSBHST_INTERFACE_DESCRIPTOR    pInterfaceDesc;
    pUSBHST_ENDPOINT_DESCRIPTOR     pEndpointDesc;
    UINT8                           uConfigIndex;
    USB2_MSC_DEVICE                *pMscDevice;
    UINT8                           bulkInEpAddr = 0;
    UINT8                           bulkOutEpAddr = 0;
    UINT8                           intInEpAddr = 0;

    USB2_MSC_VDBG("MSC Driver is notified of a new " \
                  "Device %p, interface %p, speed %p...\n",
                  hDevice, uInterfaceNum, uSpeed, 4, 5, 6);

    /* Get the device information, for the descriptors */

    usbdTranslateDeviceHandle(hDevice, &pDeviceInfo);
    if (NULL == pDeviceInfo )
    {
        USB2_MSC_ERR("MSC device is apparently not connected anymore,"\
                     "the USBD pDeviceInfo is NULL\n",
                     1, 2, 3, 4, 5, 6);

        return USBHST_FAILURE;
    }

    /* Cast to configuration descr */

    pCurrentConfiguration = (pUSBHST_CONFIG_DESCRIPTOR)
                            pDeviceInfo->pCurrentConfiguration;

    /* Check if uInterfaceNum is valid */

    if (uInterfaceNum >= pCurrentConfiguration->bNumInterfaces)
    {
        USB2_MSC_ERR("uInterfaceNum >= bNumInterfaces\n",
                     uInterfaceNum,
                     pCurrentConfiguration->bNumInterfaces, 3, 4, 5, 6);

        return USBHST_FAILURE;
    }

    /* Get the interface info */

    pInterfaceInfo = &(pDeviceInfo->pInterfacesInfo[uInterfaceNum]);
    if (NULL == pInterfaceInfo )
    {
        USB2_MSC_ERR("ERROR : No Interface at index %d\n",
                     uInterfaceNum, 2, 3, 4, 5, 6);

        return USBHST_FAILURE;
    }

    /* Check if this is the expected interface of our device */

    if (pInterfaceInfo->uInterfaceClass != USB2_MSC_CLASS_MASS_STORAGE)
    {
        USB2_MSC_ERR("Interface %d (class %p) is not MSC class\n",
                     uInterfaceNum,
                     pInterfaceInfo->uInterfaceClass,
                     3, 4, 5, 6);

        return USBHST_FAILURE;
    }

    USB2_MSC_INFO("Storage driver got a device attach notification.\n",
                  1, 2, 3 , 4, 5, 6);


    /* Select the current configuration */

    if (usbHstSetConfiguration (hDevice,
                                pCurrentConfiguration->bConfigurationValue - 1) != USBHST_SUCCESS)
    {
        USB2_MSC_ERR("Failed to set configuration - device not added.\n",
                     1, 2, 3, 4, 5, 6);

        return USBHST_FAILURE;
    }

    uConfigIndex = pCurrentConfiguration->bConfigurationValue - 1;

    /*
     * USB MSC Bulk Only Spec "4.3 Interface Descriptors":
     *
     * The interface may have multiple alternate settings.
     * The host shall examine each of the alternate settings
     * to look for the bInterfaceProtocol and bInterfaceSubClass
     * it supports optimally.
     */

    pInterfaceDesc = usb2MscFindOptimalInterface(pDeviceInfo, uInterfaceNum);

    /* No optimal interface found */

    if (pInterfaceDesc == NULL)
    {
        USB2_MSC_ERR("Can not find an optimal interface %d\n",
                     uInterfaceNum, 2, 3, 4, 5, 6);

        return USBHST_FAILURE;
    }

    USB2_MSC_VDBG("Setting Interface %d altSetting %d (%p, %p, %p) at %p\n",
                  pInterfaceDesc->bInterfaceNumber,
                  pInterfaceDesc->bAlternateSetting,
                  pInterfaceDesc->bInterfaceClass,
                  pInterfaceDesc->bInterfaceSubClass,
                  pInterfaceDesc->bInterfaceProtocol,
                  (int)pInterfaceDesc);

    /* Select the optimal interface setting */

    if ((hstStatus = usbHstSetInterface(hDevice,
                                        pInterfaceDesc->bInterfaceNumber,
                                        pInterfaceDesc->bAlternateSetting))
            != USBHST_SUCCESS)
    {
        USB2_MSC_ERR("Failed to set interface - device not added \n",
                     1, 2, 3, 4, 5, 6);

        /*
         * If a device only supports a default setting for the
         * specified interface, then a STALL may be returned in
         * the Status stage of the request. And in this case we
         * should continue as this is a control pipe protocol STALL
         * and will be cleared automatically when the device
         * receives the next setup packet.
         */

        if (hstStatus != USBHST_STALL_ERROR)
            return USBHST_FAILURE;
    }

    /* Find first bulk in */

    pEndpointDesc = usb2FindEndpoint((UINT8 *)pInterfaceDesc,
                                     USB2_ATTR_BULK,
                                     USB2_ENDPOINT_IN,
                                     0,
                                     0,
                                     0);

    if (pEndpointDesc != NULL)
    {
        USB2_MSC_VDBG("BULK IN at 0x%x\n",
                      pEndpointDesc->bEndpointAddress, 2, 3, 4, 5, 6);

        bulkInEpAddr = pEndpointDesc->bEndpointAddress;
    }

    /* Find fisrt bulk out */

    pEndpointDesc = usb2FindEndpoint((UINT8 *)pInterfaceDesc,
                                     USB2_ATTR_BULK,
                                     USB2_ENDPOINT_OUT,
                                     0,
                                     0,
                                     0);

    if (pEndpointDesc != NULL)
    {
        USB2_MSC_VDBG("BULK OUT at 0x%x\n",
                      pEndpointDesc->bEndpointAddress, 2, 3, 4, 5, 6);

        bulkOutEpAddr = pEndpointDesc->bEndpointAddress;
    }

    /* Check interrupt endpoint only for CB[I] devices */

    if ((pInterfaceDesc->bInterfaceProtocol == USB2_MSC_PROTOCOL_CBI) ||
            (pInterfaceDesc->bInterfaceProtocol == USB2_MSC_PROTOCOL_CB))
    {
        /* Find first interrupt in */

        pEndpointDesc = usb2FindEndpoint((UINT8 *)pInterfaceDesc,
                                         USB2_ATTR_INTERRUPT,
                                         USB2_ENDPOINT_IN,
                                         0,
                                         0,
                                         0);

        if (pEndpointDesc != NULL)
        {
            USB2_MSC_DBG("INT IN at 0x%x\n",
                         pEndpointDesc->bEndpointAddress, 2, 3, 4, 5, 6);

            intInEpAddr = pEndpointDesc->bEndpointAddress;
        }
    }

    /* Try to create the device structure */

    pMscDevice = usb2MscDeviceCreate(pInterfaceDesc->bInterfaceNumber,
                                     pInterfaceDesc->bAlternateSetting,
                                     pInterfaceDesc->bInterfaceSubClass,
                                     pInterfaceDesc->bInterfaceProtocol,
                                     bulkInEpAddr,
                                     bulkOutEpAddr,
                                     intInEpAddr);

    /* Check if the device created OK */

    if (!pMscDevice)
    {
        USB2_MSC_ERR("Failed to create the MSC device structure\n",
                     1, 2, 3, 4, 5, 6);

        return USBHST_FAILURE;
    }

    /* Save the device speed */

    pMscDevice->uSpeed = uSpeed;

    /* Save the devie info */

    pMscDevice->pDeviceInfo = pDeviceInfo;

    /* Look up quirky device info */

    pMscDevice->pQuirky = (USB2_MSC_QUIRKY_INFO * )usrUsb2MscLookupQuirkyInfo(
                              pDeviceInfo->uVendorID,
                              pDeviceInfo->uDeviceID,
                              pDeviceInfo->uBCDDevice);

    /* If there is quirky info entry found, check it */

    if (pMscDevice->pQuirky)
    {
        pMscDevice->staticFlags = pMscDevice->pQuirky->flags;

        /* Check if the device needs to be ignored */

        if (pMscDevice->staticFlags & USB2_MSC_DEV_FLAG_IGNORE_DEVICE)
        {
            USB2_MSC_ERR("USB2_MSC_DEV_FLAG_IGNORE_DEVICE\n",
                         1, 2, 3, 4, 5, 6);

            /* Delete the device structure */

            usb2MscDeviceDelete(pMscDevice);

            return USBHST_FAILURE;
        }

        /* Check if we need to force subclass to be provided by user */

        if (pMscDevice->pQuirky->forceSubclass != USB2_MSC_SUBCLASS_RESERVED)
        {
            pMscDevice->subClassCode = pMscDevice->pQuirky->forceSubclass;
        }

        /* Check if we need to force protocol to be provided by user */

        if (pMscDevice->pQuirky->forceProtocol != USB2_MSC_PROTOCOL_RESERVED)
        {
            pMscDevice->protocolCode = pMscDevice->pQuirky->forceProtocol;
        }

        /* Check if we need to call the user provided setup routine */

        if (pMscDevice->pQuirky->setup != NULL)
        {
            pMscDevice->pQuirky->setup(hDevice, pMscDevice->pQuirky);
        }
    }

    /* Take the driver global mutex */

    status = usb2TakeDriver(pUsb2MscDriver);
    if (status != OK)
    {
        USB2_MSC_ERR("Driver mutex not taken\n",
                     1, 2, 3, 4, 5, 6);

        return USBHST_FAILURE;
    }

    /* Save the driver data to be used for device removal */

    *ppDriverData = pMscDevice;

    /* Create the class device structure */

    pMscDevice->pClassDevice = usb2ClassDeviceCreate(pUsb2MscDriver,
                               hDevice,
                               uConfigIndex,
                               pInterfaceDesc->bInterfaceNumber,
                               pInterfaceDesc->bAlternateSetting);
    if (!pMscDevice->pClassDevice)
    {
        USB2_MSC_ERR("Class device creation failed\n",
                     1, 2, 3, 4, 5, 6);

        /* Clear the driver data */

        *ppDriverData = NULL;

        /* Delete the device structure */

        usb2MscDeviceDelete(pMscDevice);

        /* Release the driver */

        usb2ReleaseDriver(pUsb2MscDriver);

        return USBHST_FAILURE;
    }

    /* Now set the flag to allow IO */

    pMscDevice->ioReady = TRUE;

    /* Check if there is enough name space remain usefull */

    if (usrUsb2MscReserveDevice(pMscDevice->pClassDevice->hDevice,
                                &pMscDevice->hUsrConfig)
            != OK)
    {
        USB2_MSC_ERR("Can not allow new device to be mounted\n",
                     1, 2, 3, 4, 5, 6);

        /* Delete the device structure */

        usb2MscDeviceDelete(pMscDevice);

        /* Release the driver */

        usb2ReleaseDriver(pUsb2MscDriver);

        return ERROR;
    }

    /* Release the driver */

    usb2ReleaseDriver(pUsb2MscDriver);

    USB2_MSC_VDBG("Try to mount the device \n",
                  1, 2, 3, 4, 5, 6);

    status = usb2MscDeviceMount(pMscDevice);

    if (status != OK)
    {
        USB2_MSC_ERR("Failed to mount the device \n",
                     1, 2, 3, 4, 5, 6);

        /* Delete the device structure */

        usb2MscDeviceDelete(pMscDevice);

        hstStatus = USBHST_FAILURE;
    }
    else
    {
        USB2_MSC_VDBG("Succeed to mount the device \n",
                      1, 2, 3, 4, 5, 6);

        hstStatus = USBHST_SUCCESS;
    }

    /* Check if user has enabled direct access module */

    if (usrUsb2MscDirectAccessEnabled() == TRUE)
    {
        /* Add the device to direct access module */

        usb2MscDirectAccessDeviceAdd(pMscDevice);
    }

#if 0
    if(USBHST_SUCCESS == hstStatus)
    {
        /* 释放信号量,检测到U盘插入并且设备状态正常  */
        semGive(g_MscHaveMountedSemId);
    }
#endif
    return hstStatus;
}

/*******************************************************************************
*
* usb2MscDeviceRemove - device remove method of USBD interface
*
* This routine is called by the USBD each time a device is removed from the
* system. This routine is responsible for ensuring all outstanding IO requests
* are completed or aborted and tearing down the I/O structure.
*
* RETURNS: N/A
*
* ERRNO: N/A
*
* \NOMANUAL
*/

LOCAL void usb2MscDeviceRemove
(
    UINT32  hDevice,
    void   *pDriverData
)
{
    USB2_MSC_DEVICE    *pMscDevice;
    STATUS              status;

    USB2_MSC_VDBG("MSC Driver is notified of a removal for " \
                  "Device %p, pDriverData %p\n",
                  hDevice, pDriverData, 3, 4, 5, 6);

    /* Validity check */

    pMscDevice = (USB2_MSC_DEVICE *) pDriverData;
    if (!pMscDevice)
    {
        return ;
    }

    USB2_MSC_INFO("Storage driver got a device remove notification.\n",
                  1, 2, 3 , 4, 5, 6);

    /* Take the driver global mutex */

    status = usb2TakeDriver(pUsb2MscDriver);
    if (status != OK)
    {
        USB2_MSC_ERR("Driver mutex not taken\n",
                     1, 2, 3, 4, 5, 6);
        return;
    }

    USB2_MSC_VDBG("Stop further IO\n",
                  1, 2, 3, 4, 5, 6);

    pMscDevice->ioReady = FALSE;
    pMscDevice->deviceRemoved = TRUE;

    /* Check if user has enabled direct access module */

    if (usrUsb2MscDirectAccessEnabled() == TRUE)
    {
        /* Remove the device from direct access module */

        usb2MscDirectAccessDeviceRemove(pMscDevice);
    }

    /* Try to release name space used */

    if (usrUsb2MscUnreserveDevice(pMscDevice->pClassDevice->hDevice)
            != OK)
    {
        USB2_MSC_WARN("This device is not in the reserved state! \n",
                      1, 2, 3, 4, 5, 6);

        /* Just continue */
    }

    /* Release the driver */

    usb2ReleaseDriver(pUsb2MscDriver);

    usb2MscDeviceUnmount(pMscDevice);

    usb2DeviceDeleteMsgPost(
        pMscDevice->pClassDevice,
        usb2MscDeviceDelete,
        pMscDevice
    );
}

/*******************************************************************************
*
* usb2MscDeviceSuspend - device suspend method of USBD interface
*
* This routine is called by the USBD to suspend the USB mass storage device.
* Right now there is nothing to do, so this routine simply returns.
*
* RETURNS: N/A
*
* ERRNO: N/A
*
* \NOMANUAL
*/

LOCAL void usb2MscDeviceSuspend
(
    UINT32  hDevice,
    void   *pDriverData
)
{

    USB2_MSC_VDBG("Suspend called Device - %d  Driver 0x%X\n",
                  hDevice, (int)pDriverData, 3, 4, 5, 6);

    return;
}

/*******************************************************************************
*
* usb2MscDeviceResume - device resume method of USBD interface
*
* This routine is called by the USBD to resume the USB mass storage device.
* Right now there is nothing to do, so this routine simply returns.
*
* RETURNS: N/A
*
* ERRNO: N/A
*
* \NOMANUAL
*/

LOCAL void usb2MscDeviceResume
(
    UINT32  hDevice,
    void   *pDriver
)
{

    USB2_MSC_VDBG("Resume called Device - %d  Driver 0x%X\n",
                  hDevice, (int)pDriver, 3, 4, 5, 6);

    return;
}

/*******************************************************************************
*
* usb2MscDrvInit - register the USB mass storage class driver with the USBD
*
* This routine is called to register the USB mass storage class driver with
* the USBD. It is supposed to be called by the user configuration code, with
* a pointer to a constant string as the base name for direct access module.
*
* RETURNS: OK, or ERROR if there is any failure.
*
* ERRNO: N/A
*/

STATUS usb2MscDrvInit
(
    char *pName
)
{
    USB2_MSC_VDBG("Initializing the printer Driver...\n",
                  1, 2, 3, 4, 5, 6);

    /* If already initialized, ignore and return. */

    if (NULL != pUsb2MscDriver)
    {
        USB2_MSC_DBG("Driver already here, return...\n",
                     1, 2, 3, 4, 5, 6);

        return OK;
    }

    /* If there is no name passed in, return as ERROR */

    if (!pName)
    {
        USB2_MSC_ERR("Please provide name parameter\n",
                     1, 2, 3, 4, 5, 6);
        return ERROR;
    }

    /* The caller should provide a non-NULL default name */

    pUsb2MscDriver = usb2ClassDriverCreate (pName);

    /* If the driver cannot be created, return with ERROR. */

    if (NULL == pUsb2MscDriver)
    {
        USB2_MSC_ERR("Driver cannot be created\n",
                     1, 2, 3, 4, 5, 6);
        return ERROR;
    }

    /* Check if user has enabled direct access module */

    if (usrUsb2MscDirectAccessEnabled())
    {
        /* Init direct access module */

        usb2MscDirectAccessInit();
    }

    /*
     * Initialize structure with driver specific data
     *
     * UINT16 deviceClass - USB class code
     * UINT16 deviceSubClass - USB sub-class code
     * UINT16 deviceProtocol - USB device protocol code
     * BOOL vendorSpecific - For vendor specific devicers
     *                    TRUE - if vendor specific driver
     *                    FALSE - if class specific driver
     */

    pUsb2MscDriver->hstDriver.bFlagVendorSpecific = FALSE;
    pUsb2MscDriver->hstDriver.uVendorIDorClass = USB2_MSC_CLASS_MASS_STORAGE;
    pUsb2MscDriver->hstDriver.uProductIDorSubClass = USBD_NOTIFY_ALL;
    pUsb2MscDriver->hstDriver.uBCDUSBorProtocol = USBD_NOTIFY_ALL;
    pUsb2MscDriver->hstDriver.addDevice = usb2MscDeviceAdd;
    pUsb2MscDriver->hstDriver.removeDevice = usb2MscDeviceRemove;
    pUsb2MscDriver->hstDriver.suspendDevice = usb2MscDeviceSuspend;
    pUsb2MscDriver->hstDriver.resumeDevice = usb2MscDeviceResume;

    /* Register the client with USBD */

    if (usbHstDriverRegister(&pUsb2MscDriver->hstDriver, NULL, "usb2Msc")
            != USBHST_SUCCESS)
    {
        USB2_MSC_ERR("usb2Msc Class driver registration failed\n",
                     1, 2, 3, 4, 5, 6);

        usb2ClassDriverDelete(pUsb2MscDriver);

        /* Check if user has enabled direct access module */

        if (usrUsb2MscDirectAccessEnabled())
        {
            /* UnInit direct access module */

            usb2MscDirectAccessUnInit();
        }

        return ERROR;
    }

    USB2_MSC_VDBG("usb2Msc Class driver registration succeeded\n",
                  1, 2, 3, 4, 5, 6);

#if 0
    /* 第一次插入U盘时创建信号量 */
    if(g_MscHaveMountedSemId == NULL)
    {
        /* 创建U盘检测信号量,信号量使用计数信号量这样可以使应用层多次获取  */
        g_MscHaveMountedSemId = semCCreate(SEM_Q_PRIORITY, SEM_EMPTY);
    }
#endif

    /* 创建消息 */
    g_MscHaveMountedMsgID = msgQCreate(100, 10, MSG_Q_FIFO);

    return OK;
}

/*******************************************************************************
*
* usb2MscDrvUnInit - deregister the USB mass storage class driver with the USBD
*
* This routine is called to deregister the USB mass storage class driver with
* the USBD. All USB mass storage instances must be removed from the system
* prior to calling this routine.
*
* RETURNS: OK, or ERROR if there is any failure.
*
* ERRNO: N/A
*/

STATUS usb2MscDrvUnInit (void)
{
    USBHST_STATUS   hstStatus;
    STATUS          status;
    BOOL            driverEmpty;

    status = usb2TakeDriver(pUsb2MscDriver);

    if (OK != status)
    {
        USB2_MSC_ERR("Driver mutex not taken\n", 1, 2, 3, 4, 5, 6);

        return ERROR;
    }

    /*
     * Unregister the driver with the USBD
     */

    hstStatus = usbHstDriverDeregister (&pUsb2MscDriver->hstDriver);

    if (hstStatus != USBHST_SUCCESS)
    {
        USB2_MSC_ERR("Unable to deregister USB MSC driver with USBD.\n",
                     1, 2, 3, 4, 5, 6);

        usb2ReleaseDriver(pUsb2MscDriver);

        return(ERROR);
    }

    /* Loop to wait until there is no one occupying the driver */

    driverEmpty = usb2DriverIsEmpty (pUsb2MscDriver);

    while (FALSE == driverEmpty)
    {
        USB2_MSC_VDBG("Wait driverEmpty\n", 1, 2, 3, 4, 5, 6);

        /* Release the driver to give other tasks a chance to clean up */

        usb2ReleaseDriver(pUsb2MscDriver);

        /* Give other task a chance to run */

        taskDelay(sysClkRateGet());

        /* Take the driver again */

        usb2TakeDriver(pUsb2MscDriver);

        /* Check the occupying status again */

        driverEmpty = usb2DriverIsEmpty (pUsb2MscDriver);
    }

    /* Now let's delete the driver */

    usb2ClassDriverDelete(pUsb2MscDriver);

    /* Set the driver pointer to NULL inidicating not initialized */

    pUsb2MscDriver = NULL;

    return (OK);
}

