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

int mayTamaKa();                // prompts the user that he/she got the correct answer
void betterLuckNextTime();    // prompts the user that he/she got the wrong answer
void wrongInput();        // displays the highscores
void quitter();     // displays the window if the user quits in the middle of the game

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
int  limit = 0, increment = 0, randomNumberIndex = 1, flag = 0;;
FILE * fp;

int main(){ 
    char keypress = start;
    char categoryChar;

	int i, j, totalScore = 0, quitting = 0;

	set_graphics(VGA_320X200X256);

	do{
        keypress = mainMenu();
        
        if(keypress == start){
            do{
                keypress = category();             
                categoryChar = keypress;

                if(keypress == category1 || keypress == category2){
                    enterName();

                    for(i = 0; i < (question_limit*3); i++){
                        // sets the settings for a certain difficulty (how many points earned if correct, resets 
                        // index for array containing non-repeating random numbers, and sets the flag used in generating
                        // the array containing non-repeating random numbers).
                        setSettingsForDifficulty(i);

                        // chooses what file to read according to category and difficulty, this also sets
                        // the question count limit on each file to be used in file 
                        chooseFileToRead(i, categoryChar);

                        // generates and array containing non-repeating, randomized number
                        // flag's use is to let the program generate the array of random numbers whenever
                        // a new level of difficulty starts
                        if(flag == 0) generateRandomizedNumber(limit); flag = 1;
                        
                        do{
                            // displays the question panel with the corresponding category and difficulty, returns the correct answer
                            if( i <= 4 ) rightAnswer = questionPanel((i+1), "Easy", BLUE, totalScore, randomNumArray[randomNumberIndex], limit);
                            else if( i <= 9 ) rightAnswer = questionPanel((i+1), "Average", GREEN, totalScore, randomNumArray[randomNumberIndex], limit);
                            else if( i <= 14 ) rightAnswer = questionPanel((i+1), "Difficult", RED, totalScore, randomNumArray[randomNumberIndex], limit);

                            // gets the input from user in the question panel
                            keypress = (char)getch();
                            erase(1,1,400,220);

                            // this determines what will be the wrongs answers after reading the correct answer on the file
                            evaluateCorrectAnswer();

                            // this evaluates if the answer is correct, wrong, or the user entered an invalid input
                            if(keypress == rightAnswer){ totalScore = mayTamaKa(totalScore, increment); randomNumberIndex++; break; }
                            else if(keypress == wrongAnswer1 || keypress == wrongAnswer2 || keypress == wrongAnswer3){ betterLuckNextTime(); randomNumberIndex++; break; }
                            else if(keypress == quit){ quitter(); quitting = 1; break; }
                            else  wrongInput();
                            
                            // if the player presses quit, terminates the progress but saves the score
                        }while(keypress != 'a' && keypress != 'b' && keypress != 'c' && keypress != 'd' && keypress != 'q');
                        if(quitting == 1) break;
                    }

                    // TODO: Write to file - highscores
                    totalScorePanel(totalScore);
                }
            }while(keypress != return_main_menu);
        }
        else if(keypress == high_score) highScore();
        else if(keypress == instruction_menu) instructionsPanel();
        else if(keypress == quit_game) byeUserManggagamit();

        // reset the integers used
        totalScore = 0;
        quitting = 0;
	} while (keypress != quit_game);

	set_graphics(VGA_TEXT80X25X16);
	clrscr();
}

