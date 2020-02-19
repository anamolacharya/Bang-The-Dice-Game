#ifndef CS_2413_DICE_H
#define CS_2413_DICE_H

typedef enum {arrow, dynamite, bullseye1, bullseye2, beer, gatling} DiceVal;

typedef struct dice {
    DiceVal value;
    bool canReroll;
} Dice;

/**
 * Generate a random dice and return it
 * @author Jonathon Surles
 * @return the newly created dice object
 */
Dice rollDice();

#endif //CS_2413_DICE_H
