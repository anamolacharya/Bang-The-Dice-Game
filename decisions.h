#ifndef CS_2413_DECISIONS_H
#define CS_2413_DECISIONS_H

#include "players.h"
#include "friendliness.h"

/**
 * Determine which of the two players to shoot
 * @param left The left player
 * @param right The right player
 * @param friendliness The friendliness graph
 * @param role The role of the active player
 * @param mustShoot Whether this function call is determining if we want that die or if we are resolving that die
 * @return The player to shoot, or nullptr if we don't currently have to nor want to shoot
 */
Seat shoot (Seat left, Seat right, Graph friendliness, Role role, int outlawsDead, int mustShoot);

/**
 * Determine which player to heal
 * @param table The table of all players, beginning with the active player
 * @param friendliness The friendliness graph
 * @param playerID The role of the active player
 * @param mustHeal Whether this function call is determining if we want that die or if we are resolving that die
 * @return The player to heal, or nullptr if we don't currently have to nor want to shoot
 */
Seat heal(Seat table, Graph friendliness, int mustHeal);

#endif //CS_2413_DECISIONS_H