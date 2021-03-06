// btree_bisearch.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
// 使用折半查找法创建二叉查找树
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

/**
 * ril range_index_left
 * rir range_index_right
 */
btree createbtree_bisearch(int *data, int ril, int rir)
{
	int mid;
	btree newnode;

	if (ril <0 || ril > rir) {
		return NULL;
	}

	mid = (ril + rir) / 2;

	newnode = (btree)malloc(sizeof(treenode));
	newnode->data = data[mid];
	newnode->left = createbtree_bisearch(data, ril, mid-1);
	newnode->right = createbtree_bisearch(data, mid+1, rir);

	return newnode;
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
	int data[9] = { 5, 19, 23, 47, 56, 89, 91, 95, 99 };

	root = createbtree_bisearch(data, 0, 8);
	
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
