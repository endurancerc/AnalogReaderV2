/*********************************************************************
 *
 *                Microchip USB C18 Firmware Version 1.0
 *
 *********************************************************************
 * FileName:        usb.h
 * Dependencies:    See INCLUDES section below
 * Processor:       PIC18
 * Compiler:        C18 2.30.01+
 * Company:         Microchip Technology, Inc.
 *
 * Software License Agreement
 *
 * The software supplied herewith by Microchip Technology Incorporated
 * (the 鼎ompany・ for its PICmicroｮ Microcontroller is intended and
 * supplied to you, the Company痴 customer, for use solely and
 * exclusively on Microchip PICmicro Microcontroller products. The
 * software is owned by the Company and/or its supplier, and is
 * protected under applicable copyright laws. All rights are reserved.
 * Any use in violation of the foregoing restrictions may subject the
 * user to criminal sanctions under applicable laws, as well as to
 * civil liability for the breach of the terms and conditions of this
 * license.
 *
 * THIS SOFTWARE IS PROVIDED IN AN 鄭S IS・CONDITION. NO WARRANTIES,
 * WHETHER EXPRESS, IMPLIED OR STATUTORY, INCLUDING, BUT NOT LIMITED
 * TO, IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A
 * PARTICULAR PURPOSE APPLY TO THIS SOFTWARE. THE COMPANY SHALL NOT,
 * IN ANY CIRCUMSTANCES, BE LIABLE FOR SPECIAL, INCIDENTAL OR
 * CONSEQUENTIAL DAMAGES, FOR ANY REASON WHATSOEVER.
 *
 * Author               Date        Comment
 *~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * Rawin Rojvanit       11/19/04    Original.
 ********************************************************************/

/*
 * usb.h provides a centralize way to include all files
 * required by Microchip USB Firmware.
 *
 * The order of inclusion is important.
 * Dependency conflicts are resolved by the correct ordering.
 */

//////////////////////////////////////////////////////////////////////////////
#include "device.h"


//////////////////////////////////////////////////////////////////////////////
//** D E F I N I T I O N S *******************************************/
//joined originally from usbcfg.h
#define EP0_BUFF_SIZE           8   // 8, 16, 32, or 64
#define MAX_NUM_INT             1   // For tracking Alternate Setting

/* Parameter definitions are defined in usbdrv.h */
#define MODE_PP                 _PPBM0
#define UCFG_VAL                _PUEN|_TRINT|_FS|MODE_PP

/* yts以下の機能は使用しないので、コメントアウトしました。
#define USE_SELF_POWER_SENSE_IO
#define USE_USB_BUS_SENSE_IO
*/

/** D E V I C E  C L A S S  U S A G E *******************************/
#define USB_USE_HID

/*
 * MUID = Microchip USB Class ID
 * Used to identify which of the USB classes owns the current
 * session of control transfer over EP0
 */
#define MUID_NULL               0
#define MUID_USB9               1
#define MUID_HID                2
#define MUID_CDC                3

/** E N D P O I N T S  A L L O C A T I O N **************************/
/*
 * See usbmmap.c for an explanation of how the endpoint allocation works
 */

/* HID */
#define HID_INTF_ID             0x00
#define HID_UEP                 UEP1
#define HID_BD_OUT              ep1Bo
#define HID_INT_OUT_EP_SIZE     8
#define HID_BD_IN               ep1Bi
#define HID_INT_IN_EP_SIZE      DEVICE_SENDDATA_SIZE
#define HID_NUM_OF_DSC          1
#define HID_RPT01_SIZE          DEVICE_DESCTABLE_SIZE

/* HID macros */
#define mUSBGetHIDDscAdr(ptr)               \
{                                           \
    if(usb_active_cfg == 1)                 \
        ptr = (rom byte*)&cfg01.hid_i00a00; \
}

