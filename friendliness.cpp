#include "friendliness.h"
#include <stdlib.h>
#include <limits.h>

Graph createGraph(int numPlayers, Seat table) {
    auto graph = new struct friendlinessGraph;
    // Allocate memory for matrix
    graph->matrix = (int **) malloc(numPlayers * sizeof(int *));
    for (int i = 0; i < numPlayers; ++i) {
        graph->matrix[i] = (int *) malloc(numPlayers * sizeof(int));
    }
    // Initialize matrix
    for (int i = 0; i < numPlayers; ++i) {
        for (int j = 0; i < numPlayers; ++i) {
            graph->matrix[i][j] = 0;
        }
    }
    // Initialize player array
    graph->players = (Seat *) malloc(numPlayers * sizeof(Seat));
    for (int i = 0; i < numPlayers; ++i) {
        graph->players[table->player->id] = table;
        if (table->player->role == sheriff) {
            graph->sheriffID = table->player->id;
        }
        table = table->left;
    }
    graph->matrix[graph->sheriffID][graph->sheriffID] = INT_MAX;
    return graph;
}
