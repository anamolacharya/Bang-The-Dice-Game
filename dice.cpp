#include <iostream>
#include <stdlib.h>
#include "dice.h"

using namespace std;

Dice rollDice() {
    Dice die = Dice();
    die.value = (DiceVal)(rand() % 6);
    die.canReroll = die.value != dynamite;
    return die;
}