#define mUSBGetHIDRptDscAdr(ptr)            \
{                                           \
    if(usb_active_cfg == 1)                 \
        ptr = (rom byte*)&hid_rpt01;        \
}

#define mUSBGetHIDRptDscSize(count)         \
{                                           \
    if(usb_active_cfg == 1)                 \
        count = sizeof(hid_rpt01);          \
}


#define MAX_EP_NUMBER           1           // UEP1


//////////////////////////////////////////////////////////////////////////////
//#include "system\usb\usbdefs\usbdefs_std_dsc.h"
/** D E F I N I T I O N S ****************************************************/

/* Descriptor Types */
#define DSC_DEV     0x01
#define DSC_CFG     0x02
#define DSC_STR     0x03
#define DSC_INTF    0x04
#define DSC_EP      0x05

/******************************************************************************
 * USB Endpoint Definitions
 * USB Standard EP Address Format: DIR:X:X:X:EP3:EP2:EP1:EP0
 * This is used in the descriptors. See autofiles\usbdsc.c
 * 
 * NOTE: Do not use these values for checking against USTAT.
 * To check against USTAT, use values defined in "system\usb\usbdrv\usbdrv.h"
 *****************************************************************************/
#define _EP01_OUT   0x01
#define _EP01_IN    0x81
#define _EP02_OUT   0x02
#define _EP02_IN    0x82
#define _EP03_OUT   0x03
#define _EP03_IN    0x83
#define _EP04_OUT   0x04
#define _EP04_IN    0x84
#define _EP05_OUT   0x05
#define _EP05_IN    0x85
#define _EP06_OUT   0x06
#define _EP06_IN    0x86
#define _EP07_OUT   0x07
#define _EP07_IN    0x87
#define _EP08_OUT   0x08
#define _EP08_IN    0x88
#define _EP09_OUT   0x09
#define _EP09_IN    0x89
#define _EP10_OUT   0x0A
#define _EP10_IN    0x8A
#define _EP11_OUT   0x0B
#define _EP11_IN    0x8B
#define _EP12_OUT   0x0C
#define _EP12_IN    0x8C
#define _EP13_OUT   0x0D
#define _EP13_IN    0x8D
#define _EP14_OUT   0x0E
#define _EP14_IN    0x8E
#define _EP15_OUT   0x0F
#define _EP15_IN    0x8F

/* Configuration Attributes */
#define _DEFAULT    0x01<<7         //Default Value (Bit 7 is set)
#define _SELF       0x01<<6         //Self-powered (Supports if set)
#define _RWU        0x01<<5         //Remote Wakeup (Supports if set)

/* Endpoint Transfer Type */
#define _CTRL       0x00            //Control Transfer
#define _ISO        0x01            //Isochronous Transfer
#define _BULK       0x02            //Bulk Transfer
#define _INT        0x03            //Interrupt Transfer

/* Isochronous Endpoint Synchronization Type */
#define _NS         0x00<<2         //No Synchronization
#define _AS         0x01<<2         //Asynchronous
#define _AD         0x02<<2         //Adaptive
#define _SY         0x03<<2         //Synchronous

/* Isochronous Endpoint Usage Type */
#define _DE         0x00<<4         //Data endpoint
#define _FE         0x01<<4         //Feedback endpoint
#define _IE         0x02<<4         //Implicit feedback Data endpoint


/** S T R U C T U R E ********************************************************/

/******************************************************************************
 * USB Device Descriptor Structure
 *****************************************************************************/
typedef struct _USB_DEV_DSC
{
    byte bLength;       byte bDscType;      word bcdUSB;
    byte bDevCls;       byte bDevSubCls;    byte bDevProtocol;
    byte bMaxPktSize0;  word idVendor;      word idProduct;
    word bcdDevice;     byte iMFR;          byte iProduct;
    byte iSerialNum;    byte bNumCfg;
} USB_DEV_DSC;

/******************************************************************************
 * USB Configuration Descriptor Structure
 *****************************************************************************/
