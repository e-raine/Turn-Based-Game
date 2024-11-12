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

//Libraries
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h>

//Global Variables
int input, verify;
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
int stat[2][4] = {{1,MAXHP,0,0},{1,MAXHP,0,0}};


//Prototypes
void menu();                                           // [1]
int verifyInputSelection(int input,int min,int max);   // [2]
void pickAction();                                     // [4] 
void botAction();                                      // [5]
void gameSetup();                                      // [6]
void coinflip();                                       // [7]
void game();                                           // [8]
void cleanScreen();                                    // [9]
void display(int x); // [23]
void roundDisplay(int round); // [24]
void load(int x); // [25]
int verifyscanf(int x);

//GameSetup Functions
void chooseTheme();                                    // [10]
void chooseMaxHP();                                    // [11]
void chooseRounds();                                   // [12]


//Theme Selection
void valorant();                                       // [13]
void gtav();                                           // [14]
void f1();                                             // [15]

void botSelect(int size,char *CharactersName[3]);      // [16]


//Game
int attack(int defense, char *name);                   // [17] 
int updatedefense(int receiver, int damage);           // [18]
int defense();                                         // [19]
int heal();                                            // [20]
int checkEnergy();                                     // [21]
int ApplySpecialAttack();                              // [22]


//Common Function
void delay(int milliseconds) {
    clock_t start_time = clock();
    while (clock() < start_time + milliseconds);
}


//Main Function
void main()
{
    srand(time(NULL));          //Important for the Rand function

	printf("Welcome to Ultimate Showdown\n\n");
    delay(2000); //Welcome Screen
	menu();
} // end of main


