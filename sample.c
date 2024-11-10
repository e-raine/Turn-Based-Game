//Libraries

#include <stdio.h>

#include <stdlib.h>

#include <time.h>



//Global Variables

int input;

char *PlayerName;

char *BotName;

int themeSelect;

unsigned int MaxHP;

unsigned int TotalRounds;

unsigned int move;

int playermovedeterminer;

int botmovedeterminer



//Defined Constants

#define minhp 50

#define maxhp 200

#define minround 5

#define maxround 50



//Prototypes

void menu();

int verifyInputSelection(int input,int min,int max);

void gameSetup();

void coinflip();

void game();



//GameSetup Functions

void chooseTheme();

void chooseMaxHP();

void chooseRounds();



void valorant();

void gtav();

void f1();



void botSelect(int size,char *CharactersName[3]);







//Main Function

int main(){

	printf("Welcome to Ultimate Showdown\n\n");

	menu();

}



//Functions

void menu(){

	//local variable

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

  printf("First Move will be decided by a coin flip.");

   

  do{

    printf("Choose a coin side\n[1]Heads\n[2]Tails"

    scanf("%d",&input)

    if(verifyInputSelection(input,1,2)){

      printf("\nPlease Select Head or Tails only.\n");

		}else{

		  int coin = (rand()%1)+1;

		   

		  if(coin==input){

		    playermovedeterminer=1;

		    botmovedeterminer=0;

		     

		    printf("You get to move first.\n\n");

		  }else{

		    playermovedeterminer=0;

		    botmovedeterminer=1;

		     

		    printf("Opponent get to move first.\n\n");

		  }

		  break;

    }

  }while(1);

}

void game(){

  int playerstat[3]={};

  int botstat[3]={};

   

  int round = =;

  for(;round<TotalRounds;round++){

    if()

  }

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

    printf("Please Enter Maximum Health Points(%dhp-%dhp)",minhp,maxhp);

    if(verifyInputSelection(input,minhp,maxhp)){

      if(input<minhp){

        printf("HP is too small,input a larger amount of health points");

      }

      if(input>maxhp){

        printf("HP is too small,input a larger amount of health points");

      }

    }else{

      MaxHP=input;

      break;

    }

  }while(1);

}

void chooseRounds(){

  do{

    printf("Enter the number of rounds you want to play:");

     

    if(verifyInputSelection(input,minround,maxround)){

      if(input<minround){

        printf("You can only play a MINIMUM 5 rounds.\n Try Again");

      }

      if(input>maxround){

        printf("You can only play a MAXIMUM of 50 rounds.\n Try Again");

      }

    }else{

      TotalRounds=input;

      break;

    }

  }while(1);

}



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

     

    if(verifyInputSelection(input,1,10)){

		  printf("Agent does not Exist\n Try Again!\n");

		}else{

		  PlayerName=CharactersName[input-1];

		  printf("\nYou have selected %s.",PlayerName);

		  int size = sizeof(CharactersName)/sizeof(CharactersName[0]);

		  botSelect(CharacterSize,CharactersName);

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

     

    if(verifyInputSelection(input,1,10)){

		  printf("Character does not Exist\n Try Again!\n");

		}else{

		  PlayerName=CharactersName[input-1];

		  printf("\nYou have selected %s.",PlayerName);

		  int size = sizeof(CharactersName)/sizeof(CharactersName[0]);

		  botSelect(CharacterSize,CharactersName);

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

		  int size = sizeof(CharactersName)/sizeof(CharactersName[0]);

		  botSelect(CharacterSize,CharactersName);

		  break;

		}

  }while(1);

}

void botSelect(int size, char *CharactersName[]){

   

  do{

    BotName=CharactersName[(rand()%size)+1];

  }while(PlayerName==BotName);

  printf("\nThe opponent have selected %s.",BotName);

}
