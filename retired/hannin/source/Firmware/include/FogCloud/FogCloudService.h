/**
******************************************************************************
* @file    FogCloudService.h 
* @author  Eshen Wang
* @version V0.2.0
* @date    23-Nov-2014
* @brief   This header contains interfaces of FogCloud service.
  operation
******************************************************************************
* @attention
*
* THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
* WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
* TIME. AS A RESULT, MXCHIP Inc. SHALL NOT BE HELD LIABLE FOR ANY
* DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
* FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
* CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
*
* <h2><center>&copy; COPYRIGHT 2014 MXCHIP Inc.</center></h2>
******************************************************************************
*/ 

#ifndef __FOGCLOUD_SERVICE_H_
#define __FOGCLOUD_SERVICE_H_

#include "FogCloudServiceDef.h"
#include "FogCloudUtils.h"

/*******************************************************************************
 * INTERFACES
 ******************************************************************************/

OSStatus FogCloudServiceInit(easycloud_service_context_t* const context);
OSStatus FogCloudServiceStart(easycloud_service_context_t* const context);  //start thread

easycloud_service_state_t FogCloudServiceState(easycloud_service_context_t* const context);

OSStatus FogCloudActivate(easycloud_service_context_t* const context);
OSStatus FogCloudAuthorize(easycloud_service_context_t* const context);

OSStatus FogCloudPublish(easycloud_service_context_t* const context, 
                          const unsigned char *msg, unsigned int msgLen);
// publish to any topic
OSStatus FogCloudPublishto(easycloud_service_context_t* const context, 
                            const char* topic, 
                            const unsigned char *msg, unsigned int msgLen);
// publish to sub-level "device_id/in/<level>"
OSStatus FogCloudPublishtoChannel(easycloud_service_context_t* const context, 
                            const char* channel, 
                            const unsigned char *msg, unsigned int msgLen);

OSStatus FogCloudGetLatestRomVersion(easycloud_service_context_t* const context); //get rom version
OSStatus FogCloudGetRomData(easycloud_service_context_t* const context,
                             ecs_ota_flash_params_t ota_flash_params); //get rom data && write to flash

OSStatus FogCloudDeviceReset(easycloud_service_context_t* const context);

OSStatus FogCloudServiceStop(easycloud_service_context_t* const context);
OSStatus FogCloudServiceDeInit(easycloud_service_context_t* const context);

int FogCloudServiceVersion(easycloud_service_context_t* const context);

#endif
