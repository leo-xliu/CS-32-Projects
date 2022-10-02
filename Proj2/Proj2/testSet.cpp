#include "Set.h"
#include <iostream>
#include <cassert>
using namespace std;

int main()
{
    //Insert function testing
    Set a;
    assert(a.empty() && a.size() == 0);
    assert(a.insert("2") && a.size() == 1);
    assert(a.insert("3") && a.size() == 2); //insert a large value
    assert(a.insert("1") && a.size() == 3); //insert a smaller value
    assert(a.contains("1") && a.contains("2") && a.contains("3"));
    assert(!a.empty());
    assert(!a.insert("2") && a.size() == 3); //does not insert
    assert(a.insert("test") && a.size() == 4);
    for (int i = 0; i < 100; i++) //add string integers 4-100
    {
        string test = to_string(i);
        a.insert(test);
        assert(a.contains(test));
    }
    assert(a.size() == 101);
    assert(a.insert("") && a.size() == 102);
    
    //Erase function testing
    Set b;
    assert(b.empty() && b.size() == 0);
    assert(!b.erase("")); //attempt to erase from empty list
    for (int i = 0; i < 10; i++)
    {
        string test = to_string(i);
        b.insert(test);
        assert(b.contains(test));
    }
    assert(b.size() == 10);
    assert(b.erase("0") && !b.contains("0") && b.size() == 9); //erase from front of list
    assert(b.erase("9") && !b.contains("9") && b.size() == 8); //erase from back of list
    assert(b.erase("4") && !b.contains("4") && b.size() == 7); //erase from middle of list
    assert(b.erase("2") && !b.contains("2") && b.size() == 6); //erase from second value of list
    assert(!b.erase("0") && b.size() == 6); //value not in list
    
    
    //Get function testing
    Set c;
    ItemType placehold = "non";
    assert(c.empty() && c.size() == 0);
    //General testing for get
    assert(!c.get(0, placehold) && placehold == "non");
    assert(c.insert("a") && c.insert("b") && c.insert("c") && c.size() == 3);
    assert(c.get(0, placehold) && placehold == "c");
    assert(c.get(1, placehold) && placehold == "b");
    assert(c.get(2, placehold) && placehold == "a");
    assert(!c.get(3, placehold) && placehold == "a");
    //Testing the sorting aspect of insert using get
    Set d;
    assert(d.insert("abcdef") && d.insert("bcdefg") && d.insert("aZZZZZ") && d.insert("Abcdef") && d.insert("z") && d.size() == 5);
    assert(d.get(0, placehold) && placehold == "z");
    assert(d.get(1, placehold) && placehold == "bcdefg");
    assert(d.get(2, placehold) && placehold == "abcdef");
    assert(d.get(3, placehold) && placehold == "aZZZZZ");
    assert(d.get(4, placehold) && placehold == "Abcdef");
    
    //Swap function testing
    //Using previously declared sets a and b
    a.swap(a); //aliasing
    assert(a.size() == 102 && a.contains("test"));
    a.swap(b);
    assert(a.size() == 6 && a.contains("5"));
    assert(b.size() == 102 && b.contains("test"));
    assert(a.erase("5") && a.size() == 5 && b.size() == 102);
    assert(a.insert("100000") && !b.contains("100000")); //Make sure they are independent of each other
    assert(b.insert("20000") && !a.contains("20000"));
    b.swap(a); //Make sure going backwards works too
    assert(a.size() == 103 && a.contains("test"));
    assert(b.size() == 6 && b.contains("100000"));

    
    //Copy constructor testing
    //Using previously declared sets c
    Set e(c);
    assert(e.size() == 3 && e.contains("a") && e.contains("b") && e.contains("c"));
    assert(e.insert("d") && e.size() == 4 && !c.contains("d")); //make sure that modifying e doesnt affect c
    assert(e.erase("a") && e.size() == 3 && c.contains("a"));
    
    
    //Assignment operator testing
    //Using previously declare sets e and d
    e = e; //aliasing
    assert(e.size() == 3);
    e = d;
    assert(e.size() == 5);
    assert(e.insert("hello") && e.insert("bye") && !d.contains("hello") && !d.contains("bye"));
    d = e;
    assert(d.size() == 7 && d.insert("cya") && !e.contains("cya"));
    
    
    //Destructor/Memory leak testing
    Set f;
    if (f.empty())
    {
        Set g(d);
        f = g;
    }
    assert(f.contains("cya") && f.size() == 8);
    assert(d.size() == 8);
    Set result;
    unite(c, b, result);
    difference(d,e, result);
    
    //Unite function testing
    Set h;
    Set i;
    assert(h.insert("1") && h.insert("both") && h.insert("2") && h.insert("unique") && h.insert("3"));
    assert(i.insert("4") && i.insert("both") && i.insert("5") && i.insert("unique2") && i.insert("6"));
    Set united;
    unite(h, i, united);
    assert(united.size() == 9);
    assert(united.contains("both") && united.contains("unique"));
    unite(h, i, h); //aliasing
    assert(h.contains("unique2") && h.size() == 9);
    unite(h,h,h); //aliasing
    assert(h.contains("1") && h.size() == 9);
    unite (i,h, i); //aliasing
    assert(i.contains("1") && i.size() == 9);
    
    
    //Difference function testing
    Set j;
    Set k;
    Set differenced;
    assert(j.insert("a") && j.insert("b") && j.insert("c") && j.insert("d") && j.insert("e"));
    assert(k.insert("a") && k.insert("b") && k.insert("f") && k.insert("g") && k.insert("h") && k.insert("i"));
    difference(j, k, differenced);
    assert(differenced.size() == 7 && !differenced.contains("a") && !differenced.contains("b"));
    difference(j,j,j); //aliasing
    assert(j.size() == 0 && j.empty());
    difference(k, differenced, k); //aliasing
    assert(k.size() == 5 && k.contains("a") & k.contains("b"));
    difference(k, differenced, differenced); //aliasing
    assert(differenced.size() == 6 && differenced.contains("f") && differenced.contains("i"));
    
    cout<<"All test cases passed!"<<endl;
    return 0;
}
