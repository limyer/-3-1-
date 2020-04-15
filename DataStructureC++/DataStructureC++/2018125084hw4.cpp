// �ѱ��װ��� ����Ʈ�����а� 2018125084 �ӿ���
// �ڷᱸ���� C++ ���α׷��� (Ȳ���� ������)
// 2020�� 4�� 14��


//	���׽��� �Է�, ���, ����ϴ� ���α׷��� �����Ѵ�.
//	���׽��� ��ü(class)�� �����ؾ� �ϸ�, ���׽� ������ ���Ͽ� ������ �����ε� ����� �̿��Ѵ�.
//	
//	���׽� a, b, c�� �Է¹޾� ������ �־��� ������ �����Ѵ�.(�پ��� �Է� ���� �׽�Ʈ�ϴ� ���� ��õ��)
//	���׽���(����, ���) ǥ�� ���¸� �̿��Ѵ�.
//	�Է� �� : 3x2 + 2x + 1 -- > (2, 3) (1, 2) (0, 1)
//	���׽��� ��� ������ �Ʒ��� ���� ������ ������. (��ȣ ^�� ������ �ǹ�)
//	��� �� : 3x2 + 2x + 1 -- > 3x ^ 2 + 2x + 1
//	÷�������� ���α׷� �ڵ带 �����Ѵ�.



// Ŭ���� Polynomial�� ���� ���� ��� �Լ��� �����϶�.
// �� ���׽��� �Է� : >>
// �� ���׽��� ��� : <<
// �� ���׽��� ���� : +							//A(x)+B(x)
// �� ���׽��� ���� ���� : sMultPoly(c, e)		// A(x)*cx^e�� ���
// �� ���׽��� ���� : *							//A(x)*B(x) <- ���� ���� �����̿�
// �� ���׽��� �� ��� : evalPoly(c)			// x=c�϶� ���׽��� �������


// �Ʒ� ���α׷� �ڵ带 �����϶�
//	Polynomial a, b, c, d, t;
//	int x;
//	cin >> a; //���׽��� �а� ������
//	cin >> b;
//	cin >> c;
//	cout << "A(x) = " << a; //���׽��� �����
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
	float coef; // ���
	int exp; // ����
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
		// �������� �����ϴ� �Լ�
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
	// ���׽��� �Է� �޴� ������

	while (true) {
		try {
			char input[1000] = { NULL };
			char temp[100] = { NULL };
			int index = 0, count = 0;
			float coef = 0.;
			int exp = 0;

			is >> input;
			if (!strcmp(input, ".")) { // . �Է¹��� ��� ���α׷� ����
				cout << "���α׷��� �����մϴ�" << endl;
				exit(0);
			}

			char *ptr = strtok(input, ")");      // ")" ���ڸ� �������� ���ڿ��� �ڸ�, ������ ��ȯ

			while (ptr != NULL)               // �ڸ� ���ڿ��� ������ ���� ������ �ݺ�
			{
				strcpy(temp, ptr);
				while (temp[index] != NULL) {
					if (isdigit(temp[index])) { // ������ ����� ���������� �ۿ� ������
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
					throw NegativeExp("������ �����Դϴ�."); // ������ ������ �� ����ó��
				}
				p.newTerm(coef, exp);
				ptr = strtok(NULL, ")");      // ���� ���ڿ��� �߶� �����͸� ��ȯ
			}
			break;
		}
		catch (NegativeExp &nge) {
			cout << "���� �߻� : " << nge.getMessage() << endl;
			cout << "�ٽ� �Է����ּ���" << endl;
		}
	}


	return is;
}

ostream& operator<<(ostream& os, Polynomial& p) {
	// ���׽��� ����ϱ� ���� ��� ������
	// ����� ���� ������ 2 �̻��� ���� ��, 1�� ��, ���� �� ������ ��츦 ����Ͽ� ����Ѵ�
	// �� �ȿ��� ���� �� ó������, ����� 1���� Ȯ���Ѵ�.

	p.SelectionSort(p.termArray, p.terms); // ����ϱ� ���� �������� ����

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
	// ���ο� ���� termArray ���� ÷��
	if (terms == capacity) {
		//termArray�� ũ�⸦ �� ��� Ȯ��
		capacity *= 2;
		Term *temp = new Term[capacity]; // ���ο� �迭
		copy(termArray, termArray + terms, temp);
		delete[]termArray; // �� �� �޸𸮸� ��ȯ
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
	cin >> a; //���׽��� �а� ������
	cin >> b;
	cin >> c;
	cin >> x;
	cout << "A(x) = " << a; //���׽��� �����
	cout << "B(x) = " << b;
	cout << "C(x) = " << c;
	t = a * b;
	d = t + c;
	cout << "T(x) = " << t;
	cout << "D(x) = " << d;

	cout << "x = " << x << " --> " << d.evalPoly(x);
}