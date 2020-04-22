#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define SYMBOL(term) (term>=123&&term<=126)||(term>=33&&term<=47)||(term>=58&&term<=64)||(term>=91&&term<=96)
#define CAPALPHA(term) (term>='A'&&term<='Z')
#define LOWALPHA(term) (term>='a'&&term<='z')
#define ALPHA(term) ((CAPALPHA(term))||(LOWALPHA(term)))
#define WHITESPACE(term) ((term>=0&&term<=32)||term==127||term=='\n')
#define NUMBER(term) (term>='0'&&term<='9')
#define HEXNUMBER(term) ((term>='A'&&term<='f')||(term>='A'||term<='f'))

#define KEYWORD_COUNT 0

enum type { identifier, string, spsymbol, keyword, character, number, hexnumber };
char type2[25][25] = { "identifier\0","string\0","symbol\0","keyword\0","character\0","number\0","hexnumber\0" };

enum keywords { regx, regy };
char keywords2[25][25] = { "regx\0","regy\0" };

struct Tokens { //Tokens structure
	char *t; //actual token
	int tlen; //token length
	int ttype; //token type
	int lineno; //token line no
	int keyword;
};

struct Tokens *token[100000];
int main() {
	char *input = malloc(100000 * sizeof(char));
	FILE *fp = fopen("file", "r");
	FILE *of = fopen("lexout", "w");
	char symbol;
	if (fp != NULL) {
		int j = 0;
		while (1)
		{
			symbol = fgetc(fp);
			printf("%c",symbol);
			if (symbol != EOF)
				input[j++] = symbol;
			else {
				input[j++] = symbol;
				break;
			}
		}
		fclose(fp);
	}

	int c = -1;   //file current character
	int current_token = 0; //current_token counter
	int line = 1; //current line number

	int halt = 0;
	while (1) {
		if (halt) break;
		token[current_token] = (struct Tokens*)malloc(sizeof(struct Tokens)); //allocate memory for token structure
		token[current_token]->t = (char*)malloc(sizeof(char) * 30); //allocate memory for token size

		int tokenTypeSet = 0;
		int in = 0;   //structure token counter

		while (1) {
			c++;
			if (input[c] == '\n') line++;
			/*detect end of file*/
			if (input[c] == '%'&&input[c + 1] == 'E'&&input[c + 2] == 'O'&&input[c + 3] == 'F'&&input[c + 4] == '%') {
				halt = 1;
				break;
			}
			/*identify singleline comments*/
			if (input[c] == '/'&&input[c + 1] == '/') {
				while (input[c + 1] != '\n') {
					c++;
				}
				continue;
			}
			/*identify multiline comments*/
			if (input[c] == '/'&&input[c + 1] == '*') {
				c++;
				c++;
				while (input[c] != '*'&&input[c + 1] != '/') {
					if (input[c] == '\n') {
						line++;
					}
					c++;
				}
				c++;
				continue;
			}
			/*identify string*/
			if (input[c] == '"') {
				//identify token type
				if (!tokenTypeSet) {
					token[current_token]->ttype = string;
					tokenTypeSet = 1;
				}
				c++;
				while (1) {
					//newline
					if (input[c] == '\n') {
						c++;
						line++;
					}
					//backslash escaped
					if (input[c] == '\\'&&input[c + 1] == '\\') {
						token[current_token]->t[in++] = input[c];
						c++;
						token[current_token]->t[in++] = input[c];
						c++;
						continue;
					}
					//double-quote escaped
					if (input[c] == '\\'&&input[c + 1] == '"') {
						token[current_token]->t[in++] = input[c];
						c++;
						token[current_token]->t[in++] = input[c];
						c++;
						continue;
					}
					//contiguous double-quotes
					if (input[c] == '"'&&input[c + 1] == '"') {
						token[current_token]->t[in++] = input[c];
						c++;
						token[current_token]->t[in++] = input[c];
						c++;
						continue;
					}
					//terminate string
					if (input[c] == '"') {
						//c++;
						break;
					}
					token[current_token]->t[in++] = input[c];
					c++;
				}
				token[current_token]->t[in] = '\0';
				break;
			}
			/*identify characters*/
			if (input[c] == '\'') {
				//identify token type
				if (!tokenTypeSet) {
					token[current_token]->ttype = character;
					tokenTypeSet = 1;
				}
				c++;
				while (1) {
					//backslash escaped
					if (input[c] == '\\'&&input[c + 1] == '\\') {
						token[current_token]->t[in++] = input[c];
						c++;
						token[current_token]->t[in++] = input[c];
						c++;
						continue;
					}
					//sigle-quote escaped
					if (input[c] == '\\'&&input[c + 1] == '\'') {
						token[current_token]->t[in++] = input[c];
						c++;
						token[current_token]->t[in++] = input[c];
						c++;
						continue;
					}
					//contiguous single-quotes
					if (input[c] == '\''&&input[c + 1] == '\'') {
						token[current_token]->t[in++] = input[c];
						c++;
						token[current_token]->t[in++] = input[c];
						c++;
						continue;
					}
					//terminate character
					if (input[c] == '\'') {
						//c++;
						break;
					}
					token[current_token]->t[in++] = input[c];
					c++;
				}
				token[current_token]->t[in] = '\0';
				break;
			}
			/*mark hexnumbers*/
			if (!tokenTypeSet) {
				if (input[c] == '0' && (input[c + 1] == 'x' || input[c + 1] == 'X')) {
					token[current_token]->t[in++] = input[c];
					c++;
					token[current_token]->t[in++] = input[c];
					c++;
					token[current_token]->ttype = hexnumber;
					tokenTypeSet = 1;
				}
				//continue;
			}
			/*read hex numbers*/
			if (token[current_token]->ttype == hexnumber) {
				if (HEXNUMBER(input[c]) || NUMBER(input[c])) {
					token[current_token]->t[in++] = input[c];
				}
				if (WHITESPACE(input[c + 1])) {
					token[current_token]->t[in] = '\0';
					//c++; //undo
					break;
				}
				if (SYMBOL(input[c + 1])) {
					token[current_token]->t[in] = '\0';
					break;
				}
				if (!(HEXNUMBER(input[c + 1]) || NUMBER(input[c + 1]))) {
					token[current_token]->t[in] = '\0';
					break;
				}
				continue;
			}
			/*read an alphabet or an underscore*/
			if (ALPHA(input[c]) || input[c] == '_') {
				//identify token type
				if (!tokenTypeSet) {
					token[current_token]->ttype = identifier;
					tokenTypeSet = 1;
				}
				token[current_token]->t[in++] = input[c];
				//detect end of token
				if (WHITESPACE(input[c + 1])) {
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
			/*read a symbol*/
			if (SYMBOL(input[c])) {
				if (!tokenTypeSet) {
					token[current_token]->ttype = spsymbol;
					tokenTypeSet = 1;
				}
				token[current_token]->t[in++] = input[c];
				//detect end of token
				if (WHITESPACE(input[c + 1])) {
					token[current_token]->t[in] = '\0';
					//c++; //undo
					break;
				}
				if (SYMBOL(input[c + 1]) || ALPHA(input[c + 1]) || NUMBER(input[c + 1])) {
					token[current_token]->t[in] = '\0';
					break;
				}
				continue;
			}
			/*read a number*/
			if (NUMBER(input[c])) {
				//identify token type
				if (!tokenTypeSet) {
					token[current_token]->ttype = number;
					tokenTypeSet = 1;
				}
				token[current_token]->t[in++] = input[c];
				//detect end of token
				if (WHITESPACE(input[c + 1])) {
					token[current_token]->t[in] = '\0';
					//c++; //undo
					break;
				}
				if (!(NUMBER(input[c + 1]))) {
					if (token[current_token]->ttype == identifier && (ALPHA(input[c + 1]) || input[c + 1] == '_')) {
						continue;
					}
					token[current_token]->t[in] = '\0';
					break;
				}
				/*if(SYMBOL(input[c+1])||ALPHA(input[c+1])){
					token[current_token]->t[in]='\0';
					break;
				}*/
				continue;
			}
		}
		token[current_token]->lineno = line;
		current_token++;
	}

	//DEBUGGER
	printf("Total nos of tokens = %d\n\n",current_token-1);
	fprintf(of, "Total nos of tokens = %d\n\n", current_token - 1);
	for (int i = 0; i < current_token - 1; i++) {
		printf("%s:%s\n",type2[token[i]->ttype],token[i]->t);
		if (token[i]->ttype == identifier) {
			for (int j = 0; j < KEYWORD_COUNT; j++) {
				if (strcmp(token[i]->t, keywords2[j])) {
					token[i]->ttype = keyword;
					break;
				}
			}
		}
		fprintf(of, "lnos:%d,%s:%s\n", token[i]->lineno, type2[token[i]->ttype], token[i]->t);
	}
	printf("%s", "***********************\n");
	//END OF LEXING
	return 0;
}