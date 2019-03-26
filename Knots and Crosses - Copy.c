//inclues libraries
#include <stdio.h>
#include <stdlib.h>
//checks to see what Operating System the user is using
#ifdef _WIN32
  #include <windows.h>
  #define PLATFORM_NAME "Windows OS"
#endif
#ifdef __APPLE__
  #include <unistd.h>
  #define PLATFORM_NAME "MAC OSX"
#endif
#ifdef __linux__
  #include <unistd.h>
  #define PLATFORM_NAME "Linux OS"
#endif

//Sets up global variables such as the game board and the players
char gameBoard[9] = {'1','2','3','4','5','6','7','8','9'};
int player1 = 0;
int player2 = 0;
int cpu = 0;

//Setting up structs for the circular linked list
struct Node
{
    int data;
    struct Node *next;
};

//Creates an empty circular linked list and adds a value that has been passed int
struct Node *addToEmpty(struct Node *last, int data){
  if (last != NULL)
    return last;

  struct Node *temp =
        (struct Node*)malloc(sizeof(struct Node));

  temp -> data = data;
  last = temp;

  last -> next = last;

  return last;
}

//Adds a node to the start of the linked list if it exists
struct Node *addBegin(struct Node *last, int data)
{
  if (last == NULL)
     return addToEmpty(last, data);

  struct Node *temp
        = (struct Node *)malloc(sizeof(struct Node));

  temp -> data = data;

  temp -> next = last -> next;
  last -> next = temp;

  return last;
}

//Adds a node to the end of the linked list
struct Node *addEnd(struct Node *last, int data)
{
  if (last == NULL)
     return addToEmpty(last, data);

  // Creating a node dynamically.
  struct Node *temp =
        (struct Node *)malloc(sizeof(struct Node));

  // Assigning the data.
  temp -> data = data;

  // Adjusting the links.
  temp -> next = last -> next;
  last -> next = temp;
  last = temp;

  return last;
}

//Reverses the circular linked list which is used for replaying through
void reverse(struct Node* last)
{
    if (last == NULL)
        return;

    struct Node* prev = NULL;
    struct Node* current = last;
    struct Node* next;
    do {
        next = current->next;
        current->next = prev;
        prev = current;
        current = next;
    } while (current != (last));

    (last)->next = prev;
    last = prev;
}

//Draws the gameboard depending if its vs another player or the computer shown as cpu
void drawBoard(int cpu){
  printf("Noughts and Crosses Game :D\n");
  printf("--------------------------------\n");
  printf("\n");
  printf("\n");
  if(cpu == 1){
      printf("Player 1 (X) ------- vs ------- CPU (O)\n");
  }else{
    printf("Player 1 (X) ------- vs ------- Player 2 (O)\n");
  }
  printf("\n");

  printf("     |      |      \n");
  printf(" %c   |   %c  |   %c \n", gameBoard[0], gameBoard[1], gameBoard[2]);
  printf("_____|______|_____\n");
  printf("     |      |     \n");
  printf(" %c   |   %c  |   %c \n", gameBoard[3], gameBoard[4], gameBoard[5]);
  printf("_____|______|_____\n");
  printf("     |      |      \n");
  printf(" %c   |   %c  |   %c \n", gameBoard[6], gameBoard[7], gameBoard[8]);
  printf("     |      |      \n");
}

//draws the main menu with its options and displays what OS the user is running
void drawMainMenu(){
  printf("\n");
  printf("\t");
  printf("%s detected\n", PLATFORM_NAME);
  printf("\n");
  printf("\t");
  printf("Welcome to Noughts and Crosses Game :D\n");
  printf("\t");
  printf("Made by Chris Jones Pog\n");
  printf("\t");
  printf("--------------------------------\n");
  printf("\n");
  printf("\t");
  printf("Please choose an option\n");
  printf("\t");
  printf("____________________________\n");
  printf("\t");
  printf("|                          |\n");
  printf("\t");
  printf("| 1. Player vs Player      |\n");
  printf("\t");
  printf("|                          |\n");
  printf("\t");
  printf("|                          |\n");
  printf("\t");
  printf("| 2. Player vs CPU         |\n");
  printf("\t");
  printf("|                          |\n");
  printf("\t");
  printf("|                          |\n");
  printf("\t");
  printf("| 3. Rules and how to play |\n");
  printf("\t");
  printf("|                          |\n");
  printf("\t");
  printf("____________________________\n");
}

