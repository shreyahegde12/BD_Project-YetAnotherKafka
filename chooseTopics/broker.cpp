#include "broker.h"                                                                                                                            
#include "Topic.h"
#include <thread>

key_t broker::key =0;
int broker::msgid =0;
std::map<int,Topic*> broker::consumerMap;
vector<string> broker::topic_names;
broker::broker()
{  
    key = ftok("producer", 65);
    msgid = msgget(key, 0666 | IPC_CREAT);
   
    topic_names.push_back("Weather");
    topic_names.push_back("Temparature");
    topic_names.push_back("Games");
    topic_names.push_back("Stock");

   
}  
void broker::CreateTopic(string topic_name)
{
   topic_names.push_back(topic_name);
}  
void broker::getTopics()
{  
   for(int i=0;i<topic_names.size();i++)
   {
      cout << topic_names[i] << endl;
   }
}
int broker::run(int thrNo)
{

    Message msg;
    for(;;)
    {
        cout <<endl<< "Broker Waiting for Message " << endl;
        msgrcv(msgid, &msg, sizeof(message), 25, 0);
        cout << "Broker received Message" << endl;

        map<int,Topic*>::iterator iter = consumerMap.find(msg.mesg_type);
        if(iter != consumerMap.end())
        {
            cout << "Found the consumer Sending Message to Consumer" << endl;
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
