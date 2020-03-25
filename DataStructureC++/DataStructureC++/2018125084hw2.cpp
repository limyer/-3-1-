// 한국항공대 소프트웨어학과 2018125084 임예랑
// 자료구조와 C++ 프로그래밍 (황수찬 교수님)
// 2020년 3월 25일

// 1주차에 작성한 학과명, 학번, 이름, 생년월일, 나이, 현재날짜를 출력하는 c++ 프로그램을 수정하여 다음 기능을 포함하도록 작성하라.
//
// exception handling을 구현하기 위한 try - catch의 구조를 이용하여 사용자의 입력 데이터에 오류가 있을 때 처리하는 프로그램을 작성하라.
// (사용자의 입력 오류로 프로그램이 오작동하는 경우가 발생하지 않도록 최대한 대처할 수 있도록 할 것)
// 예: 생일 입력시  "2000/03/33"과 같이 잘못된 날짜를 입력한 경우 다시 입력할 것을 요구 함


#include <iostream>
#include <string>
#include <ctime>
#pragma warning(disable : 4996)

using namespace std;

class RuntimeException { // generic run-time exception
private:
	string errMsg;
public:
	RuntimeException(const string& err) { errMsg = err; }
	string getMessage() const { return errMsg; }
};

class InvalidFormat : public RuntimeException
{
public:
	InvalidFormat(const string& err) : RuntimeException(err) {}
private:
};

class InvalidDate : public RuntimeException
{
public:
	InvalidDate(const string& err) : RuntimeException(err) {}
private:
};

class WrongID : public RuntimeException
{
public:
	WrongID(const string& err) : RuntimeException(err) {}
private:
};

class Date {
public:
	Date();
	Date(string date);
	void show();
	void showCurrentTime();
	int calculateAge();
	int getYear();
	int getMonth();
	int getDay();

private:
	int year, month, day;
	time_t now;
	struct tm *tm;

};


Date::Date() { // 매개변수 없이 오늘 날짜로 만드는 생성자
	now = time(0);
	tm = localtime(&now);
	year = tm->tm_year + 1900;
	month = tm->tm_mon + 1;
	day = tm->tm_mday;
}

Date::Date(string date) { // 문자열 매개변수를 갖는 생성자
	now = time(0);
	tm = localtime(&now);
	year = stoi(date.substr(0, 4));
	month = stoi(date.substr(5, 8));
	day = stoi(date.substr(8, 11));
}

void Date::show() { // 생년월일 출력
	cout << year << "년 " << month << "월 " << day << "일";
}

void Date::showCurrentTime() { // 현재 시간 출력
	cout << tm->tm_year + 1900 << "년 " << tm->tm_mon + 1 << "월 " << tm->tm_mday << "일";
}

int Date::calculateAge() { // 만나이 계산
	int age;

	age = tm->tm_year + 1900 - year; // 먼저 올해에서 생년을 빼고 시작
	if (month - (tm->tm_mon + 1) < 0) { // 생월이 지났을 경우
		return age;
	}
	else if (month - (tm->tm_mon + 1) > 0) { // 생월이 지나지 않았을 경우
		return age - 1;
	}
	else // 생월과 현재 월이 같을 경우
	{
		if (day - (tm->tm_mday) < 0) // 날짜가 지났을 경우
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
	int year, month, day;
	Date thisDate;
	int thisYear = thisDate.getYear();


	cout << "환영합니다! 학과명, 학번, 이름, 생년월일(yyyy/mm/dd)을 입력하세요" << endl;


	while (true) {
		try {
			cin >> department >> studentNum >> name >> birth;

			department.pop_back(); // 마지막 콤마를 빼준다
			studentNum.pop_back();
			name.pop_back();

			char* p;
			strtol(studentNum.c_str(), &p, 10); // 문자열 모든 부분이 숫자이면 p가 0

			if (*p) { // p가 0이면 숫자
				throw WrongID("학번은 숫자로 입력해주세요.");
			}

			if (birth.length() != 10 ||
				birth.compare(4, 1, "/") ||
				birth.compare(7, 1, "/")
				) { // 서식에 슬래쉬가 들어가지 않고 길이가 맞지 않는 경우
				throw InvalidFormat("날짜가 서식에 맞지 않습니다.");
			}

			year = stoi(birth.substr(0, 4));
			bool invalidYear = (year < 1900 || year > thisYear); // 1900년도보다 작고 현재 년도보다 클 경우
			month = stoi(birth.substr(5, 8));
			bool invalidMonth = (month < 1 || month > 12); // 1월보다 적고 12월보다 클 경우
			day = stoi(birth.substr(8, 11));
			bool invalidDay;
			switch (month){
			case 2:
				invalidDay = (day > 29) ? true : false; // 2월달 확인
				break;
			case 4:
			case 6:
			case 9:
			case 11:
				invalidDay = (day > 30) ? true : false; // 4,6,9,11월달 확인
				break;
			default:
				invalidDay = (day > 31) ? true : false; // 나머지 달
				break;
			}
			if (day < 0) invalidDay = true; // 날짜가 0보다 작으면

			if (invalidYear ||
				invalidMonth ||
				invalidDay // 하나라도 잘못된 날짜가 있을 경우
				) {
				throw InvalidDate("올바르지 않은 날짜입니다.");
			}

			break; // 맞게 입력했으면 루프 탈출

		}
		catch (InvalidFormat &inf) {
			cout << "에러 발생 : " << inf.getMessage() << endl;
			cout << "다시 입력해주세요" << endl;
		}
		catch (InvalidDate &ivd) {
			cout << "에러 발생 : " << ivd.getMessage() << endl;
			cout << "다시 입력해주세요" << endl;
		}
		catch (WrongID &wid) {
			cout << "에러 발생 : " << wid.getMessage() << endl;
			cout << "다시 입력해주세요" << endl;
		}
	}


	Date birthDate(birth); // 생년월일 생성
	studentAge = birthDate.calculateAge();

	cout << department << " " << studentNum << " " << name << "님 ";
	birthDate.show();
	cout << "생 ";
	birthDate.showCurrentTime();
	cout << " 현재 " << studentAge << "세입니다." << endl;

	return 0;
}