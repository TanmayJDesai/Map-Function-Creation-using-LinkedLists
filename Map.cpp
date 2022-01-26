#include "Map.h"

//Normal Constructor
Map::Map()
{
    //Not a circular doublylinked list so didn't use a dummy node;
    m_head  = nullptr; // set m_head to nullptr;
    m_tail  = nullptr; // set m_tail to nullptr;
    m_items = 0;       // set the size of the linked list to 0;
    // Create an empty map (i.e., one with no key/value pairs)
}
//Copy Constructor
Map::Map(const Map &cpyFrom)
: m_items(cpyFrom.m_items)
//set the items equal to the items in the linked list that you are copying from.
{
    //If the size is 0 which means the linked list is empty
    //Then enter this statement
    if (cpyFrom.size() == 0)
    {
        //Because we have an empty list we just do the same thing we
        //do in the normal constructor. Except, we don't set size
        //because that was already done.
        m_head = nullptr;
        //set the head to a nullptr.
        m_tail = nullptr;
        //set the tail to a nullptr.
    }
    //If the size is not 0 and thus the linked list is not empty:
    else
    {
        //create a new node and set the m_head to point to it
        m_head = new Node;
        //Then the m_head's previous is a nullptr because not a circular doubly linked list.
        m_head -> m_prev = nullptr;
        //Create two pointers: Set one equal to the head pointer and the other equal to the linked list
        //being passed in the parameter that we are copying from.
        Node * alpha = m_head;
        Node * point = cpyFrom.m_head;
        //Enter the while loop until the point's next is equal to the nullptr because
        //that is when the linked list is empty.
        //Go until the next isn't a nullptr so we can add the last node manually after the loop.
        //We add this manually because we want to set the tail equal to that last node and we would have tail point to different nodes if we put it in the while loop.
        while (point -> m_next != nullptr)
        {
            //create a pointer and set it to a new node.
            Node * pointerNew = new Node;
            //set the key and values from the old to the new node.
            alpha -> m_keyType = point -> m_keyType;
            alpha -> m_valueType = point -> m_valueType;
            //Set the alpha to the next node so the pointer carries over.
            alpha -> m_next = pointerNew;
            //set the pointer that points to the current node set its prev to alpha so one points
            //to the previous node and the other points to the current node.
            pointerNew -> m_prev = alpha;
            //Set the alpha to the pointerNew so it then points to the new
            alpha = pointerNew;
            //Set the original pointer that pointed to the linked list passed in by the parameter
            //to its next so we know the next thing it opints to...we save that.
            point = point -> m_next;
        }
        //Once it exits you know the next of that would be the nullptr so we want to set the last nodes
        //key and value pairs and then set the next of the alpha to a nullptr so that we know the tail
        //would complete the doubly linked list.
        alpha -> m_keyType = cpyFrom.m_tail -> m_keyType;
        alpha -> m_valueType = cpyFrom.m_tail ->m_valueType;
        
        alpha -> m_next = nullptr;
        m_tail = alpha;
    }
}

Map & Map::operator = (const Map & cpyFrom)
{
    //Just did what Prof. Smallberg implemented in his HW1 solutions but for linked list.
    //created a temp map and copied into it the parameter and then swapped it.
    if (this != &cpyFrom)
    {
        Map m_temp(cpyFrom);
        swap(m_temp);
    }
    
    return *this;
}

Map::~Map()
{
    //Destructor
    if (m_head == nullptr)
    {
        //If the head is a nullptr the linked list is empty so return.
        return;
    }
    //created a pointed to the m_head of the linked list.
    Node * point = m_head;
    //while the pointer isn't a nullptr create a new pointer and set that equal to the m_head's next or old pointer's next. Delete the old point thus making sure no memory leaks occur and set the old point = the next pointer.
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
    //If m_items is 0 then you know its empty so return true saying its empty
    if (m_items == 0)
    {
        emptyOrNot = true;
    }
    //if mitems not 0 it has a value so return false;
    return emptyOrNot;
    // Return true if the map is empty, otherwise false.
}

int Map::size() const
{
    return m_items;
    // Return the number of key/value pairs in the map.
}

