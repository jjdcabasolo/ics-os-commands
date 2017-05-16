#include <stdio.h>
#include <time.h>

int main(){
	int array[5];
	int x, p;
	int count;
	int i=0;

	srand(time(NULL));

	while(i<5){
		int r = rand()%5;

		for(x = 0;  x < i;  x++){
			if(array[x]==r){
				break;
			}
		}
		
		if(x==i){
			array[i++]=r;
		}
	}


	for(p=0; p<5; p++){
		printf("%d ", array[p]);
	}

	return 0;
}
