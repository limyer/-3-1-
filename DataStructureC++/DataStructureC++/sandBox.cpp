/*
파일 이름 : Polynomial.c
문제 정의 : 자료구조 4장 4.4절 연습문제
			7. 다항식들을 표현하고 관리하는 연결 할당 시스템(linked allocation system)
			을 설계하고 작성하라. 헤드 노드를 가진 원형 연결 리스트를 사용하고, 다항식의
			각 항은 다음 구조를 가진 노드로 표현한다.
					| coef | expon | link |
			다항식을 효과적으로 제거하기 위해 이 절에서 설명한 가용 공간 리스트와 관련된
			함수를 사용하라.
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream.h>

#define IS_FULL(ptr) (!(ptr))
#define MAX_POLYNOMIAL_SIZE 100
#define COMPARE(x,y) (((x)<(y)) ? -1:((x)==(y)) ? 0:1)
#define FALSE 0
#define TRUE 1

/* 다항식 리스트의 구조체 :
   정수형 계수(coef)와 지수(expon), 노드 포인터를 가진다.
*/
typedef struct _poly_node *poly_pointer;
typedef struct _poly_node {
	int coef;
	int expon;
	poly_pointer link;
} poly_node;
// 다항식의 최상위 포인터 
poly_pointer firstPolyHead, secondPolynomial, resultPolynomial;

// 함수 원형들을 선언
poly_pointer PolynomialRead();
poly_pointer nodeCreate(char* polyarray);
void PolynomialWrite(poly_pointer polynomial);
poly_pointer cpadd(poly_pointer first, poly_pointer second);
void attach(int coefficient, int exponent, poly_pointer *ptr);
poly_pointer psub(poly_pointer first, poly_pointer second);
poly_pointer pmult(poly_pointer first, poly_pointer second);
void eval(poly_pointer polynomial, double f);
void cerase(poly_pointer *ptr);

void print_menu();
void submenu_read();
void submenu_write();
void submenu_add();
void submenu_substract();
void submenu_multi();
void submenu_eval();
void submenu_erase();
void submenu_read();

/* 메인 함수 :
   다항식의 입력, 출력, 덧셈, 뺄셈, 곱셈, 계산, 삭제 가능
*/
int main(void)
{
	// 메뉴를 입력할 때 사용할 변수 
	int MenuNumber;
	while (1)
	{
		print_menu();
		scanf("%d", &MenuNumber);
		fflush(stdin);		// 버퍼를 비운다. 

		switch (MenuNumber)
		{
		case 1:			// 다항식을 입력
			submenu_read();
			break;
		case 2:			// 입력 받은 다항식을 출력
			submenu_write();
			break;
		case 3:			// d = a + b (다항식의 덧셈)
			submenu_add();
			break;
		case 4:			// d = a - b (다항식의 뺄셈)
			submenu_substract();
			break;
		case 5:			// d = a * b (다항식의 곱셈)
			submenu_multi();
			break;
		case 6:			// 실수값에 대해서 다항식 계산 
			submenu_eval();
			break;
		case 7:			// 다항식을 가용 공간 리스트에 반환 
			submenu_erase();
			break;
		case 8:			// 종료 
			return 0;
		default:
			printf("잘못된 메뉴 입력.\n");
			break;
		}
	}
}

// 메인 메뉴를 출력하는 함수  
void print_menu()
{
	printf("----------------------------\n");
	printf("      M    E    N    U      \n");
	printf("1. Polynomial Read\n");
	printf("2. Polynomial Write\n");
	printf("3. Polynomial Add\n");
	printf("4. Polynomial Subtraction\n");
	printf("5. Polynomial Multiply\n");
	printf("6. Polynomial Evaluation\n");
	printf("7. Polynomial Erase\n");
	printf("8. Exit\n");
	printf("----------------------------\n");
	printf("You select a menu number\n");
	printf("Menu: ");
}

// 메인 메뉴의 다항식 출력에 대한 함수 
void submenu_write()
{
	if (firstPolyHead != NULL && secondPolynomial != NULL)
	{
		printf("-----------------다항식의 출력-------------------\n");
		printf("첫번째 ");
		PolynomialWrite(firstPolyHead);

		printf("두번째 ");
		PolynomialWrite(secondPolynomial);
	}
	else
		printf("다항식을 입력해 주세요...\n");

}

