

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


//Stack 정의
template <class T>
class Stack
	// objects: 0개 이상의 원소를 가진 유한 순서 리스트
{
public:
	Stack(int stackCapacity = 10); // 크기가 stackCapacity인 공백 스택 생성
	bool isEmpty() const; // 스택 내의 원수가 0일 경우 TRUE 아닐 경우 FALSE
	T &Top() const; // 스택의 top 원소를 반환
	void Push(const T &item); // 스택의 톱에 item  삽입
	T &Pop(); // 스택의 톱 원소 삭제하고 반환

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
	return (len == 1 && str[0] == b); //같다는 것은 문자길이가 1이면서 같은 문자
}



bool Token::operator!=(char b)
{
	return (len != 1 || str[0] != b); //문자길이가 1이 아니거나 같은 문자가 아닐 때
}

Token::Token()
{

}

Token::Token(char c) :len(1), type(c) //길이가 1인 연산자 혹은 피연산자
{
	str = new char[1];
	str[0] = c;
}

Token::Token(char c, char c2, int ty) :len(2), type(ty) //길이가 2인 연산자
{
	str = new char[2];
	str[0] = c;
	str[1] = c2;
}


Token::Token(char *arr, int l, int ty = ID) :len(l), type(ty) //피연산자 길이가 2 이상일 때
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

bool Token::IsOperand() //피연산자인가
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
	if (!(c >= 'a' && c <= 'z' || c >= 'A'&&c <= 'Z')) //알파벳이 아니면 거짓
		return false;
	arr[idlen++] = c; //배열에 저장하고
	e.pos++;
	c = e.str[e.pos]; //다음 문자
	while (c >= 'a'&&c <= 'z' || c >= 'A'&&c <= 'Z' || c >= '0'&&c <= '9') //알파벳이거나 숫자인 경우에만
	{
		arr[idlen++] = c;
		e.pos++;
	}

	arr[idlen] = '\0'; //문자열의 마지막은 개행
	tok = Token(arr, idlen, ID);
	return true;

}



bool GetINT(Expression &e, Token &tok) //IsDigit
{
	//GetID와 비슷하게
	char arr[MAXLEN];
	int len = 0;
	char c = e.str[e.pos];
	if (!(c >= '0' &&  c <= '9')) //숫자가 아니면 거짓
		return false;
	arr[len++] = c;
	e.pos++;
	while ((c = e.str[e.pos]) >= '0' && c <= '9') //숫자일경우에만
	{
		arr[len++] = c;
		e.pos++;
	}
	arr[len] = '\0';
	tok = Token(arr, len);

	return true;
}



void SkipBlanks(Expression &e) //공백을 넘어가는 함수
{
	char c;
	while (e.pos < e.len && ((c = e.str[e.pos]) == ' ' || c == '\t'))
		e.pos++;
}

bool TwoCharOp(Expression &e, Token &tok) //길이가 2인 연산자
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



bool OneCharOp(Expression &e, Token &tok) //길이가 1인 연산자
{
	//주의:나머지 연산자 %는 실수 operand를 사용 못함
	char c = e.str[e.pos];
	if (c == '-' || c == '!' || c == '*' || c == '/' || c == '%' || c == '+' || c == '<' || c == '>' || c == '(' || c == ')' || c == '=')
	{
		tok = Token(c);
		e.pos++;
		return true;
	}
	return false;
}

Token NextToken(Expression &e, bool INFIX = true) //다음 Token을 반환하는 함수
{
	static bool oprrFound = true; //전에 연산자를 발견되었다고 가정
	Token tok;
	SkipBlanks(e);
	if (e.pos == e.len) //끝에 도달
	{
		if (INFIX)
			oprrFound = true;
		return Token('#');
	}

	if (GetID(e, tok) || GetINT(e, tok)) //피연산자의 경우
	{
		if (INFIX)
			oprrFound = false; //연산자가 아니므로 false
		return tok;
	}

	if (TwoCharOp(e, tok) || OneCharOp(e, tok)) //연산자의 경우
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
	//t.type이 '('면 0, UMINUS나 '!'면 1, '*'나 '/'나 '%'면 2,
	//'+'나 '-'면 3, '<' 나 '>'나 LE나 GE면 4, EQ나 NE면 5
	//AND면 6, OR이면 7, '='이면 9, '#'면 10을 return

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
	// '(' 경우 0, 기타의 경우 icp(t)를 return
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



void Postfix(Expression e) //후위연산자로 변환해주는 함수

{
	Stack<Token> stack;
	stack.Push('#');

	for (Token x = NextToken(e); x != '#'; x = NextToken(e))
	{
		if (x.IsOperand()) //피연산자라면
			cout << x;

		else if (x == ')') //괄호라면
		{
			for (; stack.Top() != '('; stack.Pop()) //앞에 괄호까지 출력하면서 Pop
				cout << stack.Top();
			stack.Pop();

		}

		else
		{
			for (; isp(stack.Top()) <= icp(x); stack.Pop()) //앞에 들어올 연산자의 우선순위가 현재 연산자의 우선순위보다 작으면 출력 후 Pop
				cout << stack.Top();
			stack.Push(x);
		}

	}

	while (stack.Top() != '#') //#을 출력하지 않기 위해 바꾼 문장
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
		Expression e(line); //line 버퍼를 이용
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