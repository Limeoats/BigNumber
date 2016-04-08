#include "src/bignumber.h"

#include <assert.h>

int main() {
    //Test the add functionality
    assert((BigNumber("50") + BigNumber("32")).getString() == "82");
    assert((BigNumber("5") + BigNumber("622")).getString() == "627");
    assert((BigNumber("-33") + BigNumber("8")).getString() == "-25");
    assert((BigNumber("15535") + BigNumber("0")).getString() == "15535");
    assert((BigNumber("126") + BigNumber("39285")).getString() == "39411");

    //Test the subtract functionality
    assert((BigNumber("50") - BigNumber("32")).getString() == "18");
    assert((BigNumber("50") - BigNumber("60")).getString() == "-10");
    assert((BigNumber("0") - BigNumber("46")).getString() == "-46");
    assert((BigNumber("50") - BigNumber("50")).getString() == "0");
    assert((BigNumber("482847") - BigNumber("89787941")).getString() == "-89305094");
    assert((BigNumber("6828") - BigNumber("1")).getString() == "6827");
}