/*
���� �̸� : Polynomial.c
���� ���� : �ڷᱸ�� 4�� 4.4�� ��������
			7. ���׽ĵ��� ǥ���ϰ� �����ϴ� ���� �Ҵ� �ý���(linked allocation system)
			�� �����ϰ� �ۼ��϶�. ��� ��带 ���� ���� ���� ����Ʈ�� ����ϰ�, ���׽���
			�� ���� ���� ������ ���� ���� ǥ���Ѵ�.
					| coef | expon | link |
			���׽��� ȿ�������� �����ϱ� ���� �� ������ ������ ���� ���� ����Ʈ�� ���õ�
			�Լ��� ����϶�.
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

/* ���׽� ����Ʈ�� ����ü :
   ������ ���(coef)�� ����(expon), ��� �����͸� ������.
*/
typedef struct _poly_node *poly_pointer;
typedef struct _poly_node {
	int coef;
	int expon;
	poly_pointer link;
} poly_node;
// ���׽��� �ֻ��� ������ 
poly_pointer firstPolyHead, secondPolynomial, resultPolynomial;

// �Լ� �������� ����
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

/* ���� �Լ� :
   ���׽��� �Է�, ���, ����, ����, ����, ���, ���� ����
*/
int main(void)
{
	// �޴��� �Է��� �� ����� ���� 
	int MenuNumber;
	while (1)
	{
		print_menu();
		scanf("%d", &MenuNumber);
		fflush(stdin);		// ���۸� ����. 

		switch (MenuNumber)
		{
		case 1:			// ���׽��� �Է�
			submenu_read();
			break;
		case 2:			// �Է� ���� ���׽��� ���
			submenu_write();
			break;
		case 3:			// d = a + b (���׽��� ����)
			submenu_add();
			break;
		case 4:			// d = a - b (���׽��� ����)
			submenu_substract();
			break;
		case 5:			// d = a * b (���׽��� ����)
			submenu_multi();
			break;
		case 6:			// �Ǽ����� ���ؼ� ���׽� ��� 
			submenu_eval();
			break;
		case 7:			// ���׽��� ���� ���� ����Ʈ�� ��ȯ 
			submenu_erase();
			break;
		case 8:			// ���� 
			return 0;
		default:
			printf("�߸��� �޴� �Է�.\n");
			break;
		}
	}
}

// ���� �޴��� ����ϴ� �Լ�  
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

// ���� �޴��� ���׽� ��¿� ���� �Լ� 
void submenu_write()
{
	if (firstPolyHead != NULL && secondPolynomial != NULL)
	{
		printf("-----------------���׽��� ���-------------------\n");
		printf("ù��° ");
		PolynomialWrite(firstPolyHead);

		printf("�ι�° ");
		PolynomialWrite(secondPolynomial);
	}
	else
		printf("���׽��� �Է��� �ּ���...\n");

}

// ���� �޴��� ���׽� ������ ���� �Լ� 
void submenu_add()
{
	if (firstPolyHead != NULL && secondPolynomial != NULL)
	{
		printf("------ù��° ���׽� + �ι�° ���׽��� ���-------\n");
		PolynomialWrite(firstPolyHead);
		printf("                +\n");
		PolynomialWrite(secondPolynomial);

		resultPolynomial = cpadd(firstPolyHead, secondPolynomial);

		printf("���\n");
		PolynomialWrite(resultPolynomial);
		cerase(&resultPolynomial);
	}
	else
		printf("���׽��� �Է��� �ּ���...\n");

}

// ���� �޴��� ���׽� ������ ���� �Լ� 
void submenu_substract()
{
	if (firstPolyHead != NULL && secondPolynomial != NULL)
	{
		printf("------ù��° ���׽� - �ι�° ���׽��� ���-------\n");
		PolynomialWrite(firstPolyHead);
		printf("                -\n");
		PolynomialWrite(secondPolynomial);

		resultPolynomial = psub(firstPolyHead, secondPolynomial);
		printf("���\n");
		PolynomialWrite(resultPolynomial);
		cerase(&resultPolynomial);
	}
	else
		printf("���׽��� �Է��� �ּ���...\n");

}

// ���� �޴��� ���׽� ������ ���� �Լ� 
void submenu_multi()
{
	if (firstPolyHead != NULL && secondPolynomial != NULL)
	{
		printf("------ù��° ���׽� * �ι�° ���׽��� ���-------\n");
		PolynomialWrite(firstPolyHead);
		printf("               *\n");
		PolynomialWrite(secondPolynomial);

		resultPolynomial = pmult(firstPolyHead, secondPolynomial);
		printf("���\n");
		PolynomialWrite(resultPolynomial);
		cerase(&resultPolynomial);
	}
	else
		printf("���׽��� �Է��� �ּ���...\n");

}

