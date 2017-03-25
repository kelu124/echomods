/**
******************************************************************************
* @file    MICOConfigMenu.c 
* @author  William Xu
* @version V1.0.0
* @date    05-May-2014
* @brief   This file provide function for createing configration menu that can 
*          be displayed on EasyLink APP on iOS or Android.
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

#include "Debug.h"
#include "JSON-C/json.h"
#include "MICOConfigMenu.h"

OSStatus MICOAddSector(json_object* sectors, char* const name,  json_object *menus)
{
  OSStatus err;
  json_object *object;
  err = kNoErr;

  object = json_object_new_object();
  require_action(object, exit, err = kNoMemoryErr);
  json_object_object_add(object, "N", json_object_new_string(name));      
  json_object_object_add(object, "C", menus);
  json_object_array_add(sectors, object);

exit:
  return err;
}

OSStatus MICOAddStringCellToSector(json_object* menus, char* const name,  char* const content, char* const privilege, json_object* secectionArray)
{
  OSStatus err;
  json_object *object;
  err = kNoErr;

  object = json_object_new_object();
  require_action(object, exit, err = kNoMemoryErr);
  json_object_object_add(object, "N", json_object_new_string(name));      
  json_object_object_add(object, "C", json_object_new_string(content));
  json_object_object_add(object, "P", json_object_new_string(privilege)); 

  if(secectionArray)
    json_object_object_add(object, "S", secectionArray); 

  json_object_array_add(menus, object);


exit:
  return err;
}

OSStatus MICOAddNumberCellToSector(json_object* menus, char* const name,  int content, char* const privilege, json_object* secectionArray)
{
  OSStatus err;
  json_object *object;
  err = kNoErr;

  object = json_object_new_object();
  require_action(object, exit, err = kNoMemoryErr);
  json_object_object_add(object, "N", json_object_new_string(name));      

  json_object_object_add(object, "C", json_object_new_int(content));
  json_object_object_add(object, "P", json_object_new_string(privilege)); 

  if(secectionArray)
    json_object_object_add(object, "S", secectionArray); 

  json_object_array_add(menus, object);

exit:
  return err;
}

OSStatus MICOAddFloatCellToSector(json_object* menus, char* const name,  float content, char* const privilege, json_object* secectionArray)
{
  OSStatus err;
  json_object *object;
  err = kNoErr;

  object = json_object_new_object();
  require_action(object, exit, err = kNoMemoryErr);
  json_object_object_add(object, "N", json_object_new_string(name));      

  json_object_object_add(object, "C", json_object_new_double(content));
  json_object_object_add(object, "P", json_object_new_string(privilege)); 

  if(secectionArray)
    json_object_object_add(object, "S", secectionArray); 

  json_object_array_add(menus, object);

exit:
  return err;  
}


OSStatus MICOAddSwitchCellToSector(json_object* menus, char* const name,  boolean switcher, char* const privilege)
{
  OSStatus err;
  json_object *object;
  err = kNoErr;

  object = json_object_new_object();
  require_action(object, exit, err = kNoMemoryErr);
  json_object_object_add(object, "N", json_object_new_string(name));      
  json_object_object_add(object, "C", json_object_new_boolean(switcher));
  json_object_object_add(object, "P", json_object_new_string(privilege)); 
  json_object_array_add(menus, object);

exit:
  return err;
}

OSStatus MICOAddMenuCellToSector(json_object* menus, char* const name, json_object* lowerSectors)
{
  OSStatus err;
  json_object *object;
  err = kNoErr;

  object = json_object_new_object();
  require_action(object, exit, err = kNoMemoryErr);
  json_object_object_add(object, "N", json_object_new_string(name));
  json_object_object_add(object, "C", lowerSectors);
  json_object_array_add(menus, object);

exit:
  return err;
}

OSStatus MICOAddTopMenu(json_object **outTopMenu, char* const inName, json_object* sectors, OTA_Versions_t inVersions)
{
  OSStatus err;
  json_object *object;
  err = kNoErr;
  require_action(inVersions.protocol, exit, err = kParamErr);
  require_action(inVersions.hdVersion, exit, err = kParamErr);
  require_action(inVersions.fwVersion, exit, err = kParamErr);

  object = json_object_new_object();
  require_action(object, exit, err = kNoMemoryErr);
  json_object_object_add(object, "T", json_object_new_string("Current Configuration"));
  json_object_object_add(object, "N", json_object_new_string(inName));
  json_object_object_add(object, "C", sectors);

  json_object_object_add(object, "PO", json_object_new_string(inVersions.protocol));
  json_object_object_add(object, "HD", json_object_new_string(inVersions.hdVersion));
  json_object_object_add(object, "FW", json_object_new_string(inVersions.fwVersion));
  if(inVersions.rfVersion)
    json_object_object_add(object, "RF", json_object_new_string(inVersions.rfVersion));
 
  *outTopMenu = object;
exit:
  return err;
}