// 메인 메뉴의 다항식 덧셈에 대한 함수 
void submenu_add()
{
	if (firstPolyHead != NULL && secondPolynomial != NULL)
	{
		printf("------첫번째 다항식 + 두번째 다항식의 계산-------\n");
		PolynomialWrite(firstPolyHead);
		printf("                +\n");
		PolynomialWrite(secondPolynomial);

		resultPolynomial = cpadd(firstPolyHead, secondPolynomial);

		printf("결과\n");
		PolynomialWrite(resultPolynomial);
		cerase(&resultPolynomial);
	}
	else
		printf("다항식을 입력해 주세요...\n");

}

// 메인 메뉴의 다항식 뺄셈에 대한 함수 
void submenu_substract()
{
	if (firstPolyHead != NULL && secondPolynomial != NULL)
	{
		printf("------첫번째 다항식 - 두번째 다항식의 계산-------\n");
		PolynomialWrite(firstPolyHead);
		printf("                -\n");
		PolynomialWrite(secondPolynomial);

		resultPolynomial = psub(firstPolyHead, secondPolynomial);
		printf("결과\n");
		PolynomialWrite(resultPolynomial);
		cerase(&resultPolynomial);
	}
	else
		printf("다항식을 입력해 주세요...\n");

}

// 메인 메뉴의 다항식 곱셈에 대한 함수 
void submenu_multi()
{
	if (firstPolyHead != NULL && secondPolynomial != NULL)
	{
		printf("------첫번째 다항식 * 두번째 다항식의 계산-------\n");
		PolynomialWrite(firstPolyHead);
		printf("               *\n");
		PolynomialWrite(secondPolynomial);

		resultPolynomial = pmult(firstPolyHead, secondPolynomial);
		printf("결과\n");
		PolynomialWrite(resultPolynomial);
		cerase(&resultPolynomial);
	}
	else
		printf("다항식을 입력해 주세요...\n");

}

// 메인 메뉴의 다항식 계산에 대한 함수 
void submenu_eval()
{
	double a;

	if (firstPolyHead != NULL && secondPolynomial != NULL)
	{
		printf("-------어떤 실수값에 대해서 다항식을 계산--------\n");
		printf("다항식의 x값에 넣을 실수를 입력하세요.\n");
		printf("실수: ");
		scanf("%lf", &a);

		PolynomialWrite(firstPolyHead);
		printf("위의 다항식에 ");
		eval(firstPolyHead, a);
		PolynomialWrite(secondPolynomial);
		printf("위의 다항식에 ");
		eval(secondPolynomial, a);
	}
	else
		printf("다항식을 입력해 주세요...\n");
}

// 메인 메뉴의 가용 공간 리스트에 반환하는 것에 대한 함수  
void submenu_erase()
{
	if (firstPolyHead != NULL && secondPolynomial != NULL)
	{
		printf("----------지금까지 사용한 다항식을 삭제----------\n");
		cerase(&firstPolyHead);
		cerase(&secondPolynomial);
	}
	else
		printf("사용한 다항식이 없습니다.\n");
}

// 메인 메뉴의 다항식 입력에 대한 함수 
void submenu_read()
{
	printf("다항식을 5x^3 + 4x^2 + 6x + 1 의 형태로 입력하세요.\n");
	printf("-----------------첫번째 다항식-------------------\n");
	fflush(stdin);
	firstPolyHead = PolynomialRead();

	printf("-----------------두번째 다항식-------------------\n");
	fflush(stdin);
	secondPolynomial = PolynomialRead();
}

