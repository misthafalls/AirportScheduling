#include "Process.h"

Process::Process(int i) {
    id = i;
    int randomPeriod = ((rand() + 10) % 100) * 10;
    double utalization = (double)(((rand() % 100) - 5) % 50 + 5)/100;
    
    period = randomPeriod;
    deadline = period;
    calc = period * utalization;    
}

Process::Process(int i, int c, int t, int d) {
    id = i;
    calc = c;
    period = t;
    deadline = d;
}

void Process::calcRNon(vector<Process*> *p) {
    int response = 0;
    for(int i = 0; i < p->size(); i++) {
        response += p->at(i)->getCalculationTime();
    }
    wrctn = response;
}

void Process::calcRPre(vector<Process*> *p, int x) {
    int index = p->size() - priority;
    int response = calc;
    for(int i = index-1; i >= 0; i--) {
        response += abs(x / p->at(i)->getPeriod()) * p->at(i)->getCalculationTime();
    }
    wrctp = response;
}

void Process::calcRTre(vector<Process*> *p) {
    int response = calc;
    for(int i = 0; i < p->size(); i++) {
        if(p->at(i)->getId() != id && priority <= p->at(i)->getThreshold()) {        
            if(p->at(i)->getPriority() <= threshold) {
                response += p->at(i)->getCalculationTime();
            } else {
                response += p->at(i)->wrctt;
            }  
        }
    }
    wrctt = response;
}

void Process::print(int i) {
    cout << "T" << i 
            << " C" << i << " " << calc 
            << "\tT" << i << " " << period
            << "\tD" << i << " " << deadline
            << "\tPI" << i << " " << priority
            << "\tGA" << i << " " << threshold
            << "  WCRTn"  << " " << wrctn
            << "  WCRTp" << " " << wrctp 
            << "  WCRTt" << " " << wrctt << endl;
}

void Process::setPriority(int p) {
    priority = p;
}

void Process::setThreshold(int t) {
    threshold = t;
}

int Process::getId() {
    return id;
}

int Process::getCalculationTime() {
    return calc;
}

int Process::getDeadline() {
    return deadline;
}

int Process::getPeriod() {
    return period;
}

int Process::getPriority() {
    return priority;
}

int Process::getThreshold() {
    return threshold;
} 

int Process::getWRCTN() {
    return wrctn;
} 

int Process::getWRCTP() {
    return wrctp;
} 

int Process::getWRCTT() {
    return wrctt;
} 



