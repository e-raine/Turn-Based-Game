//Libraries
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

//Global Variables
int input;
char *PlayerName;
char *BotName;
char *SpecialAttack;
int themeSelect;
unsigned int TotalRounds;
int playermovedeterminer;
int userflag=0;

//Defined Constants
#define MINHP 50
#define MAXHP 200
#define MINROUND 5
#define MAXROUND 50
#define MINENERGY 4
#define MAXDAMAGE 5+1
#define DEFENSE 3
#define MAXDEFENSE
#define HEAL 2
#define MINSPECIALDAMAGE 5
#define MAXSPECIALDAMAGE 30

//Stats
int stat[2][4] ={1,MAXHP,0,0},{1,MAXHP,0,0}

//Prototypes
void menu();
int verifyInputSelection(int input,int min,int max);
void displaystat();
void pickAction();
void botAction();
void gameSetup();
void coinflip();
void game();

//GameSetup Functions
void chooseTheme();
void chooseMaxHP();
void chooseRounds();

//Theme Selection
void valorant();
void gtav();
void f1();
void botSelect(int size,char *CharactersName[3]);

//Game
int attack(int damage, char *name);
int updatedefense();
void defense();
void heal();
void checkEnergy();
void ApplySpecialAttack();

//Main Function

void main(){
  srand(time(NULL));

	printf("Welcome to Ultimate Showdown\n\n");
	menu();
  
}

//Functions

void menu(){

	do{
		printf("Ultimate Showdown \n[1]New Game\n[2]Exit Game\nChoice:");
		scanf("%d", &input);

		if(verifyInputSelection(input,1,2)){
		  printf("Option does not Exist\n Try Again!\n");
		}else{
		  break;
		}
	}while(1);

	switch(input){
		case 1:
					printf("\nCreating New Game\n\n");
					gameSetup();
					coinflip();
					game();
					break;
		case 2:
					printf("2");
					break;
	}

}

int verifyInputSelection(int input,int min,int max){

  if(input<min||input>max){
    return 1;
  }else{
    return 0;
  }

}

void gameSetup(){
  chooseTheme();
  chooseMaxHP();
  chooseRounds();
}

void coinflip(){
  printf("\nFirst Move will be decided by a coin flip.\n");
  
  do{
    printf("Choose a coin side\n[1]Heads\n[2]Tails\nSide:");
    scanf("%d",&input);
    if(verifyInputSelection(input,1,2)){
      printf("\nPlease Select Head or Tails only.\n");
		}else{
		  int coin = (rand()%2)+1;
		  if(coin==input){
		    playermovedeterminer=1;
		    printf("You get to move first.\n\n");
		  }else{
		    playermovedeterminer=0;
		    printf("\nOpponent get to move first.\n\n");
		  }
		  break;
    }
  }while(1);
}

void game(){
  int round = 1;
  do{
    printf("Round %d\n", round);
    displaystat();
    if(playermovedeterminer){
      pickAction();
      printf("Bot Move\n\n");
    }else{
      printf("Bot Move\n");
      pickAction();
    }
    round++;
  }while(round<=TotalRounds);
}

void chooseTheme(){

  do{
    printf("Please choose a theme:\n[1]Valorant\n[2]GTA V\n[3]F1\nChoice:");
    scanf("%d", &input);

    if(verifyInputSelection(input,1,4)){
		  printf("Theme does not Exist\n Try Again!\n");
		}else{
		  break;
		}
  }while(1);

  switch(input){
    case 1:
      valorant();
      break;
    case 2:
      gtav();
      break;
    case 3:
      f1();
      break;
  }
}

void chooseMaxHP(){
  do{
    printf("\n\nPlease Enter Maximum Health Points(%dhp-%dhp)\nHealth Points:",MINHP,MAXHP);
    scanf("%d",&input);

    if(verifyInputSelection(input,MINHP,MAXHP)){
      if(input<MINHP){
        printf("\nHP is too small, input a larger amount of health points");
      }
      if(input>MAXHP){
        printf("\nHP is too Big, input a smaller amount of health points");
      }
    }else{
      stat[0][1]=input;
      stat[1][1]=input;
      break;
    }
  }while(1);
}

void chooseRounds(){

  do{
    printf("\nEnter the number of rounds you want to play:");
    scanf("%d",&input);

    if(verifyInputSelection(input,MINROUND,MAXROUND)){
      if(input<MINROUND){
        printf("You can only play a MINIMUM 5 rounds.\n Try Again");
      }
      if(input>MAXROUND){
        printf("You can only play a MAXIMUM of 50 rounds.\n Try Again");
      }
    }else{
      TotalRounds=input;
      break;
    }
  }while(1);
}

//Themes
void valorant(){
  char *CharactersName []={"Jett","Phoenix","Raze","Sova","Breach","Sage","Cypher","Brimstone","Viper","Omen"};
  int CharacterSize = sizeof(CharactersName)/sizeof(CharactersName[0]);
  
  do{
    printf("\nChoose an Agent\n");
    
    int i=1;
    for(;i<=CharacterSize;i++){
      printf("[%d] %s\n",i,CharactersName[i-1]);
    }

    printf("Choice:");
    scanf("%d", &input);

    if(verifyInputSelection(input,1,CharacterSize)){
		  printf("Agent does not Exist\n Try Again!\n");
		}else{
		  PlayerName=CharactersName[input-1];
		  printf("\nYou have selected %s.",PlayerName);
		  botSelect(CharacterSize,CharactersName);
      SpecialAttack="Ultimate";
		  break;
		}
  }while(1);
}

