#ifndef __HUFFMAN_H_FE
#define __HUFFMAN_H_FE

// ���������Ľڵ�ṹ
typedef struct _huff_node {
    float    weight;            // �ڵ�Ȩ��
    int        lchild;            // �ڵ������
    int        rchild;            // �ڵ���Һ���
    int        parent;            // �ڵ�ĸ��ڵ�
} HUFF_NODE, *PHUFF_NODE;

// ��������
typedef struct _huff_tree {
    int            leaf_num;        // ����Ҷ�ڵ�Ҳ������Ҫ����Ľڵ����Ŀ
    int            node_num;        // ��Ӧ��Ҷ�ڵ����Ŀ,����������һ����Ҫ 2*leaf_num - 1 ���ڵ�
    PHUFF_NODE    nodes;            // �������еĽڵ�,��һ����������Щ�ڵ�
    char**        huff_code;        // Ҷ�ڵ��Ӧ�Ĺ���������
} HUFF_TREE;

// ��ʼ��һ�ù�������������Ϊ���������ռ��Լ�Ȩ�صȵĳ�ʼ��
void init_huff_tree(float *weights, int leaf_num, HUFF_TREE &tree);

// ����һ�ù���������ǰ���Ǳ����Ѿ���ʼ����
void create_huff_tree(HUFF_TREE &tree);

// ��ӡһ���Ѿ������õĹ���������Ҷ�ڵ��Ӧ�Ĺ���������
void print_huff_code(HUFF_TREE &tree);

// ����һ�ù����������ͷų�ʼ��ʱ����Ľڵ��Լ�����ռ�
void destroy_huff_tree(HUFF_TREE &tree);

#endif
