// 한국항공대 소프트웨어학과 2018125084 임예랑
// 자료구조와 C++ 프로그래밍 (황수찬 교수님)
// 2020년 4월 14일


//	다항식을 입력, 출력, 계산하는 프로그램을 구현한다.
//	다항식은 객체(class)로 생성해야 하며, 다항식 연산을 위하여 연산자 오버로딩 기능을 이용한다.
//	
//	다항식 a, b, c를 입력받아 문제에 주어진 연산을 수행한다.(다양한 입력 예를 테스트하는 것을 추천함)
//	다항식은(지수, 계수) 표현 형태를 이용한다.
//	입력 예 : 3x2 + 2x + 1 -- > (2, 3) (1, 2) (0, 1)
//	다항식의 출력 형식은 아래와 같은 형식을 따른다. (기호 ^는 지수를 의미)
//	출력 예 : 3x2 + 2x + 1 -- > 3x ^ 2 + 2x + 1
//	첨부파일의 프로그램 코드를 실행한다.



// 클래스 Polynomial을 위한 다음 멤버 함수를 정의하라.
// ① 다항식의 입력 : >>
// ② 다항식의 출력 : <<
// ③ 다항식의 덧셈 : +							//A(x)+B(x)
// ④ 다항식의 단항 곱셈 : sMultPoly(c, e)		// A(x)*cx^e을 계산
// ⑤ 다항식의 곱셈 : *							//A(x)*B(x) <- 단항 곱셈 연산이용
// ⑥ 다항식의 값 계산 : evalPoly(c)			// x=c일때 다항식의 값을계산


// 아래 프로그램 코드를 수행하라
//	Polynomial a, b, c, d, t;
//	int x;
//	cin >> a; //다항식을 읽고 생성함
//	cin >> b;
//	cin >> c;
//	cout << "A(x) = " << a; //다항식을 출력함
//	cout << "B(x) = " << b << endl << "C(x) = " << c;
//	t = a * b;
//	d = t + c;
//	cout << "T(x) = " << t;
//	cout << "D(x) = " << d;
//	cin >> x;
//	cout << " x = " << x << " --> " << d.evalPoly(x);


#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>
#include <cmath>
#define EPSILON 0.000001

using namespace std;

class Polynomial;


class Term {
	friend Polynomial;
	friend istream& operator>>(istream& is, Polynomial& P);
	friend ostream& operator<<(ostream& os, Polynomial& p);
	friend Polynomial operator+(Polynomial& p1, Polynomial& p2);
	friend Polynomial operator*(Polynomial& p1, Polynomial& p2);
private:
	float coef; // 계수
	int exp; // 지수
};

class Polynomial {
private:
	Term *termArray;
	int capacity;
	int terms;
public:
	Polynomial() {
		capacity = 10;
		termArray = new Term[capacity];
		terms = 0;
	}
	friend istream& operator>>(istream& is, Polynomial& p);
	friend ostream& operator<<(ostream& os, Polynomial& p);
	friend Polynomial operator+(Polynomial& p1, Polynomial& p2);
	friend Polynomial operator*(Polynomial& p1, Polynomial& p2);

	void newTerm(const float theCoeff, const int theExp);
	Polynomial sMultPoly(float c, float e);
	float evalPoly(float c);

	void SelectionSort(Term* termArray, const int terms) {
		// 차수별로 정렬하는 함수
		for (int i = 0; i < terms; i++) {
			int min = i;
			for (int j = i + 1; j < terms; j++) {
				if (termArray[min].exp < termArray[j].exp) min = j;
			}
			Term tmp = termArray[i];
			termArray[i] = termArray[min];
			termArray[min] = tmp;
		}
	}

};

class RuntimeException { // generic run-time exception
private:
	string errMsg;
public:
	RuntimeException(const string& err) { errMsg = err; }
	string getMessage() const { return errMsg; }
};

class NegativeExp : public RuntimeException
{
public:
	NegativeExp(const string& err) : RuntimeException(err) {}
private:
};




istream& operator>>(istream& is, Polynomial& p) {
	// 다항식을 입력 받는 연산자

	while (true) {
		try {
			char input[1000] = { NULL };
			char temp[100] = { NULL };
			int index = 0, count = 0;
			float coef = 0.;
			int exp = 0;

			is >> input;
			if (!strcmp(input, ".")) { // . 입력받을 경우 프로그램 종료
				cout << "프로그램을 종료합니다" << endl;
				exit(0);
			}

			char *ptr = strtok(input, ")");      // ")" 문자를 기준으로 문자열을 자름, 포인터 반환

			while (ptr != NULL)               // 자른 문자열이 나오지 않을 때까지 반복
			{
				strcpy(temp, ptr);
				while (temp[index] != NULL) {
					if (isdigit(temp[index])) { // 아직은 계수를 정수형으로 밖에 못받음
						if (count == 0) {
							coef = (float)(temp[index] - '0');
							count++;
						}
						else {
							exp = (temp[index] - '0');
						}
					}
					index++;
				}
				index = 0;
				count = 0;
				if (exp < 0) {
					throw NegativeExp("지수가 음수입니다."); // 지수가 음수일 때 예외처리
				}
				p.newTerm(coef, exp);
				ptr = strtok(NULL, ")");      // 다음 문자열을 잘라서 포인터를 반환
			}
			break;
		}
		catch (NegativeExp &nge) {
			cout << "에러 발생 : " << nge.getMessage() << endl;
			cout << "다시 입력해주세요" << endl;
		}
	}


	return is;
}