void gtav(){
  char *CharactersName []={"Franklin","Michael","Trevor"};
  int CharacterSize = sizeof(CharactersName)/sizeof(CharactersName[0]);

  do{
    printf("\nChoose a Character\n");
    
    int i=1;
    for(;i<=CharacterSize;i++){
      printf("[%d] %s\n",i,CharactersName[i-1]);
    }

    printf("Choice:");
    scanf("%d", &input);

    if(verifyInputSelection(input,1,CharacterSize)){
		  printf("Character does not Exist\n Try Again!\n");
		}else{

		  PlayerName=CharactersName[input-1];
		  printf("\nYou have selected %s.",PlayerName);
		  botSelect(CharacterSize,CharactersName);
      SpecialAttack="Special Ability";
		  break;
		}
  }while(1);
}

void f1(){
  char *CharactersName []={"Max Verstrappen","Charles Leclerc","Lewis Hamilton"};
  int CharacterSize = sizeof(CharactersName)/sizeof(CharactersName[0]);

  do{
    printf("\nChoose a Driver\n");

    int i=1;
    for(;i<=CharacterSize;i++){
      printf("[%d] %s\n",i,CharactersName[i-1]);
    }

    printf("Choice:");
    scanf("%d", &input);

    if(verifyInputSelection(input,1,10)){
		  printf("Driver does not Exist\n Try Again!\n");
		}else{
		  PlayerName=CharactersName[input-1];
		  printf("\nYou have selected %s.",PlayerName);
		  botSelect(CharacterSize,CharactersName);
      SpecialAttack="DRS";
		  break;
		}
  }while(1);
}

void botSelect(int size, char *CharactersName[]){
  printf("\n\nBot Character Selection\n");
  
  do{
    BotName=CharactersName[rand()%size-1];
    if(PlayerName!=BotName){
      break;
    }
  }while(1);
  printf("\nThe opponent have selected %s.",BotName);
}

//Move
void playermove(){
  displaystat();

  pickAction();
}

void displaystat(){
  printf("\n%s(you)\nHP:%d\t\tArmor:%d\t\tSpecial Energy:%d/5", PlayerName,stat[0][1],stat[0][2],playerstat[0][3]);
  printf("\n\n%s(bot)\nHP:%d\t\tArmor:%d", BotName,botstat[1],botstat[2]);
}

void pickAction(){
  userflag=1;
  do{
    int flag=0;
    printf("\n\nChoose and Action\n[1]Attack\t[2]Defend\t[3]Heal\t\t[4]Special Attack\nChoice:");
    scanf("%d",&input);

    if(verifyInputSelection(input,1,4)){
      printf("\nSuch action does not exist.\n Please select again.\n");
    }else{
      printf("\nPerforming");

      switch (input){
        case 1:{
          int damage= attack(botstat[2],BotName);
          botstat[1]-= damage;
          botstat[2]-= updatedefense(botstat[2],damage);
          flag=1;
          break;
        }
          
        case 2:
          
          flag=1;

          break;
        case 3:
          playerstat[1] += HEAL;
          flag=1;
          break;
        case 4:{
          if(checkEnergy){
            int damage=((rand()%MAXSPECIALDAMAGE+MINSPECIALDAMAGE)-botstat[2]);
            botstat[1]-=damage;
            printf("You(%s) dealt %dhp damage to %s.",SpecialAttack,damage, BotName);
          }else{
            flag=0;
          }
         
          break;
        }
       
      }

    }
      if(flag)
        break;
  }while(1);
}

void botAction(){
  userflag=0;
  printf("Bot's Turn");

  do{
    int flag = 0;
    int bot=(rand()%4)+1;

    switch (bot){
        case 1:{
          int damage= attack(playerstat[2],BotName);
          playerstat[1]-= damage;
          playerstat[2]-= updatedefense(playerstat[2],damage);
          flag=1;
          break;
        }
          
        case 2:
          
          flag=1;

          break;
        case 3:
          playerstat[1] += HEAL;
          flag=1;
          break;
        case 4:{
          if(checkEnergy){
            int damage=((rand()%MAXSPECIALDAMAGE+MINSPECIALDAMAGE)-botstat[2]);
            botstat[1]-=damage;
            printf("You(%s) dealt %dhp damage to %s.",SpecialAttack,damage, BotName);
          }else{
            flag=0;
          }
         
          break;
        }
    }
      if(flag)
        break;
  }while(1);
  
  
}
int attack(int defense, char *name){

    int init_damage = ((rand()%MAXDAMAGE)-defense);
    int damage =init_damage-defense;

    if(damage<defense){
      if(userflag){
        printf("Your attack got blocked by %s",name);
      }else{
        printf("You blocked %s attack",name);
      }
      defense-=damage;
      return 0;
    }else{
      printf("\nYou dealt %dhp damage to %s.\n\n",damage, name);
    return damage;
    }
 
}

int updatedefense(int receiver, int damage){
   if(receiver>damage){
    return receiver-damage;
   }else{
    return 0;
   }
}

void defense(){
  playerstat[2] += DEFENSE;
}

void checkEnergy(){
  if(playerstat[3]<MINENERGY){
    printf("\nYou don't have enough Energy. \n Choose another action\n");
  }
}