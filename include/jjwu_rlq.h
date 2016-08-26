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

#ifndef __JJWU_RLQ_H__
#define __JJWU_RLQ_H__

#include <stdlib.h>
#include <string.h>

/* The following definition should not change manually. */

#define RLQ_INIT(NAME, SIZE)\
	RLQ NAME = { .head = 0, .tail = 0, .size = SIZE, .available = SIZE, .relocatable = RLQ_NOT_RELOCATABLE, .data = calloc(SIZE, 1) }

#define RLQ_INIT_RELOCATE(NAME, SIZE)\
	RLQ NAME = { .head = 0, .tail = 0, .size = SIZE, .available = SIZE, .relocatable = RLQ_RELOCATABLE, .data = calloc(SIZE, 1) }

typedef enum relocate
{
	RLQ_NOT_RELOCATABLE = 0,
	RLQ_RELOCATABLE = 1,
} RELOCATE;

typedef struct rlq
{
	unsigned int head;
	unsigned int tail;
	unsigned int size;
	unsigned int available;
	unsigned int occupied;
	RELOCATE relocatable;
	void *data;
} RLQ, *PRLQ;

inline void rlq_init(PRLQ prlq, unsigned int size, void *buffer)
{
	prlq->head = 0;
	prlq->tail = 0;
	prlq->size = size;
	prlq->available = size;
	prlq->occupied = 0;
	prlq->relocatable = RLQ_NOT_RELOCATABLE;
	prlq->data = buffer;
}

inline void rlq_init_relocate(PRLQ prlq, unsigned int size, void *buffer)
{
	prlq->head = 0;
	prlq->tail = 0;
	prlq->size = size;
	prlq->available = size;
	prlq->occupied = 0;
	prlq->relocatable = RLQ_RELOCATABLE;
	prlq->data = buffer;
}

inline void rlq_clear(PRLQ prlq)
{
	bzero(prlq->data, prlq->size);
	prlq->head = 0;
	prlq->tail = 0;
	prlq->available = prlq->size;
	prlq->occupied = 0;
}

inline unsigned int jjwu_rlq_enqueue(PRLQ prlq, const void *src, unsigned int size)
{
	unsigned int copy_size = 0;

	if (prlq->data != NULL)
	{
		if (prlq->available > size)
			copy_size = size;
		else
			copy_size = prlq->available;

		memcpy(prlq->data+prlq->head, src, copy_size);
		prlq->head += copy_size;
		prlq->available -= copy_size;
		prlq->occupied += copy_size;
	}

	return copy_size;
}

inline void rlq_relocate(PRLQ prlq)
{
	if (prlq->occupied != 0)
	{
		if (prlq->tail != 0)
		{
			unsigned int size = prlq->occupied;
			void *tmp = calloc(size, 1);

			if (tmp != NULL)
			{
				memcpy(tmp, prlq->data+prlq->tail, size);
				rlq_clear(prlq);
				jjwu_rlq_enqueue(prlq, tmp, size);
			}

			free(tmp);
		}
	}
	else
	{
		rlq_clear(prlq);
	}
}

inline unsigned int rlq_enqueue(PRLQ prlq, const void *src, unsigned int size)
{
	if (prlq->relocatable)
		rlq_relocate(prlq);

	return jjwu_rlq_enqueue(prlq, src, size);
}

inline unsigned int jjwu_rlq_dequeue(PRLQ prlq, void *dest, unsigned int size)
{
	unsigned int copy_size = 0;

	if (prlq->data != NULL)
	{
		if (prlq->occupied > size)
			copy_size = size;
		else
			copy_size = prlq->occupied;

		memcpy(dest, prlq->data+prlq->tail, copy_size);
		prlq->tail += copy_size;
		prlq->occupied -= copy_size;
	}

	return copy_size;
}

inline unsigned int rlq_dequeue(PRLQ prlq, void *dest, unsigned int size)
{
	unsigned int dequeue_size = jjwu_rlq_dequeue(prlq, dest, size);

	if (prlq->relocatable)
		rlq_relocate(prlq);

	return dequeue_size;
}

inline int rlq_empty(PRLQ prlq)
{
	return (prlq->occupied == 0);
}

inline int rlq_full(PRLQ prlq)
{
	return (prlq->head >= prlq->size);
}

inline void rlq_calloc(PRLQ prlq)
{
	prlq->data = calloc(prlq->size, 1);
}

inline void rlq_free(PRLQ prlq)
{
	free(prlq->data);
	prlq->head = 0;
	prlq->tail = 0;
	prlq->size = 0;
	prlq->available = 0;
	prlq->occupied = 0;
	prlq->data = NULL;
}

inline void rlq_dump(PRLQ prlq)
{
	printf("++++++++++++++++++++++++++++++++++++++++RLQ DUMP++++++++++++++++++++++++++++++++++++++++\n");

	if (prlq->occupied != 0)
	{
		char *buf = calloc(prlq->size, 1);
		int index = 0;

		memcpy(buf, prlq->data+prlq->tail, prlq->occupied);
		
		for (index = 0 ; index != prlq->occupied ; index++)
		{
			if (index != 0 && (index % 0x10 == 0))
				printf("\n");

			printf("0x%02X ", buf[index]);
		}

		free(buf);
	}

	printf("\n++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n");
}

inline void rlq_statistics(PRLQ prlq)
{
	printf("head: %u\n", prlq->head);
	printf("tail: %u\n", prlq->tail);
	printf("size: %u\n", prlq->size);
	printf("available: %u\n", prlq->available);
	printf("occupied: %u\n", prlq->occupied);
	printf("relocatable: %u\n", prlq->relocatable);
}

#endif
