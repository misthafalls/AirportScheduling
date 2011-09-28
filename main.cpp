/* 
 * File:   main.cpp
 * Author: dustin
 *
 * Created on September 23, 2011, 3:04 PM
 */

#include <cstdlib>
#include <iostream>
#include <vector>

#include <stdlib.h>

#include "Process.h"

using namespace std;

void bubbleSort(vector<Process*>* a) {
    int n = a->size();
    int j = 0;
    bool swapped = true;
    Process* tmp;
    while (swapped) {
        swapped = false;
        j++;
        for (int i = 0; i < n - j; i++) {
            if (a->at(i)->getDeadline() > a->at(i + 1)->getDeadline()) {
                tmp = a->at(i);
                a->at(i) = a->at(i+1);
                a->at(i+1) = tmp;
                swapped = true;
                cout << "Had to do some swapping..." << endl;
            }
        }
    }
}

/*
 * 
 */
int main(int argc, char** argv) {
    srand(time(NULL));
    
    //1. make new list;
    vector<Process*>* v = new vector<Process*>();
    
    //2. populate list
    v->push_back(new Process(v->size(), 40, 400, 400));
    v->push_back(new Process(v->size(), 20, 70, 50));
    v->push_back(new Process(v->size(), 20, 80, 80));
    
    //3. sort list by deadline
    bubbleSort(v);

    //4. assign priorities
    int priorities = v->size();
    for(int i = 0; i < v->size(); i++) {
        v->at(i)->setPriority(priorities--);
    }
    
    //5. assign preemption thresholds
    v->at(0)->setThreshold(3);
    v->at(1)->setThreshold(3);
    v->at(2)->setThreshold(2);
    
    //6. calculate WCRT
    for(int i = 0; i < v->size(); i++) {
        v->at(i)->calcRNon(v);
        v->at(i)->calcRPre(v, v->at(i)->getPeriod());
        v->at(i)->calcRTre(v);
    }

    //7. make schedule
    for(int i = 0; i < v->size(); i++) {
        v->at(i)->print(i+1);
    }
    
    //8. check schedulability
    bool nonSchedulable = true;
    bool preSchedulable = true;
    bool treSchedulable = true;
    for(int i = 0; i < v->size(); i++) {
        Process *t = v->at(i);
        nonSchedulable = nonSchedulable && t->getWRCTN() <= t->getDeadline();
        preSchedulable = preSchedulable && t->getWRCTP() <= t->getDeadline();
        treSchedulable = treSchedulable && t->getWRCTT() <= t->getDeadline();
    }
    
    cout << endl;
    cout << "Schedulable without preemption = " << nonSchedulable << endl;
    cout << "Schedulable with preemption = " << preSchedulable << endl;
    cout << "Schedulable with preemption threshold = " << treSchedulable << endl;
    
    return 0;
}
