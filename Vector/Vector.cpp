#include "Vector.h"
#include <iostream>
#include <cstdlib>

Vector::Vector(const Value* rawArray, const size_t size, float coef) {
	_multiplicativeCoef = coef;
	_capacity = size * coef;
	_size = size;
	_data = new Value[_capacity];
	std::copy(rawArray, rawArray + size, _data);
}
Vector::Vector(const Vector& other) {
	_multiplicativeCoef = other._multiplicativeCoef;
	_capacity = other._capacity;
	_size = other._size;
	_data = new Value[_capacity];
	std::copy(other._data, other._data + other._size, _data);
}
Vector& Vector::operator=(const Vector& other) {
	_size = other._size;
	_capacity = other._capacity;
	_multiplicativeCoef = other._multiplicativeCoef;
	delete[] _data;
	_data = new Value[_capacity];
	std::copy(other._data, other._data + other._size, _data);

	return *this;
}
Vector& Vector::operator=(Vector&& other) noexcept {
	if (this != &other) {
		delete[] _data;
		_data = other._data;
		_size = other._size;
		_multiplicativeCoef = other._multiplicativeCoef;
		_capacity = other._capacity;
		other._size = 0;
		other._capacity = 0;
		other._multiplicativeCoef = 2.0f;
		other._data = nullptr;
	}
	return *this;
}
Vector::Vector(Vector&& other) noexcept {
	_size = other._size;
	_capacity = other._capacity;
	_data = other._data;
	_multiplicativeCoef = other._multiplicativeCoef;
	other._multiplicativeCoef = 2.0f;
	other._size = 0;
	other._capacity = 0;
	other._data = nullptr;
}
Vector::~Vector() {
	std::cout << "Destruct!!!" << std::endl;
	delete[] _data;
}
void Vector::pushBack(const Value& value) {
	if (_size >= _capacity) {
		reserve(std::max(_capacity * (size_t)_multiplicativeCoef, (size_t)_multiplicativeCoef));
	}
	std::cout << "cap = " << _capacity << " size = " << _size << std::endl;
	_data[_size] = value;
	_size++;
}
void Vector::pushFront(const Value& value) {
	if (_size >= _capacity) {
		reserve(std::max(static_cast<int>(_capacity * _multiplicativeCoef), static_cast<int>(_multiplicativeCoef)));
	}
	std::copy(_data, _data + _size, _data + 1);
	_data[0] = value;
	_size++;
}
void Vector::insert(const Value& value, size_t pos) {
	if (_size >= _capacity) {
		reserve(std::max(static_cast<int>(_capacity * _multiplicativeCoef), static_cast<int>(_multiplicativeCoef)));
	}
	std::copy(_data + pos, _data + _size, _data + 1 + pos);
	_data[pos] = value;
	_size++;
}
void Vector::insert(const Value* values, size_t size, size_t pos) {
	for (size_t i = 0; i < size; i++) {
		this->insert(values[i], pos + i);
	}
}
void Vector::insert(const Vector& vector, size_t pos) {
	this->insert(vector._data, vector._size, pos);
}
void Vector::popBack() {
	if (_size != 0) {
		_size--;

	}
}
void Vector::popFront() {
	if (_size != 0) {
		std::copy(_data + 1, _data + _size, _data);
		_size--;
	}
}
void Vector::erase(size_t pos, size_t count) {
	if (_size != 0) {
		std::copy(_data + pos + count + 1, _data + _size, _data + pos);
		_size -= count;
	}
}
void Vector::eraseBetween(size_t beginPos, size_t endPos) {
	if (_size != 0) {
		std::copy(_data + endPos + 1, _data + _size, _data + beginPos);
	}
}
size_t Vector::size() const {
	return _size;
}
size_t Vector::capacity() const {
	return _capacity;
}
double Vector::loadFactor() const {
	return static_cast<double>(_size / _capacity);
}
Value& Vector::operator[](size_t idx) {
	return _data[idx];
}
const Value& Vector::operator[](size_t idx) const {
	return _data[idx];
}
long long Vector::find(const Value& value) const {
	for (size_t i = 0; i < _size; i++) {
		if (_data[i] == value) {
			return i;
		}
	}
}
void Vector::reserve(size_t capacity) {
	if (capacity >= _capacity) {
		Value* data = new Value[capacity];
		std::copy(_data, _data + _size, data);
		delete[] _data;
		_data = data;
		_capacity = capacity;
	}
	else {
		std::cout << "capacity < _capacity" << std::endl;
	}
}
void Vector::shrinkToFit() {
	if (_size < _capacity) {
		Value* data = new Value[_size];
		std::copy(_data, _data + _size, data);
		delete[] _data;
		_data = data;
	}
	else {
		std::cout << "_size >= _capacity" << std::endl;
	}
}
Vector::Iterator::Iterator(Value* ptr) : _ptr(ptr) {

}
Value& Vector::Iterator::operator*() {
	return *(_ptr);
}
const Value& Vector::Iterator::operator*() const {
	return *(_ptr);
}
Value* Vector::Iterator::operator->() {
	return _ptr;
}
const Value* Vector::Iterator::operator->() const {
	return _ptr;
}
Vector::Iterator Vector::Iterator::operator++() {
	++_ptr;
	return *this;
}
Vector::Iterator Vector::Iterator::operator++(int) {
	*(_ptr++);
	return *this;
}
bool Vector::Iterator::operator==(const Iterator& other) const {
	return (_ptr == other._ptr);
}
bool Vector::Iterator::operator!=(const Iterator& other) const {
	return (_ptr != other._ptr);
}
Vector::Iterator Vector::begin() {
	return Iterator(_data);
}
Vector::Iterator Vector::end() {
	return Iterator(_data + _size);
}