bool Map::insert(const KeyType& key, const ValueType& value)
{
    bool isTrue = true;
    //Create a bool isTrue and store that as true;
    //Check to see if the key already exists in the map
    if (contains(key))
    {
        return false;
    }
    //If it does return false otherwise add the node (key and value) to the map.
    else
    {
        //Create a pointer newguy and set that to a new node.
        Node * new_Guy         = new Node;
        //set the key value pairs.
        new_Guy -> m_keyType   = key;
        new_Guy -> m_valueType = value;
        
        //set the next to a nullptr Because we are adding to the end so last node would contain nullptr.
        new_Guy -> m_next      = nullptr;
        //set the previous to the tail
        new_Guy -> m_prev      = m_tail;
        if (empty())
        {
            //if its empty set the head and tail both to newGuy cause newGuy would be the last one.
            m_head = new_Guy;
            m_tail = new_Guy;
            //increment items in map
            m_items++;
        }
        else if (!empty())
        {
            //otherwise set the tail's next to new guy then set tail to newguy so you are pointing to
            m_tail -> m_next = new_Guy;
            m_tail           = new_Guy;
            //increment items in map
            m_items++;

        }
        //set bool to true and return it.
        isTrue = true;
    }
    
    // If key is not equal to any key currently in the map, and if the
    // key/value pair can be added to the map, then do so and return true.
    // Otherwise, make no change to the map and return false (indicating
    // that either the key is already in the map, or the map has a fixed
    // capacity and is full).
    return isTrue;
        
}


bool Map::update(const KeyType& key, const ValueType& value)
{
    //check to see if the key already exists in the map.
    for (Node * point = m_head; point != nullptr; point = point -> m_next)
    {
        //if it exists set the value for that key equal to
        //the key provided in the parameter.
        if (point -> m_keyType == key)
        {
            point -> m_valueType = value;
            //return true if you could update otherwise false
            return true;
        }
    }
    // If key is equal to a key currently in the map, then make that key no
    // longer map to the value that it currently maps to, but instead map to
    // the value of the second parameter; return true in this case.
    // Otherwise, make no change to the map and return false.
    return false;
}


