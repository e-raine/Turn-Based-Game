/*
Things to remember:
Random:
    - Computer's action
    - Toss coin kung kinsa mag 1st move
    - Attack random Damage from 0 to 5

User input:
    - Max HP (50 - 200)


Game End Conditions
HP <= 0 
rounds>50
    if P_HP>B_HP


Special Attack 0 - 15;
defend reset every turn

*/

// Library 
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

//Constants
    #define ATTACK (rand() % 6)
    #define DEFEND 3
    #define HEAL 2
    #define MAX_ROUND 50

//Variables
int P_HP, B_HP, Attack;

//Arrays
P_moves[MAX_ROUND];
B_moves[MAX_ROUND];
// move[2][4] = {1,2,3,4},{"Attack","Defend","Heal",""};

//Conditions 
#define GAME_END_CHECKHP (P_HP<=0)||(B_HP<=0)
#define GAME_END_MAXRND ()
#define GAME_END ()||()



void main(){
    startup();
}

void startup(){
    printf("Welcome to Valorant Lite");

}

int coin_flip(){

}
void select_move(){
    //Diri ibutang ang mag select move || naka switch case
    

}



