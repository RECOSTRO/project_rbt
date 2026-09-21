#include "struct_rbt.hpp"
#include <iostream>

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

// функция поиска максимуму(предшественик поиск)
template <typename mytypel>
rbt<mytypel> *search_max(rbt<mytypel> *head){
    if (head == nullptr) return nullptr;

    rbt<mytypel> *temp = head;

    while (temp->right != nullptr) temp = temp->right; // идём до самого правого узла в дереве

    return temp;
}
////////////////////

// функция поиска минимума(поиск последователя)
template <typename mytypel>
rbt<mytypel> *search_min(rbt<mytypel> *head){
    if (head == nullptr) return nullptr;

    rbt<mytypel> *temp = head;

    while (temp->left != nullptr) temp = temp->left; // идём до самого левого узла в дереве

    return temp;
}
////////////////////

// функция инициализации дерева
template <typename mytypel>
void make_tree(mytypel data, rbt<mytypel> *( &head), int key){
    if (head != nullptr) return;

    head = new rbt<mytypel>;

    head->key = key;
    head->data = data;
    head->colour = 'b';
    head->right = nullptr;
    head->left = nullptr;
    head->parent = nullptr;
}
/////////////////////

// Функция левого поворота вокруг узла
template <typename mytypel>
void left_rotate(rbt<mytypel> *(&head), rbt<mytypel> *node){
    if (node == nullptr || node->right == nullptr) return; 

    rbt<mytypel> *y = node->right; 

    node->right = y->left;
    if (y->left != nullptr) y->left->parent = node;
    
    y->parent = node->parent;
    if (node->parent == nullptr) head = y; 
    else if (node == node->parent->left) node->parent->left = y;
    else node->parent->right = y;

    y->left = node;
    node->parent = y;
}
/////////////////////

// Функция правого поворота вокруг узла
template <typename mytypel>
void right_rotate(rbt<mytypel> *(&head), rbt<mytypel> *node){
    if (node == nullptr || node->left == nullptr) return;

    rbt<mytypel> *x = node->left;

    node->left = x->right;
    if (x->right != nullptr) x->right->parent = node;

    x->parent = node->parent;
    if (node->parent == nullptr) head = x;
    else if (node == node->parent->right) node->parent->right = x;
    else node->parent->left = x;

    x->right = node;
    node->parent = x;
}
/////////////////////

// функция балансировки кчд при вставке
template <typename mytypel>
void balance_insert(rbt<mytypel> *(&head), rbt<mytypel> *New_node){
    if (New_node->parent == nullptr) return;
    if (New_node->parent->parent == nullptr) return; 
    if (New_node->parent->colour == 'b') return;

    rbt<mytypel> *father = New_node->parent;
    rbt<mytypel> *grand = father->parent;
    rbt<mytypel> *uncle = (grand->left == father) ? grand->right : grand->left;

    // Случай 1: Дядя красный
    if (uncle != nullptr && uncle->colour == 'r'){
        father->colour = 'b';
        uncle->colour = 'b';
        grand->colour = 'r';
        balance_insert(head, grand);
        return;
    }

    // Если отец - левый потомок
    if (grand->left == father) {
        if (father->right == New_node){ // Случай 2: Зиг-заг сслева
            New_node = father;
            left_rotate(head, New_node);
            father = New_node->parent;
            grand = father->parent;
        }
        // Случай 3: прямая сслева
        father->colour = 'b';
        grand->colour = 'r';
        right_rotate(head, grand);   
    } else {
        if (father->left == New_node){ // Случай 2 справа
            New_node = father;
            right_rotate(head, New_node);
            father = New_node->parent;
            grand = father->parent;
        }
        // Случай 3 прямая справа
        father->colour = 'b';
        grand->colour = 'r';
        left_rotate(head, grand);
    }
    head->colour = 'b';
}
/////////////////////

