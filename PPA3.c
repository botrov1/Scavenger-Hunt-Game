#include <stdio.h>
#include "MacUILib.h"
#include "myStringLib.h"   // This is your first custom C library
// [TODO] Import the required library for rand() and srand()
// [TODO] Import the required library for accessing the current time - for seeding random number generation
#include <stdlib.h>
#include <time.h>












// PREPROCESSOR DIRECTIVE CONSTANTS
// ================================
// For program-wide constants, define them here using #define.  Add as seen needed.




// [COPY AND PASTE FROM PPA2] Copy your additional preprocessor constants from PPA2 and paste them below








// [TODO] Then, define more constants here as seen needed.




















// GLOBAL VARIABLES
// ================================




int exitFlag; // Program Exiting Flag




// [COPY AND PASTE FROM PPA2] Copy your additional global from PPA2 and paste them below




char frame_array[10][20];
int cmd;
int cols=20;
int rows=10;
char input;
struct objPos
{
    int x;
    int y;
    char symbol;
};


struct objPos player;

enum FSMMode {STOP, LEFT, RIGHT, UP, DOWN};
enum FSMMode myFSMMode;
enum SPEED{VERYSLOW, SLOW, STEADY, FAST,VERYFAST};
enum SPEED mySpeed;

// [TODO] Declare More Global Variables as seen needed.

char goal_string[]="McMaster-ECE";//the mystery string
int moveCount=0;
int vector[10][20]={0};


// [TODO] Declare Global Pointers as seen needed / instructed in the manual.
//creatinga n array of to hold identical number of characters as the goal strinmg on the heap
char *char_array=NULL;
struct objPos *posptr;
 
// FUNCTION PROTOTYPES
// ================================
// Declare function prototypes here, so that we can organize the function implementation after the main function for code readability.

void Initialize(void);
void GetInput(void);
void RunLogic(void);
void DrawScreen(void);
void LoopDelay(void);
void CleanUp(void);

// [TODO] In PPA3, you will need to implement this function to generate random items on the game board
//        to set the stage for the Scavenger Hunter game.
// list[]       The pointer to the Item Bin
// listSize     The size of the Item Bin (5 by default)
// playerPos    The pointer to the Player Object, read only.
// xRange       The maximum range for x-coordinate generation (probably the x-dimension of the gameboard?)
// yRange       The maximum range for y-coordinate generation (probably the y-dimension of the gameboard?)
// str          The pointer to the start of the Goal String (to choose the random characters from)
void GenerateItems(struct objPos list[], const int listSize, const struct objPos *playerPos, const int xRange, const int yRange, const char* str);


// MAIN PROGRAM
// ===============================
int main(void)
{

    Initialize();

    while(!exitFlag)  
    {
        GetInput();

        RunLogic();

        DrawScreen();

        LoopDelay();

    }
    CleanUp();

}

// INITIALIZATION ROUTINE
// ===============================
void Initialize(void)
{
    MacUILib_init();


    MacUILib_clearScreen();


    // [COPY AND PASTE FROM PPA2] Copy your initialization routine from PPA2 and paste them below
    MacUILib_init();
    MacUILib_clearScreen();

    input = 0; // NULL
    exitFlag = 0;  // not exiting    
   
    // [TODO] : Initialize more variables here as seen needed.
    //          PARTICULARLY for the structs!!


    player.x = 9;              // Initialize x
    player.y = 4;              // Initialize y
    player.symbol = '@';
   
    myFSMMode = STOP;
    mySpeed=STEADY;

    exitFlag = 0;

    // [TODO] Allocated heap memory for on-demand variables as required.  Initialize them as required.
    int n=my_strlen(goal_string);
    char_array=(char*)malloc((n+1)*sizeof(char));


     if (char_array==NULL){
        printf("Out of memory\n");
    }


    int i;
    for(i=0;i<n;i++){
        *(char_array+i)='?';
    }
    *(char_array+n)='\0';

    posptr=(struct objPos *)malloc(5*sizeof(struct objPos));

    // [TODO] Seed the random integer generation function with current time.
    srand(time(NULL));

    // [TODO] Generate the initial random items on the game board at the start of the game.
    GenerateItems(posptr, 5, &player, cols, rows, goal_string);

}
 
// INPUT COLLECTION ROUTINE
// ===============================
void GetInput(void)
{
    if (MacUILib_hasChar()){
        input=MacUILib_getChar();
    }
    // Asynchronous Input - non blocking character read-in
   
    // Insert input collection routine 

    // [TODO]you may insert any additional logic for input processing.

}

