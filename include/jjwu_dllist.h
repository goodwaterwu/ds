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

/* The following definition should not change manually. */

#define DLLIST_INIT(dllist)\
	DLLIST dllist = { .prior = &dllist, .next = &dllist }

#define dllist_entry(node)\
	((node)->self)

#define dllist_prior_entry(node)\
	((node)->prior->self)

#define dllist_next_entry(node)\
	((node)->next->self)

#define dllist_for_each_node(pdllist, node)\
	for (node = (pdllist)->next ; node != pdllist ; node = node->next)

#define dllist_for_each_node_prior(pdllist, node)\
	for (node = (pdllist)->prior ; node != pdllist ; node = node->prior)

#define dllist_for_each_node_next(pdllist, node)\
	dllist_for_each_node(pdllist, node)

#define dllist_for_each_entry(pdllist, node, entry)\
	for (node = (pdllist)->next ; (node != pdllist) && (entry = node->self) ; node = node->next)

#define dllist_for_each_entry_prior(pdllist, node, entry)\
	for (node = (pdllist)->prior ; (node != pdllist) && (entry = node->self) ; node = node->prior)

#define dllist_for_each_entry_next(pdllist, node, entry)\
	dllist_for_each_entry(pdllist, node, entry)

typedef struct dllist
{
	void *self;
	struct dllist *prior;
	struct dllist *next;
} DLLIST, *PDLLIST;

static inline void dllist_init(PDLLIST pdllist)
{
	pdllist->prior = pdllist;
	pdllist->next = pdllist;
}

static inline void jjwu_dllist_addnode(PDLLIST prior, PDLLIST next, PDLLIST node)
{
	prior->next = node;
	node->prior = prior;
	node->next = next;
	next->prior = node;
}

inline void dllist_addnode(PDLLIST pdllist, PDLLIST node)
{
	jjwu_dllist_addnode(pdllist, pdllist->next, node);	
}

inline void dllist_addnode_tail(PDLLIST pdllist, PDLLIST node)
{
	
	jjwu_dllist_addnode(pdllist->prior, pdllist, node);	
}

inline void dllist_addnode_next(PDLLIST pdllist, PDLLIST node)
{
	dllist_addnode(pdllist, node);
}

static inline void jjwu_dllist_deletenode(PDLLIST node)
{
	node->prior->next = node->next;
	node->next->prior = node->prior;
	dllist_init(node);
}

inline void dllist_deletenode(PDLLIST node)
{
	jjwu_dllist_deletenode(node);	
}

inline void dllist_movenode(PDLLIST pdllist, PDLLIST node)
{
	dllist_deletenode(node);
	dllist_addnode(pdllist, node);
}

inline void dllist_movenode_tail(PDLLIST pdllist, PDLLIST node)
{
	dllist_deletenode(node);
	dllist_addnode_tail(pdllist, node);
}

inline void dllist_movenode_next(PDLLIST pdllist, PDLLIST node)
{
	dllist_movenode(pdllist, node);
}

inline int dllist_empty(PDLLIST pdllist)
{
	return ((pdllist->prior == pdllist) && (pdllist->next == pdllist));	
}

inline void dllist_concat(PDLLIST dest, PDLLIST src)
{
	PDLLIST dn = dest->next;

	dest->next = src->next;
	src->next->prior = dest;
	src->prior->next = dn;
	dn->prior = src->prior;
	dllist_init(src);
}

inline void dllist_concat_tail(PDLLIST dest, PDLLIST src)
{
	PDLLIST dp = dest->prior;

	dest->prior = src->prior;
	src->prior->next = dest;
	src->next->prior = dp;
	dp->next = src->next;
	dllist_init(src);
}

inline void dllist_concat_next(PDLLIST dest, PDLLIST src)
{
	dllist_concat(dest, src);
}

inline int dllist_exist(PDLLIST pdllist, PDLLIST node)
{
	PDLLIST iternode = NULL;
	int ret = 0;

	if (!dllist_empty(pdllist))
	{
		dllist_for_each_node(pdllist, iternode)
		{
			if (iternode == node)
			{
				ret = 1;
				break;
			}
		}
	}
	
	return ret;
}

#endif