bool Map::insertOrUpdate(const KeyType& key, const ValueType& value)
{
    if (update(key, value) == true)
    {
        //Used the insert and update functions already created.
        //if you could update it do that and return true otherwise try to insert
        //and return whatever the result of that is.
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


bool Map::erase(const KeyType& key)
{
    //If the map doesn't contain key return false because
    //you can't delete something that isn't there.
    if (!contains(key))
    {
        return false;
    }
    //create a pointer and bool isTrue.
    Node * point;
    bool isTrue = true;
    //there are 3 main conditions we want to check
    //1. when heads keytype is the key and its the only node in the list.
    //2. when the tails key is the key in the parameter
    //3. when the head's key is the key in the parameter and its not the only node.
    //don't need to check for tail and only 1 because that would be covered in 1st case.
    
    //If it is head and only 1 element
    //delete the m_head
    //and set tail and head to nullptr
    //decrement or we could set to 0 manually but following same convention for all cases.
    if (m_head -> m_keyType == key && size() == 1)
    {
        delete m_head;
        m_head = nullptr;
        m_tail  = nullptr;
        m_items--;
        return isTrue;
    }
    //if tail
    //use the pointer we created beforehand and set that to the tail .
    //set the tails, previous, next so the tail itself to the pointers next.
    //delete the pointer and then decrement
    if (m_tail -> m_keyType == key)
    {
        point = m_tail;
        m_tail -> m_prev -> m_next = point -> m_next;
        m_tail = point -> m_prev;
        delete point;
        m_items --;
        return isTrue;
    }
    //if head and not 1
    //set the point that we had established to m_head
    //set the m_head to the pointer's previous
    //delete the pointer and decrement items.
    if (m_head -> m_keyType == key)
    {
        point = m_head;
        m_head -> m_next -> m_prev = point -> m_prev;
        m_head = point -> m_next;
        delete point;
        m_items--;
        return isTrue;
    }
    
    Node * newPoint;
    //Created a new pointer and looped through the linked list until I found the
    //point where the pointer's next isn't a nullptr and its next's key is the key in the parameter.
    for ( newPoint = m_head; newPoint != nullptr ; newPoint = newPoint -> m_next)
    {
        if (newPoint -> m_next != nullptr && newPoint -> m_next ->m_keyType == key)
        {
            break;
        }
    }
    //because you break the loop when you either meet the req or its a nullptr check for the nullptr.
    //if its a nullptr enter the statement
    //set the pointer = the newpointers next.
    //Then set that same newpointers next equal to the points next.
    //Set the actual point to its next (basically increment the pointer.
    //delete the pointer and decrement the items
    if (newPoint != nullptr)
    {
        point = newPoint -> m_next;
        newPoint -> m_next = point -> m_next;
        point -> m_next -> m_prev = point -> m_prev;
        delete point;
        m_items--;
        return isTrue;
    }
    isTrue = false;

    // If key is equal to a key currently in the map, remove the key/value
    // pair with that key from the map and return true.  Otherwise, make
    // no change to the map and return false.
    return isTrue;
}

 
bool Map::contains(const KeyType& key) const
{
    // Return true if key is equal to a key currently in the map, otherwise
    // false.
    for (Node * point = m_head; point != nullptr; point = point -> m_next)
    {
        if (point -> m_keyType == key)
        {
            //Basically loop through the linked list and if the key of the point equals to the key return true otherwise false.
            return true;
        }
    }
    return  false;
}
 
 
bool Map::get(const KeyType& key, ValueType& value) const
{
    for (Node * point = m_head; point != nullptr; point = point -> m_next)
    {
        //Loop through the linked list and find when the pointer's key is the key
        //from the parameter. then set the value to that pointer's value.
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

bool Map::get(int i, KeyType& key, ValueType& value) const
{
    //Basically just did what I did in HW but changed the loops so they incremeneted the pointer.
    Node * firstPoint = m_head;
    //Deal with the edge case first
    //if i < 0 and >= items return false.
    if (i < 0  ||  i >= m_items)
    {
        return false;
    }
    //while the pointer we declared isn't the nullptr
    while (firstPoint != nullptr)
    {
        int numGreaterThanI = 0;
        //set a count
        Node * secondPoint = m_head;
        while (secondPoint != nullptr)
        {
            //Everytime one is greater than the other increment count.
            if (firstPoint -> m_keyType > secondPoint -> m_keyType)
            {
                numGreaterThanI ++;
            }
            secondPoint = secondPoint -> m_next;
        }
        //if the count is equal to i set the key = the key associated with the pointer
        //set the value = the value associated with the pointer.
        if (numGreaterThanI == i)
        {
            key = firstPoint -> m_keyType;
            value = firstPoint -> m_valueType;
            return true;
        }
        firstPoint = firstPoint -> m_next;
        //increment the pointer one more time.
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
    //create a temporary head, int, and tail.
    
    m_head       = other.m_head;
    other.m_head = swapHead;
    //swap head pointers.
    
    m_tail       = other.m_tail;
    other.m_tail = swapTail;
    //swap tail pointers.
    
    m_items       = other.m_items;
    other.m_items = swapItems;
    //swap the number of items each map contains.
    // Exchange the contents of this map with the other one.
}

bool merge(const Map& m1, const Map& m2, Map& result)
{
    int j = 0;
    int k = 0;
    
    KeyType m1FirstKey; ValueType m1FirstValue;
    ValueType checkForSame;
    KeyType m2FirstKey; ValueType m2FirstValue;
    //declare multiple keytypes and value types for different get functions.
    bool hasSameOrDifferentValues = true;
    
    Map emptyMap;
    result.swap(emptyMap);
    //create and empty map and swap with the result incase result is not empty.
    while (j != m1.size())
    {
        m1.get(j, m1FirstKey, m1FirstValue);
        if (!m2.contains(m1FirstKey))
        {
            result.insertOrUpdate(m1FirstKey, m1FirstValue);
            //in the loop when it doesn't contain the key insert it.
        }
        else if (m2.contains(m1FirstKey))
        {
            m2.get(m1FirstKey, checkForSame);
            if (m1FirstValue == checkForSame)
            {
                //if it contains the key and the value from the first get and the value from this get are the same
                //insert the first key and first value.
                result.insertOrUpdate(m1FirstKey, m1FirstValue);
            }
            else
            {
                //otherwise set the bool variable to false and increment the loop.
                hasSameOrDifferentValues = false;
            }
        }
        j++;
    }
    
    while (k != m2.size())
    {
        //while it doesn't equal the size loop through and see if it doesn't contain the key and then insert it.
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
    
    int j = 0;
    
    KeyType keyB; ValueType valB;
    KeyType keyC; ValueType valC;
    KeyType keyD; ValueType valD;
    
    //Create three keytype and valuetype for the three gets.
    
    Map createEmptyMap;
    result.swap(createEmptyMap);
    //Basically if the map is not empty then swap it with an empty map
    int sizeOrig = m.size();
    //if the size is 1 or empty then have the result just be the m map.
    if (sizeOrig == 1 || sizeOrig == 0)
    {
        result = m;
    }
    
    m.get(0, keyB, valB);
    //in the loop see if the j + 1 = the size of the map m
    //if it is insert that in result
    //otherwise get the value at j+1 and insert that. 
    while (j != sizeOrig)
    {
        m.get(j, keyC, valC);
        if (j+1 == sizeOrig)
        {
            result.insertOrUpdate(keyC, valB);
        }
        else
        {
            m.get(j+1, keyD, valD);
            result.insertOrUpdate(keyC, valD);
        }
        j++;
    }
}
