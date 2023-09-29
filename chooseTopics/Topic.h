#ifndef TOPIC_H
#define TOPIC_H                                                                                                                                

#include <iostream>
#include <stdio.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#define MAX 100

using namespace std;

typedef struct mesg_buffer {
    long mesg_type;
    char mesg_text[100];
} Message;
class Topic
{
    public:
    key_t key;
    int msgid;
    int topicId;
    Topic(string cons_name,int topic_id)
    {  
        topicId = topic_id;
        // ftok to generate unique key
        key = ftok(cons_name.c_str(), 65);
        msgid = msgget(key, 0666 | IPC_CREAT);
    }  
 // structure for message queue                                                                                                                
typedef struct mesg_buffer {
    long mesg_type;
    char mesg_text[100];
} message;

void SendMessage(Message &msg)
{


    // msgget creates a message queue
    // and returns identifier
    msg.mesg_type = topicId;

    // msgsnd to send message
    msgsnd(msgid, &msg, sizeof(message), 0);

    // display the message
    cout <<endl<< "Data sent is : " <<  msg.mesg_text << endl;

    return;
}
};
#endif
