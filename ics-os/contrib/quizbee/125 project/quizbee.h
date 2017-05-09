// GLOBAL VARIABLES
int score = 0;
char * name;

// file reading
FILE *fp;
char question[1000];
char choice1[120];
char choice2[120];
char choice3[120];
char choice4[120];
char answer[120];
char newLineCatch[1];

// typedef struct to
int questionNumber;
char ** questions;

// typedef struct answers
// int questionNumber;
char ** answers;

// FUNCTIONS
// file reading
void getQuestionProcess(){
	int i = 0;
	if(fp != NULL){
		while(!feof(fp)){
			fgets(question, 1000, fp);

			fscanf(fp, "%s", &choice1);
			fscanf(fp, "%s", &choice2);
			fscanf(fp, "%s", &choice3);
			fscanf(fp, "%s", &choice4);
			fscanf(fp, "%s", &answer);
			fscanf(fp, "%s", &newLineCatch);
			
			// TODO: paano lagyan yung array of strings ng laman sa c
			// questions[i] = name;

			// TODO: Gawan na ng data structure to: typedef
			i++;
		}				
		fclose(fp);
	}
	else{
		printf("File not found.\n");
	}
}

void getPokemonEasyQuestions(){
	fp = fopen("files/pokemonEasyQuestions.txt", "r");
	getQuestionProcess(); // TODO: ipass dito yung data struct for easy
}

void getPokemonAverageQuestions(){
	fp = fopen("files/pokemonAverageQuestions.txt", "r");
	getQuestionProcess(); // TODO: ipass dito yung data struct for ave
}

void getPokemonDifficultQuestions(){
	fp = fopen("files/pokemonDifficultQuestions.txt", "r");
	getQuestionProcess(); // TODO: ipass dito yung data struct for diff
}

void getQuestions(){
	getPokemonEasyQuestions();
	getPokemonAverageQuestions();
	getPokemonDifficultQuestions();
}

// menus 
void mainMenu(){
	printf("\nQuiz Bee!\n");
	printf("1 - Play!\n");
	printf("2 - High Scores\n");
	printf("3 - Quit\n");
}

void chooseCategory(){
	printf("\nChoose your category\n");
	printf("4 - Pokemon\n");
	printf("5 - Movies\n");
	printf("6 - Return to main menu\n");	
}

void askName(){
	printf("Enter your name here: ");
}

int randomizeQuestionCount(){
	int random = 0;
	// TODO: randomize number here
	return random;
}

// question proper
void presentQuestions(int count, char * question){
	printf("Question #%d\n", count);

	printf("%s\n", question);

	// TODO: [ui] display current score
	// TODO: [ui] display quit button
}

void updateScore(int points){
	printf("Correct! You got %d points!\n", points);
	score += points;
}

void wrongAnswer(char * answer){
	printf("Wrong! The correct answer ois %s\n", answer);	
}

// high score related
void sortHighScore(){
	// TODO: process [sort] muna dito para ascending yung highscores
}

void printHighScore(){
	int count = 5; // top 5 lang 
	printf("\nHigh scores\n");

	sortHighScore();

	printf("Pokemon masters\n");
	for(int i = 0; i < count; ++i){
		printf("%d - %s\n", (i+1), name);
	}
	
	printf("Movie people\n");
	for(int i = 0; i < count; ++i){
		printf("%d - %s\n", (i+1), name);
	}
}

// file writing
void addToHighScore(int score){
	printf("You've got %d points in total!\n", score);

	fp = fopen("highScorePokemon.txt", "r");
	if(fp != NULL){
		fprintf(fp, "%d", name);
		fprintf(fp, "%d", score);
		fclose(fp);
	}
	else{
		printf("File not found.\n");
	}
}