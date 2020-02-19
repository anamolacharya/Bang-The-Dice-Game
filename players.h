#ifndef CS_2413_PLAYERS_H
#define CS_2413_PLAYERS_H

#include "characters.h"
#include "roles.h"

typedef struct player {
    int id;
    Character character;
    Role role;
    int maxHP;
    int currentHP;
    int arrows;
} Player;

typedef struct seat {
    Player *player;
    struct seat *left;
    struct seat *right;
} *Seat;

/**
 * Generate the "table" for the game, represented as a double linked list of seats.
 * @param players The array of players
 * @param numPlayers The number of players
 * @return The generated table, specifically the first player (the sheriff)
 */
Seat generateTable(Player players[], int numPlayers);

#endif //CS_2413_PLAYERS_H