//This method checks to see if someone has won the game. If the game returns 1 then its a win, -1 if its still going and, 0 if its a draw
int wincheck(){
  if (gameBoard[0] == gameBoard[1] && gameBoard[1] == gameBoard[2])
    return 1;

  else if (gameBoard[3] == gameBoard[4] && gameBoard[4] == gameBoard[5])
    return 1;

  else if (gameBoard[6] == gameBoard[7] && gameBoard[7] == gameBoard[8])
    return 1;

  else if (gameBoard[0] == gameBoard[3] && gameBoard[3] == gameBoard[6])
    return 1;

  else if (gameBoard[1] == gameBoard[4] && gameBoard[4] == gameBoard[7])
    return 1;

  else if (gameBoard[2] == gameBoard[5] && gameBoard[5] == gameBoard[8])
    return 1;

  else if (gameBoard[0] == gameBoard[4] && gameBoard[4] == gameBoard[8])
    return 1;

  else if (gameBoard[2] == gameBoard[4] && gameBoard[4] == gameBoard[6])
    return 1;

  else if (gameBoard[0] != '1' && gameBoard[1] != '2' && gameBoard[2] != '3' &&
          gameBoard[3] != '4' && gameBoard[4] != '5' && gameBoard[5] != '6' &&
          gameBoard[6] != '7' && gameBoard[7] != '8' && gameBoard[8] != '9')

          return 0;
      else
          return -1;
}

//Restarts the entire game or can be used to just set the gameboard back its orignial point
void restartGame(int withMain){
  gameBoard[0] ='1';
  gameBoard[1] ='2';
  gameBoard[2] ='3';
  gameBoard[3] ='4';
  gameBoard[4] ='5';
  gameBoard[5] ='6';
  gameBoard[6] ='7';
  gameBoard[7] ='8';
  gameBoard[8] ='9';
  if(withMain == 1){
    main();
  }
}

//Was used to bug test by displaying the linked list that was passed in
void traverse(struct Node *last){
  struct Node *p;

    if (last == NULL)
    {
        return;
    }

    p = last -> next;

    do
    {

        p = p -> next;
        printf("order: %d\n", p->data);

    }
    while(p != last->next);

}

//This is used for undoing and redoing values
int undoredo(struct Node *last, int j){
  struct Node *p;
  //checks to see if the linked list is null first because that would otherwise be a problem
  if (last == NULL)
  {
      return 0;
  }
  //loops through the linked list one less times to get the value before the current value to undo
  //and will loop to the end to redo
  for (int i = 1; i < j; i++){
    last = last->next;
  }
  p = last -> next;

  //returns the int
  return p->data;

}

//this is used to write to file which will always be output.txt
void writeToFile(struct Node *last , int j){
  FILE *fp;
  //gets the file to write to and opens it
  fp = fopen("output.txt", "w+");
  last=last->next;
  for(int i = 1; i < j; i++){
    //adds all of the linked list to the file
    fprintf(fp, "%d\n", last->data);
    last=last->next;
  }
  //closes the file
  fclose(fp);
}

//this is used to read from the file which the user can pick
struct Node* readFromFile(char *userfile){
  FILE *fp;
  char line[128];
  //sets up a temp node
  struct Node *p = NULL;
  //opens the users file
  fp = fopen(userfile, "r");
  //reads in every line
  while(fgets(line, sizeof(line), fp)){
    //changes the data from a char to an int
    int changetoInt = *line - '0';
    p = addBegin(p, changetoInt);
    p = p->next;
  }
  fclose(fp);
  return p;
}

//this gets a count of how many nodes are in a circular linked list so it can be looped
int getCount(struct Node* last)
{
  struct Node* temp = last;
 int result = 0;
 if (last != NULL) {
     do {
         temp = temp->next;
         result++;
     } while (temp != last);
 }

 return result;
}

