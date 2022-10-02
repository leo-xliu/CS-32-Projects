#include "provided.h"
#include <iostream>
#include <cassert>
using namespace std;


int main()
{
    SmartPlayer bp1("Leopard");
    HumanPlayer bp2("Computer");
    Game g(4, 4, 3, &bp1, &bp2);
    g.play();
}