/* 다항식을 입력 받아 원형 연결 리스트로 변환하는 함수 :
   다항식을 스트링으로 입력 받아 항의 수 만큼 노드를 연결하고
   각 항에서 계수와 지수를 노드의 데이터에 입력한다.
*/
poly_pointer PolynomialRead()
{
	// 입력 받는 다항식에 사용 될 변수 
	char c;
	// 스트링 배열의 index를 나타낼 변수 
	int i = 0;
	int j = 0;
	// 처음 스트링으로 입력 받는 다항식을 위한 변수 
	char Poly[MAX_POLYNOMIAL_SIZE] = { '\0', };
	// 다항식을 항으로 잘라 낼 때 사용할 변수 
	char poly[MAX_POLYNOMIAL_SIZE] = { '\0', };
	poly_pointer prePolynomial, Head = NULL, Tail = NULL;

	Head = (poly_pointer)malloc(sizeof(poly_node));
	if (IS_FULL(Head))
	{
		fprintf(stderr, "The memory is full\n");
		exit(2);
	}

	Head->expon = -1;			// 헤드 노드 
	Head->link = Head;
	Tail = Head;

	// 다항식을 입력 
	printf("Polynomial: ");
	while ((c = getchar()) != '\n')
	{
		if (c == EOF)
		{
			printf("Program terminated...\n");
			break;
		}
		if (c != ' ')
			Poly[i++] = c;
	}
	strcat(Poly, "\0");
	printf("\n");

	poly[0] = '\0';

	i = 0;
	do {
		// 다항식을 항으로 잘라 냄 
		// 항의 구분을 부호로 하여 노드 생성 
		if (Poly[i] == '-' || Poly[i] == '+' || Poly[i] == '\0')
		{
			if (poly[0] != '\0')
			{
				poly[j] = '\0';
				// 잘라낸 항(poly)의 노드 생성 
				prePolynomial = nodeCreate(poly);
				// 생성된 노드를 원형 연결 리스트에 연결
				Tail->link = prePolynomial;
				Tail = Tail->link;
				Tail->link = Head;

				// poly배열을 초기화 
				for (; j > 0; j--)
					poly[j] = '\0';
			}
			// 계수 부호를 결정 
			poly[j] = Poly[i];
		}
		else
			// 부호 이전까지 정보를 poly에 삽입(항 삽입)
			poly[j] = Poly[i];
		j++;
	} while (Poly[i++] != '\0');

	fflush(stdin);			// 버퍼를 비운다.
	return Head;			// 헤드를 반환 		
}

/* 다항식을 항으로 잘라낸 배열 polyarray의 정보로
   coef|expon|link 노드를 생성하는 함수 :
   스트링으로 표현된 x 계수를 숫자로 바꾸어 노드에 입력,
   '^' 뒤쪽에 붙는 지수도 숫자로 바꾸어 노드에 입력
*/
poly_pointer nodeCreate(char* polyarray)
{
	// 항의 계수와 지수를 잘라낼 때 사용하는 배열  
	char poly[20] = { '\0' };
	// 배열의 index를 나타낼 변수 
	int i, j;
	// 항에 x변수가 있는지 확인하기 위한 변수 
	int check = 0;
	// 스트링을 숫자로 바꾸어 저장 될 변수(계수, 지수)  
	int transCoef = 0;
	int transExpon = 0;
	// 계수와 지수를 입력할 노드 포인터 
	poly_pointer polynode;

	polynode = (poly_pointer)malloc(sizeof(poly_node));

	// 항 배열이 끝날 때까지 반복 
	for (i = 0, j = 0; polyarray[i] != '\0'; i++)
	{
		// 항에서 계수만 잘라냄 - x 변수 이전까지의 정보 입력 
		if (!(polyarray[i] == 'x' || polyarray[i] == 'X'))
		{
			poly[j] = polyarray[i];
			j++;
		}
		else if (polyarray[i] == 'x' || polyarray[i] == 'X')
		{
			// 항에 x변수가 존재하므로 1로 변환 
			check = 1;
			// poly에 정보가 없지만 x인 경우 - 입력값 : x
			if (poly[0] == '\0')
				polynode->coef = 1;	// x의 계수 : 1	
			else
			{
				// poly에 부호만 있을 경우 : +x or -x
				if (polyarray[i - 1] == '+' || polyarray[i - 1] == '-')
				{
					poly[j] = '1';
					j++;
				}
				poly[j] = '\0';
				// 스트링으로 표현된 poly의 계수를 숫자로 변환 
				transCoef = atoi(poly);
				polynode->coef = transCoef;	// 계수 입력 
			}

			// '^'의 다음 숫자: 지수
			if (polyarray[i + 1] == '^')
			{
				// 계수를 위해 사용된 poly를 초기화
				for (; j > 0; j--)
					poly[j] = '\0';
				// polyarray의 현재 지점에서 지수의 숫자가 나오도록 이동
				i += 2;
				j = 0;
				// 지수 입력
				while (polyarray[i] != '\0')
				{
					poly[j++] = polyarray[i++];
				}
				poly[j] = '\0';
				transExpon = atoi(poly);
				polynode->expon = transExpon;	// 지수를 노드에 입력 
			}
			else
			{	// 입력값이 : ax 인 경우 (a: 0이 아닌 상수)		
				polynode->expon = 1;		// 지수 : 1 
			}
			break;

		}
	}
	// 상수만 입력 했을 경우 
	if (poly != NULL && check == 0)
	{
		poly[j] = '\0';
		transCoef = atoi(poly);
		polynode->coef = transCoef;
		polynode->expon = 0;
	}
	polynode->link = NULL;
	return polynode;
}

