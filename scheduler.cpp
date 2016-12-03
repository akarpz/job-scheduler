#include <iostream>
#include <fstream>

using namespace std;

class System{
    public:
        int start_time;
        int memory;
        int devices;
        int quantum;
};

void config_system(System &s, int start_time, int memory, int devices, int quantum){
    cout << "Configuring System..." << endl;
    s.start_time = start_time;
    s.memory = memory;
    s.devices = devices;
    s.quantum = quantum;
    return;
}

void job_arrival(){
    cout << "Adding Job..." << endl;
    return;
}

void device_request(){
    cout << "Device Request..." << endl;
    return;
}

void device_release(){
    cout << "Releasing Device..." << endl;
    return;
}

void print_status(){
    cout << "Printing System Status..." << endl;
    return;
}

int main() {
    System system1;
    ifstream file ("input.txt");
    string line;
    
    if(!file.is_open()) {
        cout << "unable to open file. exiting" << endl;
        exit(0);
    } 
    else 
    {
        
        while ( getline (file, line) ) {
            
            switch(line[0]) {
                
                case 'C':
                config_system(system1,0,0,0,0);
                break;
                
                case 'A':
                job_arrival();
                break;
                
                case 'Q':
                device_request();
                break;
                
                case 'L':
                device_release();
                break;
                
                case 'D':
                print_status();
                break;
            }
        }
    }
    
    return 0;
}
