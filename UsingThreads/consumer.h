#include <iostream>                                                                                                                            
#include "broker.h"

class consumer
{
    public:
    static key_t key;
    static int msgid;

    typedef struct mesg_buffer {
    long mesg_type;
    char mesg_text[100];
    } message;

    consumer(broker* brk,string cons_name,int topicNo);
    ~consumer();

    static int run(int thrNo);

};
