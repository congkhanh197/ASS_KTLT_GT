#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#define MAX_ROW 10
#define MAX_COL 20
#define MAX_NUM_OF_BOXES 4

typedef enum {END=0, LOSE=1, WIN=2} STATUS;

char map[MAX_ROW][MAX_COL + 2];
char *steps;
int numOfSteps = 0;
int numOfBoxes = 0;
int characterPosX = 0, characterPosY = 0;

int boxPosX[MAX_NUM_OF_BOXES];
int boxPosY[MAX_NUM_OF_BOXES];
int goalPosX[MAX_NUM_OF_BOXES + 1];
int goalPosY[MAX_NUM_OF_BOXES + 1];

STATUS gameStatus = END;

FILE *in, *out;

void readFiles(char *filename);
void writeStep(int posX, int posY);
void writeStatus();
void printCurrentMap(char [MAX_ROW][MAX_COL + 2]);
int getCurrentStep(char currentStep);

void moveTop();
void moveDown();
void moveLeft();
void moveRight();

int main(int argc, char* argv[])
{
    char *fileInput = "input.txt";
    char *fileOutput = "output.txt";

    /**
    ** QUAN TRONG: truoc khi submit cac ban comment out 2 dong lenh phia ben tren
    ** va uncomment 2 dong lenh phia ben duoi nhu the nay nhe:
    **      /// char *fileInput = "input.txt";
    **      /// char *fileOutput = "output.txt";
    **
    **      char *fileInput = argv[1];
    **      char *fileOutput = argv[2];
    ** Ban nao khong thuc hien thao tac nay truoc khi submit se bi 0 diem.
    **/

    /// char *fileInput = argv[1];
    /// char *fileOutput = argv[2];

    /// read file input
    readFiles(fileInput);
    numOfSteps = strlen(steps);

    /// print out the current map to the console
    printCurrentMap(map);

    /// open file output to write data
    out = fopen(fileOutput, "w");

    /// write the initial position of main character
    writeStep(characterPosX, characterPosY);

    int i;
    for (i = 0; i < numOfSteps; i++)
    {
        /// implement the body part of the program here
        /** TODO: BEGIN **/
        
        switch (steps[i])
        {
            case '^':
                printf("Buoc %c:\n",steps[i]);
                moveTop();
                break;
            case 'v':
                printf("Buoc %c:\n",steps[i]);
                moveDown();
                break;
            case '<':
                printf("Buoc %c:\n",steps[i]);
                moveLeft();
                break;
            case '>':
                printf("Buoc %c:\n",steps[i]);
                moveRight();
                break;
            default:
                break;
        }
        if (gameStatus == LOSE)
            break;

        /** TODO: END **/

        /// exit the loop when reaching WIN status
        if (gameStatus == WIN)
            break;
    }

    /// write status of the game after finishing the steps
    writeStatus();

    /// close file output
    fclose(out);

    return 0;
}

/**
* Print the current map to the console
* You may find this function helpful for debugging
**/
void printCurrentMap(char current_map[MAX_ROW][MAX_COL + 2])
{
    printf("\nCurrent Map:\n");
    int i = 0, j = 0;

    for (i = 0; i < MAX_COL + 2; i++)
    {
        printf(" -");
    }
    printf("\n");

    for (i = 0; i < MAX_ROW; i++)
    {
        printf("%d| ", (MAX_ROW - 1 - i)%10);
        for (j = 0; j < MAX_COL; j++)
        {
            printf("%c ", current_map[MAX_ROW - 1 - i][j]);
        }
        printf("|\n");
    }

    for (i = 0; i < MAX_COL + 2; i++)
    {
        printf(" -");
    }
    printf("\n");

    printf("  ");
    for (i = 0; i < MAX_COL; i++)
    {
        printf(" %d", i%10);
    }
    printf("  ");
    printf("\n");
}

