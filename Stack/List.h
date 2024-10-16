#pragma once
#include <iostream>
#include "StackImplementation.h"
#include <list>

using ValueType = double;

class Node {
public:
    ValueType data;
    Node* next;

    Node(ValueType _data, Node* _next = nullptr) : data(_data), next(_next) {}
};

class List: public IStackImplementation{
public:
//    class Node {
//    public:
//        ValueType data;
//        Node* next;
//
//        Node(ValueType _data, Node* _next = nullptr) : data(_data), next(_next) {
//
//        }
//    };

    List() = default;

    List(const List& obj);

    List& operator=(const List& obj);

    ValueType& operator[](int index);

    List(const ValueType* rawArray, const size_t size);

    virtual void push(const ValueType& value);

    virtual void pop();

    void Del(size_t index);

    void Del();

    virtual const ValueType& top() const;

    virtual bool isEmpty() const;

    virtual size_t size() const;

    void Clear();

    ~List();
private:
    size_t _size = 0;
    Node* head = nullptr;
    Node* last = nullptr;

    Node* Move(size_t index);

    void Copy(const List& obj);
};