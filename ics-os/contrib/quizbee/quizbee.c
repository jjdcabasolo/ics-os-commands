#include "../../sdk/dexsdk.h"
#include "../../sdk/time.h"
#include "quizbee.h"

// PROTOTYPES
char mainMenu();                // displays the main menu - returns the coice of the user
char category();                // displays the window for picking the category
void enterName();            // asks the user of its name - which is utilized in the highscore panel
void highScore();            // displays the window for highscores on both categories
void enterIGN();
void drawRectangle();

char questionPanel();         // the window for each of the question
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

// categories
#define category1 '4'
#define category2 '5'
#define return_main_menu '6'

// number of questions per category
#define question_limit 5
#define quit 'q'

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

int main(){ 
    char keypress = start;
	int i, j;

	set_graphics(VGA_320X200X256);

	do{
        keypress = mainMenu(); //print menu
        if(keypress == start){
            do{
                keypress = category();             
                if(keypress == category1){
                    enterIGN();
                    int totalScore = 0, increment = 0, quitting = 0;

                    write_text(name,120,40,WHITE,1);

                    for(i = 0; i < (question_limit*3); i++){ // traverse the question list :: easy pa lang to shet
                        if( i == 0 ) increment = ezPanel();
                        if( i == 5 ) increment = avePanel();
                        if( i == 10 ) increment = ggPanel();

                        do{
                            if( i <= 4 ) keypress = questionPanel((i+1), "Easy", BLUE);
                            else if( i <= 9 ) keypress = questionPanel((i+1), "Average", GREEN);
                            else if( i <= 14 ) keypress = questionPanel((i+1), "Difficult", RED);

                            // TODO: make function na mageevaluate kung anu-ano yung tama at maling character
                            char rightAnswer = 'a';
                            char wrongAnswer1 = 'b';
                            char wrongAnswer2 = 'c';
                            char wrongAnswer3 = 'd';

                            if(keypress == rightAnswer) totalScore = mayTamaKa(totalScore, increment);
                            else if(keypress == wrongAnswer1 || keypress == wrongAnswer2 || keypress == wrongAnswer3) betterLuckNextTime();
                            else if(keypress != 'a' && keypress != 'b' && keypress != 'c' && keypress != 'd' && keypress != 'q') wrongInput();
                            
                            if(keypress == quit){
                                quitter();
                                quitting = 1;
                                break;
                            }
                        }while(keypress != 'a' && keypress != 'b' && keypress != 'c' && keypress != 'd' && keypress != 'q');
                        
                        if(quitting == 1) break;
                    }

                    // TODO: Write to file - highscores
                    totalScorePanel(totalScore);
                }
                else if(keypress == category2){
                    // TODO: [prereq:: if(keypress == category1)] copy category 1 here
                }
            }while(keypress != return_main_menu);
        }
        else if(keypress == high_score) highScore();
        else if(keypress == quit_game) byeUserManggagamit();
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

char questionPanel(int count, char difficulty[], int color){
    erase(1,1,400,220);

    // tanong
	write_text("Question #",20,20,WHITE,1);

    char scoreToChar[2];
    sprintf(scoreToChar, "%ld", count);
    write_text(scoreToChar,120,20,WHITE,1);

    write_text("|",150,20,WHITE,1);
    write_text(difficulty,155,20,color,1);

    // yung mismong tanong
    // three liner questions lang :( - 30 characters
    FILE * fp = fopen("pez.txt", "r");
    if(fp != NULL){
        char line1[31];
        char line2[31];
        char line3[31];
        char line4[31];
        char line5[31];
        char line6[31];
        char line7[31];
        char line8[31];
        char answer1[11];
        char answer2[11];
        char answer3[11];
        char answer4[11];

        fgets(line1,31,fp);
        line1[31] = '\0';
        write_text(line1,20,50,WHITE,-1);
        fgets(line2,31,fp);
        line2[31] = '\0';
        write_text(line2,20,60,WHITE,-1);
        fgets(line3,31,fp);
        line3[31] = '\0';
        write_text(line3,20,70,WHITE,-1);
        fgets(line4,31,fp);
        line4[31] = '\0';
        write_text(line4,20,80,WHITE,-1);
        fgets(line5,31,fp);
        line5[31] = '\0';
        write_text(line5,20,90,WHITE,-1);
        fgets(line6,31,fp);
        line6[31] = '\0';
        write_text(line6,20,100,WHITE,-1);
        fgets(line7,31,fp);
        line7[31] = '\0';
        write_text(line7,20,110,WHITE,-1);
        fgets(line8,31,fp);
        line8[31] = '\0';
        write_text(line8,20,120,WHITE,-1);

    	write_text("a.",20,140,WHITE,0); 
        fgets(answer1,10,fp);
        answer1[8] = '\0';
        write_text(answer1,50,140,WHITE,0); 

    	write_text("b.",20,150,WHITE,0); 
        fgets(answer2,10,fp);
        answer2[8] = '\0';
        write_text(answer2,50,150,WHITE,0); 

    	write_text("c.",180,140,WHITE,0);   
        fgets(answer3,10,fp);
        answer3[8] = '\0';
        write_text(answer3,210,140,WHITE,0);   
    	
        write_text("d.",180,150,WHITE,0);   
        fgets(answer4,10,fp);
        answer4[8] = '\0';
        write_text(answer4,210,150,WHITE,0);   

        char correctAnswer;
        fgets(answer4,10,fp);

        fclose(fp);
    }
    else{
        char line1[30] = "file reading error. file read-";
        write_text(line1,20,50,WHITE,-1);
    }


    // score
    write_text("Score:",20,170,WHITE,0);   
    int score = 0;
    write_text((char)score,80,170,WHITE,0);   
    
    // quitting station
    write_text("[q] Quit game",165,170,GRAY,0);   

    char keypress=(char)getch();
    erase(1,1,400,220); //erase menu
    return keypress;
}

// void highScore(){
//     erase(1,1,400,220);

//     // mainMenu
// 	write_text("High scores!",110,20,WHITE,1);

//     // catogory 1
// 	write_text("Pokemon",50,40,YELLOW,1);
//     // top 5
// 	write_text("1 - Player 1",20,60,WHITE,0); 
// 	write_text("2 - Player 1",20,80,WHITE,0); 
// 	write_text("3 - Player 1",20,100,WHITE,0);   
// 	write_text("4 - Player 1",20,120,WHITE,0);   
// 	write_text("5 - Player 1",20,140,WHITE,0);   

//     // catogory 2
// 	write_text("Movies",230,40,CYAN,1);
//     // top 5
//     write_text("1 - Player 1",180,60,WHITE,0); 
//     write_text("2 - Player 1",180,80,WHITE,0); 
//     write_text("3 - Player 1",180,100,WHITE,0);   
//     write_text("4 - Player 1",180,120,WHITE,0);   
//     write_text("5 - Player 1",180,140,WHITE,0);   

//     write_text("Press any key to continue...",35,170,GRAY,0);
//     char keypress=(char)getch();
//     erase(1,1,400,220); //erase menu
// }

void enterName(){   
    int i = 0;
    erase(1,1,400,220); //erase menu

    // greetings
	write_text("Hello!",125,40,WHITE,1);

    // question
    write_text("What is your name?",72,80,GRAY,1);
    write_text("(enter 5 characters)",65,100,WHITE,0);

    // write_text("Name: ",50,120,WHITE,0);
    // write_text("_",90,120,WHITE,0);
    // write_text("_",100,120,WHITE,0);
    // write_text("_",110,120,WHITE,0);
    // write_text("_",120,120,WHITE,0);
    // write_text("_",130,120,WHITE,0);
    // write_text("Press key to enter name...",35,150,GRAY,0);
    // char stop2 = (char)getch();  

    // for(i = 1; i < question_limit; i++){
    //   erase(1,1,400,220); //erase menu
    // }

    char stop = (char)getch();  
}


void enterIGN(){
    int inputLen=0;
    char ign[10];
    int j=90;
    int notFinished = 0;

    drawRectangle(0,0,320,220, BLACK);
    write_text("Enter Name : ",20,50,WHITE,1);
    write_text("(at most eight characters only)",20,70,WHITE,0);
    write_text("Press 1 to start.",150,170,GRAY,0);

    int k = 0;

    while (notFinished != 8){
        char keypress=(char)getch();
        // name[k] = keypress;

        if(keypress == 1) break;        
        if(keypress == 'a') write_text("A", j+=10 , 90, WHITE, 1);
        if(keypress == 'b') write_text("B", j+=10 , 90, WHITE, 1);
        if(keypress == 'c') write_text("C", j+=10 , 90, WHITE, 1);
        if(keypress == 'd') write_text("D", j+=10 , 90, WHITE, 1);
        if(keypress == 'e') write_text("E", j+=10 , 90, WHITE, 1);
        if(keypress == 'f') write_text("F", j+=10 , 90, WHITE, 1);
        if(keypress == 'g') write_text("G", j+=10 , 90, WHITE, 1);
        if(keypress == 'h') write_text("H", j+=10 , 90, WHITE, 1);
        if(keypress == 'i') write_text("I", j+=10 , 90, WHITE, 1);
        if(keypress == 'j') write_text("J", j+=10 , 90, WHITE, 1);
        if(keypress == 'k') write_text("K", j+=10 , 90, WHITE, 1);
        if(keypress == 'l') write_text("L", j+=10 , 90, WHITE, 1);
        if(keypress == 'm') write_text("M", j+=10 , 90, WHITE, 1);
        if(keypress == 'n') write_text("N", j+=10 , 90, WHITE, 1);
        if(keypress == 'o') write_text("O", j+=10 , 90, WHITE, 1);
        if(keypress == 'p') write_text("P", j+=10 , 90, WHITE, 1);
        if(keypress == 'q') write_text("Q", j+=10 , 90, WHITE, 1);
        if(keypress == 'r') write_text("R", j+=10 , 90, WHITE, 1);
        if(keypress == 's') write_text("S", j+=10 , 90, WHITE, 1);
        if(keypress == 't') write_text("T", j+=10 , 90, WHITE, 1);
        if(keypress == 'u') write_text("U", j+=10 , 90, WHITE, 1);
        if(keypress == 'v') write_text("V", j+=10 , 90, WHITE, 1);
        if(keypress == 'w') write_text("W", j+=10 , 90, WHITE, 1);
        if(keypress == 'x') write_text("X", j+=10 , 90, WHITE, 1);
        if(keypress == 'y') write_text("Y", j+=10 , 90, WHITE, 1);
        if(keypress == 'z') write_text("Z", j+=10 , 90, WHITE, 1);

        notFinished++;
        k++;
    }
}

void highScore(){   
    char line[30][35];
    int linebreak = 20, skip;
    int i,j;

    // mainMenu
    drawRectangle(0,0,320,220, GRAY);
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

    char score[] = "a. Answer 1";
    write_text(score,120,110,WHITE,0);

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
    write_text("correct answer!",90,70,WHITE,0);

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
    write_text("correct answer!",90,70,WHITE,0);

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
    write_text("correct answer!",90,70,WHITE,0);

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

void drawRectangle(int x, int y, int w, int h, int color){
   int i,j;
   for (i=y;i<=(y+h);i++)
      for (j=x;j<=(x+w);j++)
         write_pixel(j,i,color);
}
