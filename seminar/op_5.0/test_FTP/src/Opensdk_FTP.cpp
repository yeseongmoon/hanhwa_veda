
#include "Opensdk_FTP.h"

// Global static pointer used to ensure a single instance
Opensdk_Ftp *Opensdk_Ftp::m_pInstance = NULL;

/**
*@ ********************************************************************
*@ Name           : get_instance                                      *
*@ Description    : singleton implementation of Opensdk_Ftp           *
*@ Arguments      : N/A                                               *
*@ Return Value   : Instance of Opensdk_Ftp class                     *
*@ Notes          :                                                   *
*@ Change History :                                                   *
*@ ********************************************************************
**/
Opensdk_Ftp *Opensdk_Ftp::get_instance(void)
{
    if(m_pInstance == NULL) {
        //Create single instance of Opensdk_Ftp
        m_pInstance = new Opensdk_Ftp();   
    }    
    return m_pInstance;
}

/**
*@ ********************************************************************
*@ Name           : delete_instance                                   *
*@ Description    : delete Opensdk_Ftp instance                       *
*@ Arguments      : N/A                                               *
*@ Return Value   : N/A                                               *
*@ Notes          :                                                   *
*@ Change History :                                                   *
*@ ********************************************************************
**/
void Opensdk_Ftp::delete_instance(void)
{
    if(m_pInstance) {
        //delete single instance of Opensdk_Ftp
        delete m_pInstance;
        m_pInstance = NULL;
    }    
    return;
}


Opensdk_Ftp::Opensdk_Ftp()
{
    m_bTaskStatus   = false;

    m_nThread = (pthread_t)NULL;
    m_pBuffMgr     = NULL;
    m_pWritePacket = NULL;
    m_pReadPacket  = NULL;     
    send_image = 1;
    ftp_initialize();
}
Opensdk_Ftp::~Opensdk_Ftp()
{
    if(m_pBuffMgr) {
        delete m_pBuffMgr;
        m_pBuffMgr = NULL;
    }

}
OPENSDK_ERR_CODE Opensdk_Ftp::event_notify(TASK_STATUS* status)
{

    if(status->TaskError != OPENSDK_APP_OK) {
       fprintf(stdout,"FTP Send Data Failed %d \n",status->TaskError);     
    }
    
    OPENSDK_ERR_CODE err_code;

    //Initialize local variable
    err_code = OPENSDK_APP_OK;

    //Set task status to true
    m_bTaskStatus = true;

    return err_code;
}

OPENSDK_ERR_CODE Opensdk_Ftp::ftp_initialize()
{

    OPENSDK_ERR_CODE errCode;

    //Initialize local variable
    errCode   = OPENSDK_APP_OK;

    //Create & initialize FTP upload structure
    m_pFtpUpload = new OPENSDK_FTP_UPLOAD();
    if(m_pFtpUpload) {
            memset(m_pFtpUpload, NULL, sizeof(OPENSDK_FTP_UPLOAD));
    } else {
            errCode = OPENSDK_APP_ERR_NO_SUFFICIENT_MEMORY;
    }

    //Create instance of YUV I/P buffer manager and initialize
    m_pBuffMgr = new FTP_BUFFER_MANAGER();
    if(m_pBuffMgr) {
        m_pBuffMgr->initBufferManager(10,(1920*1080));
    } else {
        errCode = OPENSDK_APP_ERR_NO_SUFFICIENT_MEMORY;
    }

    pthread_create(&m_nThread, NULL, ThreadFunc, (void *)this);

   return errCode;
}


void *Opensdk_Ftp::ThreadFunc(void *arg)
{    
    Opensdk_Ftp *target;

    // Initialize variable
    target = static_cast<Opensdk_Ftp*>(arg);
    target->FtpRun();
    return NULL;
}

void Opensdk_Ftp::FtpRun()
{
    while(send_image) {
        get_filled_buffer();
        m_bTaskStatus = false;
    }
}

