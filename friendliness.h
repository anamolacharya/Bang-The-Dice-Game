#ifndef CS_2413_FRIENDLINESS_H
#define CS_2413_FRIENDLINESS_H

#include "players.h"

typedef struct friendlinessGraph {
    int **matrix;
    struct seat **players;
    int sheriffID;
} *Graph;

/**
 * Create and initialize an empty graph
 * @param numPlayers The number of players in the graph
 * @param table The table of players
 * @return The newly created graph
 */
Graph createGraph(int numPlayers, Seat table);

#endif //CS_2413_FRIENDLINESS_H