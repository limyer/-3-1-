// �ѱ��װ��� ����Ʈ�����а� 2018125084 �ӿ���
// �ڷᱸ���� C++ ���α׷��� (Ȳ���� ������)
// 2020�� 3�� 30��

// �Ʒ��� ���� ����� �����ϴ� ���α׷��� �ۼ��϶�.
// 1. �������� ������ �ؽ�Ʈ ������ �Է� �޴´�.
// 2. �ؽ�Ʈ�� �ִ� �ܾ���� �������� ����� �̿��Ͽ� �����Ѵ�.�̶� �����ȣ(�� ��, .��)�� �����Ѵ�.
// 3. ���ĵ� �ܾ� ����Ʈ���� �ߺ��� �ܾ�� �����Ѵ�.
// 4. ����ڰ� �ܾ �Է��ϸ� �� �ܾ ���ĵ� �ܾ� ����Ʈ���� �� ��° �ܾ����� �� ����� ��ȯ�Ѵ�.
// ��ȯ�� �̿� Ž�� ����� ����ϵ��� �Ѵ�.

// �Է� ������ ������ "input.txt"�� ����(�����ȣ, �ߺ� �ܾ ������ ���� ���)
// �����(����� ����) : �Է����� ����, �ܾ� ���� ���, �ߺ� ���� ���, �ܾ� �˻� ��� ��
// �ܾ� ���� ���, �ߺ� ���� ��� ����(�ܾ� ��ġ, �ܾ�)�� ���� ������ ǥ���ϸ�, ��� ����(ǥ, ����Ʈ ��)�� �������� ����
// �˻� ���� �Է¿� ���ԵǾ� �ִ� �ܾ�, ���� �ܾ� �� 3���� �˻��Ͽ� ��� ���̰� �Ѵ�.
// ���α׷��� ���� ���� �� ���� �������� �ݺ������� �˻��� �� �ֵ��� �Ѵ�. (.(��ħǥ)�Է½� ���α׷� ����)
// �����ȣ�� �ּ� '"!?,. 6���� ���ܽ�Ų��.
// ���忡 �����ϴ� �ܾ �Է��� �ÿ��� �ܾ��� ��ġ(1���� ����), ���� ��쿡�� - 1�� ����Ѵ�.
// �ڵ忡 �ڸ�Ʈ�� �޾Ƽ� �����ϱ� ������ �Ѵ�.
// ** �ݵ�� ������ �־��� �˰����� ����Ѵ�. (��������, ��ȯ�� �̿� Ž��)
// 
// 
// ��������, ��ȯ�� �̿� Ž���� �ݵ�� ���� ����


#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>

#define R 1001
using namespace std;

// ���� ��ȣ ���� �Լ�
void GetInFormat(char* s) {
	// dest �����ʹ� s�� �����ϰ� ����
	char *dest = s;
	// s�� ������
	while (*s != 0) {
		if (*s != ' ' && 
			*s != '\"' && 
			*s != '.' && 
			*s != '\'' && 
			*s != ',' &&
			*s != '!' &&
			*s != '?') { // s�� �����Ͱ� �����ȣ�� ����Ű�� ���� ����
			*dest = *s; // dest�� ����Ű�� ��ġ�� s�� ����
			dest++; // dest�� ��������
		}
		s++; // �����ȣ�� �����ѵ� s���� �Ѿ
	}
	*dest = 0; // �������� null����
}

// �������� �Լ�
void SelectionSort(char Array[][R], const int Size) {
	int min = 0;
	for (int i = 0; i < Size; i++) {
		min = i;
		for (int j = i + 1; j < Size; j++) {
			if (strcmp(Array[min], Array[j]) == 1) { // min�� ���ڰ� j�� ���ں��� �ڿ� �´ٸ�
				min = j;
			}
		}
		// ���� ���� ���� ������ ��ȯ
		swap(Array[min], Array[i]);
	}
}

