/*********************************************************************
 This is an example for our Feather WIFI modules
 Pick one up today in the adafruit shop!
 Adafruit invests time and resources providing this open source code,
 please support Adafruit and open-source hardware by purchasing
 products from Adafruit!
 MIT license, check LICENSE for more information
 All text above, and the splash screen below must be included in
 any redistribution
*********************************************************************/

/* This example scans for nearby networks and prints out the SSID
 * details every 10 seconds. Hidden SSIDs are printed as '*'.
 */

#include <adafruit_feather.h>

#define MAX_SCAN_NUM   20
wl_ap_info_t scan_result[MAX_SCAN_NUM];

/**************************************************************************/
/*!
    @brief  The setup function runs once when reset the board
*/
/**************************************************************************/
void setup()
{
  Serial.begin(115200);

  // wait for serial port to connect. Needed for native USB port only
  while (!Serial) delay(1);

  Serial.println("Network Scan Example\r\n");
}

/**************************************************************************/
/*!
    @brief  The loop function runs over and over again forever
*/
/**************************************************************************/
void loop()
{
  Serial.println();
  Serial.println("Scanning available networks...");
  listNetworks();

  Serial.println();
  Serial.println("Waiting 10 seconds before trying again");
  delay(10000);
}

/**************************************************************************/
/*!
    @brief  Scan and list avaialable network nearby
*/
/**************************************************************************/
void listNetworks()
{
  int numSsid = Feather.scanNetworks(scan_result, MAX_SCAN_NUM);

  // print the list of networks seen:
  Serial.print("Number of available networks:");
  Serial.println(numSsid);

  if (numSsid == 0) return;

  // print the network number and name for each network found:
  Serial.printf("ID SSID                 Enc   Ch Signal\n");
  for (int i = 0; i < numSsid; i++)
  {
    Serial.printf("%02d %-20s %-05s %02d %02d (dBm)",
                  i,
                  (scan_result[i].ssid[i] == 0) ? "*" : scan_result[i].ssid, // hidden SSID display as "*"
                  getEncryptionStr( scan_result[i].security ),
                  scan_result[i].channel,
                  scan_result[i].rssi);

    Serial.println();
  }
}

/**************************************************************************/
/*!
    @brief  Helper to print encryption type
*/
/**************************************************************************/
char const* getEncryptionStr(int32_t encType)
{
  // read the encryption type and print out the name:
  switch (encType)
  {
    case ENC_TYPE_WEP:
      return "WEP";
    break;

    case ENC_TYPE_WPA_TKIP:
    case ENC_TYPE_WPA_AES:
    case ENC_TYPE_WPA_MIXED:
      return "WPA";
    break;

    case ENC_TYPE_WPA2_AES:
    case ENC_TYPE_WPA2_TKIP:
    case ENC_TYPE_WPA2_MIXED:
      return "WPA2";
    break;

    case ENC_TYPE_OPEN:
      return "OPEN";
    break;

    default:
      return "OTHER";
    break;
  }
}
