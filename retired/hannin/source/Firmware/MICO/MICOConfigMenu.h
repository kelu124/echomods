/**
******************************************************************************
* @file    MICOConfigMenu.h 
* @author  William Xu
* @version V1.0.0
* @date    05-May-2014
* @brief   This file provide function prototypes for createing configration 
*      menu that can be displayed on EasyLink APP on iOS or Android.
******************************************************************************
*
*  The MIT License
*  Copyright (c) 2014 MXCHIP Inc.
*
*  Permission is hereby granted, free of charge, to any person obtaining a copy 
*  of this software and associated documentation files (the "Software"), to deal
*  in the Software without restriction, including without limitation the rights 
*  to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
*  copies of the Software, and to permit persons to whom the Software is furnished
*  to do so, subject to the following conditions:
*
*  The above copyright notice and this permission notice shall be included in
*  all copies or substantial portions of the Software.
*
*  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR 
*  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, 
*  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE 
*  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
*  WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR 
*  IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
******************************************************************************
*/

#ifndef __MICOCONFIGMENU_H
#define __MICOCONFIGMENU_H

#include "Common.h"
#include "JSON-C/json.h"

typedef struct {
  char*  protocol;
  char*  hdVersion;
  char*  fwVersion;
  char*  rfVersion;
} OTA_Versions_t;


OSStatus MICOAddSector(json_object* sectors, char* const name,  json_object *menus);

OSStatus MICOAddStringCellToSector(json_object* menus, char* const name,  char* const content, char* const privilege, json_object* secectionArray);

OSStatus MICOAddNumberCellToSector(json_object* menus, char* const name,  int content, char* const privilege, json_object* secectionArray);

OSStatus MICOAddFloatCellToSector(json_object* menus, char* const name,  float content, char* const privilege, json_object* secectionArray);

OSStatus MICOAddSwitchCellToSector(json_object* menus, char* const name,  boolean content, char* const privilege);

OSStatus MICOAddMenuCellToSector(json_object* menus, char* const name, json_object* lowerSectors);

OSStatus MICOAddTopMenu(json_object **deviceInfo, char* const name, json_object* sectors, OTA_Versions_t versions);

#endif
