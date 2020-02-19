#include <iostream>
using namespace std;
#include "display.h"

void printDice(Dice *dice) {
    for (int i = 0; i < NUM_DICE; ++i) {
        switch(dice[i].value) {
            case arrow:
                print_arrow();
                break;
            case beer:
                print_beer();
                break;
            case bullseye1:
                print_bullsEye1();
                break;
            case bullseye2:
                print_bullsEye2();
                break;
            case dynamite:
                print_dynamite();
                break;
            case gatling:
                print_gatlingGun();
                break;
        }
    }
}

void print_arrow() {
    cout << " ----------" << endl;
    cout <<"|          |" << endl;
    cout <<"|          |" << endl;
    cout <<"|          |" << endl;
    cout <<"|>>>---->> |" << endl;
    cout <<"| (Arrow)  |" << endl;
    cout <<"|          |" << endl;
    cout <<"|          |" << endl;
    cout << " ----------" << endl;
}

void print_beer() {
    cout << " ----------" << endl;
    cout <<"|   ┉┉┉┉┉    |" << endl;
    cout <<"|  ┃ ||| ┃   |" << endl;
    cout <<"|  ┃ ||| ┃═╗ |" << endl;
    cout <<"|  ┃ ||| ┃ ║ |" << endl;
    cout <<"|  ┗╸┉┉┉┉┛═╝ |" << endl;
    cout <<"|   (Beer)   |" << endl;
    cout <<"|            |" << endl;
    cout << " ----------" << endl;
}

void print_dynamite() {
    cout << " ----------" << endl;
    cout <<"|     ╭--->>>" << endl;
    cout <<"|    /| /    |" << endl;
    cout <<"|   /  /     |" << endl;
    cout <<"|  /  /      |" << endl;
    cout <<"| /  /       |" << endl;
    cout <<"| ---        |" << endl;
    cout <<"|(Dynamite)  |" << endl;
    cout << " ----------" << endl;
}

void print_gatlingGun() {
    cout << " ----------" << endl;
    cout <<"|          |" << endl;
    cout <<"|          |" << endl;
    cout <<"|  ◈  ◈    |" << endl;
    cout <<"|    ◈     |" << endl;
    cout <<"|          |" << endl;
    cout <<"| (Gatling |" << endl;
    cout <<"|   Gun)   |" << endl;
    cout << " ----------" << endl;
}

void print_bullsEye1() {
    cout << " ----------" << endl;
    cout <<"|  ╭╸┿╸-╮  |" << endl;
    cout <<"|  |╭ ╮ |  |" << endl;
    cout <<"|  ┿|1| ┿  |" << endl;
    cout <<"|  |╰ ╯ |  |" << endl;
    cout <<"|  ╰╸┿ -╯  |" << endl;
    cout <<"|( Bulls   |" << endl;
    cout <<"|  Eye 1)  |" << endl;
    cout << " ----------" << endl;
}

void print_bullsEye2() {
    cout << " ----------" << endl;
    cout <<"|  ╭╸┿╸-╮  |" << endl;
    cout <<"|  |╭ ╮ |  |" << endl;
    cout <<"|  ┿|2| ┿  |" << endl;
    cout <<"|  |╰ ╯ |  |" << endl;
    cout <<"|  ╰╸┿ -╯  |" << endl;
    cout <<"|( Bulls   |" << endl;
    cout <<"|  Eye 2)  |" << endl;
    cout << " ----------" << endl;
}

void displayWinners(Player *players, int numPlayers, GameOver winCondition) {
    switch (winCondition) {
        case deputyWin: {
            cout << "All outlaws and renegades are eliminated! The sheriff and deputies win!" << endl;
            cout << "The winners are: " << endl;
            for (int i = 0; i < numPlayers; ++i) {
                if (players[i].role == sheriff || players[i].role == deputy) {
                    cout << players[i].character.name << endl;
                }
            }
            break;
        }
        case outlawWin: {
            cout << "The sheriff is dead! Outlaws win!" << endl;
            cout << "The winners are: " << endl;
            for (int i = 0; i < numPlayers; ++i) {
                if (players[i].role == outlaw) {
                    cout << players[i].character.name << endl;
                }
            }
            break;
        }
        case renegadeWin: {
            cout << "A renegade is the last one standing!" << endl;
            cout << "The winner is " << flush;
            for (int i = 0; i < numPlayers; ++i) {
                if (players[i].role == renegade && players[i].currentHP > 0) {
                    cout << players[i].character.name << "!" << endl;
                }
            }
            break;
        }
        default:
            cerr << "The game shouldn't be over. How did you end up here?" << endl;
    }
}

void displayTitle() {
    cout << " =========╮╮           //╲╲           ||╲╲          ||   ╭╭============╮╮    ^^ " << endl;
    cout << "||        ||          //  ╲╲          ||  ╲╲        ||   ||            ||    || " << endl;
    cout << "||        ||         //    ╲╲         ||   ╲╲       ||   ||            ||    || " << endl;
    cout << "||        ||        //      ╲╲        ||    ╲╲      ||   ||            ||    || " << endl;
    cout << "||        ||       //        ╲╲       ||     ╲╲     ||   ||                  || " << endl;
    cout << "|| =======╯╯      //----------╲╲      ||      ╲╲    ||   ||                  || " << endl;
    cout << "||        ╮╮     // ---------- ╲╲     ||       ╲╲   ||   ||        ╭╭===╮╮   || " << endl;
    cout << "||        ||    //              ╲╲    ||        ╲╲  ||   ||        ||   ||   || " << endl;
    cout << "||        ||   //                ╲╲   ||         ╲╲ ||   ||        ||   ||   || " << endl;
    cout << "||        ||  //                  ╲╲  ||          ╲╲||   ||        ||   ||  ╭--╮" << endl;
    cout << " =========╯╯ //                    ╲╲ ||           ╲ |   ╰╰=========    ||  ╰--╯" << endl;
    cout << endl;
    cout << "Written by Jonathon Surles, Shree Shrestha, and Anamol Acharya." << endl;
}

void displayDeath(Player *player) {
    cout << player->character.name << " has died! They were " << flush;
    switch(player->role) {
        case sheriff:
            cout << "the sheriff." << endl;
            break;
        case outlaw:
            cout << "an outlaw." << endl;
            break;
        case renegade:
            cout << "a renegade." << endl;
            break;
        case deputy:
            cout << "a deputy." << endl;
            break;
    }
}