// FUNCTIONS
char mainMenu(){
    erase(1,1,400,220);

    // borders
    int i = 0, j = 0;
    for (i=10;i<285;i++)write_pixel(i+10,20,PALE_YELLOW); // top
    for (i=10;i<285;i++)write_pixel(i+10,21,PALE_YELLOW); // top

    for (j=0;j<80;j++)write_pixel(10+10,j+20,PALE_YELLOW); // left
    for (j=0;j<80;j++)write_pixel(10+11,j+20,PALE_YELLOW); // left

    for (j=0;j<80;j++)write_pixel(285+10,j+20,PALE_YELLOW); // right
    for (j=0;j<80;j++)write_pixel(285+11,j+20,PALE_YELLOW); // right

    for (i=10;i<287;i++)write_pixel(i+10,100,PALE_YELLOW); // bottom
    for (i=10;i<287;i++)write_pixel(i+10,101,PALE_YELLOW); // bottom

    // title
	write_text("Quiz Bee!",120,40,WHITE,1);

	//menu options :: borders
    // for (i=30;i<120;i++)write_pixel(i,150,ROYAL_BLUE); // top
    // for (i=30;i<120;i++)write_pixel(i,151,ROYAL_BLUE); // top
    // for (j=150;j<20;j++)write_pixel(20,j,ROYAL_BLUE); // left
    // for (j=150;j<20;j++)write_pixel(21,j,ROYAL_BLUE); // right
    // for (j=130;j<20;j++)write_pixel(120+10,j+20,ROYAL_BLUE); // left
    // for (j=130;j<20;j++)write_pixel(120+11,j+20,ROYAL_BLUE); // right
    // for (i=120;i<285;i++)write_pixel(i+10,20,PALE_YELLOW); // bottom
    write_text("[1] Start",120,120,WHITE,0); 

    // for (i=190;i<120;i++)write_pixel(i,150,ROYAL_BLUE); // top
    // for (i=190;i<120;i++)write_pixel(i,151,ROYAL_BLUE); // top
    // for (j=150;j<20;j++)write_pixel(20,j,ROYAL_BLUE); // left
    // for (j=150;j<20;j++)write_pixel(21,j,ROYAL_BLUE); // right
	write_text("[2] High Score",100,140,WHITE,0);

    write_text("[3] Quit",125,160,WHITE,0);

    char keypress=(char)getch();
    erase(1,1,400,220); //erase menu
    return keypress;
}

char category(){
    erase(1,1,400,220);

    // prompt
	write_text("Choose a category",90,40,WHITE,1);

    // pick categories
	write_text("[4] Pokemon",50,100,YELLOW,0); 
	write_text("[5] Movies",50,120,CYAN,0); 
	write_text("[6] Return to main menu",50,140,WHITE,0);

    char keypress=(char)getch();
    erase(1,1,400,220); //erase menu
    return keypress;
}

// displays the question panel with the corresponding category and difficulty, returns the correct answer
// @ param: int count = determines the question count
char questionPanel(int count, char difficulty[], int color, int score, int questionCount, int limit){
    int i = 0, j = 0;

    erase(1,1,400,220);

    // tanong
	write_text("Question #",20,20,WHITE,1);

    char countToChar[2];
    sprintf(countToChar, "%ld", count);
    write_text(countToChar,120,20,WHITE,1);

    write_text("|",140,20,WHITE,1);
    write_text(difficulty,155,20,color,1);

    // yung mismong tanong
    if(fp != NULL){
        for(i = 0; i < limit; i++){
            if((i + 1) == questionCount){
                // question lines
                char line1[32];
                char line2[32];
                char line3[32];
                char line4[32];
                char line5[32];
                char line6[32];
                char line7[32];
                char line8[36];


                // reading the questions per line
                fgets(line1,32,fp);
                line1[31] = '\0';
                write_text(line1,20,50,WHITE,-1);

                fgets(line2,32,fp);
                line2[31] = '\0';
                write_text(line2,20,60,WHITE,-1);

                fgets(line3,32,fp);
                line3[31] = '\0';
                write_text(line3,20,70,WHITE,-1);

                fgets(line4,32,fp);
                line4[31] = '\0';
                write_text(line4,20,80,WHITE,-1);

                fgets(line5,32,fp);
                line5[31] = '\0';
                write_text(line5,20,90,WHITE,-1);

                fgets(line6,32,fp);
                line6[31] = '\0';
                write_text(line6,20,100,WHITE,-1);

                fgets(line7,32,fp);
                line7[31] = '\0';
                write_text(line7,20,110,WHITE,-1);

                fgets(line8,36,fp);
                line8[31] = '\0';
                write_text(line8,20,120,WHITE,-1);

                // reading the answers
                // for(j = 0; j < 4; j++){

                // }
                write_text("a.",20,140,WHITE,0); 
                fgets(answer1,16,fp);
                answer1[12] = '\0';
                write_text(answer1,40,140,WHITE,0); 

                write_text("b.",20,150,WHITE,0); 
                fgets(answer2,16,fp);
                answer2[12] = '\0';
                write_text(answer2,40,150,WHITE,0); 

                write_text("c.",170,140,WHITE,0);   
                fgets(answer3,16,fp);
                answer3[12] = '\0';
                write_text(answer3,190,140,WHITE,0);   
                
                write_text("d.",170,150,WHITE,0);   
                fgets(answer4,16,fp);
                answer4[12] = '\0';
                write_text(answer4,190,150,WHITE,0);   

                // reading the correct answer
                fgets(correctAnswer,2,fp);
                correctAnswer[1] = '\0';
                write_text(correctAnswer,210,160,RED,0);   
                write_text(name,20,160,YELLOW,0);   

                break;
            }
            else{
                // gets the question component - the question, 4 possible answers, and the correct answer
                char dummyQuestion[264];
                fgets(dummyQuestion,264,fp);
                char answerCatch[17];
                fgets(answerCatch,17,fp);
                fgets(answerCatch,17,fp);
                fgets(answerCatch,17,fp);
                fgets(answerCatch,17,fp);
                fgets(answerCatch,17,fp);
                char correctAnswerCatch[1];
                fgets(correctAnswerCatch,1,fp);   
            }
        }
        
        fclose(fp);
    }
    else{
        char line1[30] = "file reading error. file read-";
        write_text(line1,20,50,WHITE,-1);
    }

    // score
    write_text("Score:",20,170,WHITE,0);   
    char scoreToChar[2];
    sprintf(scoreToChar, "%ld", score);
    write_text(scoreToChar,80,170,YELLOW,0);   
    
    // quitting station
    write_text("[q] Quit game",165,170,GRAY,0);   

    return correctAnswer[0];
}

