#include <iostream>
#include "decisions.h"

using namespace std;

Seat shoot(Seat left, Seat right, Graph friendliness, Role role, int outlawsDead, int mustShoot) {
    int leftFriend, rightFriend;
    leftFriend = friendliness->matrix[left->player->id][friendliness->sheriffID];
    rightFriend = friendliness->matrix[right->player->id][friendliness->sheriffID];
    // Acting Evil
    if (role == outlaw || (role == renegade && !outlawsDead)) {
        if (leftFriend < 0 && rightFriend < 0 && !mustShoot) {
            return nullptr;
        } else {
            if (leftFriend == rightFriend) {
                return rand() % 2 ? left : right;
            }
            return leftFriend > rightFriend ? left : right;
        }
    }
    // Acting Good
    else {
        if (leftFriend > 0 && rightFriend > 0 && !mustShoot) {
            return nullptr;
        } else {
            if (leftFriend == rightFriend) {
                return rand() % 2 ? left : right;
            }
            return leftFriend < rightFriend ? left : right;
        }
    }
}

Seat heal(Seat table, Graph friendliness, int mustHeal) {
    int numPlayers = 0;
    Seat ptr = table->left;
    while (ptr != table) {
        ++numPlayers;
        ptr = ptr->left;
    }
    int healNum = rand() % numPlayers;
    Seat toHeal = table;
    for (int i = 0; i < healNum; ++i) {
        toHeal = toHeal->left;
    }
    return toHeal;
}
