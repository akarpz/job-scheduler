#include <iostream>
#include <fstream>
#include <sstream>
#include <string.h>
#include <vector>
#include <list>

using namespace std;

class Job {
    public:
        int start_time;
        int job_number;
        int memory;
        int devices;
        int priority;
        int duration;
        
        bool operator == (const Job& s) const { 
            return job_number == s.job_number;
        }
        bool operator != (const Job& s) const { 
            return !operator==(s);
        }
};

class System{
    public:
        int start_time;
        int total_memory;
        int current_memory;
        int total_devices;
        int current_devices;
        int quantum;
        int current_time = 0;
        int max_time = 1;
        
        void checkHoldQ();
        void checkReadyQ();
        void checkRunningQ();
        void checkWaitQ();
        void run();
        
        list<Job> holdQ1;
        list<Job> holdQ2;
        list<Job> readyQ;
        list<Job> running;
        list<Job> waitQ;
        
};

void System::checkReadyQ() {
    Job temp = readyQ.front();
    for(auto i: readyQ) {
        if(temp.priority > i.priority) {
            temp = i;
        }
    }
    for(auto i: readyQ) {
        if(temp.start_time > i.start_time) {
            temp = i;
        }
    }
    running.push_back(temp);
    readyQ.remove(temp);
    return;
}

void System::checkRunningQ() {
    for(auto &i: running) {
        //cout << " Running Job: " << i.job_number << "Duration: "<< i.duration << endl;
        i.duration - quantum;
        waitQ.push_back(i);
        //running.remove(i);
    }
    return;
}

void System::checkHoldQ() {
    for(auto i: holdQ1) {
        Job temp = i;
        if(temp.memory > current_memory || temp.devices > current_devices) {
            //don't add this to ready queue
        }
        else{
            //add temp to ready queue
        }
    }
}

void System::checkWaitQ() {
    for(auto i: waitQ) {
        cout << i.job_number << endl;
    }
    readyQ.push_back(waitQ.front());
    if(!waitQ.empty()){
        waitQ.pop_front();    
    }else{
        cout << "waitQ is empty" << endl;
    }
    return;
}

void config_system(System &s, int start_time, int total_memory, int total_devices, int quantum) {
    cout << "Configuring System..." << endl;
    s.start_time = start_time;
    s.current_time = start_time;
    s.max_time = start_time + 1;
    s.total_memory = total_memory;
    s.current_memory = total_memory;
    s.total_devices = total_devices;
    s.current_devices = total_devices;
    s.quantum = quantum;
    
    return;
}

void job_arrival(System &s, int start_time, int job_number, int memory, int devices, int duration, int priority) {
    Job temp;
    temp.start_time = start_time;
    temp.job_number = job_number;
    temp.memory = memory;
    temp.devices = devices;
    temp.duration = duration;
    temp.priority = priority;
    
    s.max_time = start_time + duration; //system will continue processing until last job has completed; while loop will continue until then
    
    cout << "Adding Job Number: " << temp.job_number << endl;
    if(memory > s.total_memory || devices > s.total_devices) {
        cout << "not enough total resources. rejecting job" << endl;
        return;
    }
    else if(memory > s.current_memory || devices > s.current_devices) {
        if(priority == 1) {
            s.holdQ1.push_back(temp);
        }
        else if(priority == 2) {
            s.holdQ2.push_back(temp);
        }
        else {
            cout << "incorrect input. exiting..." << endl;
            exit(0);
        }
    }
    else {
        cout << "READYQ JOB# : " << temp.job_number << endl;
        s.readyQ.push_back(temp);
    }
    return;
}

void System::run() {
        checkHoldQ();
        if(current_time % quantum == 0) {
             checkReadyQ();
             checkRunningQ();
             checkWaitQ();
        }
        //cout << "CURRENT TIME : " << s.current_time << endl;
        current_time++;
        return;
}

void device_request(System &s, int start_time, int job_number, int num_devices){
    cout << "Device Request..." << endl;
    return;
}

void device_release(System &s, int start_time, int job_number, int num_devices){
    cout << "Releasing Device..." << endl;
    return;
}

void print_status(System &s, int start_time){
    cout << "Printing System Status..." << endl;
    return;
}

int main() {
    
    System s;
    ifstream file ("input.txt");
    string line;
    
    while ( s.current_time <= s.max_time ) {
        
        streampos oldpos = file.tellg();
        getline(file, line);
        
        vector<string> buf;
        char* str = new char[line.length() +1]; 
        strcpy(str, line.c_str());
        char* pch;
        pch = strtok (str," =");
        for(int i = 0; pch!=NULL; i++)
        {
            buf.push_back(pch);
            pch = strtok (NULL, " =");
        }
        
        if(stoi(buf.at(1)) > s.current_time){
            
            file.seekg (oldpos);
            s.current_time++;
            s.max_time++;
            s.run();
            if(s.current_time < 40) { 
                cout << " SCHEDULED JOB TIME : " << stoi(buf.at(1)) << endl;
                cout << s.current_time << endl;
            }
            continue;
        }
        
        switch(buf.at(0)[0]) {
                
            case 'C':
            config_system(s,stoi(buf.at(1)),stoi(buf.at(3)),stoi(buf.at(5)),stoi(buf.at(7)));
            break;
                
            case 'A':
            job_arrival(s,stoi(buf.at(1)),stoi(buf.at(3)),stoi(buf.at(5)),stoi(buf.at(7)),stoi(buf.at(9)),stoi(buf.at(11)));
            break;
                
            case 'Q':
            device_request(s,stoi(buf.at(1)),stoi(buf.at(3)),stoi(buf.at(5)));
            break;
                
            case 'L':
            device_release(s,stoi(buf.at(1)),stoi(buf.at(3)),stoi(buf.at(5)));
            break;
                
            case 'D':
            print_status(s,stoi(buf.at(1)));
            break;
            
            default:
            cout << "invalid input. exiting..." << endl;
            exit(0);
   
        s.run();
        }
    }
}