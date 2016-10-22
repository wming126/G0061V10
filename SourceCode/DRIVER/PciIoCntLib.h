/********************************************************************
文件名称:   PciIoCntLib.h

文件功能:   GAD64655板卡驱动程序头文件(在源板卡基础上添加了计数器)

文件说明:   GAD64655板卡驱动程序,IO板外设寄存器映射到PCI设备IO空间
            所以不需要vxworks不需要对其进行内存映射，直接访问其IO空
            间即可。

当前版本:   V1.0

修改记录:   2016-07-07  V1.0    王 明 创建
            2016-08-10  V1.1    王 明 添加  添加io中断支持
********************************************************************/
#ifndef _PCIIOCNTLIB_H_
#define _PCIIOCNTLIB_H_

#pragma pack(1)                         /* 结构体以一个字节对齐 */

#define IO_INT_MODE         1           /* 1:上升沿 0：下降沿 */

#define VENDOR_ID           0x10b5      /* PCI VENDOR ID*/
#define DEVICE_ID           0x9054      /* PCI DEVICE ID*/

#define MAX_GAD64655_NUM    2           /* 多板卡时办卡个数 */
#define MAX_IN_PORT         6           /* 单板IO输入port数，每个port 8个IO */
#define MAX_OUT_PORT        2           /* 单板IO输出port数，每个port 8个IO */
#define MAX_CNT_NUM         8           /* 单块板卡计数器个数 */

#define FPGA_IO_INT_STATE   8           /* 中断状态 0XFF:中断产生 0XFE:无中断 */
#define FPGA_IO_INT_CLEAR   9           /* 清除中断bit0:清中断 bit1:中断使能 */
#define FPGA_IO_INT_ENABLE  10          /* 清除中断bit0:清中断 bit1:中断使能 */
#define FPGA_IO_INT_MODE    11          /* IO中断触发方式：bit0 1：上升沿 bit0 0：下降沿 */


/* 输入端口号 */
typedef enum InPort_e
{
    InPort1 = 0, InPort2 = 1, InPort3 = 2, InPort4 = 3, InPort5 = 4, InPort6 = 5
} InPort_t;

/* 输出端口号 */
typedef enum OutPort_e
{
    OutPort1 = 0, OutPort2 = 1
} OutPort_t;

#ifdef __cplusplus
extern "C" {
#endif

/* index为多块板卡时PCI设备索引，创建设备时依次加一  */
int CreatePciIoCnt(int index);
int RemovePciIoCnt(int index);

/* fd为驱动内部维护的描述符，用于多块办卡的控制,fd=0为第一块板卡 */
int OpenPciIoCnt(int fd);
int ClosePciIoCnt(int fd);
int WritePciIo(int fd, OutPort_t port, unsigned char ch);
unsigned char ReadPciIo(int fd, InPort_t port);

int StartPciCnt(int fd, int cnt_num);
int StopPciCnt(int fd, int cnt_num);
unsigned short ReadPciCnt(int fd, int cnt_num);
int ClearPciCnt(int fd, int cnt_num);
int WaitPciIo(int fd, int timeout);

#ifdef __cplusplus
}
#endif

#endif
