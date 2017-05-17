#include "../../sdk/dexsdk.h"
#include "../../sdk/time.h"

// PROTOTYPES
char mainMenu();                // displays the main menu - returns the coice of the user
char category();                // displays the window for picking the category
void enterName();            // asks the user of its name - which is utilized in the highscore panel
void highScore();            // displays the window for highscores on both categories

void evaluateCorrectAnswer();
char questionPanel(int count, char difficulty[], int color, int score, int questionCount, int limit);         // the window for each of the question
void generateRandomizedNumber(int limit);
void displayRandomizedNumber(int limit);
void chooseFileToRead(int i, char categoryChar);
void setSettingsForDifficulty(int i);
void instructionsPanel();

int mayTamaKa(int score, int increment);                // prompts the user that he/she got the correct answer
void betterLuckNextTime();    // prompts the user that he/she got the wrong answer
void wrongInput();        // displays the highscores
void quitter();     // displays the window if the user quits in the middle of the game
int gumamitNgPowerUp(int score, int increment);
void walaNaTamaNa();

int ezPanel();          // baka naman i-mali mo pa!?
int avePanel();     // kebs lang. 
int ggPanel();          // syempre hinirapan namin, ano?
void totalScorePanel();   // tapusin mo man o hindi, ija-judge ka pa rin. 
void byeUserManggagamit();    // parting is such sweet sorrow. :(

void erase();               // basically covers an area with a black rectangle

// CONSTANTS
// main menu
#define start '1'
#define high_score '2'
#define quit_game '3'
#define instruction_menu '7'

// categories
#define category1 '4'
#define category2 '5'
#define return_main_menu '6'

// number of questions per category
#define question_limit 5
#define quit 'q'
#define choice_1 'a'
#define choice_2 'b'
#define choice_3 'c'
#define choice_4 'd'
#define skip_question 's'

// questionCount
#define pkmn_ez_count 10
#define pkmn_ave_count 10
#define pkmn_dif_count 10
#define mov_ez_count 10
#define mov_ave_count 10
#define mov_dif_count 10

// scores
#define EZ_SCORE 2
#define AVE_SCORE 3
#define DIFF_SCORE 5

// colors!!!
#define BLACK 0
#define BLUE 1
#define GREEN 2
#define CYAN 3
#define RED 4
#define MAGENTA 5
#define BROWN 6
#define LIGHTGRAY 7
#define DARKGRAY 8
#define LIGHTBLUE 9
#define LIGHTGREEN 10
#define LIGHTCYAN 11
#define LIGHTRED 12
#define LIGHTMAGENTA 13
#define DARK_YELLOW 14
#define BLINK 128
#define YELLOW 54
#define PALE_YELLOW 62
#define ROYAL_BLUE 1
#define DARK_BLUE 8
#define GRAY 56
#define WHITE 63

// GLOBAL VARIABLES
char name[8], rightAnswerText[16], answer1[16], answer2[16], answer3[16], answer4[16], correctAnswer[2];
char rightAnswer, wrongAnswer1, wrongAnswer2, wrongAnswer3;
int randomNumArray[10];
int limit = 0, increment = 0, randomNumberIndex = 1, flag = 0, skipCount = 3;
FILE * fp;