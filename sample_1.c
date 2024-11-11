//Libraries
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

//Global Variables
int input;
char *PlayerName;
char *BotName;
char *SpecialAttack;
char *themeSelect;
unsigned int TotalRounds;
int playermovedeterminer;
int user=0;

//Defined Constants
#define MINHP 50
#define MAXHP 200
#define MINROUND 5
#define MAXROUND 50
#define MINENERGY 4
#define MAXENERGY 10
#define MAXDAMAGE 5+1
#define DEFENSE 3
#define MAXDEFENSE
#define HEAL 2
#define MINSPECIALDAMAGE 5
#define MAXSPECIALDAMAGE 30

//Stats
int stat[2][4] ={{1,MAXHP,0,0},{1,MAXHP,0,0}};

//Prototypes
void menu();
int verifyInputSelection(int input,int min,int max);
void displaystat();
void pickAction();
void botAction();
void gameSetup();
void coinflip();
void game();
void cleanScreen();

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
int checkEnergy();
void ApplySpecialAttack();

//Common Function
void delay(int milliseconds) {
    clock_t start_time = clock();
    while (clock() < start_time + milliseconds);
}

//Main Function

void main(){
  srand(time(NULL));

	printf("Welcome to Ultimate Showdown\n\n");
	menu();
  
}

//Functions

void menu(){
  cleanScreen();
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
  cleanScreen();
  int gameSetupFlag=1;

  do{
    chooseTheme();
    chooseMaxHP();
    chooseRounds();
    cleanScreen();

    do{
      char c_input;

      printf("Game SETUP:\nTheme: %s\nMaximum Health Points: %d\nTotal of Rounds:%d\n\nConfirm Game Setup[Y/N]",themeSelect,stat[0][1],TotalRounds);
      scanf("%c",c_input);

      if(c_input=='Y'||c_input == 'y'){
        gameSetupFlag=0;
        break;
      }else if(c_input=='N'||c_input=='n'){
        
        do{
          cleanScreen();
          printf("Which do you want to change?\n[1]Theme\\Character\n[2]Maximum Health Points\n[3]Total of Rounds\n\nChoice:");
          
          scanf("%d",input);

          if(verifyInputSelection(input,1,3)){
            cleanScreen();
            printf("\nInput out of bounds.!\n try Again\n");
          }else{
            break;
          }
        }while(1);
        
        switch(input){

          case 1:
            chooseTheme();
            break;
          case 2:
            chooseMaxHP();
            break;
          case 3:
            chooseRounds();
            break;
        }
      }

      if(c_input!='y'||c_input != 'Y'||c_input != 'n'||c_input != 'N'){
        cleanScreen();
        printf("Please Input a Valid Character!\n");
      }else{
        break;
      }
    }while(1);
    

  }while(gameSetupFlag);
  
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
  cleanScreen();
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
  printf("Game Setup\n");

  do{
    printf("Please choose a theme:\n[1]Valorant\n[2]GTA V\n[3]F1\n\nChoice:");
    scanf("%d", &input);

    if(verifyInputSelection(input,1,4)){
		  printf("Theme does not Exist\n Try Again!\n");
		}else{
		  break;
		}
  }while(1);

  switch(input){
    case 1:
      themeSelect="Valorant";
      valorant();
      delay(1000);
      break;
    case 2:
      themeSelect="GTA V";
      gtav();
      delay(1000);
      break;
    case 3:
      themeSelect="F1";
      f1();
      delay(1000);
      break;
  }
  cleanScreen();
}

void chooseMaxHP(){
  printf("Game Setup\n");
  do{
    printf("Please Enter Maximum Health Points(%dhp-%dhp)\n\nHealth Points:",MINHP,MAXHP);
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
  cleanScreen();
}

void chooseRounds(){
  printf("Game Setup\n");

  do{
    printf("Enter the number of rounds you want to play:\n");
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
  cleanScreen();
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

    printf("\n\nChoice:");
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

    printf("\n\nChoice:");
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

    printf("\n\nChoice:");
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
  printf("\n%s(you)\nHP:%d\t\tDefense Points:%d\t\tSpecial Energy:%d/5", PlayerName,stat[0][1],stat[0][2],stat[0][3]);
  printf("\n\n%s(bot)\nHP:%d\t\tDefense Points:%d", BotName,stat[1][1],stat[1][2]);
}

void pickAction(){
  user=0;
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
          int damage= attack(stat[1][2],BotName);
          stat[1][1]-= damage;
          stat[1][2]-= updatedefense(stat[1][2],damage);
          flag=1;
          break;
        }
          
        case 2:
          
          flag=1;

          break;
        case 3:
          stat[0][1] += HEAL;
          flag=1;
          break;
        case 4:{
          if(checkEnergy){
           
  			int damage;
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

  //Move Increment
  stat[0][0]+=1;

  //Special Energy Increment
  if (stat[0][3]<=MAXENERGY)
    stat[0][3]+=1;
}

void botAction(){
  user=0;
  printf("Bot's Turn");

  do{
    int flag = 0;
    int bot=(rand()%4)+1;

    switch (bot){
        case 1:{
          int damage= attack(stat[user][2],BotName);
          stat[0][1]-= damage;
          stat[0][2]-= updatedefense(stat[0][2],damage);
          flag=1;
          break;
        }
          
        case 2:
          
          flag=1;

          break;
        case 3:
          stat[0][1] += HEAL;
          flag=1;
          break;
        case 4:{
          if(checkEnergy){
            int damage=((rand()%MAXSPECIALDAMAGE+MINSPECIALDAMAGE)-stat[1][2]);
            stat[1][1]-=damage;
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
  
  //Move Increment
  stat[1][0]+=1;

  //Special Energy Increment
  if (stat[1][3]<=MAXENERGY)
    stat[1][3]+=1;

}
int attack(int defense, char *name){

    int init_damage = ((rand()%MAXDAMAGE)-defense);
    int damage =init_damage-defense;

    if(damage<defense){
      if(!user){
        printf("Your attack got blocked by %s",name);
      }else{
        printf("You blocked %s attack",name);
      }
      defense-=damage;
      return 0;
    }else{
      if(!user){
        printf("\nYou dealt %dhp damage to %s.\n\n",damage, name);
      }else{
        printf("\n %s dealt %dhp damage to you",name,damage);
      }
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
  stat[0][2] += DEFENSE;
}

int checkEnergy(){
  if(stat[0][3]<MINENERGY){
    if(!user)printf("\nYou don't have enough Energy. \n Choose another action\n");
    return 0;
  }
  return 1;
}

void cleanScreen(){
  printf("\033[H\033[J");
}
