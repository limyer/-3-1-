// �ѱ��װ��� ����Ʈ�����а� 2018125084 �ӿ���
// �ڷᱸ���� C++ ���α׷��� (Ȳ���� ������)
// 2020�� 3�� 15��

// 1���� ����:
// �а���, �й�, �̸�, ��������� �Է¹޾Ƽ� �а���, �й�, �̸�, �������, ����, ���糯¥�� ����ϴ� C++ ���α׷��� �ۼ��϶�.
// 
// Date Ŭ������ �����ؼ� �̿��϶�.
// ����� �� :
// ȯ���մϴ�!�а���, �й�, �̸�, �������(yyyy / mm / dd)�� �Է��ϼ��� > ����Ʈ�����а�, 1111222333, ȫ�浿, 2000 / 03 / 01
// 
// >> ����Ʈ�����а� 1111222333 ȫ�浿�� 2000��3��1�ϻ� 2020��3��16�� ���� 20���Դϴ�.
// 
// ** ���α׷��� ������ ����  ���� ��¥�� ����ؾ��ϸ�, ������ �й��� �̸��� ��Ȯ�� ����ؾ���(�⼮ �� ���� ���� Ȯ�ο�).������ ���Ƿ� �ۼ� ����.
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


Date::Date(string date) { // ���ڿ� �Ű������� ���� ������
	year = stoi(date.substr(0, 4));
	month = stoi(date.substr(5, 8));
	day = stoi(date.substr(8, 11));
	now = time(0);
	localtime_s(&tm, &now);
}

void Date::show() { // ������� ���
	cout << year << "�� " << month << "�� " << day << "��";
}

void Date::showCurrentTime() { // ���� �ð� ���
	cout << tm.tm_year + 1900 << "�� " << tm.tm_mon + 1 << "�� " << tm.tm_mday << "��";
}

int Date::calculateAge() { // ������ ���
	int age;

	age = tm.tm_year + 1900 - year; // ���� ���ؿ��� ������ ���� ����
	if (month - (tm.tm_mon + 1) < 0) { // ������ ������ ���
		return age;
	}
	else if (month - (tm.tm_mon + 1) > 0) { // ������ ������ �ʾ��� ���
		return age - 1;
	}
	else // ������ ���� ���� ���� ���
	{
		if (day - (tm.tm_mday) < 0) // ��¥�� ������ ���
			return age;
		else // ��¥�� ������ �ʾ��� ���
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


	cout << "ȯ���մϴ�! �а���, �й�, �̸�, �������(yyyy/mm/dd)�� �Է��ϼ���" << endl;

	cin >> department >> studentNum >> name >> birth;

	if (department.empty() || studentNum.empty() || name.empty() || birth.empty() || birth.length() != 10) { // �� �Է��̳� ���Ŀ� ���� ���� ��
		cout << "�Է��� �߸��Ǿ����ϴ�. ���α׷��� �����մϴ�." << endl;
		return 0;
	}

	department.pop_back(); // ������ �޸��� ���ش�
	studentNum.pop_back();
	name.pop_back();

	Date birthDate(birth); // ������� ����
	studentAge = birthDate.calculateAge();

	cout << department << " " << studentNum << " " << name << "�� ";
	birthDate.show();
	cout << "�� ";
	birthDate.showCurrentTime();
	cout << " ���� " << studentAge << "���Դϴ�." << endl;

	return 0;
}