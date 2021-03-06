// btree.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include "pch.h"
#include <iostream>

struct tree {
	int data;
	struct tree *left;
	struct tree *right;
};
typedef struct tree treenode;
typedef treenode *btree;

btree insertnode(btree root, int value)
{
	btree newnode;
	btree current;
	btree back = NULL;

	newnode = (btree)malloc(sizeof(treenode));
	newnode->data = value;
	newnode->left = NULL;
	newnode->right = NULL;

	if (NULL == root) {
		return newnode;
	}
	else {
		current = root;
		while (current != NULL) {
			back = current;
			if (current->data > value) {
				current = current->left;
			}
			else {
				current = current->right;
			}
		}

		if (back->data > value) {
			back->left = newnode;
		}
		else {
			back->right = newnode;
		}
	}

	return root;
}

btree createbtree(int *data, int len)
{
	btree root = NULL;
	int i;

	for (i = 0; i < len; i++) {
		root = insertnode(root, data[i]);
	}

	return root;
}

btree btreesearch(btree ptr, int value)
{
	while (ptr != NULL) {
		if (ptr->data == value) {
			return ptr;
		}
		else {
			if (ptr->data > value) {
				ptr = ptr->left;
			}
			else {
				ptr = ptr->right;
			}
		}
	}

	return NULL;
}

int main()
{
	btree root = NULL;
	btree ptr = NULL;
	int value;
	int data[9] = { 55, 61, 41, 87, 24, 35, 79, 11, 99 };

	root = createbtree(data, 9);
	while (1) {
		printf("please input the value to search(0-99) ==> ");
		scanf_s("%d", &value);
		if (value != -1) {
			ptr = btreesearch(root, value);
			if (ptr != NULL) {
				printf("have found the data [%d].\n", ptr->data);
			}
			else {
				printf("have NOT found.\n");
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
