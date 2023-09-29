#include <iostream>                                                                                                                            
#include "producer.h"
#include <thread>
#include <string.h>
#include <unistd.h>

using namespace std;
key_t producer::key =0;
int producer::msgid =0;
producer::producer()
{  
   key = ftok("producer", 65);
   msgid = msgget(key, 0666 | IPC_CREAT);
   //std::thread prod_thread(run,1);
   //prod_thread.join();
}  
int producer::run(int thrNo)
{
    message msg;
    string text;
    for(;;)
    {
        //Send Messages to Broker
        msg.mesg_type = 25;
        cout<<endl;
        cout<<"Enter message1 to send: ";
        getline(cin,text);
        strcpy(msg.mesg_text,text.c_str());


        cout << "Sending Message1 to Broker" << endl;
         // msgsnd to send message
         msgsnd(msgid, &msg, sizeof(message), 0);
         sleep(5);
         msg.mesg_type = 50;
         cout<<endl;
         cout<<"Enter message2 to send"<<endl;
         getline(cin,text);
         strcpy(msg.mesg_text,text.c_str());
         cout << "Sending Message2 to Broker" << endl;
         msgsnd(msgid, &msg, sizeof(message), 0);
         sleep(5);

    }

}
producer::~producer()
{
}
