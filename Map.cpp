#include "Map.h"

Map::Map()
{
    //Not a circular doublylinked list so didn't use a dummy node;
    m_head  = nullptr; // set m_head to nullptr;
    m_tail  = nullptr; // set m_tail to nullptr;
    m_items = 0;       // set the size of the linked list to 0;
    // Create an empty map (i.e., one with no key/value pairs)
}

Map::Map(const Map &cpyFrom)
{
    // Edge case if the head is a nullptr it is an empty linked list so initalizing it would just be setting head and tail to nullptr and size to 0.
    if (cpyFrom.m_head == nullptr)
    {
        m_head  = nullptr;
        m_tail  = nullptr;
        m_items = 0;
    }
    //Otherwise its not empty so creating a new node and seting it to m_head and then setting the previous to the nullptr.
    m_head               = new Node;
    m_head -> m_prev     = nullptr;
    Node * cpyInto = m_head;
    //Created a temp variable and set the pointer to the first node of 
    for (Node * point = cpyFrom.m_head; point -> m_next != nullptr; point = point -> m_next)
    {
        Node * nextPoint       = new Node;
        cpyInto -> m_keyType   = point -> m_keyType;
        cpyInto -> m_valueType = point -> m_valueType;
        cpyInto -> m_next      = nextPoint;
        nextPoint -> m_prev    = cpyInto;
        cpyInto                = nextPoint;
    }
    cpyInto -> m_keyType   = cpyFrom.m_tail -> m_keyType;
    cpyInto -> m_valueType = cpyFrom.m_tail -> m_valueType;
    cpyInto -> m_next      = nullptr;
    m_tail                 = cpyInto;
    
}

Map & Map::operator = (const Map & cpyFrom)
{
    if (this != &cpyFrom)
    {
        Map m_temp(cpyFrom);
        swap(m_temp);
    }
    return *this;
}

Map::~Map()
{
    if (m_head == nullptr)
    {
        return;
    }
    Node * point = m_head;
    while (point != nullptr)
    {
        Node * new_Point = point -> m_next;
        delete point;
        point = new_Point;
    }
}

bool Map::empty() const
{
    bool emptyOrNot = false;
    if (m_items == 0)
    {
        emptyOrNot = true;
    }
    return emptyOrNot;
    // Return true if the map is empty, otherwise false.
}

int Map::size() const
{
    return m_items;
    // Return the number of key/value pairs in the map.
}

bool Map::insert(const std::string& key, const double& value)
{
    bool isTrue = true;
    if (contains(key))
    {
        return false;
    }
    else
    {
        
        Node * new_Guy         = new Node;
        new_Guy -> m_keyType   = key;
        new_Guy -> m_valueType = value;
        new_Guy -> m_next      = nullptr;
        new_Guy -> m_prev      = m_tail;
        if (empty())
        {
            m_head = new_Guy;
            m_tail = new_Guy;
            m_items++;
        }
        else if (!empty())
        {
            m_tail -> m_next = new_Guy;
            m_tail           = new_Guy;
            m_items++;
        }
        isTrue = true;
    }
    // If key is not equal to any key currently in the map, and if the
    // key/value pair can be added to the map, then do so and return true.
    // Otherwise, make no change to the map and return false (indicating
    // that either the key is already in the map, or the map has a fixed
    // capacity and is full).
    return isTrue;
        
}


bool Map::update(const std::string& key, const double& value)
{
    for (Node * point = m_head; point != nullptr; point = point -> m_next)
    {
        if (point -> m_keyType == key)
        {
            point -> m_valueType = value;
            return true;
        }
    }
    // If key is equal to a key currently in the map, then make that key no
    // longer map to the value that it currently maps to, but instead map to
    // the value of the second parameter; return true in this case.
    // Otherwise, make no change to the map and return false.
    return false;
}


bool Map::insertOrUpdate(const std::string& key, const double& value)
{
    if (update(key, value) == true)
    {
        return true;
    }
    return (insert(key, value));
    // If key is equal to a key currently in the map, then make that key no
    // longer map to the value that it currently maps to, but instead map to
    // the value of the second parameter; return true in this case.
    // If key is not equal to any key currently in the map and if the
    // key/value pair can be added to the map, then do so and return true.
    // Otherwise, make no change to the map and return false (indicating
    // that the key is not already in the map and the map has a fixed
    // capacity and is full).
}


bool Map::erase(const std::string& key)
{
    if (!contains(key))
    {
        return false;
    }
    Node * point;
    for (point = m_head; point != nullptr; point = point -> m_next)
    {
        if (point -> m_keyType == key)
        {
            if (point -> m_next != nullptr)
            {
                point -> m_next -> m_prev = point -> m_prev;
            }
            else
            {
                m_tail = point -> m_prev;
            }
            if (point -> m_prev != nullptr)
            {
                point -> m_prev -> m_next = point -> m_next;
            }
            else
            {
                m_head = point -> m_next;
            }
        }
    }
    m_items--;
    delete point;
    return true;
    // If key is equal to a key currently in the map, remove the key/value
    // pair with that key from the map and return true.  Otherwise, make
    // no change to the map and return false.
}

 
bool Map::contains(const std::string& key) const
{
    // Return true if key is equal to a key currently in the map, otherwise
    // false.
    for (Node * point = m_head; point != nullptr; point = point -> m_next)
    {
        if (point -> m_keyType == key)
        {
            return true;
        }
    }
    return  false;
}
 
 
bool Map::get(const std::string& key, double& value) const
{
    for (Node * point = m_head; point != nullptr; point = point -> m_next)
    {
        if (point -> m_keyType == key)
        {
            value = point -> m_valueType;
            return true;
        }
    }
    // If key is equal to a key currently in the map, set value to the
    // value in the map which that key maps to, and return true.  Otherwise,
    // make no change to the value parameter of this function and return
    // false.
    return false; 
}

