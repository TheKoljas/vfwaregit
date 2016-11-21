#ifndef __WJALINK_CALLBACK_H__
#define __WJALINK_CALLBACK_H__

typedef struct SYSTEM_TIME_WJA{
	int  year;///< 年。   
	int  month;///< 月，January = 1, February = 2, and so on.	
	int  day;///< 日。	 
	int  wday;///< 星期，Sunday = 0, Monday = 1, and so on	 
	int  hour;///< 时。   
	int  minute;///< 分。	
	int  second;///< 秒。	
	int  isdst;///< 夏令时标识。   
}WJA_SYSTEM_TIME;

typedef struct RecordTime_WJA{
	WJA_SYSTEM_TIME StartTime;
	WJA_SYSTEM_TIME EndTime;
}WJA_RECORDTIME;

typedef enum{
 	 ALL_TYPE,                //全部
	 SYSTEM_TYPE,            //系统操作
	 CONIFG_TYPE,            //配置操作
	 DATAMANAGER_TYPE,      //数据管理
	 ALARM_TYPE,             //报警事件
     RECORD_OPERRATION_TYPE, //录像操作
     USERMANAGER_TYPE,      //用户管理
	 CLEAR_TYPE,             //日志清除
     File_operate              //文件操作
 }WJA_Log_Type;

typedef struct tagQueryLog_WJA
{
	WJA_Log_Type  ucLogType;/*查询的日志类型*/
		/* 0 全部1 系统操作2 配置操作3 数据管理
		4 报警事件5 录像操作6 用户管理7 日志清除8 文件操作*/
	WJA_SYSTEM_TIME  stStartTime;/*起始时间*/
	WJA_SYSTEM_TIME  stEndTime;/*结束时间*/
	unsigned char  ucRes[16];
}WJA_NET_QUERY_SYSYTEM_LOG;

typedef struct tagNetLogInfo_WJA
{
    WJA_Log_Type      usType;         /*日志类型*/
	WJA_SYSTEM_TIME  stTime;			/* 日志时间 */
	unsigned char     ucContext[64]; 		/*内容*/
	unsigned char  	 ucRes1[4];
}WJA_NET_LOG_INFO;

int wja_GetLogInfo_CallBack(WJA_NET_QUERY_SYSYTEM_LOG* LogInfo,WJA_NET_LOG_INFO** ptr ,int *LogSize);

/* Functionality:
   set Record  DownLoadTime,the first step of Record  DownLoad,sum twp steps
 Parameters:
 	chn:for IPC,the value is zero
 		for nvr .the value is nvr channel for IPC
 	time:start time and End Time
 Return:
   1 have Record on storage , 0 no Record for DownLoad
 */
int wja_RecordDownLoadTimeSet(int chn,WJA_RECORDTIME time,unsigned int clientid);

int wja_RecordDownLoadFileOpen(int chn, char recordname[80],unsigned int clientid);

/* Functionality:
   start DownLoad Record,the second step of Record  DownLoad,sum twp steps
 Parameters:
 	chn:for IPC,the value is zero
 		for nvr .the value is nvr channel for IPC
 Return:
   0 on success, otherwise fail.
 */
int wja_RecordSendStart(int chn);

/* Functionality:
   stop DownLoad Record
 Parameters:
 	chn:for IPC,the value is zero
 		for nvr .the value is nvr channel for IPC
 Return:
   0 on success, otherwise fail.
 */
int wja_RecordSendStop(int chn);

/* Functionality:
   stop all DownLoad Record of device
 Return:
   0 on success, otherwise fail.
 */
int wja_RecordSendStopAll();


typedef struct 
{
	unsigned char ucFileType; /* 0 录像  1 图片 */
	unsigned char ucSubType; /* 子类型0 全部1 外部报警2 动检（包括视频遮挡视频丢失动态检测）3 所有报警（包括1，2类型外还包括异常报警，硬盘满等）4 手动录像 5定时录像 6卡号录像*/
	unsigned char ucChannel; /* 录像通道 */
	unsigned char ucRes;
	unsigned char ucFileName[80];/* 文件名格式:通道号_开始时间(yyyy-MM-dd-HH-mm-ss)_结束时间(yyyy-MM-dd-HH-mm-ss)_盘号_分区号_簇号_文件序号_文件类型(00录像 01图片)_文件长度*/  
	WJA_SYSTEM_TIME stStartTime;
	WJA_SYSTEM_TIME stEndTime;
	unsigned int	FileLen;
	unsigned char ucRes1[16];
}WJA_NET_FILEINFO;

