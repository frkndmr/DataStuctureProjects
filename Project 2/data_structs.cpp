
#include <iostream>
#include <stdlib.h>
#include <string.h>
#include "data_structs.h"

using namespace std;


void Stack::init(){
    head = NULL;
}

bool Stack::isEmpty(){
    if(head==NULL){
        return true;
    }
    else{
        return false;
    }
}

bool Queue::isEmpty(){
    if(head==NULL){
        return true;
    }
    else{
        return false;
    }
}

void Stack::push(Subtask* in){
    Subtask* temp = new Subtask;
    temp->name = in->name;
    temp->duration = in->duration;
    temp->next = head;
    head = temp;
}

Subtask* Stack::pop(){
    if(isEmpty()){
        return NULL;
    }
    Subtask* temp = new Subtask;
    Subtask* topnode;
    topnode = head;
    head = head->next;
    temp->name = topnode->name;
    temp->duration = topnode->duration;
    delete topnode;
    return temp;
}


void Queue::init(){
    head = NULL;
    tail = NULL;
}

void Queue::queue(Process* in){
    Process* temp = new Process;
    temp->name = in->name;
    temp->arrival_time = in->arrival_time;
    temp->priority = in->priority;
    temp->task_count = in->task_count;
    temp->task_stack = in->task_stack;
    temp->deadline = in->deadline;
    temp->next = NULL;
    
    

    if(isEmpty()){
        tail = temp;
        head = tail;    
    }
    else{
        tail->next = temp;
        tail = temp; 
    }
}


Process* Queue::dequeue(){
    Process* temp = new Process;
    Process* topnode;
    topnode = head;
    head = head->next;
    if(head == NULL){
        tail = NULL;
    }
    temp->name = topnode->name;
    temp->arrival_time = topnode->arrival_time;
    temp->priority = topnode->priority;
    temp->task_count = topnode->task_count;
    temp->task_stack = topnode->task_stack;
    delete topnode;
    return temp;
  
}

void MultiQueue::queue(Process* in){
    queues[in->priority-1].queue(in);
}

Process* MultiQueue::dequeue(int priority){
    return queues[priority-1].dequeue();
}


void Stack::close(){
    Subtask* temp = new Subtask;
    while(head){
        temp = head;
        head = head->next;
        delete temp;
    }
}

void Queue::close(){
    Process* temp = new Process;
    while(head){
        temp = head;
        head = head->next;
        temp->task_stack.close();
        delete temp;
    }
}

void MultiQueue::close(){
    
    for(int i=0; i<3; i++){
        queues[i].close();   
    }
}

void MultiQueue::init(){
    for(int i=0; i<3; i++){
            queues[i].init();
        }
}




