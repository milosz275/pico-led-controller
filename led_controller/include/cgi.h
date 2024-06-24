#ifndef _CGI_H
#define _CGI_H

#include <stdio.h>
#include <httpd.h>
#include "lwip/apps/httpd.h"

/**
 * CGI onboard LED handler. Function handles CGI requests for the onboard LED.
 * 
 * @param iIndex: index of the CGI handler
 * @param iNumParams: number of parameters
 * @param pcParam: array of parameters
 * @param pcValue: array of values
 * @return: redirect URL
 */
const char* cgi_onboard_led_handler(int iIndex, int iNumParams, char* pcParam[], char* pcValue[]);

/**
 * CGI LED handler. Function handles CGI requests for the LED strip.
 * 
 * @param iIndex: index of the CGI handler
 * @param iNumParams: number of parameters
 * @param pcParam: array of parameters
 * @param pcValue: array of values
 * @return: redirect URL
 */
const char* cgi_led_handler(int iIndex, int iNumParams, char* pcParam[], char* pcValue[]);

/**
 * CGI LED mode handler. Function handles CGI requests for the LED strip mode.
 * 
 * @param iIndex: index of the CGI handler
 * @param iNumParams: number of parameters
 * @param pcParam: array of parameters
 * @param pcValue: array of values
 * @return: redirect URL
 */
const char* cgi_led_mode_handler(int iIndex, int iNumParams, char* pcParam[], char* pcValue[]);

/**
 * CGI favicon handler. Function handles CGI requests for the favicon.
 * 
 * @param iIndex: index of the CGI handler
 * @param iNumParams: number of parameters
 * @param pcParam: array of parameters
 * @param pcValue: array of values
 * @return: redirect URL
 */
const char* cgi_favicon_handler(int iIndex, int iNumParams, char* pcParam[], char* pcValue[]);

/**
 * CGI m icon handler. Function handles CGI requests for the m icon.
 * 
 * @param iIndex: index of the CGI handler
 * @param iNumParams: number of parameters
 * @param pcParam: array of parameters
 * @param pcValue: array of values
 * @return: redirect URL
 */
const char* cgi_m_icon_handler(int iIndex, int iNumParams, char* pcParam[], char* pcValue[]);

/**
 * CGI manifest handler. Function handles CGI requests for the manifest.
 * 
 * @param iIndex: index of the CGI handler
 * @param iNumParams: number of parameters
 * @param pcParam: array of parameters
 * @param pcValue: array of values
 * @return: redirect URL
 */
const char* cgi_manifest_handler(int iIndex, int iNumParams, char* pcParam[], char* pcValue[]);

/**
 * CGI data handler. Function handles CGI requests for the data.
 * 
 * @param iIndex: index of the CGI handler
 * @param iNumParams: number of parameters
 * @param pcParam: array of parameters
 * @param pcValue: array of values
 * @return: redirect URL
 */
const char* cgi_data_handler(int iIndex, int iNumParams, char* pcParam[], char* pcValue[]);

/**
 * CGI timestamp handler. Function handles CGI requests for the timestamp.
 * 
 * @param iIndex: index of the CGI handler
 * @param iNumParams: number of parameters
 * @param pcParam: array of parameters
 * @param pcValue: array of values
 * @return: redirect URL
 */
const char* cgi_timestamp_handler(int iIndex, int iNumParams, char* pcParam[], char* pcValue[]);

/**
 * CGI handlers. Array of CGI handlers with endpoint and handler function.
 */
static const tCGI cgi_handlers[] =
{
    { "/onboard_led", cgi_onboard_led_handler },
    { "/led", cgi_led_handler },
    { "/mode", cgi_led_mode_handler },
    { "/favicon.ico", cgi_favicon_handler },
    { "/m.png", cgi_m_icon_handler },
    { "/manifest.json", cgi_manifest_handler },
    { "/data.shtml", cgi_data_handler },
    { "/timestamp.shtml", cgi_timestamp_handler },
    { NULL, NULL }
};

/**
 * Initialize CGI handlers. Function initializes the CGI handling and respective handlers.
 */
void cgi_init();

#endif
