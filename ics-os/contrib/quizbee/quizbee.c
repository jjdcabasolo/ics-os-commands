#include "../../sdk/dexsdk.h"
#include "../../sdk/time.h"
#include "quizbee.h"

void set_coordinates(int x, int y); //initialize bulb coordinates
void setup_level(); //self explanatory
void flip_fxn(int x, int y); 
void gray(int x, int y); //prints a gray bulb socket
void light(int r, int c, int x, int y); //prints a bulb light
void print_bulb(int r, int c, int x, int y); //print a bulb
void print_board(int x, int y); //set up initial board
void edit_board(); // update selected and previously selected bulb colors
void erase(); //basically covers an area with a black rectangle

//displays menus
void mainMenu();
void category();
void questionPanel();
void mayTamaKa();
void betterLuckNextTime();
void highScore();
void wrongInput();

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
#define quit 'g'

#define YELLOW 54
#define PALE_YELLOW 62
#define ROYAL_BLUE 1
#define DARK_BLUE 8
#define GRAY 56
#define WHITE 63

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
#define YELLOW 14
#define BLINK 128

int main(){ 
    char keypress = start;
	int i, j;
	char str[15];
	int champion = 0;

	set_graphics(VGA_320X200X256);

	do{
        erase(1,1,400,220);

        mainMenu(); //print menu
        keypress=(char)getch();
        erase(1,1,400,220); //erase menu

        if(keypress == start){
            do{
                // print category
                category();       
                keypress=(char)getch();
                erase(1,1,400,220); //erase menu

                if(keypress == category1){
                    
                    // traverse the question list
                    for(i = 0; i < question_limit; i++){
                        erase(1,1,400,220); //erase menu

                        do{
                            questionPanel();
                            keypress=(char)getch();
                            char rightAnswer = 'a';
                            char wrongAnswer = 'b';

                            if(keypress == rightAnswer) mayTamaKa();
                            else if(keypress == wrongAnswer) betterLuckNextTime();
                            else wrongInput();
                            
                        }while(keypress != 'a' && keypress != 'b' && keypress != 'c' && keypress != 'd' && keypress != 'q');


                        if(keypress == quit){
                            break;
                            keypress == return_main_menu;
                        }
                    }

                }
                else if(keypress == category2){
                }

            }while(keypress != return_main_menu);
        }
        else if(keypress == high_score){
            // print highscore
            highScore();       
            keypress=(char)getch();
            erase(1,1,400,220); //erase menu            
        }

	} while (keypress != quit_game);

	set_graphics(VGA_TEXT80X25X16);
	clrscr();
}

// ---- MENUS ----
// displays mainMenu
void mainMenu(){
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
	write_text("1 - Start",120,120,WHITE,0); 

    // for (i=190;i<120;i++)write_pixel(i,150,ROYAL_BLUE); // top
    // for (i=190;i<120;i++)write_pixel(i,151,ROYAL_BLUE); // top
    // for (j=150;j<20;j++)write_pixel(20,j,ROYAL_BLUE); // left
    // for (j=150;j<20;j++)write_pixel(21,j,ROYAL_BLUE); // right
	write_text("2 - High Score",100,140,WHITE,0);

    write_text("3 - Quit",125,160,WHITE,0);
}


// displays categories
void category(){
    // prompt
	write_text("Choose a category",90,40,WHITE,1);

    // pick categories
	write_text("4 - Pokemon",50,100,YELLOW,0); 
	write_text("5 - Movies",50,120,ROYAL_BLUE,0); 
	write_text("6 - Return to main menu",50,140,WHITE,0);
}

