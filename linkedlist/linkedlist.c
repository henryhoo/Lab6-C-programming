#include <stdio.h>
#include <stdlib.h>
#include "linkedlist.h"
/**
 * Create a newly allocated empty linkedlist_t with head and tail initialized to NULL
 * Parameters:
 *      None
 * Returns:
 *      A pointer to an allocated linked_list_t structure,
 *      the caller is responsible for deallocating using
 *      free_linkedlist()
 */
linkedlist_t * create_linkedlist(){
  linkedlist_t *newlist = malloc(sizeof(linkedlist_t));
  newlist->head=NULL;
  newlist->tail=NULL;
  return newlist;
}

/**
 * Free the memory allocated for the linkedlist_t object. This includes
 * using delete_node() to delete all the nodes and the values in the nodes
 * Parameters:
 *      list - Pointer to the linkedlist object to
 * Returns:
 *      Nothing
 */
void free_linkedlist(linkedlist_t *list){
  node_t *walk = list->head;
  node_t *next = NULL;
  while(walk)
  {
    next = walk->next;
    free(walk);
    walk = next;
  }
  free(list);
}

/**
 * Add a linkedlist node to the tail of the list. After this function
 * returns, list->tail should be the same as node.
 * Parameters:
 *      list - Pointer to the linkedlist we are adding the node to
 *      node - Pointer to the node we are appending to the tail of the list
 * Return:
 *      0 if the insertion is successful -1 otherwise or if either parameter is NULL
 */
int add_node(linkedlist_t *list, node_t *node){
  if (list==NULL||node==NULL) {
    /* code */
    return -1;
  }
  else{
    if (list->head==NULL) {
      /* code */
      list->head=node;
      list->tail=node;
return 0;
    }
    if (list->tail!=NULL) {
      /* code */
      node->prev=list->tail;
      list->tail->next=node;
      list->tail=node;
return 0;
    }
    return -1;
  }
}

/**
 * Given a pointer to a linkedlist node and the linkedlist, remove
 * the node from the list. This does not deallocate the node or it's
 * contents.
 *i Parameters:
 *      list - Pointer to the linkedlist we are removing the node from
 *      node - Pointer to the node we are removing from the list
 * Return:
 *      0 if the removal is successful, or -1 if the removal failed or either parameter is NULL
 */
int remove_node(linkedlist_t *list, node_t *node){
	if (list==NULL||node==NULL||list->head==NULL) {
		/* code */
		return -1;
	}
	else if(list->head==node){
		list->head=node->next;
		return 0;
	}
	else if(list->tail==node){
		list->tail=node->prev;
		return 0;
	}
	else{

		node->prev->next=node->next;
		node->next->prev=node->prev;
		return 0;
	}
	return -1;
}

/**
 * Create a new node containing the given values
 * Parameters:
 *      timestamp   - The timestamp of the transaction
 *      transaction_type - The value indicating the type of transaction
 *      company1    - Pointer to the string containing the name of the first company in the transaction
 *      company2    - Pointer to the string containing the name of the second company in the transaction
 *      value       - Numeric value for either the initial balance (ADD) or transfer amount (TRANSFER)
 * Return:
 *      Return a pointer to a newly allocated node_t initialized with the parameters.
 *      Return NULL if memory allocation failed, otherwise return a pointer to the node
 * Remarks:
 *      For both company1 and company2, ownership of the memory pointed to
 *      by company1 and company2 is not transfered to this function meaning
 *      that after this function call returns, it is possible that the memory
 *      is modified, so a copy of the underlying memory must be performed.
 *      Both company1 and company2 are allowed to be NULL.
 */
node_t *create_node(long int timestamp, short transaction_type, const char *company1, const char *company2, double value){
	node_t *newnode = malloc(sizeof(node_t));
	if(newnode == NULL) return NULL;
	newnode->timestamp=timestamp;
	newnode->transaction_type=transaction_type;
	newnode->company1=(char *)company1;
	newnode->company2=(char *)company2;
	newnode->value=value;
	return newnode;
}

/**
 * Delete a node, including any strings or values it contains
 * Parameters:
 *      node - Pointer to the node that should be deleted
 * Remarks:
 */
void delete_node(node_t *node){
	//node->prev->next=node->next;
	//node->next->prev=node->prev;

	free(node);
}

/**
 * Find a node based on the timestamp.
 * Parameters:
 *      list - The linkedlist to search for the given timestamp
 *      timestamp - The timestamp to search for in the linked list
 * Return:
 *      Return a pointer to the node if a node with the given timestamp
 *      can be found, otherwise return NULL if no node with that
 *      timestamp is found or the arguments are invalid.
 */
node_t* find_node(linkedlist_t *list, long int timestamp){

	if (list==NULL||list->head==NULL) {
		/* code */
		return NULL;
	}
	else{
		node_t *walk = list->head;
		while(walk){
			if (walk->timestamp==timestamp) {
				/* code */
				return walk;
			}
			walk=walk->next;
		}
	}
	return NULL;
}
