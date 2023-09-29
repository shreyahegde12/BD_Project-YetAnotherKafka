#include <iostream>
#include <stdio.h>                                                                                                                            
#include <sys/ipc.h>
#include <sys/msg.h>
#include <string>

#define MAX 100

class producer
{
    public:
    static key_t key;
    static int msgid;
typedef    struct mesg_buffer {
    long mesg_type;
    char mesg_text[100];
} message;


    producer();
    ~producer();

    static int run(int thrNo);

};