//Functions
void menu()
{
    cleanScreen();
    do
    {
		printf("Ultimate Showdown \n[1]New Game\n[2]Exit Game\nChoice:");
		verify=scanf("%d", &input);

        if(verifyscanf(verify)){
            
            if(verifyInputSelection(input,1,2))
            {
                cleanScreen();
                printf("\nOption does not Exist\nTry Again!\n\n");
                delay(1000);
                cleanScreen();
            }
            else
            {
                break;
            }
        }
    }
    while(1);

	switch(input){
		case 1:
            load(input);
            gameSetup();           
            coinflip();
            game();
            break;
		case 2:
            load(input);
			break;
	}
}// end of menu

    void gameSetup()
    {                                
        cleanScreen();
        int gameSetupFlag = 1;
        
        do
        {   
            chooseTheme();
            chooseMaxHP();
            chooseRounds();

            do
            {
                char c_input;
                display(0);
                printf("Theme: %s\nCharacter:%s\nOpponent:%s\nMaximum Health Points: %d\nTotal of Rounds:%d\n\nConfirm Game Setup[Y/N]?",themeSelect,PlayerName,BotName,stat[0][1],TotalRounds);
                getchar() != '\n';         //To make sure that it won't skip to line 138;
                scanf("%c",&c_input);

                if(toupper(c_input) != 'Y'&& toupper(c_input) != 'N')
                {
                    cleanScreen();
                    printf("Please Input a Valid Character!\n\n\n");
                }
                else
                {
                    if(toupper(c_input)=='Y')
                    {
                        gameSetupFlag = 0;
                        break;
                    }
                    else if(toupper(c_input)=='N')
                    {
                        do
                        {
                            cleanScreen();
                            printf("Which do you want to change?\n[1]Theme\\Character\n[2]Maximum Health Points\n[3]Total of Rounds\n\nChoice:");
                            scanf("%d",&input);

                            if(verifyInputSelection(input,1,3))
                            {
                                cleanScreen();
                                printf("\nInput out of bounds try Again\n");
                            }
                            else
                                break;
                        }
                        while(1);
                        cleanScreen();
                        switch(input)
                        {
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
            }
            while(1);
        }
        while(gameSetupFlag);   
    } // end of gameSetup 


    void coinflip()
    {

    do
    {
        display(4);
        printf("Choose a coin side\n[1]Heads\n[2]Tails\nSide:");
        scanf("%d",&input);

        if(verifyInputSelection(input,1,2))
        {
        printf("\nPlease Select Head or Tails only.\n");
        }
        else
        {
            int coin = (rand()%2)+1;

            if(coin == input)
            {
                playermovedeterminer = 1;
                printf("\nYou get to move first.\n\n");
                delay(800);
            }
            else
            {
                playermovedeterminer = 0;
                printf("\nOpponent get to move first.\n\n");
                delay(800);
            }

            load(0);

            break;
        }
    }
    while(1);
    } // end of coinflip


    void game()
    {
        cleanScreen();

        int round = 1;
        int j = 0;
        
        do
        {
            roundDisplay(round);
            display(5);

            if(playermovedeterminer)
            {
                pickAction();
                delay(1000);
                botAction();
            }
            else
            {
                botAction();
                delay(1000);
                pickAction();
            }
            if (j > 0){
                cleanScreen();
            }
            cleanScreen();
            round++;
        }
        while(round <= TotalRounds);
    } // end of game


        void chooseTheme()
        {

            do
            {   
                display(0);
                printf("Please choose a theme:\n[1]Valorant\n[2]GTA V\n[3]F1\n\nChoice: ");
                scanf("%d", &input);

                if(verifyInputSelection(input, 1, 4))
                    printf("Theme does not Exist\n Try Again!\n");
                else
                    break;
            }
            while(1);

            switch(input)
            {
                case 1:
                    themeSelect = "Valorant";
                    valorant();
                    delay(1000);
                    break;
                case 2:
                    themeSelect = "GTA V";
                    gtav();
                    delay(1000);
                    break;
                case 3:
                    themeSelect="F1";
                    f1();
                    delay(1000);
                    break;
            }

        } // end of chooseTheme


        void chooseMaxHP()
        {
        
            do
            {
                cleanScreen();
                display(0);
                printf("Please Enter Maximum Health Points(%dhp-%dhp)\n\nHealth Points: ", MINHP, MAXHP);
                scanf("%d",&input);

                if(verifyInputSelection(input , MINHP, MAXHP))
                {
                   cleanScreen();
                    if(input < MINHP)
                        printf("\nHP is too small, input a larger amount of health points");
                    if(input > MAXHP)
                        printf("\nHP is too Big, input a smaller amount of health points");
                    delay(2000);
                }
                else
                {
                    stat[0][1] = input;
                    stat[1][1] = input;
                    TotalHP = input;

                    break;
                }
            }
            while(1);
        } // end of chooseMaxHP


        void chooseRounds()
        {

            do
            {
                cleanScreen();
                display(0);
                printf("Enter the number of rounds you want to play. \n\nChoice: ");
                scanf("%d", &input);

                if(verifyInputSelection(input, MINROUND, MAXROUND))
                {
                    if(input < MINROUND)
                        printf("You can only play a MINIMUM 5 rounds.\nTry Again");
                    if(input > MAXROUND)
                        printf("You can only play a MAXIMUM of 50 rounds.\nTry Again");
                }
                else
                {
                    TotalRounds = input;
                    break;
                }
            }
            while(1);
            cleanScreen();
        } // end of chooseRounds

            //Themes
            void valorant()
            {
                char *CharactersName []={"Jett","Phoenix","Raze","Sova","Breach","Sage","Cypher","Brimstone","Viper","Omen"};
                int CharacterSize = sizeof(CharactersName)/sizeof(CharactersName[0]);

                display(1);
                do
                {
                    
                    int i = 1;
                    for(;i <= CharacterSize; i++)
                        printf("[%d] %s\n", i ,CharactersName[i-1]);

                    printf("\nChoice:");
                    scanf("%d", &input);

                    if(verifyInputSelection(input,1,CharacterSize))
                        printf("Agent does not Exist\n Try Again!\n");
                    else
                    {
                        PlayerName = CharactersName[input-1];
                        printf("\nYou have selected %s.",PlayerName);
                        botSelect(CharacterSize,CharactersName);
                        SpecialAttack = "Ultimate";
                        break;
                    }
                }
                while(1);
            } // end of valorant


            void gtav()
            {
                char *CharactersName []={"Franklin","Michael","Trevor"};
                int CharacterSize = sizeof(CharactersName)/sizeof(CharactersName[0]);

                display(2);
                do{
                    int i=1;
                    for(;i<=CharacterSize;i++)
                        printf("[%d] %s\n",i,CharactersName[i-1]);
                    
                    printf("\n\nChoice:");
                    scanf("%d", &input);

                    if(verifyInputSelection(input,1,CharacterSize))
                        printf("Character does not Exist\n Try Again!\n");
                    else
                    {
                        PlayerName=CharactersName[input-1];
                        printf("\nYou have selected %s.",PlayerName);
                        botSelect(CharacterSize,CharactersName);
                        SpecialAttack="Special Ability";
                        break;
                    }
                }
                while(1);
            }

            void f1()
            {
                char *CharactersName []={"Max Verstrappen","Charles Leclerc","Lewis Hamilton"};
                int CharacterSize = sizeof(CharactersName)/sizeof(CharactersName[0]);

                display(3);
                do
                {

                    int i=1;
                    for(;i<=CharacterSize;i++)
                        printf("[%d] %s\n",i,CharactersName[i-1]);
                    
                    printf("\n\nChoice:");
                    scanf("%d", &input);

                    if(verifyInputSelection(input,1,10))
                        printf("Driver does not Exist\n Try Again!\n");
                    else
                    {
                        PlayerName=CharactersName[input-1];
                        printf("\nYou have selected %s.",PlayerName);
                        botSelect(CharacterSize,CharactersName);
                        SpecialAttack="DRS";
                        break;
                    }
                }
                while(1);
            }

            void botSelect(int size, char *CharactersName[])
            {
                do
                {
                    int i=rand()%size-1;
                    printf("\n\nBot Selecting a Character \n");
                    delay(1000);
                    BotName = CharactersName[i];
                    
                    if(PlayerName!=BotName)
                        break;
                }
                while(1);
                
                printf("\nThe opponent have selected %s.\n",BotName);
                load(0);
            } // botSelect

        void pickAction(int round)
        {
            user=0;
            do
            {
                int flag=0;
                printf("\nChoose and Action\n[1]Attack\t[2]Defend\t[3]Heal\t\t[4]Special Attack\nChoice:");
                scanf("%d",&input);

                if(verifyInputSelection(input,1,4))
                    printf("\nSuch action does not exist.\n Please select again.\n");
                else
                {
                    switch (input)
                    {
                        case 1:
                            flag=attack(stat[bot][dp],BotName);
                            break;
                        case 2:
                            flag=defense();
                            break;
                        case 3:
                            flag=heal();
                            break;
                        case 4:
                            if(checkEnergy()){
                                flag=ApplySpecialAttack(stat[bot][dp]);
                            }else{
                                flag=0;
                            }
                            break;
                    }
                }
                if(flag)
                break;
            }
            while(1);

            //Move Increment
            stat[player][move] += 1;

            //Special Energy Increment
            if (stat[player][energy] <= MAXENERGY)
                stat[player][energy] += 1;
        } // end pickAction


        void botAction()
        {
            user=1;
            printf("\n");
            printf("\nBot's Turn\n");

            do
            {
                int flag=0;
                input=(rand()%4)+1;

                switch (input)
                {
                    case 1:
                        flag=attack(stat[player][dp],BotName);
                        break;
                    case 2:
                        flag=defense();
                        break;          
                    case 3:
                        flag=heal();
                        break;
                    case 4:
                        if(checkEnergy())
                            flag=ApplySpecialAttack(stat[player][dp]);
                        else
                            flag=0;
                        break;
                }
                if(flag)
                break;
            }
            while(1);

            //Move Increment
            stat[bot][0]+=1;

            //Special Energy Increment
            if (stat[bot][3]<=MAXENERGY)
                stat[bot][3]+=1;
        } // end botAction


            int attack(int defense, char *name)
            {
                int init_damage = ((rand()%MAXDAMAGE)+1);

                if(DAMAGE<defense)
                {
                    if(!user)
                    {
                        printf("Your attack got blocked by %s",name);
                        stat[bot][hp]-=DAMAGE;                                     //damage to bot

                        updatedefense(bot, init_damage);
                    }
                    else
                    {
                        printf("You blocked %s attack",name);
                        stat[player][hp]-=DAMAGE;                                 //damage to player

                        updatedefense(player, init_damage);
                    }
                    
                    return 1;
                }
                else
                {
                    if(!user)
                    {
                        printf("\nYou dealt %dhp damage to %s.\n\n",DAMAGE, name);
                        stat[bot][hp]-=DAMAGE;                                    //damage to bot

                        updatedefense(bot, init_damage);
                    }
                    else
                    {
                        printf("\n %s dealt %dhp damage to you",name,DAMAGE);
                        stat[player][hp]-=DAMAGE;                                 //damage to player

                        updatedefense(player, init_damage);
                    }

                    return 1;
                }
            } // end of attack


                int updatedefense(int receiver, int damage)
                {
                    stat[receiver][dp]-=damage;                        //Reduce Defense

                    if(stat[receiver][dp] < 0)                        //ensure that defense points is not negative.
                        stat[receiver][dp] = 0;

                    return stat[receiver][dp];
                } // end of updatedefense


            int defense(){
                if(stat[user][2]<MAXDEFENSE)
                {
                    stat[user][2]+=3;

                    if (stat[user][2]>=MAXDEFENSE)
                    {
                        if(!user)
                            printf("You have maxed out your ability to Defend.\n");
                        else
                            printf("Opponent maxed out the ability to Defend.");
                            
                        stat[user][2]=MAXDEFENSE;
                        return 1;
                    }
                    else
                    {
                        if(!user)
                            printf("You can now Defend up to %dhp attacks.\n",stat[user][2]);
                        else
                            printf("Opponent increased its defense");

                        return 1;
                    }
                }
                else
                {
                    if(!user)
                        printf("\nYou have already maxed out your ability to defend.\nChoose another move.");

                    return 0;
                }
            } // end of defense

            int heal(){
                if(stat[user][1]<TotalHP)
                {
                    stat[user][1]+= HEAL;

                    if(stat[user][1]>=TotalHP){
                        if(!user)
                            printf("You healed back to Full HP.\n");
                        else
                            printf("Opponent is fully healed.\n");

                        stat[user][1]+= TotalHP;
                    }
                    else
                    {
                        if(!user)
                            printf("You gained %d from healing and now you have %dHP.", HEAL,stat[user][1]);
                        else
                            printf("Opponent healed %dhp.",HEAL);
                    }

                    return 1;
                }
                else
                {
                    if(!user)
                        printf("You are already fully healed. You Cannot Heal at the moment Choose another move.\n");

                    return 0;
                }
            } // end of heal 


            int checkEnergy()
            {
                if(stat[user][3]<MINENERGY)
                {
                    if(!user)
                        printf("\nYou don't have enough Energy. \n Choose another action.\n");
                    return 0;
                }

                return 1;
            } // end of check energy

            int ApplySpecialAttack(int defense)
            {
                if(!user)
                {//Player to Bot
                    int init_damage = ((rand()%MAXDAMAGE)+1)*stat[player][3];
                    printf("\nYour %s dealt %dhp damage to %s.\n\n",SpecialAttack,DAMAGE, BotName);
                    stat[bot][hp]-=DAMAGE;                                    //damage to bot

                    updatedefense(bot, init_damage);
                    stat[player][energy]=0;
                }
                else
                {//Bot To Player
                    int init_damage = ((rand()%MAXDAMAGE)+1)*stat[bot][3];
                    printf("\n %s's dealt %dhp damage to you",BotName,SpecialAttack,DAMAGE);
                    stat[player][hp]-=DAMAGE;                                 //damage to player

                    updatedefense(player, init_damage);
                    stat[bot][energy]=0;
                }
                
                return 1;
            }

void cleanScreen()
{
    printf("\033[H\033[J");
}

void display(int x)
{    
    if (x != 5)
    {
        cleanScreen();
        if (x == 0 || x < 4)
        {
            printf("._______________.\t\n");
            printf("|   Game Setup  |\n");
            printf("._______________.\t\n\n");
            switch (x)
            {
                case 1:
                    printf("Choose an Agent\n");
                    break;
                case 2:
                    printf("Choose a Character\n");
                    break;
                case 3:
                    printf("Choose a Driver\n");
                    break;
            }
        }
        else{
            printf("._______________.\t\n");
            printf("|   COINFLIP    |\n");
            printf("._______________.\t\n\n");
            printf("First Move will be decided by a coin flip.\n\n");
        }
    }
    else
    {
        printf("%s(you)\nHP:%d\t\tDefense Points:%d\t\tSpecial Energy:%d/5", PlayerName,stat[0][1],stat[0][2],stat[0][3]);
        printf("\n\n%s(bot)\nHP:%d\t\tDefense Points:%d", BotName,stat[1][1],stat[1][2]);
    }

}

int verifyInputSelection(int input,int min,int max)
    {
    
    if(input<min||input>max)
        return 1;
    else
        return 0;
    } // end of verifyInputSelection

void roundDisplay(int round){
    printf("\n----- Round %d -----\n", round);
}


void load(int x){       //Game load
    int i;

    if (x == 1 )
    {
        printf("\nCreating New Game");
        for(; i<3; i++)
        {
            delay(800);
            printf(".");
        } 
        return;
    }
    else if (x == 2){
        printf("\nYou have exited the game... Have a nice day (❁´◡`❁).\n\n");
        return;    
    }
    else
    {
        printf("Loading");

         for(; i<3; i++)
        {
            delay(800);
            printf(".");
        } 
        return;
    }
}

int verifyscanf(int x)
{
    if (x!=)
    {
        while (getchar() != '\n'); 
        cleanScreen()
        printf("Invalid input!\nPlease enter an integer.\n");
        delay(2000);
        return 0;
    }
    else
    {
        return 1;
    }

}