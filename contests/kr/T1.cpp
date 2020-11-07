#include <functional>
#include <vector>
#include <unordered_set>
template <typename K, typename V, typename H = std::hash<K>>
class AssociativeArray {
public:
    /* необходимо для стандартных алгоритмов */
    using value_type = std::pair<K const, V>;
    using reference = std::pair<K const, V>&;
    using const_reference = std::pair<K const, V> const &;
    using pointer = std::pair<K const, V>*;
    using iterator = std::; //укажите необходимый тип итератора
    using const_iterator = /* ??? */ //укажите необходимый тип итератора на неизменяемый элемент

    AssociativeArray(); //реализуйте самостоятельно

    iterator insert(K k,V v){

    } //метод вставки, см. примеры кода
    iterator find(/* ??? */); //метод поиска, см. примеры кода
    const_iterator find(/* ??? */) const; //метод поиска в неизменяемом объекте, см. примеры
    iterator erase(/* ??? */); //метод удаления, см. примеры кода

    //использование см. в примерах кода
    iterator begin();
    iterator end();
    const_iterator begin() const;
    const_iterator end() const;
private:
    struct h {

    };
    /* ??? */ //расположите необходимые внутренние данные
};