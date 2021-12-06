/************************************************************************
 *
 *      Copyright (C) 2004-2008 ZyXEL Communications, Corp.
 *      All Rights Reserved.
 *
 * ZyXEL Confidential; Need to Know only.
 * Protected as an unpublished work.
 *
 * The computer program listings, specifications and documentation
 * herein are the property of ZyXEL Communications, Corp. and shall
 * not be reproduced, copied, disclosed, or used in whole or in part
 * for any reason without the prior express written permission of
 * ZyXEL Communications, Corp.
 *
 *************************************************************************/
#ifndef _LIST_H
#define _LIST_H
/*-----------------------------------------------------------------*/

/*-----------------------------------------------------------------*/


//------ linked list--------
/**
 * Structure for referencing a node in a list_t element.
 * @struct __node
 */
typedef struct __node
{
	void *next;                 /**< next __node_t containing element */
	void *element;              /**< element in Current node */
}__node_t;

/**
 * Structure for referencing a list of elements.
 */
typedef struct _list
{
	int nb_elt;         /**< Number of element in the list */
	__node_t *node;     /**< Next node containing element  */

}list_t;

/* added by bennewit@cs.tu-berlin.de */
typedef struct
{
	__node_t *actual;
	__node_t **prev;
	list_t *li;
	int pos;
}list_iterator_t ;

/**
 * Initialise a list_t element.
 * NOTE: this element MUST be previously allocated with
 * dns_malloc(). The dns_free() call on the list is
 * still automatically done by list_free(). This
 * also means you can't use a static list_t variable
 * if you want to use list_free().
 * @param li The element to initialise.
 */
int list_init (list_t * li);

/**
 * Free a list of element.
 * Each element will be free with the method given as the second parameter.
 * @param li The element to work on.
 * @param free_func The method that is able to release one element of the list.
 */
void list_special_free (list_t * li, void *(*free_func) (void *));

/**
 * Free a list of element where elements are pointer to 'char'.
 * @param li The element to work on.
*/
void list_ofchar_free (list_t * li);

/**
 * Get the size of a list of element.
 * @param li The element to work on.
 */
int list_size (const list_t * li);

/**
 * Check if the end of list is detected .
 * @param li The element to work on.
 * @param pos The index of the possible element.
 */
int list_eol (const list_t * li, int pos);

/**
 * Add an element in a list.
 * @param li The element to work on.
 * @param element The pointer on the element to add.
 * @param pos the index of the element to add. (or -1 to append the element at the end)
 */
int list_add (list_t * li, void *element, int pos);

/**
 * Get an element from a list.
 * @param li The element to work on.
 * @param pos the index of the element to get.
 */
void *list_get (const list_t * li, int pos);

/**
 * Remove an element from a list.
 * @param li The element to work on.
 * @param pos the index of the element to remove.
 */
int list_remove (list_t * li, int pos);

/* added by bennewit@cs.tu-berlin.de */
void *list_get_first (list_t * li, list_iterator_t * it);

/* added by bennewit@cs.tu-berlin.de */
void *list_get_next (list_iterator_t * it);

/* added by bennewit@cs.tu-berlin.de */
void *list_iterator_remove (list_iterator_t * it);

#endif
