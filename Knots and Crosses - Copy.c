#include <stdio.h>
#include <windows.h>

char gameBoard[9] = {'1','2','3','4','5','6','7','8','9'};
int player1 = 0;
int player2 = 0;
int cpu = 0;

struct Node
{
    int data;
    struct Node *next;
};

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

void deleteNode(struct Node *last, int position)
{
   if (last == NULL)
      return;

   struct Node* temp = last;

    if (position == 0)
    {
        last = temp->next;
        free(temp);
        return;
    }

    for (int i=0; temp!=NULL && i<position-1; i++)
         temp = temp->next;

    if (temp == NULL || temp->next == NULL)
         return;

    struct Node *next = temp->next->next;
    free(temp->next);  // Free memory

    temp->next = next;
}

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

void drawMainMenu(){
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

void restartGame(){
  gameBoard[0] ='1';
  gameBoard[1] ='2';
  gameBoard[2] ='3';
  gameBoard[3] ='4';
  gameBoard[4] ='5';
  gameBoard[5] ='6';
  gameBoard[6] ='7';
  gameBoard[7] ='8';
  gameBoard[8] ='9';
  main();
}

void clearGameBoard(){
  gameBoard[0] ='1';
  gameBoard[1] ='2';
  gameBoard[2] ='3';
  gameBoard[3] ='4';
  gameBoard[4] ='5';
  gameBoard[5] ='6';
  gameBoard[6] ='7';
  gameBoard[7] ='8';
  gameBoard[8] ='9';
}

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

int undoredo(struct Node *last, int j){
  struct Node *p;
  if (last == NULL)
  {
      return 0;
  }
  for (int i = 1; i < j; i++){
    last = last->next;
  }
  p = last -> next;

  return p->data;

}

void writeToFile(struct Node *last , int j){
  FILE *fp;
  fp = fopen("output.txt", "w+");
  for(int i = 1; i < j; i++){
    fprintf(fp, "%d\n", last->data);
    last=last->next;
  }
  fclose(fp);
}

struct Node* readFromFile(char *userfile){
  FILE *fp;
  char line[128];
  struct Node *p = NULL;
  fp = fopen(userfile, "r");
  while(fgets(line, sizeof(line), fp)){
    int changetoInt = *line - '0';
    p = addBegin(p, changetoInt);
    p = p->next;
  }
  fclose(fp);
  return p;
}

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

void replayThroughGame(struct Node *last, struct Node* undo, struct Node* redo, int j, int ai){
  int counter = 0;
  int overallGameCounter = 1;
  int undoUsed = 0;
  int redoUsed = 0;
  int onlyForNormalGame = 0;
  char restart[30];
    reverse(last);
    reverse(undo);
    reverse(redo);
    for(int i = 1; i < j+1 ; i++){
      drawBoard(ai);

      printf("data %d\n", last->data);
      printf("next %d\n", last->next->data);
      printf("game counter %d\n", overallGameCounter);

    if(undo != NULL){
      printf("undo %d\n", undo->data);
      undoUsed = 1;
    }

    if(redo != NULL){
       printf("redo %d\n", redo->data);
       redoUsed = 1;
     }

     if(undoUsed == 1 && redo == 0){
       if(last->data != last->next->data && overallGameCounter != undo->data){
         if(counter % 2 == 0){
             gameBoard[last->data-1] = 'X';
             printf("On turn %d: X played in square %d\n", i, last->data);
         }else{
             gameBoard[last->data-1] = 'O';
             printf("On turn %d: O played in square %d\n", i, last->data);
         }
       }else{
         if(counter % 2 == 0){
            gameBoard[last->next->data-1] = 'X';
            printf("On turn %d: X undid their last go in square %d and moved to square %d\n", i, last->data, last->next->data);
          }else{
            gameBoard[last->next->data-1] = 'O';
            printf("On turn %d: O undid their last go in square %d and moved to square %d\n", i, last->data, last->next->data);
          }
          undo = undo->next;
          counter--;
       }
       onlyForNormalGame = 1;
     }

    if(undoUsed == 1 && redoUsed == 1){
      if(last->data != last->next->data && overallGameCounter != undo->data){
        if(counter % 2 == 0){
            gameBoard[last->data-1] = 'X';
            printf("On turn %d: X played in square %d\n", i, last->data);
        }else{
            gameBoard[last->data-1] = 'O';
            printf("On turn %d: O played in square %d\n", i, last->data);
        }
      }else if(undo->data == redo->data){
              if(counter % 2 == 0){
                  gameBoard[last->data-1] = 'X';
                  printf("On turn %d: X undid and redid their last go in square %d\n", i, last->data);
               }else{
                  gameBoard[last->data-1] = 'O';
                 printf("On turn %d: O undid and redid their last go in square %d\n", i, last->data);
               }
               undo = undo->next;
               redo = redo->next;
               last = last->next;
            }else{
             if(counter % 2 == 0){
                gameBoard[last->next->data-1] = 'X';
                printf("On turn %d: X undid their last go in square %d and moved to square %d\n", i, last->data, last->next->data);
              }else{
                gameBoard[last->next->data-1] = 'O';
                printf("On turn %d: O undid their last go in square %d and moved to square %d\n", i, last->data, last->next->data);
              }
              undo = undo->next;

            counter--;
          }
        }else if(onlyForNormalGame == 0){
            if(counter % 2 == 0){
                gameBoard[last->data-1] = 'X';
                printf("On turn %d: X played in square %d\n", i, last->data);
            }else{
                gameBoard[last->data-1] = 'O';
                printf("On turn %d: O played in square %d\n", i, last->data);
            }
          }
        Sleep(2000);
        last = last->next;
        counter++;
        overallGameCounter++;

    }
    printf("Wish to play again? Type restart\n");
    printf("Or wish to watch the replay again? Type replay\n");
    printf("Or type anything else to quit\n");

    scanf("%s", restart);
    if (strcmp(restart, "restart") == 0){
      printf("Player 1 (X) has %d and Player 2 (O) has %d wins\n", player1, player2);
      restartGame();
    }else if(strcmp(restart, "replay") == 0 || strcmp(restart, "re")== 0){
        clearGameBoard();
        replayThroughGame(last, undo, redo, overallGameCounter, ai);
        drawBoard(ai);
    }
}

char aiBot(int n, int num_shuffles){
  char temp[9];
  for (int i = 0; i < 9; i++) {
     temp[i] = gameBoard[i];
  }
  srand((unsigned)time(NULL));
   for (int j = 0; j < num_shuffles; j++) {
       for (int i = 0; i < n - 1; i++) {
           size_t j = i + rand() / (RAND_MAX / (n - i) + 1);
           char t = temp[j];
           temp[j] = temp[i];
           temp[i] = t;
       }
   }
   int changetoIntX = 'X' - '0';
   int changetoIntO = 'O' - '0';
   int value = temp[0] - '0';
   printf("%c\n", temp[0]);
   if(value == changetoIntX || value == changetoIntO){
     aiBot(9, 2);
   }else{
     return temp[0];
   }
   return 'n';
}

int main(){
  drawMainMenu();
  int input = 0;
  printf("\n");
  scanf("%d", &input);
  if(input == 1 || input == 2){
    int ai = 0;
    if(input == 1){
      ai = 0;
    }else{
      ai = 1;
    }
    drawBoard(ai);
    if(ai == 0){
      printf("Player 1 (X) has %d and Player 2 (O) has %d wins\n", player1, player2);
    }else{
        printf("Player 1 (X) has %d and CPU (O) has %d wins\n", player1, cpu);
    }
    printf("\n");
    printf("Please enter in a location to start for X\n");


    char area[50];
    int counter = 0;
    int gameOver = 0;
    char restart[50];
    char aiValue;
    int undoredoCounter = 0;
    int overallGameCounter = 1;
    int playingFlag = 0;
    struct Node *savingGameData = NULL;
    struct Node *writingTofile = NULL;
    struct Node *turnUndo = NULL;
    struct Node *turnRedo = NULL;

    while(overallGameCounter < 11){
      if(ai == 0){
        scanf("%s", area);
      }else if(counter % 2 == 0){
        scanf("%s", area);
      }

    if(strcmp(area, "undo") == 0 || strcmp(area, "u") == 0)  {
      overallGameCounter--;
      playingFlag = 0;
      if(counter == 0 ){
        printf("you cant undo on your first go\n");
        counter -=2;
      }else if (counter == 1){
        restartGame();
      }else{
        turnUndo = addBegin(turnUndo, overallGameCounter);
        undoredoCounter++;
        int undoValue = undoredo(savingGameData, undoredoCounter);
        char changetoChar = undoValue + '0';
        gameBoard[undoValue-1] = changetoChar;
        counter -=2;
        printf("overallGameCounter: %d\n", overallGameCounter);
        traverse(writingTofile);
        deleteNode(writingTofile, overallGameCounter-1);
        printf("\n");
        traverse(writingTofile);
        }
      }

    if(strcmp(area, "redo") == 0 || strcmp(area, "r") == 0){
      overallGameCounter--;
      playingFlag = 0;
        if(undoredoCounter == 0 || counter == 0){
          printf("There is nothing to redo\n");
        }else{
            turnRedo = addBegin(turnRedo, overallGameCounter);
            int redoValue = undoredo(savingGameData, undoredoCounter);
            if(counter % 2 == 0){
                gameBoard[redoValue-1] = 'X';
            }else{
                gameBoard[redoValue-1] = 'O';
            }
            savingGameData = addBegin(savingGameData, redoValue);
         }
    }

    if(strcmp(area, "read") == 0){
      char read[20];
      struct Node *readData = NULL;
      int sizeofReadData = 0;
      playingFlag = 0;

      printf("Please enter a file name you wish to read from\n");
      scanf("%s", read);
      readData = readFromFile(read);
      sizeofReadData = getCount(readData);
      printf("%d", sizeofReadData);
      readData = readData->next;

      for(int i = 0; i < sizeofReadData ; i++){
        for(int j = 0; j < 9; j++){
          char changetoInt = gameBoard[j] - '0';
          if(readData->data == changetoInt){
            if(counter % 2 == 0){
                gameBoard[j] = 'X';
            }else{
                gameBoard[j] = 'O';
            }
            counter++;
          }
          printf("gameboard: %c\n", gameBoard[j]);
          printf("data: %d\n",readData->data);
        }
        readData = readData->next;
      }
      counter--;
    }

    if(strcmp(area, "save") == 0 || strcmp(area, "s")==0){
       writeToFile(writingTofile, overallGameCounter);
       playingFlag = 0;
       counter--;
     }
     printf("counter %d\n", counter);
     if(ai == 1 && counter % 2 != 0){
       playingFlag = 1;
       aiValue = aiBot(9, 4);
       printf("ai Value: %c\n", aiValue);
       int changetoInt = aiValue - '0';
       gameBoard[changetoInt-1] = 'O';
     }

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


      gameOver = wincheck();
      if(gameOver == 1){
        int changetoInt = *area - '0';
        savingGameData = addBegin(savingGameData, changetoInt);
        writingTofile = addBegin(writingTofile, changetoInt);
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
      else if(gameOver == 0){
        printf("ITS A DRAW STAND DOWN\n");
      }

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

      if(playingFlag == 1)  {
        if (ai == 0 || counter % 2 == 0){
          int changetoInt = *area - '0';
          savingGameData = addBegin(savingGameData, changetoInt);
          writingTofile = addBegin(writingTofile, changetoInt);
        }else{
          int changetoInt = aiValue - '0';
          savingGameData = addBegin(savingGameData, changetoInt);
          writingTofile = addBegin(writingTofile, changetoInt);
        }

        //traverse(savingGameData);
      }

      counter++;
      overallGameCounter++;

    }

    scanf("%s", restart);
    if (strcmp(restart, "restart") == 0){
      if (ai == 0){
        printf("Player 1 (X) has %d and Player 2 (O) has %d wins\n", player1, player2);
      }else{
        printf("Player 1 (X) has %d and CPU (O) has %d wins\n", player1, cpu);
      }
      restartGame();
    }
    else if(strcmp(restart, "replay") == 0 || strcmp(restart, "re")== 0){
        clearGameBoard();
        replayThroughGame(savingGameData,turnUndo, turnRedo, overallGameCounter, ai);
        drawBoard(ai);
    }
  }else if(input == 3){
    int input = 0;
    printf("\n");
    printf("Rules: The rules for playing noughts and crosses are very simple.\n");
    printf("Each player takes it in turn to place their X or O into one of the\n");
    printf("empty squares in the grid by clicking on it.\n");
    printf("To win the game get three of your symbols in a line horizontally, vertically or diagonally.\n");
    printf("\n");
    printf("Type 1 to go back\n");

    scanf("%d", &input);
    if (input == 1){
      main();
    }
  }
 return 0;

}
