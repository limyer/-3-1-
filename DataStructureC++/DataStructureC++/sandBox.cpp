

#include <algorithm>
#include <iostream>

using namespace std;



#define ID 257
#define NUM 258
#define EQ 259
#define NE 260
#define GE 261
#define LE 262
#define AND 263
#define OR 264
#define UMINUS 265
#define MAXLEN 80



struct Expression
{
	char *str;
	int pos;
	int len;
	Expression(char *s) :str(s), pos(0)
	{
		for (len = 0; str[len] != '\0'; len++);
	}
};



struct Token
{
	int type;
	char *str;
	int len;
	int ival;
	bool operator==(char);
	bool operator!=(char);
	Token();
	Token(char);
	Token(char, char, int);
	Token(char*, int, int);
	bool IsOperand();
};


//Stack ����
template <class T>
class Stack
	// objects: 0�� �̻��� ���Ҹ� ���� ���� ���� ����Ʈ
{
public:
	Stack(int stackCapacity = 10); // ũ�Ⱑ stackCapacity�� ���� ���� ����
	bool isEmpty() const; // ���� ���� ������ 0�� ��� TRUE �ƴ� ��� FALSE
	T &Top() const; // ������ top ���Ҹ� ��ȯ
	void Push(const T &item); // ������ �鿡 item  ����
	T &Pop(); // ������ �� ���� �����ϰ� ��ȯ

private:
	T *stack;
	int top;
	int capacity;

};


ostream &operator<<(ostream &, Token);
ostream &operator<<(ostream &, Expression);
Token NextToken(Expression &, bool);
void Postfix(Expression e);







template <class T>
Stack<T>::Stack(int stackCapacity) :capacity(stackCapacity)
{
	if (capacity < 1)
		throw "Stack capcity must be >= 0";
	stack = new T[capacity];
	top = -1;
}

template <class T>
inline bool Stack<T>::isEmpty() const
{
	return top == -1;
}

template <class T>
inline T &Stack<T>::Top() const
{
	if (isEmpty())
		throw "Stack is empty";
	return stack[top];
}

template <class T>
void ChangeSize1D(T *& a, const int oldSize, const int newSize)
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
		ChangeSize1D(stack, capacity, 2 * capacity);
		capacity *= 2;
	}
	stack[++top] = x;
}

template <class T>
T &Stack<T>::Pop()
{
	T & delItem = stack[top];
	if (isEmpty())
		throw "Stack is empty. Cannot delete.";
	stack[top--].~T();

	return delItem;
}



bool Token::operator==(char b)
{
	return (len == 1 && str[0] == b); //���ٴ� ���� ���ڱ��̰� 1�̸鼭 ���� ����
}



bool Token::operator!=(char b)
{
	return (len != 1 || str[0] != b); //���ڱ��̰� 1�� �ƴϰų� ���� ���ڰ� �ƴ� ��
}

Token::Token()
{

}

Token::Token(char c) :len(1), type(c) //���̰� 1�� ������ Ȥ�� �ǿ�����
{
	str = new char[1];
	str[0] = c;
}

Token::Token(char c, char c2, int ty) :len(2), type(ty) //���̰� 2�� ������
{
	str = new char[2];
	str[0] = c;
	str[1] = c2;
}


Token::Token(char *arr, int l, int ty = ID) :len(l), type(ty) //�ǿ����� ���̰� 2 �̻��� ��
{
	str = new char[len + 1];
	for (int i = 0; i < len; i++)
		str[i] = arr[i];
	str[len] = '\0';
	if (type == NUM)
	{
		ival = arr[0] - '0';
		for (int i = 1; i < len; i++)
			ival = ival * 10 + arr[i] - '0';
	}
	else if (type == ID)
		ival = 0;
	else
		throw "must be ID or NUM";
}

bool Token::IsOperand() //�ǿ������ΰ�
{
	return type == ID || type == NUM;
}

ostream &operator<<(ostream &os, Token t)
{
	if (t.type == UMINUS)
		os << "-u";
	else if (t.type == NUM)
		os << t.ival;
	else
		for (int i = 0; i < t.len; i++)
			os << t.str[i];
	os << " ";
	return os;
}

ostream &operator<<(ostream &os, Expression e)
{
	for (int i = 0; i < e.len; i++)
		os << e.str[i];
	os << endl;
	return os;
}



bool GetID(Expression &e, Token &tok) //IsAlpha
{
	char arr[MAXLEN];
	int idlen = 0;
	char c = e.str[e.pos];
	if (!(c >= 'a' && c <= 'z' || c >= 'A'&&c <= 'Z')) //���ĺ��� �ƴϸ� ����
		return false;
	arr[idlen++] = c; //�迭�� �����ϰ�
	e.pos++;
	c = e.str[e.pos]; //���� ����
	while (c >= 'a'&&c <= 'z' || c >= 'A'&&c <= 'Z' || c >= '0'&&c <= '9') //���ĺ��̰ų� ������ ��쿡��
	{
		arr[idlen++] = c;
		e.pos++;
	}

	arr[idlen] = '\0'; //���ڿ��� �������� ����
	tok = Token(arr, idlen, ID);
	return true;

}



bool GetINT(Expression &e, Token &tok) //IsDigit
{
	//GetID�� ����ϰ�
	char arr[MAXLEN];
	int len = 0;
	char c = e.str[e.pos];
	if (!(c >= '0' &&  c <= '9')) //���ڰ� �ƴϸ� ����
		return false;
	arr[len++] = c;
	e.pos++;
	while ((c = e.str[e.pos]) >= '0' && c <= '9') //�����ϰ�쿡��
	{
		arr[len++] = c;
		e.pos++;
	}
	arr[len] = '\0';
	tok = Token(arr, len);

	return true;
}



