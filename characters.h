#ifndef BANG_PROJECT_CHARACTERS_H
#define BANG_PROJECT_CHARACTERS_H

typedef struct character {
    char name[20];
    int health;
} Character;

typedef struct characterCard {
    Character character;
    struct characterCard *next;
} *CharacterCard;

typedef struct characterDeck {
    CharacterCard top;
    int cards;
} *CharacterDeck;

/**
 * Create a deck with the appropriate number and type of cards
 * @return A deck with the correct number of roles for the given number of players
 */
CharacterDeck createCharacterDeck(void);

/**
 * Pop a card from a random position in the deck
 * @param deck The deck to modify
 * @return The role on the card at that position
 */
Character dealCharacterCard(CharacterDeck deck);

#endif //BANG_PROJECT_CHARACTERS_H
