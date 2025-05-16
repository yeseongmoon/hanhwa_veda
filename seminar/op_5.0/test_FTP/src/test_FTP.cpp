#include <stdio.h>
#include <stdlib.h>

#include <SDKAPI/opensdk_defines.h>
#include <SDKAPI/opensdk_device.h>
#include <SDKAPI/opensdk_profile.h>
#include <SDKAPI/opensdk_ptz.h>
#include <SDKAPI/opensdk_record.h>
#include <SDKAPI/opensdk_videoanalytics.h>
#include <SDKAPI/opensdk_videosetup.h>

#include "Opensdk_FTP.h"

/**
*@ ********************************************************************
*@ Name           : recv_event                                        *
*@ Description    : Receives input event from camera SDK              *
*@ Arguments      : eventIn[IN]: Input event type                     *
*@                : pData[IN]  : Data for input event                 *
*@ Return Value   : N/A                                               *
*@ Notes          :                                                   *
*@ Change History :                                                   *
*@ ********************************************************************
**/
void recv_event(OPENSDK_INPUT_EVENT eventIn, void* pData)
{
    Opensdk_Ftp*  pInstance;
    OPENSDK_ERR_CODE errCode;
    
    //Initialize local variable
    errCode   = OPENSDK_APP_OK;
    pInstance = NULL;

    //Get MOTIONDETECTOR class instance
    pInstance  = Opensdk_Ftp::get_instance();    
    if(pInstance == NULL) {
        //OPENSDK::EVENT::send_event(OPENSDK_STOP_APPLICATION, NULL,NULL, NULL);
        //MOTIONDETECTOR::delete_instance();
        return;
    }

    //Handle the input events here
    switch(eventIn) {
        case OPENSDK_MEDIA_VIDEO:
        {
            //fprintf(stdout,"receive Encoded Video\n");
            OPENSDK_ENCVIDEO_EVENT* vidEvent;            
            //debug_message("Event Type: OPENSDK_MEDIA_VIDEO\n");
            vidEvent = (OPENSDK_ENCVIDEO_EVENT*) pData;
            /*
            printf("\033[33m[Event Type: OPENSDK_MEDIA_VIDEO] size: %d(%d x %d), frameType: %d, codec: %d, time_stamp: %d\033[0m\n"
              ,vidEvent->size
              ,vidEvent->width
              ,vidEvent->height
              ,vidEvent->frameType
              ,vidEvent->codec
              ,vidEvent->time_stamp);
            */
            if(vidEvent->codec == OPENSDK_MEDIA_MJPEG) {
                if(vidEvent->size > ((vidEvent->width * vidEvent->height) / 20))
                {
                  pInstance->fill_buffer(vidEvent);
                }
                else
                {
                  //fprintf(stdout,"file size is small(not best shot)\n");
                }
            } else {
            	debug_message("Only MJPEG Codec is supported\n");
            	fprintf(stdout,"Only MJPEG Codec is supported\n");
            }
            //Process encoded video
            break;
        }
        case OPENSDK_EVENT_STATUS:
        {
            TASK_STATUS* status;

            //Get TASK_STATUS
            status = (TASK_STATUS*)pData;
            if(status->TaskName == OPENSDK_FTP_FILE_UPLOAD) {
                pInstance->event_notify(status);
            }
            break;
        }
        default:
        {
            debug_message("Unknown event %d occurred\n", eventIn);
            break;
        }
    }

    return;
}
/**
*@ ********************************************************************
*@ Name           : recv_data                                         *
*@ Description    : Receives data from camera SDK                     *
*@ Arguments      : payload_request[IN]: Request from web page        *
*@                : payload_response[OUT]  : Response to web page     *
*@ Return Value   : N/A                                               *
*@ Notes          :                                                   *
*@ Change History :                                                   *
*@ ********************************************************************
**/
OPENSDK_ERR_CODE recv_data(void *payload_request,
                           void *payload_response)
{
    OPENSDK_PAYLOAD_REQUEST*  req_payload;
    OPENSDK_PAYLOAD_RESPONSE* res_payload;
    OPENSDK_ERR_CODE          errCode;
    
    //Initialize local variable
    errCode = OPENSDK_APP_OK;
    
    //Get the request & response pointer
    req_payload = (OPENSDK_PAYLOAD_REQUEST*)payload_request;
    res_payload = (OPENSDK_PAYLOAD_RESPONSE*)payload_response;
    
    debug_message("Request from web page: %s and len %d\n", 
                req_payload->pBuff, req_payload->pBufLen);
    
    //Process request & send response
    
    return errCode;
}

/**
*@ ********************************************************************
*@ Name           : one_shot                                          *
*@ Description    : called to initialize application                  *
*@ Arguments      : N/A                                               *
*@ Return Value   : N/A                                               *
*@ Notes          :                                                   *
*@ Change History :                                                   *
*@ ********************************************************************
**/
void one_shot(void)
{
    debug_message("one_shot\n");
    
    return;
}


