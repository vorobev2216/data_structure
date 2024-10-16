#include "Vector.h"
#include "Stack.h"
#include "List.h"
#include <iostream>

Stack::Stack(StackContainer container) {
    _containerType = container;
    if (_containerType == StackContainer::Vector) {
        _pimpl = new Vector();
    }
    else if (_containerType == StackContainer::List) {
        _pimpl = new List();
    }
}

Stack::Stack(const ValueType *valueArray, const size_t arraySize, StackContainer container) {
    _containerType = container;
    if (_containerType == StackContainer::Vector) {
        _pimpl = new Vector(valueArray, arraySize);
    }
    else if (_containerType == StackContainer::List) {
        _pimpl = new List(valueArray, arraySize);
    }
}

Stack::Stack(const Stack &copyStack) {
    _containerType = copyStack._containerType;
    if (_containerType == StackContainer::Vector) {
        _pimpl = new Vector(*dynamic_cast<Vector *>(copyStack._pimpl));
    }
    else if (_containerType == StackContainer::List) {
        _pimpl = new List(*dynamic_cast<List *>(copyStack._pimpl));
    }

}

Stack &Stack::operator=(const Stack &copyStack) {
    if (this == &copyStack) {
        return *this;
    }
    delete _pimpl;
    _containerType = copyStack._containerType;
    if (_containerType == StackContainer::Vector) {
        _pimpl = new Vector(*dynamic_cast<Vector *>(copyStack._pimpl));
    }
    else if (_containerType == StackContainer::List) {
        _pimpl = new List(*dynamic_cast<List *>(copyStack._pimpl));
    }
    return *this;
}

Stack::Stack(Stack &&moveStack) noexcept {
    _containerType = moveStack._containerType;
    _pimpl = moveStack._pimpl;
    moveStack._pimpl = nullptr;
}

Stack &Stack::operator=(Stack &&moveStack) noexcept {
    if (this == &moveStack) {
        return *this;
    }
    delete _pimpl;
    _pimpl = moveStack._pimpl;
    _containerType = moveStack._containerType;
    moveStack._pimpl = nullptr;
    return *this;
}

Stack::~Stack() {
    delete _pimpl;
}

void Stack::push(const ValueType &value) {
    _pimpl->push(value);
}

void Stack::pop() {
    _pimpl->pop();
}

const ValueType &Stack::top() const {
    return _pimpl->top();
}

bool Stack::isEmpty() const {
    return _pimpl->isEmpty();
}

size_t Stack::size() const {
    return _pimpl->size();
}

//std::cout << "stack: " << stack3.top() << " " << stack3.size() << std::endl;
//int main() {
//    Stack stack(StackContainer::List);
//    stack.push(1);
//    stack.push(2);
//    stack.push(3);
//
//    Stack stack2(stack);
//    stack2.push(4);
//    stack2.push(5);
//    stack2.push(6);
//    Stack stack3(stack2);
//    stack3.push(7);
//    stack3.push(8);
//    stack3.push(9);
//    Stack stack4(stack3);
//
//    std::cout << "stack: " << stack.top() << " " << stack.size() << std::endl;
//    std::cout << "stack: " << stack2.top() << " " << stack2.size() << std::endl;
//    std::cout << "stack: " << stack4.top() << " " << stack4.size() << std::endl;
//
//    return 0;