typedef struct _USB_CFG_DSC
{
    byte bLength;       byte bDscType;      word wTotalLength;
    byte bNumIntf;      byte bCfgValue;     byte iCfg;
    byte bmAttributes;  byte bMaxPower;
} USB_CFG_DSC;

/******************************************************************************
 * USB Interface Descriptor Structure
 *****************************************************************************/
typedef struct _USB_INTF_DSC
{
    byte bLength;       byte bDscType;      byte bIntfNum;
    byte bAltSetting;   byte bNumEPs;       byte bIntfCls;
    byte bIntfSubCls;   byte bIntfProtocol; byte iIntf;
} USB_INTF_DSC;

/******************************************************************************
 * USB Endpoint Descriptor Structure
 *****************************************************************************/
typedef struct _USB_EP_DSC
{
    byte bLength;       byte bDscType;      byte bEPAdr;
    byte bmAttributes;  word wMaxPktSize;   byte bInterval;
} USB_EP_DSC;


//////////////////////////////////////////////////////////////////////////////
//#include "autofiles\usbdsc.h"
#if defined(USB_USE_HID)
#include "hid.h"
#endif

/** D E F I N I T I O N S *******************************************/
#define CFG01 rom struct            \
{   USB_CFG_DSC     cd01;           \
    USB_INTF_DSC    i00a00;         \
    USB_HID_DSC     hid_i00a00;     \
    USB_EP_DSC      ep01i_i00a00;   \
} cfg01

/** E X T E R N S ***************************************************/
extern rom USB_DEV_DSC device_dsc;
extern CFG01;
extern rom const unsigned char *rom USB_CD_Ptr[];
extern rom const unsigned char *rom USB_SD_Ptr[];

extern rom struct{byte report[HID_RPT01_SIZE];} hid_rpt01;
extern rom pFunc ClassReqHandler[1];


//////////////////////////////////////////////////////////////////////////////
//#include "system\usb\usbdefs\usbdefs_ep0_buff.h"
/******************************************************************************
 * CTRL_TRF_SETUP:
 *
 * Every setup packet has 8 bytes.
 * However, the buffer size has to equal the EP0_BUFF_SIZE value specified
 * in autofiles\usbcfg.h
 * The value of EP0_BUFF_SIZE can be 8, 16, 32, or 64.
 *
 * First 8 bytes are defined to be directly addressable to improve speed
 * and reduce code size.
 * Bytes beyond the 8th byte have to be accessed using indirect addressing.
 *****************************************************************************/