//this method is used to replay through the game after the player has won and wants to watch it back
void replayThroughGame(struct Node *last, struct Node* undo, struct Node* redo, int j, int ai, int reverseNeeded){
  //intialising variables
  int counter = 0;
  int overallGameCounter = 1;
  int undoUsed = 0;
  int redoUsed = 0;
  int prev = 0;
  int onlyForNormalGame = 0;
  char restart[30];

  //checks to see if the linked list needs to be reversed (only not used for reading from a file)
  if(reverseNeeded == 1){
    reverse(last);
  }
  //reverses undo and redo lists
  reverse(undo);
  reverse(redo);

  //loops around depending how many nodes are in the list given
    for(int i = 1; i < j+1 ; i++){
      drawBoard(ai);

    //checks to see if undo and redo are null because otherwise it crashes D:
    if(undo != NULL){
      printf("undo %d\n", undo->data);
      undoUsed = 1;
    }

    if(redo != NULL){
       printf("redo %d\n", redo->data);
       redoUsed = 1;
     }

     //This is used if only an undo is used and not a redo
     if(undoUsed == 1 && redo == 0){
       //Checks to see if the current node doesnt = the next node and the game counter doesnt = a value that has been undone by the user
       if(last->data != last->next->data && overallGameCounter != undo->data){
         //Checks to see whos turn it is
         if(counter % 2 == 0){
             //changes the value of the gameboard to either X or O (Note: Its -1 because my array starts at element 0 not 1)
             gameBoard[last->data-1] = 'X';
             printf("On turn %d: X played in square %d\n", i, last->data);
         }else{
             gameBoard[last->data-1] = 'O';
             printf("On turn %d: O played in square %d\n", i, last->data);
         }
       }else{
         if(counter % 2 == 0){
            //Does the same thing as the above however if the player did undo their move it checks to see where they placed it after
            gameBoard[last->next->data-1] = 'X';
            printf("On turn %d: X undid their last go in square %d and moved to square %d\n", i, last->data, last->next->data);
          }else{
            gameBoard[last->next->data-1] = 'O';
            printf("On turn %d: O undid their last go in square %d and moved to square %d\n", i, last->data, last->next->data);
          }
          //moves the pointer to the next node
          undo = undo->next;
          counter--;
       }
       //to make sure it doesnt try to run a normal game after doing this
       onlyForNormalGame = 1;
     }

    //checks to see if undos and redos have been used
    if(undoUsed == 1 && redoUsed == 1){
      //same as above
      if(last->data != last->next->data && overallGameCounter != undo->data){
        if(counter % 2 == 0){
            gameBoard[last->data-1] = 'X';
            printf("On turn %d: X played in square %d\n", i, last->data);
        }else{
            gameBoard[last->data-1] = 'O';
            printf("On turn %d: O played in square %d\n", i, last->data);
        }
      //checks to see if both the undo and redo lists have the same turn in them. This means the player undid and then redid their go
      }else if(undo->data == redo->data){
              if(counter % 2 == 0){
                  gameBoard[last->data-1] = 'X';
                  printf("On turn %d: X undid and redid their last go in square %d\n", i, last->data);
               }else{
                  gameBoard[last->data-1] = 'O';
                 printf("On turn %d: O undid and redid their last go in square %d\n", i, last->data);
               }
               //move all the pointers to the next node
               undo = undo->next;
               redo = redo->next;
               last = last->next;
            }else{
             //this means they undid but did not redo that go
             if(counter % 2 == 0){
                gameBoard[last->next->data-1] = 'X';
                printf("On turn %d: X undid their last go in square %d and moved to square %d\n", i, last->data, last->next->data);
              }else{
                gameBoard[last->next->data-1] = 'O';
                printf("On turn %d: O undid their last go in square %d and moved to square %d\n", i, last->data, last->next->data);
              }
              //so just move the undo pointer forward
              undo = undo->next;

            counter--;
          }
        //this is for a normal game with no undos or redos OR a read in file
        }else if(onlyForNormalGame == 0){
          //checks to see if there is a 0 in the data. This is a flag for an undo
          if(last->data == 0){
            //checks to see if the previous value = the next value after 0 this means they undid and redid their go
            if(last->next->data == prev){
              //if this is the case them we move the pointer 2 places forward because the next value is the same as the previous
              last = last->next->next;
              //same with the counter and loop
              counter+=2;
              i+=2;
            }else{
              //if the value is still 0 but the previous value doesnt = the next value then they moved when they undid
              //so we change the previous value from an int to char for the array and add it to the array
              char changetoChar = prev + '0';
              gameBoard[prev-1] = changetoChar;
              counter++;
              printf("Player undid their go\n");
              last = last->next;
              i++;
            }
          }
            //This is just for a bog standard game with nothing speical happening
            if(counter % 2 == 0){
                gameBoard[last->data-1] = 'X';
                printf("On turn %d: X played in square %d\n", i, last->data);
            }else{
                gameBoard[last->data-1] = 'O';
                printf("On turn %d: O played in square %d\n", i, last->data);
            }
          }
        //So the user can actually see wtf is happening when they replay there is a 2.5sec delay on each of the boards being drawn
        Sleep(2500);
        //sets the previous value to the current and then moves the list pointer to the next
        prev = last->data;
        last=last->next;
        counter++;
        overallGameCounter++;

    }
    //Draws the game after the replay is completed and the user can either restart or quit
    drawBoard(ai);
    printf("Wish to play again? Type restart\n");
    printf("Or type anything else to quit\n");
    scanf("%s", restart);
    if (strcmp(restart, "restart") == 0){
      printf("Player 1 (X) has %d and Player 2 (O) has %d wins\n", player1, player2);
      restartGame(1);
    }
}

