
#include "IUart2.h"
#include "ipc_inc.h"



//在UART2Create 调用之前调用有效
//默认为阻塞模式
//iFlag 1 非阻塞0,阻塞
int UART2SetNonBlock(int iFlag){  return 0;}

/// 创建前面板设备
/// 
/// \param 无
/// \retval <0 创建失败
/// \retval 0 创建成功
int UART2Create(void){  return 0;}


/// 销毁前面板设备
/// 
/// \param 无
/// \retval <0 销毁失败
/// \retval 0 销毁成功
int UART2Destory(void){  return 0;}


/// 设置串口属性。
/// 
/// \param [in] pAttr 指向串口属性结构COMM_ATTR的指针。
/// \retval 0  关闭成功
/// \retval <0  关闭失败
int UART2SetAttribute(UART2_ATTR *pAttr){  return 0;}

/// 读前面板数据，一直等到读出指定的字节或出错时才返回，否则阻塞。
/// 
/// \param [out] pData 数据缓冲的指针。
/// \param [in] nBytes 要读出的字节数
/// \return>0  读出的字节数
/// \retval <=0 读失败
int UART2Read(void* pData, uint nBytes){  return 0;}


/// 写前面板数据，一直等到写入指定的字节或出错时才返回，否则阻塞。
/// 
/// \param [in] pData 数据缓冲的指针。
/// \param [in] nBytes 要写入的字节数
/// \return>0  写入的字节数
/// \retval <=0  写失败
int UART2Write(void* pData, uint nBytes){  return 0;}

/// @} end of group


