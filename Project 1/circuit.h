

#ifndef CIRCUIT_H
#define CIRCUIT_H
#include <stdio.h>
#include <string.h>
#include <iostream>

using namespace std;

struct resistor{
    char group;
    double value;
    int quantity;
    resistor *next;
};

struct info{
    double value;
    int quantity;
    info *next;
};


struct circuit{
    resistor *head;
    info *head2;
    void create();
    void add_resistor(char, double);
    void remove_resistor(char, double);
    void delete_resistor(char);
    void circuit_info();
    void clear();
};
void circuit::create(){
    head = NULL;
    head2 = NULL;
}
void circuit::add_resistor(char grp, double val){

    if(head == NULL){
        head = new resistor;
        head->next = NULL;
        head->group = grp;
        head->value = val;
        head->quantity=1;
    }

    else if(head->group > grp){

        resistor* temp = new resistor;
        temp->next = head;
        temp->group = grp;
        temp->value = val;
        temp->quantity=1;
        head = temp;  
    }
    else if(head->group == grp){
        head->quantity++;
    }
    else{
    resistor* iter = head;
    while(iter->next!=NULL && iter->next->group <= grp){
        if(iter->next->group == grp){
            iter->next->quantity++;
            return;
        }
        else{
            iter = iter -> next;
        }   
    }
    resistor* temp = new resistor;
    temp->next = iter->next;
    temp->group = grp;
    temp->value = val;
    temp->quantity = 1;
    iter->next = temp;

    }
}


void circuit::remove_resistor(char grp, double val){
     
    resistor* iter = head;
    if(head->group == grp){
        if(head->quantity >1){
            head->quantity--;
        }  
        else{
            delete_resistor(grp);
        }
    }
    else{
        while(iter->next->group != grp){
            iter=iter->next;
            if(iter->next == NULL ){
                cout<<"NO_RESISTOR"<<endl;
                return;
            }     
        }
        if(iter->next->quantity > 1){
            iter->next->quantity--;
        }   
        else{
            delete_resistor(grp);
        }   

    }          

}

void circuit::delete_resistor(char grp){
    resistor* temp = new resistor;
    if(head->group == grp){
        temp = head;
        head = head->next;
        delete temp;  
    }
    else{
        resistor* iter = head;
        while(iter->next->group != grp){
             iter = iter->next; 
        }
        temp = iter->next;
        iter->next = iter->next->next;
        delete temp;
    }    
}

void circuit::circuit_info(){
    double res=0;
    resistor* iter = head;

    while(iter != NULL){
        info* iter2 = head2;
        res += (iter->value/iter->quantity);

        if(head2 == NULL){
            head2 = new info;
            head2->value = iter->value;
            head2->quantity = iter->quantity;
            head2 ->next = NULL; 
      
        }
        else if(iter->value < head2->value){
            info* temp = new info;
            temp->next = head2;
            temp->value = iter->value;
            temp->quantity = iter->quantity;
            head2 = temp;
    
        }
        else if(iter->value == head2->value){
            head2->quantity+=iter->quantity;
        }
        else{
            while(iter2->next != NULL && iter2->next->value < iter->value){
            
                iter2 = iter2->next;
      
            }
            if(iter2->next != NULL && iter2->next->value == iter->value){
                iter2->next->quantity+=iter->quantity;
            }
            else{
                info* temp = new info;
                temp->next = iter2->next;
                temp->value = iter->value;
                temp->quantity = iter->quantity;
                iter2->next = temp;
            
            }
            
        }
    iter=iter->next;
    } 
    
    info* iter5 = head2;
    while(iter5 != NULL){
        cout<<iter5->value<<":"<<iter5->quantity<<endl;
        iter5 = iter5->next;
    }
    cout<<"Total resistance="<<res<<" ohm"<<endl;
    while (head2){
        info *iter6 = head2;
        head2 = head2->next;
        delete iter6;
    }

}

void circuit::clear(){
    
    while (head){
        resistor *iter = head;
        head = head->next;
        delete iter;
    }
}



    



#endif