// ���� �޴��� ���׽� ��꿡 ���� �Լ� 
void submenu_eval()
{
	double a;

	if (firstPolyHead != NULL && secondPolynomial != NULL)
	{
		printf("-------� �Ǽ����� ���ؼ� ���׽��� ���--------\n");
		printf("���׽��� x���� ���� �Ǽ��� �Է��ϼ���.\n");
		printf("�Ǽ�: ");
		scanf("%lf", &a);

		PolynomialWrite(firstPolyHead);
		printf("���� ���׽Ŀ� ");
		eval(firstPolyHead, a);
		PolynomialWrite(secondPolynomial);
		printf("���� ���׽Ŀ� ");
		eval(secondPolynomial, a);
	}
	else
		printf("���׽��� �Է��� �ּ���...\n");
}

// ���� �޴��� ���� ���� ����Ʈ�� ��ȯ�ϴ� �Ϳ� ���� �Լ�  
void submenu_erase()
{
	if (firstPolyHead != NULL && secondPolynomial != NULL)
	{
		printf("----------���ݱ��� ����� ���׽��� ����----------\n");
		cerase(&firstPolyHead);
		cerase(&secondPolynomial);
	}
	else
		printf("����� ���׽��� �����ϴ�.\n");
}

// ���� �޴��� ���׽� �Է¿� ���� �Լ� 
void submenu_read()
{
	printf("���׽��� 5x^3 + 4x^2 + 6x + 1 �� ���·� �Է��ϼ���.\n");
	printf("-----------------ù��° ���׽�-------------------\n");
	fflush(stdin);
	firstPolyHead = PolynomialRead();

	printf("-----------------�ι�° ���׽�-------------------\n");
	fflush(stdin);
	secondPolynomial = PolynomialRead();
}

/* ���׽��� �Է� �޾� ���� ���� ����Ʈ�� ��ȯ�ϴ� �Լ� :
   ���׽��� ��Ʈ������ �Է� �޾� ���� �� ��ŭ ��带 �����ϰ�
   �� �׿��� ����� ������ ����� �����Ϳ� �Է��Ѵ�.
*/
poly_pointer PolynomialRead()
{
	// �Է� �޴� ���׽Ŀ� ��� �� ���� 
	char c;
	// ��Ʈ�� �迭�� index�� ��Ÿ�� ���� 
	int i = 0;
	int j = 0;
	// ó�� ��Ʈ������ �Է� �޴� ���׽��� ���� ���� 
	char Poly[MAX_POLYNOMIAL_SIZE] = { '\0', };
	// ���׽��� ������ �߶� �� �� ����� ���� 
	char poly[MAX_POLYNOMIAL_SIZE] = { '\0', };
	poly_pointer prePolynomial, Head = NULL, Tail = NULL;

	Head = (poly_pointer)malloc(sizeof(poly_node));
	if (IS_FULL(Head))
	{
		fprintf(stderr, "The memory is full\n");
		exit(2);
	}

	Head->expon = -1;			// ��� ��� 
	Head->link = Head;
	Tail = Head;

	// ���׽��� �Է� 
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
		// ���׽��� ������ �߶� �� 
		// ���� ������ ��ȣ�� �Ͽ� ��� ���� 
		if (Poly[i] == '-' || Poly[i] == '+' || Poly[i] == '\0')
		{
			if (poly[0] != '\0')
			{
				poly[j] = '\0';
				// �߶� ��(poly)�� ��� ���� 
				prePolynomial = nodeCreate(poly);
				// ������ ��带 ���� ���� ����Ʈ�� ����
				Tail->link = prePolynomial;
				Tail = Tail->link;
				Tail->link = Head;

				// poly�迭�� �ʱ�ȭ 
				for (; j > 0; j--)
					poly[j] = '\0';
			}
			// ��� ��ȣ�� ���� 
			poly[j] = Poly[i];
		}
		else
			// ��ȣ �������� ������ poly�� ����(�� ����)
			poly[j] = Poly[i];
		j++;
	} while (Poly[i++] != '\0');

	fflush(stdin);			// ���۸� ����.
	return Head;			// ��带 ��ȯ 		
}

