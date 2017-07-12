#ifndef __HUFFMAN_H_FE
#define __HUFFMAN_H_FE

// 哈夫曼树的节点结构
typedef struct _huff_node {
    float    weight;            // 节点权重
    int        lchild;            // 节点的左孩子
    int        rchild;            // 节点的右孩子
    int        parent;            // 节点的父节点
} HUFF_NODE, *PHUFF_NODE;

// 哈夫曼树
typedef struct _huff_tree {
    int            leaf_num;        // 树中叶节点也就是需要编码的节点的数目
    int            node_num;        // 对应于叶节点的数目,哈夫曼树中一共需要 2*leaf_num - 1 个节点
    PHUFF_NODE    nodes;            // 树中所有的节点,用一个数组存放这些节点
    char**        huff_code;        // 叶节点对应的哈夫曼编码
} HUFF_TREE;

// 初始化一棵哈夫曼树，包括为这棵树分配空间以及权重等的初始化
void init_huff_tree(float *weights, int leaf_num, HUFF_TREE &tree);

// 创建一棵哈夫曼树，前提是必须已经初始化了
void create_huff_tree(HUFF_TREE &tree);

// 打印一棵已经创建好的哈夫曼树的叶节点对应的哈夫曼编码
void print_huff_code(HUFF_TREE &tree);

// 销毁一棵哈夫曼树，释放初始化时申请的节点以及编码空间
void destroy_huff_tree(HUFF_TREE &tree);

#endif
