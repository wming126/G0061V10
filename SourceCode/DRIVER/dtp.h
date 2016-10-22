/********************************************************************
�ļ�����:   dtp.h

�ļ�����:   VxWorks���ܲ��Ժ���ͷ�ļ�

�ļ�˵��:   ����һЩ��ͽṹ��

��ǰ�汾:   V2.7

�޸ļ�¼:   2010-10-12  V1.0    ���ı  ����
            2012-03-31  V1.1    ���ı  ����    ���Ӹ��ֲ��Ժ���
            2012-04-18  V1.2    ������  ����    �������������Ժ���
            2012-04-26  V1.3    ���ı  ����    ��������㲥������
            2012-09-04  V1.4    ���ı  ����    ���Ӵ��ڲ�ѯ���ͺ���
            2012-12-19  V1.5    ���ı  ����    ����˫���л����Ժ���
            2013-04-27  V1.6    ���ı  ����    ����TCP���ܲ���
            2013-06-07  V1.7    ���ı  ����    ����VxWorks6.8֧��
            2013-06-27  V1.8    ���ı  ����    ����Һ�����������
            2013-11-06  V1.9    ���ı  ����    ���ӵ��Կ���
            2014-01-26  V2.0    ���ı  ����    ����ǧ��������
            2014-07-04  V2.1    ���ı  ����    �����ź�������
            2015-03-10  V2.2    ���ı  ����    ���˫���л������޸�
            2015-04-28  V2.3    ����    ����    ����˫���л����ܲ���
            2015-05-21  V2.4    ���ı  ����    ���Ӷ�ʱ��0����
            2015-08-13  V2.5    ���ı  ����    ����鲥����BUG
            2015-10-22  V2.6    ���ı  ����    �����������ƺ�λ��
            2016-04-08  V2.7    ���ı  ����    ���Ӳ�����ѡ��
********************************************************************/

#define INCLUDE_WINDML_TEST     0       /* WindML���� 1:���� 0:������ */
#define INCLUDE_COM_TIMEOUT     0       /* ���ڳ�ʱ���չ��� 1:ʹ�� 0:��ʹ�� */
#define INCLUDE_NET_SWITCH      0       /* ˫�����л����� 1:���� 0:������ */
#define NET_SWITCH_TYPE         0       /* ˫���л����� 0:������ 1:ǧ���� */
#define VXWORKS_TYPE            0       /* 0:VxWorks5.5.1 1:VxWorks6.8 */

#define UDP_SERVER_TID          0       /* UDP�������������� */
#define TCP_SERVER_TID          12      /* TCP�������������� */
#define UDP_GROUP_TID           24      /* UDP�鲥�������� */
#define UDP_BROADCAST_TID       36      /* UDP�鲥�������� */
#define TCP_PERFORM_TID         48      /* TCP������������ */
#define UDP_SERVER_PORT         1984    /* UDP������ʹ�ö˿ں� */
#define UDP_CLIENT_PORT         1986    /* UDP�ͻ���ʹ�ö˿ں� */
#define TCP_SERVER_PORT         1988    /* TCP������ʹ�ö˿ں� */
#define TCP_CLIENT_PORT         1990    /* TCP�ͻ���ʹ�ö˿ں� */
#define UDP_GROUP_PORT          1992    /* UDP�鲥ʹ�ö˿ں� */
#define UDP_BROADCAST_PORT      1994    /* UDP�㲥ʹ�ö˿ں� */

#define UDP_GROUP_ADDRESS1      "224.1.1.1" /* UDP�鲥��ַ1 */
#define UDP_GROUP_ADDRESS2      "224.1.1.2" /* UDP�鲥��ַ2 */

#define TCP_PERFORMANCE_SIZE    (200 * 1024 * 1024)     /* TCP���ܲ����������� */

#define INT_NUM_IRQ0            0x20                    /* �˴�ע�⵱����ʹ��PICģʽʱ��Ҫ�޸� */
#define INT_VEC_GET(irq)        (INT_NUM_IRQ0 + irq)

#define BOARD_CPU_FREQUENCE     (1600000000L)            /* LX3160:500MHz PM4060:800MHZ ~ 1.4MHZ */

#define LPT_BASE_ADDRESS        0x378       /* ���ڻ���ַ */

#define DMA_BUFFER_ADDR         0x200000    /* ʹ�õ�DMA�����ַ */
#define DMA_BUFFER_SIZE         0x10000     /* DMA��������󳤶� */