/* ���׽��� ������ �߶� �迭 polyarray�� ������
   coef|expon|link ��带 �����ϴ� �Լ� :
   ��Ʈ������ ǥ���� x ����� ���ڷ� �ٲپ� ��忡 �Է�,
   '^' ���ʿ� �ٴ� ������ ���ڷ� �ٲپ� ��忡 �Է�
*/
poly_pointer nodeCreate(char* polyarray)
{
	// ���� ����� ������ �߶� �� ����ϴ� �迭  
	char poly[20] = { '\0' };
	// �迭�� index�� ��Ÿ�� ���� 
	int i, j;
	// �׿� x������ �ִ��� Ȯ���ϱ� ���� ���� 
	int check = 0;
	// ��Ʈ���� ���ڷ� �ٲپ� ���� �� ����(���, ����)  
	int transCoef = 0;
	int transExpon = 0;
	// ����� ������ �Է��� ��� ������ 
	poly_pointer polynode;

	polynode = (poly_pointer)malloc(sizeof(poly_node));

	// �� �迭�� ���� ������ �ݺ� 
	for (i = 0, j = 0; polyarray[i] != '\0'; i++)
	{
		// �׿��� ����� �߶� - x ���� ���������� ���� �Է� 
		if (!(polyarray[i] == 'x' || polyarray[i] == 'X'))
		{
			poly[j] = polyarray[i];
			j++;
		}
		else if (polyarray[i] == 'x' || polyarray[i] == 'X')
		{
			// �׿� x������ �����ϹǷ� 1�� ��ȯ 
			check = 1;
			// poly�� ������ ������ x�� ��� - �Է°� : x
			if (poly[0] == '\0')
				polynode->coef = 1;	// x�� ��� : 1	
			else
			{
				// poly�� ��ȣ�� ���� ��� : +x or -x
				if (polyarray[i - 1] == '+' || polyarray[i - 1] == '-')
				{
					poly[j] = '1';
					j++;
				}
				poly[j] = '\0';
				// ��Ʈ������ ǥ���� poly�� ����� ���ڷ� ��ȯ 
				transCoef = atoi(poly);
				polynode->coef = transCoef;	// ��� �Է� 
			}

			// '^'�� ���� ����: ����
			if (polyarray[i + 1] == '^')
			{
				// ����� ���� ���� poly�� �ʱ�ȭ
				for (; j > 0; j--)
					poly[j] = '\0';
				// polyarray�� ���� �������� ������ ���ڰ� �������� �̵�
				i += 2;
				j = 0;
				// ���� �Է�
				while (polyarray[i] != '\0')
				{
					poly[j++] = polyarray[i++];
				}
				poly[j] = '\0';
				transExpon = atoi(poly);
				polynode->expon = transExpon;	// ������ ��忡 �Է� 
			}
			else
			{	// �Է°��� : ax �� ��� (a: 0�� �ƴ� ���)		
				polynode->expon = 1;		// ���� : 1 
			}
			break;

		}
	}
	// ����� �Է� ���� ��� 
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

/* �Է��� ���׽� ����ϴ� �Լ� :
   ���׽��� �ֻ��� �����͸� �Ű������� �Ͽ�
   ����� �����͸� ���� ���鼭 ��� ��尡
   ���� ������ ���׽��� ����� ������ ���
*/
void PolynomialWrite(poly_pointer polynomial)
{
	// ���� ����Ʈ���� ��� ��带 ������ ��带 ����ų ������ 
	poly_pointer Link;

	printf("���׽� : ");
	Link = polynomial->link;
	// ��尡 ��� ��尡 �� ������ �ݺ� 
	for (; Link->expon != -1; Link = Link->link)
	{
		if (Link->coef >= 0)
			printf("+%dx^%d ", Link->coef, Link->expon);
		else
			printf("%dx^%d ", Link->coef, Link->expon);
	}
	printf("\n");
}

/* �� ���׽��� ���ϴ� �Լ� :
   �� ���׽��� �ֻ��� �����͸� �Ű������� �Ͽ�
   �� ���׽��� ������ ���ϸ鼭 ������ �Ѵ�.
   �Է��� �� ���׽��� ���ϸ� �ȵȴ�.
*/
poly_pointer cpadd(poly_pointer first, poly_pointer second)
{
	// first�� ���� ��ġ�� ����ϱ� ���� ������ 
	poly_pointer starta;
	// ������ ����� ����Ʈ�� ���� �ֻ��� ������
	poly_pointer d = NULL;
	poly_pointer lastd;
	int sum, done = FALSE;
	starta = first;			// first�� ������ ��� 
	// first�� second�� ��� ��带 �ǳʶ� 
	first = first->link;
	second = second->link;

	// �ջ�� ��� ��带 ���� �޸� �Ҵ� 
	d = (poly_pointer)malloc(sizeof(poly_node));
	if (IS_FULL(d))
	{
		fprintf(stderr, "The memory is full\n");
		exit(2);
	}

	d->expon = -1;
	lastd = d;
	do {
		// �� ���׽��� ������ �� 
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

/* coef = coefficient�̰� exopn = exponent�� ���ο� ��带 �����ϰ�,
   �װ��� ptr�� ���� �����Ǵ� ��忡 ÷���Ѵ�.
   ptr�� �����Ͽ� �� ���ο� ��带 �����ϵ��� �Ѵ�.
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

/* �� ���׽��� ������ �ϴ� �Լ� :
   �� ���׽��� �ֻ��� �����͸� �Ű������� �Ͽ�
   �� ���׽��� ������ ���ϸ鼭 ������ �Ѵ�.
   �Է��� �� ���׽��� ���ϸ� �ȵȴ�.
*/
poly_pointer psub(poly_pointer first, poly_pointer second)
{
	poly_pointer starta, d, lastd;
	int subresult, done = FALSE;
	starta = first;
	// �� ���׽��� ��� ��带 �ǳʶڴ�.
	first = first->link;
	second = second->link;

	// ������ ��� ��带 ���� �޸� �Ҵ� 
	d = (poly_pointer)malloc(sizeof(poly_node));
	if (IS_FULL(d))
	{
		fprintf(stderr, "The memory is full\n");
		exit(2);
	}

	d->expon = -1;
	lastd = d;
	do {
		// �� ���׽��� ������ ���Ѵ�.
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

/* �� ���׽��� ���ϴ� �Լ� :
   �� ���׽��� �ֻ��� �����͸� �Ű������� �Ͽ�
   �ι�° ���׽��� �ϳ��� �װ� ù��° ���׽��� ��
   ������ �й��Ģ�� �����Ͽ� ����Ѵ�.
   �� ���׽��� ���ϸ� �ȵȴ�.
*/
poly_pointer pmult(poly_pointer first, poly_pointer second)
{
	poly_pointer startfirst, startsecond, temp;
	poly_pointer resulta, resultc, lasta, lastc;

	// �� ���׽��� ��带 �ǳʶڴ�.
	startfirst = first->link;
	startsecond = second->link;

	// ���ϱ� ������ �ϴ� ���߿� ��� �� ��� ��� 
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

	// ����� ������� �� ��� ��� ����
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

	// ���ϱ�� �ι�° ���׽��� �ϳ��� �װ� ù��° ���׽��� �� ������ �й��Ģ�� ����  
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
			lasta = temp;		// ���� ���� ��带 resulta�� ���� 
			// ����� resulta�� ��� ���׽��� resultc�� ���Ѵ�.
			// ���� ������ ����� ��� �����ش�.
			resultc = cpadd(resultc, resulta);
			resulta->link = lasta->link;
			free(lasta);
			lasta = resulta;
		}
		startfirst = startfirst->link;
	}
	return resultc;
}

/* � �Ǽ��� f�� ���ؼ� ���׽��� ����ϸ�,
   �� ����� �Ǽ��� ��ȯ�ϴ� �Լ�
*/
void eval(poly_pointer polynomial, double f)
{
	// ���� ����� ������ŭ �Ǽ����� �����ֱ� ���� ����ϴ� ���� 
	int expon;
	//�Ǽ����� ���� ��갪�� ��� �� ���� 
	double sum = 0;
	// ���� x�� �Ǽ��� �־� ���� ���� ���� ���� 
	double multsum = 1;
	poly_pointer Link;

	// ���׽��� ��� ��带 �ǳʶ� 
	Link = polynomial->link;
	for (; Link->expon != -1; Link = Link->link)
	{
		for (expon = Link->expon; expon > 0; expon--)
			multsum = multsum * f;		// ������ŭ f�� ���Ѵ�. 
		if (Link->expon != 0)	// f�� �־� ���� x���� ����� ���� �� ���Ѵ�.
			sum = sum + (Link->coef * multsum);
		else
			sum = sum + Link->coef;
		multsum = 1;
	}
	printf("�Ǽ� %0.5f�� �־ ���� ��� : %0.5f\n", f, sum);
}

/* ���� ����Ʈ�� ǥ���� ���׽��� ���� ���� ����Ʈ�� ��ȯ�ϴ� �Լ�
*/
void cerase(poly_pointer *ptr)
{
	poly_pointer temp, last;

	temp = (*ptr)->link;
	// ��ũ�� ���� ���鼭 ��带 free ��Ų��. 
	while (temp != *ptr)
	{
		last = temp->link;
		free(temp);
		temp = last;
	}
	free(*ptr);
}