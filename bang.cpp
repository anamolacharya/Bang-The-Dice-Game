#include <iostream>
#include "players.h"
#include "dice.h"
#include "bang.h"
#include "display.h"
#include "decisions.h"

#define SHOOT_PENALTY -2
#define HEAL_BONUS 1

using namespace std;

void bang() {

    displayTitle();
    cout << "Press enter to begin simulation..." << endl;
    cin.get();

    int numPlayers = rand() % 5 + 4;

    Player players[numPlayers];
    RoleDeck roleDeck = createRoleDeck(numPlayers);
    CharacterDeck characterDeck = createCharacterDeck();

    // Initialize players
    for (int i = 0; i < numPlayers; ++i) {
        players[i].id = i;
        players[i].role = dealRoleCard(roleDeck);
        players[i].character = dealCharacterCard(characterDeck);
        players[i].maxHP = players[i].character.health + (players[i].role == sheriff ? 2 : 0);
        players[i].currentHP = players[i].maxHP;
        players[i].arrows = 0;
    }

    // Create table
    Seat activePlayer = generateTable(players, numPlayers);
    int alivePlayers = numPlayers;
    int tableArrows = 9;
    bool activePlayerDead = false;
    GameOver gameEnd = noExit;

    Graph friendliness = createGraph(numPlayers, activePlayer);

    do {
        cout << activePlayer->player->character.name << "'s turn." << endl;
        // Initial roll
        Dice dice[NUM_DICE];
        for (int die = 0; die < NUM_DICE; ++die) {
            dice[die] = rollDice();
        }
        cout << "Their first roll:" << endl;
        printDice(dice);
        // Arrow logic
        for (int die = 0; die < NUM_DICE; ++die) {
            if (dice[die].value == arrow) {
                --tableArrows;
                if (!tableArrows) {
                    cout << "Indian attack!" << endl;
                    Seat ptr = activePlayer;
                    do {
                        ptr->player->currentHP -= ptr->player->arrows;
                        tableArrows += ptr->player->arrows;
                        ptr->player->arrows = 0;
                        if (checkDeath(ptr, friendliness, alivePlayers) && ptr == activePlayer) {
                            activePlayerDead = true;
                            break;
                        }
                        ptr = ptr->left;
                    } while (ptr != activePlayer);
                    gameEnd = checkEnd(players, numPlayers);
                    if (gameEnd) {
                        break;
                    }
                }
            }
        }
        // Rerolls
        int rerolls = 0;
        bool canReroll = true;
        while (true) {
            // Check if we can reroll
            int numDynamite = 0;
            for (int die = 0; die < NUM_DICE; ++die) {
                if (dice[die].value == dynamite) {
                    ++numDynamite;
                }
            }
            if (rerolls >= 2) {
                canReroll = false;
            }
            if (numDynamite >= 3) {
                canReroll = false;
                --activePlayer->player->currentHP;
                if (checkDeath(activePlayer, friendliness, alivePlayers)) {
                    activePlayerDead = true;
                    gameEnd = checkEnd(players, numPlayers);
                }
                break;
            }
            if (!canReroll || gameEnd) {
                break;
            }
            // Check if we want to reroll
            int wantReroll = rand() % 2;
            if (wantReroll) {
                cout << "They have chosen to reroll." << endl;
                reroll(dice);
                printDice(dice);
                // Check for any arrows
                for (int die = 0; die < NUM_DICE; ++die) {
                    if (dice[die].value == arrow) {
                        --tableArrows;
                        ++activePlayer->player->arrows;
                        if (!tableArrows) {
                            cout << "Indian attack!" << endl;
                            Seat ptr = activePlayer;
                            do {
                                ptr->player->currentHP -= ptr->player->arrows;
                                tableArrows += ptr->player->arrows;
                                ptr->player->arrows = 0;
                                if (checkDeath(ptr, friendliness, alivePlayers) && ptr == activePlayer) {
                                    activePlayerDead = true;
                                    break;
                                }
                                ptr = ptr->left;
                            } while (ptr != activePlayer);
                            gameEnd = checkEnd(players, numPlayers);
                            if (gameEnd) {
                                break;
                            }
                        }
                    }
                }
                ++rerolls;
            } else {
                break;
            }
        }
        // Dice resolution
        for (int die = 0; die < NUM_DICE && !gameEnd; ++die) {
            switch (dice[die].value) {
                case bullseye1:
                case bullseye2: {
                    Seat left = nullptr, right = nullptr;
                    if (dice[die].value == bullseye1) {
                        left = activePlayer->left;
                        right = activePlayer->right;
                    } else if (dice[die].value == bullseye2) {
                        left = activePlayer->left->left;
                        right = activePlayer->right->right;
                    }
                    bool outlawsDead = true;
                    for (int i = 0; i < numPlayers; ++i) {
                        if (players[i].role == outlaw && players[i].currentHP > 0) {
                            outlawsDead = false;
                            break;
                        }
                    }
                    Seat toShoot = shoot(left, right, friendliness, activePlayer->player->role, outlawsDead, true);
                    cout << "They have chosen to shoot " << toShoot->player->character.name << endl;
                    --toShoot->player->currentHP;
                    friendliness->matrix[activePlayer->player->id][toShoot->player->id] += SHOOT_PENALTY;
                    friendliness->matrix[toShoot->player->id][activePlayer->player->id] += SHOOT_PENALTY;
                    if (checkDeath(toShoot, friendliness, alivePlayers)) {
                        --alivePlayers;
                        tableArrows += toShoot->player->arrows;
                        toShoot->player->arrows = 0;
                        gameEnd = checkEnd(players, numPlayers);
                    }
                    break;
                }
                case beer: {
                    Seat toHeal = heal(activePlayer, friendliness, false);
                    cout << "They have chosen to heal " << toHeal->player->character.name << endl;
                    if (toHeal->player->currentHP < toHeal->player->maxHP) {
                        ++toHeal->player->currentHP;
                    }
                    friendliness->matrix[activePlayer->player->id][toHeal->player->id] += SHOOT_PENALTY;
                    friendliness->matrix[toHeal->player->id][activePlayer->player->id] += SHOOT_PENALTY;
                    break;
                }
                default: break;
            }
            if (gameEnd) {
                break;
            }
        }
        int numGatling = 0;
        for (int die = 0; die < NUM_DICE; ++die) {
            if (dice[die].value == gatling) {
                ++numGatling;
            }
        }
        if (numGatling >= 3) {
            cout << "They are firing the gatling gun!" << endl;
            Seat ptr = activePlayer->right;
            while (ptr != activePlayer) {
                --ptr->player->currentHP;
                ptr = ptr->left;
                checkDeath(ptr->right, friendliness, alivePlayers);
            }
            tableArrows += activePlayer->player->arrows;
            activePlayer->player->arrows = 0;
        }
        // Check for game end
        gameEnd = checkEnd(players, numPlayers);
        // Pass the turn
        activePlayer = activePlayer->left;
    } while (!gameEnd);
    displayWinners(players, numPlayers, gameEnd);
}

