#include <iostream>
#include <fstream>
#include <string>
#include <unistd.h>

using namespace std;

// 경로 설정시 /sys/class/gpio/gpio4/ 맨 마지막 슬래쉬 꼭 표기
#define GPIO_NUMBER "4"
#define GPIO4_PATH	"/sys/class/gpio/gpio4/"
#define GPIO_SYSFS "/sys/class/gpio/"


void writeGPIO(string path, string filename, string value){
	fstream fs;
	fs.open((path+filename).c_str(), fstream::out);
	fs << value;
	fs.close();
}

int main(int argc, char* argv[]){
	if(argc != 2){
		cout << "Usage is makeLED and one of: " << endl;
		cout << "  setup, on, off, status, or close" << endl;
		cout << " e.g. makeLED on" << endl;
		return 2;
	}
	string cmd(argv[1]);
	cout << "Starting the makeLED program" << endl;
	cout << "The current LED path is: " << GPIO4_PATH <<endl;

	if(cmd == "on"){
		cout << "Turning the LED on" << endl;
		writeGPIO(string(GPIO4_PATH), "value", "1");
	}
	else if(cmd == "off"){
		cout << "Turning the LED off" << endl;
		writeGPIO(string(GPIO4_PATH), "value", "0");
	}
	else if( cmd == "setup"){
		cout << "Setting up the GPIO" << endl;
		writeGPIO(string(GPIO_SYSFS), "export", GPIO_NUMBER);
		usleep(100000);
		writeGPIO(string(GPIO4_PATH), "direction", "out");
	}
	else if(cmd == "close"){
		cout << "Unexporting the GPIO" << endl;
		writeGPIO(string(GPIO_SYSFS), "unexport", GPIO_NUMBER);
	}
	else if(cmd == "status"){
		fstream fs;
		fs.open( GPIO4_PATH "value", fstream::in);
		string line;
		while(getline(fs,line)) cout << "The state is: " << line << endl;
		fs.close();
	}
	else{
		cout << "Invalid command!" <<endl;
	}
	cout << "Finished the makeLED Program" << endl;
	return 0;
}
