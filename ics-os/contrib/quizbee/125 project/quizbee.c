// #include <stdio.h>
// #include <stdlib.h>

// #include "quizbee.h"
// #define questionCount 10

// #define easyPoints 10
// #define averagePoints 10
// #define difficultPoints 10

// int main(){
// 	int choice = 0, i = 0, level = 1;
// 	char answer, * question, * rightAnswerString, correctAnswer;
	
// 	while(choice != 3){
// 		mainMenu();
// 		printf("\tchoice: ");
// 		scanf("%d", &choice);

// 		if(choice == 1){
// 			while(choice != 6){
// 				chooseCategory();
// 				printf("\tchoice: ");
// 				scanf("%d", &choice);

// 				if(choice == 4 || choice == 5){
// 					askName();
// 					scanf("%s", name);

// 					if(choice == 4)	getQuestions();	// TODO: parameter nito ay pokemon
// 					if(choice == 5)	getQuestions();	// TODO: parameter nito ay movie

// 					for(i = 0; i < questionCount; ++i){
// 						randomizeQuestionCount();

// 						presentQuestions(i, question);
// 						printf("\tchoice: ");
// 						scanf("%c", answer);

// 						if(i % 5 == 0) level++;

// 						if(answer == correctAnswer){
// 							if(level == 1) updateScore(easyPoints);
// 							if(level == 2) updateScore(averagePoints);
// 							if(level == 3) updateScore(difficultPoints);
// 						}
// 						else{
// 							wrongAnswer(rightAnswerString);
// 						}
// 						if(answer == 'q') break;	
// 					}

// 					addToHighScore(score);
// 				}
// 			}
// 		}
// 		else if(choice == 2){
// 			printHighScore();
// 		}
// 	}
	
// 	return 0;
// }