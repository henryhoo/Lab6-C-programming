//
//  io.c
//  LAB6
//
//  Created by henry hoo on 4/7/16.
//  Copyright © 2016 henry hoo. All rights reserved.
//

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "io.h"
#include "hashtable.h"
#include "linkedlist.h"
/**
 * Read the initial account information from a file
 * by creating a new hashtable with one entry per line
 * in the file, containing the <CompanyName> as the key
 * and the <AccountBalance> as the value. If a given
 * <CompanyName> already exists in the hashtable,
 * overwrite the existing balance associated with
 * the <CompanyName>
 * Input Format:
 *  <CompanyName> <AccountBalance>
 *  <CompanyName> <AccountBalance>
 *  <CompanyName> <AccountBalance>
 *  ......
 *  <CompanyName> <AccountBalance>
 *  there may be leading or trailing spaces
 * Parameters:
 *      fd - File descriptor to read from
 * Return:
 *      Pointer to newly created hashtable, the caller is
 *      responsible for freeing this later. Return NULL
 *      if fd is NULL or if the account file is incorrectly
 *      formatted.
 */
hashtable_t *read_accounts(FILE *fd){
	if(fd==NULL){
		return NULL;}
	hashtable_t *table=create_hashtable(3);
	char name[10];
	int score2;
	while (fscanf(fd,"%s",name)!=EOF){
		fscanf(fd,"%d",&score2);
		if (set(table, name, score2)!=0) {
			return NULL;
		}
	}
	return table;
}

/**
 * Write the final account information to a file by iterating
 * through the hashtable and outputting valid entries to the file
 * Output Format:
 *      <CompanyName> <AccountBalance>
 *      <CompanyName> <AccountBalance>
 *      ....
 *      ....
 *      <CompanyName> <AccountBalance>
 * Sample Output Records:
 *      "Google 10000"
 *      "Microsoft 43082.34"
 * Parameters:
 *      fd - File descriptor to write the output to
 *      accounts - Pointer to hashtable to write to the file
 * Remarks:
 *      The ordering in which the <CompanyName> <AccountBalance> lines
 *      are written to file does not matter
 */
void write_accounts(FILE *fd, hashtable_t *accounts){
	hashtable_ent_t **p = accounts->table;
	hashtable_ent_t *t = NULL;
	int i = 0;
	for (i=0;i<accounts->table_len;i++) {
		t=*p;
		while (t) {
			fprintf(fd, "%s %d\n",t->key,(int)t->value);
			t=t->next;
		}
		p++;
	}

}

/**
 * Read a list of transactions from a file
 * Input Format:
 *      <TimeStamp> <TransactionType> <Company1> [<Company2> <Value>]
 * Sample Input Lines:
 *      "159742987 TRANSFER Google Microsoft 10000000"
 *      "7398079827 ADD Google 1000000"
 *      "907983988 REMOVE Microsoft"
 * Parameters:
 *      fd - File descriptor for the file to read input from
 * Returns:
 *      A pointer to a linkedlist_t structure containing the transactions in the order
 *      they were in the file or NULL if fd is invalid or the file contains a transaction
 *      that was invalid (Unknown transaction type, timestamps out of order, etc)
 */
linkedlist_t *read_transactions(FILE *fd){
	if(fd==NULL){
		return NULL;}
	linkedlist_t *list=create_linkedlist();
	linkedlist_t *temp=create_linkedlist();
	long int timestamp=NULL;
	short transaction_type=0;
	char arg1[10];
	char arg2[20];
	char arg3[20];
	double arg4;
	node_t *node=NULL;
	node_t *small=NULL;
	while (fscanf(fd,"%li",&timestamp)!=EOF){
		fscanf(fd,"%s",arg1);	
		if (strcmp(arg1, "TRANSFER") == 0) {
			transaction_type=2;
		fscanf(fd,"%s",arg2);	
		fscanf(fd,"%s",arg3);	
		fscanf(fd,"%lf",&arg4);	
		}
		else if (strcmp(arg1, "ADD")==0) {
			transaction_type=1;
		fscanf(fd,"%s",arg2);	
		fscanf(fd,"%lf",&arg4);	
		}
		else if (strcmp(arg1, "REMOVE")==0) {
			transaction_type=3;
		fscanf(fd,"%s",arg2);	
		}
		else{
			return NULL;
		}
		node=create_node(timestamp, transaction_type, arg2, arg3, arg4);
		add_node(temp,node);
	}
	while(temp->head){
		node = temp->head;
		small = temp->head;
		while(node){
			if(node->timestamp<small->timestamp){
				small=node;
			}
			node=node->next;	
		}	
				add_node(list,small);
				remove_node(temp,small);
	}
	free_linkedlist(temp);
	return list;
}
/**
 * Iterate from the head to the tail of the transaction linked list
 * and apply the transactions in order to the accounts hashtable.
 * For each node in the list, perform the transaction the list
 * node describes, then move onto the next node.
 * Transaction:
 *      Each node in the linked list contains five fields describing the transaction:
 *      1. 'timestamp' - The time at which the transaction occured
 *      2. 'transaction_type' - Integer representing the transaction type (ADD, REMOVE, TRANSFER)
 *      3. 'company1' - A pointer to the string containing the first company name
 *      4. 'company2' - A pointer to the string containing the second company name (Only for TRANSFERs)
 *      5. 'value'    - The numeric value of the TRANSFER or inital account balance for an ADD
 * Transaction Type:
 *      ADD 'company1' 'value'
 *          Add 'company1' to the account hashtable with a value of 'value'
 *      REMOVE 'company1'
 *          Remove 'company1' from the hashtable if it exists, error if it doesn't
 *      TRANSFER 'company1' 'company2' 'value'
 *          Transfer 'value' from the account of 'company1' into the account of 'company2'
 * Parameters:
 *      transactions - Ordered transactions in a linked list
 *      accounts - Hashtable mapping company name to account balance
 * Return:
 *      -1 if any of the parameters are NULL or an illegal transaction
 *      occurs, otherwise return the number of processed transactions
 */
int apply_transactions(linkedlist_t *transactions, hashtable_t *accounts){

	node_t *node=NULL;
	node=transactions->head;
	double *cm1=malloc(sizeof(double*)),*cm2=malloc(sizeof(double *));
	while(node){
		switch(node->transaction_type){
			case 1:
				set(accounts,node->company1,node->value);
				break;
			case 2:
				get(accounts,node->company1,cm1);
				get(accounts,node->company2,cm2);
				set(accounts,node->company1,*cm1-node->value);
				set(accounts,node->company2,*cm2+node->value);
				break;
			case 3:
				remove_key(accounts,node->company1);
				break;
		}
node=node->next;
	}
	free(cm1);
	free(cm2);

}
