#ifndef CS_2413_BANG_H
#define CS_2413_BANG_H

#include "dice.h"
#include "players.h"
#include "friendliness.h"

#define NUM_DICE 5

typedef enum {noExit, outlawWin, renegadeWin, deputyWin} GameOver;

/**
 * The main function to run the game
 * @authors Anamol Acharya, Jonathon Surles, and Shree Shrestha
 */
void bang();

/**
 * Reroll a random number of dice in the provided array
 * @author Anamol Acharya
 * @param dice The array of dice
 */
void reroll(Dice *dice);

/**
 * Check if the game is over. If so, return the win condition that was met.
 * @param players The array of all players who started the game
 * @param numPlayers The number of players at the beginning of the game
 * @return The win condition that was met
 */
GameOver checkEnd(Player *players, int numPlayers);

/**
 * Check if the player at the given seat has died. If they have, remove them from the table
 * @param player The player at the table
 * @param friendliness The friendliness graph to update if death happened
 * @return True if the player died, false if they are still alive
 */
bool checkDeath(Seat player, Graph friendliness, int alivePlayers);

#endif //CS_2413_BANG_H