typedef union _CTRL_TRF_SETUP
{
    /** Array for indirect addressing ****************************************/
    struct
    {
        byte _byte[EP0_BUFF_SIZE];
    };
    
    /** Standard Device Requests *********************************************/
    struct
    {
        byte bmRequestType;
        byte bRequest;    
        word wValue;
        word wIndex;
        word wLength;
    };
    struct
    {
        unsigned :8;
        unsigned :8;
        WORD W_Value;
        WORD W_Index;
        WORD W_Length;
    };
    struct
    {
        unsigned Recipient:5;           //Device,Interface,Endpoint,Other
        unsigned RequestType:2;         //Standard,Class,Vendor,Reserved
        unsigned DataDir:1;             //Host-to-device,Device-to-host
        unsigned :8;
        byte bFeature;                  //DEVICE_REMOTE_WAKEUP,ENDPOINT_HALT
        unsigned :8;
        unsigned :8;
        unsigned :8;
        unsigned :8;
        unsigned :8;
    };
    struct
    {
        unsigned :8;
        unsigned :8;
        byte bDscIndex;                 //For Configuration and String DSC Only
        byte bDscType;                  //Device,Configuration,String
        word wLangID;                   //Language ID
        unsigned :8;
        unsigned :8;
    };
    struct
    {
        unsigned :8;
        unsigned :8;
        BYTE bDevADR;                   //Device Address 0-127
        byte bDevADRH;                  //Must equal zero
        unsigned :8;
        unsigned :8;
        unsigned :8;
        unsigned :8;
    };
    struct
    {
        unsigned :8;
        unsigned :8;
        byte bCfgValue;                 //Configuration Value 0-255
        byte bCfgRSD;                   //Must equal zero (Reserved)
        unsigned :8;
        unsigned :8;
        unsigned :8;
        unsigned :8;
    };
    struct
    {
        unsigned :8;
        unsigned :8;
        byte bAltID;                    //Alternate Setting Value 0-255
        byte bAltID_H;                  //Must equal zero
        byte bIntfID;                   //Interface Number Value 0-255
        byte bIntfID_H;                 //Must equal zero
        unsigned :8;
        unsigned :8;
    };
    struct
    {
        unsigned :8;
        unsigned :8;
        unsigned :8;
        unsigned :8;
        byte bEPID;                     //Endpoint ID (Number & Direction)
        byte bEPID_H;                   //Must equal zero
        unsigned :8;
        unsigned :8;
    };
    struct
    {
        unsigned :8;
        unsigned :8;
        unsigned :8;
        unsigned :8;
        unsigned EPNum:4;               //Endpoint Number 0-15
        unsigned :3;
        unsigned EPDir:1;               //Endpoint Direction: 0-OUT, 1-IN
        unsigned :8;
        unsigned :8;
        unsigned :8;
    };
    /** End: Standard Device Requests ****************************************/
    
} CTRL_TRF_SETUP;

/******************************************************************************
 * CTRL_TRF_DATA:
 *
 * Buffer size has to equal the EP0_BUFF_SIZE value specified
 * in autofiles\usbcfg.h
 * The value of EP0_BUFF_SIZE can be 8, 16, 32, or 64.
 *
 * First 8 bytes are defined to be directly addressable to improve speed
 * and reduce code size.
 * Bytes beyond the 8th byte have to be accessed using indirect addressing.
 *****************************************************************************/
typedef union _CTRL_TRF_DATA
{
    /** Array for indirect addressing ****************************************/
    struct
    {
        byte _byte[EP0_BUFF_SIZE];
    };
    
    /** First 8-byte direct addressing ***************************************/
    struct
    {
        byte _byte0;
        byte _byte1;
        byte _byte2;
        byte _byte3;
        byte _byte4;
        byte _byte5;
        byte _byte6;
        byte _byte7;
    };
    struct
    {
        word _word0;
        word _word1;
        word _word2;
        word _word3;
    };

} CTRL_TRF_DATA;


//////////////////////////////////////////////////////////////////////////////
//#include "system\usb\usbmmap.h"
/** D E F I N I T I O N S ****************************************************/

/* Buffer Descriptor Status Register Initialization Parameters */
#define _BSTALL     0x04                //Buffer Stall enable
#define _DTSEN      0x08                //Data Toggle Synch enable
#define _INCDIS     0x10                //Address increment disable
#define _KEN        0x20                //SIE keeps buff descriptors enable
#define _DAT0       0x00                //DATA0 packet expected next
#define _DAT1       0x40                //DATA1 packet expected next
#define _DTSMASK    0x40                //DTS Mask
#define _USIE       0x80                //SIE owns buffer
#define _UCPU       0x00                //CPU owns buffer

/* USB Device States - To be used with [byte usb_device_state] */
#define DETACHED_STATE          0
#define ATTACHED_STATE          1
#define POWERED_STATE           2
#define DEFAULT_STATE           3
#define ADR_PENDING_STATE       4
#define ADDRESS_STATE           5
#define CONFIGURED_STATE        6

/* Memory Types for Control Transfer - used in USB_DEVICE_STATUS */
#define _RAM 0
#define _ROM 1