// this determines what will be the wrongs answers after reading the correct answer on the file
void evaluateCorrectAnswer(){
    int i = 0;
    if(rightAnswer == choice_1){
        // char line1[30] = "the answer is AAAA";
        // write_text(line1,20,50,YELLOW,0);
        // // char keypress = (char)getch();

        wrongAnswer1 = 'b';
        wrongAnswer2 = 'c';
        wrongAnswer3 = 'd';

        // rightAnswerText[0] = choice_1;
        // rightAnswerText[1] = '.';
        // rightAnswerText[2] = ' ';
        // for(i = 3; i < 16; i++){
        //     rightAnswerText[i] = answer1[i-3];
        // }
        strcpy(rightAnswerText, answer1);
    }
    else if(rightAnswer == choice_2){
        // char line1[30] = "the answer is bb";
        // write_text(line1,20,50,YELLOW,0);
        // // char keypress = (char)getch();

        wrongAnswer1 = 'a';
        wrongAnswer2 = 'c';
        wrongAnswer3 = 'd';

        // rightAnswerText[0] = choice_2;
        // rightAnswerText[1] = '.';
        // rightAnswerText[2] = ' ';
        // for(i = 3; i < 16; i++){
        //     rightAnswerText[i] = answer2[i-3];
        // }
        strcpy(rightAnswerText, answer2);
    }
    else if(rightAnswer == choice_3){
        // char line1[30] = "the answer is ccccccccc";
        // write_text(line1,20,50,YELLOW,0);
        // // char keypress = (char)getch();

        wrongAnswer1 = 'b';
        wrongAnswer2 = 'a';
        wrongAnswer3 = 'd';

        // rightAnswerText[0] = choice_3;
        // rightAnswerText[1] = '.';
        // rightAnswerText[2] = ' ';
        // for(i = 3; i < 16; i++){
        //     rightAnswerText[i] = answer3[i-3];
        // }
        strcpy(rightAnswerText, answer3);
    }
    else if(rightAnswer == choice_4){
        // char line1[30] = "the answer is d";
        // write_text(line1,20,50,YELLOW,0);
        // // char keypress = (char)getch();

        wrongAnswer1 = 'b';
        wrongAnswer2 = 'c';
        wrongAnswer3 = 'a';

        // rightAnswerText[0] = choice_4;
        // rightAnswerText[1] = '.';
        // rightAnswerText[2] = ' ';
        // for(i = 3; i < 16; i++){
        //     rightAnswerText[i] = answer4[i-3];
        // }
        strcpy(rightAnswerText, answer4);
    }
}