void questionPanel(){
    // tanong
	write_text("Question #1",20,20,WHITE,1);

    // yung mismong tanong
    // three liner questions lang :( - 30 characters
    char line1[] = "asdfkjsahdf dfskj hdsakf rghdf";
    char line2[] = "as--dsf-sad-dere=--93746 rghdf";
    char line3[] = "7823489gdakfy7906qw uiyadsef09";
    char line4[] = "asdfkjsahdf d3fskj hsakf rghdf";
    char line5[] = "asdfkjsahdf dfskj 4hsakf rghdf";
    char line6[] = "asdfkjsahdf dfskj hdsakf rghdf";
    char line7[] = "asdfkjsahdf dfskj hdsakf rghdf";
    char line8[] = "asdfkjsahdf dfskj hdsakf rghdf";
    write_text(line1,20,50,WHITE,-1);
    write_text(line2,20,60,WHITE,-1);
    write_text(line3,20,70,WHITE,-1);
    write_text(line4,20,80,WHITE,-1);
    write_text(line5,20,90,WHITE,-1);
    write_text(line6,20,100,WHITE,-1);
    write_text(line7,20,110,WHITE,-1);
    write_text(line8,20,120,WHITE,-1);

    // sagot
	write_text("a. Answer 1",20,140,WHITE,0); 
	write_text("b. Answer 2",20,150,WHITE,0); 
	write_text("c. Answer 3",180,140,WHITE,0);   
	write_text("d. Answer 4",180,150,WHITE,0);   

    // score
    write_text("Score:",20,170,WHITE,0);   
    int score = 0;
    write_text((char)score,80,170,WHITE,0);   
    
    // quitting station
    write_text("q - Quit game",165,170,WHITE,0);   
}

void highScore(){
    // mainMenu
	write_text("High scores!",120,40,WHITE,1);

    // catogory 1
	write_text("Category title 1",120,40,WHITE,1);
    // top 5
	write_text("1 - Player 1",120,100,WHITE,0); 
	write_text("2 - Player 1",120,120,WHITE,0); 
	write_text("3 - Player 1",120,140,WHITE,0);   
	write_text("4 - Player 1",120,140,WHITE,0);   
	write_text("5 - Player 1",120,140,WHITE,0);   

    // catogory 2
	write_text("Category title 2",120,40,WHITE,1);
    // top 5
    write_text("1 - Player 1",120,100,WHITE,0); 
    write_text("2 - Player 1",120,120,WHITE,0); 
    write_text("3 - Player 1",120,140,WHITE,0);   
    write_text("4 - Player 1",120,140,WHITE,0);   
    write_text("5 - Player 1",120,140,WHITE,0);   
}

void erase(int x, int y, int w, int h){ //basically covers an area with a black rectangle 
    int i,j;
    for (i=y;i<=(y+h);i++){
        for (j=x;j<=(x+w);j++){
            write_pixel(j,i,100);
        }
    }
}

void wrongInput(){
    erase(1,1,400,220); //erase menu

    write_text("Ayusin ang input :(",80,80,GRAY,1);
    write_text("a, b, c, d, or q",90,100,WHITE,0);
    write_text("lang ang choices.",90,110,WHITE,0);
    
    write_text("Press any key to continue...",35,150,GRAY,0);
    char stop = (char)getch();    
}

void mayTamaKa(){
    erase(1,1,400,220); //erase menu

    write_text("Correct!!!",120,80,YELLOW,1);
    write_text("You have earned",40,100,WHITE,0);

    char score[] = "1";
    write_text(score,190,100,WHITE,0);

    write_text("points.",220,100,WHITE,0);
    
    write_text("Press any key to continue...",35,150,GRAY,0);
    char stop = (char)getch();
}

void betterLuckNextTime(){
    erase(1,1,400,220); //erase menu

    write_text("Wrong!!!",120,80,RED,1);
    write_text("The correct answer is",50,100,WHITE,0);

    char score[] = "a. Answer 1";
    write_text(score,100,110,WHITE,0);

    write_text("Press any key to continue...",35,150,GRAY,0);
    char stop = (char)getch();
}

// filereading @ dexsdk.h
// FILE *openfile(const char  *filename,int mode);
// int feof(FILE *f);
// FILE *fopen(const char *filename,const char *s);
// int fgetc (FILE *stream);
// char *fgets(char *s, int n, FILE* f);
// int fread(const void *buf,int itemsize,int noitems,FILE* fhandle);
// int fwrite(const void *buf,int itemsize,int noitems,FILE* fhandle);
// char fputc(char c,FILE *f);
// int fclose(FILE *stream);
// int fflush (FILE *stream);
// char *fseek(FILE* f,long x,int y);
// long int ftell(FILE *stream);
// int closefile(FILE* fhandle);
// int remove(char *filename);
// int mkdir (const char *filename, mode_t mode);
// int copyfile(const char *src, const char *dest);