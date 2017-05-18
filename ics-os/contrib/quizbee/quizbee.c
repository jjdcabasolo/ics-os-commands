#include "quizbee.h"

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
                            // for some reasons, this is called once more due to some reasons which I really do not know why it happens
                            chooseFileToRead(i, categoryChar);

                            // displays the question panel with the corresponding category and difficulty, returns the correct answer
                            if( i <= 4 ) rightAnswer = questionPanel((i+1), "Easy", LIGHTCYAN, totalScore, randomNumArray[randomNumberIndex], limit);
                            else if( i <= 9 ) rightAnswer = questionPanel((i+1), "Average", LIGHTBLUE, totalScore, randomNumArray[randomNumberIndex], limit);
                            else if( i <= 14 ) rightAnswer = questionPanel((i+1), "Difficult", LIGHTGRAY, totalScore, randomNumArray[randomNumberIndex], limit);

                            // gets the input from user in the question panel
                            keypress = (char)getch();
                            erase(1,1,400,220);

                            // this determines what will be the wrongs answers after reading the correct answer on the file
                            evaluateCorrectAnswer();

                            // this evaluates if the answer is correct, wrong, or the user entered an invalid input
                            if(keypress == rightAnswer){ totalScore = mayTamaKa(totalScore, increment); randomNumberIndex++; break; }
                            else if(keypress == wrongAnswer1 || keypress == wrongAnswer2 || keypress == wrongAnswer3){ betterLuckNextTime(); randomNumberIndex++; break; }
                            else if(keypress == skip_question && skipCount > 0){ totalScore = gumamitNgPowerUp(totalScore, increment); randomNumberIndex++; skipCount--; break; }
                            else if(keypress == quit){ quitting = 1; break; }
                            else if(keypress == skip_question && skipCount == 0) walaNaTamaNa();
                            else  wrongInput();
                            
                            // if the player presses quit, terminates the progress but saves the score
                        }while(keypress != 'a' && keypress != 'b' && keypress != 'c' && keypress != 'd' && keypress != 'q');
                        if(quitting == 1){ totalScore = 0; break; } // resets highscore and the quitting flag
                    }

                    if(quitting == 1){ quitter(totalScore); quitting = 0; } // if the player quits
                    else totalScorePanel(totalScore); // shows total score
                    
                    // Write in a .bin file - highscores, whether the player finishes the game or not.
                    if(categoryChar == category1) writeToFilePKMN(totalScore);
                    else if(categoryChar == category2) writeToFileMOV(totalScore);
                    skipCount = 3;
                }
            }while(keypress != return_main_menu);
        }
        else if(keypress == high_score) highScore();
        else if(keypress == instruction_menu) instructionsPanel();
        else if(keypress == quit_game) byeUserManggagamit();
	} while (keypress != quit_game);

    // freeMallocsPKMN();

	set_graphics(VGA_TEXT80X25X16);
	clrscr();
}

// FUNCTIONS
char mainMenu(){
    erase(1,1,400,220);

    // borders
    int i = 0, j = 0;
    for(i=10;i<150;i++) write_pixel(i+10,20,CYAN); // top
    for(i=10;i<150;i++) write_pixel(i+10,21,CYAN); // top
    for(j=0;j<160;j++) write_pixel(10+10,j+20,CYAN); // left
    for(j=0;j<160;j++) write_pixel(10+11,j+20,CYAN); // left
    for(j=0;j<160;j++) write_pixel(150+10,j+20,CYAN); // right
    for(j=0;j<160;j++) write_pixel(150+11,j+20,CYAN); // right
    for(i=10;i<152;i++) write_pixel(i+10,180,CYAN); // bottom
    for(i=10;i<152;i++) write_pixel(i+10,181,CYAN); // bottom

    // title
	write_text("Quiz Bee!",55,100,WHITE,1);
    write_text("MENU",170,30,BLUE,1); 

	write_text("[2] High Score",170,50,WHITE,0);
	write_text("[7] Instructions",170,60,WHITE,0);
    write_text("[3] Quit",170,70,WHITE,0);

    write_text("[1] Start!!!",170,95,LIGHTGRAY,1); 

    write_text("cmsc125project",170,130,GRAY,0);
    write_text("abasolo +",170,140,GRAY,0);
    write_text("jerusalem",170,150,GRAY,0);
    write_text("T-3L",170,160,GRAY,0);

    char keypress=(char)getch();
    erase(1,1,400,220); //erase menu
    return keypress;
}

char category(){
    erase(1,1,400,220);

    // borders
    int i = 0, j = 0;
    for(i=10;i<285;i++) write_pixel(i+10,20,CYAN); // top
    for(i=10;i<285;i++) write_pixel(i+10,21,CYAN); // top
    for(j=0;j<60;j++) write_pixel(10+10,j+20,CYAN); // left
    for(j=0;j<60;j++) write_pixel(10+11,j+20,CYAN); // left
    for(j=0;j<60;j++) write_pixel(285+10,j+20,CYAN); // right
    for(j=0;j<60;j++) write_pixel(285+11,j+20,CYAN); // right
    for(i=10;i<285+2;i++) write_pixel(i+10,60+20,CYAN); // bottom
    for(i=10;i<285+2;i++) write_pixel(i+10,60+21,CYAN); // bottom
	write_text("Choose a category",85,40,WHITE,1);

	write_text("[4] Pokemon",55,100,WHITE,0); 
	write_text("[5] Movies",55,120,WHITE,0); 

	write_text("[6] Return to main menu",55,160,GRAY,0);

    char keypress=(char)getch();
    erase(1,1,400,220); //erase menu
    return keypress;
}

