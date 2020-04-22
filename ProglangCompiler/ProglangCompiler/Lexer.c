#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

#define SYMBOL(term) (term>=123&&term<=126)||(term>=33&&term<=47)||(term>=58&&term<=64)||(term>=91&&term<=96)

#define KEYWORD_COUNT 10
#define BUFFLEN 100000
#define TOKEN_SIZE 100000
#define MAX_TOKEN_LEN 1000

enum type { ID, string, spsymbol, keyword, charLit, intLit, floatLit, operator,  comment };
char type2[25][25] = { "Id\0","string\0","symbol\0", "\0", "\0", "\0", "\0", "\0", "\0" };

char keywords[25][25] = { "int\0","float\0", "bool\0", "char\0", "else\0", "false\0", "if\0", "main\0", "true\0", "while\0" };

typedef struct _Token { // 토큰 구조체
	char *t; // 실제 토큰
	int ttype; // 토큰 타입
	int lineno; // 토큰 라인 번호
	int keyword;
}Token;

int current_token = 0; //토큰 갯수 카운터
int c = -1;   //입력 위치
int line = 1; //현재 라인 넘버
bool halt = false;
int tokenTypeSet = 0;
int in = 0;   // 구조체 내부 토큰 카운터
Token *token[TOKEN_SIZE];

void next_token(char* input) {
	do {
		c++;
		/* EOF 확인 */
		if (input[c] == EOF) {
			halt = true;
			break;
		}
		/* 주석 or Divide */
		if (input[c] == '/') {
			/* 주석 확인 */
			if (input[c + 1] == '/') {
				//토큰 타입 설정
				if (!tokenTypeSet) {
					token[current_token]->ttype = comment;
					tokenTypeSet = 1;
				}
				do {
					token[current_token]->t[in++] = input[c];
				} while (input[c++ + 1] != '\n');
				c--;
				token[current_token]->t[in] = '\0';
				break;
			}
			// Divide
			else {
				//토큰 타입 설정
				if (!tokenTypeSet) {
					token[current_token]->ttype = spsymbol;
					tokenTypeSet = 1;
				}
				token[current_token]->t[in++] = input[c++];
				token[current_token]->t[in] = '\0';
			}
		}
		/* EOL 확인 */
		if (input[c] == '\n') {
			token[current_token]->t[in] = '\0';
			line++;
			continue;
		}
		if (input[c] == ' ' || input[c] == '\t' || input[c] == '\r') {
			token[current_token]->t[in] = '\0';
			continue;
		}

		/*알파벳이나 언더스코어*/
		if (isalpha(input[c]) || input[c] == '_') {
			//토큰 타입 설정
			if (!tokenTypeSet) {
				token[current_token]->ttype = ID;
				tokenTypeSet = 1;
			}
			token[current_token]->t[in++] = input[c];
			// 토큰 끝 확인
			if (isspace(input[c + 1])) {
				token[current_token]->t[in] = '\0';
				//c++; //undo
				break;
			}
			if ((SYMBOL(input[c + 1])) && (input[c + 1] != '_')) {
				token[current_token]->t[in] = '\0';
				break;
			}
			continue;
		}
		/*숫자가 들어왔을 때*/
		else if (isdigit(input[c])) {
			//토큰 타입 설정
			if (!tokenTypeSet) {
				token[current_token]->ttype = intLit;
				tokenTypeSet = 1;
			}
			token[current_token]->t[in++] = input[c];
			// float 타입 확인
			if (input[c + 1] == '.') {
				if (!tokenTypeSet) {
					token[current_token]->ttype = floatLit;
					tokenTypeSet = 1;
				}
				c++;
				token[current_token]->t[in++] = input[c];
				continue;
			}
			// 토큰 끝 확인
			if (isspace(input[c + 1])) {
				token[current_token]->t[in] = '\0';
				break;
			}
			if (!(isdigit(input[c + 1]))) {
				if (token[current_token]->ttype == ID && (isalpha(input[c + 1]) || input[c + 1] == '_')) {
					continue;
				}
				token[current_token]->t[in] = '\0';
				break;
			}
			continue;
		}

		/* 오퍼레이터 읽기*/
		if (input[c] == '-' || '|' || '&&' || '~' || '!' || '<' || '=' || '>' || '+' || '*' || '[' || ']') {
			//토큰 타입 설정
			if (!tokenTypeSet) {
				token[current_token]->ttype = operator;
				tokenTypeSet = 1;
			}
			token[current_token]->t[in++] = input[c];
			// 토큰 끝 확인
			if (isspace(input[c + 1])) {
				token[current_token]->t[in] = '\0';
				break;
			}
			if (SYMBOL(input[c + 1]) || isalpha(input[c + 1]) || isdigit(input[c + 1])) {
				token[current_token]->t[in] = '\0';
				break;
			}
			continue;
		}



	} while (true);
}

void get_token(char* input) {
	while (!halt) {
		token[current_token] = (Token*)malloc(sizeof(Token)); //토큰 구조체에 동적 할당
		token[current_token]->t = (char*)calloc(MAX_TOKEN_LEN, sizeof(char)); //토큰 구조체에 토큰 크기 할당


		tokenTypeSet = 0;
		in = 0;

		next_token(input);

		token[current_token]->lineno = line;
		current_token++;
	}
}


int main() {
	char *input = calloc(BUFFLEN, sizeof(char));

	FILE *fp = fopen("input.txt", "r");
	char symbol;
	if (fp == NULL) {
		puts("Cannot open input file");
		exit(1);
	}
	else {
		int j = 0;
		while (!feof(fp)) {
			symbol = fgetc(fp);
			input[j++] = symbol;
		}
		input[j++] = EOF;
		;		fclose(fp);
	}

	printf("%s\n", input);


	get_token(input);

	for (int i = 0; i < current_token - 1; i++) {
		// Id로 들어온 것 중에 키워드 확인
		if (token[i]->ttype == ID) {
			for (int j = 0; j < KEYWORD_COUNT; j++) {
				if (strcmp(token[i]->t, keywords[j])) {
					token[i]->ttype = keyword;
					break;
				}
			}
		}
		printf("Line %d : %s %s\n", token[i]->lineno, type2[token[i]->ttype], token[i]->t);
	}
	printf("%s", "***********************\n");

	free(input);
	free(*token);

	return 0;
}
