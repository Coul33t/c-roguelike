#include "message.h"

void free_msg(Message* msg) {
    free(msg->msg);
    free(msg);
}