void SkipBlanks(Expression &e) //������ �Ѿ�� �Լ�
{
	char c;
	while (e.pos < e.len && ((c = e.str[e.pos]) == ' ' || c == '\t'))
		e.pos++;
}

bool TwoCharOp(Expression &e, Token &tok) //���̰� 2�� ������
{
	char c = e.str[e.pos];
	char c2 = e.str[e.pos + 1];
	int op;
	if (c == '<'&&c2 == '=')
		op = LE;
	else if (c == '>'&&c2 == '=')
		op = GE;
	else if (c == '='&&c2 == '=')
		op = EQ;
	else if (c == '!'&&c2 == '=')
		op = NE;
	else if (c == '&'&&c2 == '&')
		op = AND;
	else if (c == '|'&&c2 == '|')
		op = OR;
	else if (c == '~' && c2 == 'u')
		op = UMINUS;
	else
		return false;

	tok = Token(c, c2, op);
	e.pos += 2;

	return true;

}



bool OneCharOp(Expression &e, Token &tok) //���̰� 1�� ������
{
	//����:������ ������ %�� �Ǽ� operand�� ��� ����
	char c = e.str[e.pos];
	if (c == '-' || c == '!' || c == '*' || c == '/' || c == '%' || c == '+' || c == '<' || c == '>' || c == '(' || c == ')' || c == '=')
	{
		tok = Token(c);
		e.pos++;
		return true;
	}
	return false;
}

Token NextToken(Expression &e, bool INFIX = true) //���� Token�� ��ȯ�ϴ� �Լ�
{
	static bool oprrFound = true; //���� �����ڸ� �߰ߵǾ��ٰ� ����
	Token tok;
	SkipBlanks(e);
	if (e.pos == e.len) //���� ����
	{
		if (INFIX)
			oprrFound = true;
		return Token('#');
	}

	if (GetID(e, tok) || GetINT(e, tok)) //�ǿ������� ���
	{
		if (INFIX)
			oprrFound = false; //�����ڰ� �ƴϹǷ� false
		return tok;
	}

	if (TwoCharOp(e, tok) || OneCharOp(e, tok)) //�������� ���
	{
		if (tok.type == '-' && INFIX && oprrFound)
			tok = Token('-', 'u', UMINUS);
		if (INFIX)
			oprrFound = true;
		return tok;
	}

	throw "Illegal Character Found";
}



int icp(Token &t) //in-coming priority
{
	//t.type�� '('�� 0, UMINUS�� '!'�� 1, '*'�� '/'�� '%'�� 2,
	//'+'�� '-'�� 3, '<' �� '>'�� LE�� GE�� 4, EQ�� NE�� 5
	//AND�� 6, OR�̸� 7, '='�̸� 9, '#'�� 10�� return

	if (t.type == '(')
		return 0;

	else if (t.type == UMINUS || t.type == '!')
		return 1;

	else if (t.type == '*' || t.type == '/' || t.type == '%')
		return 2;

	else if (t.type == '+' || t.type == '-')
		return 3;

	else if (t.type == '<' || t.type == '>' || t.type == LE || t.type == GE)
		return 4;

	else if (t.type == EQ || t.type == NE)
		return 5;

	else if (t.type == AND)
		return 6;

	else if (t.type == OR)
		return 7;

	else if (t.type == '=')
		return 9;

	else if (t.type == '#')
		return 10;

}



int isp(Token &t) //in-stack priority
{
	// '(' ��� 0, ��Ÿ�� ��� icp(t)�� return
	if (t.type == '(')
		return 9;

	else if (t.type == UMINUS || t.type == '!')
		return 1;

	else if (t.type == '*' || t.type == '/' || t.type == '%')
		return 2;

	else if (t.type == '+' || t.type == '-')
		return 3;

	else if (t.type == '<' || t.type == '>' || t.type == LE || t.type == GE)
		return 4;

	else if (t.type == EQ || t.type == NE)
		return 5;

	else if (t.type == AND)
		return 6;

	else if (t.type == OR)
		return 7;

	else if (t.type == '=')
		return 9;

	else if (t.type == '#')
		return 10;

}



void Postfix(Expression e) //���������ڷ� ��ȯ���ִ� �Լ�

{
	Stack<Token> stack;
	stack.Push('#');

	for (Token x = NextToken(e); x != '#'; x = NextToken(e))
	{
		if (x.IsOperand()) //�ǿ����ڶ��
			cout << x;

		else if (x == ')') //��ȣ���
		{
			for (; stack.Top() != '('; stack.Pop()) //�տ� ��ȣ���� ����ϸ鼭 Pop
				cout << stack.Top();
			stack.Pop();

		}

		else
		{
			for (; isp(stack.Top()) <= icp(x); stack.Pop()) //�տ� ���� �������� �켱������ ���� �������� �켱�������� ������ ��� �� Pop
				cout << stack.Top();
			stack.Push(x);
		}

	}

	while (stack.Top() != '#') //#�� ������� �ʱ� ���� �ٲ� ����
	{
		cout << stack.Top();
		stack.Pop();
	}
	cout << endl;

}





int main(void)
{
	char line[MAXLEN];
	while (cin.getline(line, MAXLEN))
	{
		Expression e(line); //line ���۸� �̿�
		try
		{
			Postfix(e);

		}

		catch (char const *msg)
		{
			cerr << "Exception: " << msg << endl;
		}
	}

	return 0;

}