/** T Y P E S ****************************************************************/
typedef union _USB_DEVICE_STATUS
{
    byte _byte;
    struct
    {
        unsigned RemoteWakeup:1;// [0]Disabled [1]Enabled: See usbdrv.c,usb9.c
        unsigned ctrl_trf_mem:1;// [0]RAM      [1]ROM
    };
} USB_DEVICE_STATUS;

typedef union _BD_STAT
{
    byte _byte;
    struct{
        unsigned BC8:1;
        unsigned BC9:1;
        unsigned BSTALL:1;              //Buffer Stall Enable
        unsigned DTSEN:1;               //Data Toggle Synch Enable
        unsigned INCDIS:1;              //Address Increment Disable
        unsigned KEN:1;                 //BD Keep Enable
        unsigned DTS:1;                 //Data Toggle Synch Value
        unsigned UOWN:1;                //USB Ownership
    };
    struct{
        unsigned BC8:1;
        unsigned BC9:1;
        unsigned PID0:1;
        unsigned PID1:1;
        unsigned PID2:1;
        unsigned PID3:1;
        unsigned :1;
        unsigned UOWN:1;
    };
    struct{
        unsigned :2;
        unsigned PID:4;                 //Packet Identifier
        unsigned :2;
    };
} BD_STAT;                              //Buffer Descriptor Status Register

typedef union _BDT
{
    struct
    {
        BD_STAT Stat;
        byte Cnt;
        byte ADRL;                      //Buffer Address Low
        byte ADRH;                      //Buffer Address High
    };
    struct
    {
        unsigned :8;
        unsigned :8;
        byte* ADR;                      //Buffer Address
    };
} BDT;                                  //Buffer Descriptor Table

/** E X T E R N S ************************************************************/
extern byte usb_device_state;
extern USB_DEVICE_STATUS usb_stat;
extern byte usb_active_cfg;
extern byte usb_alt_intf[MAX_NUM_INT];

extern volatile far BDT ep0Bo;          //Endpoint #0 BD Out
extern volatile far BDT ep0Bi;          //Endpoint #0 BD In
extern volatile far BDT ep1Bo;          //Endpoint #1 BD Out
extern volatile far BDT ep1Bi;          //Endpoint #1 BD In
extern volatile far BDT ep2Bo;          //Endpoint #2 BD Out
extern volatile far BDT ep2Bi;          //Endpoint #2 BD In
extern volatile far BDT ep3Bo;          //Endpoint #3 BD Out
extern volatile far BDT ep3Bi;          //Endpoint #3 BD In
extern volatile far BDT ep4Bo;          //Endpoint #4 BD Out
extern volatile far BDT ep4Bi;          //Endpoint #4 BD In
extern volatile far BDT ep5Bo;          //Endpoint #5 BD Out
extern volatile far BDT ep5Bi;          //Endpoint #5 BD In
extern volatile far BDT ep6Bo;          //Endpoint #6 BD Out
extern volatile far BDT ep6Bi;          //Endpoint #6 BD In
extern volatile far BDT ep7Bo;          //Endpoint #7 BD Out
extern volatile far BDT ep7Bi;          //Endpoint #7 BD In
extern volatile far BDT ep8Bo;          //Endpoint #8 BD Out
extern volatile far BDT ep8Bi;          //Endpoint #8 BD In
extern volatile far BDT ep9Bo;          //Endpoint #9 BD Out
extern volatile far BDT ep9Bi;          //Endpoint #9 BD In
extern volatile far BDT ep10Bo;         //Endpoint #10 BD Out
extern volatile far BDT ep10Bi;         //Endpoint #10 BD In
extern volatile far BDT ep11Bo;         //Endpoint #11 BD Out
extern volatile far BDT ep11Bi;         //Endpoint #11 BD In
extern volatile far BDT ep12Bo;         //Endpoint #12 BD Out
extern volatile far BDT ep12Bi;         //Endpoint #12 BD In
extern volatile far BDT ep13Bo;         //Endpoint #13 BD Out
extern volatile far BDT ep13Bi;         //Endpoint #13 BD In
extern volatile far BDT ep14Bo;         //Endpoint #14 BD Out
extern volatile far BDT ep14Bi;         //Endpoint #14 BD In
extern volatile far BDT ep15Bo;         //Endpoint #15 BD Out
extern volatile far BDT ep15Bi;         //Endpoint #15 BD In

