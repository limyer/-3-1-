// 한국항공대 소프트웨어학과 2018125084 임예랑
// 자료구조와 C++ 프로그래밍 (황수찬 교수님)
// 2020년 3월 30일

// 아래와 같은 기능을 수행하는 프로그램을 작성하라.
// 1. 문장으로 구성된 텍스트 파일을 입력 받는다.
// 2. 텍스트에 있는 단어들을 선택정렬 방법을 이용하여 정렬한다.이때 문장부호(“ ”, .등)는 제거한다.
// 3. 정렬된 단어 리스트에서 중복된 단어는 제거한다.
// 4. 사용자가 단어를 입력하면 그 단어가 정렬된 단어 리스트에서 몇 번째 단어인지 그 결과를 반환한다.
// 순환적 이원 탐색 기법을 사용하도록 한다.

// 입력 파일의 제목은 "input.txt"로 통일(문장부호, 중복 단어를 포함한 예문 사용)
// 결과물(출력할 내용) : 입력파일 내용, 단어 정렬 결과, 중복 제거 결과, 단어 검색 결과 예
// 단어 정렬 결과, 중복 제거 결과 등은(단어 위치, 단어)와 같이 쌍으로 표현하며, 출력 형식(표, 리스트 등)은 자유로이 선택
// 검색 예는 입력에 포함되어 있는 단어, 없는 단어 각 3개씩 검색하여 결과 보이게 한다.
// 프로그램의 종료 없이 한 번의 실행으로 반복적으로 검색할 수 있도록 한다. (.(마침표)입력시 프로그램 종료)
// 문장부호는 최소 '"!?,. 6개를 제외시킨다.
// 문장에 존재하는 단어를 입력할 시에는 단어의 위치(1부터 시작), 없는 경우에는 - 1을 출력한다.
// 코드에 코멘트를 달아서 이해하기 쉽도록 한다.
// ** 반드시 문제에 주어진 알고리즘을 사용한다. (선택정렬, 순환적 이원 탐색)
// 
// 
// 선택정렬, 순환적 이원 탐색을 반드시 직접 구현


#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>

#define R 1001
using namespace std;

// 문장 부호 삭제 함수
void GetInFormat(char* s) {
	// dest 포인터는 s와 동일하게 시작
	char *dest = s;
	// s의 끝까지
	while (*s != 0) {
		if (*s != ' ' && 
			*s != '\"' && 
			*s != '.' && 
			*s != '\'' && 
			*s != ',' &&
			*s != '!' &&
			*s != '?') { // s의 포인터가 문장부호를 가리키지 않을 때만
			*dest = *s; // dest가 가리키는 위치로 s값 변경
			dest++; // dest는 다음으로
		}
		s++; // 문장부호를 가리켜도 s값은 넘어감
	}
	*dest = 0; // 마지막에 null문자
}

// 선택정렬 함수
void SelectionSort(char Array[][R], const int Size) {
	int min = 0;
	for (int i = 0; i < Size; i++) {
		min = i;
		for (int j = i + 1; j < Size; j++) {
			if (strcmp(Array[min], Array[j]) == 1) { // min의 문자가 j의 문자보다 뒤에 온다면
				min = j;
			}
		}
		// 제일 낮은 값과 앞쪽을 교환
		swap(Array[min], Array[i]);
	}
}

// 이원 탐색 함수
int BinarySearch(char Array[][R], const char target[], const int size) {
	// 정렬된 배열에서 target을 탐색
	int left = 0, right = size - 1;
	while (left <= right) {
		int middle = (left + right) / 2;
		if (strcmp(Array[middle], target) == 1) right = middle - 1;
		else if (strcmp(Array[middle], target) == -1) left = middle + 1;
		else return middle;
	}
	// 발견되지 않았을 때
	return -1;
}



char word[R]; // 텍스트파일에서 문자를 그대로 받아오는 변수입니다.
char WordDataSet[R][R]; // 받은 데이터를 담고있는 2차원 배열입니다.
char searchWord[R]; // 검색으로 입력받을 단어입니다.
bool dupFlag = false; // 중복 확인 플래그
bool escFlag = false; // 프로그램 탈출 플래그

int main() {

	FILE *f = fopen("input.txt", "r"); // 파일을 읽기 형식으로 받아줍니다. 
	printf("파일을 로딩 중입니다...\n\n");

	if (f == NULL) {
		printf("파일이 없습니다\n"); // 파일이 존재하지 않을 경우 예외처리입니다.
		return 0;
	}
	int i = 0; //  받은 데이터들의 인덱스를 표시하는 변수입니다.

	printf("읽은 파일 내용:\n");
	// 전부 가져와서 표시
	while (!feof(f)) {
		fgets(word, sizeof(word), f);
		printf("%s\n", word);
	}

	// eof가 나왔기 때문에 일단 파일을 닫습니다
	fclose(f);

	FILE *rf = fopen("input.txt", "r"); // 파일 다시 열기

	while (!feof(rf)) {
		fscanf(rf, "%s", WordDataSet[i]); // 텍스트파일에서 문자열을 받습니다.
		int size = strlen(WordDataSet[i]); //  텍스트파일에 있는 문자열의 길이를 구합니다.
		GetInFormat(WordDataSet[i]); // 문장 부호 삭제
		for (int j = 0; j < i; j++) {
			if (strcmp(WordDataSet[i], WordDataSet[j]) == 0) {
				dupFlag = true;
				break; // 같은 단어 찾았을 경우 플래그 세우고 탈출
			}
		}
		if (!dupFlag) {
			i++; // 같은 단어 없을 때
		}
		else {
			dupFlag = false; // 있을 때는 i를 증가시키지 않고 재반복
		}
	}

	printf("\n중복 및 문장부호 제거 결과:\n");
	for (int j = 0; j < i; j++) { // 중복 및 문장부호가 제거된 문자열을 출력합니다.
		printf("%d. %s\n",j+1, WordDataSet[j]);
	}

	
	// 선택 정렬 실행
	SelectionSort(WordDataSet, i);

	printf("\n정렬 결과:\n");
	for (int j = 0; j < i; j++) { // 선택정렬로 정렬된 문자열을 출력합니다.
		printf("%d. %s\n",j+1, WordDataSet[j]);
	}


	while (!escFlag) { // 플래그가 세워질 때까지 반복합니다
		printf("\n검색할 단어를 입력해주세요 (마침표로 종료) : ");
		scanf("%s", &searchWord);
		if (strcmp(searchWord, ".") == 0) { // 마침표를 입력 받았을 경우
			printf("프로그램을 종료합니다.");
			escFlag = true;
		}
		else {
			int result = BinarySearch(WordDataSet, searchWord, i); // 이원 탐색을 실행합니다
			if (result == -1) { // 단어가 없을 경우
				printf("-1, 단어를 찾지 못했습니다.\n");
			}
			else {
				printf("%s의 위치 : %d\n", searchWord, result + 1); // result는 0번째부터 세기 때문에 1을 더해줘야 합니다
			}
		}
	}
	fclose(rf);

	return 0;
}