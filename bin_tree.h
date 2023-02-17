#ifndef _BIN_TREE_H_
#define _BIN_TREE_H_

#include <memory>
#include <iostream>
#include <functional>
#include <exception>
#include <cmath>
#include <queue>


// new insert
// спиральный обход


// get() - указатель на объект
// move() - смена владельца

template<class T>
class BinaryTree{
private:
    //struct Node;
    //using uNode = std::unique_ptr<Node>;

    struct Node{
        std::unique_ptr<Node> left = nullptr;
        std::unique_ptr<Node> right = nullptr;
        T data;

        Node(const T &_data)
            : data(_data)
        { }

        T getData() { return data; }
    };


    std::unique_ptr<Node> root = nullptr;


    
    void in_order(const std::unique_ptr<Node> & node);
    void pre_order(const std::unique_ptr<Node> & node);
    void post_order(const std::unique_ptr<Node> & node);

    void copy(const std::unique_ptr<Node> & node);
    void remove(const T &data, std::unique_ptr<Node>& node);

    std::unique_ptr<Node> & getMin(std::unique_ptr<Node>& node);

    void print(const std::string &prefix, const std::unique_ptr<Node> & node, int i = 0);
    bool search(const std::unique_ptr<Node> & node, const T &data)  const;
    void invert(std::unique_ptr<Node> & node);

    size_t height(const std::unique_ptr<Node> &node) const;

    bool isEquual(const std::unique_ptr<Node> &node1, const std::unique_ptr<Node> &node2);

    void printLevel(const std::unique_ptr<Node> &, size_t, size_t);
    T toSummTree(Node *);

// PUBLIC STARTS HERE !!!!!!!!!!!!!!!!!!!!!!!
public:    
    explicit BinaryTree() { }
    explicit BinaryTree(const BinaryTree &tree); // копирование

    void insert(const T &data); // вставка
    void remove(const T &data); // удаление

    void in_order(); // центрированный обход
    void pre_order(); // прямой
    void post_order(); // обратный
    void in_width(); // обход в ширину

    void print(); // печать
    bool search(const T &data) const; // поиск элемента в дереве

    T getMin(); // поиск минимума
    T getMax(); // поиск максимума
    
    void clear(); // очистка дерева

    


    // Тренировка

    size_t height() const; // высота
    bool isBalanced() const; // проверка на сбалансирванность

    bool operator ==(const BinaryTree &tr2); // проверка двух деревьев на равенство
    void invert(); // инвертировать дерево
    void spiralPrint(); // спиральный обход 


    void traversalBack(); // обратный обход
    void toSummTree(); // преобразование в дерево сумм
};


template<class T>
T BinaryTree<T>::toSummTree(Node *node){
    if(!node) {
        return 0;
    }

    std::cout << "ff" << std::endl;

    T left = toSummTree(node->left.get());
    T right = toSummTree(node->right.get());

    node->data = left + right + node->data;

    return node->data;

}

template<class T>
void BinaryTree<T>::toSummTree(){
    if(!root) return;

   // std::cout << "here" << std::endl;
    root->data = toSummTree(root.get());
}

template<class T>
void BinaryTree<T>::printLevel(const std::unique_ptr<Node> &node, size_t cur_level, size_t print_level){
    if(!node || cur_level < print_level) return;
    
    printLevel(node->left, cur_level - 1, print_level);

    //std::cout << height << std::endl;
    if(cur_level == print_level){
        std::cout << node->data << " ";
        return;
    }
    //std::cout << height << std::endl;

    printLevel(node->right, cur_level - 1, print_level);
}

template<class T>
void BinaryTree<T>::traversalBack(){
    if(!root) return;

    size_t h = height();

    std::cout << h <<  std::endl;


    size_t i = 0;

    while(i <= h){
        printLevel(root, h, i);
        i++;
    }

    std::cout << std::endl;

}


template<class T>
void BinaryTree<T>::spiralPrint(){
    if(!root) return;

    std::queue<Node*> q;
    q.push(root.get());

    bool left = true;

    while(q.size() != 0){
        Node *tmp = q.front();
        std::cout << tmp->data << " ";
        q.pop();
        
        if(left){
            left = false;
            if(tmp->left)
                q.push(tmp->left.get());
            if(tmp->right)
                q.push(tmp->right.get());
        }
        else{
            left = true;
            if(tmp->left)
                q.push(tmp->left.get());
            if(tmp->right)
                q.push(tmp->right.get());
        }
    }
}

template<class T>
void BinaryTree<T>::clear(){
    while(root)
        remove(root->data);
}


template<class T>
void BinaryTree<T>::in_width(){
    if(!root) return;
    std::queue<Node*> q;
    q.push(root.get());

    while(q.size() != 0){
        Node *tmp = q.front();
        std::cout << tmp->data << " ";
        q.pop();
        if(tmp->left)
            q.push(tmp->left.get());
        if(tmp->right)
            q.push(tmp->right.get());
    }

    std::cout << std::endl;
}

template<class T>
bool BinaryTree<T>::isEquual(const std::unique_ptr<Node> &node1, const std::unique_ptr<Node> &node2){
    if(!node1 && !node2) return true;

    return node1 && node2 && (node1->data == node2->data) &&
            isEquual(node1->left, node2->left) && isEquual(node1->right, node2->right);
}

template<class T>
bool BinaryTree<T>::operator ==(const BinaryTree<T> &tr2){
    return isEquual(this->root, tr2.root);
}