//This is my highly intelligent bot that doesnt just randomly pick a value
char aiBot(int n, int num_shuffles){
  //adds the gameboard values to a temp array
  char temp[9];
  for (int i = 0; i < 9; i++) {
     temp[i] = gameBoard[i];
  }
  //randomly scrambles the temp array by a set amount of shuffles
  srand((unsigned)time(NULL));
   for (int j = 0; j < num_shuffles; j++) {
       for (int i = 0; i < n - 1; i++) {
           size_t j = i + rand() / (RAND_MAX / (n - i) + 1);
           char t = temp[j];
           temp[j] = temp[i];
           temp[i] = t;
       }
   }
   //changes X, O and, the value from the first element in the temp array into int form
   int changetoIntX = 'X' - '0';
   int changetoIntO = 'O' - '0';
   int value = temp[0] - '0';
   //if that temp value = an X or O then reshuffle because the player, the computer itself has already played there
   if(value == changetoIntX || value == changetoIntO){
     aiBot(9, 2);
   }else{
     //return element 0 :P or n if the bot has malfunctioned some how
     return temp[0];
   }
   return 'n';
}

//the main program
int main(){
  //draw the main menu
  drawMainMenu();
  int input = 0;

  //checks to see if the user is going to play player vs player or player vs cpu
  printf("\n");
  scanf("%d", &input);

  if(input == 1 || input == 2){
    //if the input is 1 then its a player, 2 is user and 3 is rules
    int ai = 0;
    if(input == 1){
      ai = 0;
    }else{
      ai = 1;
    }
    //draws the board with or without the ai title
    drawBoard(ai);

    if(ai == 0){
      printf("Player 1 (X) has %d and Player 2 (O) has %d wins\n", player1, player2);
    }else{
        printf("Player 1 (X) has %d and CPU (O) has %d wins\n", player1, cpu);
    }

    printf("\n");
    printf("Please enter in a location to start for X\n");

    //Initialzing a ton of variables and lists that are used throughtout this program
    char area[50];
    int counter = 0;
    int gameOver = 0;
    char restart[50];
    char aiValue;
    int undoredoCounter = 0;
    int overallGameCounter = 1;
    int playingFlag = 0;
    int readFlag = 0;
    struct Node *savingGameData = NULL;
    struct Node *writingTofile = NULL;
    struct Node *turnUndo = NULL;
    struct Node *turnRedo = NULL;
    struct Node *readData = NULL;

    //While the turn is below 11 because it starts on 1 then keep playing
    while(overallGameCounter < 11){
      //checks to see the user input for where they wish to play
      if(ai == 0){
        scanf("%s", area);
      }else if(counter % 2 == 0){
        scanf("%s", area);
      }

    //checks to see if the user has typed undo or u for short
    if(strcmp(area, "undo") == 0 || strcmp(area, "u") == 0){
      //Doesnt count as a turn and we dont want to write any data to the linked list so a flag is not set
      overallGameCounter--;
      playingFlag = 0;

      //if the user tries to undo on their first go then they will be told thats impossible :/
      if(counter == 0 ){
        printf("you cant undo on your first go\n");
        counter -=2;
      //if the user undos the first go then the game just restarts
      }else if (counter == 1){
        restartGame(1);
      }else{
        //else we add the turn the undo was used on to the undo list
        turnUndo = addBegin(turnUndo, overallGameCounter);

        //this is used to count how many times undo is typed in a row
        undoredoCounter++;

        //we then get the value previous turn
        int undoValue = undoredo(savingGameData, undoredoCounter);
        //change it to a char and readd it back to the board
        char changetoChar = undoValue + '0';
        gameBoard[undoValue-1] = changetoChar;

        //need to go back 2 turns
        counter -=2;

        //this list is used for writing to file and an undo is ID'd by a 0
        writingTofile = addBegin(writingTofile, 0);
        }
      }

    //checks to see if the user has typed redo or r for short
    if(strcmp(area, "redo") == 0 || strcmp(area, "r") == 0){

      overallGameCounter--;
      playingFlag = 0;
        //checks to see if anything can actually be redone
        if(undoredoCounter == 0 || counter == 0){
          printf("There is nothing to redo\n");
        }else{
            //add the turn to the redo counter like undo
            turnRedo = addBegin(turnRedo, overallGameCounter);
            int redoValue = undoredo(savingGameData, undoredoCounter);

            //redo the value to either X or O on the gameboard
            if(counter % 2 == 0){
                gameBoard[redoValue-1] = 'X';
            }else{
                gameBoard[redoValue-1] = 'O';
            }

            //save so it can be replayed or written to file
            savingGameData = addBegin(savingGameData, redoValue);
            writingTofile = addBegin(writingTofile, redoValue);
         }
    }

    //checks to see if the user has typed read, load or l for short
    if(strcmp(area, "read") == 0 || strcmp(area, "load") == 0 || strcmp(area, "l") == 0){
      //sets the gameboard back to its orignial state
      restartGame(0);

      //intializing variables
      counter = 0;
      int prev = 0;
      char read[20];
      int sizeofReadData = 0;
      playingFlag = 0;
      readFlag = 1;

      //asks the user to enter a file they wish to read from
      printf("Please enter a file name you wish to read from\n");
      scanf("%s", read);

      //gets the read data and finds out how many nodes are in the list
      readData = readFromFile(read);
      sizeofReadData = getCount(readData);

      //uses 2 loops to compare all the values from the read data and the gameboard
      for(int i = 0; i < sizeofReadData ; i++){
        for(int j = 0; j < 9; j++){
          //changes the gameboard value into a char
          char changetoChar = gameBoard[j] - '0';

          //if the read data contains a 0
          if(readData->data == 0){

            //if the next nodes data is the same as the previous then the user undid and redid their go
            if(readData->next->data == prev){

              counter--;
              if(counter % 2 == 0){
                  gameBoard[j] = 'X';
              }else{
                  gameBoard[j] = 'O';
              }

            readData = readData->next;

            i++;
            counter++;
            }else{
              //changes an int to char and adds the previous value to the game board as it is not the same
              char changetoChar = prev + '0';
              gameBoard[prev-1] = changetoChar;

              counter++;
            }
          }
          //if the current data is = to the gameboard value in the array then see whos go it is and add an X or O
          if(readData->data == changetoChar){
            if(counter % 2 == 0){
                gameBoard[j] = 'X';
            }else{
                gameBoard[j] = 'O';
            }
            counter++;
          }
        }
        //sets up the previous and moves the pointer forward
        prev = readData->data;
        readData = readData->next;
      }
      counter--;
    }

    //checks to see if the user has typed save or s for short
    if(strcmp(area, "save") == 0 || strcmp(area, "s")==0){
       //reverses the list that will be written to file
       reverse(writingTofile);

       //gets the count of how many nodes there are and writes them to file
       int count = getCount(writingTofile);
       writeToFile(writingTofile, count+1);

       playingFlag = 0;
       counter--;
     }

     //if the player is playing against the cpu and it isnt the players turn
     if(ai == 1 && counter % 2 != 0){
       //then this play will be saved so it can be replayed
       playingFlag = 1;
       //the value of the shuffle is then returned
       aiValue = aiBot(9, 4);

       //and is turned into a char and added to the gameboard
       int changetoInt = aiValue - '0';
       gameBoard[changetoInt-1] = 'O';
     }

     //change the user input into a char
     int changetoIntArea = *area - '0';

     //this checks to see if the players or cpu is trying to play in the same space as a player or cpu
     //as in it has an X or O already there
      if(gameBoard[changetoIntArea-1] == 'X' && ai == 0){
        counter--;
        printf("You cant play in the same area as Player 1 :/\n");
      }else if(gameBoard[changetoIntArea-1] == 'O'){
        counter--;
        if (ai == 0){
          printf("You cant play in the same area as Player 2 :/\n");
        }else{
            printf("You cant play in the same area as the CPU :/\n");
        }
      }else{

        //This whole segment just compares the users input to the game board and if it finds a match
        //it adds an X or O depending on whos go it is
        if(strcmp(area, "1") == 0 && gameBoard[0] == '1'){
          undoredoCounter = 0;
          playingFlag = 1;
          if(counter % 2 == 0){
              gameBoard[0] = 'X';
          }else{
              gameBoard[0] = 'O';
          }
        }


        else if(strcmp(area, "2") == 0 && gameBoard[1] == '2'){
          undoredoCounter = 0;
          playingFlag = 1;
          if(counter % 2 == 0){
              gameBoard[1] = 'X';
          }else{
              gameBoard[1] = 'O';
          }
        }

      else if(strcmp(area, "3") == 0 && gameBoard[2] == '3'){
        undoredoCounter = 0;
        playingFlag = 1;
          if(counter % 2 == 0){
              gameBoard[2] = 'X';
          }else{
              gameBoard[2] = 'O';
          }
        }

      else if(strcmp(area, "4") == 0 && gameBoard[3] == '4'){
        undoredoCounter = 0;
        playingFlag = 1;
          if(counter % 2 == 0){
              gameBoard[3] = 'X';
          }else{
              gameBoard[3] = 'O';
          }
        }

       else if(strcmp(area, "5") == 0 && gameBoard[4] == '5'){
         undoredoCounter = 0;
         playingFlag = 1;
          if(counter % 2 == 0){
              gameBoard[4] = 'X';
          }else{
              gameBoard[4] = 'O';
          }
        }

      else if(strcmp(area, "6") == 0 && gameBoard[5] == '6'){
        undoredoCounter = 0;
        playingFlag = 1;
          if(counter % 2 == 0){
              gameBoard[5] = 'X';
          }else{
              gameBoard[5] = 'O';
          }
        }

      else if(strcmp(area, "7") == 0 && gameBoard[6] == '7'){
        undoredoCounter = 0;
        playingFlag = 1;
          if(counter % 2 == 0){
              gameBoard[6] = 'X';
          }else{
              gameBoard[6] = 'O';
          }
        }

      else if(strcmp(area, "8") == 0 && gameBoard[7] == '8'){
        undoredoCounter = 0;
        playingFlag = 1;
          if(counter % 2 == 0){
              gameBoard[7] = 'X';
          }else{
              gameBoard[7] = 'O';
          }
        }

       else if(strcmp(area, "9") == 0 && gameBoard[8] == '9'){
         undoredoCounter = 0;
         playingFlag = 1;
          if(counter % 2 == 0){
              gameBoard[8] = 'X';
          }else{
              gameBoard[8] = 'O';
          }
        }

        drawBoard(ai);

        //checks to see if there is a winner
        gameOver = wincheck();

        //if there is a winner
        if(gameOver == 1){
          //get the final play of the user and add it to all the lists
          int changetoInt = *area - '0';
          savingGameData = addBegin(savingGameData, changetoInt);
          writingTofile = addBegin(writingTofile, changetoInt);
          readData = addEnd(readData, changetoInt);

          //check which player or cpu has actually won, give them some options, add 1 to their score and finally break out of the while loop
          if(counter % 2 == 0){
            printf("Player 1 (X) HAS WON :D POG IN THE CHAT\n");
            printf("Wish to play again? Type restart\n");
            printf("Or wish to watch back yor game? Type replay\n");
            printf("Or save the game?\n");
            printf("Or type anything else to quit\n");
            player1++;
            break;
          }else{
            if (ai == 0){
              printf("Player 2 (O) HAS WON :D POG IN THE CHAT\n");
            }else{
              printf("CPU (O) HAS WON :D POG IN THE CHAT\n");
            }
            printf("Wish to play again? Type restart\n");
            printf("Or wish to watch back yor game? Type replay\n");
            printf("Or save the game?\n");
            printf("Or type anything else to quit\n");

            if(ai == 0){
              player2++;
            }else{
              cpu++;
            }
            break;
          }
        }
        //if the check returns 0 then its a draw
        else if(gameOver == 0){
          //samething happens as a win but no one gets a pint
          int changetoInt = *area - '0';
          savingGameData = addBegin(savingGameData, changetoInt);
          writingTofile = addBegin(writingTofile, changetoInt);
          readData = addEnd(readData, changetoInt);

          printf("ITS A DRAW STAND DOWN\n");
          printf("Wish to play again? Type restart\n");
          printf("Or wish to watch back yor game? Type replay\n");
          printf("Or save the game?\n");
          printf("Or type anything else to quit\n");
          break;
        }

        //checks to see whos go it is and notifies the user.
        //the cpu has a 1sec delay between its go so its not too fast
        if(counter % 2 == 0){
          if(ai == 0){
            printf("Players 2 (O) GO\n");
          }else{
            printf("CPU (O) GO\n");
            Sleep(1000);
          }
        }else{
            printf("Players 1 (X) GO\n");
        }

        //if a play is actually being made (ie no undos or redos)
        if(playingFlag == 1)  {
          //checks to see if its an ai game or not and is it the player who just played? or the computer
          if (ai == 0 || counter % 2 == 0){
            //if it isnt and the player just played then we use the user input to write to the lists
            int changetoInt = *area - '0';
            savingGameData = addBegin(savingGameData, changetoInt);
            writingTofile = addBegin(writingTofile, changetoInt);
            readData = addEnd(readData, changetoInt);
          }else{
            //else if its it a cpu game and it just played we use the value it picked to write to the lists
            int changetoInt = aiValue - '0';
            savingGameData = addBegin(savingGameData, changetoInt);
            writingTofile = addBegin(writingTofile, changetoInt);
            readData = addEnd(readData, changetoInt);
          }
        }
      }
      counter++;
      overallGameCounter++;

    }

    //once out of the while loop the user gets their options which they can pick from
    scanf("%s", restart);
    //checks to see if restart has been typed
    if (strcmp(restart, "restart") == 0){
      if (ai == 0){
        printf("Player 1 (X) has %d and Player 2 (O) has %d wins\n", player1, player2);
      }else{
        printf("Player 1 (X) has %d and CPU (O) has %d wins\n", player1, cpu);
      }
      restartGame(1);
    }
    //checks to see if replay has been typed or re for short
    else if(strcmp(restart, "replay") == 0 || strcmp(restart, "re")== 0){
        restartGame(0);
        //if the game hasnt been read then it has been played we used the saving game data list
        if(readFlag == 0){
          replayThroughGame(savingGameData,turnUndo, turnRedo, overallGameCounter, ai, 1);
        }else{
          //however it the game has been read then we use that list instead
          int count = getCount(readData);
          replayThroughGame(readData, turnUndo, turnRedo, count, ai, 0);
        }
      /*
      if(strcmp(restart, "save") == 0 || strcmp(restart, "s")==0){
         reverse(writingTofile);
         int count = getCount(writingTofile);
         writeToFile(writingTofile, count+1);
       }
       */
        drawBoard(ai);
    }
  //these are the rules
  }else if(input == 3){
    int input = 0;

    printf("\n");
    printf("Rules: The rules for playing noughts and crosses are very simple.\n");
    printf("Each player takes it in turn to place their X or O into one of the\n");
    printf("empty squares in the grid by clicking on it.\n");
    printf("To win the game get three of your symbols in a line horizontally, vertically or diagonally.\n");
    printf("\n");
    printf("Type 1 to go back\n");

    //once the user has read the rules they can go back to the main menu to pick another option
    scanf("%d", &input);
    if (input == 1){
      main();
    }
  }
 return 0;

}
