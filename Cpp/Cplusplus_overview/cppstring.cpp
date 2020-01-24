/*
 * cppstring.cpp
 *
 *  Created on: Jan 21, 2020
 *      Author: rpi
 */


#include <iostream>
#include <sstream>
#include <cstring>

using namespace std;

int main(){
	string a = "hello ";
	char temp[] = { 'w', 'o', 'r', 'l', 'd', '!', '\0'};
	string b(temp);

	a[0] = 'H';
	string c = a + b;
	cout << "The string c is : " << c << endl;
	cout << "The length of c is  " << c.length() << endl;

	int loc = c.find_first_of('w');
	c.replace(loc, 1, 1, 'W');
	cout << "The string c is now: " << c << endl;

	if(string("cat") < string("dog")){	//사전적인 문자(ascii)순서 대로 비교
		cout << "cat comes before dog (lexicographically)\n ";
	}

	c.insert(5, " to the"); //5번째 문자 이후 문장을 삽입
	cout << "The c string is now: "<< c << endl;

	//공백을 사용해 문자열을 토큰화하며 Boost.Tokenizer를 사용할 수도 있고
	//C++11의 개선된 구문을 사용할 수도 있다. 여기에서는 stringstream을 사용한다.
	stringstream ss;
	ss << c;
	string token;
	while(getline(ss, token, ' ')){	//' '마다 ss의 문자열을 나눈다.
		cout << "Token: " << token << endl;
	}

	return 0;
}