template<class T>
void BinaryTree<T>::invert(){
    invert(root);
}

template<class T>
void BinaryTree<T>::invert(std::unique_ptr<Node> & node){
    if(!node) return;
    node->left.swap(node->right);

    invert(node->left);
    invert(node->right);
}


template<class T>
bool BinaryTree<T>::isBalanced() const{

    if(!root || (!root->left && !root->right)) return true;

 //   std::cout << height(root->left) << " " << height(root->right) << std::endl;

    return (abs(height(root->left) - height(root->right)) <= 1) ? true : false;
}


template<class T>
size_t BinaryTree<T>::height(const std::unique_ptr<Node> &node) const{
    if(!node)
        return 0;
    return 1 + std::max(height(node->left), height(node->right));
}

template<class T>
size_t BinaryTree<T>::height() const{
    if(!root) return 0;

    return 1 + std::max(height(root->left), height(root->right));
}

template<class T>
T BinaryTree<T>::getMax(){
    if(!root)
        throw std::logic_error("Tree is empty");

    Node *p = root.get();
    while(p->right)
        p = p->right.get();

    return p->data;
}

template<class T>
bool BinaryTree<T>::search(const T &data) const{
    return search(root, data);
}

template<class T>
bool BinaryTree<T>::search(const std::unique_ptr<Node> & node, const T &data) const{
    if(!node)
        return false;
    if(data == node->data)
        return true;
    if(data < node->data)
        return search(node->left, data);
    else
        return search(node->right, data);
}

template<class T>
void BinaryTree<T>::copy(const std::unique_ptr<Node> & node){
    if(!node) return;
    
    this->insert(node->data);
    copy(node->left);
    copy(node->right);
}

template<class T>
BinaryTree<T>::BinaryTree(const BinaryTree<T> &tree){
    copy(tree.root);
}

template<class T>
T BinaryTree<T>::getMin(){
    if(!root) throw std::logic_error("Tree is empty");
    Node *tmp = root.get();
    while(tmp->left != nullptr)
        tmp = tmp->left.get();
    return tmp->data;
}

template <typename T>
std::unique_ptr<typename BinaryTree<T>::Node>& BinaryTree<T>::getMin(std::unique_ptr<Node>& node) {
    if(node == nullptr){
        throw "Min value not found";
    } else if(node->left == nullptr){
        return node;
    } else{
        return this->getMin(node->left);
    }
}


template<class T>
void BinaryTree<T>::remove(const T &data, std::unique_ptr<Node>& node){
    if(node == nullptr)
        std::cout << "val not found" << std::endl;
    else if(node->data == data){
        if(node->left == nullptr && node->right == nullptr){
            node = std::move(nullptr);
        }
        else if(node->right == nullptr && node->left != nullptr){
            node = std::move(node->left);
        }
        else if(node->right != nullptr && node->left == nullptr){
            node = std::move(node->right);
        }
        else if(node->left != nullptr && node->right != nullptr){
            std::unique_ptr<Node> &min_node = getMin(node->right);
            node->data = min_node->data;
            remove(min_node->data, min_node);
        }    
    }
    else if(data < node->data)
        remove(data, node->left);
    else
        remove(data, node->right);
}

template<class T>
void BinaryTree<T>::remove(const T &data){
    if(!root) {
        throw std::logic_error("Tree is empty");
    }

    remove(data, root);
}


template<class T>
void BinaryTree<T>::insert(const T &data){
    std::unique_ptr<Node> node = std::make_unique<Node>(data);
    if(!root)
        root = std::move(node); 
    else{
        Node *tmp = root.get();
        Node *prev = root.get();
        while(tmp){
            prev = tmp;
            if(data < tmp->data)
                tmp = tmp->left.get();
            else
                tmp = tmp->right.get();
        }
        if(data < prev->data)
            prev->left = std::move(node);
        else
            prev->right = std::move(node);
    }
}

template<class T>
void BinaryTree<T>::in_order(const std::unique_ptr<Node> & node){
    if(!node) return;
    
    in_order(node->left);

    std::cout << node->data << " ";
    
    in_order(node->right);
}

template<class T>
void BinaryTree<T>::in_order(){
    if(!root) return;
    in_order(root);  

    std::cout << std::endl;
}

template<class T>
void BinaryTree<T>::post_order(const std::unique_ptr<Node> & node){
    if(!node) return;

    post_order(node->left);
    post_order(node->right);
    std::cout << node->data << " ";
}

template<class T>
void BinaryTree<T>::post_order(){
    if(!root) return;
    post_order(root);

    std::cout << std::endl;
}


template<class T>
void BinaryTree<T>::pre_order(const std::unique_ptr<Node> & node){
    if(!node) return;

    std::cout << node->data << " ";
    pre_order(node->left);
    pre_order(node->right);
}

template<class T>
void BinaryTree<T>::pre_order(){
    if(!root) return;
    pre_order(root);

    std::cout << std::endl;
}


template<class T>
void BinaryTree<T>::print(){
    if(!root) return;
    print("", root);
}

template<class T>
void BinaryTree<T>::print(const std::string &prefix, const std::unique_ptr<Node> & node, int i)
{
    if(node){
         print("/", node->left, i + 1);     
        for(int j = 0; j < i; j++)
            std::cout << "   |";
        std::cout << prefix << node->data << std::endl;
       
        print("\\", node->right, i + 1);
    }
}


#endif