void reroll(Dice *dice)
{
    int totalRerollable = 0;
    for (int die = 0; die < NUM_DICE; ++die) {
        if (dice[die].canReroll) {
            ++totalRerollable;
        }
    }
    int numReroll = rand() % totalRerollable + 1;

    // Reroll all the dice
    while (numReroll > 0) {
        // Determine which rerollable dice to reroll
        int toReroll = rand() % numReroll;
        // Traverse to that dice
        Dice *reroll = nullptr;
        int rerollNum = 0;
        for (int die = 0; die < NUM_DICE; ++die) {
            if (dice[die].canReroll) {
                if (++rerollNum > toReroll) {
                    reroll = &dice[die];
                    break;
                }
            }
        }
        if (!reroll) {
            cerr << "ERROR: Rerollable dice not found." << endl;
            return;
        }
        // Reroll the die
        *reroll = rollDice();
        reroll->canReroll = false;
        --numReroll;
    }
    // Reset canReroll values
    for (int die = 0; die < NUM_DICE; ++die) {
        dice[die].canReroll = dice[die].value != dynamite;
    }
}

GameOver checkEnd(Player *players, int numPlayers) {
    // Check for sheriff death conditions
    for (int i = 0; i < numPlayers; ++i) {
        if (players[i].role == sheriff && players[i].currentHP <= 0) {
            // Check if exactly one renegade is alive
            int aliveCount = 0;
            for (int j = 0; j < numPlayers; ++j) {
                if (players[j].currentHP > 0) {
                    ++aliveCount;
                    if (aliveCount > 1 || players[j].role != renegade) {
                        return outlawWin;
                    }
                }
            }
            return renegadeWin;
        }
    }
    // Check if all outlaws and renegades are dead
    for (int i = 0; i < numPlayers; ++i) {
        if (players[i].currentHP > 0 && (players[i].role == outlaw || players[i].role == renegade)) {
            return noExit;
        }
    }
    return deputyWin;
}

bool checkDeath(Seat player, Graph friendliness, int alivePlayers) {
    if (player->player->currentHP > 0) {
        return false;
    } else {
        Seat ptr = player->left;
        int playerID = player->player->id;
        int multiplier = player->player->role == sheriff || player->player->role == renegade ? 1 : -1;
        for (int i = 1; i < alivePlayers; ++i) {
            if (ptr->player->role == sheriff) {
                continue;
            }
            friendliness->matrix[friendliness->sheriffID][ptr->player->id] += multiplier * friendliness->matrix[playerID][ptr->player->id];
            friendliness->matrix[ptr->player->id][friendliness->sheriffID] += multiplier * friendliness->matrix[playerID][ptr->player->id];
            ptr = ptr->left;
        }
        player->left->right = player->right;
        player->right->left = player->left;
        displayDeath(player->player);
        return true;
    }
}