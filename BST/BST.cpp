#include <iostream>
#include "BST.h"
#include <vector>

BinarySearchTree::Node::Node(Key key, Value value, Node* parent, Node* left, Node* right) : parent(parent), left(left), right(right) {
    std::pair<Key, Value> p1 = std::make_pair(key, value);
    keyValuePair = p1;
}
BinarySearchTree::Node::Node(BinarySearchTree::Node& other) {
    keyValuePair.first = other.keyValuePair.first;
    keyValuePair.second = other.keyValuePair.second;
    parent = other.parent;
    if (other.left == nullptr) {
        left = nullptr;
    }
    else {
        left = new Node(*other.left);
    }
    if (other.right == nullptr) {
        right = nullptr;
    }
    else {
        right = new Node(*other.right);
    }
}
bool BinarySearchTree::Node::operator==(const Node &other) {
    if (keyValuePair == other.keyValuePair && parent == other.parent && left == other.left && right == other.right) {
        return true;
    }
    return false;
}
void BinarySearchTree::Node::insert(const Key &key, const Value &value) {
    if (key < keyValuePair.first) {
        if (left == nullptr) {
            left = new Node(key, value, this);
        }
        else {
            left->insert(key, value);
        }
    }
    else if (key > keyValuePair.first) {
        if (right == nullptr) {
            right = new Node(key, value, this);
        }
        else {
            right->insert(key, value);
        }
    }
    else if (value < keyValuePair.first) {
        if (left == nullptr) {
            left = new Node(key, value, this);
        }
        else {
            left->insert(key, value);
        }
    }
    else {
        if (right == nullptr) {
            right = new Node(key, value, this);
        }
        else {
            right->insert(key, value);
        }
    }
}
void BinarySearchTree::Node::erase(const Key &key)  {
    if (key < keyValuePair.first) {
        if (left != nullptr) {
            left->erase(key);
        }
    }
    else if (key > keyValuePair.first) {
        if (right != nullptr) {
            right->erase(key);
        }
    }
    else {
        if (left == nullptr && right == nullptr) {
            if (parent!= nullptr) {
                if (parent->left == this) {
                    parent->left = nullptr;
                }
                else {
                    parent->right = nullptr;
                }
            }
            delete this;
        }
        else if (left  == nullptr) {
            if (parent != nullptr) {
                if (parent->left == this) {
                    parent->left = right;
                }
                else {
                    parent->right = right;
                }
                right->parent = parent;
                delete this;
            }
        }
        else if (right == nullptr) {
            if (parent != nullptr) {
                if (parent->left == this) {
                    parent->left = left;
                } else {
                    parent->right = left;
                }
                left->parent = parent;
                delete this;
            }
        }
        else {
            Node* node = new Node(*right);
            while (node->left != nullptr) {
                node = node->left;
            }
            keyValuePair = node->keyValuePair;
            node->erase(node->keyValuePair.first);
        }
    }
}
BinarySearchTree::BinarySearchTree(const BinarySearchTree& other) {
    _size = other._size;
    if (other._root == nullptr) {
        _root = nullptr;
    }
    else {
        _root = new Node(*other._root);
    }
}
BinarySearchTree& BinarySearchTree::operator=(const BinarySearchTree& other) {
    if (this == &other) {
        return *this;
    }
    this->~BinarySearchTree(); //recursive delete
    _size = other._size;
    if (other._root == nullptr) {
        _root = nullptr;
    }
    else {
        _root = new Node(*other._root);
    }
    return *this;
}
BinarySearchTree::BinarySearchTree(BinarySearchTree&& other) noexcept {
    /*_size = other._size;
    if (other._root == nullptr) {
        _root = other._root;
    }
    else {
        _root = new Node(*other._root);
    }
    other._size = 0;
    if (other._root != nullptr) {
        other.~BinarySearchTree();
    }*/
    _root = other._root;
    other._root = nullptr;
    _size = other._size;
    other._size = 0;
}
BinarySearchTree& BinarySearchTree::operator=(BinarySearchTree&& other) noexcept {
    if (this != &other) {
        this->~BinarySearchTree();
        _size = other._size;
        _root = other._root;
        other._root = nullptr;
        //other.~BinarySearchTree();
        other._size = 0;
    }
    return *this;
}
BinarySearchTree::~BinarySearchTree() {
    /*if (_root != nullptr) {
        erase(_root->keyValuePair.first);
    }*/
    if (_root != nullptr) {
        std::vector<Node *> nodes;
        nodes.push_back(_root);
        while (!nodes.empty()) {
            Node *node = nodes.back();
            nodes.pop_back();
            if (node->left != nullptr) {
                nodes.push_back(node->left);
            }
            if (node->right != nullptr) {
                nodes.push_back(node->right);
            }
            delete node;
        }
    }
}
BinarySearchTree::Iterator::Iterator(Node *node) : _node(node) {

}
std::pair<Key, Value>& BinarySearchTree::Iterator::operator*() {
    return _node->keyValuePair;
}
const std::pair<Key, Value>& BinarySearchTree::Iterator::operator*() const {
    return _node->keyValuePair;
}
std::pair<Key, Value>* BinarySearchTree::Iterator::operator->() {
    return &_node->keyValuePair;
}
const std::pair<Key, Value>* BinarySearchTree::Iterator::operator->() const {
    return &_node->keyValuePair;
}
BinarySearchTree::Iterator BinarySearchTree::Iterator::operator++() {
    if (_node->right != nullptr) {
        _node = _node->right;
        while (_node->left != nullptr) {
            _node = _node->left;
        }
    }
    else {
        while (_node->parent != nullptr && _node == _node->parent->right) {
            _node = _node->parent;
        }
        _node = _node->parent;
    }
    return *this;
}
BinarySearchTree::Iterator BinarySearchTree::Iterator::operator++(int) {
    BinarySearchTree::Iterator p = *this;
    ++(*this);
    return p;
}
BinarySearchTree::Iterator BinarySearchTree::Iterator::operator--() {
    if (_node->left != nullptr) {
        _node = _node->left;
        while (_node->right != nullptr) {
            _node = _node->right;
        }
    }
    else {
        while (_node->parent != nullptr && _node->parent->left == _node) {
            _node = _node->parent;
        }
        _node = _node->parent;
    }
    return *this;
}
BinarySearchTree::Iterator BinarySearchTree::Iterator::operator--(int) {
    BinarySearchTree::Iterator p = *this;
    --(*this);
    return p;
}
bool BinarySearchTree::Iterator::operator==(const Iterator& other) const {
    return _node == other._node;
}
bool BinarySearchTree::Iterator::operator!=(const Iterator& other) const {
    return !(*this == other);
}
BinarySearchTree::ConstIterator::ConstIterator(const Node* node) {
    _node = node;
}
const std::pair<Key, Value>& BinarySearchTree::ConstIterator::operator*() const {
    return (*_node).keyValuePair;
}

