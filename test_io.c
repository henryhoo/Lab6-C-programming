nclude <stdio.h>
#include <stdlib.h>
#include "linkedlist.h"
#include "hashtable.h"

int main(){
FILE *f1=fopen("./accounts.txt","r");
FILE *f2=fopen("./trans.txt","r");
hashtable_t t = read_accounts(f1);
linkedlist_t l = read_transactions(f2);
apply_transactions(l,t);


}
