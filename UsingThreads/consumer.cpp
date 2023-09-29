#include <iostream>                                                                                                                            
#include <thread>
#include <string>
#include "Topic.h"
#include "consumer.h"
#include "broker.h"
   
using namespace std;
key_t consumer::key =0;
int consumer::msgid =0;
   
   
consumer::consumer(broker* brk,string cons_name,int topicNo)
{
   
   key = ftok(cons_name.c_str(), 65);
   msgid = msgget(key, 0666 | IPC_CREAT);
   
   Topic* top = new Topic(cons_name,topicNo);
   brk->register_topic(topicNo,top);

   //thread consumer_thread(run, 3);
  // consumer_thread.join();
}
int consumer::run(int thrNo)
{
    message msg;
    for(;;)
    {
        //Receive Messages from Broker
        cout << "Consumer Waiting to receive Message " << endl;
        msgrcv(msgid, &msg, sizeof(message), 25, 0);
        cout << "CONSUMER data received: " <<  msg.mesg_text << endl;
    }

}
consumer::~consumer()
{
}