/* 입력한 다항식 출력하는 함수 :
   다항식의 최상위 포인터를 매개변수로 하여
   노드의 포인터를 따라 가면서 헤드 노드가
   나올 때까지 다항식의 계수와 지수를 출력
*/
void PolynomialWrite(poly_pointer polynomial)
{
	// 연결 리스트에서 헤드 노드를 제외한 노드를 가리킬 포인터 
	poly_pointer Link;

	printf("다항식 : ");
	Link = polynomial->link;
	// 노드가 헤드 노드가 될 때까지 반복 
	for (; Link->expon != -1; Link = Link->link)
	{
		if (Link->coef >= 0)
			printf("+%dx^%d ", Link->coef, Link->expon);
		else
			printf("%dx^%d ", Link->coef, Link->expon);
	}
	printf("\n");
}

/* 두 다항식을 더하는 함수 :
   두 다항식의 최상위 포인터를 매개변수로 하여
   두 다항식의 지수를 비교하면서 덧셈을 한다.
   입력한 두 다항식은 변하면 안된다.
*/
poly_pointer cpadd(poly_pointer first, poly_pointer second)
{
	// first의 시작 위치를 기록하기 위한 포인터 
	poly_pointer starta;
	// 덧셈한 결과값 리스트를 위한 최상위 포인터
	poly_pointer d = NULL;
	poly_pointer lastd;
	int sum, done = FALSE;
	starta = first;			// first의 시작을 기록 
	// first와 second의 헤드 노드를 건너뜀 
	first = first->link;
	second = second->link;

	// 합산용 헤드 노드를 위한 메모리 할당 
	d = (poly_pointer)malloc(sizeof(poly_node));
	if (IS_FULL(d))
	{
		fprintf(stderr, "The memory is full\n");
		exit(2);
	}

	d->expon = -1;
	lastd = d;
	do {
		// 두 다항식의 지수를 비교 
		switch (COMPARE(first->expon, second->expon))
		{
		case -1:		// first->expon < second->expon		
			attach(second->coef, second->expon, &lastd);
			second = second->link;
			break;
		case 0:		// first->expon = second->expon
			if (starta == first)
			{
				done = TRUE;
			}
			else
			{
				sum = first->coef + second->coef;
				if (sum)
					attach(sum, first->expon, &lastd);
				first = first->link;
				second = second->link;
			}
			break;
		case 1:		// first->expon < second->expon
			attach(first->coef, first->expon, &lastd);
			first = first->link;
		}
	} while (!done);
	lastd->link = d;
	return d;
}

/* coef = coefficient이고 exopn = exponent인 새로운 노드를 생성하고,
   그것을 ptr에 의해 참조되는 노드에 첨가한다.
   ptr을 갱신하여 이 새로운 노드를 참조하도록 한다.
*/
void attach(int coefficient, int exponent, poly_pointer *ptr)
{
	poly_pointer temp;
	temp = (poly_pointer)malloc(sizeof(poly_node));
	if (IS_FULL(temp)) {
		fprintf(stderr, "The memory is full\n");
		exit(3);
	}
	temp->coef = coefficient;
	temp->expon = exponent;
	(*ptr)->link = temp;
	*ptr = temp;
}

/* 두 다항식의 뺄셈을 하는 함수 :
   두 다항식의 최상위 포인터를 매개변수로 하여
   두 다항식의 지수를 비교하면서 뺄셈을 한다.
   입력한 두 다항식은 변하면 안된다.
*/
poly_pointer psub(poly_pointer first, poly_pointer second)
{
	poly_pointer starta, d, lastd;
	int subresult, done = FALSE;
	starta = first;
	// 두 다항식의 헤드 노드를 건너뛴다.
	first = first->link;
	second = second->link;

	// 뺄셈용 헤드 노드를 위한 메모리 할당 
	d = (poly_pointer)malloc(sizeof(poly_node));
	if (IS_FULL(d))
	{
		fprintf(stderr, "The memory is full\n");
		exit(2);
	}

	d->expon = -1;
	lastd = d;
	do {
		// 두 다항식의 지수를 비교한다.
		switch (COMPARE(first->expon, second->expon))
		{
		case -1:		// first->expon < second->expon
			second->coef = (-1)*second->coef;
			attach(second->coef, second->expon, &lastd);
			second = second->link;
			break;
		case 0:		// first->expon = second->expon
			if (starta == first)
				done = TRUE;
			else
			{
				subresult = first->coef - second->coef;
				if (subresult)
					attach(subresult, first->expon, &lastd);
				first = first->link;
				second = second->link;
			}
			break;
		case 1:		// first->expon < second->expon
			attach(first->coef, first->expon, &lastd);
			first = first->link;
		}
	} while (!done);
	lastd->link = d;
	return d;
}

