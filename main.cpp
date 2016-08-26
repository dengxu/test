#include <stdio.h>
#include <iostream>

#define ABS(a) ((a) < 0 ? -(a) : (a))

#define MAX(a, b) ((a) < (b) ? (b) : (a))
#define MIN(a, b) ((a) < (b) ? (a) : (b))


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

int height(Tree *node) {
    if (!node) {
        return -1;
    }
    
    return MAX(node->dp_l, node->dp_r);
}

Tree * balenceLL(Tree *tree) {
    Tree *l = tree->left;
    tree->left = l->right;
    l->right = tree;
    tree->dp_l = height(tree->left) + 1;
    l->dp_r = height(l->right) + 1;
    return l;
}


Tree *balenceRR(Tree *tree) {
    Tree *r = tree->right;
    tree->right = r->left;
    r->left = tree;
    tree->dp_r = height(tree->right) + 1;
    r->dp_l = height(r->left) + 1;
    return r;
}

Tree *balenceLR(Tree *tree) {
    tree->left = balenceRR(tree->left);
    return balenceLL(tree);
}

Tree *balenceRL(Tree *tree) {
    tree->right = balenceLL(tree->right);
    return balenceRR(tree);
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

Tree *insert(Tree *root, Tree *node, Tree *parent) {
    Tree *retNode = root;

    if (node->n < root->n) {
        if (!root->left) {
            root->left = node;
            root->dp_l++;
        } else {
            root->left = insert(root->left, node, root);
            root->dp_l = height(root->left) + 1;
        }
        
    } else {
        
        if (!root->right) {
            root->right = node;
            root->dp_r++;
        } else {
            root->right = insert(root->right, node, root);
            root->dp_r = height(root->right) + 1;
        }
    }
    
    if (root->dp_l > root->dp_r) {
        if (root->dp_l - root->dp_r > 1) {
            // L
            Tree *l = root->left;
            if (l->dp_l > l->dp_r) {
                // LL
                Tree *newNode = balenceLL(root);
                retNode = newNode;
                
                // 修复树
                if (parent) {
                    if (parent->left == root) {
                        parent->left = newNode;
                        parent->dp_l = height(parent->left) + 1;
                    } else {
                        parent->right = newNode;
                        parent->dp_r = height(parent->right) + 1;
                    }
                }
            } else if (l->dp_r > l->dp_l) {
                // LR
                Tree *newNode = balenceLR(root);
                retNode = newNode;
                
                // 修复树
                if (parent) {
                    if (parent->left == root) {
                        parent->left = newNode;
                        parent->dp_l = height(parent->left) + 1;
                    } else {
                        parent->right = newNode;
                        parent->dp_r = height(parent->right) + 1;
                    }
                }
            }
        }
    } else {
        if (root->dp_r - root->dp_l > 1) {
            // R
            Tree *r = root->right;
            if (r->dp_r > r->dp_l) {
                // RR
                Tree *newNode = balenceRR(root);
                retNode = newNode;
                
                // 修复树
                if (parent) {
                    if (parent->left == root) {
                        parent->left = newNode;
                        parent->dp_l = height(parent->left) + 1;
                    } else {
                        parent->right = newNode;
                        parent->dp_r = height(parent->right) + 1;
                    }
                }
                
            } else if (r->dp_l > r->dp_r) {
                // RL
                Tree *newNode = balenceRL(root);
                retNode = newNode;
                
                // 修复树
                if (parent) {
                    if (parent->left == root) {
                        parent->left = newNode;
                        parent->dp_l = height(parent->left) + 1;
                    } else {
                        parent->right = newNode;
                        parent->dp_r = height(parent->right) + 1;
                    }
                }
            }
        }
    }
    
    return retNode;
}

Tree *maketree(int a[], int count) {
    
    Tree *root = NULL;
    
    for (int i = 0; i < count; i++) {
        
        Tree *node = new Tree;
        node->n = a[i];
        
        if (!root) {
            root = node;
        } else {
            root = insert(root, node, NULL);
        }
    }
    
    return root;
}


int main(int argc, const char * argv[]) {
    
//    int a [] = {1, -1, 3, 4, 5, 6, 7, 18, 9, 12, 100, 106, 107, 199};
    int a [] = {11, 11, 11, 11, 11, 11, 11};
    Tree *root = maketree(a, sizeof (a) / sizeof (a[0]));
    print_tree(root, 0);
    
    return 0;
    
}