int Opensdk_Ftp::fill_buffer(OPENSDK_ENCVIDEO_EVENT* vidEvent)
{

    int err_code;

    //Initialize the variable here
    err_code = 0;

    //free the buffer
    if(m_pWritePacket)
        m_pWritePacket->setFree(false);

    //Get the frame from media packet
    while((m_pWritePacket = m_pBuffMgr->getEmptyPacket()) == NULL) {
        usleep(3*1000);
    }

    //Get the buffer ptr from media packet
    if(m_pWritePacket) {    
         memcpy(m_pWritePacket->m_pBuffer, vidEvent->buff, vidEvent->size);
         m_pWritePacket->setAvailable(vidEvent->size);
         memcpy(m_pWritePacket->m_pFrameTime, vidEvent->frameTime, MAX_TIME_LENGTH);
    } else {
        err_code = -1;
    }

    return err_code;
}
int Opensdk_Ftp::get_filled_buffer(void)
{
    int err_code;

    char *pBuff;
    int  size;
    char *pframetime;

    //Initialize the variable here
    err_code = 0;
    pBuff    = NULL;
    size     = 0;

    //free the buffer
    if(m_pReadPacket){
        m_pReadPacket->setFree(true);
    }

    //Get the frame from media packet
    while((m_pReadPacket = m_pBuffMgr->getFilledPacket()) == NULL) {
        usleep(3*1000);
    }

    //Get the buffer ptr from media packet
    if(m_pReadPacket) {
        pBuff = (char*)m_pReadPacket->m_pBuffer;
        size = m_pReadPacket->getAvailable();
        pframetime =m_pReadPacket->m_pFrameTime;
        SendFtp(pBuff,size,pframetime);
    }

    return err_code;
}


OPENSDK_ERR_CODE Opensdk_Ftp::SendFtp(char *pBuff,int size,char *pframeTime)
{
    OPENSDK_ERR_CODE errCode;
    INT8_N           file_name[FTP_MAX_FILE_NAME_LEN];
    INT8_N           frametime[FTP_MAX_FILE_NAME_LEN];
    INT32_N          event_id;
    INT32_N          struct_size;

    //Initialize local variable
    errCode   = OPENSDK_APP_OK;
    memset(&file_name[0],NULL,FTP_MAX_FILE_NAME_LEN);
    struct_size   = sizeof(OPENSDK_FTP_UPLOAD);

    memcpy(frametime,pframeTime,MAX_TIME_LENGTH);


    // generate file name to send over ftp
    errCode   = ftp_generate_file_name_message(file_name,frametime);

    fprintf(stdout,"filename %s \n",file_name);

    // fill the jpeg buffer 
    m_pFtpUpload->buff     = pBuff;
    m_pFtpUpload->size     = size;
    m_pFtpUpload->fileName = file_name;

    
    //Send event notification to email
    errCode = OPENSDK::EVENT::send_event(OPENSDK_FTP_FILE_UPLOAD,
                &event_id,
                (void*)m_pFtpUpload,
                struct_size);

    send_image = 0;

    //Need to wait for encoded data
    if(errCode == OPENSDK_APP_OK) {
        while(m_bTaskStatus == false) {
                usleep(1000);
        }
    }    
    return errCode;   
}

OPENSDK_ERR_CODE Opensdk_Ftp::ftp_generate_file_name_message(INT8_N* fileName,char *pframetime)
{
    OPENSDK_ERR_CODE err_code;
    INT8_N        frame_time[FTP_MAX_TIME_LENGTH];

    //Initialize local variable
    err_code = OPENSDK_APP_OK;

    //Get frame time
    memcpy(frame_time,pframetime,FTP_MAX_TIME_LENGTH);

    //Get current year from time
    m_tFrameTime.tm_year = atoi(strtok(frame_time, "/"));
    m_tFrameTime.tm_mon  = atoi(strtok(NULL, "/"));
    m_tFrameTime.tm_mday = atoi(strtok(NULL, " "));
    m_tFrameTime.tm_hour = atoi(strtok(NULL, ":"));
    m_tFrameTime.tm_min  = atoi(strtok(NULL, ":"));
    m_tFrameTime.tm_sec  = atoi(strtok(NULL, " "));

    sprintf(fileName,
            "%04d%02d%02d%02d%02d%02d.jpg",
            m_tFrameTime.tm_year, m_tFrameTime.tm_mon, m_tFrameTime.tm_mday,
            m_tFrameTime.tm_hour, m_tFrameTime.tm_min, m_tFrameTime.tm_sec);

    //sprintf(fileName,"123456789_123456789_123456789_123456789_123456789_.jpg");

        
    return err_code;
}

