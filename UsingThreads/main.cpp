#include "producer.h"                                                                                                                          
#include "consumer.h"
#include "consumer2.h"
#include "broker.h"
#include <thread>


using namespace std;

int main()
{
    cout << "Creating Broker " << endl;
    broker*   brok = new broker();
    thread broker_thread(broker::run,1);
    cout << "Creating consumer " << endl;

    consumer* cons  = new consumer(brok,"consumer1",25);
    thread consumer_thread(consumer::run,2);

    consumer2* cons2  = new consumer2(brok,"consumer2",50);
    thread consumer2_thread(consumer2::run,3);

    cout << "Creating producer " << endl;
    producer* prod = new producer();
    thread producer_thread(producer::run,4);

    broker_thread.join();
    consumer_thread.join();
    consumer2_thread.join();
    producer_thread.join();

}
