// linear_probing.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include "pch.h"
#include <iostream>

#include <time.h>

#define	MAX	10
#define	NUM	8
#define	BLANK	-1

int hashtable[MAX];

int hashfunc(int value)
{
	return value % MAX;
}

int linehash(int key)
{
	int pos;
	int temp;

	pos = hashfunc(key);
	temp = pos;

	while (hashtable[temp] != key && hashtable[temp] != BLANK) {
		temp = (temp + 1) % MAX;
		if (pos == temp) {
			return -1;
		}
	}

	if (BLANK == hashtable[temp]) {
		return -1;
	}
	else {
		return temp;
	}
}

void createtable(int key)
{
	int pos;
	int temp;

	pos = hashfunc(key);
	temp = pos;
	while (hashtable[temp] != BLANK) {
		temp = (temp + 1) % MAX;
		if (pos == temp) {
			printf("the hash table is FULL!\n");
			return;
		}
	}

	hashtable[temp] = key;
}

int main()
{
	int checked[50];
	int i, j, temp;
	long temptime;

	for (i = 0; i < MAX; i++) {
		hashtable[i] = BLANK;
	}

	for (i = 0; i < 50; i++) {
		checked[i] = 0;
	}

	printf("hash table's content:\n");
	srand(time((time_t*)&temptime) % 60);
	i = 0;
	while (i < NUM) {
		temp = rand() % 50;
		if (0 == checked[temp]) {
			createtable(temp);
			printf("%2d => ", temp);
			for (j = 0; j < MAX; j++) {
				printf("[%2d]", hashtable[j]);
			}
			printf("\n");
			checked[temp] = 1;
			i++;
		}
	}

	while (1) {
		printf("\nplease input the value for search(0-49) ==> ");
		scanf_s("%d", &temp);
		if (temp != -1) {
			i = linehash(temp);
			if (i != -1) {
				printf("have found the value: %d[%d]\n", temp, i);
			}
			else {
				printf("have NOT found the value: %d\n", temp);
			}
		}
		else {
			exit(1);
		}
	}
}

// 运行程序: Ctrl + F5 或调试 >“开始执行(不调试)”菜单
// 调试程序: F5 或调试 >“开始调试”菜单

// 入门提示: 
//   1. 使用解决方案资源管理器窗口添加/管理文件
//   2. 使用团队资源管理器窗口连接到源代码管理
//   3. 使用输出窗口查看生成输出和其他消息
//   4. 使用错误列表窗口查看错误
//   5. 转到“项目”>“添加新项”以创建新的代码文件，或转到“项目”>“添加现有项”以将现有代码文件添加到项目
//   6. 将来，若要再次打开此项目，请转到“文件”>“打开”>“项目”并选择 .sln 文件