// MAIN LOGIC ROUTINE
// ===============================
void RunLogic(void)
{
    // [COPY AND PASTE FROM PPA2] Copy your main logic routine from PPA2 and paste them below
   
    if (input != 0) {  
        //move the number of counts by 1 for
        switch (input) {
                case ' ':  
                exitFlag = 1;
                break;

            case 'w':
                if (myFSMMode != DOWN){
                    myFSMMode = UP;
                }  
                break;

            case 's':
                if (myFSMMode != UP){
                    myFSMMode = DOWN;
                }  
                   
                break;

            case 'a':
                if (myFSMMode != RIGHT){
                    myFSMMode = LEFT;
                }
                   
                break;

            case 'd':
                if (myFSMMode != LEFT){
                    myFSMMode = RIGHT;
                }  
                break;

            case ','://very slow
                mySpeed = VERYSLOW;
                break;

            case '='://very fast
                mySpeed = VERYFAST;
                break;

            case '-'://fast
                mySpeed = FAST;
                break;

            case '.'://slow
                mySpeed = SLOW;
                break;

            case '/'://steady
                mySpeed = STEADY;
                break;
            default:
                break;
        }

    input = 0;
}

switch (myFSMMode) {

    case UP:
        player.y -= 1;
        moveCount++;
        break;

    case LEFT:
        player.x -= 1;
        moveCount++;  
        break;

    case DOWN:
        player.y += 1;
        moveCount++;  
        break;

    case RIGHT:
        player.x += 1;
        moveCount++;  
        break;

    default:
        break;
}

     if (player.x <= 0) {
        player.x = cols - 2;  
    }
    else if (player.x >= cols-1) {
        player.x = 1;  
    }

    if (player.y <= 0) {
        player.y = rows - 2;
    }
    else if (player.y >= rows-1) {
        player.y = 1;
    }
    // [TODO]   Implement the Object Collision logic 
    //
    //      Simple Collision Algorithm
    //      1. Go through all items on board and check their (x,y) against the player object x and y.

        int i,j;

        for(i=0;i<5;i++)
        {
            if(posptr[i].x==player.x && posptr[i].y==player.y)
            {

                for (j=0;j<my_strlen(goal_string);j++)
                {
                    if(goal_string[j]==posptr[i].symbol && char_array[j] != posptr[i].symbol)
                    {
                        char_array[j]=posptr[i].symbol;
                    }
 
                }
                GenerateItems(posptr, 5, &player, cols, rows, goal_string);
                break;

            }


        }

       if(my_strcmp(goal_string,char_array)==1)
            {
                myFSMMode=STOP;
            }


    //      2. If a match is found, use the ASCII symbol of the collided character, and
    //         find all the occurrences of this ASCII symbol in the Goal String
    //      3. For every occurrence, reveal its ASCII character at the corresponding location in the
    //         Collected String
    //      4. Then, determine whether the game winning condition is met.




    // [TODO]   Implement Game Winning Check logic here
    //
    //      Game Winning Check Algorithm
    //      1. Check if the contents of the Collected String exactly matches that of the Goal String.
    //      2. If matched, end the game.
    //      3. Otherwise, discard the current items on the game board, and
    //         generate a new set of random items on the board.  Game continues.
   
}
// DRAW ROUTINE
// ===============================
void DrawScreen(void)
{
       
    
    MacUILib_clearScreen();
   
    int i,j;
    for (i=0;i<rows;i++){
        for (j=0;j<cols;j++){
            if(i==0||i==rows-1||j==0||j==cols-1){
                frame_array[i][j]='#';
            } else{
                frame_array[i][j]=' ';
            }
        }
    }
   
    frame_array[player.y][player.x]=player.symbol; //placing the player on the game board
    //MacUILib_printf("Item Bin:\n");
     for ( i = 0; i < 5; i++) {
     
       frame_array[posptr[i].y][posptr[i].x]=posptr[i].symbol;


       //MacUILib_printf("{%d,%d,%c} \n", posptr[i].x, posptr[i].y, posptr[i].symbol);




    }

    for (i=0;i<rows;i++){
        for (j=0;j<cols;j++){
            MacUILib_printf("%c",frame_array[i][j]);
        }
        MacUILib_printf("\n");
    }

    MacUILib_printf("PRESS ,: VERY SLOW (0.4 sec)\n");
    MacUILib_printf("PRESS .: SLOW (0.3 sec)\n");
    MacUILib_printf("PRESS /: STEADY (0.2 sec)\n");    
    MacUILib_printf("PRESS -: FAST (0.1 sec)\n");
    MacUILib_printf("PRESS =: VERY FAST (0.09 sec)\n");    

    switch (mySpeed) {


        case VERYSLOW:
        MacUILib_printf("\nCURRENT SPEED: VERY SLOW! (0.4 sec)");
            break;

        case SLOW:
            MacUILib_printf("\nCURRENT SPEED: SLOW! (0.3 sec)");
            break;

        case STEADY:
            MacUILib_printf("\nCURRENT SPEED: STEADY! (0.2 sec)"); // move up by decreasing y-coordinate
            break;

        case FAST:
            MacUILib_printf("\nCURRENT SPEED: FAST! (0.1 sec)");
            break;


        case VERYFAST:
            MacUILib_printf("\nCURRENT SPEED: VERY FAST! (0.09)");
            break;


        default:
            break;
   
}
    // [TODO]   Insert somewhere in the draw routine to draw the randomly generated items on the board.




    // [TODO]   Display the "Mystery String" contents at the bottom of the game board
    //          To help players keep track of their game progress.
   
    MacUILib_printf("\nMystery String: %s", char_array);
    MacUILib_printf("\nMove Count: %d", moveCount);
      if(my_strcmp(goal_string,char_array)==1)
            {
                MacUILib_printf("\nCongratulations! You won the game! :)");
            }
    if(exitFlag==1)
            {
                MacUILib_printf("\nYou lost the game! :(");
            }
    /*MacUILib_printf("\nPlayer: {%d,%d,%c}", player.x, player.y, player.symbol);
     for (i=0;i<5;i++){
         MacUILib_printf("\nRandomly generated coordinates: [%d , %d, %c]\n", posptr[i].x, posptr[i].y, posptr[i].symbol);
    }*/
}

