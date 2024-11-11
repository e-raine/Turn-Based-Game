#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "sample_1.c"

int stat[2][4] = {{0}};
char *BotName = "TestBot";
char *SpecialAttack = "TestAttack";

int attack(int defense, char *name) {
    return 5;
}

int updatedefense(int receiver, int damage) {
    return 2;
}

int checkEnergy() {
    return 1;
}

int main() {
    return 0;
}
