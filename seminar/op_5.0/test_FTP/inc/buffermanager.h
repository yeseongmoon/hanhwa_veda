/*
************************************************************************
** Copyright 2011 Samsung Techwin Co. Ltd. all right reserved.	      **
**                                                                    **
** This software is the property of Samsung Techwin and is furnished  **
** under license by Samsung Techwin. This software may be used only   **
** in accordance with the terms of said license. This copyright notice**
** may not be removed, modified or obliterated without the prior      **
** written permission of Samsung Techwin.                             **
**                                                                    **
** This software may not be copied, transmitted, provided to or       **
** otherwise made available to any other person, company, corporation **
** or other entity except as specified in the terms of said  license. **
**                                                                    **
** No right, title, ownership or other interest in the software is    **
** hereby granted or transferred.                                     **
**                                                                    **
** The information contained herein is subject to change without      **
** notice and should not be construed as a commitment by              **
** Samsung Techwin.                                                   **
************************************************************************
************************************************************************
*/

#ifndef _BUFFERMANAGER_H_
#define _BUFFERMANAGER_H_

#include <stdio.h>
#include <pthread.h>
#include <time.h>

#define BUFF_16BIT_ALLIGNMENT     16
#define MAX_TIME_LENGTH           32

class FTP_MEDIA_PACKET {
public:
    FTP_MEDIA_PACKET(int nSize) {
		unsigned int align_bytes;

		align_bytes  = BUFF_16BIT_ALLIGNMENT;
		m_nMaxSize   = nSize;
		m_pBuffer    = NULL;
		m_bFree      = true;
		m_nAvailable = 0;
		m_nSize      = 0;

		m_alloc_ptr  = new char[m_nMaxSize + align_bytes];

		//! Get Alignment address
		m_pBuffer = (char *)((size_t)m_alloc_ptr + align_bytes - ((size_t)m_alloc_ptr % align_bytes));

                m_pFrameTime    = new char[MAX_TIME_LENGTH];
	}
	
	~FTP_MEDIA_PACKET()	{
		if(m_alloc_ptr) {
			delete[] m_alloc_ptr;
			m_alloc_ptr = NULL;
			m_pBuffer   = NULL;
		}
		if(m_pFrameTime) {
			delete[] m_pFrameTime;
			m_pFrameTime = NULL;
		}

	}
public:
    //Check media packet is free or not
    int  isFree(void){return m_bFree;};

    //get the size of media packet
    int getSize(void){return m_nSize;};

    //set the available data from media packet
    void  setAvailable(int nAvail) {
    	m_nAvailable = nAvail;
    	return;
    };

    //Get the available data from media packet
    int getAvailable(void){ return m_nAvailable;};

    //Set the media packet state to free
    void  setFree(bool bFree){
    	m_bFree = bFree;
    	return;
    };

public:
    char*   m_pBuffer;      
    char*   m_alloc_ptr;
    int     m_nSize;       //size of the relevant data present in the packet m_nSize<=m_nMaxSize
    char*   m_pFrameTime;  //Audio and Video time
private:
    bool    m_bFree;         //Whether the packet is free or not
    int     m_nMaxSize;      //max packet size
    int     m_nAvailable;
};

class FTP_BUFFER_MANAGER
{
public:
    FTP_BUFFER_MANAGER();
    ~FTP_BUFFER_MANAGER();

public:
    //Initialize the buffer manager
    int initBufferManager(unsigned long nBuffCount,
    		          unsigned long nBuffSize);

    //Get the filled media packet
    FTP_MEDIA_PACKET* getFilledPacket(void);

    //Get empty media packet
    FTP_MEDIA_PACKET* getEmptyPacket(void);

    //Get the media packet count
    int getBuffCnt(void){return m_nBuffCount;};

private:
    //Get the current write buffer index
    int getWriteBuffIndex(void);

    //Get the current read buffer index
    int getReadBuffIndex(void);

private:
    pthread_mutex_t    m_buffMutex;
    FTP_MEDIA_PACKET** m_pBuffers;
    int                m_nBuffCount;
    int                m_nCurrReadIndex;
    int                m_nCurrWriteIndex;
};

#endif /* FTP_BUFFERMANAGER_H_ */
