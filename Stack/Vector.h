#pragma once
#include <iostream>
#include "StackImplementation.h"

using ValueType = double;

class Vector: public IStackImplementation {
public:
    Vector() = default;

    Vector(const ValueType* rawArray, const size_t size, float coef = 2.0f);

    Vector(const Vector& other);

    virtual void pop();

    virtual const ValueType& top() const;

    virtual void push(const ValueType& value);

    void reserve(size_t capacity);

    virtual bool isEmpty() const;

    virtual size_t size() const;

    ~Vector();
private:
    ValueType* _data = nullptr;
    size_t _size = 0;
    size_t _capacity = 0;
    float _multiplicativeCoef = 2.0f;
};
