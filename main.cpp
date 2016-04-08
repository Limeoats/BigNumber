#include "src/bignumber.h"

#include <assert.h>

int main() {
    //Addition
    assert((BigNumber("50") + BigNumber("32")).getString() == "82");
    assert((BigNumber("5") + BigNumber("622")).getString() == "627");
    assert((BigNumber("-33") + BigNumber("8")).getString() == "-25");
    assert((BigNumber("15535") + BigNumber("0")).getString() == "15535");
    assert((BigNumber("126") + BigNumber("39285")).getString() == "39411");
    assert((BigNumber("0") + BigNumber("0")).getString() == "0");

    //Subtraction
    assert((BigNumber("50") - BigNumber("32")).getString() == "18");
    assert((BigNumber("50") - BigNumber("60")).getString() == "-10");
    assert((BigNumber("0") - BigNumber("46")).getString() == "-46");
    assert((BigNumber("50") - BigNumber("50")).getString() == "0");
    assert((BigNumber("482847") - BigNumber("89787941")).getString() == "-89305094");
    assert((BigNumber("6828") - BigNumber("1")).getString() == "6827");

    //Exponentiation
    assert((BigNumber("2").pow(3)).getString() == "8");
    assert((BigNumber("1").pow(38)).getString() == "1");
    assert((BigNumber("5").pow(2)).getString() == "25");
    assert((BigNumber("10").pow(10)).getString() == "10000000000");
    assert((BigNumber("5").pow(1)).getString() == "5");
    assert((BigNumber("5").pow(0)).getString() == "1");
    assert((BigNumber("-5").pow(2)).getString() == "25");

    //Greater than
    assert((BigNumber("5") > BigNumber("2")));
    assert((BigNumber("30") > BigNumber("-40")));
    assert((BigNumber("-5") > BigNumber("-10")));
    assert((BigNumber("0") > BigNumber("-1")));

    //Less than
    assert((BigNumber("10") < BigNumber("20")));
    assert((BigNumber("-5") < BigNumber("0")));
    assert((BigNumber("30") < BigNumber("30000")));

    //Greater than or equal to
    assert((BigNumber("5") >= BigNumber("0")));
    assert((BigNumber("-5") >= BigNumber("-5")));
    assert((BigNumber("-5") >= BigNumber("-10")));
    assert((BigNumber("0") >= BigNumber("0")));
    assert((BigNumber("32") >= BigNumber("-32")));

    //Less than or equal to
    assert((BigNumber("5") <= BigNumber("10")));
    assert((BigNumber("0") <= BigNumber("0")));
    assert((BigNumber("-5") <= BigNumber("0")));
    assert((BigNumber("30") <= BigNumber("30")));
    assert((BigNumber("400") <= BigNumber("392342")));

    //Index
    assert(BigNumber("423")[1] == 2);
    assert(BigNumber("0")[0] == 0);
    assert(BigNumber("-5")[1] == 5);
}