#include <iostream>
#include <fstream>
#include <string>
#include <unistd.h>		//마이크로 초의 sleep 함수를 위해

using namespace std;
#define GPIO "/sys/class/gpio/"
#define FLASH_DELAY 50000	//50 밀리초

//클래스 선언
class LED{
	private:					//비공개 상태, LED 클래스에 쓰이는 내부 변수
		string gpioPath;
		int gpioNumber;
		void writeSysfs(string path, string filename, string value);

	public:						//공개 상태, LED 기능들
		LED(int gpioNumber);	//생성자 -- 객체를 생성
		virtual void turnOn();
		virtual void turnOff();
		virtual void displayState();
		virtual ~LED();			//소멸자 -- 자동으로 호출됨
};


LED::LED(int gpioNumber)		//생성자 구현
{
	this->gpioNumber = gpioNumber;	//this->gpioNumber: LED클래스 private gpioNumber
	gpioPath = string(GPIO "gpio") + to_string(gpioNumber) + string("/");
	writeSysfs(string(GPIO), "export", to_string(gpioNumber));
	usleep(100000);
	writeSysfs(gpioPath, "direction", "out");
}

//이 구현 함수는 클래스 와부로부터 "숨겨짐"
void LED::writeSysfs(string path, string filename, string value){	//라즈베리파이 gpio 파일 쓰기
	ofstream fs;

	// .c_str: string의 첫번째 문자의 주소값
	//path+filename의 시작주소 값 반환
	//fs.open((파일경로+파일명).시작 주소 값);
	fs.open((path+filename).c_str());	//파일 오픈
	fs << value;						//파일에 값(string) 쓰기
	fs.close();							//파일 쓰고난 후 닫기
}

void LED::turnOn(){
	writeSysfs(gpioPath, "value", "1");//(경로, gpio번호, in/out)
}

void LED::turnOff(){
	writeSysfs(gpioPath, "value", "0");//(경로, gpio번호, in/out)
}

void LED::displayState(){
	ifstream fs;

	fs.open((gpioPath+ "value").c_str());
	string line;
	cout << "The current LED state is ";
	while(getline(fs, line)) cout << line << endl;
	fs.close();
}


LED::~LED(){  // The destructor unexports the sysfs GPIO entries
   cout << "Destroying the LED with GPIO number " << gpioNumber << endl;

   // /sys/class/gpio/unexport에 gpio번호쓰기
   writeSysfs(string(GPIO), "unexport", to_string(gpioNumber));
}

int main(int argc, char* argv[]){
	cout << "Starting the makeLEDs program" << endl;
	LED led1(4), led2(17);
	cout << "Flashing the LEDs for 5seconds" << endl;


	for(int i = 0; i < 50; i++){
		led1.turnOn();
		led2.turnOff();
		usleep(FLASH_DELAY);
		led1.turnOff();
		led2.turnOn();
		usleep(FLASH_DELAY);
	}

	led1.displayState();
	led2.displayState();

	cout << "Finished the makeLEDs program" << endl;

	return 0;
}