/* 두 다항식을 곱하는 함수 :
   두 다항식의 최상위 포인터를 매개변수로 하여
   두번째 다항식의 하나의 항과 첫번째 다항식의 곱
   순으로 분배법칙을 적용하여 계산한다.
   두 다항식은 변하면 안된다.
*/
poly_pointer pmult(poly_pointer first, poly_pointer second)
{
	poly_pointer startfirst, startsecond, temp;
	poly_pointer resulta, resultc, lasta, lastc;

	// 두 다항식의 헤드를 건너뛴다.
	startfirst = first->link;
	startsecond = second->link;

	// 곱하기 연산을 하는 도중에 사용 할 헤드 노드 
	resulta = (poly_pointer)malloc(sizeof(poly_node));

	if (IS_FULL(resulta))
	{
		fprintf(stderr, "The memory is full\n");
		exit(2);
	}
	resulta->coef = -1;
	resulta->expon = -1;
	lasta = resulta;
	lasta->link = resulta;

	// 연산된 결과값이 들어갈 헤드 노드 생성
	resultc = (poly_pointer)malloc(sizeof(poly_node));
	if (IS_FULL(resultc))
	{
		fprintf(stderr, "The memory is full\n");
		exit(2);
	}
	resultc->coef = -1;
	resultc->expon = -1;
	lastc = resultc;
	lastc->link = resultc;

	// 곱하기는 두번째 다항식의 하나의 항과 첫번째 다항식의 곱 순으로 분배법칙을 적용  
	for (; startsecond->expon != -1; startsecond = startsecond->link)
	{
		for (; startfirst->expon != -1; startfirst = startfirst->link)
		{
			temp = (poly_pointer)malloc(sizeof(poly_node));
			if (IS_FULL(temp))
			{
				fprintf(stderr, "The memory is full\n");
				exit(2);
			}
			temp->coef = startfirst->coef * startsecond->coef;
			temp->expon = startfirst->expon + startsecond->expon;
			temp->link = lasta->link;
			lasta->link = temp;
			lasta = temp;		// 새로 계산된 노드를 resulta에 연결 
			// 연결된 resulta와 결과 다항식인 resultc을 더한다.
			// 같은 지수가 생기는 경우 더해준다.
			resultc = cpadd(resultc, resulta);
			resulta->link = lasta->link;
			free(lasta);
			lasta = resulta;
		}
		startfirst = startfirst->link;
	}
	return resultc;
}

/* 어떤 실수값 f에 대해서 다항식을 계산하며,
   그 결과를 실수로 반환하는 함수
*/
void eval(poly_pointer polynomial, double f)
{
	// 현재 노드의 지수만큼 실수값을 곱해주기 위해 사용하는 변수 
	int expon;
	//실수값에 대한 계산값이 들어 갈 변수 
	double sum = 0;
	// 변수 x에 실수를 넣어 계산된 값을 위한 변수 
	double multsum = 1;
	poly_pointer Link;

	// 다항식의 헤드 노드를 건너뜀 
	Link = polynomial->link;
	for (; Link->expon != -1; Link = Link->link)
	{
		for (expon = Link->expon; expon > 0; expon--)
			multsum = multsum * f;		// 지수만큼 f를 곱한다. 
		if (Link->expon != 0)	// f를 넣어 나온 x값과 계수를 곱한 후 더한다.
			sum = sum + (Link->coef * multsum);
		else
			sum = sum + Link->coef;
		multsum = 1;
	}
	printf("실수 %0.5f를 넣어서 계산된 결과 : %0.5f\n", f, sum);
}

/* 원형 리스트로 표현된 다항식을 가용 공간 리스트에 반환하는 함수
*/
void cerase(poly_pointer *ptr)
{
	poly_pointer temp, last;

	temp = (*ptr)->link;
	// 링크를 따라 가면서 노드를 free 시킨다. 
	while (temp != *ptr)
	{
		last = temp->link;
		free(temp);
		temp = last;
	}
	free(*ptr);
}