bool Map::get(int i, std::string& key, double& value) const
{
    //Basically just did what I did in HW but changed the loops so they incremeneted the pointer.
    Node * firstPoint = m_head;
    if (i < 0  ||  i >= m_items)
    {
        return false;
    }
    while (firstPoint != nullptr)
    {
        int numGreaterThanI = 0;
        Node * secondPoint = m_head;
        while (secondPoint != nullptr)
        {
            if (firstPoint -> m_keyType > secondPoint -> m_keyType)
            {
                numGreaterThanI ++;
            }
            secondPoint = secondPoint -> m_next;
        }
        if (numGreaterThanI == i)
        {
            key = firstPoint -> m_keyType;
            value = firstPoint -> m_valueType;
            return true;
        }
        firstPoint = firstPoint -> m_next;
    }

    // If 0 <= i < size(), copy into the key and value parameters the
    // key and value of the key/value pair in the map whose key is strictly
    // greater than exactly i keys in the map and return true.  Otherwise,
    // leave the key and value parameters unchanged and return false.
    return false; 
   /*
    bool isTrue = false;
    int j = 0;
    Node * point = m_head;
    if (i == 0)
    {
        Node * p = m_head;
        key = p -> m_keyType;
        value = p -> m_valueType;
        return true;
    }
    if (i < 0  ||  i >= m_items)
    {
        return false;
    }
     
    while (j < i)
    {
        point = point -> m_next;
        j++;
    }
    if (point != nullptr)
    {
        key    = point -> m_keyType;
        value  = point -> m_valueType;
        isTrue = true;
    }
    return isTrue;
    */
    /*
    if (i < 0  ||  i >= m_items)
    {
        return false;
    }
     
    int count = -1;
    if (i == 0)
    {
        Node * p = m_head;
        key = p -> m_keyType;
        value = p -> m_valueType;
        return true; 
    }
    for (Node * point = m_head; point != nullptr; point = point -> m_next)
    {
        count ++;
        if (count == i)
        {
            key = point -> m_keyType;
            value = point -> m_valueType;
            return true;
        }
    }
    return false;
  */

}


void Map::swap(Map& other)
{
    int swapItems   = m_items;
    Node * swapHead = m_head;
    Node * swapTail = m_tail;
    
    m_head       = other.m_head;
    other.m_head = swapHead;
    
    m_tail       = other.m_tail;
    other.m_tail = swapTail;
    
    m_items       = other.m_items;
    other.m_items = swapItems;
    // Exchange the contents of this map with the other one.
}

bool merge(const Map& m1, const Map& m2, Map& result)
{
    int i = 0;
    int j = 0;
    int k = 0;
    bool hasSameOrDifferentValues = true;
    while (i != result.size())
    {
        KeyType resultKey; ValueType resultValue;
        result.get(0, resultKey, resultValue);
        result.erase(resultKey);
        i++;
    }
    while (j != m1.size())
    {
        KeyType m1FirstKey; ValueType m1FirstValue;
        m1.get(j, m1FirstKey, m1FirstValue);
        if (!m2.contains(m1FirstKey))
        {
            result.insertOrUpdate(m1FirstKey, m1FirstValue);
        }
        else if (m2.contains(m1FirstKey))
        {
            ValueType checkForSame;
            m2.get(m1FirstKey, checkForSame);
            if (m1FirstValue == checkForSame)
            {
                result.insertOrUpdate(m1FirstKey, m1FirstValue);
            }
            else
            {
                hasSameOrDifferentValues = false;
            }
        }
        j++;
    }
    while (k != m2.size())
    {
        KeyType m2FirstKey; ValueType m2FirstValue;
        m2.get(k, m2FirstKey, m2FirstValue);
        if (!m1.contains(m2FirstKey))
        {
            result.insertOrUpdate(m2FirstKey, m2FirstValue);
        }
        k++;
    }
    return hasSameOrDifferentValues;
}

void reassign(const Map& m, Map& result)
{
    int i = 0;
    int j = 0;
    KeyType mKey; ValueType mValue;
    m.get(0, mKey, mValue);
    
    while (i != result.size())
    {
        KeyType resultKey; ValueType resultValue;
        result.get(0, resultKey, resultValue);
        result.erase(resultKey);
        i++;
    }
    while (j != m.size())
    {
        ValueType mValue1; KeyType mKey1;
        m.get(i, mKey1, mValue1);
        if (i+1 != m.size())
        {
            KeyType mKey2; ValueType mValue2;
            m.get(i+1, mKey2, mValue2);
            result.insertOrUpdate(mKey1, mValue2);
        }
        else if (i+1 == m.size())
        {
            result.insertOrUpdate(mKey1, mValue);
        }
    }
}
