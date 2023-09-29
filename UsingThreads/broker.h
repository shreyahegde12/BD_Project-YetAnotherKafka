#ifndef BROKER_H                                                                                                                              
#define BROKER_H
#include <iostream>
#include "Topic.h"
#include <map>

class broker
{
    public:
    static key_t key;
    static int msgid;
    typedef struct mesg_buffer {
    long mesg_type;
    char mesg_text[100];
    } message;

    static std::map<int, Topic*> consumerMap;
    broker();
    ~broker();

    static int run(int thrNo);
    void register_topic(int topNo,Topic* top);

};
#endif
