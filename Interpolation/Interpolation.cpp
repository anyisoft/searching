// Interpolation.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include "pch.h"
#include <iostream>

#define	MAX	20

struct element {
	int key;
};
typedef struct element record;

record data[MAX] = {
	 2,  5,  7,  9, 17, 21, 25,
	33, 46, 48, 51, 52, 63, 69,
	77, 78, 80, 89, 94, 99
};

/**
 * the interpolation search algorithm with recursive
 */
int interfind(int key, int left, int right)
{
	int next_guess;
	int offset;
	int range;
	int index_range;
	int temp;

	if (data[left].key == key) {
		return left;
	}
	else {
		if (left == right || data[left].key == data[right].key) {
			return -1;
		}
		else {
			index_range = right - left;
			range = data[right].key - data[left].key;
			offset = key - data[left].key;
			temp = (offset*index_range) / range;
			next_guess = left + temp;
			if (next_guess == left) {
				next_guess++;
			}

			if (key < data[next_guess].key) {
				return interfind(key, left, next_guess - 1);
			}
			else {
				return interfind(key, next_guess, right);
			}
		}
	}
}

int intersearch(int n, int key)
{
	if (key < data[0].key || key > data[n - 1].key) {
		return -1;
	}
	else {
		return interfind(key, 0, n - 1);
	}
}

/**
 * 在一个已排序的数组中，用插补查找算法检索
 */
int main()
{
	int found;
	int value;

	while (1) {
		printf("\nplease input the value to search(0-100): ==> ");
		scanf_s("%d", &value);
		if (value != -1) {
			found = intersearch(MAX, value);
			if (found != -1) {
				printf("have found the value: %d[%d]", value, found);
			}
			else {
				printf("have NOT found value: %d", value);
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
