#ifndef _SSI_H
#define _SSI_H

#include <stdint.h>
#include "lwip/apps/httpd.h"

/**
 * SSI handler. Function handles SSI requests.
 * 
 * @param iIndex: index of the SSI handler
 * @param pcInsert: array of inserts
 * @param iInsertLen: length of the insert
 * @return: length of the insert value
 */
u16_t ssi_handler(int iIndex, char *pcInsert, int iInsertLen);

/**
 * SSI init. Function initializes SSI handler and respective SSI tags.
 */
void ssi_init();

#endif
