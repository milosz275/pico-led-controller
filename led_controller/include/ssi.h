#ifndef _SSI_H
#define _SSI_H

#include <stdint.h>
#include "lwip/apps/httpd.h"

u16_t ssi_handler(int iIndex, char *pcInsert, int iInsertLen);

void ssi_init();

#endif
