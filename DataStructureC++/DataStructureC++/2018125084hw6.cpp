// �ѱ��װ��� ����Ʈ�����а� 2018125084 �ӿ���
// �ڷᱸ���� C++ ���α׷��� (Ȳ���� ������)
// 2020�� 5�� 14��


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
	friend class ChainNode;
	friend class Chain;
	friend class Polynomial;
	friend istream& operator>>(istream& is, Polynomial& P);
	friend ostream& operator<<(ostream& os, Polynomial& p);
	friend Polynomial operator+(Polynomial& p1, Polynomial& p2);
	friend Polynomial operator*(Polynomial& p1, Polynomial& p2);
private:
	float coef; // ���
	int exp; // ����
public:
	Term Set(float c, int e) {
		coef = c; exp = e; return *this;
	}
};

class ChainNode {
	friend class Chain;
	friend class Term;
public:
	ChainNode(int c = 0, int e = 0, ChainNode* next = 0){
		Term data;
		data.Set(c, e);
		link = next;
	}
private:
	Term data;
	ChainNode *link;
};

class Chain {
	friend class ChainNode;
private:
	ChainNode* first;
	ChainNode* last;
public:
	Chain() {
		// ��� ��������Ʈ �ʱ�ȭ
		ChainNode* headerNode = new ChainNode(0, -1, 0);
		first = last = headerNode;
		first->link = first;
		last->link = first;
	}
	void addNode(float, int);

	class iterator {
	private:
		ChainNode* current;
	public:
		// ������
		iterator(ChainNode* startNode = 0) {
			current = startNode;
		}

		//������ ������
		Term& operator*() const {
			return current->data;
		}
		Term* operator->() const {
			return &current->data;
		}

		//����
		iterator& operator++() {
			current = current->link;
			return *this;
		}
		iterator operator++(int) {
			iterator old = *this;
			current = current->link;
			return old;
		}

		//���� �˻�
		bool operator!=(const iterator right) const {
			return current != right.current;
		}
		bool operator==(const iterator right) const {
			return current == right.current;
		}
	};

	// ��� ��������Ʈ�̱� ������ ������ first�� link
	iterator begin() {
		return iterator(first->link);
	}

	// ���� last�� link
	iterator end() {
		return iterator(last->link);
	}

};

//���� ���׽� ����Ʈ�� ��� ���� ���� 
void Chain::addNode(float coef, int exp) {
	Chain::iterator i = this->begin();
	while (i != this->end()) { // ���� ������ �̹� ü�ο� �ִ��� Ȯ��
		if (exp == i->exp) { // ������ �ִٸ� ����� ���ϰ� ���� (��带 ������ ����)
			i->coef += coef;
			return;
		}
		i++;
	}
	//�ӽ� ���� ��� 
	ChainNode* newNode;
	//�޸� �Ҵ� 
	newNode = (ChainNode *)malloc(sizeof(ChainNode));
	//���� ���, ���� newNode�� ���� 
	newNode->data.Set(coef, exp);
	// ���� ������ �ۿ� ���� ���
	if (first->link == first) {
		newNode->link = first;
		last = newNode;
		first->link = newNode;
	}
	// ������ ���� �ٸ� ��尡 ���� ��� ������ ������ ����
	else {
		newNode->link = first->link;
		first->link = newNode;
	}
}





class Polynomial {
private:
	Chain poly; //IS_IMPLEMENTED_BY ����
public:
	Polynomial() {
		Chain* p = new Chain;
		poly = *p;
	}
	friend istream& operator>>(istream& is, Polynomial& p);
	friend ostream& operator<<(ostream& os, Polynomial& p);
	friend Polynomial operator+(Polynomial& p1, Polynomial& p2);
	friend Polynomial operator*(Polynomial& p1, Polynomial& p2);

	Polynomial sMultPoly(Polynomial& p, float c, float e);
	float evalPoly(Polynomial& p, float c);