// функция вставки узла в кчд
template <typename mytypel>
void insert(mytypel data, rbt<mytypel> *( &head), int key){
    if (head == nullptr){
        make_tree(data, head, key);
        return;
    }

    rbt<mytypel> *temp = head;
    rbt<mytypel> *point = temp;

    while (temp != nullptr){// проход до нужного узла

        point = temp;

        if (temp->key == key){// ключ уже существует
            std::cout << "Key is already use" << std::endl;
            return;
        }
        else if (temp->key > key) temp = temp->left;
        else temp = temp->right;
    }

    rbt<mytypel> *poison = nullptr;

    if (point->key > key){ // вставка в левое поддерево

        make_tree(data, poison, key);

        poison->parent = point;
        poison->colour = 'r';
        point->left = poison;
    } else { // вставка в правое поддерево

        make_tree(data, poison, key);

        poison->parent = point;
        poison->colour = 'r';
        point->right = poison;
    }

    balance_insert(head, poison);// балансировка при вставке
}
/////////////////////

// функция балансировки кчд при удалении
template <typename mytypel>
void balance_del(rbt<mytypel> *(&head), rbt<mytypel> *father, rbt<mytypel> *child) {
    
    while (child != head && (child == nullptr || child->colour == 'b')){
        
        if (father->left == child){// удалили узел сслева
            rbt<mytypel> *brother = father->right;

            // Случай 1
            if (brother->colour == 'r'){
                brother->colour = 'b';
                father->colour = 'r';
                left_rotate(head, father);
                brother = father->right;
            }

            // Случай 2
            if ((brother->left == nullptr || brother->left->colour == 'b') && (brother->right == nullptr || brother->right->colour == 'b')){
                brother->colour = 'r';
                child = father;
                father = child->parent;
            } else {
                // Случай 3
                if (brother->right == nullptr || brother->right->colour == 'b'){
                    if (brother->left != nullptr) brother->left->colour = 'b';
                    brother->colour = 'r';
                    right_rotate(head, brother);
                    brother = father->right;
                }

                // Случай 4
                brother->colour = father->colour;
                father->colour = 'b';
                if (brother->right != nullptr) brother->right->colour = 'b';
                left_rotate(head, father);
                child = head;
            }
            
        } else { // удалили узел справа
            rbt<mytypel> *brother = father->left;

            // Случай 1
            if (brother->colour == 'r'){
                brother->colour = 'b';
                father->colour = 'r';
                right_rotate(head, father);
                brother = father->left;
            }

            // Случай 2
            if ((brother->right == nullptr || brother->right->colour == 'b') && (brother->left == nullptr || brother->left->colour == 'b')){
                brother->colour = 'r';
                child = father;
                father = child->parent;
            } else {
                // Случай 3
                if (brother->left == nullptr || brother->left->colour == 'b'){
                    if (brother->right != nullptr) brother->right->colour = 'b';
                    brother->colour = 'r';
                    left_rotate(head, brother);
                    brother = father->left;
                }

                // Случай 4
                brother->colour = father->colour;
                father->colour = 'b';
                if (brother->left != nullptr) brother->left->colour = 'b';
                right_rotate(head, father);
                child = head; 
            }
        }
    }
    if (child != nullptr) child->colour = 'b';
}
/////////////////////

// функция удаление узла из дерева
template <typename mytypel>
void delete_node(rbt<mytypel> *(&head), int key){
    if (head == nullptr) return;

    rbt<mytypel> *temp = head;

    while(temp != nullptr){
        if (temp->key == key) break;
        else if (temp->key > key) temp = temp->left;
        else temp = temp->right;
    }

    if (temp == nullptr) return;

    rbt<mytypel> *prut = nullptr;
    rbt<mytypel> *child = nullptr;

    if (temp->left!=nullptr && temp->right != nullptr){
        prut = search_min(temp->right);
        temp->key = prut->key;
        temp->data = prut->data;
        temp = prut;
    }
    
    if (temp->left != nullptr ) child = temp->left;
    if (temp->right != nullptr) child = temp->right;

    if (child != nullptr) child->parent = temp->parent;

    if (temp->parent == nullptr) head = child;
    else if (temp->parent->left == temp) temp->parent->left = child;
    else temp->parent->right = child;

    char d_colour = temp->colour;
    prut = temp->parent;
    delete temp;

    if(d_colour == 'b') balance_del(head, prut, child);
}
/////////////////////

// ещё одна функция инициализации дерева по совету коментатора (перегрузка функции)
template <typename mytypel>
void  make_tree(Node<mytypel> *storage, rbt<mytypel> *( &head), int *key, int len){
    if (len <= 0) return;

    for (int i = 0; i < len; i++){
        insert(storage[i].data ,head, key[i]);
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