// sets the settings for a certain difficulty (how many points earned if correct, resets 
// index for array containing non-repeating random numbers, and sets the flag used in generating
// the array containing non-repeating random numbers).
void setSettingsForDifficulty(int i){
    if(i == 0){
        increment = ezPanel();
        flag = 0;
        randomNumberIndex = 0;
    }
    else if(i == 5){
        increment = avePanel();
        flag = 0;
        randomNumberIndex = 0;
    }
    else if(i == 10){
        increment = ggPanel();
        flag = 0;
        randomNumberIndex = 0;
    }
}

void enterName(){
    int j = 90, notFinished = 0;

    write_text("Enter Name : ",20,50,WHITE,1);
    write_text("(at most eight characters only)",20,70,WHITE,0);
    write_text("Press enter to start.",120,170,GRAY,0);

    int k = 0;

    while (notFinished != 8){
        char keypress = (char)getch();
        name[k] = keypress;
        k++;

        if(keypress == 10) break;        
        else if(keypress == 'a') write_text("A", j+=10 , 90, WHITE, 1);
        else if(keypress == 'b') write_text("B", j+=10 , 90, WHITE, 1);
        else if(keypress == 'c') write_text("C", j+=10 , 90, WHITE, 1);
        else if(keypress == 'd') write_text("D", j+=10 , 90, WHITE, 1);
        else if(keypress == 'e') write_text("E", j+=10 , 90, WHITE, 1);
        else if(keypress == 'f') write_text("F", j+=10 , 90, WHITE, 1);
        else if(keypress == 'g') write_text("G", j+=10 , 90, WHITE, 1);
        else if(keypress == 'h') write_text("H", j+=10 , 90, WHITE, 1);
        else if(keypress == 'i') write_text("I", j+=10 , 90, WHITE, 1);
        else if(keypress == 'j') write_text("J", j+=10 , 90, WHITE, 1);
        else if(keypress == 'k') write_text("K", j+=10 , 90, WHITE, 1);
        else if(keypress == 'l') write_text("L", j+=10 , 90, WHITE, 1);
        else if(keypress == 'm') write_text("M", j+=10 , 90, WHITE, 1);
        else if(keypress == 'n') write_text("N", j+=10 , 90, WHITE, 1);
        else if(keypress == 'o') write_text("O", j+=10 , 90, WHITE, 1);
        else if(keypress == 'p') write_text("P", j+=10 , 90, WHITE, 1);
        else if(keypress == 'q') write_text("Q", j+=10 , 90, WHITE, 1);
        else if(keypress == 'r') write_text("R", j+=10 , 90, WHITE, 1);
        else if(keypress == 's') write_text("S", j+=10 , 90, WHITE, 1);
        else if(keypress == 't') write_text("T", j+=10 , 90, WHITE, 1);
        else if(keypress == 'u') write_text("U", j+=10 , 90, WHITE, 1);
        else if(keypress == 'v') write_text("V", j+=10 , 90, WHITE, 1);
        else if(keypress == 'w') write_text("W", j+=10 , 90, WHITE, 1);
        else if(keypress == 'x') write_text("X", j+=10 , 90, WHITE, 1);
        else if(keypress == 'y') write_text("Y", j+=10 , 90, WHITE, 1);
        else if(keypress == 'z') write_text("Z", j+=10 , 90, WHITE, 1);

        else if(keypress == '1') write_text("1", j+=10 , 90, WHITE, 1);
        else if(keypress == '2') write_text("2", j+=10 , 90, WHITE, 1);
        else if(keypress == '3') write_text("3", j+=10 , 90, WHITE, 1);
        else if(keypress == '4') write_text("4", j+=10 , 90, WHITE, 1);
        else if(keypress == '5') write_text("5", j+=10 , 90, WHITE, 1);
        else if(keypress == '6') write_text("6", j+=10 , 90, WHITE, 1);
        else if(keypress == '7') write_text("7", j+=10 , 90, WHITE, 1);
        else if(keypress == '8') write_text("8", j+=10 , 90, WHITE, 1);
        else if(keypress == '9') write_text("9", j+=10 , 90, WHITE, 1);
        else if(keypress == '0') write_text("0", j+=10 , 90, WHITE, 1);

        notFinished++;
    }

    name[k] = '\0';
}