/* Functionality:
   get VideoFile list infoation between stStartTime and stEndTime,use for video PlayBack or Search
 Parameters:
 	SearchFileInfo:include chn ,stStartTime stEndTime and so on
 	ptr:			output file list for 	VideoFile search,include VideoFile name
 	size			output for VideoFile count
 Return:
   0 on success, otherwise fail.
 */
int wja_VideoFileSearch_CallBack(WJA_NET_FILEINFO *SearchFileInfo, WJA_NET_FILEINFO **ptr, int *size);

typedef struct _DEV_VideoDataFormat_WJA
{
	unsigned int codec;			//锟斤拷锟诫方式
	unsigned int bitrate;        //锟斤拷锟斤拷锟斤拷, bps
	unsigned short width;			//图锟斤拷锟斤拷
	unsigned short height;			//图锟斤拷叨锟�
	unsigned char framerate;		//帧锟斤拷, fps
	unsigned char colorDepth;		//should be 24 bits
	unsigned char frameInterval;   //I帧锟斤拷锟�
	unsigned char reserve;

}WJA_VideoDataFormat;

/* Functionality:
   open VideoFile  for PlayBack,and also get stream parameter
 Parameters:
 	recordname:PlayBack video file
 	chn:			input
 	videoinfo			output for VideoFile stream parameter
 Return:
   0 on success, otherwise fail.
 */
int wja_PlayBackSendStreamOpen(int chn, char recordname[80],WJA_VideoDataFormat* videoinfo);
int wja_PlayBackPointTime(int chn, WJA_RECORDTIME time,WJA_VideoDataFormat* videoinfo);

/* Functionality:
   after open VideoFile  for PlayBack,then inform the IPC to send record data
 Parameters:
 	chn:			input
 Return:
   0 on success, otherwise fail.
 */
int wja_PlayBackSendStart(int chn);



/* Functionality:
   after  IPC send record data,manual control PlayBack speed 
 Parameters:
 	chn:			input
 Return:
   0 on success, otherwise fail.
 */
int wja_PlayBackSendControl(int chn,int cmd,int value);

/* Functionality:
   after open VideoFile  for PlayBack,need close PlayBack
 Parameters:
 	chn:			input
 Return:
   0 on success, otherwise fail.
 */
int wja_PlayBackSendStop(int chn);

/* Functionality:
   stop all PlayBack for device
 Return:
   0 on success, otherwise fail.
 */
int wja_PlayBackSendStopAll();

/* Functionality:
  start RealTime video Play
 Parameters:
 	chn:			input
 	stream:	main stream or sub stream
 	videoinfo: output for VideoFile stream parameter
 Return:
   0 on success, otherwise fail.
 */
int wja_RealTimePlayOpen(int chn,int stream,WJA_VideoDataFormat* videoinfo);


/* Functionality:
  stop RealTime video Play
 Parameters:
 	chn:			input
 	stream:	main stream or sub stream
 Return:
   0 on success, otherwise fail.
 */
int wja_RealTimePlayClose(int chn,int stream);

/* Functionality:
  stop all RealTime video Play
 Parameters:
 Return:
   0 on success, otherwise fail.
 */
int wja_RealTimePlayCloseAll();


int wja_SnapStart(int chn);

typedef struct{
	int iDevStatus;    //设备运行状态
	int iDiskStatus;    //硬盘状态
	int iDiskCap;       //硬盘容量
	int iDiskReCap;     //硬盘剩余容量
	int iDev4gStatus;   //4G状态
	int iDevWifiStatus; //WIFI状态
	char verdata[64];   //版本信息
	WJA_SYSTEM_TIME StartTime; //开机时间
}WJA_DevStatus;
int wja_GetDevStatus(int chn,WJA_DevStatus* Status);

typedef struct{
	int iEnable;
	char szSsid[32];
	char szPswd[32];
}WJA_WifiInfo;

int wja_GetWifiInfo(WJA_WifiInfo* WifiInfo);
int wja_SetWifiInfo(WJA_WifiInfo WifiInfo);

typedef enum{
	MAINCHIP=0,
}WJA_CHIP_TYPE;

bool wja_FirmwareUpload(WJA_CHIP_TYPE type);

#endif
