#include <stdio.h>
#include <stdlib.h>

#include <SDKAPI/opensdk_defines.h>
#include <SDKAPI/opensdk_device.h>
#include <SDKAPI/opensdk_profile.h>
#include <SDKAPI/opensdk_ptz.h>
#include <SDKAPI/opensdk_record.h>
#include <SDKAPI/opensdk_videoanalytics.h>
#include <SDKAPI/opensdk_videosetup.h>

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
    //Handle the input events here
    switch(eventIn) {
        case OPENSDK_RAW_VIDEO:
        {
            OPENSDK_ENCVIDEO_EVENT* vidEvent;            
            debug_message("Event Type: OPENSDK_RAW_VIDEO\n");
            vidEvent = (OPENSDK_ENCVIDEO_EVENT*) pData;
            //Process raw video
            break;
        }
        case OPENSDK_RAW_AUDIO:
        {
            OPENSDK_ENCAUDIO_EVENT* audEvent;            
            debug_message("Event Type: OPENSDK_RAW_AUDIO\n");
            audEvent = (OPENSDK_ENCAUDIO_EVENT*) pData;
            //Process raw audio
            break;
        }
        case OPENSDK_MEDIA_VIDEO:
        {
            OPENSDK_ENCVIDEO_EVENT* vidEvent;            
            debug_message("Event Type: OPENSDK_MEDIA_VIDEO\n");
            vidEvent = (OPENSDK_ENCVIDEO_EVENT*) pData;
            //Process encoded video
            break;
        }
        case OPENSDK_MEDIA_AUDIO:
        {
            OPENSDK_ENCAUDIO_EVENT* audEvent;            
            debug_message("Event Type: OPENSDK_MEDIA_AUDIO\n");
            audEvent = (OPENSDK_ENCAUDIO_EVENT*) pData;
            //Process encoded audio
            break;
        }
        case OPENSDK_RECORDED_VIDEO:
        {
            OPENSDK_ENCVIDEO_EVENT* vidEvent;            
            debug_message("Event Type: OPENSDK_MEDIA_VIDEO\n");
            vidEvent = (OPENSDK_ENCVIDEO_EVENT*) pData;
            //Process encoded video
            break;
        }
        case OPENSDK_NEW_CLIENT:
        {
            OPENSDK_NETWORK_CLIENT* client;
            client = (OPENSDK_NETWORK_CLIENT*) pData;
            debug_message("Event Type: OPENSDK_NEW_CLIENT\n");
            debug_message("Client IP: %s, port: %d ID: %d\n", 
                    client->ip_address, client->port, client->client_id);            
            break;
        }
        case OPENSDK_NETWORK_DATA:
        {
            OPENSDK_NETWORK_PACKET* packet;            
            debug_message("Event Type: OPENSDK_NETWORK_DATA\n");            
            packet = (OPENSDK_NETWORK_PACKET*) pData;           
            break;
        } 
        case OPENSDK_CLIENT_CLOSED:
        {
            int* client_id;
            debug_message("Event Type: OPENSDK_CLIENT_CLOSED\n"); 
            
            client_id = (int*) pData;  
            debug_message("Client ID: %d\n", *client_id); 
            break;
        }
        case OPENSDK_MD_EVENT:
        {
            OPENSDK_VA_EVENTS* mdEvent;            
            mdEvent = (OPENSDK_VA_EVENTS*) pData;

            if(mdEvent->State) {
                debug_message("Event Type: OPENSDK_MD_EVENT ON\n");
            } else {
                debug_message("Event Type: OPENSDK_MD_EVENT OFF\n");
            }
            break;
        }
        case OPENSDK_FD_EVENT:
        {
            OPENSDK_VA_EVENTS* fdEvent;
            fdEvent = (OPENSDK_VA_EVENTS*) pData;

            if(fdEvent->State) {
                debug_message("Event Type: OPENSDK_FD_EVENT ON\n");
            } else {
                debug_message("Event Type: OPENSDK_FD_EVENT OFF\n");
            }
            break;
        }
        case OPENSDK_TAMP_EVENTS:
        {
            OPENSDK_VA_EVENTS* tampEvent;
            tampEvent = (OPENSDK_VA_EVENTS*) pData;

            if(tampEvent->State) {
                debug_message("Event Type: OPENSDK_TAMP_EVENT ON\n");
            } else {
                debug_message("Event Type: OPENSDK_TAMP_EVENT OFF\n");
            }
            break;
        }
        case OPENSDK_IV_PASSING_EVENT:
        {
            OPENSDK_VIDEOANALYTIC_EVENT* vaEvent;
            vaEvent = (OPENSDK_VIDEOANALYTIC_EVENT*) pData;
            debug_message("Event Type: LINE ACTION %d\n",vaEvent->Action);
			break;
        }
	case OPENSDK_ENTER_EXIT_EVENT:
        {
            OPENSDK_VIDEOANALYTIC_EVENT* vaEvent;
            vaEvent = (OPENSDK_VIDEOANALYTIC_EVENT*) pData;
            debug_message("Event Type: AREA ACTION %d\n",vaEvent->Action);
			break;
        }
	case OPENSDK_AD_EVENT:
        {
            OPENSDK_VIDEOANALYTIC_EVENT* adEvent;
            adEvent = (OPENSDK_VIDEOANALYTIC_EVENT*) pData;
            debug_message("Event Type: OPENSDK_AD_EVENT \n");
            break;
        }
        case OPENSDK_ALARM_EVENT:
        {
            OPENSDK_VA_EVENTS* alarmEvent;
            alarmEvent = (OPENSDK_VA_EVENTS*) pData;

            if(alarmEvent->Level) {
                debug_message("Event Type: OPENSDK_ALARM_EVENT ON\n");
            } else {
                debug_message("Event Type: OPENSDK_ALARM_EVENT OFF\n");
            }
            break;
        }
        case OPENSDK_SDCARD_INSERTED:
        {
            debug_message("Event Type: OPENSDK_SDCARD_INSERTED\n");
            break;
        }
        case OPENSDK_SDCARD_REMOVED:
        {
            debug_message("Event Type: OPENSDK_SDCARD_REMOVED\n");
            break;
        }
        case OPENSDK_NETWORK_CONNECTED:
        {
            debug_message("Event Type: OPENSDK_NETWORK_CONNECTED\n");
            break;
        }
        case OPENSDK_NETWORK_DISCONNECTED:
        {
            debug_message("Event Type: OPENSDK_NETWORK_DISCONNECTED\n");
            break;
        }
        case OPENSDK_CPU_USAGE_HIGH:
        {
            debug_message("Event Type: OPENSDK_CPU_USAGE_HIGH\n");
            break;
        }
        case OPENSDK_MEMORY_USAGE_HIGH:
        {
            debug_message("Event Type: OPENSDK_MEMORY_USAGE_HIGH\n");
            break;
        }
        case OPENSDK_CPU_MEMORY_USAGE_HIGH:
        {
            debug_message("Event Type: OPENSDK_CPU_MEMORY_USAGE_HIGH\n");
            break;
        }
        case OPENSDK_NETWORK_BANDWIDTH_HIGH:
        {
            debug_message("Event Type: OPENSDK_NETWORK_BANDWIDTH_HIGH\n");
            break;
        }
        case OPENSDK_DISK_USAGE_HIGH:
        {
            debug_message("Event Type: OPENSDK_DISK_USAGE_HIGH\n");
            break;
        }
        case OPENSDK_STOP_APP_CMD:
        {
            debug_message("Event Type: OPENSDK_STOP_APP_CMD\n");
            break;
        }
        case OPENSDK_NOTIFY:
        {
            debug_message("Event Type: OPENSDK_MESSAGE\n");
            break;
        }
        case OPENSDK_NETWORK_INTERFACE:
        {
            debug_message("Event Type: OPENSDK_NETWORK_INTERFACE\n");
            break;
        }
        case OPENSDK_NETWORK_PORTS:
        {
            debug_message("Event Type: OPENSDK_NETWORK_PORTS\n");
            break;
        }
        case OPENSDK_VIDEO_PROFILE:
        {
            debug_message("Event Type: OPENSDK_VIDEO_PROFILE\n");
            break;
        }
        case OPENSDK_MEDIA_CONFIG:
        {
            debug_message("Event Type: OPENSDK_MEDIA_CONFIG\n");
            break;
        }
        case OPENSDK_IMAGE_CONFIG:
        {
            debug_message("Event Type: OPENSDK_IMAGE_CONFIG\n");
            break;
        }
        case OPENSDK_STORAGE:
        {
            debug_message("Event Type: OPENSDK_STORAGE\n");
            break;
        }
        case OPENSDK_EVENT_CONFIG:
        {
            debug_message("Event Type: OPENSDK_EVENT_CONFIG\n");
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
	MJPEGSERVER* pServer;
	OPENSDK_NETWORK_CONFIG networkconfig;
	char* portNo;
	int len;
	bool flag;

	debug_message("one_shot\n");

	//Initialize local variable
	flag = false;
	pServer = MJPEGSERVER::create_instance();
	portNo = new char[MAX_PORT_NO_LEN];

	//Get port number from config file
	if (portNo && pServer)
	{
		//Get the port value from config file
		len = OPENSDK::SETTINGS::read_keyValue("portNo", 10, portNo);

		if (len > MAX_PORT_NO_LEN)
		{
			//Setting value len greater than allocated memory
			//Reallocate memory
			delete[] portNo;
			portNo = new char[len];

			//Get the port value from config file
			if (portNo)
			{
				len = OPENSDK::SETTINGS::read_keyValue("portNo", len, portNo);
				flag = true;
			}
		}
		else
		{
			flag = true;
		}
	}

	//Start the server push mjpeg service
	if (flag == true)
	{
		networkconfig.socketType = OPENSDK_TCP;
		networkconfig.serviceType = OPENSDK_SERVER;
		networkconfig.ipAddress = NULL;
		networkconfig.portNo = atoi(portNo);

		debug_message("portNo: %d\n", networkconfig.portNo);

		//Start network service
		OPENSDK::EVENT::send_event(OPENSDK_START_SERVICE, NULL,
				(void*) &networkconfig, sizeof(networkconfig));
	}
	else
	{
		debug_message("Error in starting application\n");
		//Stop application
		OPENSDK::EVENT::send_event(OPENSDK_STOP_APPLICATION, NULL, NULL, 0);
	}

	//Free the memory
	if (portNo)
	{
		delete[] portNo;
		portNo = NULL;
	}

	return;
}