const std::pair<Key, Value>* BinarySearchTree::ConstIterator::operator->() const {
    return &_node->keyValuePair;
}

BinarySearchTree::ConstIterator BinarySearchTree::ConstIterator::operator++() {
    if (_node->right != nullptr) {
        _node = _node->right;
        while (_node->left != nullptr) {
            _node = _node->left;
        }
    }
    else {
        while (_node->parent != nullptr && _node == _node->parent->right) {
            _node = _node->parent;
        }
        _node = _node->parent;
    }
    return *this;
}
BinarySearchTree::ConstIterator BinarySearchTree::ConstIterator::operator++(int) {
    BinarySearchTree::ConstIterator t(*this);
    ++(*this);
    return t;
}
BinarySearchTree::ConstIterator BinarySearchTree::ConstIterator::operator--() {
    if (_node->left != nullptr) {
        _node = _node->left;
        while (_node->right != nullptr) {
            _node = _node->right;
        }
    }
    else {
        while (_node->parent != nullptr && _node == _node->parent->left) {
            _node = _node->parent;
        }
        _node = _node->parent;
    }
    return *this;
}
BinarySearchTree::ConstIterator BinarySearchTree::ConstIterator::operator--(int) {
    BinarySearchTree::ConstIterator p = *this;
    --(*this);
    return p;
}
bool BinarySearchTree::ConstIterator::operator==(const ConstIterator& other) const {
    return _node == other._node;
}
bool BinarySearchTree::ConstIterator::operator!=(const ConstIterator& other) const {
    return !(*this == other);
}
void BinarySearchTree::insert(const Key& key, const Value& value) {
    _size++;
    if (_root == nullptr)  {
        _root = new Node(key, value);
    }
    else {
        _root->insert(key, value);
    }
}
void BinarySearchTree::erase(const Key& key) {
    Iterator i = this->find(key);
    Iterator r_i(_root);
    while (_root != nullptr && i->first == key) {
        _size--;
        if (i == r_i && (_root->left == nullptr || _root->right == nullptr)) {
            Node* d = new Node(*_root);
            if (_root->left != nullptr) {
                _root = _root->left;
                _root->parent = nullptr;
            }
            else if (_root->right != nullptr) {
                _root = _root->right;
                _root->parent = nullptr;
            }
            else {
                _root = nullptr;
            }
            r_i = Iterator(_root);
            delete d;
        }
        else {
            _root->erase(key);
        }
        i = this->find(key);
    }
}
BinarySearchTree::ConstIterator BinarySearchTree::find(const Key& key) const {
    Node* x = _root;
    while (x != nullptr) {
        if (key < x->keyValuePair.first) {
            x = x->left;
        }
        else if (key > x->keyValuePair.first) {
            x = x->right;
        }
        else {
            break;
            //return ConstIterator(x);
        }
    }
    if (x == nullptr) {
        return this->cend();
    }
    return ConstIterator(x);
}
BinarySearchTree::Iterator BinarySearchTree::find(const Key& key) {
    Node* x =_root;
    while (x != nullptr) {
        if (key < x->keyValuePair.first) {
            x = x->left;
        }
        else if (key > x->keyValuePair.first) {
            x = x->right;
        }
        else {
            break;
            //return Iterator(x);
        }
    }
    if (x == nullptr) {
        return this->end();
    }
    return Iterator(x);
    //return Iterator(nullptr);
}
std::pair<BinarySearchTree::Iterator, BinarySearchTree::Iterator> BinarySearchTree::equalRange(const Key& key) {
    Iterator it_start = find(key);
    if (it_start == end()) {
        return std::make_pair(it_start, it_start);
    }
    Iterator it_tmp = it_start;
    Iterator it_end = it_start;
    it_tmp--;
    Iterator begin_it = begin();
    while (it_tmp->first == key && it_tmp != begin_it) {
        it_start--;
        it_tmp--;
    }
    it_tmp = it_end;
    it_tmp++;
    Iterator end_it = end();
    while (it_tmp->first == key && it_tmp != end_it) {
        it_end++;
        it_tmp++;
    }
    it_end++;
    return std::make_pair(it_start, it_end);
}
std::pair<BinarySearchTree::ConstIterator, BinarySearchTree::ConstIterator> BinarySearchTree::equalRange(const Key& key) const {
    ConstIterator begin = find(key);
    if (begin == cend()) {
        std::pair<BinarySearchTree::ConstIterator, BinarySearchTree::ConstIterator> p1 = std::make_pair(begin, begin);
        return  p1;
    }
    ConstIterator end = begin;
    ConstIterator i = begin;
    i--;
    ConstIterator st = cbegin();
    while (i->first == key && i != st) {
        begin--;
        i--;
    }
    i = end;
    ConstIterator en = cend();
    i++;
    while (i->first == key && i != en) {
        i++;
        end++;
    }
    end++;
    std::pair<BinarySearchTree::ConstIterator, BinarySearchTree::ConstIterator> p1 = std::make_pair(begin, end);
    return  p1;
}
BinarySearchTree::ConstIterator BinarySearchTree::min(const Key& key) const {
    Node* x = _root;
    Node* y = nullptr;
    while (x != nullptr) {
        if (key < x->keyValuePair.first) {
            x = x->left;
        }
        else if (key > x->keyValuePair.first) {
            x = x->right;
        }
        else {
            break;
            //y = new Node(*x);
            //x = x->left;
        }
    }
    while (x->left != nullptr) {
        x = x->left;
    }
    return ConstIterator(x);
}
BinarySearchTree::ConstIterator BinarySearchTree::max(const Key& key) const {
    Node* x = _root;
    Node* y = nullptr;
    while (x != nullptr) {
        if (key < x->keyValuePair.first) {
            x = x->right;
        }
        else if (key > x->keyValuePair.first) {
            x = x->left;
        }
        else {
            break;
//            y = new Node(*x);
//            x = x->right;
        }
    }
    while (x->right != nullptr) {
        x =x->right;
    }
    return ConstIterator(x);
}
BinarySearchTree::Iterator BinarySearchTree::begin() {
    Node* node = _root;
    if (node == nullptr) {
        return Iterator(node);
    }
    while (node->left != nullptr) {
        node = node->left;
    }
    return Iterator(node);
}
BinarySearchTree::Iterator BinarySearchTree::end() {
    Node* node = _root;
    if (node == nullptr) {
        return Iterator(node);
    }
    while (node->right != nullptr) {
        node = node ->right;
    }
    return Iterator(node);
}
BinarySearchTree::ConstIterator BinarySearchTree::cbegin() const {
    Node* node = _root;
    if (node == nullptr) {
        return ConstIterator(node);
    }
    while (node->left != nullptr) {
        node = node->left;
    }
    return ConstIterator(node);
}
BinarySearchTree::ConstIterator BinarySearchTree::cend() const {
    Node* node = _root;
    if (node == nullptr) {
        return ConstIterator(node);
    }
    while (node->right != nullptr) {
        node = node ->right;
    }
    return ConstIterator(node);
}
size_t BinarySearchTree::size() const {
    return _size;
}

