
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>
using namespace std;

int main() {
	char input[1000] = { NULL };
	char temp[100] = { NULL };
	int index = 0;
	int count = 0;
	float coef = 0.;
	int exp = 0;

	cin.getline(input, 1000);

	char *ptr = strtok(input, ")");      // ")" 공백 문자를 기준으로 문자열을 자름, 포인터 반환


	while (ptr != NULL)               // 자른 문자열이 나오지 않을 때까지 반복
	{
		strcpy(temp, ptr);
		printf("%s\n", temp);
		while (temp[index] != NULL) {
			if (isdigit(temp[index])) {
				if (count == 0) {
					coef = (float)(temp[index] - '0');
					count++;
				}
				else {
					exp = (temp[index] - '0');
				}
			}
			index++;
		}
		index = 0;
		count = 0;
		printf("%f is coef, %d is exp\n", coef, exp);
		ptr = strtok(NULL, ")");      // 다음 문자열을 잘라서 포인터를 반환
	}


	return 0;

}