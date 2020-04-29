// �ѱ��װ��� ����Ʈ�����а� 2018125084 �ӿ���
// �ڷᱸ���� C++ ���α׷��� (Ȳ���� ������)
// 2020�� 4�� 29��

// ������ ������ �Է� �޾Ƽ� ����� ���ִ� ����
// ���α׷��� �ۼ��϶�.�ݵ�� TemplateŬ������ ������ ����Ͽ� �����϶�.
// ���� 0���� ������ ���� ����ó�� ���� �ʾƵ� ��.


// �Է�: ù ��° �ٿ� ����� ���� ���ڿ� a�� �Էµȴ�.
// 	(��� ���� ����, 0~9 �ڿ��� �Է�)
// ��� : ù ° �ٿ� �Էµ� ������ ���������� ��ȯ�� ����� ���� �������� ����Ѵ�.
// 	�� ��° �ٿ��� ��Ģ������ �Ͽ� ���� ��� ���� ����Ѵ�.
//
// #���ڿ� �Է�����.�� �Էµ� ������ ���Է��� �޵��� �Ѵ�.
// 
// #����� ���� ������ �и����� �ʰ� �� ���� cpp������ �����Ѵ�.
// 
// #�Է°��� �ݺ������� ���� �� �ְ� �ϰ�, .(��ħǥ)�� �Է��ϸ� ���α׷��� �����ϵ��� �Ѵ�.


#include <iostream>
#include <algorithm>
#define MAXLEN 256

using namespace std;

//Stack ����
template <class T>
class Stack
	// objects: 0�� �̻��� ���Ҹ� ���� ���� ���� ����Ʈ
{
public:
	Stack(int stackCapacity = 10); // ũ�Ⱑ stackCapacity�� ���� ���� ����
	bool IsEmpty() const; // ���� ���� ������ 0�� ��� TRUE �ƴ� ��� FALSE
	T &Top() const; // ������ top ���Ҹ� ��ȯ
	void Push(const T &item); // ������ �鿡 item  ����
	T &Pop(); // ������ �� ���� �����ϰ� ��ȯ

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



void InfixToPostfix(const char* _Infix, char* _Postfix); // ���� ������ ���� �������� �ٲٴ� �Լ�
int Eval(const char* postfix); // ���� ���� ���� ó���ϴ� �Լ�
int Calc(int Operland1, int Operland2, char Operator); // ������ ����ϴ� �Լ�
bool GetPriorityOperation(char Operation1, char Operation2); // ������ �켱���� Ȯ�� �Լ�
int SetPriorityOperation(char Operation); // ������ �켱���� Ȯ�� �Լ�


void InfixToPostfix(const char* _Infix, char* _Postfix) {
	Stack<char> OperationStack;
	int j = 0;

	for (int i = 0; _Infix[i]; i++) {
		switch (_Infix[i]) {
		case ' ': break; 			// �������� ���ڰ� ����
		case '+': case '-': case '*': case '/': 			// �������� ���ڰ� �������� ���
			if (OperationStack.IsEmpty()) {
				OperationStack.Push(_Infix[i]); // ������ ������� ��� �����ڸ� ���ÿ� �ִ´�.
			}
			else {
				if (GetPriorityOperation(OperationStack.Top(), _Infix[i])) { // ���� ���� �����ڰ� ������ �����ں��� �켱������ ���� ���
					_Postfix[j++] = OperationStack.Top(); // ���� ���� �����ڸ� ����
					OperationStack.Pop();
				}
				OperationStack.Push(_Infix[i]); // �����ڸ� �־��ش�
			}
			break;
		case '(': // ��ȣ ���� ��
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

	// ���ÿ� �ִ� ������ �ֱ�
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