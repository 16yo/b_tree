#include "tree.h"

b_tree create_empty_b_tree() {
    b_tree t;
    t.n = 0;
    t.last_id = -1;
    t.d = create_empty_imap();
    t.c = create_empty_imap();
    t.root = NULL;
    return t;
}

int8_t is_empty_b_tree(const b_tree* t) {
    return t->root == NULL;
}

void init_b_tree(b_tree* t, const int64_t data) {
    if (!is_empty_b_tree(t)) {
        exception_exit("Initializing not empty b_tree");
    }
    t->root = new_node(0, data, NULL);
    t->last_id = 0;
    t->n = 1;
    t->d = create_empty_imap();
    imap_add(&(t->d), 0, 0);
    imap_copy(&(t->c), &(t->d));
}

void add_node_by_id (b_tree* t, const int64_t id, const SIDE s, const int64_t data) {
    // Create new node
    node* v = node_by_id(t->root, id);
    add_node_by_node(t, v, s, data);
}

void add_node_by_node(b_tree* t, const node* p, const SIDE s, const int64_t data) {
    node* v = p;
    // Add new node to accentor with given id
    if (s == N_LEFT) {
        if (v->left == NULL) {
            v->left = new_node(t->last_id + 1, data, v);
        } else {
            exception_exit("%ld node already has left child - %ld node", v->id, v->left->id);
        }
    } else {
        if (v->right == NULL) {
            v->right = new_node(t->last_id + 1, data, v);
        }
        else {
            exception_exit("%ld node already has right child - %ld node", v->id, v->right->id);
        }
    }
    t->last_id++;
    t->n++;
}

node* node_by_id(const node* root, int64_t id) {
    node* i = root;
    if (i == NULL || i->id == id) {
        return i;
    }
    node* l = i->left,* r = i->right;
    l = node_by_id(l, id);
    r = node_by_id(r, id);
    if (l != NULL) {
        return l;
    }
    if (r != NULL) {
        return r;
    }
    return NULL;
}

node* new_node(const int64_t id, const int64_t data, const node* p) {
    node* v = (node*)malloc(sizeof(node));
    v->id= id;
    v->data = data;
    v->left = NULL;
    v->right = NULL;
    v->p = p;
    return v;
}

void delete_node_by_id(b_tree* t, const int64_t id) {
    node* v = node_by_id(t->root, id);
    delete_node_by_node(t, v);
}

void delete_node_by_node(b_tree* t, node* v) {
    node* i = v;

    node* l = v->left,* r = v->right;

    if (!(l == NULL)) {
        delete_node_by_node(t, l);
    }
    if (!(r == NULL)) {
        delete_node_by_node(t, r);
    }
    if (!(i->p == NULL)) {
        if (i->p->left == i) {
            i->p->left = NULL;
        } else {
            i->p->right = NULL;
        }
    }
    free(i);
    --t->last_id;
    --t->n;
    if (t->n == 0) {
        t->root = NULL;
    }
}

int64_t data_by_id(const b_tree* t, int64_t id) {
    node* v = node_by_id(t->root, id);
    if (v == NULL) {
        exception_exit("There is no node with given id in the b_tree\n")
    }
    return v->data;
}

int8_t node_is_in_b_tree(const node* root, const node* v) {
    if (v == NULL || root == NULL) {
        return 0;
    }
    if (root == v) {
        return 1;
    }
    return node_is_in_b_tree(root->left, v) \
        || node_is_in_b_tree(root->right, v);
}

void clear_tree(b_tree* t) {
    delete_node_by_node(t, t->root);
    clear_imap(&(t->d));
    clear_imap(&(t->c));
}

void update_depth(b_tree* t) {
    node* i = t->root;
    if (i == NULL) {
        clear_tree(t);
        return;
    }
    clear_imap(&(t->d));
    __update_depth(&(t->d), t->root, 0);
}

void __update_depth(imap* d, const node* root, int64_t depth) {
    if (root == NULL) {
        return;
    }
    imap_add(d, root->id, depth);
    __update_depth(d, root->left, depth + 1);
    __update_depth(d, root->right, depth + 1);
}

void update_degree(b_tree* t) {
    node* i = t->root;
    if (i == NULL) {
        clear_tree(t);
        return;
    }
    clear_imap(&(t->c));
    __update_degree(&(t->c), t->root);
}

void __update_degree(imap* c, const node* root) {
    if (root == NULL) {
        return;
    }
    int8_t c_ = 0;
    if (!(root->left == NULL)) {
        ++c_;
        __update_degree(c, root->left);
    }
    if (!(root->right == NULL)) {
        ++c_;
        __update_degree(c, root->right);
    }    
    imap_add(c, root->id, c_);
}

void print_b_tree(const node* root, uint8_t tab, const int8_t side) {
    if (root == NULL) {
        return;
    }
    printf("%ld", root->id);
    for (uint8_t i = 0; i <= tab; ++i) {
        printf("\t");
        printf("|");
    }
    if (side == -1) {
        printf("L: ");
    } else if (side == 1) {
        printf("R: ");
    } else {
        printf("Root: ");
    }
    printf("%ld\n", root->data);
    print_b_tree(root->left, tab + 1, -1);
    print_b_tree(root->right, tab + 1, 1);
    //printf("\n");
}