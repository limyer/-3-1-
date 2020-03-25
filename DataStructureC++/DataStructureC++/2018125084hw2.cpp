// �ѱ��װ��� ����Ʈ�����а� 2018125084 �ӿ���
// �ڷᱸ���� C++ ���α׷��� (Ȳ���� ������)
// 2020�� 3�� 25��

// 1������ �ۼ��� �а���, �й�, �̸�, �������, ����, ���糯¥�� ����ϴ� c++ ���α׷��� �����Ͽ� ���� ����� �����ϵ��� �ۼ��϶�.
//
// exception handling�� �����ϱ� ���� try - catch�� ������ �̿��Ͽ� ������� �Է� �����Ϳ� ������ ���� �� ó���ϴ� ���α׷��� �ۼ��϶�.
// (������� �Է� ������ ���α׷��� ���۵��ϴ� ��찡 �߻����� �ʵ��� �ִ��� ��ó�� �� �ֵ��� �� ��)
// ��: ���� �Է½�  "2000/03/33"�� ���� �߸��� ��¥�� �Է��� ��� �ٽ� �Է��� ���� �䱸 ��


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


Date::Date() { // �Ű����� ���� ���� ��¥�� ����� ������
	now = time(0);
	tm = localtime(&now);
	year = tm->tm_year + 1900;
	month = tm->tm_mon + 1;
	day = tm->tm_mday;
}

Date::Date(string date) { // ���ڿ� �Ű������� ���� ������
	now = time(0);
	tm = localtime(&now);
	year = stoi(date.substr(0, 4));
	month = stoi(date.substr(5, 8));
	day = stoi(date.substr(8, 11));
}

void Date::show() { // ������� ���
	cout << year << "�� " << month << "�� " << day << "��";
}

void Date::showCurrentTime() { // ���� �ð� ���
	cout << tm->tm_year + 1900 << "�� " << tm->tm_mon + 1 << "�� " << tm->tm_mday << "��";
}

int Date::calculateAge() { // ������ ���
	int age;

	age = tm->tm_year + 1900 - year; // ���� ���ؿ��� ������ ���� ����
	if (month - (tm->tm_mon + 1) < 0) { // ������ ������ ���
		return age;
	}
	else if (month - (tm->tm_mon + 1) > 0) { // ������ ������ �ʾ��� ���
		return age - 1;
	}
	else // ������ ���� ���� ���� ���
	{
		if (day - (tm->tm_mday) < 0) // ��¥�� ������ ���
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
	int year, month, day;
	Date thisDate;
	int thisYear = thisDate.getYear();


	cout << "ȯ���մϴ�! �а���, �й�, �̸�, �������(yyyy/mm/dd)�� �Է��ϼ���" << endl;


	while (true) {
		try {
			cin >> department >> studentNum >> name >> birth;

			department.pop_back(); // ������ �޸��� ���ش�
			studentNum.pop_back();
			name.pop_back();

			char* p;
			strtol(studentNum.c_str(), &p, 10); // ���ڿ� ��� �κ��� �����̸� p�� 0

			if (*p) { // p�� 0�̸� ����
				throw WrongID("�й��� ���ڷ� �Է����ּ���.");
			}

			if (birth.length() != 10 ||
				birth.compare(4, 1, "/") ||
				birth.compare(7, 1, "/")
				) { // ���Ŀ� �������� ���� �ʰ� ���̰� ���� �ʴ� ���
				throw InvalidFormat("��¥�� ���Ŀ� ���� �ʽ��ϴ�.");
			}

			year = stoi(birth.substr(0, 4));
			bool invalidYear = (year < 1900 || year > thisYear); // 1900�⵵���� �۰� ���� �⵵���� Ŭ ���
			month = stoi(birth.substr(5, 8));
			bool invalidMonth = (month < 1 || month > 12); // 1������ ���� 12������ Ŭ ���
			day = stoi(birth.substr(8, 11));
			bool invalidDay;
			switch (month){
			case 2:
				invalidDay = (day > 29) ? true : false; // 2���� Ȯ��
				break;
			case 4:
			case 6:
			case 9:
			case 11:
				invalidDay = (day > 30) ? true : false; // 4,6,9,11���� Ȯ��
				break;
			default:
				invalidDay = (day > 31) ? true : false; // ������ ��
				break;
			}
			if (day < 0) invalidDay = true; // ��¥�� 0���� ������

			if (invalidYear ||
				invalidMonth ||
				invalidDay // �ϳ��� �߸��� ��¥�� ���� ���
				) {
				throw InvalidDate("�ùٸ��� ���� ��¥�Դϴ�.");
			}

			break; // �°� �Է������� ���� Ż��

		}
		catch (InvalidFormat &inf) {
			cout << "���� �߻� : " << inf.getMessage() << endl;
			cout << "�ٽ� �Է����ּ���" << endl;
		}
		catch (InvalidDate &ivd) {
			cout << "���� �߻� : " << ivd.getMessage() << endl;
			cout << "�ٽ� �Է����ּ���" << endl;
		}
		catch (WrongID &wid) {
			cout << "���� �߻� : " << wid.getMessage() << endl;
			cout << "�ٽ� �Է����ּ���" << endl;
		}
	}


	Date birthDate(birth); // ������� ����
	studentAge = birthDate.calculateAge();

	cout << department << " " << studentNum << " " << name << "�� ";
	birthDate.show();
	cout << "�� ";
	birthDate.showCurrentTime();
	cout << " ���� " << studentAge << "���Դϴ�." << endl;

	return 0;
}