/*
************************************************************************
** Copyright 2011 Samsung Techwin Co. Ltd. all right reserved.        **
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

#include "buffermanager.h"


FTP_BUFFER_MANAGER::FTP_BUFFER_MANAGER()
{
    m_nCurrWriteIndex = 0;
    m_nCurrReadIndex  = 0;
    m_nBuffCount      = 0;
    m_pBuffers        = NULL;
    pthread_mutex_init(&m_buffMutex, NULL);
 }

FTP_BUFFER_MANAGER::~FTP_BUFFER_MANAGER()
{
    for(int i=0; i < m_nBuffCount; i++) {
        if(m_pBuffers[i]) {
            delete m_pBuffers[i];
            m_pBuffers[i] = NULL;
        }
    }

    if(m_pBuffers) {
        delete[] m_pBuffers;
        m_pBuffers = NULL;
    }
    pthread_mutex_destroy(&m_buffMutex);
}

/**
*@ **********************************************************************************
*@ Name           : initBufferManager                                               *
*@ Description    : BufferManager initialization module.nBuffCount no of buffers    *
*@                  are allocated with each hving the size of nBuffSize.            *
*@ Arguments      : nBuffCount[IN] : Number of buffer packets.                      *
                    nBuffSize[IN] : Buffer size.                                    *
*@ Return Value   : zero in case of success and -1 incase of failure                *
*@ Change History :                                                                 *
*@ **********************************************************************************
**/
int FTP_BUFFER_MANAGER::initBufferManager(unsigned long nBuffCount,
                                          unsigned long nBuffSize)
{
    int error;

    //Initialize variable
    error        = 0;
    m_nBuffCount = nBuffCount;

        //Lock the buffer mutex
        pthread_mutex_lock(&m_buffMutex);
        //Allocate memory for media packets count
        m_pBuffers    = new FTP_MEDIA_PACKET *[m_nBuffCount];
        for(int i=0; i < m_nBuffCount; i++) {
            //Allocate memory for each media packet
            m_pBuffers[i] = new FTP_MEDIA_PACKET(nBuffSize);
            if(!m_pBuffers[i])
                error= -1;
        }
        pthread_mutex_unlock(&m_buffMutex);

    return error;
}

/**
*@ *********************************************************************
*@ Name           : getFilledPacket                                    *
*@ Description    : return a Filled packet for reading                 *
*@                                                                     *
*@ Arguments      : VOID                                               *
*@ Return Value   : pointer to the Filled packet                       *
*@ Change History :                                                    *
*@                                                                     *
*@ *********************************************************************
**/
FTP_MEDIA_PACKET* FTP_BUFFER_MANAGER::getFilledPacket()
{
    //Lock the buffer mutex
    pthread_mutex_lock(&m_buffMutex);
    //Get the current read buffer index
    int index = getReadBuffIndex();

    if( (index != -1) && (m_pBuffers[index]) ) {
        pthread_mutex_unlock(&m_buffMutex);
        return m_pBuffers[index];
    }
    pthread_mutex_unlock(&m_buffMutex);

    return NULL;
}

/**
*@ **********************************************************************
*@ Name           : getEmptyPacket                                      *
*@ Description    : return a Empty packet for reading/wrinting.         *
*@                                                                      *
*@ Arguments      : VOID                                                *
*@ Return Value   : pointer to the Empty packet                         *
*@ Change History :                                                     *
*@                                                                      *
*@ **********************************************************************
**/
FTP_MEDIA_PACKET* FTP_BUFFER_MANAGER::getEmptyPacket()
{
    //Lock the buffer mutex
    pthread_mutex_lock(&m_buffMutex);
    //Get the current write buffer index
    int index = getWriteBuffIndex();

    if( (index != -1) && (m_pBuffers[index])) {
        pthread_mutex_unlock(&m_buffMutex);
        return m_pBuffers[index];
    }
    pthread_mutex_unlock(&m_buffMutex);

    return NULL;
}

/**
*@ **********************************************************************
*@ Name           : getWriteBuffIndex                                   *
*@ Description    : Reurns the current write buffer index which can be  *
*@                utilized by others for writing into current packet.   *
*@ Arguments      : VOID                                                *
*@ Return Value   : current index of the buffer to be written           *
*@ Change History :                                                     *
*@                                                                      *
*@ **********************************************************************
**/
int FTP_BUFFER_MANAGER::getWriteBuffIndex()
{
    int index;

    //Initialize variable
    index = m_nCurrWriteIndex;

    //Check free buffer to write
    if(m_pBuffers[m_nCurrWriteIndex]->isFree()){
        m_nCurrWriteIndex = m_nCurrWriteIndex+1;
        if(m_nCurrWriteIndex == m_nBuffCount)
            m_nCurrWriteIndex = 0;
        return index;
    }

    return -1;
}

/**
*@ **********************************************************************
*@ Name           : getReadBuffIndex                                    *
*@ Description    : Return buffers index where currently its pointing   *
*@                  for reading the packets.                            *
*@ Arguments      : VOID                                                *
*@ Return Value   : current index of the buffer to be read              *
*@ Change History :                                                     *
*@ **********************************************************************
**/
int FTP_BUFFER_MANAGER::getReadBuffIndex()
{
    int index = 0;

    //Initialize variable
    index = m_nCurrReadIndex;

    //Check filled buffer to read
    if(!m_pBuffers[m_nCurrReadIndex]->isFree()){
        m_nCurrReadIndex = m_nCurrReadIndex+1;
        if(m_nCurrReadIndex == m_nBuffCount)
            m_nCurrReadIndex = 0;
        return index;
    }

    return -1;
}