#define DMAC0_BASE              0x00                                /* DMA0��������ַ�Ĵ��� */
#define DMAC0_CH_CA(channel)    (DMAC0_BASE + (channel << 1))       /* ͨ��0-3��ǰ��ַ�Ĵ��� */
#define DMAC0_CH_CC(channel)    (DMAC0_BASE + (channel << 1) + 1)   /* ͨ��0-3��ǰ�ֽڼ����Ĵ��� */

#define DMAC0_STATUS_CMD        (DMAC0_BASE + 8)     /* ״̬/����Ĵ��� */
#define DMAC0_REQUEST           (DMAC0_BASE + 9)     /* ����Ĵ��� */
#define DMAC0_MASK              (DMAC0_BASE + 10)    /* ���μĴ��� */
#define DMAC0_MODE              (DMAC0_BASE + 11)    /* ģʽ�Ĵ��� */
#define DMAC0_CLEAR_FF          (DMAC0_BASE + 12)    /* ����Ⱥ󴥷����Ĵ��� */
#define DMAC0_CLEAR_ALL         (DMAC0_BASE + 13)    /* ������Ĵ��� */
#define DMAC0_CLEAR_MASK        (DMAC0_BASE + 14)    /* ������μĴ��� */
#define DMAC0_MAKK_ALL          (DMAC0_BASE + 15)    /* ��ͨ��������μĴ��� */

#define DMAC1_BASE              0xC0                                    /* DMA1��������ַ�Ĵ��� */
#define DMAC1_CH_CA(channel)    (DMAC1_BASE + ((channel - 4) << 2))     /* ͨ��4-7��ǰ��ַ�Ĵ��� */
#define DMAC1_CH_CC(channel)    (DMAC1_BASE + ((channel - 4) << 2) + 2) /* ͨ��4-7��ǰ�ֽڼ����Ĵ��� */

#define DMAC1_STATUS_CMD        (DMAC1_BASE + 16)    /* ״̬/����Ĵ��� */
#define DMAC1_REQUEST           (DMAC1_BASE + 18)    /* ����Ĵ��� */
#define DMAC1_MASK              (DMAC1_BASE + 20)    /* ���μĴ��� */
#define DMAC1_MODE              (DMAC1_BASE + 22)    /* ģʽ�Ĵ��� */
#define DMAC1_CLEAR_FF          (DMAC1_BASE + 24)    /* ����Ⱥ󴥷����Ĵ��� */
#define DMAC1_CLEAR_ALL         (DMAC1_BASE + 26)    /* ������Ĵ��� */
#define DMAC1_CLEAR_MASK        (DMAC1_BASE + 28)    /* ������μĴ��� */
#define DMAC1_MAKK_ALL          (DMAC1_BASE + 30)    /* ��ͨ��������μĴ��� */

#define DMA_MODE_DEMAND         0x00
#define DMA_MODE_SINGLE         0x40
#define DMA_MODE_BLOCK          0x80
#define DMA_MODE_CASCADE        0xc0
#define DMA_MODE_DECREMENT      0x20
#define DMA_MODE_INCREMENT      0x00
#define DMA_MODE_AUTO_ENABLE    0x10
#define DMA_MODE_AUTO_DISABLE   0x00
#define DMA_MODE_WRITE          0x04
#define DMA_MODE_READ           0x08

#define DMA_CMD_DACK_H          0x80
#define DMA_CMD_DACK_L          0x00
#define DMA_CMD_DREQ_H          0x00
#define DMA_CMD_DREQ_L          0x40
#define DMA_CMD_MEM_ENABLE      0x01
#define DMA_CMD_MEM_DISABLE     0x00

#define BCD_TO_BIN(x) (((x) & 0x0F) + (((x) >> 4) * 10))
#define BIN_TO_BCD(x) ((((x) / 10) << 4) + ((x) % 10))

#define RTC_INDEX       0x70
#define RTC_DATA        0x71
#define RTC_CENTURY     0x32
#define RTC_YEAR        0x09
#define RTC_MONTH       0x08
#define RTC_DAY         0x07
#define RTC_HOUR        0x04
#define RTC_MINUTE      0x02
#define RTC_SECOND      0x00

#define TIMER0          0x40
#define TIMER1          0x41
#define TIMER2          0x42
#define TIMER2_GATE     0x61
#define TIMER_CONTROL   0x43

#define CLOCK           1193181
