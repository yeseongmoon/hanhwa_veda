#ifndef _OPENSDK_FTP_H_
#define _OPENSDK_FTP_H_


#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include <pthread.h>
#include <time.h>

#include "buffermanager.h"
#include <SDKAPI/opensdk_defines.h>

#define FTP_MAX_TIME_LENGTH    32
#define FTP_MAX_FILE_NAME_LEN  128

class Opensdk_Ftp
{
private:
    //constructor
    Opensdk_Ftp();
public:
    //Destructor
    ~Opensdk_Ftp();
    OPENSDK_ERR_CODE SendFtp(char *pBuff,int size,char *pframeTime);

    static Opensdk_Ftp* get_instance(void);    
    static VOID_N delete_instance(void);
    OPENSDK_ERR_CODE event_notify(TASK_STATUS* status);
    OPENSDK_ERR_CODE ftp_initialize();
    OPENSDK_ERR_CODE ftp_generate_file_name_message(INT8_N* fileName,char *pframetime);
    
    static void* ThreadFunc(void *arg);
    void FtpRun();
    int fill_buffer(OPENSDK_ENCVIDEO_EVENT* vidEvent);
    int get_filled_buffer(void);

private:

    OPENSDK_FTP_UPLOAD*      m_pFtpUpload;
    struct tm                m_tFrameTime;
    volatile BOOL_N          m_bTaskStatus;
    static Opensdk_Ftp*      m_pInstance;
    pthread_t	             m_nThread; 
    FTP_MEDIA_PACKET*        m_pWritePacket;
    FTP_MEDIA_PACKET*        m_pReadPacket;
    FTP_BUFFER_MANAGER*      m_pBuffMgr;
	BOOL_N          		 send_image;
};

#endif  //_OPENSDK_FTP_H_
