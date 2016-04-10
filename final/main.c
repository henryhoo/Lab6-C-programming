#include <stdio.h>
#include <stdlib.h>
#include<string.h>
#include "linkedlist.h"
#include "hashtable.h"
#include "io.h"
int main(int argc,char* argv[]){
	if(argc!=4){
		printf("%s","Usage: <transaction_file> <account_in_file> <account_out_file>");
		return 1;	
	}
FILE *f1=fopen(argv[2],"r");
FILE *f2=fopen(argv[1],"r");
FILE *f3=fopen(argv[3],"w");
hashtable_t *t = read_accounts(f1);
linkedlist_t *l = read_transactions(f2);
apply_transactions(l,t);
write_accounts(f3,t);

}
