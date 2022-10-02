#include "Set.h"

Set::Set()
{
    mHead = new Node;
    mHead->mNext = mHead;
    mHead->mPrev = mHead;
    mSize = 0;
    
}

Set::Set(const Set& other)
{
    mSize = other.mSize;
    mHead = new Node;
    mHead->mNext = mHead;
    mHead->mPrev = mHead;
    Node* p = mHead;
    Node* p2 = other.mHead;
    //Iterates through the list and makes a new identical copy
    for (int i = 0; i < mSize; i++)
    {
        p->mNext = new Node;
        p->mNext->mPrev = p;
        p->mNext->mValue = p2->mNext->mValue;
        //Finishes the circle aspect of list
        if (i == mSize-1)
        {
            p->mNext->mNext = mHead;
            mHead->mPrev = p->mNext;
        }
        p = p->mNext;
        p2 = p2->mNext;
    }
}

bool Set::empty() const
{
    return(mSize == 0);
}

int Set::size() const
{
    return(mSize);
}

bool Set::insert(const ItemType& value)
{
    //Iterate through list for duplicates
    for (Node* p = mHead->mNext; p != mHead; p = p->mNext)
    {
        if (p->mValue == value)
        {
            return false;
        }
    }
    if (mSize > 0)
    {
        //Iterate through list to compare values to see where to place new value
        for (Node* p = mHead->mNext; p != mHead; p = p->mNext)
        {
            if (p->mValue < value)
            {
                Node* temp = p->mPrev;
                p->mPrev = new Node;
                p->mPrev->mValue = value;
                p->mPrev->mPrev = temp;
                p->mPrev->mNext = p;
                temp->mNext = p->mPrev;
                break;
            }
            //If new value is the smallest value, it will be placed at the end
            else if ((p->mNext == mHead) && (p->mValue > value))
            {
                p->mNext = new Node;
                p->mNext->mValue = value;
                p->mNext->mNext = mHead;
                p->mNext->mPrev = p;
                mHead->mPrev = p->mNext;
                break;
            }
        }
    }
    //For special case of empty list
    else
    {
        mHead->mNext = new Node;
        mHead->mNext->mValue = value;
        mHead->mNext->mNext = mHead;
        mHead->mNext->mPrev = mHead;
        mHead->mPrev = mHead->mNext;
    }
    mSize++;
    return true;
}

bool Set::erase(const ItemType& value)
{
    //Iterates through list to find value
    for (Node* p = mHead->mNext; p != mHead; p = p->mNext)
    {
        if (p->mValue == value)
        {
            //If present, rearrange the pointers and delete the dynamically allocated node
            p->mPrev->mNext = p->mNext;
            p->mNext->mPrev = p->mPrev;
            delete p;
            mSize--;
            return true;
        }
    }
    return false;
}

bool Set::contains(const ItemType& value) const
{
    for (Node* p = mHead->mNext; p != mHead; p = p->mNext)
    {
        if (p->mValue == value)
        {
            return true;
        }
    }
    return false;
}

bool Set::get(int pos, ItemType& value) const
{
    if ((pos >=0) && (pos < mSize))
    {
        //Runs through sorted list and points to desired node position
        Node* p = mHead->mNext;
        for (int i = 0; i < pos; i++)
        {
            p = p->mNext;
        }
        value = p->mValue;
        return true;
    }
    else
    {
        return false;
    }
}

void Set::swap(Set& other)
{
    //Make sure no error for when the same set is attempted to be copied
    if (this != &other)
    {
        //Temporary node pointer to swap the heads of the lists which is all that is needed
        Node* temp;
        temp = mHead;
        mHead = other.mHead;
        other.mHead = temp;
        
        //Temporary integer to switch sizes
        int temp2;
        temp2 = mSize;
        mSize = other.mSize;
        other.mSize = temp2;
    }
}

Set& Set::operator=(const Set& rhs)
{
    if (this != &rhs)
    {
        Set temp(rhs);
        swap(temp);
    }
    return(*this);
}

Set::~Set()
{
    Node* p = mHead;
    //Iterates through list to deallocate all dynamically allocated nodes
    for (int i = 0; i < mSize; i++)
    {
        p = p->mNext;
        delete p->mPrev;
    }
    delete p;
}


void unite(const Set& s1, const Set& s2, Set& result)
{
    //Guards against alliasing
    Set temps1(s1);
    Set temps2(s2);
    result = temps1;
    //Iterates throguh temps2 and inserts any new value
    for (int i = 0; i < temps2.size(); i++)
    {
        ItemType temp;
        temps2.get(i, temp);
        result.insert(temp);
    }
}

void difference(const Set& s1, const Set& s2, Set& result)
{
    //Guards against alliasing
    Set temps1(s1);
    Set temps2(s2);
    result = temps1;
    //Iterates through temps2 and deletes identical values and inserts new ones
    for (int i = 0; i < temps2.size(); i++)
    {
        ItemType temp;
        temps2.get(i, temp);
        if (result.contains(temp))
        {
            result.erase(temp);
        }
        else
        {
            result.insert(temp);
        }
    }
}

