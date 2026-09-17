#include <iostream>
#include <struct_rbt.hpp>
using namespace std;


// функция инициализации дерева
template <typename mytypel>
void make_tree(mytypel data, rbt<mytypel> *( &head), int key){
    if (head != nullptr) return;

    head = new rbt<mytypel>;

    head->key = key;
    head->data = data;
    head->right = nullptr;
    head->left = nullptr;
    head->parent = nullptr;
}
/////////////////////

template <typename mytypel>
void insert(rbt<mytypel> *( &head), int key, )

// ещё одна функция инициализации дерева по совету коментатора
template <typename mytypel>
void  make_tree(Node<mytypel> *storage, rbt<mytypel> *( &head), int *key, int len){
    if (head == nullptr){
        head = new rbt<mytypel>;
        head->key = key[0];
        head->data = storage[0].data;
        head->right = nullptr;
        head->left = nullptr;
        head->parent = nullptr;
    }

    for (int i = 1; i < len; i++){
        insert(storage[i].data ,head, key[i]);// добавим на следующем релитзе
    }
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