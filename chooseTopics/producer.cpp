#include <iostream>                                                                                                                            
#include "producer.h"
#include <thread>
#include <string.h>
#include <unistd.h>
#include "broker.h"

using namespace std;
key_t producer::key =0;
int producer::msgid =0;
broker* producer::brk;

producer::producer(broker* brok)
{
   key = ftok("producer", 65);
   msgid = msgget(key, 0666 | IPC_CREAT);
   brk = brok;
   //std::thread prod_thread(run,1);
   //prod_thread.join();
}
int producer::run(int thrNo)
{
    message msg;
    int choice;
    string topic_name;
    string mesg;
    string text;

    for(;;)
    {  
        cout << "1. Create Topic" << endl;
        cout << "2. Send Msg To Broker " << endl;
        cout << "3. List Topics in Broker " << endl;
        cin >> choice;

        switch(choice)
        {
            case 1:
                cout << " Enter Topic Name " << endl;
                cin >> topic_name;
                brk->CreateTopic(topic_name);
                break;
            case 2:
                cout <<endl<< "Enter Message1 to send: " << endl;
                fflush(stdin);
                cin>>text;
                break;
            case 3:
                brk->getTopics();
                break;
            default:
                cout << "Wrong Choice " << endl;
                continue;
        }

       if(choice==2){

        //Send Messages to Broker
        msg.mesg_type = 25;
      
        strcpy(msg.mesg_text,text.c_str());
	cout<<endl;

        cout << "Sending Message to Broker" << endl;
         // msgsnd to send message
         msgsnd(msgid, &msg, sizeof(message), 0);
         sleep(5);
         msg.mesg_type = 50;
         cout << "Enter Message2 to send: " << endl;
         cin>>text;
         strcpy(msg.mesg_text,text.c_str());
        cout << "Sending Message to Broker for C2" << endl;
         msgsnd(msgid, &msg, sizeof(message), 0);
         sleep(5);
       }

    }

}
producer::~producer(){}
