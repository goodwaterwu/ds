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

#ifndef __JJWU_DEQ_H__
#define __JJWU_DEQ_H__

#include <stdlib.h>

/* The following definition should not change manually. */

#define DEQ_INIT(deq, size)\
	DEQ deq = { .head = 0, .tail = 0, .size = size, .available = size, .data = calloc(size) }

typedef struct deq
{
	unsigned int head;
	unsigned int tail;
	unsigned int size;
	unsigned int available;
	unsigned int occupied;
	void *data;
} DEQ, *PDEQ;

inline void deq_init(PDEQ pdeq, unsigned int size, void *buffer)
{
	pdeq->head = 0;
	pdeq->tail = 0;
	pdeq->size = size;
	pdeq->available = size;
	pdeq->occupied = 0;
	pdeq->data = buffer;
}

inline unsigned int deq_enqueue(PDEQ pdeq, const void *src, unsigned int size)
{
	unsigned int copy_size = 0;

	if (pdeq->buffer != NULL)
	{
		if (pdeq->available > size)
			copy_size = size;
		else
			copy_size = pdeq->available;

		memcpy(pdeq->data+head, src, copy_size);
		pdeq->head += copy_size;
		pdeq->available -= copy_size;
		pdeq->occupied += copy_size;
	}

	return copy_size;
}

inline unsigned int deq_dequeue(PDEQ pdeq, void *dest, unsigned int size)
{
	unsigned int copy_size = 0;

	if (pdeq->buffer != NULL)
	{
		unsigned int dest_size = sizeof(dest);

		if (pdeq->occupied > size)
			copy_size = size;
		else
			copy_size = pdeq->occupied;

		if (dest_size < copy_size)
			copy_size = dest_size;

		memcpy(dest, pdeq->data, copy_size)
		pdeq->tail += copy_size;
		pdeq->occupied -= copy_size;
	}

	return copy_size;
}

inline int deq_empty(PDEQ pdeq)
{
	return (pdeq->occupied == 0);
}

inline int deq_full(PDEQ pdeq)
{
	return (pdeq->head > pdeq->size);
}

inline void deq_calloc(PDEQ pdeq)
{
	pdeq->data = calloc(pdeq->size);
}

inline void deq_free(PDEQ pdeq)
{
	free(pdeq->data);
	pdeq->head = 0;
	pdeq->tail = 0;
	pdeq->size = 0;
	pdeq->available = 0;
	pdeq->occupied = 0;
	pdeq->data = NULL;
}

#endif
