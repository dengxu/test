#include <stdio.h>
#include <iostream>

#define ABS(a) ((a) < 0 ? -(a) : (a))


class Tree {
public:
    Tree() : left(NULL), right(NULL), dp_l(0), dp_r(0) {
    }
    
    int dp_l;
    int dp_r;
    int n;
    Tree *left;
    Tree *right;
};

void print_tabs(int tabs) {
    for (int i = 0; i < tabs; i++) {
        putchar('\t');
    }
}

void print_tree(Tree *t, int tabs) {
    if (!t) {
        return;
    }
    
    print_tabs(tabs);
    printf("%d (%d %d)\n", t->n, t->dp_l, t->dp_r);
    print_tree(t->left, tabs + 1);
    print_tree(t->right, tabs + 1);
}

void insert(Tree *root, Tree *node) {
    if (node->n < root->n) {
        root->dp_l++;
        if (!root->left) {
            root->left = node;
        } else {
            insert(root->left, node);
        }
        
    } else {
        root->dp_r++;
        if (!root->right) {
            root->right = node;
        } else {
            insert(root->right, node);
        }
    }
    
    if (root->dp_l > root->dp_r && root->dp_l - root->dp_r > 1) {
        
    } else if (root->dp_r > root->dp_l && root->dp_r - root->dp_l > 1) {
        
    }
}

Tree *maketree(int a[], int count) {
    
    Tree *root = NULL;
    
    for (int i = 0; i < count; i++) {
        
        Tree *node = new Tree;
        node->n = a[i];
        
        if (!root) {
            root = node;
        } else {
            insert(root, node);
        }
    }
    
    return root;
}

void balenceLL(Tree *tree) {
    
}

void balenceRR(Tree *tree) {
    
}

void balenceLR(Tree *tree) {
    
}

void balenceRL(Tree *tree) {
    
}
int main(int argc, const char * argv[]) {
    
    int a [] = {1, -1, 3, 4, 5, 6, 7};
    Tree *root = maketree(a, sizeof (a) / sizeof (a[0]));
    
    print_tree(root, 0);
    
    
    return 0;
    
}









