// 한국항공대 소프트웨어학과 2018125084 임예랑
// 자료구조와 C++ 프로그래밍 (황수찬 교수님)
// 2020년 5월 30일

// 임의의 정수들을 차례로 공백인 이원탐색트리에 입력하고
// 이를 중위 순회로 출력하여 정렬하는 프로그램을 작성하라.
// - 이원탐색트리는 연결리스트 구조로 표현한다.
// - 중위 순회 프로그램은 반복적 알고리즘으로 작성한다

#define _CRT_SECURE_NO_WARNINGS
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

// BST 정의
class BinarySearchTree {
	struct Node {
		Node() : Data(0), Left(nullptr), Right(nullptr) {}
		Node(int data) : Data(data), Left(nullptr), Right(nullptr) {}
		int		Data;
		Node*	Left;
		Node*	Right;
	};
public:
	BinarySearchTree();
	~BinarySearchTree();

public:
	void insert(int data);
	bool empty();
	void stackinorder(); // 스택으로 만든 중위 순회

private:
	Node* m_Root;


};

BinarySearchTree::BinarySearchTree() {
	m_Root = nullptr;
}

BinarySearchTree::~BinarySearchTree() {

}

void BinarySearchTree::insert(int data) {
	Node* NewNode = new Node(data);
	Node* Cur = m_Root;

	if (empty() == true) {
		m_Root = NewNode;
	}
	else {
		while (true) {
			if (Cur->Data <= NewNode->Data) {
				if (Cur->Right != NULL) Cur = Cur->Right;
				else {
					Cur->Right = NewNode;
					break;
				}
			}
			else {
				if (Cur->Left != NULL) Cur = Cur->Left;
				else {
					Cur->Left = NewNode;
					break;
				}
			}
		}
	}
}

bool BinarySearchTree::empty() {
	return m_Root == nullptr;
}


void BinarySearchTree::stackinorder() {
	if (!m_Root) return;

	Stack<Node*> Nodestack;


	Node* CurNode = m_Root;

	while (true) {
		while (CurNode) {
			Nodestack.Push(CurNode);
			CurNode = CurNode->Left;
		}

		if (!Nodestack.IsEmpty()) {
			CurNode = Nodestack.Top();
			Nodestack.Pop();
			printf("%d ", CurNode->Data);
			CurNode = CurNode->Right;
		}
		else break;
	}
}


int main() {
	while (true) {

		char input[MAXLEN];
		char temp[MAXLEN];
		int index = 0;
		BinarySearchTree Btree;

		cin.getline(input, 100);


		if (!strcmp(input, ".")) {
			break;
		}

		char *ptr = strtok(input, " ");

		try
		{
			while (ptr != NULL)               // 자른 문자열이 나오지 않을 때까지 반복
			{
				strcpy(temp, ptr);
				Btree.insert((int)(*temp - '0'));
				ptr = strtok(NULL, " ");      // 다음 문자열을 잘라서 포인터를 반환
			}

			Btree.stackinorder();
		}

		catch (char const *msg)
		{
			cerr << "Exception: " << msg << endl;
		}

	}



	return 0;
}