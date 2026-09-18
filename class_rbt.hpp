using namespace std;

template <typename mytypel>
struct Node{// структура и класс почти ничем не отличаются в с++
public:// модификатор доступа(можно не писать, так как в структуре все аргументы в начале публичны)
    int key;
    char colour;
    mytypel data;
    struct Node *right;
    struct Node *left;
    struct Node *parent;
};

template <typename mytypel>
class RBT{
private:// модификатор доступа(можно не писать, так как в начале в классе все аргументы в начале приватные)
    Node *root;
}
