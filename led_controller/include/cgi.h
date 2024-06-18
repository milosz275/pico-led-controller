#ifndef _CGI_H
#define _CGI_H

#include <stdio.h>
#include "lwip/apps/httpd.h"

const char* cgi_onboard_led_handler(int iIndex, int iNumParams, char* pcParam[], char* pcValue[]);
const char* cgi_led_handler(int iIndex, int iNumParams, char* pcParam[], char* pcValue[]);
const char* cgi_led_mode_handler(int iIndex, int iNumParams, char* pcParam[], char* pcValue[]);
const char* cgi_favicon_handler(int iIndex, int iNumParams, char* pcParam[], char* pcValue[]);
const char* cgi_m_icon_handler(int iIndex, int iNumParams, char* pcParam[], char* pcValue[]);
const char* cgi_manifest_handler(int iIndex, int iNumParams, char* pcParam[], char* pcValue[]);
const char* cgi_data_handler(int iIndex, int iNumParams, char* pcParam[], char* pcValue[]);
const char* cgi_timestamp_handler(int iIndex, int iNumParams, char* pcParam[], char* pcValue[]);

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

void cgi_init();

#endif
