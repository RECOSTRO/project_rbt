#include <iostream>
using namespace std;

// Шаблон для кчд дерева
template <typename mytypel>
struct rbt{
    int key;
    mytypel data;
    rbt *left;
    rbt *right;
    rbt *parent;
};
///////////////

// функция инициализации дерева
template <typename mytypel>
void make_tree(rbt<mytypel> *( &head), int key, mytypel data){
    if (head != nullptr){
        return;
    }
    head = new rbt<mytypel>;

    head->key = key;
    head->data = data;
    head->right = nullptr;
    head->left = nullptr;
    head->parent = nullptr;
}
/////////////////////


// функция очистки дерева
template <typename mytypel>
void freel(rbt<mytypel> *( &head)){
    if (head == nullptr) return;

    freel(head->right);
    freel(head->left);

    delete (head);

    head = nullptr;
}
/////////////////////

// функция поиска
template <typename mytypel>
rbt<mytypel> *search(rbt<mytypel> *head, int key){
    if (head == nullptr) return nullptr;

    rbt<mytypel> *temp = head;

    while (temp != nullptr){
        if (key < temp->key) temp = temp->left;
        else if (key > temp->key) temp = temp->right;
        else break;
    }


    return temp;
}
////////////////////

// функция поиска максимуму
template <typename mytypel>
rbt<mytypel> *search_max(rbt<mytypel> *head){
    if (head == nullptr) return nullptr;

    rbt<mytypel> *temp = head;

    while (temp->right != nullptr) temp = temp->right;

    return temp;
}
////////////////////

// функция поиска минимума
template <typename mytypel>
rbt<mytypel> *search_min(rbt<mytypel> *head){
    if (head == nullptr) return nullptr;

    rbt<mytypel> *temp = head;

    while (temp->left != nullptr) temp = temp->left;

    return temp;
}
////////////////////