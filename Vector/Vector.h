#pragma once

#include <iostream>

using Value = int;
//! \brief �����, ����������� �++ ��������� vector ��� ���� int
class Vector
{
public:
    //! ����������� ��� ����������
    Vector() = default;
    //! ����������� � �����������
    Vector(const Value* rawArray, const size_t size, float coef = 2.0f);
    //! ����������� �����������
    //! \param other - ���������� ������
    explicit Vector(const Vector& other);
    //! �������� ������������ ������������
    //! \param other - ���������� ������
    Vector& operator=(const Vector& other);
    //! ����������� �����������
    //! \param other - ������������ ������
    explicit Vector(Vector&& other) noexcept;
    //! �������� ������������ ������������
    //! \param other - ������������ ������
    Vector& operator=(Vector&& other) noexcept;
    //! ����������
    ~Vector();


    void pushBack(const Value& value);
    void pushFront(const Value& value);

    void insert(const Value& value, size_t pos);
    void insert(const Value* values, size_t size, size_t pos);
    void insert(const Vector& vector, size_t pos);

    void popBack();
    void popFront();

    /*!
        \brief Remove item(s) from vector

        \param pos: position of removing begin
        \param count: count of elements which must be removed

        if (pos + count) > size then [pos, size) should be removed
    */
    void erase(size_t pos, size_t count = 1);

    /*!
        \brief Remove item(s) from vector

        \param beginPos: position of removing begin
        \param endPos: position of removing end

        All items in interval [beginPos, endPos) should be removed:
            [1, 2, 3, 4] -> erase(1, 3) -> [1, 4]

        if endPos > size then [beginPos, size) should be removed
    */
    void eraseBetween(size_t beginPos, size_t endPos);


    size_t size() const;
    size_t capacity() const;
    double loadFactor() const;

    //! ������ � �������� �� �������
    Value& operator[](size_t idx);
    //! ������ � �������� �� �������
    const Value& operator[](size_t idx) const;

    //! ����� ������� ��������� ��������
    //! \return - ������ ��������
    long long find(const Value& value) const;

    /*!
        Changes current capacity and allocate new memory if capacity > _capacity.
        Else do nothing
    */
    void reserve(size_t capacity);

    /*!
        Decreases _capacity to _size.
    */
    void shrinkToFit();

    class Iterator
    {
        Value* _ptr;
    public:
        explicit Iterator(Value* ptr);

        Value& operator*();

        const Value& operator*() const;

        Value* operator->();

        const Value* operator->() const;

        Iterator operator++();

        Iterator operator++(int);

        bool operator==(const Iterator& other) const;

        bool operator!=(const Iterator& other) const;
    };

    Iterator begin();
    Iterator end();
private:
    Value* _data = nullptr;
    size_t _size = 0;
    size_t _capacity = 0;
    float _multiplicativeCoef = 2.0f;
};
