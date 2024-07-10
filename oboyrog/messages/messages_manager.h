#ifndef __MESSAGE_MANAGER_H__
#define __MESSAGE_MANAGER_H__

#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "message.h"

#include "../constants.h"


typedef struct MessagesList {
    Message* msgs[50]; // Only the last X will be displayed
    int idx;
    int nb_msgs;
    bool is_full;
} MessagesList;

MessagesList* get_msgs_lst();
void add_msg(MessagesList* msg_lst, char* str);

#endif