// �̿� Ž�� �Լ�
int BinarySearch(char Array[][R], const char target[], const int size) {
	// ���ĵ� �迭���� target�� Ž��
	int left = 0, right = size - 1;
	while (left <= right) {
		int middle = (left + right) / 2;
		if (strcmp(Array[middle], target) == 1) right = middle - 1;
		else if (strcmp(Array[middle], target) == -1) left = middle + 1;
		else return middle;
	}
	// �߰ߵ��� �ʾ��� ��
	return -1;
}



char word[R]; // �ؽ�Ʈ���Ͽ��� ���ڸ� �״�� �޾ƿ��� �����Դϴ�.
char WordDataSet[R][R]; // ���� �����͸� ����ִ� 2���� �迭�Դϴ�.
char searchWord[R]; // �˻����� �Է¹��� �ܾ��Դϴ�.
bool dupFlag = false; // �ߺ� Ȯ�� �÷���
bool escFlag = false; // ���α׷� Ż�� �÷���

int main() {

	FILE *f = fopen("input.txt", "r"); // ������ �б� �������� �޾��ݴϴ�. 
	printf("������ �ε� ���Դϴ�...\n\n");

	if (f == NULL) {
		printf("������ �����ϴ�\n"); // ������ �������� ���� ��� ����ó���Դϴ�.
		return 0;
	}
	int i = 0; //  ���� �����͵��� �ε����� ǥ���ϴ� �����Դϴ�.

	printf("���� ���� ����:\n");
	// ���� �����ͼ� ǥ��
	while (!feof(f)) {
		fgets(word, sizeof(word), f);
		printf("%s\n", word);
	}

	// eof�� ���Ա� ������ �ϴ� ������ �ݽ��ϴ�
	fclose(f);

	FILE *rf = fopen("input.txt", "r"); // ���� �ٽ� ����

	while (!feof(rf)) {
		fscanf(rf, "%s", WordDataSet[i]); // �ؽ�Ʈ���Ͽ��� ���ڿ��� �޽��ϴ�.
		int size = strlen(WordDataSet[i]); //  �ؽ�Ʈ���Ͽ� �ִ� ���ڿ��� ���̸� ���մϴ�.
		GetInFormat(WordDataSet[i]); // ���� ��ȣ ����
		for (int j = 0; j < i; j++) {
			if (strcmp(WordDataSet[i], WordDataSet[j]) == 0) {
				dupFlag = true;
				break; // ���� �ܾ� ã���� ��� �÷��� ����� Ż��
			}
		}
		if (!dupFlag) {
			i++; // ���� �ܾ� ���� ��
		}
		else {
			dupFlag = false; // ���� ���� i�� ������Ű�� �ʰ� ��ݺ�
		}
	}

	printf("\n�ߺ� �� �����ȣ ���� ���:\n");
	for (int j = 0; j < i; j++) { // �ߺ� �� �����ȣ�� ���ŵ� ���ڿ��� ����մϴ�.
		printf("%d. %s\n",j+1, WordDataSet[j]);
	}

	
	// ���� ���� ����
	SelectionSort(WordDataSet, i);

	printf("\n���� ���:\n");
	for (int j = 0; j < i; j++) { // �������ķ� ���ĵ� ���ڿ��� ����մϴ�.
		printf("%d. %s\n",j+1, WordDataSet[j]);
	}


	while (!escFlag) { // �÷��װ� ������ ������ �ݺ��մϴ�
		printf("\n�˻��� �ܾ �Է����ּ��� (��ħǥ�� ����) : ");
		scanf("%s", &searchWord);
		if (strcmp(searchWord, ".") == 0) { // ��ħǥ�� �Է� �޾��� ���
			printf("���α׷��� �����մϴ�.");
			escFlag = true;
		}
		else {
			int result = BinarySearch(WordDataSet, searchWord, i); // �̿� Ž���� �����մϴ�
			if (result == -1) { // �ܾ ���� ���
				printf("-1, �ܾ ã�� ���߽��ϴ�.\n");
			}
			else {
				printf("%s�� ��ġ : %d\n", searchWord, result + 1); // result�� 0��°���� ���� ������ 1�� ������� �մϴ�
			}
		}
	}
	fclose(rf);

	return 0;
}