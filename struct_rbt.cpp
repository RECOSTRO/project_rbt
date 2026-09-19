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

// функция балансировки кчд при вставке (не очень удобно реализованно из-за большего чискла указателей, но структурировано(чтобы понять логику самой балансировки))
template <typename mytypel>
void balance_insert(rbt<mytypel> *(&head), rbt<mytypel> *( &New_node)){
    if (New_node->parent == nullptr) return;
    if (New_node->parent->parent == nullptr) return; // родитель корень
    if(New_node->parent->colour == 'b') return;

    rbt<mytypel> *father = New_node->parent;// отец
    rbt<mytypel> *uncle = nullptr;// ищем дядю
    rbt<mytypel> *grand = New_node->parent->parent;// деда

    if (grand->left == father) uncle = grand->right; // дядя справа
    else uncle = grand->left; // дядя слева

    if (uncle != nullptr){
        if (uncle->colour == 'r'){//  случай 1(дядя красный)

            father->colour = 'b';
            uncle->colour = 'b';
            uncle->parent->colour = 'r';
            balance_insert(head, uncle->parent);
            return;

        }
    }

    // случай 2 появился зиг-заг в правом и в левом поддереве
    if (grand->left == father && father->right == New_node){
        // поворотвокруг родителя в левом поддереве
        New_node->parent = grand;
        father->parent = New_node;
        father->right = New_node->left;
        if (father->right != nullptr) father->right->parent = father;
        New_node->left = father;
        grand->left = New_node;
        father = New_node;
        New_node = New_node->left;

    } else if (grand->right == father && father->left == New_node){
        // поворот вокруг родителя в правом поддереве
        New_node->parent = grand;
        father->parent = New_node;
        father->left = New_node->right;
        if (father->left != nullptr) father->left->parent = father;
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
        if (grand->left != nullptr) grand->left->parent = grand;
        father->right = grand;
    } else {
        grand->right = father->left;
        if (grand->right != nullptr) grand->right->parent = grand;
        father->left = grand;
    }

    if (father->parent != nullptr){
        if (father->parent->left == grand) father->parent->left = father;
        else father->parent->right = father;
    } else head = father;
    
    head->colour = 'b';
}

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
            cout << "Key is already use" << endl;
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

// ещё одна функция инициализации дерева по совету коментатора (перегрузка функции)
template <typename mytypel>
void  make_tree(Node<mytypel> *storage, rbt<mytypel> *( &head), int *key, int len){
    if (len <= 0) return;

    for (int i = 0; i < len; i++){
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

    if (temp == head){

        if (temp->left == nullptr && temp->right == nullptr) head == nullptr;

        else if (temp->left == nullptr){
            head = temp->right;
            head->parent = temp->parent;
        } else if (temp->right == nullptr){
            head = temp->left ;
            head->parent = temp->parent;
        } else {
            rbt<mytypel> *prut = search_min(head->right);
            prut->parent->left = nullptr;
            prut->parent = temp->parent;
            prut->left = temp->left;
            prut->right = temp->right;
            prut->right->parent = prut;
            prut->left->parent = prut;
            head = prut;
        }

    } else {
        if (temp->parent->left == temp){

            if (temp->left == nullptr && temp->right == nullptr) temp->parent->left = nullptr;
            else if (temp->left == nullptr){
                temp->parent->left = temp->right;
                temp->right->parent = temp->parent;
            } else if (temp->right == nullptr){
                temp->parent->left = temp->left;
                temp->left->parent = temp->parent;
            } else {
                rbt<mytypel> *prut = search_min(head->right);
                prut->parent->left = nullptr;
                prut->parent = temp->parent;
                prut->left = head->left;
                prut->right = head->right;
                prut->right->parent = prut;
                prut->left->parent = prut;
            }
        } else {
            if (temp->left == nullptr && temp->right == nullptr) temp->parent->right = nullptr;
            else if (temp->left == nullptr){
                temp->parent->right = temp->right;
                temp->right->parent = temp->parent;
            } else if (temp->right == nullptr){
                temp->parent->right = temp->left;
                temp->left->parent = temp->parent;
            } else {
                rbt<mytypel> *prut = search_min(head->right);
                prut->parent->left = nullptr;
                prut->parent = temp->parent;
                prut->left = head->left;
                prut->right = head->right;
                prut->right->parent = prut;
                prut->left->parent = prut;
            }
        }
    }

    delete temp;

    balance_del()
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