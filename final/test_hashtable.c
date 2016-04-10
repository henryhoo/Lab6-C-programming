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
	set(t,"you",300);
	set(t,"he",300);
	set(t,"she",400);
	set(t,"they",1000);
	if(get(t,"me",p)!=0){
		printf("%s\n","get error");}
	printf("%s%f\n","get me:",value);
	get(t,"you",p);
	printf("%s%f\n","get you:",value);
	get(t,"he",p);
	printf("%s%f\n","get he:",value);
	get(t,"she",p);
	printf("%s%f\n","get she:",*p);
	if(key_exists(t,"they")){
	printf("%s\n","they exist");
	
}
	if(!key_exists(t,"hey")){
	printf("%s\n","hey not  exist");
	
}	
	remove_key(t,"they");
	if(!key_exists(t,"they")){
	printf("%s\n","they deleted");
	
}
	free_hashtable(t);
	return 0;
}
