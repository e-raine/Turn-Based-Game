//Libraries
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h>

//Global Variables
int input;
char *PlayerName;
char *BotName;
char *SpecialAttack;
char *themeSelect;
int TotalHP;
int TotalRounds;
int playermovedeterminer;
int user=0;
int player = 0, bot = 1;
int move = 0, hp = 1, dp = 2, energy =3;

//Defined Constants
#define MINHP 50
#define MAXHP 200
#define MINROUND 5
#define MAXROUND 50
#define MINENERGY 3
#define MAXENERGY 10
#define MAXDAMAGE 5
#define DEFENSE 3
#define MAXDEFENSE 5
#define HEAL 2
#define DAMAGE init_damage-defense

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
int attack(int defense, char *name);
int updatedefense(int receiver, int damage);
int defense();
int heal();
int checkEnergy();
int ApplySpecialAttack();

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
          cleanScreen();
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

      printf("Game SETUP:\nTheme: %s\nCharacter:%s\nOpponent:%s\nMaximum Health Points: %d\nTotal of Rounds:%d\n\nConfirm Game Setup[Y/N]",themeSelect,PlayerName,BotName,stat[0][1],TotalRounds);
      getchar() != '\n';         //To make sure that it won't skip to line 138;
      scanf("%c",&c_input);

      if(toupper(c_input) != 'Y'&& toupper(c_input) != 'N'){
        cleanScreen();
        printf("Please Input a Valid Character!\n\n\n");
      }else{

        if(toupper(c_input)=='Y'){

          gameSetupFlag=0;
          break;

        }else if(toupper(c_input)=='N'){
        
          do{
            cleanScreen();
            printf("Which do you want to change?\n[1]Theme\\Character\n[2]Maximum Health Points\n[3]Total of Rounds\n\nChoice:");
            
            scanf("%d",&input);

            if(verifyInputSelection(input,1,3)){
              cleanScreen();
              printf("\nInput out of bounds try Again\n");
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
      }


    }while(1);
  }while(gameSetupFlag);
  
}

void coinflip(){
  printf("COINFLIP\nFirst Move will be decided by a coin flip.\n");
  
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
      int i;
      printf("Loading");
        for(;i<3;i++){
          delay(800);
          printf(".");
        }
      printf("\n");
      break;
    }
    
  }while(1);
}

