#ifndef M_TREE_H

#define M_TREE_H

#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
#include "imap.h"

typedef enum {
    N_LEFT,
    N_RIGHT
} SIDE;

// Inary tree node structure
typedef struct node {
    // Identification number of each node
    uint64_t id;
    // Data of node
    int64_t data;
    // Pointer to left node of b_three
    struct node* left;
    // Pointer to right node of b_tree
    struct node* right;
    // Pointer to node's accentor
    struct node* p;
} node;

// Binary tree
typedef struct b_tree{
    // Count of nodes
    int64_t n;
    // Id of last added node
    int64_t last_id;
    // Depth of each node
    imap d;
    // Degree of each node
    imap c;
    // Pointer to root node of b_tree   
    node* root;

} b_tree;

// Creates empty b_tree
// {
//      n = 0
//      last_id = -1
//      d = create_empty_vector()
//      c = create_empty_vector()
//      root = NULL
// }
b_tree create_empty_b_tree();

void copy_b_tree(b_tree* t, const b_tree* t_);

void _copy_b_subtree(node** root, const node* to_copy, const node* acc);

void init_b_tree(b_tree* t, const int64_t data);

// Checks if root pointer is NULL
int8_t is_empty_b_tree(const b_tree* t);

// Adds node py pointer to its accentor by accentors id
void add_node_by_node(b_tree* t, node* p, const SIDE s, const int64_t data);

// Adds node py pointer to its accentor by accentors id
void add_node_by_id(b_tree* t, const int64_t id, const SIDE s, const int64_t data);

//      Deletes node by id
void delete_node_by_id(b_tree* t, const int64_t id);

//      Deletes node by pointer
void delete_node_by_node(b_tree* t, node* v);

// Returns pointer to node of b_tree by id
node* node_by_id(const node* root, int64_t id);

// Returns id node data
int64_t data_by_id(const b_tree* t, int64_t id);

// Checks if given node is in b_tree
int8_t node_is_in_b_tree(const node* root, const node* v);

// Removes all nodes from b_tree and sets it empty
void clear_tree(b_tree* t);

// Node
// {
//     id = id;
//     data = data;
//     left = NULL;
//     right = NULL;
// }
node* new_node(const int64_t id, const int64_t data, const node* p);

void copy_node(node* v, const node* v_);

void update_depth(b_tree* t);

void __update_depth(imap* d, const node* root, int64_t depth);

void update_degree(b_tree* t);

void __update_degree(imap* c, const node* root);

void print_b_tree(const node* t, uint8_t tab, const int8_t side);

int8_t is_B_tree(const b_tree* t);

#define log_exception(M, ...)                                             \
{                                                                         \
    fprintf(stderr, "(%s:%d) " M "\n", __FILE__, __LINE__, ##__VA_ARGS__); \
}

#define exception_exit(M, ...)           \
{                                        \
    log_exception(M, ##__VA_ARGS__);     \
    exit(-1);                            \
}

#endif