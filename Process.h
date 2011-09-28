/* 
 * File:   process.h
 * Author: dustin
 *
 * Created on September 23, 2011, 3:05 PM
 */

#ifndef PROCESS_H
#define	PROCESS_H

#include <iostream>
#include <vector>

#include <stdlib.h>

using namespace std;

class Process {
private:
    int id, calc, period, deadline, priority, threshold, wrctn, wrctp, wrctt;
    
public:
    Process(int i, int c, int t, int d);
    Process(int i);
    ~Process();
    
    int getId();
    int getCalculationTime();
    int getPeriod();
    int getDeadline();
    int getPriority();
    int getThreshold();
    
    int getWRCTN();
    int getWRCTP();
    int getWRCTT();
    
    void calcRNon(vector<Process*> *p);
    void calcRPre(vector<Process*> *p, int x);
    void calcRTre(vector<Process*> *p);
    void setPriority(int p);
    void setThreshold(int t);
    void print(int i);
};

#endif	/* PROCESS_H */

