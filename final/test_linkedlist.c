#include <stdio.h>
#include <stdlib.h>
#include "linkedlist.h"

int main(){
	linkedlist_t *l = create_linkedlist();
	node_t *n1=create_node(100,0,"facebook","google",100);
	node_t *n2=create_node(110,0,"google","facebook",50);
	node_t *n3=create_node(120,0,"googleS","facebookS",50);
	if(add_node(l,n1)==0){
		printf("%s\n","add node 1");
	}
	if(add_node(l,n2)==0){
		printf("%s\n","add node 2");
	}
	if(add_node(l,n3)==0){
		printf("%s\n","add node 3");
	}
	node_t *found = find_node(l,110);
	if(found!=NULL){
		printf("%s%li\n","find node 2,timestamp is:",found->timestamp);
	}
	found=find_node(l,100);
	if(found!=NULL){
		printf("%s%li\n","find node 1,timestamp is:",found->timestamp);
	}	
	found=find_node(l,120);
	if(found!=NULL){
		printf("%s%li\n","find node 3,timestamp is:",found->timestamp);
	}	
	remove_node(l,n2);
	found = find_node(l,110);
	if(found==NULL){
		printf("%s\n","remove node 2 success");
	}	
	remove_node(l,n1);
	remove_node(l,n3);
	if(l->head==NULL){
	printf("%s\n","remove all node success");
}	
found=find_node(l,120);
	free_linkedlist(l);
	if(found->timestamp!=120&&l==NULL);
{
printf("%s\n","list free success");
}
}