// displays the question panel with the corresponding category and difficulty, returns the correct answer
// @ param: int count = determines the question count
char questionPanel(int count, char difficulty[], int color, int score, int questionCount, int limit){
    int i = 0, j = 0, increment = 0;

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

                for(j = 0; j < 8; j++){
                    char line1[32];
                    if(j!=7) fgets(line1,32,fp);
                    else fgets(line1,36,fp);
                    line1[31] = '\0';
                    write_text(line1,20,50+increment,WHITE,-1);
                    increment+=10;
                }

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
        char line1[30] = "file reading error.";
        write_text(line1,20,50,WHITE,-1);
    }

    // score
    write_text("Score:",20,170,WHITE,0);   
    char scoreToChar[2];
    sprintf(scoreToChar, "%ld", score);
    write_text(scoreToChar,80,170,YELLOW,0);   
    
    write_text("Skips:",110,170,WHITE,0);   
    char skipToChar[2];
    sprintf(skipToChar, "%ld", skipCount);
    write_text(skipToChar,170,170,YELLOW,0);     

    // quitting station
    write_text("[q] Quit",225,170,GRAY,0);   

    return correctAnswer[0];
}

// this determines what will be the wrong answers after reading the correct answer on the file
void evaluateCorrectAnswer(){
    int i = 0;
    if(rightAnswer == choice_1){
        wrongAnswer1 = 'b';
        wrongAnswer2 = 'c';
        wrongAnswer3 = 'd';
        strcpy(rightAnswerText, answer1);
    }
    else if(rightAnswer == choice_2){
        wrongAnswer1 = 'a';
        wrongAnswer2 = 'c';
        wrongAnswer3 = 'd';
        strcpy(rightAnswerText, answer2);
    }
    else if(rightAnswer == choice_3){
        wrongAnswer1 = 'b';
        wrongAnswer2 = 'a';
        wrongAnswer3 = 'd';
        strcpy(rightAnswerText, answer3);
    }
    else if(rightAnswer == choice_4){
        wrongAnswer1 = 'b';
        wrongAnswer2 = 'c';
        wrongAnswer3 = 'a';
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
    int j = 90, notFinished = 0, k = 0;

    write_text("Enter Name: ",20,50,CYAN,1);
    write_text("(at most eight characters only)",20,70,WHITE,0);
    write_text("Press enter to start.",120,170,GRAY,0);

    while (notFinished != 8){
        char keypress = (char)getch();
        name[k] = keypress;

        // the user entered enter
        if(keypress == 10){ name[k] = '\0'; break; }
        // small letters
        else if(keypress == 'a'){ write_text("a", j+=10 , 90, WHITE, 1); k++; notFinished++; }
        else if(keypress == 'b'){ write_text("b", j+=10 , 90, WHITE, 1); k++; notFinished++; }
        else if(keypress == 'c'){ write_text("c", j+=10 , 90, WHITE, 1); k++; notFinished++; }
        else if(keypress == 'd'){ write_text("d", j+=10 , 90, WHITE, 1); k++; notFinished++; }
        else if(keypress == 'e'){ write_text("e", j+=10 , 90, WHITE, 1); k++; notFinished++; }
        else if(keypress == 'f'){ write_text("f", j+=10 , 90, WHITE, 1); k++; notFinished++; }
        else if(keypress == 'g'){ write_text("g", j+=10 , 90, WHITE, 1); k++; notFinished++; }
        else if(keypress == 'h'){ write_text("h", j+=10 , 90, WHITE, 1); k++; notFinished++; }
        else if(keypress == 'i'){ write_text("i", j+=10 , 90, WHITE, 1); k++; notFinished++; }
        else if(keypress == 'j'){ write_text("j", j+=10 , 90, WHITE, 1); k++; notFinished++; }
        else if(keypress == 'k'){ write_text("k", j+=10 , 90, WHITE, 1); k++; notFinished++; }
        else if(keypress == 'l'){ write_text("l", j+=10 , 90, WHITE, 1); k++; notFinished++; }
        else if(keypress == 'm'){ write_text("m", j+=10 , 90, WHITE, 1); k++; notFinished++; }
        else if(keypress == 'n'){ write_text("n", j+=10 , 90, WHITE, 1); k++; notFinished++; }
        else if(keypress == 'o'){ write_text("o", j+=10 , 90, WHITE, 1); k++; notFinished++; }
        else if(keypress == 'p'){ write_text("p", j+=10 , 90, WHITE, 1); k++; notFinished++; }
        else if(keypress == 'q'){ write_text("q", j+=10 , 90, WHITE, 1); k++; notFinished++; }
        else if(keypress == 'r'){ write_text("r", j+=10 , 90, WHITE, 1); k++; notFinished++; }
        else if(keypress == 's'){ write_text("s", j+=10 , 90, WHITE, 1); k++; notFinished++; }
        else if(keypress == 't'){ write_text("t", j+=10 , 90, WHITE, 1); k++; notFinished++; }
        else if(keypress == 'u'){ write_text("u", j+=10 , 90, WHITE, 1); k++; notFinished++; }
        else if(keypress == 'v'){ write_text("v", j+=10 , 90, WHITE, 1); k++; notFinished++; }
        else if(keypress == 'w'){ write_text("w", j+=10 , 90, WHITE, 1); k++; notFinished++; }
        else if(keypress == 'x'){ write_text("x", j+=10 , 90, WHITE, 1); k++; notFinished++; }
        else if(keypress == 'y'){ write_text("y", j+=10 , 90, WHITE, 1); k++; notFinished++; }
        else if(keypress == 'z'){ write_text("z", j+=10 , 90, WHITE, 1); k++; notFinished++; }
        // big letters
        else if(keypress == 'A'){ write_text("A", j+=10 , 90, WHITE, 1); k++; notFinished++; }
        else if(keypress == 'B'){ write_text("B", j+=10 , 90, WHITE, 1); k++; notFinished++; }
        else if(keypress == 'C'){ write_text("C", j+=10 , 90, WHITE, 1); k++; notFinished++; }
        else if(keypress == 'D'){ write_text("D", j+=10 , 90, WHITE, 1); k++; notFinished++; }
        else if(keypress == 'E'){ write_text("E", j+=10 , 90, WHITE, 1); k++; notFinished++; }
        else if(keypress == 'F'){ write_text("F", j+=10 , 90, WHITE, 1); k++; notFinished++; }
        else if(keypress == 'G'){ write_text("G", j+=10 , 90, WHITE, 1); k++; notFinished++; }
        else if(keypress == 'H'){ write_text("H", j+=10 , 90, WHITE, 1); k++; notFinished++; }
        else if(keypress == 'I'){ write_text("I", j+=10 , 90, WHITE, 1); k++; notFinished++; }
        else if(keypress == 'J'){ write_text("J", j+=10 , 90, WHITE, 1); k++; notFinished++; }
        else if(keypress == 'K'){ write_text("K", j+=10 , 90, WHITE, 1); k++; notFinished++; }
        else if(keypress == 'L'){ write_text("L", j+=10 , 90, WHITE, 1); k++; notFinished++; }
        else if(keypress == 'M'){ write_text("M", j+=10 , 90, WHITE, 1); k++; notFinished++; }
        else if(keypress == 'N'){ write_text("N", j+=10 , 90, WHITE, 1); k++; notFinished++; }
        else if(keypress == 'O'){ write_text("O", j+=10 , 90, WHITE, 1); k++; notFinished++; }
        else if(keypress == 'P'){ write_text("P", j+=10 , 90, WHITE, 1); k++; notFinished++; }
        else if(keypress == 'Q'){ write_text("Q", j+=10 , 90, WHITE, 1); k++; notFinished++; }
        else if(keypress == 'R'){ write_text("R", j+=10 , 90, WHITE, 1); k++; notFinished++; }
        else if(keypress == 'S'){ write_text("S", j+=10 , 90, WHITE, 1); k++; notFinished++; }
        else if(keypress == 'T'){ write_text("T", j+=10 , 90, WHITE, 1); k++; notFinished++; }
        else if(keypress == 'U'){ write_text("U", j+=10 , 90, WHITE, 1); k++; notFinished++; }
        else if(keypress == 'V'){ write_text("V", j+=10 , 90, WHITE, 1); k++; notFinished++; }
        else if(keypress == 'W'){ write_text("W", j+=10 , 90, WHITE, 1); k++; notFinished++; }
        else if(keypress == 'X'){ write_text("X", j+=10 , 90, WHITE, 1); k++; notFinished++; }
        else if(keypress == 'Y'){ write_text("Y", j+=10 , 90, WHITE, 1); k++; notFinished++; }
        else if(keypress == 'Z'){ write_text("Z", j+=10 , 90, WHITE, 1); k++; notFinished++; }
        // numbers: panis may number sa pangalan
        else if(keypress == '1'){ write_text("1", j+=10 , 90, WHITE, 1); k++; notFinished++; }
        else if(keypress == '2'){ write_text("2", j+=10 , 90, WHITE, 1); k++; notFinished++; }
        else if(keypress == '3'){ write_text("3", j+=10 , 90, WHITE, 1); k++; notFinished++; }
        else if(keypress == '4'){ write_text("4", j+=10 , 90, WHITE, 1); k++; notFinished++; }
        else if(keypress == '5'){ write_text("5", j+=10 , 90, WHITE, 1); k++; notFinished++; }
        else if(keypress == '6'){ write_text("6", j+=10 , 90, WHITE, 1); k++; notFinished++; }
        else if(keypress == '7'){ write_text("7", j+=10 , 90, WHITE, 1); k++; notFinished++; }
        else if(keypress == '8'){ write_text("8", j+=10 , 90, WHITE, 1); k++; notFinished++; }
        else if(keypress == '9'){ write_text("9", j+=10 , 90, WHITE, 1); k++; notFinished++; }
        else if(keypress == '0'){ write_text("0", j+=10 , 90, WHITE, 1); k++; notFinished++; }
        // symbols: baka naman kailangan nila sa pangalan nila, ano?
        else if(keypress == '.'){ write_text(".", j+=10 , 90, WHITE, 1); k++; notFinished++; }
        else if(keypress == '?'){ write_text("?", j+=10 , 90, WHITE, 1); k++; notFinished++; }
        else if(keypress == '!'){ write_text("!", j+=10 , 90, WHITE, 1); k++; notFinished++; }
        else if(keypress == '#'){ write_text("#", j+=10 , 90, WHITE, 1); k++; notFinished++; }
        else if(keypress == '@'){ write_text("@", j+=10 , 90, WHITE, 1); k++; notFinished++; }
        else if(keypress == '$'){ write_text("$", j+=10 , 90, WHITE, 1); k++; notFinished++; }
        else if(keypress == '^'){ write_text("^", j+=10 , 90, WHITE, 1); k++; notFinished++; }
        else if(keypress == '&'){ write_text("&", j+=10 , 90, WHITE, 1); k++; notFinished++; }
        else if(keypress == '*'){ write_text("*", j+=10 , 90, WHITE, 1); k++; notFinished++; }
        else if(keypress == '('){ write_text("(", j+=10 , 90, WHITE, 1); k++; notFinished++; }
        else if(keypress == ')'){ write_text(")", j+=10 , 90, WHITE, 1); k++; notFinished++; }
        else if(keypress == '['){ write_text("[", j+=10 , 90, WHITE, 1); k++; notFinished++; }
        else if(keypress == ']'){ write_text("]", j+=10 , 90, WHITE, 1); k++; notFinished++; }
        else if(keypress == '{'){ write_text("{", j+=10 , 90, WHITE, 1); k++; notFinished++; }
        else if(keypress == '}'){ write_text("}", j+=10 , 90, WHITE, 1); k++; notFinished++; }
        else if(keypress == ':'){ write_text(":", j+=10 , 90, WHITE, 1); k++; notFinished++; }
        else if(keypress == ';'){ write_text(";", j+=10 , 90, WHITE, 1); k++; notFinished++; }
        else if(keypress == ','){ write_text(",", j+=10 , 90, WHITE, 1); k++; notFinished++; }
        else if(keypress == '<'){ write_text("<", j+=10 , 90, WHITE, 1); k++; notFinished++; }
        else if(keypress == '>'){ write_text(">", j+=10 , 90, WHITE, 1); k++; notFinished++; }
        else if(keypress == '/'){ write_text("/", j+=10 , 90, WHITE, 1); k++; notFinished++; }
        else if(keypress == '-'){ write_text("-", j+=10 , 90, WHITE, 1); k++; notFinished++; }
        else if(keypress == '+'){ write_text("+", j+=10 , 90, WHITE, 1); k++; notFinished++; }
        else if(keypress == '\\'){ write_text("\\", j+=10 , 90, WHITE, 1); k++; notFinished++; }
        else if(keypress == '\''){ write_text("'", j+=10 , 90, WHITE, 1); k++; notFinished++; }
        else if(keypress == '"'){ write_text("\"", j+=10 , 90, WHITE, 1); k++; notFinished++; }
        else if(keypress == '='){ write_text("=", j+=10 , 90, WHITE, 1); k++; notFinished++; }
    }

    name[k] = '\0';
}

void generateRandomizedNumber(int limit){
	int x, index = 0, increment = 10;

	srand(time(NULL));
	while(index < limit){
		int r = rand() % limit + 1;
		for(x = 0;  x < index;  x++){
			if(randomNumArray[x] == r) break;
		}
		if(x == index) randomNumArray[index++] = r;
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

void writeToFilePKMN(int score){
    char scoreToChar[3];
    sprintf(scoreToChar, "%ld", score);
    
	// file writing -- highscores 
	fp = fopen("highsp.bin", "ab");

	// // writing nung name nung player
	unsigned short sizeOfString = strlen(name) + 1;
	fwrite(&sizeOfString, sizeof(unsigned short), 1, fp);	//the string length + 1 for the null terminator
	fwrite(name, sizeof(char), sizeOfString, fp);			//write the string

	// writing nung score nung player
	unsigned short sizeOfNum = strlen(scoreToChar) + 1;
	fwrite(&sizeOfNum, sizeof(unsigned short), 1, fp);		//the string length + 1 for the null terminator
	fwrite(scoreToChar, sizeof(char), sizeOfNum, fp);		//write the string

    fclose(fp);
}

void writeToFileMOV(int score){
    char scoreToChar[3];
    sprintf(scoreToChar, "%ld", score);
    
	// file writing -- highscores 
	fp = fopen("highsm.bin", "ab");

	// // writing nung name nung player
	unsigned short sizeOfString = strlen(name) + 1;
	fwrite(&sizeOfString, sizeof(unsigned short), 1, fp);	//the string length + 1 for the null terminator
	fwrite(name, sizeof(char), sizeOfString, fp);			//write the string

	// writing nung score nung player
	unsigned short sizeOfNum = strlen(scoreToChar) + 1;
	fwrite(&sizeOfNum, sizeof(unsigned short), 1, fp);		//the string length + 1 for the null terminator
	fwrite(scoreToChar, sizeof(char), sizeOfNum, fp);		//write the string

    fclose(fp);
}

void freeMallocsPKMN(){
    temp = headPKMN;
    while( (temp -> next != NULL) ){
        temp = temp -> next;
        free(temp);
    }
}

void readHighScorePKMN(){
	// file reading -- highscores
	fp = fopen("highsp.bin", "rb");  

	// insert dummy node: the code shall perform insertion sort (descending order of scores)
	newNode = (highScoreNode *) malloc ( sizeof(highScoreNode) );
	newNode -> name = "dummy";
	newNode -> score = 1000000;
	newNode -> next = NULL;
	headPKMN = newNode;

	while(!feof(fp)){
		// freading nung name
		unsigned short stringLength = 0;
		fread(&stringLength, sizeof(unsigned short), 1, fp); // for the end character
		char * nameRead = malloc(sizeof(char) * stringLength);
		int count = fread(nameRead, sizeof(char), stringLength, fp); // the string itself

		// freading nung score mismo
		unsigned short numLength = 0;
		fread(&numLength, sizeof(unsigned short), 1, fp); // for the end character
		char * scoreRead = malloc(sizeof(char) * numLength);
		int count2 = fread(scoreRead, sizeof(char), numLength, fp); // the string itself

		// int score;

		// due to some reasons, may sobrang nareread yung fread, ito yung pantanggal nun
		if(strcmp(nameRead,scoreRead) != 0){
            int score = atoi(scoreRead);
			// sscanf(scoreRead, "%d", &score);
		
			// node creation
			newNode = (highScoreNode *) malloc ( sizeof(highScoreNode) );
			newNode -> name = nameRead;
			newNode -> score = score;
			newNode -> next = NULL;

			// insertion sort :: decreasing order
			temp = headPKMN;
			while( (temp -> next != NULL) && (temp -> next -> score > newNode -> score) ){
				temp = temp -> next;
			}
			newNode -> next = temp -> next;
			temp -> next = newNode;
		}
	}
}

void freeMallocsMOV(){
    temp = headMOV;
    while( (temp -> next != NULL) ){
        temp = temp -> next;
        free(temp);
    }
}

void readHighScoreMOV(){
	// file reading -- highscores
	fp = fopen("highsm.bin", "rb");  

	// insert dummy node: the code shall perform insertion sort (descending order of scores)
	newNode = (highScoreNode *) malloc ( sizeof(highScoreNode) );
	newNode -> name = "dummy";
	newNode -> score = 1000000;
	newNode -> next = NULL;
	headMOV = newNode;

	while(!feof(fp)){
		// freading nung name
		unsigned short stringLength = 0;
		fread(&stringLength, sizeof(unsigned short), 1, fp); // for the end character
		char * nameRead = malloc(sizeof(char) * stringLength);
		int count = fread(nameRead, sizeof(char), stringLength, fp); // the string itself

		// freading nung score mismo
		unsigned short numLength = 0;
		fread(&numLength, sizeof(unsigned short), 1, fp); // for the end character
		char * scoreRead = malloc(sizeof(char) * numLength);
		int count2 = fread(scoreRead, sizeof(char), numLength, fp); // the string itself

		// int score;

		// due to some reasons, may sobrang nareread yung fread, ito yung pantanggal nun
		if(strcmp(nameRead,scoreRead) != 0){
            int score = atoi(scoreRead);
			// sscanf(scoreRead, "%d", &score);
		
			// node creation
			newNode = (highScoreNode *) malloc ( sizeof(highScoreNode) );
			newNode -> name = nameRead;
			newNode -> score = score;
			newNode -> next = NULL;

			// insertion sort :: decreasing order
			temp = headMOV;
			while( (temp -> next != NULL) && (temp -> next -> score > newNode -> score) ){
				temp = temp -> next;
			}
			newNode -> next = temp -> next;
			temp -> next = newNode;
		}
	}
}

void highScore(){   
	int i = 0, increment = 20, j = 2;
    readHighScorePKMN();

    // char line[30][35];
    // int linebreak = 20, skip;
    // int i,j;

    // mainMenu
    // drawRectangle(0,0,320,220, GRAY);
    write_text("HIGH SCORES!",110,20,CYAN,1);
    write_text("Press any key to continue...",35,170,GRAY,0);

    // catogory 1
	write_text("Pokemon",40,40,YELLOW,1);
    // traversing the linked list :: top 5 db??
	temp = headPKMN;
	while(temp != NULL){
		if(i!=0){
            write_text(temp -> name,20,50+increment,WHITE,0);

            char scoreToCharPKMN[3];
            sprintf(scoreToCharPKMN, "%ld", temp -> score);
            write_text(scoreToCharPKMN,100,50+increment,YELLOW,0);

            increment+=20;
            char stop = (char)getch();
		}
		
		temp = temp -> next;
		i++;
	}

    readHighScoreMOV();
    // catogory 2
	write_text("Movies",230,40,CYAN,1);
    // top 5
    // traversing the linked list :: top 5 db??
	temp = headMOV;
    i = 0;
	while(temp != NULL){
		if(i!=0){
            write_text(temp -> name,180,50+increment,WHITE,0);

            char scoreToCharMov[3];
            sprintf(scoreToCharMov, "%ld", temp -> score);
            write_text(scoreToCharMov,260,50+increment,YELLOW,0);

            increment+=20;
            char stop = (char)getch();
		}
		
		temp = temp -> next;
		i++;
	}

    char keypress=(char)getch();


    // strcpy(line[2], "Player 1");
    // strcpy(line[3], "Player 2");
    // strcpy(line[4], "Player 3");
    // strcpy(line[5], "Player 4");
    // strcpy(line[6], "Player 5");

    // category 2
    // strcpy(line[7], "Movie Category");
    // top 5
    // strcpy(line[8], "Player 1");
    // strcpy(line[9], "Player 2");
    // strcpy(line[10], "Player 3");
    // strcpy(line[11], "Player 4");
    // strcpy(line[12], "Player 5");
    //return option
    // strcpy(line[13], "[Press any key to return]");
    
    // write_text(line[0], 115, 20, CYAN, 1);   //display high scores

    // write_text(line[1], 20, 45, BLACK, 0);       //display category title (Pokemon)
    // for(i=2; i<=6; i++){                         //display players
    //     write_text(line[i], 25, 50+linebreak, WHITE, -1);
    //     linebreak+=20;
    // }

    // linebreak = 20, skip;
    // write_text(line[7], 175, 45, BLACK, 0);     //display category title (Movie)
    // for(j=8; j<=12; j++){                       //display players
    //     write_text(line[j], 180, 50+linebreak, WHITE, -1);
    //     linebreak+=20;
    // }

    // write_text(line[13], 40, 180, CYAN, 0);     //display return option  
    // char stop = (char)getch();  
}

void wrongInput(){
    erase(1,1,400,220); //erase menu

    int i = 0, j = 0;
    for(i=10;i<287;i++) write_pixel(i+10,10+50,GRAY); // top
    for(i=10;i<287;i++) write_pixel(i+10,10+50+1,GRAY); // top
    for(j=40;j<110;j++) write_pixel(10+10,j+20,GRAY); // left
    for(j=40;j<110;j++) write_pixel(10+11,j+20,GRAY); // left
    for(j=40;j<110;j++) write_pixel(287+10,j+20,GRAY); // right
    for(j=40;j<110;j++) write_pixel(287+11,j+20,GRAY); // right
    for(i=10;i<287+2;i++) write_pixel(i+10,60+20+50,GRAY); // bottom
    for(i=10;i<287+2;i++) write_pixel(i+10,60+20+50+1,GRAY); // bottom

    write_text("Ayusin ang input :(",80,80,GRAY,1);
    write_text("Choices: [a] [b] [c] [d]",50,100,WHITE,0);
    write_text("Skip: [s]      Quit: [q]",50,110,WHITE,0);
    
    write_text("Press any key to continue...",35,160,GRAY,0);
    char stop = (char)getch();  
}

// displays the instructions on how the game works.
void instructionsPanel(){
    erase(1,1,400,220); //erase menu

	write_text("Instructions",20,20,CYAN,1);

    write_text("Navigation",20,40,CYAN,0);
    write_text("Press the key inside square",20,50,WHITE,0);
    write_text("brackets \"[\" and \"]\".",20,60,WHITE,0);

    write_text("Game Proper",20,80,CYAN,0);
    write_text("Your name will be asked first.",20,90,WHITE,0);
    write_text("You can enter lower & uppercase",20,100,WHITE,0);
    write_text("letters, numbers, and symbols.",20,110,WHITE,0);
    write_text("If the character is not",20,120,WHITE,0);
    write_text("recognized, nothing happens.",20,130,WHITE,0);
    write_text("You cannot use backspace. This",20,140,WHITE,0);
    write_text("is a quiz bee program, not",20,150,WHITE,0);
    write_text("some text editor.",20,160,WHITE,0);

    write_text("Press any key to continue...",40,180,GRAY,0);
    char stop = (char)getch();

    erase(1,1,400,220); //erase menu

	write_text("Instructions",20,20,CYAN,1);

    write_text("There will be three levels of",20,40,WHITE,0);
    write_text("difficulty, which will be ",20,50,WHITE,0);
    write_text("covered in a session. There will",20,60,WHITE,0);
    write_text("be five (5) questions per level.",20,70,WHITE,0);

    write_text("Scoring System",20,90,CYAN,0);
    write_text("two (2)   == easy",20,100,WHITE,0);
    write_text("three (3) == average",20,110,WHITE,0);
    write_text("five (5)  == difficult",20,120,WHITE,0);

    write_text("Answering",20,140,CYAN,0);
    write_text("Press [a] [b] [c] or [d] to ",20,150,WHITE,0);
    write_text("answer the question.",20,160,WHITE,0);
        
    write_text("Press any key to continue...",40,180,GRAY,0);
    char wew = (char)getch();

    erase(1,1,400,220); //erase menu

	write_text("Instructions",20,20,CYAN,1);

    write_text("Quitting",20,40,CYAN,0);
    write_text("Press [q] to quit the session.",20,50,WHITE,0);
    write_text("Your score will be recorded.",20,60,WHITE,0);

    write_text("Power Up",20,80,CYAN,0);
    write_text("You are granted three charges",20,90,WHITE,0);
    write_text("of skips [s] - this skips",20,100,WHITE,0);
    write_text("a question, resulting to a",20,110,WHITE,0);
    write_text("correct answer. Once empty, ",20,120,WHITE,0);
    write_text("it can no longer be used.",20,130,WHITE,0);

    write_text("Have fun answering the quiz!",20,150,WHITE,0);
    write_text("#ICSOSIsLife #ICSOSBestOS",20,160,WHITE,0);
        
    write_text("Press any key to continue...",40,180,GRAY,0);
    char huhu = (char)getch();
}

int mayTamaKa(int score, int increment){
    erase(1,1,400,220); //erase menu

    int i = 0, j = 0;
    for(i=10;i<287;i++) write_pixel(i+10,10+50,GREEN); // top
    for(i=10;i<287;i++) write_pixel(i+10,10+50+1,GREEN); // top
    for(j=40;j<110;j++) write_pixel(10+10,j+20,GREEN); // left
    for(j=40;j<110;j++) write_pixel(10+11,j+20,GREEN); // left
    for(j=40;j<110;j++) write_pixel(287+10,j+20,GREEN); // right
    for(j=40;j<110;j++) write_pixel(287+11,j+20,GREEN); // right
    for(i=10;i<287+2;i++) write_pixel(i+10,60+20+50,GREEN); // bottom
    for(i=10;i<287+2;i++) write_pixel(i+10,60+20+50+1,GREEN); // bottom

    write_text("Correct!!!",120,80,GREEN,1);
    write_text("You have earned",40,100,WHITE,0);
    
    char scoreToChar[2];
    sprintf(scoreToChar, "%ld", increment);
    write_text(scoreToChar,190,100,WHITE,0);
    write_text("points.",220,100,WHITE,0);
    
    write_text("Press any key to continue...",35,160,GRAY,0);
    char stop = (char)getch();
    return score + increment;
}

int gumamitNgPowerUp(int score, int increment){
    erase(1,1,400,220); //erase menu

    int i = 0, j = 0;
    for(i=10;i<287;i++) write_pixel(i+10,10+50,CYAN); // top
    for(i=10;i<287;i++) write_pixel(i+10,10+50+1,CYAN); // top
    for(j=40;j<110;j++) write_pixel(10+10,j+20,CYAN); // left
    for(j=40;j<110;j++) write_pixel(10+11,j+20,CYAN); // left
    for(j=40;j<110;j++) write_pixel(287+10,j+20,CYAN); // right
    for(j=40;j<110;j++) write_pixel(287+11,j+20,CYAN); // right
    for(i=10;i<287+2;i++) write_pixel(i+10,60+20+50,CYAN); // bottom
    for(i=10;i<287+2;i++) write_pixel(i+10,60+20+50+1,CYAN); // bottom

    write_text("Skipped!!!",120,80,CYAN,1);
    write_text("You have earned",40,100,WHITE,0);
    
    char scoreToChar[2];
    sprintf(scoreToChar, "%ld", increment);
    write_text(scoreToChar,190,100,WHITE,0);
    write_text("points.",220,100,WHITE,0);
    
    write_text("Press any key to continue...",35,160,GRAY,0);
    char stop = (char)getch();
    return score + increment;
}

void walaNaTamaNa(){
    erase(1,1,400,220); //erase menu

    int i = 0, j = 0;
    for(i=10;i<287;i++) write_pixel(i+10,10+50,BROWN); // top
    for(i=10;i<287;i++) write_pixel(i+10,10+50+1,BROWN); // top
    for(j=40;j<110;j++) write_pixel(10+10,j+20,BROWN); // left
    for(j=40;j<110;j++) write_pixel(10+11,j+20,BROWN); // left
    for(j=40;j<110;j++) write_pixel(287+10,j+20,BROWN); // right
    for(j=40;j<110;j++) write_pixel(287+11,j+20,BROWN); // right
    for(i=10;i<287+2;i++) write_pixel(i+10,60+20+50,BROWN); // bottom
    for(i=10;i<287+2;i++) write_pixel(i+10,60+20+50+1,BROWN); // bottom

    write_text("TAMA NA!!!",120,80,BROWN,1);
    write_text("Wala ka nang skip. Staph.",45,100,WHITE,0);
    write_text("No more skips. Oks lang yan.",45,110,WHITE,0);
    
    write_text("Press any key to continue...",35,160,GRAY,0);
    char stop = (char)getch();
}

void betterLuckNextTime(){
    erase(1,1,400,220); //erase menu

    int i = 0, j = 0;
    for(i=10;i<287;i++) write_pixel(i+10,10+50,RED); // top
    for(i=10;i<287;i++) write_pixel(i+10,10+50+1,RED); // top
    for(j=40;j<110;j++) write_pixel(10+10,j+20,RED); // left
    for(j=40;j<110;j++) write_pixel(10+11,j+20,RED); // left
    for(j=40;j<110;j++) write_pixel(287+10,j+20,RED); // right
    for(j=40;j<110;j++) write_pixel(287+11,j+20,RED); // right
    for(i=10;i<287+2;i++) write_pixel(i+10,60+20+50,RED); // bottom
    for(i=10;i<287+2;i++) write_pixel(i+10,60+20+50+1,RED); // bottom
    write_text("Wrong!!!",125,80,RED,1);
    write_text("The correct answer is",70,100,WHITE,0);

    write_text(correctAnswer,70,110,WHITE,0);
    write_text(". ",80,110,WHITE,0);
    write_text(rightAnswerText,100,110,WHITE,0);

    write_text("Press any key to continue...",35,160,GRAY,0);
    char stop = (char)getch();
}

void quitter(int score){
    erase(1,1,400,220);
    
    write_text("Quitter!",125,30,MAGENTA,1);
    write_text("You have earned a total of ",40,50,WHITE,0);
    
    int i = 0, j = 0;
    for(i=100;i<195;i++) write_pixel(i+10,20+50,MAGENTA); // top
    for(i=100;i<195;i++) write_pixel(i+10,20+50+1,MAGENTA); // top
    for(j=50;j<110;j++) write_pixel(100+10,j+20,MAGENTA); // left
    for(j=50;j<110;j++) write_pixel(100+11,j+20,MAGENTA); // left
    for(j=50;j<110;j++) write_pixel(195+10,j+20,MAGENTA); // right
    for(j=50;j<110;j++) write_pixel(195+11,j+20,MAGENTA); // right
    for(i=100;i<195+2;i++) write_pixel(i+10,60+20+50,MAGENTA); // bottom
    for(i=100;i<195+2;i++) write_pixel(i+10,60+20+50+1,MAGENTA); // bottom
    char scoreToChar[2];
    sprintf(scoreToChar, "%ld", score);
    write_text(scoreToChar,150,80,YELLOW,1);
    write_text("points!!!",120,100,WHITE,1);

    write_text("Good job!",120,140,WHITE,0);

    write_text("Press any key to continue...",35,160,GRAY,0);
    char stop = (char)getch();
}

int ezPanel(){
    erase(1,1,400,220);
    
    int i = 0, j = 0;
    for(i=10;i<150;i++) write_pixel(i+10,20,LIGHTCYAN); // top
    for(i=10;i<150;i++) write_pixel(i+10,21,LIGHTCYAN); // top
    for(j=0;j<160;j++) write_pixel(10+10,j+20,LIGHTCYAN); // left
    for(j=0;j<160;j++) write_pixel(10+11,j+20,LIGHTCYAN); // left
    for(j=0;j<160;j++) write_pixel(150+10,j+20,LIGHTCYAN); // right
    for(j=0;j<160;j++) write_pixel(150+11,j+20,LIGHTCYAN); // right
    for(i=10;i<152;i++) write_pixel(i+10,180,LIGHTCYAN); // bottom
    for(i=10;i<152;i++) write_pixel(i+10,181,LIGHTCYAN); // bottom
	write_text("Easy",70,85,WHITE,1);
	write_text("round!!!!",50,100,WHITE,1);

    write_text("You will earn",170,40,WHITE,0);
    char scoreToChar[2];
    sprintf(scoreToChar, "%ld", EZ_SCORE);
    write_text(scoreToChar,190,50,LIGHTCYAN,1);
    write_text("pts",200,55,WHITE,0);
    write_text("for a correct",170,65,WHITE,0);
    write_text("answer!",170,75,WHITE,0);

    write_text("Otherwise,",170,90,WHITE,0);
    write_text("no points will",170,100,WHITE,0);
    write_text("be earned.",170,110,WHITE,0);

    write_text("READY?!",170,130,WHITE,0);
    
    write_text("Press any key",170,150,GRAY,0);
    write_text("to continue...",170,160,GRAY,0);
    char stop = (char)getch();

    return EZ_SCORE;
}

int avePanel(){
    erase(1,1,400,220);
    
    int i = 0, j = 0;
    for(i=10;i<150;i++) write_pixel(i+10,20,LIGHTBLUE); // top
    for(i=10;i<150;i++) write_pixel(i+10,21,LIGHTBLUE); // top
    for(j=0;j<160;j++) write_pixel(10+10,j+20,LIGHTBLUE); // left
    for(j=0;j<160;j++) write_pixel(10+11,j+20,LIGHTBLUE); // left
    for(j=0;j<160;j++) write_pixel(150+10,j+20,LIGHTBLUE); // right
    for(j=0;j<160;j++) write_pixel(150+11,j+20,LIGHTBLUE); // right
    for(i=10;i<152;i++) write_pixel(i+10,180,LIGHTBLUE); // bottom
    for(i=10;i<152;i++) write_pixel(i+10,181,LIGHTBLUE); // bottom
	write_text("Average",55,85,WHITE,1);
	write_text("round!!!!",50,100,WHITE,1);

    write_text("You will earn",170,40,WHITE,0);
    char scoreToChar[2];
    sprintf(scoreToChar, "%ld", AVE_SCORE);
    write_text(scoreToChar,190,50,LIGHTBLUE,1);
    write_text("pts",200,55,WHITE,0);
    write_text("for a correct",170,65,WHITE,0);
    write_text("answer!",170,75,WHITE,0);

    write_text("Otherwise,",170,90,WHITE,0);
    write_text("no points will",170,100,WHITE,0);
    write_text("be earned.",170,110,WHITE,0);

    write_text("READY?!",170,130,WHITE,0);
    
    write_text("Press any key",170,150,GRAY,0);
    write_text("to continue...",170,160,GRAY,0);
    char stop = (char)getch();

    return AVE_SCORE;
}

int ggPanel(){
    erase(1,1,400,220);
    
    int i = 0, j = 0;
    for(i=10;i<150;i++) write_pixel(i+10,20,LIGHTGRAY); // top
    for(i=10;i<150;i++) write_pixel(i+10,21,LIGHTGRAY); // top
    for(j=0;j<160;j++) write_pixel(10+10,j+20,LIGHTGRAY); // left
    for(j=0;j<160;j++) write_pixel(10+11,j+20,LIGHTGRAY); // left
    for(j=0;j<160;j++) write_pixel(150+10,j+20,LIGHTGRAY); // right
    for(j=0;j<160;j++) write_pixel(150+11,j+20,LIGHTGRAY); // right
    for(i=10;i<152;i++) write_pixel(i+10,180,LIGHTGRAY); // bottom
    for(i=10;i<152;i++) write_pixel(i+10,181,LIGHTGRAY); // bottom
	write_text("Difficult",50,85,WHITE,1);
	write_text("round!!!!",50,100,WHITE,1);

    write_text("You will earn",170,40,WHITE,0);
    char scoreToChar[2];
    sprintf(scoreToChar, "%ld", DIFF_SCORE);
    write_text(scoreToChar,190,50,LIGHTGRAY,1);
    write_text("pts",200,55,WHITE,0);
    write_text("for a correct",170,65,WHITE,0);
    write_text("answer!",170,75,WHITE,0);

    write_text("Otherwise,",170,90,WHITE,0);
    write_text("no points will",170,100,WHITE,0);
    write_text("be earned.",170,110,WHITE,0);

    write_text("READY?!",170,130,WHITE,0);
    
    write_text("Press any key",170,150,GRAY,0);
    write_text("to continue...",170,160,GRAY,0);
    char stop = (char)getch();

    return DIFF_SCORE;
}

void totalScorePanel(int score){
    erase(1,1,400,220);
    
    write_text("Finished!",120,30,CYAN,1);
    write_text("You have earned a total of ",40,50,WHITE,0);
    
    int i = 0, j = 0;
    for(i=100;i<195;i++) write_pixel(i+10,20+50,CYAN); // top
    for(i=100;i<195;i++) write_pixel(i+10,20+50+1,CYAN); // top
    for(j=50;j<110;j++) write_pixel(100+10,j+20,CYAN); // left
    for(j=50;j<110;j++) write_pixel(100+11,j+20,CYAN); // left
    for(j=50;j<110;j++) write_pixel(195+10,j+20,CYAN); // right
    for(j=50;j<110;j++) write_pixel(195+11,j+20,CYAN); // right
    for(i=100;i<195+2;i++) write_pixel(i+10,60+20+50,CYAN); // bottom
    for(i=100;i<195+2;i++) write_pixel(i+10,60+20+50+1,CYAN); // bottom
    char scoreToChar[2];
    sprintf(scoreToChar, "%ld", score);
    write_text(scoreToChar,150,80,YELLOW,1);
    write_text("points!!!",120,100,WHITE,1);

    write_text("Good job!",120,140,WHITE,0);

    write_text("Press any key to continue...",35,160,GRAY,0);
    char stop = (char)getch();
}

void byeUserManggagamit(){
    erase(1,1,400,220);
    write_text("BYE!",140,80,RED,1);
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