	void SelectionSort(Polynomial& p) {
		// �������� �����ϴ� �Լ�
		for (Chain::iterator i = p.poly.begin(); i != p.poly.end(); ++i) {
			Chain::iterator min = i;
			for (Chain::iterator j = i; j != p.poly.end(); ++j) {
				if (min->exp < j->exp) min = j;
			}
			Term tmp;
			tmp.Set(i->coef, i->exp);
			i->coef = min->coef;
			i->exp = min->exp;
			min->coef = tmp.coef;
			min->exp = tmp.exp;
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
	// ���� 1�� : ���׽��� �Է� �޴� ������

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
				p.poly.addNode(coef, exp);
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
	// ���� 2�� : ���׽��� ����ϱ� ���� ��� ������
	// ����� ���� ������ 2 �̻��� ���� ��, 1�� ��, ���� �� ������ ��츦 ����Ͽ� ����Ѵ�
	// �� �ȿ��� ���� �� ó������, ����� 1���� Ȯ���Ѵ�.

	p.SelectionSort(p); // ����ϱ� ���� �������� ����

	for (Chain::iterator i = p.poly.begin(); i != p.poly.end(); ++i) {
		if (i->exp == 1) {
			if (abs(i->coef - 1) < EPSILON) {
				if (i == p.poly.begin()) {
					os << "x";
				}
				else {
					os << "+x";
				}

			}
			else if (i == p.poly.begin()) {
				os << noshowpos << i->coef << "x";
			}
			else {
				os << showpos << i->coef << "x";
			}
		}

		else if (i->exp == 0) {
			if (i == p.poly.begin()) {
				os << noshowpos << i->coef;
			}
			else {
				os << showpos << i->coef;
			}
		}

		else {
			if (abs(i->coef - 1) < EPSILON) {
				if (i == p.poly.begin()) {
					os << "x^" << noshowpos << i->exp;
				}
				else {
					os << "+x^" << noshowpos << i->exp;
				}
			}
			else if (i == p.poly.begin()) {
				os << noshowpos << i->coef << "x^" << noshowpos << i->exp;
			}
			else {
				os << showpos << i->coef << "x^" << noshowpos << i->exp;
			}
		}
	}
	os << endl;
	return os;
}

Polynomial operator+(Polynomial& p1, Polynomial& p2) {
	// ���� 3�� : ���׽��� ���ϴ� ������
	Term tmp;
	Chain::iterator ai = p1.poly.begin(), bi = p2.poly.begin();
	Polynomial c;
	while (ai != p1.poly.end() && bi != p2.poly.end()) { // �������� ����
		if (ai->exp == bi->exp) {
			int sum = ai->coef + bi->coef;
			if (sum) c.poly.addNode(sum, ai->exp);
			ai++; bi++; //���� ������
		}
		else if (ai->exp < bi->exp) {
			c.poly.addNode(bi->coef, bi->exp);
			bi++; //b�� ���� ��
		}
		else {
			c.poly.addNode(ai->coef, ai->exp);
			ai++; // a�� ���� ��
		}
	}
	while (ai != p1.poly.end()) { // p1�� ������ ����
		c.poly.addNode(ai->coef, ai->exp);
		ai++;
	}
	while (bi != p2.poly.end()) { // p2�� ������ ����
		c.poly.addNode(bi->coef, bi->exp);
		bi++;
	}
	return c;
}

Polynomial operator*(Polynomial& a, Polynomial& b) {
	// ���� 5�� : ���׽��� ����
	Polynomial c, d;

	for (Chain::iterator i = b.poly.begin(); i != b.poly.end(); ++i) {
		d = a.sMultPoly(a,i->coef, i->exp);
		c = c + d;
	}

	return c;
}

Polynomial Polynomial::sMultPoly(Polynomial& p, float c, float e) {
	// ���� 4�� : ���׽��� ���� ����
	Polynomial C;

	for (Chain::iterator i = p.poly.begin(); i != p.poly.end(); ++i) {
		C.poly.addNode(i->coef * c, i->exp + e);
	}

	return C;
}

float Polynomial::evalPoly(Polynomial& p, float c) {
	// ���� 6�� : ���׽��� �� ���
	float result = 0, term = 0;
	for (Chain::iterator i = p.poly.begin(); i != p.poly.end(); ++i) {
		term = i -> coef * pow(c, i-> exp);
		result += term;
	}

	return result;
}

int main() {
	while (true) {
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

		cout << noshowpos << "x = " << x << " --> " << d.evalPoly(d, x);
	}


}