void generateRandomizedNumber(int limit){
	int x, index = 0, increment = 10;

	srand(time(NULL));

	while(index < limit){
		int r = rand() % limit + 1;

        // char scoreToChar[2];
        // sprintf(scoreToChar, "%ld", r);
        // write_text(scoreToChar,20 + increment,170,RED,0);   
        // increment+=10;
        // char keypress = (char)getch();

		for(x = 0;  x < index;  x++){
			if(randomNumArray[x] == r){
				break;
			}
		}
		
		if(x == index){
			randomNumArray[index++] = r;
		}
	}
}

void displayRandomizedNumber(int limit){
    int increment = 10;
    for(int i = 0; i < limit; i++){
        char scoreToChar[2];
        sprintf(scoreToChar, "%ld", randomNumArray[i]);
        write_text(scoreToChar,20 + increment,170,YELLOW,0);   
        increment+=10;
        char keypress = (char)getch();
    }
}

// chooses what file to read according to category and difficulty, this also sets
// the question count limit on each file to be used in file reading 
void chooseFileToRead(int i, char categoryChar){
    if(i <= 4 && categoryChar == category1){
        fp = fopen("pez.txt", "r");
        limit = pkmn_ez_count;
    }
    else if(i <= 9 && categoryChar == category1){
        fp = fopen("pave.txt", "r");
        limit = pkmn_ave_count;
    }
    else if(i <= 14 && categoryChar == category1){
        fp = fopen("pdif.txt", "r");
        limit = pkmn_dif_count;
    }
    else if(i <= 4 && categoryChar == category2){
        fp = fopen("mez.txt", "r");
        limit = mov_ez_count;
    }
    else if(i <= 9 && categoryChar == category2){
        fp = fopen("mave.txt", "r");
        limit = mov_ave_count;
    }
    else if(i <= 14 && categoryChar == category2){
        fp = fopen("mdif.txt", "r");
        limit = mov_dif_count;
    }
}

void highScore(){   
    char line[30][35];
    int linebreak = 20, skip;
    int i,j;

    // mainMenu
    // drawRectangle(0,0,320,220, GRAY);
    strcpy(line[0], "HIGH SCORES");

    // category 1
    strcpy(line[1], "Pokemon Category");
    // top 5
    strcpy(line[2], "Player 1");
    strcpy(line[3], "Player 2");
    strcpy(line[4], "Player 3");
    strcpy(line[5], "Player 4");
    strcpy(line[6], "Player 5");


    // category 2
    strcpy(line[7], "Movie Category");
    // top 5
    strcpy(line[8], "Player 1");
    strcpy(line[9], "Player 2");
    strcpy(line[10], "Player 3");
    strcpy(line[11], "Player 4");
    strcpy(line[12], "Player 5");
    //return option
    strcpy(line[13], "[Press any key to return]");
    
    write_text(line[0], 115, 20, PALE_YELLOW, 1);   //display high scores

    write_text(line[1], 20, 45, BLACK, 0);       //display category title (Pokemon)
    for(i=2; i<=6; i++){                         //display players
        write_text(line[i], 25, 50+linebreak, WHITE, -1);
        linebreak+=20;
    }

    linebreak = 20, skip;
    write_text(line[7], 175, 45, BLACK, 0);     //display category title (Movie)
    for(j=8; j<=12; j++){                       //display players
        write_text(line[j], 180, 50+linebreak, WHITE, -1);
        linebreak+=20;
    }

    write_text(line[13], 40, 180, CYAN, 0);     //display return option  
    char stop = (char)getch();  
}

void wrongInput(){
    erase(1,1,400,220); //erase menu

    write_text("Ayusin ang input :(",80,80,GRAY,1);
    write_text("a, b, c, d, or q",90,100,WHITE,0);
    write_text("lang ang choices.",90,110,WHITE,0);
    
    write_text("Press any key to continue...",35,150,GRAY,0);
    char stop = (char)getch();  
}

// displays the instructions on how the game works.
void instructionsPanel(){
    
}

int mayTamaKa(int score, int increment){
    erase(1,1,400,220); //erase menu

    write_text("Correct!!!",120,80,YELLOW,1);
    write_text("You have earned",40,100,WHITE,0);
    
    char scoreToChar[2];
    sprintf(scoreToChar, "%ld", increment);
    write_text(scoreToChar,190,100,WHITE,0);

    write_text("points.",220,100,WHITE,0);
    
    write_text("Press any key to continue...",35,150,GRAY,0);
    char stop = (char)getch();
    return score + increment;
}

