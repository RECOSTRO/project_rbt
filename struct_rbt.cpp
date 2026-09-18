#include <struct_rbt.hpp>
using namespace std;


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
template <typename mytypel>
void balance_insert(rbt<mytypel> *( &New_node)){
    if (New_node->parent->parent == nullptr) return; // родитель корень

    rbt<mytypel> *father = New_node->parent;// отец
    rbt<mytypel> *uncle = father->parent;// ищем дядю
    rbt<metepel> *grand = New_node->parent->parent;// деда

    if (grand->left = father) uncle = grand->right; // дядя справа
    else uncle = grand->left; // дядя слева

    if (uncle != nullptr){
        if (uncle->colour = 'r'){//  случай 1(дядя красный)

            father->colour = 'b';
            uncle->colour = 'b';
            uncle->parent->colour = 'r';
            balance_insert(uncle->parent);

        }
    }

    // случай 2 появился зиг-заг в правом и в левом поддереве
    if (grand->left == father && father->right == New_node){
        // поворотвокруг родителя в левом поддереве
        New_node->parent = grand;
        father->parent = New_node;
        New_node->left = father;
        grand->left = New_node;
        father = New_node;
        New_node = New_node->left;

    } else if (grand->right == father && father->left == New_node){
        // поворот вокруг родителя в правом поддереве
        New_node->parent = grand;
        father->parent = New_node;
        New_node->right = father;
        grand->right = New_node;
        father = New_node;
        New_node = New_node->right;

    }

    // случай 3(прямая из 3 чёрных узлов)
    grand->colour = 'r';
    father->colour = 'b';
    father->parent = grand->parent;
    grand->parent = father;
    if (father->left == New_node){
        grand->left = father->right;
        father->right = grand;
    } else {
        grand->right = father->left;
        father->left = grand;
    }

    if (father->parent != nullprt){
            if (father->parent->left == grand) father->parent->left = father;
            else father->parent->right = father;
        }

}

// функция вставки узла в кчд
template <typename mytypel>
void insert(rbt<mytypel> *( &head), int key, mytypel data){
    if (head == nullptr) return;

    rbt<mytypel> *temp = head;
    rbt<mytypel> *point = temp;

    while (temp != nullptr){// проход до нужного узла

        if (temp->key == key){// ключ уже существует
            cout << "Key is already use" << endl;
            return;
        }

        point = temp;

        else if (temp->key > key) temp = temp->left;
        else temp = temp->right
    }

    if (point->key > key){ // вставка в левое поддерево
        rbt<mytypel> *poison = nullptr;

        make_tree(data, poison, key);

        poison->parent = point;
        poison->colour = 'r';
        point->left = poison;
    } else { // вставка в правое поддерево
        rbt<mytypel> *poison = nullptr;

        make_tree(data, poison, key);

        poison->parent = point;
        poison->colour = 'r';
        point->right = poison;
    }

    balance_insert(poison);// балансировка при вставке
}
/////////////////////

// ещё одна функция инициализации дерева по совету коментатора (перегрузка функции)
template <typename mytypel>
void  make_tree(Node<mytypel> *storage, rbt<mytypel> *( &head), int *key, int len){
    if (head == nullptr){
        head = new rbt<mytypel>;
        head->key = key[0];
        head->data = storage[0].data;
        head->colour = 'b';
        head->right = nullptr;
        head->left = nullptr;
        head->parent = nullptr;
    }

    for (int i = 1; i < len; i++){
        insert(storage[i].data ,head, key[i]);
    }
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

    if (temp == head){// условие на один узел в дереве
        delete head;
        return;
    }

    rbt<mytypel> *point = temp->parent;

    if (point->left == temp) {

        if (temp->right == nullptr) point->left = temp->left;
        else if (temp->left == nullptr) point->left = temp->right;
        else point->left = search_min(temp->right);

        delete temp;

        balance_del(point->left); // реализованно будет чуть позже
    } else if (point->right) {

        if (temp->right == nullptr) point->right = temp->left;
        else if (temp->left == nullptr) point->right = temp->right;
        else point->right = search_min(temp->right);

        delete temp;

        balance_del(point->right); // реализованно будет чуть позже
    }
}

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