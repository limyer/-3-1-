// �ѱ��װ��� ����Ʈ�����а� 2018125084 �ӿ���
// �ڷᱸ���� C++ ���α׷��� (Ȳ���� ������)
// 2020�� 5�� 30��

// ������ �������� ���ʷ� ������ �̿�Ž��Ʈ���� �Է��ϰ�
// �̸� ���� ��ȸ�� ����Ͽ� �����ϴ� ���α׷��� �ۼ��϶�.
// - �̿�Ž��Ʈ���� ���Ḯ��Ʈ ������ ǥ���Ѵ�.
// - ���� ��ȸ ���α׷��� �ݺ��� �˰������� �ۼ��Ѵ�

#define _CRT_SECURE_NO_WARNINGS
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

// BST ����
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
	void stackinorder(); // �������� ���� ���� ��ȸ

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
			while (ptr != NULL)               // �ڸ� ���ڿ��� ������ ���� ������ �ݺ�
			{
				strcpy(temp, ptr);
				Btree.insert((int)(*temp - '0'));
				ptr = strtok(NULL, " ");      // ���� ���ڿ��� �߶� �����͸� ��ȯ
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