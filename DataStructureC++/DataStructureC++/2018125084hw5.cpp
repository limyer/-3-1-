// 한국항공대 소프트웨어학과 2018125084 임예랑
// 자료구조와 C++ 프로그래밍 (황수찬 교수님)
// 2020년 4월 29일

// 간단한 수식을 입력 받아서 계산을 해주는 계산기
// 프로그램을 작성하라.반드시 Template클래스와 스택을 사용하여 구현하라.
// 숫자 0으로 나누는 등의 예외처리 하지 않아도 됨.


// 입력: 첫 번째 줄에 계산할 수식 문자열 a가 입력된다.
// 	(띄어 쓰기 없이, 0~9 자연수 입력)
// 출력 : 첫 째 줄에 입력된 수식을 후위식으로 변환된 결과를 공백 기준으로 출력한다.
// 	두 번째 줄에는 사칙연산을 하여 나온 결과 값을 출력한다.
//
// #문자열 입력으로.이 입력될 때까지 재입력을 받도록 한다.
// 
// #헤더와 메인 파일은 분리하지 않고 한 개의 cpp파일을 제출한다.
// 
// #입력값을 반복적으로 받을 수 있게 하고, .(마침표)를 입력하면 프로그램을 종료하도록 한다.


#include <iostream>
#include <algorithm>
#define MAXLEN 256

using namespace std;

//Stack 정의
template <class T>
class Stack
	// objects: 0개 이상의 원소를 가진 유한 순서 리스트
{
public:
	Stack(int stackCapacity = 10); // 크기가 stackCapacity인 공백 스택 생성
	bool IsEmpty() const; // 스택 내의 원수가 0일 경우 TRUE 아닐 경우 FALSE
	T &Top() const; // 스택의 top 원소를 반환
	void Push(const T &item); // 스택의 톱에 item  삽입
	T &Pop(); // 스택의 톱 원소 삭제하고 반환

private:
	T *stack;
	int top;
	int capacity;

};

template <class T>
Stack<T>::Stack(int stackCapacity) :capacity(stackCapacity)
{
	if (capacity < 1)
		throw "Stack capcity must be >= 0";
	stack = new T[capacity];
	top = -1;
}

template <class T>
inline bool Stack<T>::IsEmpty() const
{
	return top == -1;
}

template <class T>
inline T &Stack<T>::Top() const
{
	if (IsEmpty())
		throw "Stack is empty";
	return stack[top];
}

template <class T>
void changeSize1D(T *& a, const int oldSize, const int newSize)
{
	if (newSize < 0)
		throw "New length must be >=0";
	T *temp = new T[newSize];
	int number = min(oldSize, newSize);
	copy(a, a + number, temp);
	delete[]a;
	a = temp;
}

template <class T>
void Stack<T>::Push(const T &x)
{
	if (top == capacity - 1)
	{
		changeSize1D(stack, capacity, 2 * capacity);
		capacity *= 2;
	}
	stack[++top] = x;
}

template <class T>
T &Stack<T>::Pop()
{
	T & delItem = stack[top];
	if (IsEmpty())
		throw "Stack is empty. Cannot delete.";
	stack[top--].~T();

	return delItem;
}



void InfixToPostfix(const char* _Infix, char* _Postfix); // 중위 연산을 후위 연산으로 바꾸는 함수
int Eval(const char* postfix); // 후위 연산 스택 처리하는 함수
int Calc(int Operland1, int Operland2, char Operator); // 실제로 계산하는 함수
bool GetPriorityOperation(char Operation1, char Operation2); // 연산자 우선순위 확인 함수
int SetPriorityOperation(char Operation); // 연산자 우선순위 확인 함수


void InfixToPostfix(const char* _Infix, char* _Postfix) {
	Stack<char> OperationStack;
	int j = 0;

	for (int i = 0; _Infix[i]; i++) {
		switch (_Infix[i]) {
		case ' ': break; 			// 중위식의 문자가 띄어쓰기
		case '+': case '-': case '*': case '/': 			// 중위식의 문자가 연산자일 경우
			if (OperationStack.IsEmpty()) {
				OperationStack.Push(_Infix[i]); // 스택이 비어있을 경우 연산자를 스택에 넣는다.
			}
			else {
				if (GetPriorityOperation(OperationStack.Top(), _Infix[i])) { // 스택 위의 연산자가 들어오는 연산자보다 우선순위가 높을 경우
					_Postfix[j++] = OperationStack.Top(); // 스택 위의 연산자를 뺀다
					OperationStack.Pop();
				}
				OperationStack.Push(_Infix[i]); // 연산자를 넣어준다
			}
			break;
		case '(': // 괄호 여는 곳
			OperationStack.Push(_Infix[i]);
			break;
		case ')':
			while (OperationStack.Top() != '(') {
				_Postfix[j++] = OperationStack.Top();
				OperationStack.Pop();
			}
			OperationStack.Pop();
			break;
		default:
			_Postfix[j++] = _Infix[i];
			break;
		}
	}

	// 스택에 있는 연산자 넣기
	while (!OperationStack.IsEmpty()) {
		_Postfix[j++] = OperationStack.Top();
		OperationStack.Pop();
	}
	_Postfix[j] = NULL;
}

int Eval(const char* postfix) {
	Stack<char> OperlandStack;
	int Operland1 = 0;
	int Operland2 = 0;


	for (int i = 0; postfix[i]; i++) {
		switch (postfix[i]) {
		case '+': case '-': case '*': case '/':
			Operland2 = OperlandStack.Top();
			OperlandStack.Pop();
			Operland1 = OperlandStack.Top();
			OperlandStack.Pop();
			OperlandStack.Push(Calc(Operland1, Operland2, postfix[i]));
			break;

		default:
			OperlandStack.Push(postfix[i] - '0');
			break;
		}
	}

	return OperlandStack.Top();


}

int Calc(int Operland1, int Operland2, char Operator) {
	switch (Operator) {
	case '+': return Operland1 + Operland2;
	case '-': return Operland1 - Operland2;
	case '/': return Operland1 / Operland2;
	case '*': return Operland1 * Operland2;
	}

}

bool GetPriorityOperation(char Operation1, char Operation2) {
	return SetPriorityOperation(Operation1) >= SetPriorityOperation(Operation2);
}

int SetPriorityOperation(char Operation) {
	switch (Operation) {
	case '+': case '-': return 0;
	case '*': case '/': return 1;
	}
	return -1;
}


int main() {


	while (true) {
		char input[MAXLEN] = { 0, };
		char postfix[MAXLEN] = { 0, };
		char temp[MAXLEN] = { 0, };
		int c = 0;

		cin >> input;
		if (!strcmp(input, ".")) {
			break;
		}

		try
		{
			InfixToPostfix(input, temp);
			for (int i = 0; temp[i]; i++) {
				postfix[c] = temp[i];
				postfix[c + 1] = ' ';
				c += 2;
			}
			cout <<  postfix << endl;
			int result = Eval(temp);
			cout <<  result << endl;
		}

		catch (char const *msg)
		{
			cerr << "Exception: " << msg << endl;
		}

	}



	return 0;
}