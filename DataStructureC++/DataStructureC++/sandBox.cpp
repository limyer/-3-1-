
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

	char *ptr = strtok(input, ")");      // ")" ���� ���ڸ� �������� ���ڿ��� �ڸ�, ������ ��ȯ


	while (ptr != NULL)               // �ڸ� ���ڿ��� ������ ���� ������ �ݺ�
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
		ptr = strtok(NULL, ")");      // ���� ���ڿ��� �߶� �����͸� ��ȯ
	}


	return 0;

}