#include <stdio.h>

/* another way of doing this:
struct node {
	int data;
	int len;
};
typedef struct node type_node;
typedef struct node * type_node_p;
*/

typedef struct node {
	int data;
	int len;
} type_node, *type_node_p;

int main() {
	type_node n = {10, 20};
	type_node_p p = &n;
	printf("%d %d\n", n.data, n.len);
	printf("%d %d\n", p->data, p->len);
	return 0;
}

/* output:
10 20
10 20
*/

// gcc -g3 -std=c99 -pedantic -Wall typedef_test.c
