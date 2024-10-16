#include "Vector.h"
#include <iostream>
#include <cstdlib>

Vector::Vector(const ValueType* rawArray, const size_t size_new, float coef) {
    _multiplicativeCoef = coef;
    _capacity = size_new * coef;
    _size = size_new;
    _data = new ValueType[_capacity];
    std::copy(rawArray, rawArray +size_new, _data);
}
Vector::Vector(const Vector& other) {
    _multiplicativeCoef = other._multiplicativeCoef;
    _capacity = other._size;
    _size = other._size;
    _data = new ValueType[_capacity];
    std::copy(other._data, other._data + other._size, _data);
}
void Vector::pop() {
    if (_size > 0) {
        _size--;
    }
    else {
        throw std::out_of_range("(((");
    }
}
const ValueType& Vector::top() const {
    return _data[_size-1];
}
void Vector::push(const ValueType& value) {
    if (_size >= _capacity) {
        reserve(std::max(_capacity*(size_t)_multiplicativeCoef, (size_t) _multiplicativeCoef));
    }
    _data[_size] = value;
    _size++;
}
void Vector::reserve(size_t capacity) {
    if (capacity > _capacity) {
        ValueType* data = new ValueType[capacity];
        std::copy(_data, _data+_size, data);
        delete _data;
        _data = data;
        _capacity = capacity;
    }
}
bool Vector::isEmpty() const {
    if (_size == 0) {
        return true;
    }
    return false;
}
size_t Vector::size() const {
    return _size;
}
Vector::~Vector() {
    _capacity = 0;
    _size = 0;
    delete[] _data;
}