ostream& operator<<(ostream& os, Polynomial& p) {
	// 다항식을 출력하기 위한 출력 연산자
	// 출력할 값의 차수가 2 이상의 수일 때, 1일 때, 없을 때 세가지 경우를 고려하여 출력한다
	// 그 안에서 값이 맨 처음인지, 계수가 1인지 확인한다.

	p.SelectionSort(p.termArray, p.terms); // 출력하기 전에 차수별로 정렬

	for (int i = 0; i < p.terms; i++) {
		if (p.termArray[i].exp == 1) {
			if (abs(p.termArray[i].coef - 1) < EPSILON) {
				if (i == 0) {
					os << "x";
				}
				else {
					os << "+x";
				}
				
			}
			else if (i == 0) {
				os << noshowpos << p.termArray[i].coef << "x";
			}
			else {
				os << showpos << p.termArray[i].coef << "x";
			}
		}

		else if (p.termArray[i].exp == 0) {
			if (i == 0) {
				os << noshowpos << p.termArray[i].coef;
			}
			else {
				os << showpos << p.termArray[i].coef;
			}
		}

		else {
			if (abs(p.termArray[i].coef - 1) < EPSILON) {
				if (i == 0) {
					os << "x^" << noshowpos << p.termArray[i].exp;
				}
				else {
					os << "+x^" << noshowpos << p.termArray[i].exp;
				}
			}
			else if (i == 0) {
				os << noshowpos << p.termArray[i].coef << "x^" << noshowpos << p.termArray[i].exp;
			}
			else {
				os << showpos << p.termArray[i].coef << "x^" << noshowpos << p.termArray[i].exp;
			}
		}
	}
	os << endl;
	return os;
}


Polynomial operator+(Polynomial& a, Polynomial& b) {
	Polynomial C;
	int aPos = 0, bPos = 0;

	while ((aPos < a.terms) && (bPos < b.terms)) {
		if (a.termArray[aPos].exp == b.termArray[bPos].exp) {
			float t = a.termArray[aPos].coef + b.termArray[bPos].coef;
			if (t) C.newTerm(t, a.termArray[aPos].exp);
			aPos++; bPos++;
		}
		else if ((a.termArray[aPos].exp < b.termArray[bPos].exp)) {
			C.newTerm(b.termArray[bPos].coef, b.termArray[bPos].exp);
			bPos++;
		}
		else {
			C.newTerm(a.termArray[aPos].coef, a.termArray[aPos].exp);
			aPos++;
		}
	}

	for (; aPos < a.terms; aPos++) {
		C.newTerm(a.termArray[aPos].coef, a.termArray[aPos].exp);
	}

	for (; bPos < b.terms; bPos++) {
		C.newTerm(b.termArray[bPos].coef, b.termArray[bPos].exp);
	}

	return C;
}


Polynomial operator*(Polynomial& a, Polynomial& b) {
	Polynomial c, d;

	for (int i = 0; i < b.terms; i++) {
		d = a.sMultPoly(b.termArray[i].coef, b.termArray[i].exp);
		c = c + d;
	}

	return c;
}


void Polynomial::newTerm(const float theCoeff, const int theExp) {
	// 새로운 항을 termArray 끝에 첨가
	if (terms == capacity) {
		//termArray의 크기를 두 배로 확장
		capacity *= 2;
		Term *temp = new Term[capacity]; // 새로운 배열
		copy(termArray, termArray + terms, temp);
		delete[]termArray; // 그 전 메모리를 반환
		termArray = temp;
	}
	termArray[terms].coef = theCoeff;
	termArray[terms++].exp = theExp;
}

Polynomial Polynomial::sMultPoly(float c, float e) {
	Polynomial C;

	for (int i = 0; i < terms; i++) {
		C.newTerm(termArray[i].coef * c, termArray[i].exp + e);
	}

	return C;
}

float Polynomial::evalPoly(float c) {
	float result = 0, term = 0;
	for (int i = 0; i < terms; i++) {
		term = termArray[i].coef * pow(c, termArray[i].exp);
		result += term;
	}

	return result;
}


int main() {
	Polynomial a, b, c, d, t;
	int x;
	cin >> a; //다항식을 읽고 생성함
	cin >> b;
	cin >> c;
	cin >> x;
	cout << "A(x) = " << a; //다항식을 출력함
	cout << "B(x) = " << b;
	cout << "C(x) = " << c;
	t = a * b;
	d = t + c;
	cout << "T(x) = " << t;
	cout << "D(x) = " << d;

	cout << "x = " << x << " --> " << d.evalPoly(x);
}