#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define WORDS_QTY 31
#define ROWS 30
#define COLUMNS 30

typedef enum {RIGHT, LEFT, UP, DOWN, UP_RIGHT, UP_LEFT, DOWN_RIGHT, DOWN_LEFT} orientation;
    
typedef struct{
    char * word;
    int row;
    int column;
    orientation orientation;
} wordPosition;

char * orientationString(orientation orientation);
void solve(char game[ROWS][COLUMNS], char * words[WORDS_QTY], wordPosition wordPositions[WORDS_QTY]);
int checkOrientation(char game[ROWS][COLUMNS], char * word, int wordLength, int startRow, int startColumn, orientation orientation);
int getRowIncrement(orientation orientation);
int getColumnIncrement(orientation orientation);

int main(){
    char * words [WORDS_QTY] = {"ALMONDS", "APPLES", "BANANAS", "BEANS", "BLUEBERRIES", "BROCCOLI", 
    "BROWNRICE", "CARROTS", "CASHEWS", "CELERY", "CHEESE", "CHICKEN", "CORN", "CRANBERRIES", "CUCUMBERS",
    "EGGS", "LEMONS", "LETTUCE", "OATMEAL", "ORANGES", "POTATOES", "SALMON", "SPINACH", "TOFU", "TOMATOES",
    "WALNUTS", "WATER", "WATERMELON", "WHOLEGRAINS", "YOGURT", "ZUCCHINI"};

    char game[ROWS][COLUMNS] = {    "SXXDLLQTSBWNOQBQOECSBZCIBXPMSW",
                                    "ZRDYQKOCTRPBASNICJEGRIRUQXCEQC",
                                    "UBEHPMCBUOSKVVYUIIITOEAAMVLROV",
                                    "VKHBAHWLNWWQYCTORUZWCZNWBPWRXT",
                                    "NLLTMANMLNSPYTSRBKCVCIBFPYTLNM",
                                    "TROBHUMJARVPEREGKXOEOWEAMZELKN",
                                    "XENQXTCKWIELIBBLZMRDLCRKCQXMYN",
                                    "SKSFWAHUQCOQENTMHQAHIMRXDXKWIJ",
                                    "GAGVNPSCCEVUMPAZUVNDAAIQUFJXAE",
                                    "BITYSETLGULREGUCNXGQQFEFRXUTMG",
                                    "EJUTAPRLZBYSONWXHUEOTXSIQPBVQG",
                                    "APKNGHAEWTEYQDLUSCSXJKCFAYHLCS",
                                    "NPACOLRLBEVLQBFBQQVLBEGMIIHEZS",
                                    "SMNAALOBHULLPZQVSWMDQWNFBVAVYN",
                                    "CSMFLSECYSGZYYXRZAOQEKTNQYQORI",
                                    "TTWGAMHMICPBIGEDPDMQOBMOQPCVRA",
                                    "RKGEAXOERIOBXTKKXXVCGEQDXOOBPR",
                                    "VHOKQOGNWEHJAIFTDQLPGANAHTRXEG",
                                    "NSFQFOIWDSTWDFEAMNVSNZRKXANUWE",
                                    "OATMEALGFSSALIXROYESWYKLYTTPNL",
                                    "XCSVLPEVLAWEWXMMOFZTRVTRVOYTYO",
                                    "OJPXIQPENFEQCHLGQUNOCVDZWETUCH",
                                    "SBQKERZABLLJDAUWCLORCEPSQSQDAW",
                                    "EQIEBMNOEBPGSRECACORAILXHRFABL",
                                    "UXXSAALEMONSTLHUSDVASWCEWWYPLA",
                                    "WYLIBNNMGXGNQIQQBKUCKNDARYSGRF",
                                    "CHICKENLQGUDNRYKOFXXXFUELYREYV",
                                    "TPYCHHGMQZBINFICONHIXBBCQZAXZO",
                                    "PNKUVONBMJVCOZUTAPMUXSJUDNMYOR",
                                    "VPOFDLHMZZOHYGOCITBSQTSAXNXEPG"};
    
    wordPosition wordPositions[WORDS_QTY];
    solve(game, words, wordPositions);

    for(int i = 0; i<WORDS_QTY; i++){
        printf("%s:\n\tRow: %d\n\tColumn: %d\n\tOrientation: %s\n", wordPositions[i].word, wordPositions[i].row, wordPositions[i].column, orientationString(wordPositions[i].orientation));
    }
}

char * orientationString(orientation orientation){
    switch(orientation){
        case RIGHT: return "Right";
        case LEFT: return "Left";
        case UP: return "Up";
        case DOWN: return "Down";
        case UP_RIGHT: return "Up & Right";
        case UP_LEFT: return "Up & Left";
        case DOWN_RIGHT: return "Down & Right";
        case DOWN_LEFT: return "Down & Left";
        default: return NULL;
    }
}

void solve(char game[ROWS][COLUMNS], char * words[WORDS_QTY], wordPosition wordPositions[WORDS_QTY]){
    int wordPositionsIndex = 0;
    for(int wordIndex = 0; wordIndex<WORDS_QTY; wordIndex++){
        int wordFound = 0;
        for(int row = 0; row<ROWS && !wordFound; row++){
            for(int column = 0; column<COLUMNS && !wordFound; column++){
                if(game[row][column] == words[wordIndex][0]){
                    for(orientation orientation = RIGHT; orientation<=DOWN_LEFT && !wordFound; orientation++){
                        if(checkOrientation(game, words[wordIndex], strlen(words[wordIndex]), row, column, orientation)){
                            wordFound = 1;
                            wordPositions[wordPositionsIndex].word = words[wordIndex];
                            wordPositions[wordPositionsIndex].row = row;
                            wordPositions[wordPositionsIndex].column = column;
                            wordPositions[wordPositionsIndex].orientation = orientation;
                            wordPositionsIndex++;
                        }
                    }
                }
            }
        }
    }
}

int checkOrientation(char game[ROWS][COLUMNS], char * word, int wordLength, int startRow, int startColumn, orientation orientation){
    int rowIncrement = getRowIncrement(orientation);
    int columnIncrement = getColumnIncrement(orientation);

    for(int wordIndex = 0; wordIndex < wordLength; wordIndex++){
        if(wordIndex * rowIncrement + startRow >= 0 && wordIndex * rowIncrement + startRow < ROWS 
            && wordIndex * columnIncrement + startColumn >= 0 && wordIndex * columnIncrement + startColumn < COLUMNS){
            if(word[wordIndex] != game[wordIndex * rowIncrement + startRow][wordIndex * columnIncrement + startColumn]){
                return 0;
            }
        } else {
            return 0;
        }
    }
    
    return 1;
}

int getRowIncrement(orientation orientation){
    switch(orientation){
        case RIGHT: return 0;
        case LEFT: return 0;
        case UP: return -1;
        case DOWN: return 1;
        case UP_RIGHT: return -1;
        case UP_LEFT: return -1;
        case DOWN_RIGHT: return 1;
        case DOWN_LEFT: return 1;
        default: return 0;
    }
}

int getColumnIncrement(orientation orientation){
    switch(orientation){
        case RIGHT: return 1;
        case LEFT: return -1;
        case UP: return 0;
        case DOWN: return 0;
        case UP_RIGHT: return 1;
        case UP_LEFT: return -1;
        case DOWN_RIGHT: return 1;
        case DOWN_LEFT: return -1;
        default: return 0;
    }
}