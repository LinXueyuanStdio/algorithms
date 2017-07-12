#include <stdio.h>
#include <stdlib.h>
#include <float.h>
#include <memory.h>
#include "huffman.h"

void huff_encode(HUFF_TREE &tree);

// 初始化一棵哈夫曼树
void init_huff_tree(float *weights, int leaf_num, HUFF_TREE &tree)
{
    // 保存叶节点数
    tree.leaf_num = leaf_num;

    // 根据叶节点数计算整棵哈夫曼树需要的节点数
    // 一棵二叉树中，出度为0、1、2的节点之间有如下关系：
    // n = n0 + n1 + n2 且 n = n1 + 2*n2 + 1
    // 因此，有 n2 = n0 - 1
    // 在哈夫曼树中，只有出度为0和2的节点
    // 因此，n = n0 + n2 = 2*n0 - 1
    tree.node_num = 2 * leaf_num - 1;

    // 为节点分配空间
    tree.nodes = new HUFF_NODE[tree.node_num];
    if (tree.nodes == NULL) {
        printf("memry out. ");
        exit(1);
    }

    // 为每个叶节点分配存储哈夫曼编码的字符数组
    tree.huff_code = new char*[leaf_num];
    if (tree.huff_code == NULL) {
        printf("memory out. ");
        exit(1);
    }
    else {
        for (int i = 0; i < leaf_num; i++) {
            if ((tree.huff_code[i] = new char[leaf_num + 1]) == NULL) {
                printf("memory out. ");
                exit(1);
            }
            else {
                memset(tree.huff_code[i], 0, leaf_num + 1);
            }
        }
    }

    // 对节点值进行初始化
    for (int i = 0; i < tree.node_num; i++) {
        // 叶节点存储在节点数组前部，且赋上它们的初始权值
        if (i < leaf_num) {
            tree.nodes[i].weight = weights[i];
        }
        else {
            tree.nodes[i].weight = 0;
        }

        // 左右孩子以及父亲节点指针（数组索引）初始化为空（-1）
        tree.nodes[i].parent = -1;
        tree.nodes[i].lchild = -1;
        tree.nodes[i].rchild = -1;
    }
}

// 根据初始化之后的哈夫曼树创建整棵完整的哈夫曼树，包括每个叶节点的哈夫曼编码
void create_huff_tree(HUFF_TREE &tree)
{
    float min1 = FLT_MAX, min2 = FLT_MAX;        // min1存放当前最小值，min2存放当前次小值
    int lchild_temp = -1, rchild_temp = -1;

    // 组织二叉树的结构
    // 每一轮从那些还没有父节点的节点中选出权值最小的两个节点
    // 节点数组中的下一个节点的左右孩子指针分别指向最小和次小的两个节点
    // 并且，权值置为以上两个节点的和
    // 最小节点和次小节点的父节点指针置为该节点的索引
    for (int i = tree.leaf_num; i < tree.node_num; i++) {
        // 从那些还没有父节点的数组中选择权值最小的两个节点
        for (int j = 0; j < i; j++) {
            if (tree.nodes[j].parent == -1) {
                if (tree.nodes[j].weight < min1) {
                    min2 = min1;
                    rchild_temp = lchild_temp;
                    min1 = tree.nodes[j].weight;
                    lchild_temp = j;
                }
                else if (tree.nodes[j].weight < min2) {
                    min2 = tree.nodes[j].weight;
                    rchild_temp = j;
                }
            }
        }

        tree.nodes[lchild_temp].parent = i;
        tree.nodes[rchild_temp].parent = i;
        tree.nodes[i].lchild = lchild_temp;
        tree.nodes[i].rchild = rchild_temp;
        tree.nodes[i].weight = min1 + min2;

        min1 = FLT_MAX;
        min2 = FLT_MAX;
        lchild_temp = -1;
        rchild_temp = -1;
    }

    // 对哈夫曼树的叶节点进行编码
    huff_encode(tree);
}

// 对哈夫曼树的叶节点进行编码
void huff_encode(HUFF_TREE &tree)
{
    // 一个临时数组，从后向前存储哈夫曼编码
    char* code_temp = new char[tree.leaf_num + 1];
    memset(code_temp, 0, tree.leaf_num + 1);
    // 写指针初始位于临时数组末尾
    int start_pos = tree.leaf_num;

    // 从叶节点开始，一直向上直到根节点位置
    // 为每一个叶节点进行编码
    for (int i = 0; i < tree.leaf_num; i++) {
        int cur_node = i;
        int parent = tree.nodes[i].parent;
        // 一直到根节点
        while (parent != -1) {
            // 若当前节点是父节点的左孩子，则编码为0
            if (tree.nodes[parent].lchild == cur_node) {
                code_temp[--start_pos] = '0';
            }
            // 若当前节点是父节点的右孩子，则编码为1
            else if (tree.nodes[parent].rchild == cur_node) {
                code_temp[--start_pos] = '1';
            }
            // 继续向上
            cur_node = parent;
            parent = tree.nodes[parent].parent;
        }

        // 将临时编码数组中的编码拷贝到哈夫曼树中的节点对应的编码存储空间中
        memcpy(tree.huff_code[i], (code_temp + start_pos), (tree.leaf_num - start_pos + 1));

        memset(code_temp, 0, tree.leaf_num + 1);
        start_pos = tree.leaf_num;
    }

    delete[] code_temp;
}

// 打印每个叶节点的哈夫曼编码
void print_huff_code(HUFF_TREE &tree)
{
    for (int i = 0; i < tree.leaf_num; i++) {
        printf("node weight: %.2f", tree.nodes[i].weight);
        printf("	huffman code: %s ", tree.huff_code[i]);
    }
}

// 销毁哈夫曼树
void destroy_huff_tree(HUFF_TREE &tree)
{
    // 释放节点空间
    if (tree.nodes != NULL) {
        delete[] tree.nodes;
    }

    // 释放哈夫曼编码空间
    if (tree.huff_code != NULL) {
        for (int i = 0; i < tree.leaf_num; i++) {
            if (tree.huff_code[i] != NULL) {
                delete[] tree.huff_code[i];
            }
        }
        delete[] tree.huff_code;
    }
}