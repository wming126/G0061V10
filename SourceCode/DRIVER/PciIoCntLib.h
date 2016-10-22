/********************************************************************
�ļ�����:   PciIoCntLib.h

�ļ�����:   GAD64655�忨��������ͷ�ļ�(��Դ�忨����������˼�����)

�ļ�˵��:   GAD64655�忨��������,IO������Ĵ���ӳ�䵽PCI�豸IO�ռ�
            ���Բ���Ҫvxworks����Ҫ��������ڴ�ӳ�䣬ֱ�ӷ�����IO��
            �伴�ɡ�

��ǰ�汾:   V1.0

�޸ļ�¼:   2016-07-07  V1.0    �� �� ����
            2016-08-10  V1.1    �� �� ���  ���io�ж�֧��
********************************************************************/
#ifndef _PCIIOCNTLIB_H_
#define _PCIIOCNTLIB_H_

#pragma pack(1)                         /* �ṹ����һ���ֽڶ��� */

#define IO_INT_MODE         1           /* 1:������ 0���½��� */

#define VENDOR_ID           0x10b5      /* PCI VENDOR ID*/
#define DEVICE_ID           0x9054      /* PCI DEVICE ID*/

#define MAX_GAD64655_NUM    2           /* ��忨ʱ�쿨���� */
#define MAX_IN_PORT         6           /* ����IO����port����ÿ��port 8��IO */
#define MAX_OUT_PORT        2           /* ����IO���port����ÿ��port 8��IO */
#define MAX_CNT_NUM         8           /* ����忨���������� */

#define FPGA_IO_INT_STATE   8           /* �ж�״̬ 0XFF:�жϲ��� 0XFE:���ж� */
#define FPGA_IO_INT_CLEAR   9           /* ����ж�bit0:���ж� bit1:�ж�ʹ�� */
#define FPGA_IO_INT_ENABLE  10          /* ����ж�bit0:���ж� bit1:�ж�ʹ�� */
#define FPGA_IO_INT_MODE    11          /* IO�жϴ�����ʽ��bit0 1�������� bit0 0���½��� */


/* ����˿ں� */
typedef enum InPort_e
{
    InPort1 = 0, InPort2 = 1, InPort3 = 2, InPort4 = 3, InPort5 = 4, InPort6 = 5
} InPort_t;

/* ����˿ں� */
typedef enum OutPort_e
{
    OutPort1 = 0, OutPort2 = 1
} OutPort_t;

#ifdef __cplusplus
extern "C" {
#endif

/* indexΪ���忨ʱPCI�豸�����������豸ʱ���μ�һ  */
int CreatePciIoCnt(int index);
int RemovePciIoCnt(int index);

/* fdΪ�����ڲ�ά���������������ڶ��쿨�Ŀ���,fd=0Ϊ��һ��忨 */
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
