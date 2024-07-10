#include "messages_manager.h"

MessagesList* get_msgs_lst() {
    MessagesList* msgs_lst = calloc(1, sizeof(MessagesList));
    msgs_lst->is_full = false;
    msgs_lst->idx = -1;
    msgs_lst->nb_msgs = 0;
    return msgs_lst;
}

void add_msg(MessagesList* msg_lst, char* str) {
    Message* msg = calloc(1, sizeof(Message));
    
    int size = 0;
    int idx = 0;

    while (str[idx] != '\0') {
        ++size;
        ++idx;
    }

    msg->size = size;
    msg->msg = calloc(1, msg->size * sizeof(char));
    strcpy(msg->msg, str);
    msg_lst->idx++;

    // Used in order to erase old messages and free the memory when doing so
    if (msg_lst->idx == MAX_MESSAGES) {
        if (!msg_lst->is_full) {
            msg_lst->is_full = true;
        }

        msg_lst->idx = 0;
    }

    // If the message list is full, free the message that's gonna be overwritten
    if (msg_lst->is_full) {
        free_msg(msg_lst->msgs[msg_lst->idx]);
    }

    msg_lst->msgs[msg_lst->idx] = msg;

    if (msg_lst->nb_msgs < MAX_MESSAGES) {
        msg_lst->nb_msgs += 1;
    }
}