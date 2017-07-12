#include <stdio.h>
#include <stdlib.h>
#include "huffman.h"

int main(void)
{
    float weights[10] = { 14, 3, 7, 9, 34, 8, 12, 1, 5, 20 };
    HUFF_TREE huff_tree;

    printf("weights of the nodes are: ");
    for (int i = 0; i < 10; i++) {
        printf("%.2f  ", weights[i]);
    }
    printf(" ");

    init_huff_tree(weights, 10, huff_tree);
    create_huff_tree(huff_tree);
    print_huff_code(huff_tree);
    destroy_huff_tree(huff_tree);

    system("pause");

    return 0;
}