#include "broker.h"
#include "Topic.h"
#include <thread>

key_t broker::key =0;
int broker::msgid =0;
std::map<int,Topic*> broker::consumerMap;

broker::broker()
{
    key = ftok("producer", 65);
    msgid = msgget(key, 0666 | IPC_CREAT);
   // thread broker_thread(run, 2);
    //broker_thread.join();

}
int broker::run(int thrNo)
{

    Message msg;
    for(;;)
    {  
        cout << "Broker Waiting for Message " << endl;
        msgrcv(msgid, &msg, sizeof(message), 25, 0);
        cout << "Broker received Message" << endl;

        map<int,Topic*>::iterator iter = consumerMap.find(msg.mesg_type);
        if(iter != consumerMap.end())
        {                                                                                                                                      
            cout << "Found the consumer, Sending Message to Consumer" << endl;
            (iter->second)->SendMessage(msg);
        }
        else
        {
            cout << "Topic Not found " << endl;
            cout << "Topic Not Registered " << endl;
        }

    }
}
void broker::register_topic(int topNo, Topic* top)
{
    consumerMap.insert(pair<int, Topic*>(topNo,top));
}
broker::~broker()
{
}
