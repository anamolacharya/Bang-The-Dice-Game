#ifndef CS_2413_DISPLAY_H
#define CS_2413_DISPLAY_H

#include "bang.h"
#include "players.h"

/**
 * Print ascii art of the title as well as the authors' names
 * @author Anamol Acharya
 */
void displayTitle();

/**
 * Print ascii art of an arrow die
 * @author Shree Shrestha
 */
void print_arrow();

/**
 * Print ascii art of a beer die
 * @author Shree Shrestha
 */
void print_beer();

/**
 * Print ascii art of dynamite die
 * @author Shree Shrestha
 */
void print_dynamite();

/**
 * Print ascii art of a gatling gun die
 * @author Shree Shrestha
 */
void print_gatlingGun();

/**
 * Print ascii art of a bullseye (1) die
 * @author Shree Shrestha
 */
void print_bullsEye1();

/**
 * Print ascii art of a bullseye (2) die
 * @author Shree Shrestha
 */
void print_bullsEye2();

/**
 * Print out all of the dice in the array of dice
 * @author Jonathon Surles
 * @param dice The array of dice to print
 */
void printDice(Dice *dice);

/**
 * Print out the winners of the game
 * @author Jonathon Surles
 * @param players The array of players
 * @param numPlayers The number of players
 * @param winCondition The condition that ended the game
 */
void displayWinners(Player *players, int numPlayers, GameOver winCondition);

/**
 * Print out the death of a player
 * @author Jonathon Surles
 * @param player The player who has died
 */
void displayDeath(Player *player);

#endif //CS_2413_DISPLAY_H
