#ifndef CS_2413_ROLES_H
#define CS_2413_ROLES_H

typedef enum {sheriff, renegade, outlaw, deputy} Role;

typedef struct roleCard {
    Role role;
    struct roleCard *next;
} *RoleCard;

typedef struct roleDeck {
    RoleCard top;
    int cards;
} *RoleDeck;

/**
 * Create a deck with the appropriate number and type of cards
 * @author Jonathon Surles
 * @param players The number of players in the game
 * @return A deck with the correct number of roles for the given number of players
 */
RoleDeck createRoleDeck(int players);

/**
 * Pop a card from a random position in the deck
 * @author Jonathon Surles
 * @param deck The deck to modify
 * @return The role on the card at that position
 */
Role dealRoleCard(RoleDeck deck);

#endif //CS_2413_ROLES_H
