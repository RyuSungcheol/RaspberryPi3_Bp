/*
 * glibcTest.cpp
 *
 *  Created on: Jan 23, 2020
 *      Author: rpi
 */

#include <gnu/libc-version.h>
#include <sys/syscall.h>
#include <sys/types.h>
#include <pwd.h>
#include <cstdlib>
#include <sys/stat.h>
#include <iostream>
#include <signal.h>
#include <unistd.h>

using namespace std;

int main(){
	//시스템 정보를 얻기 위해 헬퍼 함수를 사용
	cout << "The GNU libc version is: " << gnu_get_libc_version() << endl;

	//glibc passwd 구조체를 사용해 사용자 정보를 얻음 - 오류검사 없음
	//getpwuid: linux/unix 계정인 uid로 그 계정에 대한 상세 정보를 얻는 함수

	struct passwd *pass = getpwuid(getuid());
	cout << "The current user's login is: " << pass->pw_name << endl;
	cout << "-> their full name is: " << pass->pw_gecos << endl;;
	cout << "-> their user ID is: " << pass->pw_uid << endl;

	//getenv() 함수를 사용해 환경 변수를 얻을 수 있음
	cout << "The user's shell is: " << getenv("SHELL") << endl;
	cout << "The user's path is: " << getenv("PATH") << endl;

	//사용자 ID를 얻는 syscall의 예 -- sys/syscall.h 참고
	int uid = syscall(0xc7);
	cout << "Syscall gives their user ID as: " << uid << endl;

	//chmod를 직접 호출 -- 자세한 정보를 보려면 "man 2 chmod"를 타이핑
	int ret = chmod("test.txt", 0644);

	//같은 일을 하기 위해 syscall을 사용할 수도 있음
	ret = syscall(SYS_chmod, "test.txt", 0666);
	return 0;
}



