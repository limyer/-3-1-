// 한국항공대 소프트웨어학과 2018125084 임예랑
// 자료구조와 C++ 프로그래밍 (황수찬 교수님)
// 2020년 3월 15일

// 1주차 과제:
// 학과명, 학번, 이름, 생년월일을 입력받아서 학과명, 학번, 이름, 생년월일, 나이, 현재날짜를 출력하는 C++ 프로그램을 작성하라.
// 
// Date 클래스를 정의해서 이용하라.
// 입출력 예 :
// 환영합니다!학과명, 학번, 이름, 생년월일(yyyy / mm / dd)을 입력하세요 > 소프트웨어학과, 1111222333, 홍길동, 2000 / 03 / 01
// 
// >> 소프트웨어학과 1111222333 홍길동님 2000년3월1일생 2020년3월16일 현재 20세입니다.
// 
// ** 프로그램을 수행할 때의  현재 날짜를 출력해야하며, 본인의 학번과 이름은 정확히 기록해야함(출석 및 과제 제출 확인용).생일은 임의로 작성 가능.
// 



#include <iostream>
#include <string>
#include <time.h>

using namespace std;

class Date {
public:
	time_t now;
	struct tm tm;
	Date(int year, int month, int day);
	Date(string date);
	void show();
	void showCurrentTime();
	int calculateAge();
	int getYear();
	int getMonth();
	int getDay();

private:
	int year, month, day;

};


Date::Date(string date) { // 문자열 매개변수를 갖는 생성자
	year = stoi(date.substr(0, 4));
	month = stoi(date.substr(5, 8));
	day = stoi(date.substr(8, 11));
	now = time(0);
	localtime_s(&tm, &now);
}

void Date::show() { // 생년월일 출력
	cout << year << "년 " << month << "월 " << day << "일";
}

void Date::showCurrentTime() { // 현재 시간 출력
	cout << tm.tm_year + 1900 << "년 " << tm.tm_mon + 1 << "월 " << tm.tm_mday << "일";
}

int Date::calculateAge() { // 만나이 계산
	int age;

	age = tm.tm_year + 1900 - year; // 먼저 올해에서 생년을 빼고 시작
	if (month - (tm.tm_mon + 1) < 0) { // 생월이 지났을 경우
		return age;
	}
	else if (month - (tm.tm_mon + 1) > 0) { // 생월이 지나지 않았을 경우
		return age - 1;
	}
	else // 생월과 현재 월이 같을 경우
	{
		if (day - (tm.tm_mday) < 0) // 날짜가 지났을 경우
			return age;
		else // 날짜가 지나지 않았을 경우
			return age - 1;
	}
}

int Date::getYear() {
	return year;
}

int Date::getMonth() {
	return month;
}

int Date::getDay() {
	return day;
}


int main() {
	string department;
	string studentNum;
	string name;
	string birth;
	int studentAge;


	cout << "환영합니다! 학과명, 학번, 이름, 생년월일(yyyy/mm/dd)을 입력하세요" << endl;

	cin >> department >> studentNum >> name >> birth;

	if (department.empty() || studentNum.empty() || name.empty() || birth.empty() || birth.length() != 10) { // 빈 입력이나 서식에 맞지 않을 시
		cout << "입력이 잘못되었습니다. 프로그램을 종료합니다." << endl;
		return 0;
	}

	department.pop_back(); // 마지막 콤마를 빼준다
	studentNum.pop_back();
	name.pop_back();

	Date birthDate(birth); // 생년월일 생성
	studentAge = birthDate.calculateAge();

	cout << department << " " << studentNum << " " << name << "님 ";
	birthDate.show();
	cout << "생 ";
	birthDate.showCurrentTime();
	cout << " 현재 " << studentAge << "세입니다." << endl;

	return 0;
}