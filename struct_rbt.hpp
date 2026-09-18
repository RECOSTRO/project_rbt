#include <iostream>
using namespace std;

// Шаблон для кчд дерева
template <typename mytypel>
struct rbt{
    int key;
    mytypel data;
    char colour; // 'r' - красный, 'b' - чёрный
    rbt *left;
    rbt *right;
    rbt *parent;
};
///////////////

// шаблон для массива data
template <typename mytypel>
struct Node{
    mytypel data;
};
///////////////

template <typename mytypel>
void make_tree(rbt<mytypel> *( &head), int key, mytypel data);

template <typename mytypel>
void insert(rbt<mytypel> *( &head), int key, mytypel data);

template <typename mytypel>
void  make_tree(Node<mytypel> *storage, rbt<mytypel> *( &head), int *key, int len);

template <typename mytypel>
void freel(rbt<mytypel> *( &head));

template <typename mytypel>
rbt<mytypel> *search(rbt<mytypel> *head, int key);

template <typename mytypel>
rbt<mytypel> *search_max(rbt<mytypel> *head);

template <typename mytypel>
rbt<mytypel> *search_min(rbt<mytypel> *head);