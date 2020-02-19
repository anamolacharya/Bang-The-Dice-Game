#include <iostream>
#include "players.h"
#include "display.h"
#include "friendliness.h"

using namespace std;

Seat generateTable(Player *players, int numPlayers) {
    Seat first = nullptr, prev = nullptr;
    for (int i = 0; i < numPlayers; ++i) {
        // Create the new node
        auto newSeat = new struct seat;
        newSeat->player = players + i;
        // Update links
        if (!first) {
            first = newSeat;
        } else {
            first->right = newSeat;
        }
        if (prev) {
            prev->left = newSeat;
        }
        newSeat->right = prev;
        prev = newSeat;
    }
    // Complete the links
    if (!first) {
        cerr << "ERROR: could not generate double circular linked list of players" << endl;
        return nullptr;
    }
    first->right = prev;
    prev->left = first;
    while (true) {
        if (first->player->role == sheriff) {
            return first;
        }
        first = first->left;
    }
}