extern volatile far CTRL_TRF_SETUP SetupPkt;
extern volatile far CTRL_TRF_DATA CtrlTrfData;

#if defined(USB_USE_HID)
extern volatile far unsigned char hid_report_out[HID_INT_OUT_EP_SIZE];
extern volatile far unsigned char hid_report_in[HID_INT_IN_EP_SIZE];
#endif


//////////////////////////////////////////////////////////////////////////////
//#include "system\usb\usbdrv\usbdrv.h"
/** D E F I N I T I O N S ****************************************************/

/* UCFG Initialization Parameters */
#define _PPBM0      0x00            // Pingpong Buffer Mode 0
#define _PPBM1      0x01            // Pingpong Buffer Mode 1
#define _PPBM2      0x02            // Pingpong Buffer Mode 2
#define _LS         0x00            // Use Low-Speed USB Mode
#define _FS         0x04            // Use Full-Speed USB Mode
#define _TRINT      0x00            // Use internal transceiver
#define _TREXT      0x08            // Use external transceiver
#define _PUEN       0x10            // Use internal pull-up resistor
#define _OEMON      0x40            // Use SIE output indicator
#define _UTEYE      0x80            // Use Eye-Pattern test

/* UEPn Initialization Parameters */
#define EP_CTRL     0x06            // Cfg Control pipe for this ep
#define EP_OUT      0x0C            // Cfg OUT only pipe for this ep
#define EP_IN       0x0A            // Cfg IN only pipe for this ep
#define EP_OUT_IN   0x0E            // Cfg both OUT & IN pipes for this ep
#define HSHK_EN     0x10            // Enable handshake packet
                                    // Handshake should be disable for isoch

/******************************************************************************
 * USB - PICmicro Endpoint Definitions
 * PICmicro EP Address Format: X:EP3:EP2:EP1:EP0:DIR:PPBI:X
 * This is used when checking the value read from USTAT
 *
 * NOTE: These definitions are not used in the descriptors.
 * EP addresses used in the descriptors have different format and
 * are defined in: "system\usb\usbdefs\usbdefs_std_dsc.h"
 *****************************************************************************/
#define OUT         0
#define IN          1

#define PIC_EP_NUM_MASK 0b01111000
#define PIC_EP_DIR_MASK 0b00000100

#define EP00_OUT    ((0x00<<3)|(OUT<<2))
#define EP00_IN     ((0x00<<3)|(IN<<2))
#define EP01_OUT    ((0x01<<3)|(OUT<<2))
#define EP01_IN     ((0x01<<3)|(IN<<2))
#define EP02_OUT    ((0x02<<3)|(OUT<<2))
#define EP02_IN     ((0x02<<3)|(IN<<2))
#define EP03_OUT    ((0x03<<3)|(OUT<<2))
#define EP03_IN     ((0x03<<3)|(IN<<2))
#define EP04_OUT    ((0x04<<3)|(OUT<<2))
#define EP04_IN     ((0x04<<3)|(IN<<2))
#define EP05_OUT    ((0x05<<3)|(OUT<<2))
#define EP05_IN     ((0x05<<3)|(IN<<2))
#define EP06_OUT    ((0x06<<3)|(OUT<<2))
#define EP06_IN     ((0x06<<3)|(IN<<2))
#define EP07_OUT    ((0x07<<3)|(OUT<<2))
#define EP07_IN     ((0x07<<3)|(IN<<2))
#define EP08_OUT    ((0x08<<3)|(OUT<<2))
#define EP08_IN     ((0x08<<3)|(IN<<2))
#define EP09_OUT    ((0x09<<3)|(OUT<<2))
#define EP09_IN     ((0x09<<3)|(IN<<2))
#define EP10_OUT    ((0x0A<<3)|(OUT<<2))
#define EP10_IN     ((0x0A<<3)|(IN<<2))
#define EP11_OUT    ((0x0B<<3)|(OUT<<2))
#define EP11_IN     ((0x0B<<3)|(IN<<2))
#define EP12_OUT    ((0x0C<<3)|(OUT<<2))
#define EP12_IN     ((0x0C<<3)|(IN<<2))
#define EP13_OUT    ((0x0D<<3)|(OUT<<2))
#define EP13_IN     ((0x0D<<3)|(IN<<2))
#define EP14_OUT    ((0x0E<<3)|(OUT<<2))
#define EP14_IN     ((0x0E<<3)|(IN<<2))
#define EP15_OUT    ((0x0F<<3)|(OUT<<2))
#define EP15_IN     ((0x0F<<3)|(IN<<2))


