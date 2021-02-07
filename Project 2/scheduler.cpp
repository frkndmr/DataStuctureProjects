
#include <iostream>
#include "data_structs.h"
#include <stdio.h>
#include <stdlib.h>
#include <fstream> 
#include <string> 

using namespace std;

int main(int argc, char* argv[]){
    bool con = false;
    int cum=0;
    int proces2_count = 0;
    int dead_line=0;
    string task;
    MultiQueue multiqueue;
    Stack stack;
    ifstream fout; 
    fout.open(argv[1]);
    string s_name;
    string priority;
    string arrival_time;
    string task_count;
    string duration;
    string line;

    multiqueue.init();
    stack.init();
    while(fout){
        Process* temp = new Process;
        temp->task_stack.init();
    	getline(fout, s_name , ' ');
        temp->name = s_name;
    	getline(fout, priority , '\n');
        temp->priority = stoi(priority);
		getline(fout, arrival_time , ' ');
        temp->arrival_time = stoi(arrival_time);
        getline(fout, task_count , '\n');
        temp->task_count = stoi(task_count);
        for(int i=0; i<temp->task_count; i++){
            Subtask* sub = new Subtask;
            getline(fout, sub->name , ' ');
    	    getline(fout, duration , '\n');
            sub->duration = stoi(duration);
            dead_line += stoi(duration);
            temp->task_stack.push(sub);
        }
        int a = stoi(arrival_time);
        dead_line = a + dead_line;
        temp->deadline = dead_line;
        multiqueue.queue(temp);
        dead_line = 0;
        getline(fout,line);
	}
    for(int i=0; i<3; i++){
        Process* iter = multiqueue.queues[i].head;
        Subtask* temp = new Subtask;
        while(iter != NULL){
            if(iter->arrival_time == 0){
                temp = iter->task_stack.pop();
                cout<<iter->name<<" "<<temp->name<<endl;
                dead_line += temp->duration;
                if(i == 1){
                    proces2_count++;
                }
                break;
            }
            iter = iter->next;
        }
    }
    
    while(multiqueue.queues[0].head != NULL || multiqueue.queues[1].head != NULL || multiqueue.queues[2].head != NULL){
        Process* iter1 = multiqueue.queues[0].head;
        Process* iter2 = multiqueue.queues[1].head;
        Process* iter3 = multiqueue.queues[2].head;
        Subtask* temp = new Subtask;
        if(iter1 != NULL && dead_line>=iter1->arrival_time){
            if(con == true){
                con = false;
                proces2_count = 0;
            }
            temp = iter1->task_stack.pop();
            if(temp == NULL){
                multiqueue.queues[0].dequeue();
                iter1 = iter1->next;
            }
            else{
                cout<<iter1->name<<" "<<temp->name<<endl;
                dead_line += temp->duration;
                if(iter1->task_stack.isEmpty()){
                    cum += (dead_line - iter1->deadline);
                }
            }
        }
        else if(iter2 != NULL && dead_line>=iter2->arrival_time && con == false){
            
            temp = iter2->task_stack.pop();
            if(temp == NULL){
                multiqueue.queues[1].dequeue();
                if(multiqueue.queues[1].head == NULL){
                    con = true;
                }
            }
            else{
                cout<<iter2->name<<" "<<temp->name<<endl;
                proces2_count++;
                dead_line += temp->duration;
                if(proces2_count == 2){
                        con = true;
                    }
                if(iter2->task_stack.isEmpty()){
                    cum += (dead_line - iter2->deadline);
                }   
            }
        }
        else if(iter3 != NULL && dead_line>=iter3->arrival_time){
            temp = iter3->task_stack.pop();
            if(temp == NULL){
                multiqueue.queues[2].dequeue();
            }
            else{
                cout<<iter3->name<<" "<<temp->name<<endl;
                proces2_count = 0;
                dead_line += temp->duration;
                if(multiqueue.queues[1].head != NULL){
                    con = false;
                }
                if(iter3->task_stack.isEmpty()){
                    cum += (dead_line - iter3->deadline);
                } 
            }
        }
        else{
            if(con != true){
                dead_line++;
            }
            
            if(con == true){
                proces2_count = 0;
                con = false;
            }       
        }
    }
    cout<<"Cumulative Lateness: "<<cum<<endl;
    multiqueue.close();
    return 0;
}
