#include <stdio.h>
#include <stdlib.h>
#include <float.h>
#include <memory.h>
#include "huffman.h"

void huff_encode(HUFF_TREE &tree);

// ��ʼ��һ�ù�������
void init_huff_tree(float *weights, int leaf_num, HUFF_TREE &tree)
{
    // ����Ҷ�ڵ���
    tree.leaf_num = leaf_num;

    // ����Ҷ�ڵ����������ù���������Ҫ�Ľڵ���
    // һ�ö������У�����Ϊ0��1��2�Ľڵ�֮�������¹�ϵ��
    // n = n0 + n1 + n2 �� n = n1 + 2*n2 + 1
    // ��ˣ��� n2 = n0 - 1
    // �ڹ��������У�ֻ�г���Ϊ0��2�Ľڵ�
    // ��ˣ�n = n0 + n2 = 2*n0 - 1
    tree.node_num = 2 * leaf_num - 1;

    // Ϊ�ڵ����ռ�
    tree.nodes = new HUFF_NODE[tree.node_num];
    if (tree.nodes == NULL) {
        printf("memry out. ");
        exit(1);
    }

    // Ϊÿ��Ҷ�ڵ����洢������������ַ�����
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

    // �Խڵ�ֵ���г�ʼ��
    for (int i = 0; i < tree.node_num; i++) {
        // Ҷ�ڵ�洢�ڽڵ�����ǰ�����Ҹ������ǵĳ�ʼȨֵ
        if (i < leaf_num) {
            tree.nodes[i].weight = weights[i];
        }
        else {
            tree.nodes[i].weight = 0;
        }

        // ���Һ����Լ����׽ڵ�ָ�루������������ʼ��Ϊ�գ�-1��
        tree.nodes[i].parent = -1;
        tree.nodes[i].lchild = -1;
        tree.nodes[i].rchild = -1;
    }
}

// ���ݳ�ʼ��֮��Ĺ��������������������Ĺ�������������ÿ��Ҷ�ڵ�Ĺ���������
void create_huff_tree(HUFF_TREE &tree)
{
    float min1 = FLT_MAX, min2 = FLT_MAX;        // min1��ŵ�ǰ��Сֵ��min2��ŵ�ǰ��Сֵ
    int lchild_temp = -1, rchild_temp = -1;

    // ��֯�������Ľṹ
    // ÿһ�ִ���Щ��û�и��ڵ�Ľڵ���ѡ��Ȩֵ��С�������ڵ�
    // �ڵ������е���һ���ڵ�����Һ���ָ��ֱ�ָ����С�ʹ�С�������ڵ�
    // ���ң�Ȩֵ��Ϊ���������ڵ�ĺ�
    // ��С�ڵ�ʹ�С�ڵ�ĸ��ڵ�ָ����Ϊ�ýڵ������
    for (int i = tree.leaf_num; i < tree.node_num; i++) {
        // ����Щ��û�и��ڵ��������ѡ��Ȩֵ��С�������ڵ�
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

    // �Թ���������Ҷ�ڵ���б���
    huff_encode(tree);
}

// �Թ���������Ҷ�ڵ���б���
void huff_encode(HUFF_TREE &tree)
{
    // һ����ʱ���飬�Ӻ���ǰ�洢����������
    char* code_temp = new char[tree.leaf_num + 1];
    memset(code_temp, 0, tree.leaf_num + 1);
    // дָ���ʼλ����ʱ����ĩβ
    int start_pos = tree.leaf_num;

    // ��Ҷ�ڵ㿪ʼ��һֱ����ֱ�����ڵ�λ��
    // Ϊÿһ��Ҷ�ڵ���б���
    for (int i = 0; i < tree.leaf_num; i++) {
        int cur_node = i;
        int parent = tree.nodes[i].parent;
        // һֱ�����ڵ�
        while (parent != -1) {
            // ����ǰ�ڵ��Ǹ��ڵ�����ӣ������Ϊ0
            if (tree.nodes[parent].lchild == cur_node) {
                code_temp[--start_pos] = '0';
            }
            // ����ǰ�ڵ��Ǹ��ڵ���Һ��ӣ������Ϊ1
            else if (tree.nodes[parent].rchild == cur_node) {
                code_temp[--start_pos] = '1';
            }
            // ��������
            cur_node = parent;
            parent = tree.nodes[parent].parent;
        }

        // ����ʱ���������еı��뿽�������������еĽڵ��Ӧ�ı���洢�ռ���
        memcpy(tree.huff_code[i], (code_temp + start_pos), (tree.leaf_num - start_pos + 1));

        memset(code_temp, 0, tree.leaf_num + 1);
        start_pos = tree.leaf_num;
    }

    delete[] code_temp;
}

// ��ӡÿ��Ҷ�ڵ�Ĺ���������
void print_huff_code(HUFF_TREE &tree)
{
    for (int i = 0; i < tree.leaf_num; i++) {
        printf("node weight: %.2f", tree.nodes[i].weight);
        printf("	huffman code: %s ", tree.huff_code[i]);
    }
}

// ���ٹ�������
void destroy_huff_tree(HUFF_TREE &tree)
{
    // �ͷŽڵ�ռ�
    if (tree.nodes != NULL) {
        delete[] tree.nodes;
    }

    // �ͷŹ���������ռ�
    if (tree.huff_code != NULL) {
        for (int i = 0; i < tree.leaf_num; i++) {
            if (tree.huff_code[i] != NULL) {
                delete[] tree.huff_code[i];
            }
        }
        delete[] tree.huff_code;
    }
}