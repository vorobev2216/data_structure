#include <iostream>
#include "List.h"

List::List(const ValueType *rawArray, const size_t size) {
    if (size != 0) {
        Node *p = new Node(rawArray[0]);
        head = p;
        _size = size;
    }
    Node *p = head;
    for (int i = 1; i < size; i++) {
        Node *current = new Node(rawArray[i]);
        p->next = current;
        p = p->next;
        if (i == size - 1) {
            last = p;
        }
    }
}
List::List(const List &obj) {
    Copy(obj);
}
List& List::operator=(const List& obj) {
    Copy(obj);
    return *this;
}
void List::push(const ValueType &value) {
    try {
        Node* elem = new Node(value);
        //elem->data = value;
        //elem->next = nullptr;

        if (head == nullptr) {
            head = last = elem;
        }
        else {
            last->next = elem;
            last = elem;
        }
        _size++;
    }
    catch (std::bad_alloc e) {
        std::cout << e.what() << std::endl;
    }
}
ValueType& List::operator[](int index) {
    Node* t = Move(index);
    return t->data;
}
void List::pop() {
    Del(_size-1);
}
void List::Del(size_t index) {
    if (_size == 0) {
        return;
    }
    if ((index < 0) || (index >= _size)) {
        return;
    }
    if (index == 0) {
        Node* t = head;
        head = head->next;
        delete t;
    }
    else {
        Node* t = Move(index-1);
        Node* t2 = t->next;
        t->next = t2->next;
        delete t2;
    }
    _size--;
}
void List::Del() {
    Del(0);
}
const ValueType& List::top() const {
    if (_size != 0) {
        Node* t = head;
        for (size_t i = 0; i < _size-1; i++) {
            t = t->next;
        }
        return t->data;
    }
}
bool List::isEmpty() const {
    return _size == 0;
}
size_t List::size() const {
    return _size;
}
Node* List::Move(size_t index) {
    if (_size > 0) {
        Node* t = head;
        for (size_t i = 0; i < index; i++) {
            t = t->next;
        }
        return t;
    }
    return nullptr;
}
void List::Copy(const List &obj) {
    Clear();

    Node* t = obj.head;
    for (size_t i = 0; i < obj._size; i++) {
        push(t->data);
        t = t->next;
    }
    _size = obj._size;
}
void List::Clear() {
    while (head != nullptr) {
        Del();
    }
}
List::~List() {
    Clear();
}
/*int main() {
    List p;
    p.push(223);
    p.push(33);
    List p1(p);
    //p1 = p;
    std::cout << "p1.top() = " << p1.top()<< std::endl;size_t arraySize = 5;
    ValueType* a = new ValueType[arraySize];
    //std::cout << "List a:" << std::endl;
    for (int i = 0; i < arraySize; i++) {
        a[i] = i;
    }
    std::cout << std::endl;
    std::cout << "List l:" << std::endl;
    List l(a, arraySize);
    for (int i = 0; i < l.size(); i++) {
        std::cout << l[i] << std::endl;
    }
    std::cout << std::endl;
    List l1(l);
    l1.push(111);
    //l1.pop();
    //std::cout << l[1] << std::endl;
    std::cout << "size l1  = " << l1.size() << std::endl;
    std::cout << "last el l = " << l.top() << std::endl;
    std::cout << "last el l1 = " << l1.top() << std::endl;
    List l2;
    List l3(l2);
    l3.push(1223);
    std::cout << "l3.top() = " << l3.top() << " l2.top() = " << l2.top() << std::endl;
    return 0;
}
/*List::List(const List &other) {
    head = other.head;
    _size = other._size;
    Node *node = other.head;
    Node* p = head;
    for (int i = 0; i < other._size; i++) {
        p->next = node->next;
        p = p->next;
        node = node->next;
    }
}
List::List(const ValueType *rawArray, const size_t size) {
    if (size != 0) {
        Node *p = new Node(rawArray[0]);
        head = p;
        _size = size;
    }
    Node* p = head;
    for (int i = 1; i < size; i++) {
        Node *current = new Node(rawArray[i]);
        p->next = current;
        p = p->next;
    }
}
void List::push(const ValueType &value) {
    if (head == nullptr) {
        head = new Node(value);
        _size++;
    }
    else {
        Node* node_new = head;
        while (node_new->next != nullptr) {
            node_new = node_new->next;
        }
        node_new->next = new Node(value);
        _size++;
    }
}
void List::pop() {
    if (head == nullptr) {
        return;
    }
    else if (_size == 1) {
        Node* p = head;
        head = p->next;
        delete p;
    }
    else {
        Node* p = head;

        size_t k = _size - 2;
        while (k) {
            p = p->next;
            k--;
        }
        //p->next = nullptr;
        delete p->next;
        p->next = nullptr;
        _size--;

    }
}
ValueType& List::operator[](int index) {
    int c = 0;
    Node* p = head;
    while (p != nullptr) {
        if (c == index) {
            return p->data;
        }
        c++;
        p = p->next;
    }
}
const ValueType &List::top() const {
    if (head != nullptr) {
        Node* p = head;
        while (p->next != nullptr) {
            p = p->next;
        }
        return p->data;
    }
}

bool List::isEmpty() const {
    if (head == nullptr) {
        return true;
    }
    return false;
}

size_t List::size() const {

    return _size;
}

List::~List() {
    while (_size) {
        pop();
    }
}*/
//List::List(const List &other) {
//    head = new Node(other.head->data);
//    last = new Node(other.last->data);
//    _size = other._size;
//    Node *node = other.head;
//    Node *p = head;
//    for (int i = 0; i < other._size - 1; i++) {
//        p->next = new Node(node->next->data);
//        p = p->next;
//        node = node->next;
//    }
//    p->next = last;
//}
//
//ValueType &List::operator[](int index) {
//    int c = 0;
//    Node *p = head;
//    while (p != nullptr) {
//        if (c == index) {
//            return p->data;
//        }
//        c++;
//        p = p->next;
//    }
//}
//
//List::List(const ValueType *rawArray, const size_t size) {
//    if (size != 0) {
//        Node *p = new Node(rawArray[0]);
//        head = p;
//        _size = size;
//    }
//    Node *p = head;
//    for (int i = 1; i < size; i++) {
//        Node *current = new Node(rawArray[i]);
//        p->next = current;
//        p = p->next;
//        if (i == size - 1) {
//            last = p;
//        }
//    }
//}
//
//void List::push(const ValueType &value) {
//    Node *p = new Node(value);
//    if (head == nullptr) {
//        head = p;
//        last = p;
//    }
//    last->next = p;
//    last = p;
//    _size++;
//}
//
//void List::pop() {
//    if (head == nullptr) {
//        return;
//    }
//    if (_size == 1) {
//        Node *p = head;
//        head = p->next;
//        delete p;
//        _size--;
//        return;
//    }
//    Node *p = head;
//    while (p->next != last) {
//        p = p->next;
//    }
//    p->next = nullptr;
//    delete last;
//    last = p;
//    _size--;
//}
//
//const ValueType &List::top() const {
//    if (_size != 0) {
//        return last->data;
//    }
//    /*if (_size == 1) {
//        return head->data;
//    }
//    else if (this->head != nullptr) {
//        Node* p = head;
//        while (p->next != last) {
//            p = p->next;
//        }
//        return p->data;
//    }*/
//}
//
//void List::pop_front() {
//    if (isEmpty()) {
//        return;
//    }
//    Node *p = head;
//    head = p->next;
//    _size--;
//    delete p;
//}
//
//bool List::isEmpty() const {
//    if (head == nullptr) {
//        return true;
//    }
//    return false;
//}
//
//size_t List::size() const {
//    return _size;
//}
//
//List::~List() {
//    //std::cout << "dec\struct" << std::endl;
//    while (_size) {
//        //std::cout << _size << std::endl;
//        pop_front();
//    }
//}