/******************************************************************************
 * Macro:           void mInitializeUSBDriver(void)
 *
 * PreCondition:    None
 *
 * Input:           None
 *
 * Output:          None
 *
 * Side Effects:    None
 *
 * Overview:        Configures the USB module, definition of UCFG_VAL can be
 *                  found in autofiles\usbcfg.h
 *
 *                  This register determines: USB Speed, On-chip pull-up
 *                  resistor selection, On-chip tranceiver selection, bus
 *                  eye pattern generation mode, Ping-pong buffering mode
 *                  selection.
 *
 * Note:            None
 *****************************************************************************/
#define mInitializeUSBDriver()      {UCFG = UCFG_VAL;                       \
                                     usb_device_state = DETACHED_STATE;     \
                                     usb_stat._byte = 0x00;                 \
                                     usb_active_cfg = 0x00;                 \
                                     }

/******************************************************************************
 * Macro:           void mDisableEP1to15(void)
 *
 * PreCondition:    None
 *
 * Input:           None
 *
 * Output:          None
 *
 * Side Effects:    None
 *
 * Overview:        This macro disables all endpoints except EP0.
 *                  This macro should be called when the host sends a RESET
 *                  signal or a SET_CONFIGURATION request.
 *
 * Note:            None
 *****************************************************************************/
#define mDisableEP1to15()       ClearArray((byte*)&UEP1,15);
/*
#define mDisableEP1to15()       UEP1=0x00;UEP2=0x00;UEP3=0x00;\
                                UEP4=0x00;UEP5=0x00;UEP6=0x00;UEP7=0x00;\
                                UEP8=0x00;UEP9=0x00;UEP10=0x00;UEP11=0x00;\
                                UEP12=0x00;UEP13=0x00;UEP14=0x00;UEP15=0x00;
*/

/******************************************************************************
 * Macro:           void mUSBBufferReady(buffer_dsc)
 *
 * PreCondition:    IN Endpoint: Buffer is loaded and ready to be sent.
 *                  OUT Endpoint: Buffer is free to be written to by SIE.
 *
 * Input:           byte buffer_dsc: Root name of the buffer descriptor group.
 *                  i.e. ep0Bo, ep1Bi, ... Declared in usbmmap.c
 *                  Names can be remapped for readability, see examples in
 *                  usbcfg.h (#define HID_BD_OUT      ep1Bo)
 *
 * Output:          None
 *
 * Side Effects:    None
 *
 * Overview:        This macro should be called each time after:
 *                  1. A non-EP0 IN endpoint buffer is populated with data.
 *                  2. A non-EP0 OUT endpoint buffer is read.
 *                  This macro turns the buffer ownership to SIE for servicing.
 *                  It also toggles the DTS bit for synchronization.
 *
 * Note:            None
 *****************************************************************************/
