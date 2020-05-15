// 한국항공대 소프트웨어학과 2018125084 임예랑
// 자료구조와 C++ 프로그래밍 (황수찬 교수님)
// 2020년 5월 14일


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
	friend class ChainNode;
	friend class Chain;
	friend class Polynomial;
	friend istream& operator>>(istream& is, Polynomial& P);
	friend ostream& operator<<(ostream& os, Polynomial& p);
	friend Polynomial operator+(Polynomial& p1, Polynomial& p2);
	friend Polynomial operator*(Polynomial& p1, Polynomial& p2);
private:
	float coef; // 계수
	int exp; // 지수
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
		// 헤더 원형리스트 초기화
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
		// 생성자
		iterator(ChainNode* startNode = 0) {
			current = startNode;
		}

		//역참조 연산자
		Term& operator*() const {
			return current->data;
		}
		Term* operator->() const {
			return &current->data;
		}

		//증가
		iterator& operator++() {
			current = current->link;
			return *this;
		}
		iterator operator++(int) {
			iterator old = *this;
			current = current->link;
			return old;
		}

		//동등 검사
		bool operator!=(const iterator right) const {
			return current != right.current;
		}
		bool operator==(const iterator right) const {
			return current == right.current;
		}
	};

	// 헤더 원형리스트이기 때문에 시작은 first의 link
	iterator begin() {
		return iterator(first->link);
	}

	// 끝은 last의 link
	iterator end() {
		return iterator(last->link);
	}

};

//원형 다항식 리스트에 노드 삽입 연산 
void Chain::addNode(float coef, int exp) {
	Chain::iterator i = this->begin();
	while (i != this->end()) { // 같은 지수가 이미 체인에 있는지 확인
		if (exp == i->exp) { // 지수가 있다면 계수를 더하고 끝냄 (노드를 만들지 않음)
			i->coef += coef;
			return;
		}
		i++;
	}
	//임시 저장 노드 
	ChainNode* newNode;
	//메모리 할당 
	newNode = (ChainNode *)malloc(sizeof(ChainNode));
	//들어온 계수, 지수 newNode에 저장 
	newNode->data.Set(coef, exp);
	// 만일 헤더노드 밖에 없을 경우
	if (first->link == first) {
		newNode->link = first;
		last = newNode;
		first->link = newNode;
	}
	// 헤더노드 말고 다른 노드가 있을 경우 헤더노드 다음에 삽입
	else {
		newNode->link = first->link;
		first->link = newNode;
	}
}





class Polynomial {
private:
	Chain poly; //IS_IMPLEMENTED_BY 관계
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
		// 차수별로 정렬하는 함수
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
	// 과제 1번 : 다항식을 입력 받는 연산자

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
				p.poly.addNode(coef, exp);
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
	// 과제 2번 : 다항식을 출력하기 위한 출력 연산자
	// 출력할 값의 차수가 2 이상의 수일 때, 1일 때, 없을 때 세가지 경우를 고려하여 출력한다
	// 그 안에서 값이 맨 처음인지, 계수가 1인지 확인한다.

	p.SelectionSort(p); // 출력하기 전에 차수별로 정렬

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
	// 과제 3번 : 다항식을 더하는 연산자
	Term tmp;
	Chain::iterator ai = p1.poly.begin(), bi = p2.poly.begin();
	Polynomial c;
	while (ai != p1.poly.end() && bi != p2.poly.end()) { // 끝노드까지 진행
		if (ai->exp == bi->exp) {
			int sum = ai->coef + bi->coef;
			if (sum) c.poly.addNode(sum, ai->exp);
			ai++; bi++; //다음 항으로
		}
		else if (ai->exp < bi->exp) {
			c.poly.addNode(bi->coef, bi->exp);
			bi++; //b의 다음 항
		}
		else {
			c.poly.addNode(ai->coef, ai->exp);
			ai++; // a의 다음 항
		}
	}
	while (ai != p1.poly.end()) { // p1의 나머지 복사
		c.poly.addNode(ai->coef, ai->exp);
		ai++;
	}
	while (bi != p2.poly.end()) { // p2의 나머지 복사
		c.poly.addNode(bi->coef, bi->exp);
		bi++;
	}
	return c;
}

Polynomial operator*(Polynomial& a, Polynomial& b) {
	// 과제 5번 : 단항식의 곱셈
	Polynomial c, d;

	for (Chain::iterator i = b.poly.begin(); i != b.poly.end(); ++i) {
		d = a.sMultPoly(a,i->coef, i->exp);
		c = c + d;
	}

	return c;
}

Polynomial Polynomial::sMultPoly(Polynomial& p, float c, float e) {
	// 과제 4번 : 다항식의 단항 곱셈
	Polynomial C;

	for (Chain::iterator i = p.poly.begin(); i != p.poly.end(); ++i) {
		C.poly.addNode(i->coef * c, i->exp + e);
	}

	return C;
}

float Polynomial::evalPoly(Polynomial& p, float c) {
	// 과제 6번 : 다항식의 값 계산
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

		cout << noshowpos << "x = " << x << " --> " << d.evalPoly(d, x);
	}


}