void betterLuckNextTime(){
    erase(1,1,400,220); //erase menu

    write_text("Wrong!!!",120,80,RED,1);
    write_text("The correct answer is",70,100,WHITE,0);

    write_text(correctAnswer,120,110,WHITE,0);
    write_text(". ",130,110,WHITE,0);
    write_text(rightAnswerText,150,110,WHITE,0);

    write_text("Press any key to continue...",35,150,GRAY,0);
    char stop = (char)getch();
}

void quitter(){
    erase(1,1,400,220); //erase menu

    write_text("Quitter!",120,50,RED,1);
    write_text("BOO!!!",130,70,WHITE,0);
    write_text("You have ended your session.",35,100,WHITE,0);
    write_text("Your score will be saved.",40,110,WHITE,0);

    write_text("Press any key to continue...",35,150,GRAY,0);
    char stop = (char)getch();
}

int ezPanel(){
    erase(1,1,400,220);
    
    write_text("Easy round!!!",100,40,BLUE,1);

    write_text("You will earn",50,60,WHITE,0);
    char scoreToChar[2];
    sprintf(scoreToChar, "%ld", EZ_SCORE);
    write_text(scoreToChar,180,60,WHITE,0);
    write_text("pts for",200,60,WHITE,0);
    write_text("a correct answer!",85,70,WHITE,0);

    write_text("Otherwise,",110,90,WHITE,0);
    write_text("no points will be earned.",50,100,WHITE,0);

    write_text("READY?!",120,120,WHITE,0);
    
    write_text("Press any key to continue...",35,150,GRAY,0);
    char stop = (char)getch();

    return EZ_SCORE;
}

int avePanel(){
    erase(1,1,400,220);
    
    write_text("Average round!!!",85,40,GREEN,1);
    write_text("You will earn",50,60,WHITE,0);
    char scoreToChar[2];
    sprintf(scoreToChar, "%ld", AVE_SCORE);
    write_text(scoreToChar,180,60,WHITE,0);
    write_text("pts for",200,60,WHITE,0);
    write_text("a correct answer!",85,70,WHITE,0);

    write_text("Otherwise,",110,90,WHITE,0);
    write_text("no points will be earned.",50,100,WHITE,0);

    write_text("READY?!",120,120,WHITE,0);
    
    write_text("Press any key to continue...",35,150,GRAY,0);
    char stop = (char)getch();

    return AVE_SCORE;
}

int ggPanel(){
    erase(1,1,400,220);
    
    write_text("Difficult round!!!",85,40,RED,1);
    write_text("You will earn",50,60,WHITE,0);
    char scoreToChar[2];
    sprintf(scoreToChar, "%ld", DIFF_SCORE);
    write_text(scoreToChar,180,60,WHITE,0);
    write_text("pts for",200,60,WHITE,0);
    write_text("a correct answer!",85,70,WHITE,0);

    write_text("Otherwise,",110,90,WHITE,0);
    write_text("no points will be earned.",50,100,WHITE,0);

    write_text("READY?!",120,120,WHITE,0);
    
    write_text("Press any key to continue...",35,150,GRAY,0);
    char stop = (char)getch();

    return DIFF_SCORE;
}

void totalScorePanel(int score){
    erase(1,1,400,220);
    
    write_text("Finished!",120,40,YELLOW,1);
    write_text("You have earned a total of ",40,60,WHITE,0);
    
    char scoreToChar[2];
    sprintf(scoreToChar, "%ld", score);

    write_text(scoreToChar,140,90,YELLOW,1);
    write_text("points!!!",120,100,WHITE,1);

    write_text("Good job!",120,140,WHITE,0);

    write_text("Press any key to continue...",35,150,GRAY,0);
    char stop = (char)getch();
}

void byeUserManggagamit(){
    erase(1,1,400,220);
    write_text("BYE!",150,80,RED,1);
    write_text("Press any key to exit...",55,150,GRAY,0);
    char stop = (char)getch();
}

void erase(int x, int y, int w, int h){ 
    int i,j;
    for (i=y;i<=(y+h);i++){
        for (j=x;j<=(x+w);j++){
            write_pixel(j,i,100);
        }
    }
}