#define mUSBBufferReady(buffer_dsc)                                         \
{                                                                           \
    buffer_dsc.Stat._byte &= _DTSMASK;          /* Save only DTS bit */     \
    buffer_dsc.Stat.DTS = !buffer_dsc.Stat.DTS; /* Toggle DTS bit    */     \
    buffer_dsc.Stat._byte |= _USIE|_DTSEN;      /* Turn ownership to SIE */ \
}

/** T Y P E S ****************************************************************/

/** E X T E R N S ************************************************************/

/** P U B L I C  P R O T O T Y P E S *****************************************/
void USBCheckBusStatus(void);
void USBDriverService(void);
void USBRemoteWakeup(void);
void USBSoftDetach(void); 

void ClearArray(byte* startAdr,byte count);


//////////////////////////////////////////////////////////////////////////////
//#include "system\usb\usbctrltrf\usbctrltrf.h"
/** D E F I N I T I O N S ****************************************************/

/* Control Transfer States */
#define WAIT_SETUP          0
#define CTRL_TRF_TX         1
#define CTRL_TRF_RX         2

/* USB PID: Token Types - See chapter 8 in the USB specification */
#define SETUP_TOKEN         0b00001101
#define OUT_TOKEN           0b00000001
#define IN_TOKEN            0b00001001

/* bmRequestType Definitions */
#define HOST_TO_DEV         0
#define DEV_TO_HOST         1

#define STANDARD            0x00
#define CLASS               0x01
#define VENDOR              0x02

#define RCPT_DEV            0
#define RCPT_INTF           1
#define RCPT_EP             2
#define RCPT_OTH            3

/** E X T E R N S ************************************************************/
extern byte ctrl_trf_session_owner;

extern POINTER pSrc;
extern POINTER pDst;
extern WORD wCount;

/** P U B L I C  P R O T O T Y P E S *****************************************/
void USBCtrlEPService(void);
void USBCtrlTrfTxService(void);
void USBCtrlTrfRxService(void);
void USBCtrlEPServiceComplete(void);
void USBPrepareForNextSetupTrf(void);


//////////////////////////////////////////////////////////////////////////////
//#include "system\usb\usb9\usb9.h"
/** D E F I N I T I O N S ****************************************************/

/******************************************************************************
 * Standard Request Codes
 * USB 2.0 Spec Ref Table 9-4
 *****************************************************************************/
#define GET_STATUS  0
#define CLR_FEATURE 1
#define SET_FEATURE 3
#define SET_ADR     5
#define GET_DSC     6
#define SET_DSC     7
#define GET_CFG     8
#define SET_CFG     9
#define GET_INTF    10
#define SET_INTF    11
#define SYNCH_FRAME 12

/* Standard Feature Selectors */
#define DEVICE_REMOTE_WAKEUP    0x01
#define ENDPOINT_HALT           0x00

/******************************************************************************
 * Macro:           void mUSBCheckAdrPendingState(void)
 *
 * PreCondition:    None
 *
 * Input:           None
 *
 * Output:          None
 *
 * Side Effects:    None
 *
 * Overview:        Specialized checking routine, it checks if the device
 *                  is in the ADDRESS PENDING STATE and services it if it is.
 *
 * Note:            None
 *****************************************************************************/
#define mUSBCheckAdrPendingState()  if(usb_device_state==ADR_PENDING_STATE) \
                                    {                                       \
                                        UADDR = SetupPkt.bDevADR._byte;     \
                                        if(UADDR > 0)                       \
                                            usb_device_state=ADDRESS_STATE; \
                                        else                                \
                                            usb_device_state=DEFAULT_STATE; \
                                    }//end if

/** E X T E R N S ************************************************************/

/** P U B L I C  P R O T O T Y P E S *****************************************/
void USBCheckStdRequest(void);


//////////////////////////////////////////////////////////////////////////////
#if defined(USB_USE_HID)                // See autofiles\usbcfg.h
#include "hid.h"
#endif

