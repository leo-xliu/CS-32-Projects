

#ifndef SET_INCLUDED
#define SET_INCLUDED

#include <string>
using ItemType = std::string;

class Set
{
private:
    //Circularly doubly-linked list creation
    struct Node
    {
        ItemType mValue;
        Node* mNext;
        Node* mPrev;
    };
    Node* mHead;
    int mSize;
    
public:
    //Constructors
    Set();
    Set(const Set& other);
    
    //Check for empty set
    bool empty() const;
    //Assessor for set size
    int size() const;
    //Add itemtype to list
    bool insert(const ItemType& value);
    //Remove itemtype from list
    bool erase(const ItemType& value);
    //Check if itemtype is in list
    bool contains(const ItemType& value) const;
    //Possibly give parameter itemtype a value from list
    bool get(int pos, ItemType& value) const;
    //Swap two sets
    void swap(Set& other);
    //Assignment operator
    Set& operator=(const Set& rhs);
    //Destructor
    ~Set();
    
};

//Combine two sets
void unite(const Set& s1, const Set& s2, Set& result);

//Combine two sets in a way that only gives unique values
void difference(const Set& s1, const Set& s2, Set& result);

#endif //SET_INCLUDED