/**
* Read data from file input
**/
void readFiles(char *filename)
{
    char line[200];
    int i = 0, j = 0;
    int boxIndex = 0, goalIndex = 0;
    in = fopen(filename, "r");

    if (in == NULL)
    {
        printf("Unable to open file");
        exit(0);
    }

    while (fgets(line, 200, in) != NULL)
    {
        if (i < MAX_ROW)
        {
            strcpy(map[MAX_ROW - 1 - i], line);

            for (j = 0; j < MAX_COL; j++)
            {
                if (map[MAX_ROW - 1 - i][j] == '@')
                {
                    characterPosX = j;
                    characterPosY = MAX_ROW - 1 - i;
                }
                else if (map[MAX_ROW - 1 - i][j] == 'o')
                {
                    boxPosX[boxIndex] = j;
                    boxPosY[boxIndex++] = MAX_ROW - 1 - i;
                }
                else if (map[MAX_ROW - 1 - i][j] == 'x')
                {
                    goalPosX[goalIndex] = j;
                    goalPosY[goalIndex++] = MAX_ROW - 1 - i;
                }
            }
            i++;
        }
        else
        {
            steps = malloc(sizeof(line));
            strcpy(steps, line);
        }
    }

    assert(goalIndex == boxIndex + 1);
    numOfBoxes = boxIndex;

    fclose(in);
}

/**
* Write the position to file output
**/
void writeStep(int posX, int posY)
{
    fprintf(out, "%d:%d\n", posX, posY);
}

/**
* Write final status of the game: WIN, LOSE or END
**/
void writeStatus()
{
    switch(gameStatus)
    {
        case WIN:
            fprintf(out, "WIN\n");
            break;
        case LOSE:
            fprintf(out, "LOSE\n");
            break;
        default:
            fprintf(out, "END\n");
            break;
    }
}

/// implement move function here
/** TODO: BEGIN **/

int lookupGoal(){
    int i = -1;
    for(i = 0; i < MAX_NUM_OF_BOXES + 1; i++){
        if(goalPosX[i] == characterPosX && goalPosY[i] == characterPosY){
            return i; 
        }
    }
    return -1;
}
int lookupBox(){
    int i = -1;
    for(i = 0; i < MAX_NUM_OF_BOXES; i++){
        if(boxPosX[i] == characterPosX && boxPosY[i] == characterPosY){
            return i; 
        }
    }
    return -1;
}

int abs(int a){
    return a >= 0 ? a : -a;
}
float absf(float a){
    return a >= 0 ? a : -a;
}

