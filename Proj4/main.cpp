
#include "Table.h"
#include <cassert>
#include <iostream>
using namespace std;

void test1()
{
    vector<string> cols = { "N", "Z" };
    Table t("Z", cols);
    assert(t.good());
    assert(t.insert("UCLA 90095"));
    assert(t.insert("Caltech 91125"));
    vector<vector<string>> v;
    t.find("90095", v);
    assert(v.size() == 1);
    assert(v[0][0] == "UCLA"  &&  v[0][1] == "90095");
    assert(t.select("Z > 90210", v) == 0);
    assert(v.size() == 1);
    assert(v[0][0] == "Caltech"  &&  v[0][1] == "91125");
    cout << "DONE" << endl;
}
 
void test2()
{
    vector<string> cols = { "N", "Z" };
    Table t("Z", cols);
    assert(t.good());
    assert(t.insert("UCLA 90095"));
    assert(t.insert("Caltech 91125"));
    assert(t.insert("Caltech 91125"));
    vector<vector<string>> v;
    t.find("91125", v);
    assert(v.size() == 2);
    assert(t.select("Z > 90210", v) == 0);
    assert(v.size() == 2);
    assert(t.insert("  Berk 333K"));
    assert(t.insert("  UCR 3X33"));
    assert(t.select("Z LT 95210", v) == 2);
    assert(v.size() == 3);
    assert(t.select("Z GT 95210", v) == 2);
    assert(v.size() == 0);
    assert(t.select("Z EQ 95210", v) == 2);
    assert(v.size() == 0);
    assert(t.select("Z EQ 333K", v) == -1);
    assert(t.select("Z EQ 91125", v) == 2);
    assert(v.size() == 2);
    assert(t.select("Z EQ 91125", v) == 2);
    assert(t.select("Z NE 91125", v) == 2);
    assert(v.size() == 1);
    assert(t.insert("UCI .333"));
    assert(t.select("Z GE .333", v) == 2);
    assert(v.size() == 4);
    assert(t.select("Z LE 99999", v) == 2);
    assert(v.size() == 4);
    assert(t.select("N < Z", v) == 0);
    assert(v.size() == 6);
    assert(t.select("N = U", v) == 0);
    assert(v.size() == 0);
    assert(t.select("N == U", v) == 0);
    assert(v.size() == 0);
    assert(t.select("N == UCR", v) == 0);
    assert(v.size() == 1);
}

int main()
{
    vector<string> friends = { "Name", "Birthday", "Phone", "FavColor" };
        Table myFriends("Name", friends);
        assert(myFriends.good());
        assert(myFriends.insert("Patty 0423 1234567 pink"));
        assert(myFriends.insert("Monica            0223 12435235 blue"));
        assert(myFriends.insert("   Natalie  1225 12481241       'light purple'"));
        assert(myFriends.insert("Matthew 0312        14685343 \t\t\t black"));
        vector<vector<string>> records;
        myFriends.find("Natalie", records);
        assert(records.size() == 1);
        myFriends.find("125451", records);
        assert(records.size() == 0);
        vector<vector<string>> anotherVector;
        assert(myFriends.select("name = Natale", anotherVector) == -1);
        assert(myFriends.select("Birthday on Christmas", anotherVector) == -1);
        assert(myFriends.select("Phone GT ''", anotherVector) == -1);
        assert(myFriends.select("Birthday eq 0423", anotherVector) == 0);
        assert(anotherVector.size() == 1);
        assert(myFriends.select("FavColor > apricot", anotherVector) == 0);
        assert(anotherVector.size() == 4);
        assert(myFriends.insert("Patty\t\t 0734 1455345 orange"));
        myFriends.find("Patty", records);
        assert(records.size() == 2);
        assert(!myFriends.insert("Patrick 0222 124125125"));
        assert(myFriends.insert("Brad 0812 1423521 brown"));
        assert(myFriends.insert("Chad 0118 1253463 red"));
        assert(myFriends.insert("'Maddy Tom' 1124 12354632 indigo"));
        myFriends.find("Maddy", records);
        assert(records.size() == 0);
        myFriends.find("Maddy Tom", records);
        assert(records.size() == 1);
        assert(myFriends.select("Phone gT 1", anotherVector) == 0);
        assert(anotherVector.size() == 8);
        assert(myFriends.insert("Frank December07 12435233 charcoal"));
        assert(myFriends.insert("Phil 12December 12343523 yellow"));
        assert(myFriends.select("Birthday LT 12512356", anotherVector) == 2);
        assert(anotherVector.size() == 8);

    cout<<"DONEEEE"<<endl;
}
