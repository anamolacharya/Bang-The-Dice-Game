#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "characters.h"

CharacterDeck createCharacterDeck(void) {
    // The arrays of attributes that each character has. The same index means the same character
    char names[20][16] = {
            "Bart Cassidy",
            "Black Jack",
            "Calamity Janet",
            "El Gringo",
            "Jesse Jones",
            "Jourdonnais",
            "Kit Carlson",
            "Lucky Duke",
            "Paul Regret",
            "Pedro Ramirez",
            "Rose Doolan",
            "Sid Ketchum",
            "Slab the Killer",
            "Suzy Lafayette",
            "Vulture Sam",
            "Willy the Kid"
    };
    int hpMaxes[16] = {8, 8, 8, 7, 9, 7, 7, 8, 9, 8, 9, 8, 8, 8, 9, 8};
    // Create the data structure
    auto deck = new struct characterDeck;
    deck->top = nullptr;
    deck->cards = 0;
    // Iterate over each character
    for (int character = 0; character < 16; ++character) {
        // Create, initialize, and add a new card
        auto new_card = new struct characterCard;
        strcpy(new_card->character.name, names[character]);
        new_card->character.health = hpMaxes[character];
        new_card->next = deck->top;
        deck->top = new_card;
        ++deck->cards;
    }
    return deck;
}

Character dealCharacterCard(CharacterDeck deck) {
    // Determine which card to pop
    int cardNum = rand() % deck->cards;
    // Traverse to the card to pop
    CharacterCard *card = &deck->top;
    for (int i = 0; i < cardNum; ++i) {
        card = &(*card)->next;
    }
    // Delete the card, storing its value
    Character character = (*card)->character;
    CharacterCard next = (*card)->next;
    delete *card;
    *card = next;
    --deck->cards;
    // Return the found character
    return character;
}