// DELAY ROUTINE
// ===============================
void LoopDelay(void)
{
    MacUILib_Delay(100000); // 0.1s delay
}


// TEAR-DOWN ROUTINE
// ===============================
void CleanUp(void)
{
    // [TODO]   To prevent memory leak, free() any allocated heap memory here
    //          Based on the PPA3 requirements, you need to at least deallocate one heap variable here.
    free(char_array);
    free(posptr);
    // Insert any additional end-game actions here.


    MacUILib_uninit();
}

// The Item Generation Routine
////////////////////////////////////
void GenerateItems(struct objPos list[], const int listSize, const struct objPos *playerPos, const int xRange, const int yRange, const char* str)
{
    int count = 0;
    int count2 = 0;
    int charbitVector2[94] = {0};   
    int mychar_array[12] = {0}; 
    int taken = 1;     
    int i;
 
    while (count < listSize) {
        int x = (rand() % (xRange - 2)) + 1; 
        int y = (rand() % (yRange - 2)) + 1;  

        if (x == (*playerPos).x && y == (*playerPos).y) 
        {
            continue;
        }

        for (i = 0; i < count; i++) {
            if (list[i].x == x && list[i].y == y) 
            {
                taken = 0;
                break;
            }
        }
        taken = 1;
        if (taken) {
            list[count].x = x;
            list[count].y = y;
            count++;
        }
    }

   
    while (count2 < 2) {
        int goal_str_index = rand() % my_strlen(str);
        if (mychar_array[goal_str_index] == 0) {
            list[count2].symbol = str[goal_str_index];
            mychar_array[goal_str_index] = 1; 
            count2++;
        }
    }

    while (count2 < 5) {
        int ascii_index = (rand() % (94)) + 33;

        // Exclude certain characters (like '@' and '#')
        if (ascii_index == (int)'@' || ascii_index == (int)'#') {
            continue;
        }

        if (charbitVector2[ascii_index] == 0) {
            list[count2].symbol = (char)ascii_index;
            charbitVector2[ascii_index] = 1; 
            count2++;
        }
    }

     // Exclude space character


    //      The x and y coordinate range should fall within the xRange and yRange limits, which should be the x- and y-dimension of the board size.

   
    // This will then be a candidate of the randomly generated Item to be placed on the game board.

    // In order to make sure this candidate is validated, it needs to meet both criteria below:
    //  1. Its coordinate and symbol has not been previously generated (no repeating item)
    //  2. Its coordinate does not overlap the Player's position
    // Thus, for every generated item candidate, check whether its x-y coordinate and symbol has previously generated.  
    //  Also, check if it overlaps the player position
    //      If yes, discard this candidate and regenerate a new one
    //      If no, this candidate is validated.  Add it to the input list[]
    // There are many efficient ways to do this question


}