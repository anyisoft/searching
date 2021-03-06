// linear_probing.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include "pch.h"
#include <iostream>

#include <time.h>

#define	MAX	1000
#define	NUM	10
#define	BLANK	-1

struct list {
	int key;
	struct list *next;
};
typedef struct list node;
typedef node *link;

node hashtable_node[MAX];

int hashtable[MAX];

int hashfunc(int value)
{
	return value % MAX;
}

/**
 * Folding
 * 1428725012 => 1428 + 7250 + 12 => 9878
 * 1428725012 => 142 + 872 + 501 + 2 => 1014+503 => 1517
 * 本例限定取1000 以内的数，最大99 + 99 = 198
 */
int hashfunc_folding(int value)
{
	int hashedIndex;
	int digit1, digit2;

	if (value > 9999) {
		return MAX - 1;
	}

	digit1 = value / 100;
	digit2 = (value % 100);

	hashedIndex = digit1 + digit2;

	return hashedIndex;
}

/**
 * the mid of square
 * 本例限定取右数第3、4、5 位3个数字为索引
 * 9999*9999 => 99980001 => 800
 */
int hashfunc_midsquare(int value)
{
	int square, hashedIndex;
	int digit3, digit4, digit5;

	if (value > 9999) {
		return MAX - 1;
	}

	square = value * value;
	digit5 = (square / 10000)%10;
	digit4 = (square / 1000)%10;
	digit3 = (square / 100)%10;

	hashedIndex = digit5 * 100 + digit4 * 10 + digit3;

	return hashedIndex;
}

/**
 * 数字分析法，直接根据目标数据集特征进行分析映射
 * 027724531 => 431
 * 027713547 => 347
 * 027737624 => 724
 * 027728513 => 813
 * 027715565 => 565
 * 注意是取的右数第1、2、4 位
 * 简单起见，仍使用随机数举例
 */
int hashfunc_analysis(int value)
{
	int hashedIndex;
	int digit1, digit2, digit4;

	digit4 = (value / 1000) % 10;
	digit2 = (value / 10) % 10;
	digit1 = value % 10;

	hashedIndex = digit4 * 100 + digit2 * 10 + digit1;

	return hashedIndex;
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

void createtable_node(int key)
{
	link ptr;
	link new_node;
	int pos;

	new_node = (link)malloc(sizeof(node));
	new_node->key = key;
	new_node->next = NULL;

	//pos = hashfunc(key);
	//pos = hashfunc_folding(key);
	//pos = hashfunc_midsquare(key);
	pos = hashfunc_analysis(key);
	ptr = hashtable_node[pos].next;
	if (ptr != NULL) {
		new_node->next = ptr;
		hashtable_node[pos].next = new_node;
	}
	else {
		hashtable_node[pos].next = new_node;
	}
}

int linkhash(int key)
{
	link ptr;
	int pos;

	//pos = hashfunc(key);
	//pos = hashfunc_folding(key);
	//pos = hashfunc_midsquare(key);
	pos = hashfunc_analysis(key);
	ptr = hashtable_node[pos].next;
	while (ptr != NULL) {
		if (ptr->key == key) {
			return 1;
		}
		else {
			ptr = ptr->next;
		}
	}

	return 0;
}

int main()
{
	link ptr;
	int checked[50];
	int i, j, temp;
	long temptime;

	/*for (i = 0; i < MAX; i++) {
		hashtable[i] = BLANK;
	}*/

	for (i = 0; i < MAX; i++) {
		hashtable_node[i].next = NULL;
	}

	for (i = 0; i < 50; i++) {
		checked[i] = 0;
	}

	printf("hash table's content:\n");
	srand(time((time_t*)&temptime) % 60);
	i = 0;
	while (i < NUM) {
		temp = rand() % 10000;
		//if (0 == checked[temp]) {
			createtable_node(temp);
			/*createtable(temp);
			printf("%2d => ", temp);
			for (j = 0; j < MAX; j++) {
				printf("[%2d]", hashtable[j]);
			}
			printf("\n");*/
			//checked[temp] = 1;
			i++;
		//}
	}
	for (i = 0; i < MAX; i++) {
		ptr = hashtable_node[i].next;
		if (ptr && ptr->key != 0) {
			printf("\n%2d ==> ", i);
			while (ptr != NULL) {
				printf("[%2d]", ptr->key);
				ptr = ptr->next;
			}
		}
	}

	while (1) {
		printf("\nplease input the value for search(0-49) ==> ");
		scanf_s("%d", &temp);
		if (temp != -1) {
			//i = linehash(temp);
			i = linkhash(temp);
			//if (i != -1) {
			if (i != 0) {
				printf("have found the value: %d\n", temp);
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
