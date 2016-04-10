#include <stdio.h>
#include <stdlib.h>
#include<string.h>
#include "linkedlist.h"
#include "hashtable.h"
#include "io.h"
int main(){
FILE *f1=fopen("./accounts.txt","r");
FILE *f2=fopen("./trans.txt","r");
FILE *f3=fopen("./out.txt","w");

//char a[100],c[5];
//char *d,*d2,*d3;
//double d4;
//long int b=0;
//while(fscanf(f2,"%li",&b)!=EOF){
//fscanf(f2,"%s",d);
//fscanf(f2,"%s",d2);
//fscanf(f2,"%s",d3);
//fscanf(f2,"%lf",&d4);
//}
hashtable_t *t = read_accounts(f1);

linkedlist_t *l = read_transactions(f2);
apply_transactions(l,t);
write_accounts(f3,t);

}
