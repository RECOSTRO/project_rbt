#include <iostream>
#include "struct_rbt.hpp"


int main(){
    rbt<int> *point = nullptr;
    make_tree(10, point, 120);
    insert(99, point, 99);
    insert(129, point, 119);
    insert(198, point, 67);
    insert(98, point, 9);
    insert(199, point, 19);
    insert(80, point, 8);
    insert(80, point, 8);
    insert(769, point, 190);
    delete_node(point, 9);
    std::cout << search_min(point)->data << std::endl;
    std::cout << search_max(point)->data << std::endl;
    freel(point);
}