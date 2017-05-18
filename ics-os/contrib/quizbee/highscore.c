#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct highScoreEntry{
	char * name;
	int score;
	struct highScoreEntry * next;
} highScoreNode;

int main(){
	FILE *fp;

	// file writing -- highscores 
	fp = fopen("highsp.bin", "ab");
	highScoreNode * newNode = NULL, * head = NULL, * temp = NULL;

	// // writing nung name nung player
	// char name[9] = "third \0";
	// unsigned short sizeOfString = strlen(name) + 1;
	// fwrite(&sizeOfString, sizeof(unsigned short), 1, fp);	//the string length + 1 for the null terminator
	// fwrite(name, sizeof(char), sizeOfString, fp);			//write the string

	// // writing nung score nung player
	// char scoreToChar[3] = "25\0";
	// unsigned short sizeOfNum = strlen(scoreToChar) + 1;
	// fwrite(&sizeOfNum, sizeof(unsigned short), 1, fp);		//the string length + 1 for the null terminator
	// fwrite(scoreToChar, sizeof(char), sizeOfNum, fp);		//write the string

	// fclose(fp);

	// file reading -- highscores
	fp = fopen("highsp.bin", "rb");  

	// insert dummy node: the code shall perform insertion sort (descending order of scores)
	newNode = (highScoreNode *) malloc ( sizeof(highScoreNode) );
	newNode -> name = "dummy";
	newNode -> score = 1000000;
	newNode -> next = NULL;
	head = newNode;

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

		int score;

		// due to some reasons, may sobrang nareread yung fread, ito yung pantanggal nun
		if(strcmp(nameRead,scoreRead) != 0){
			sscanf(scoreRead, "%d", &score);
		
			// node creation
			newNode = (highScoreNode *) malloc ( sizeof(highScoreNode) );
			newNode -> name = nameRead;
			newNode -> score = score;
			newNode -> next = NULL;

			// insertion sort :: decreasing order
			temp = head;
			while( (temp -> next != NULL) && (temp -> next -> score > newNode -> score) ){
				temp = temp -> next;
			}
			newNode -> next = temp -> next;
			temp -> next = newNode;
		}
	}

	// traversing the linked list :: top 5 db??
	// int i = 0;
	// temp = head;
	// while(temp != NULL){
	// 	if(i!=0){
	// 		printf("%s ", temp -> name);
	// 		printf("%d\n", temp -> score);
	// 	}
	// 	if(i == 6) break;
		
	// 	temp = temp -> next;
	// 	i++;
	// }

	fclose(fp);

	return 0;
}
