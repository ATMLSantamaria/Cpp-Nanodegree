#include <iostream>
#include <random>
#include "TrafficLight.h"

/* Implementation of class "MessageQueue" */


template <typename T>
T MessageQueue<T>::receive()
{
    // FP.5a : The method receive should use std::unique_lock<std::mutex> and _condition.wait() 
    // to wait for and receive new messages and pull them from the queue using move semantics. 
    // The received object should then be returned by the receive function. 
    // 1 - lock to protect against other threads
    std::unique_lock<std::mutex> lck(_mtx_msg_queue);
    // 2 - receive notification
    _cond_var_msg_queue.wait(lck,[this]{ return !_queue.empty();});
    // 3 - Take from queue
    T msg = std::move(_queue.back());
    // 4 - Erase last element
    _queue.pop_back();
    return msg;
}

template <typename T>
void MessageQueue<T>::send(T &&msg)
{
    // FP.4a : The method send should use the mechanisms std::lock_guard<std::mutex> 
    // as well as _condition.notify_one() to add a new message to the queue and afterwards send a notification.
    //Lock so only one thread access
    std::lock_guard<std::mutex> lck(_mtx_msg_queue);
    //move semantics in msg
    _queue.emplace_back(std::move(msg));
    //or .push_bach()
    //notify
    _cond_var_msg_queue.notify_one();

}


/* Implementation of class "TrafficLight" */

 
TrafficLight::TrafficLight()
{
    _currentPhase = TrafficLightPhase::red;
}

void TrafficLight::waitForGreen()
{
    // FP.5b : add the implementation of the method waitForGreen, in which an infinite while-loop 
    // runs and repeatedly calls the receive function on the message queue. 
    // Once it receives TrafficLightPhase::green, the method returns.

    TrafficLightPhase current_phase;
    while(true){
        std::this_thread::sleep_for(std::chrono::milliseconds(1));
        if(_semaphoro_queue.receive() == TrafficLightPhase::green){
            return;
        } 
    }
}

TrafficLightPhase TrafficLight::getCurrentPhase()
{
    return _currentPhase;
}

void TrafficLight::simulate()
{
    // FP.2b : Finally, the private method „cycleThroughPhases“ should be started in a thread when the public method „simulate“ is called. To do this, use the thread queue in the base class. 
     threads.emplace_back(std::thread(&TrafficLight::cycleThroughPhases, this));
}


// virtual function which is executed in a thread
void TrafficLight::cycleThroughPhases()
{
    // FP.2a : Implement the function with an infinite loop that measures the time between two loop cycles 
    // and toggles the current phase of the traffic light between red and green and sends an update method 
    // to the message queue using move semantics. The cycle duration should be a random value between 4 and 6 seconds. 
    // Also, the while-loop should use std::this_thread::sleep_for to wait 1ms between two cycles.

    //Init the cycle
    auto start = std::chrono::high_resolution_clock::now();

    std::uniform_real_distribution<double> unif(4000,6000);
    std::default_random_engine re;
    double rndm = unif(re);
    while(true){
        //Reduce CPU load
        std::this_thread::sleep_for(std::chrono::milliseconds(1));; 

        auto end = std::chrono::high_resolution_clock::now();

        auto elapsed_time_ms = std::chrono::duration<double, std::milli>(end-start).count();
        
        if (elapsed_time_ms > (4000+rndm)){
            //Change light from green to red or red to green
            _currentPhase = static_cast<TrafficLightPhase>(((int)_currentPhase+1)%2);
            //std::cout << "CUrrent phase: " << _currentPhase << "\n";
            //Send update to message queue
            _semaphoro_queue.send(std::move(_currentPhase));
            //algo.send(std::move(_currentPhase));
            //Reset the cycle
            start = std::chrono::high_resolution_clock::now();
            std::default_random_engine re2;
            rndm = unif(re);
        }


    }
}