void game(){
  cleanScreen();
  int round = 1;
  do{
    displaystat();
    if(playermovedeterminer){
      pickAction(round);
      botAction();
    }else{
      botAction();
      pickAction();
    }
    cleanScreen();
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
      TotalHP=input;
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
  
  
  do{
    int i=rand()%size-1;
    delay(1000);
    printf("\n\nBot Selecting a Character \n");
    BotName=CharactersName[i];
    
    if(PlayerName!=BotName){
      break;
    }
  }while(1);
  
  printf("\nThe opponent have selected %s.",BotName);
}

void displaystat(){
  printf("%s(you)\nHP:%d\t\tDefense Points:%d\t\tSpecial Energy:%d/5", PlayerName,stat[0][1],stat[0][2],stat[0][3]);
  printf("\n\n%s(bot)\nHP:%d\t\tDefense Points:%d", BotName,stat[1][1],stat[1][2]);
}

void pickAction(int round){
  user=0;
  do{
    int flag=0;
    printf("\n----- Round %d -----\n", round);
    printf("\nChoose and Action\n[1]Attack\t[2]Defend\t[3]Heal\t\t[4]Special Attack\nChoice:");
    scanf("%d",&input);

    if(verifyInputSelection(input,1,4)){
      printf("\nSuch action does not exist.\n Please select again.\n");
    }else{

      switch (input){
        case 1:{
          flag=attack(stat[bot][dp],BotName);
          break;
        }
          
        case 2:{

          flag=defense();
          break;
        }
          
        case 3:{
          flag=heal();
          break;
        }
          
        case 4:{
          if(checkEnergy()){
            flag=ApplySpecialAttack(stat[bot][dp]);
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
  stat[player][move]+=1;

  //Special Energy Increment
  if (stat[player][energy]<=MAXENERGY)
    stat[player][energy]+=1;
}

void botAction(){
  user=1;
  printf("\nBot's Turn\n");

  do{
    int flag=0;
    input=(rand()%4)+1;

    switch (input){
        case 1:{
          flag=attack(stat[player][dp],BotName);
          break;
        }
          
        case 2:{

          flag=defense();
          break;
        }
          
        case 3:{
          flag=heal();
          break;
        }
          
        case 4:{
          if(checkEnergy()){
            flag=ApplySpecialAttack(stat[player][dp]);
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
  stat[bot][0]+=1;

  //Special Energy Increment
  if (stat[bot][3]<=MAXENERGY)
    stat[bot][3]+=1;

}
int attack(int defense, char *name){

    int init_damage = ((rand()%MAXDAMAGE)+1);

    if(DAMAGE<defense){
      if(!user){
        printf("Your attack got blocked by %s",name);
        stat[bot][hp]-=DAMAGE;                                     //damage to bot

        updatedefense(bot, init_damage);
      }else{
        printf("You blocked %s attack",name);
        stat[player][hp]-=DAMAGE;                                 //damage to player

        updatedefense(player, init_damage);
      }
      
      return 1;
    }else{
      if(!user){
        printf("\nYou dealt %dhp damage to %s.\n\n",DAMAGE, name);
        stat[bot][hp]-=DAMAGE;                                    //damage to bot

        updatedefense(bot, init_damage);
      }else{
        printf("\n %s dealt %dhp damage to you",name,DAMAGE);
        stat[player][hp]-=DAMAGE;                                 //damage to player

        updatedefense(player, init_damage);
      }
    return 1;
    }
 
}

int updatedefense(int receiver, int damage){
  stat[receiver][dp]-=damage;                        //Reduce Defense

  if(stat[receiver][dp] < 0) {                          //ensure that defense points is not negative.
    stat[receiver][dp] = 0;
  }

  return stat[receiver][dp];
}

int defense(){
  if(stat[user][2]<MAXDEFENSE){

    stat[user][2]+=3;

    if (stat[user][2]>=MAXDEFENSE){
        if(!user)
          printf("You have maxed out your ability to Defend.\n");
        else
          printf("Opponent maxed out the ability to Defend.");
        stat[user][2]=MAXDEFENSE;
        return 1;
      }else{
        if(!user)
          printf("You can now Defend up to %dhp attacks.\n",stat[user][2]);
        else
          printf("Opponent increased its defense");
        return 1;
      }
  }else{
    if(!user)
      printf("\nYou have already maxed out your ability to defend.\nChoose another move.");
    return 0;
  }

}

int heal(){
  if(stat[user][1]<TotalHP){
    stat[user][1]+= HEAL;

    if(stat[user][1]>=TotalHP){
      if(!user)
        printf("You healed back to Full HP.\n");
      else
        printf("Opponent is fully healed.\n");
      stat[user][1]+= TotalHP;
    }else{
      if(!user)
        printf("You gained %d from healing and now you have %dHP.", HEAL,stat[user][1]);
      else
        printf("Opponent healed %dhp.",HEAL);
    }
    return 1;
  }else{
    if(!user)
      printf("You are already fully healed. You Cannot Heal at the moment Choose another move.\n");
    return 0;
  }
}
int checkEnergy(){
  if(stat[user][3]<MINENERGY){
    if(!user)
      printf("\nYou don't have enough Energy. \n Choose another action.\n");
    return 0;
  }
  return 1;
}

int ApplySpecialAttack(int defense){
  

  if(!user){//Player to Bot
    int init_damage = ((rand()%MAXDAMAGE)+1)*stat[player][3];
    printf("\nYour %s dealt %dhp damage to %s.\n\n",SpecialAttack,DAMAGE, BotName);
    stat[bot][hp]-=DAMAGE;                                    //damage to bot

    updatedefense(bot, init_damage);
    stat[player][energy]=0;
  }else{//Bot To Player
    int init_damage = ((rand()%MAXDAMAGE)+1)*stat[bot][3];
    printf("\n %s's dealt %dhp damage to you",BotName,SpecialAttack,DAMAGE);
    stat[player][hp]-=DAMAGE;                                 //damage to player

    updatedefense(player, init_damage);
    stat[bot][energy]=0;
  }
  
  return 1;

}

void cleanScreen(){
  printf("\033[H\033[J");
}

