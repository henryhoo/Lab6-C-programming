#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "hashtable.h"

int main(){
	hashtable_t *t = create_hashtable(3);
	double value = 0;
	double *p=&value;
	if(set(t,"me",100)==-1){
		printf("%s\n","set error");}
	set(t,"you",200);
	set(t,"he",300);
	set(t,"she",400);
	set(t,"they",1000);
	if(get(t,"me",p)){
		printf("%s\n","get error");}
	printf("%s%f\n","get me:",value);
	get(t,"you",p);
	printf("%s%f\n","get you:",value);
	get(t,"he",p);
	printf("%s%f\n","get he:",value);

	return 0;
}
