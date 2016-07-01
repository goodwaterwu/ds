/*
 * Copyright (c) 2016 WU, JHENG-JHONG <goodwater.wu@gmail.com>
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated 
 * documentation files (the "Software"), to deal in the Software without restriction, including without limitation 
 * the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and 
 * to permit persons to whom the Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all copies or substantial portions of 
 * the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO 
 * THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE 
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF 
 * CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS 
 * IN THE SOFTWARE.
 */

#ifndef __JJWU_DLLIST_H__
#define __JJWU_DLLIST_H__

/* The follow definition can change according to your need */




/* The following definition should not change manually. */

typedef struct dllist
{
	void *self;
	struct dllist *prev;
	struct dllist *next;
} DLLIST, *PDLLIST;

inline void dllist_init(PDLLIST pdllist)
{
	pdllist->prev = pdllist;
	pdllist->next = pdllist;
}

static inline void __dllist_addnode(PDLLIST prev, PDLLIST next, PDLLIST node)
{
	prev->next = node;
	node->prev = prev;
	node->next = next;
	next->prev = node;
}

inline void dllist_addnode(PDLLIST pdllist, PDLLIST node)
{
	__dllist_addnode(pdllist, pdllist->next, node);	
}

inline void dllist_addnode_prior(PDLLIST pdllist, PDLLIST node)
{
	
	__dllist_addnode(pdllist->prev, pdllist, node);	
}

inline void dllist_addnode_next(PDLLIST pdllist, PDLLIST node)
{
	dllist_addnode(pdllist, node);
}

static inline void __dllist_deletenode(PDLLIST node)
{
	node->prev->next = next;
	node->next->prev = prev;
	dllist_init(node);
}

inline void dllist_deletenode(PDLLIST node)
{
	__dllist_deletenode(node);	
}

inline void dllist_movenode(PDLLIST pdllist, PDLLIST node)
{
	dllist_deletenode(node);
	dllist_addnode(pdllist, node);
}

inline void dllist_movenode_prior(PDLLIST pdllist, PDLLIST node)
{
	dllist_deletenode(node);
	list_add_prior(pdllist, node);
}

inline void dllist_movenode_next(PDLLIST pdllist, PDLLIST node)
{
	dllist_movenode(pdllist, node);
}

inline int dllist_empty(PDLLIST pdllist)
{
	return ((pdllist->prev == pdllist) && (pdllist->next == pdllist));	
}

static inline void __dllist_concat(PDLLIST dest, PDLLIST src, PDLLIST src_prev)
{
	PDLLIST dest_next = dest->next;
    dest->next = src;
	src->prev = dest;
    src_prev->next = dest;
    dest_next->prev = src_prev;
}

inline void dllist_concat(PDLLIST dest, PDLLIST src)
{
	if (!dllist_empty(dest))
	{
		PDLLIST dest_next = dest->next;
		PDLLIST src_prev = src->prev;

		dest->next = src;
		src->prev = dest;
		src_prev = dest_next;
		dest_next->prev = src_prev;
	}
}

inline void dllist_concat_prior(PDLLIST dest, PDLLIST src)
{
	if (!dllist_empty(dest))
	{
		PDLLIST dest_prev = dest->prev;
		PDLLIST src_prev = src->prev;

		dest->prev = src_prev;
		src_prev->next = dest;
		src->prev = dest_prev;
		dest_prev->next = src;
	}
}

inline void dllist_concat_next(PDLLIST dest, PDLLIST src)
{
	dllist_concat(dest, src);
}

#endif
