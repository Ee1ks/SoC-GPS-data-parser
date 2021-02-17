#ifndef _SERVER_H_
#define _SERVER_H_

#include <stdio.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include "../inc/utils.h"

void open_server(unsigned char *ram_addr);

#endif