int checkWin(){
    int sum = 26;
    int index = -1;
    int i = 0;
    for(i = 0; i< MAX_NUM_OF_BOXES+1; i++){
        int range =((int)(absf(2*goalPosY[i]-19+goalPosX[i]+0.5)-1.5)
                            +(abs(9-(int)goalPosX[i]/2-goalPosY[i])-1));
        if((sum > range)||((sum == range) && ((goalPosX[i]+goalPosY[i])<(goalPosX[index]+goalPosY[index])))){
                index = i;
                sum = range;
        }
    }
    for(i = 0; i< MAX_NUM_OF_BOXES;i++){
        if(boxPosX[i] != 0|| boxPosY[i]!=0){
            int j = 0;
            for(j; j < MAX_NUM_OF_BOXES+1; j++){
                if(boxPosX[i] == goalPosX[j]  && boxPosY[i] == goalPosY[j]){
                    if(j == index)
                        return -1;
                    else break;
                }
            }
            if(j == MAX_NUM_OF_BOXES+1) return -1;
        }else break;
    }
    return 1;    
}
int checkLose(int x, int y){
    if(x == 0 || x == (MAX_COL-1) || y == 0 || y == (MAX_ROW-1)){
        return 1;
    }
    if(map[y-1][x] == '#'){
        if(map[y][x+1] == '#'||map[y][x-1] == '#') return 1;
    }
    if(map[y+1][x] == '#'){
        if(map[y][x+1] == '#'||map[y][x-1] == '#') return 1;
    }
    if(map[y-1][x] =='o'||map[y+1][x] =='o'||map[y][x-1] =='o'||map[y-1][x+1] =='o')
        return 1;
    return -1;
}
void moveTop()
{
    if(characterPosY != 9){
        switch (map[characterPosY+1][characterPosX]){
            case ' ':
            case 'x':
                map[characterPosY][characterPosX] = lookupGoal() == -1 ? ' ' : 'x';
                map[++characterPosY][characterPosX] = '@';
                printCurrentMap(map);
                writeStep(characterPosX,characterPosY);
                break;
            case 'o':
                if(map[characterPosY+2][characterPosX] != '#' && map[characterPosY+2][characterPosX] != 'o'){
                    map[characterPosY+2][characterPosX] = 'o';
                    map[characterPosY][characterPosX] = lookupGoal() == -1 ? ' ' : 'x';
                    map[++characterPosY][characterPosX] = '@';
                    boxPosY[lookupBox()]++;
                    printCurrentMap(map);
                    writeStep(characterPosX,characterPosY);
                    if(checkLose(characterPosX,characterPosY+1)==1) gameStatus = LOSE;
                    if(checkWin()==1) gameStatus = WIN;
                }else printf("Khong the di\n");
                break;
            default:
                printf("Khong the di\n");
                break;
        };
    }
}
void moveDown(){
    if(characterPosY != 0){
        switch (map[characterPosY-1][characterPosX]){
            case ' ':
            case 'x':
                map[characterPosY][characterPosX] = lookupGoal() == -1 ? ' ' : 'x';
                map[--characterPosY][characterPosX] = '@';
                printCurrentMap(map);
                writeStep(characterPosX,characterPosY);
                break;
            case 'o':
                if(map[characterPosY-2][characterPosX] != '#' && map[characterPosY-2][characterPosX] != 'o'){
                    map[characterPosY-2][characterPosX] = 'o';
                    map[characterPosY][characterPosX] = lookupGoal() == -1 ? ' ' : 'x';
                    map[--characterPosY][characterPosX] = '@';
                    boxPosY[lookupBox()]--;
                    printCurrentMap(map);
                    writeStep(characterPosX,characterPosY);
                    if(checkLose(characterPosX,characterPosY-1)==1) gameStatus = LOSE;
                    if(checkWin()==1) gameStatus = WIN;
                }else printf("Khong the di\n");
                break;
            default:
                printf("Khong the di\n");
                break;
        };
    }
}
void moveLeft(){
    if(characterPosX != 0){
        switch (map[characterPosY][characterPosX-1]){
            case ' ':
            case 'x':
                map[characterPosY][characterPosX] = lookupGoal() == -1 ? ' ' : 'x';
                map[characterPosY][--characterPosX] = '@';
                printCurrentMap(map);
                writeStep(characterPosX,characterPosY);
                break;
            case 'o':
                if(map[characterPosY][characterPosX-2] != '#' && map[characterPosY][characterPosX-2] != 'o'){
                    map[characterPosY][characterPosX-2] = 'o';
                    map[characterPosY][characterPosX] = lookupGoal() == -1 ? ' ' : 'x';
                    map[characterPosY][--characterPosX] = '@';
                    boxPosX[lookupBox()]--;
                    printCurrentMap(map);
                    writeStep(characterPosX,characterPosY);
                    if(checkLose(characterPosX-1,characterPosY)==1) gameStatus = LOSE;
                    if(checkWin()==1) gameStatus = WIN;
                }else printf("Khong the di\n");
                break;
            default:
                printf("Khong the di\n");
                break;
        };
    }
}
void moveRight(){
    if(characterPosX != 19){
        switch (map[characterPosY][characterPosX+1]){
            case ' ':
            case 'x':
                map[characterPosY][characterPosX] = lookupGoal() == -1 ? ' ' : 'x';
                map[characterPosY][++characterPosX] = '@';
                printCurrentMap(map);
                writeStep(characterPosX,characterPosY);
                break;
            case 'o':
                if(map[characterPosY][characterPosX+2] != '#' && map[characterPosY][characterPosX+2] != 'o'){
                    map[characterPosY][characterPosX+2] = 'o';
                    map[characterPosY][characterPosX] = lookupGoal() == -1 ? ' ' : 'x';
                    map[characterPosY][++characterPosX] = '@';
                    boxPosX[lookupBox()]++;
                    printCurrentMap(map);
                    writeStep(characterPosX,characterPosY);
                    if(checkLose(characterPosX+1,characterPosY)==1) gameStatus = LOSE;
                    if(checkWin()==1) gameStatus = WIN;
                }else printf("Khong the di\n");
                break;
            default:
                printf("Khong the di\n");
                break;
        };
    }
}

/** TODO: END **/
