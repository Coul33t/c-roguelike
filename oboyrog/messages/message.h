#ifndef __MESSAGE_H__
#define __MESSAGE_H__

#include <stdlib.h>

typedef struct Message {
    char* msg;
    int size;
} Message;

void free_msg(Message* msg);

#endif
