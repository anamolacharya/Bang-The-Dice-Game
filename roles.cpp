#include <stdlib.h>
#include "roles.h"

RoleDeck createRoleDeck(int players) {
    // The lookup table that determines the number of each role for the given number of players
    int lookupTable[5][4] = {
            {1, 1, 2, 0},
            {1, 1, 2, 1},
            {1, 1, 3, 1},
            {1, 1, 3, 2},
            {1, 2, 3, 2}
    };
    int tableIndex = players - 4;
    // Create the data structure
    Role roles[] = {sheriff, renegade, outlaw, deputy};
    auto deck = new struct roleDeck;
    deck->top = nullptr;
    deck->cards = 0;
    // Iterate over each role
    for (int role = 0; role < 4; ++role) {
        // Repeat the appropriate number of times for that role according to the table
        for (int roleNum = 0; roleNum < lookupTable[tableIndex][role]; ++roleNum) {
            // Create, initialize, and add a new card
            auto new_card = new struct roleCard;
            new_card->role = roles[role];
            new_card->next = deck->top;
            deck->top = new_card;
            ++deck->cards;
        }
    }
    return deck;
}

Role dealRoleCard(RoleDeck deck) {
    // Determine which card to pop
    int cardNum = rand() % deck->cards;
    // Traverse to the card to pop
    RoleCard *card = &deck->top;
    for (int i = 0; i < cardNum; ++i) {
        card = &(*card)->next;
    }
    // Delete the card, storing its value
    Role role = (*card)->role;
    RoleCard next = (*card)->next;
    delete *card;
    *card = next;
    --deck->cards;
    // Return the found role
    return role;
}
