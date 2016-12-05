#include <iostream>
#include <fstream>
#include <sstream>
#include <string.h>
#include <vector>

using namespace std;

class System{
    public:
        int start_time;
        int memory;
        int devices;
        int quantum;
};

void config_system(System &s, int start_time, int memory, int devices, int quantum) {
    cout << "Configuring System..." << endl;
    s.start_time = start_time;
    s.memory = memory;
    s.devices = devices;
    s.quantum = quantum;
    return;
}

void job_arrival(System &s, int start_time, int job_number, int memory, int devices, int duration, int priority) {
    cout << "Adding Job..." << endl;
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
    
    System system1;
    ifstream file ("input.txt");
    string line;
    
    while ( getline (file, line) ) {
        
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
    
        switch(buf.at(0)[0]) {
                
            case 'C':
            config_system(system1,stoi(buf.at(1)),stoi(buf.at(3)),stoi(buf.at(5)),stoi(buf.at(7)));
            break;
                
            case 'A':
            job_arrival(system1,stoi(buf.at(1)),stoi(buf.at(3)),stoi(buf.at(5)),stoi(buf.at(7)),stoi(buf.at(9)),stoi(buf.at(11)));
            break;
                
            case 'Q':
            device_request(system1,stoi(buf.at(1)),stoi(buf.at(3)),stoi(buf.at(5)));
            break;
                
            case 'L':
            device_release(system1,stoi(buf.at(1)),stoi(buf.at(3)),stoi(buf.at(5)));
            break;
                
            case 'D':
            print_status(system1,stoi(buf.at(1)));
            break;
            
            default:
            cout << "invalid input. exiting..." << endl;
            exit(0);
            
        }
    }
}