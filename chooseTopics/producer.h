#include <iostream>
#include <stdio.h>                                                                                                                            
#include <sys/ipc.h>
#include <sys/msg.h>
#include <string>
#include "broker.h"

#define MAX 100

class producer
{
    public:
    static key_t key;
    static int msgid;
    static broker* brk;
typedef    struct mesg_buffer {
    long mesg_type;
    char mesg_text[100];
} message;


    producer(broker* brok);
    ~producer();

    static int run(int thrNo);

};
