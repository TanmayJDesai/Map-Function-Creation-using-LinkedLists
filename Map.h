#ifndef MAP_INCLUDED
#define MAP_INCLUDED
#include <iostream>
#include <string>
using namespace std;

using KeyType = std::string;
using ValueType = double;

//Map Class Declarations:

class Map
{
    public:
        Map();
        Map(const Map &cpyFrom);
        Map &operator = (const Map & cpyFrom);
        ~Map();
        bool empty() const;
        int size() const;
        bool insert(const KeyType& key, const ValueType& value);
        bool update(const KeyType& key, const ValueType& value);
        bool insertOrUpdate(const KeyType& key, const ValueType& value);
        bool erase(const KeyType& key);
        bool contains(const KeyType& key) const;
        bool get(const KeyType& key, ValueType& value) const;
        bool get(int i, KeyType& key, ValueType& value) const;
        void swap(Map& other);
    private:
    
    //Created doubly-linked list as the private member of the map function:
    //Class Invariants:
    //If empty both m_next and m_prev have to be nulllptr;
    //If the pointers of m_next and m_prev are nullptrs the code must not follow them
        // --> that is undefined behavior.
    //Do not need m_tail but need a m_head and a dummy node;
    
        struct Node
        {
            KeyType m_keyType;
            ValueType m_valueType;
            Node* m_next;
            Node* m_prev;
        };
    
    Node * m_head;
    Node * m_tail; 
    int m_items;
    
};

//Map Algorithm Declarations:

bool merge(const Map& m1, const Map& m2, Map& result);
void reassign(const Map& m, Map& result);

#endif /* MAP_INCLUDED */
