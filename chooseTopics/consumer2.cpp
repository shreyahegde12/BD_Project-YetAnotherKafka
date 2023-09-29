#include <iostream>                                                                                                                            
#include <thread>
#include <string>
#include "Topic.h"
#include "consumer2.h"
#include "broker.h"
   
using namespace std;
key_t consumer2::key =0;
int consumer2::msgid =0;
   
   
consumer2::consumer2(broker* brk,string cons_name,int topicNo)
{
   
   key = ftok(cons_name.c_str(), 65);
   msgid = msgget(key, 0666 | IPC_CREAT);
   
   Topic* top = new Topic(cons_name,topicNo);
   brk->register_topic(topicNo,top);

   //thread consumer_thread(run, 3);
  // consumer_thread.join();
}
int consumer2::run(int thrNo)
{
    message msg;
    for(;;)
    {
        //Receive Messages from Broker
        //cout << "Consumer2 Waiting to receive Message " << endl;
        msgrcv(msgid, &msg, sizeof(message), 50, 0);
        cout << "CONSUMER2 data received: " <<  msg.mesg_text << endl;
    }

}
consumer2::~consumer2()
{
}
