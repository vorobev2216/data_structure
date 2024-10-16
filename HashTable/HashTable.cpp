#include "HashTable.h"

HashTable::HashTable(size_t size) noexcept : _capacity (size), _filled(0) {
    table.resize(_capacity);
}

HashTable::~HashTable() = default;


void HashTable::insert(const KeyType &key, const ValueType &value) {
    if (this->getLoadFactor() > 0.75) {
        _capacity = _capacity * 2;
        std::vector < std::list < std::pair < KeyType, ValueType>>> table_1(_capacity);
        for (auto i= table.begin(); i != table.end(); i++) {
            for (auto j = i->begin(); j != i->end(); j++) {
                table_1[hash_function(j->first)].push_back(std::make_pair(j->first, j->second));
            }
        }
        table = table_1;
    }
    for (auto i= table[hash_function(key)].begin(); i != table[hash_function(key)].end(); i++) {
        if (i->first == key) {
            i->second = value;
            return;
        }
    }
    table[hash_function(key)].push_back(std::make_pair(key, value));
    _filled += 1;
}

bool HashTable::find(const KeyType &key, ValueType &value) const {
    for (auto i = table[hash_function(key)].begin(); i != table[hash_function(key)].end(); i++) {
        if (key == i->first) {
            value = i->second;
            return true;
        }
    }
    return false;
}

void HashTable::remove(const KeyType &key) {
    for (auto i = table[hash_function(key)].begin(); i != table[hash_function(key)].end(); i++) {
        if (i->first == key) {
            table[hash_function(key)].erase(i);
            _filled--;
            return;
        }
    }
}

ValueType &HashTable::operator[](const KeyType &key) {
    for (auto i = table[hash_function(key)].begin(); i != table[hash_function((key))].end(); i++) {
        if (i->first == key) {
            return i->second;
        }
    }
    insert(key, 0);
    return table[hash_function(key)].back().second;
}

double HashTable::getLoadFactor() {
    return static_cast<double>(_filled) / _capacity;
}

size_t HashTable::hash_function(const KeyType &key) const {
    size_t h = 0;
    for (int i = 0; i != key.size(); i++) {
        h += key[i];
    }
    return h % _capacity;
}