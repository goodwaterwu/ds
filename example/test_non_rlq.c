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

#include <stdio.h>
#include <stdlib.h>
#include "jjwu_rlq.h"

#define RLQ_SIZE 100
#define SEPARATOR()\
	printf("\n------------------------------------------------------------------------------------------\n\n")

struct student
{
	char name[32];
	int num;
};

int main(int argc, const char *argv[])
{
	RLQ_INIT(rlq, RLQ_SIZE);
	char tmp[RLQ_SIZE] = {0};
	char str[] = "This ia a test for rlq.";
	int num = 100;
	struct student victor = { "Victor", 1 };
	char buf[RLQ_SIZE] = { 0 };

	SEPARATOR();

	printf("rlq_full(&rlq): %d\n", rlq_full(&rlq));
	printf("rlq_empty(&rlq): %d\n", rlq_empty(&rlq));
	
	SEPARATOR();

	memset(tmp, 1, RLQ_SIZE);
	printf("rlq_enqueue(&rlq, tmp, RLQ_SIZE)\n\n");
	rlq_enqueue(&rlq, tmp, RLQ_SIZE);
	rlq_dump(&rlq);
	rlq_statistics(&rlq);

	SEPARATOR();

	printf("rlq_full(&rlq): %d\n", rlq_full(&rlq));
	printf("rlq_empty(&rlq): %d\n", rlq_empty(&rlq));

	SEPARATOR();

	printf("rlq_clear(&rlq)\n");
	rlq_clear(&rlq);
	printf("rlq_full(&rlq): %d\n", rlq_full(&rlq));
	printf("rlq_empty(&rlq): %d\n", rlq_empty(&rlq));

	SEPARATOR();

	printf("rlq_enqueue(&rlq, str, strlen(str))\n\n");
	rlq_enqueue(&rlq, str, strlen(str));
	rlq_dump(&rlq);
	rlq_statistics(&rlq);

	SEPARATOR();

	printf("rlq_enqueue(&rlq, &num, sizeof(int))\n\n");
	rlq_enqueue(&rlq, &num, sizeof(int));
	rlq_dump(&rlq);
	rlq_statistics(&rlq);

	SEPARATOR();

	printf("rlq_enqueue(&rlq, &victor, sizeof(struct student))\n\n");
	rlq_enqueue(&rlq, &victor, sizeof(struct student));
	rlq_dump(&rlq);
	rlq_statistics(&rlq);

	SEPARATOR();

	printf("rlq_dequeue(&rlq, buf, strlen(str))\n\n");
	rlq_dequeue(&rlq, buf, strlen(str));
	printf("buf: %s\n", buf);
	rlq_dump(&rlq);
	rlq_statistics(&rlq);

	SEPARATOR();

	bzero(buf, RLQ_SIZE);
	printf("rlq_dequeue(&rlq, buf, sizeof(int))\n\n");
	rlq_dequeue(&rlq, buf, sizeof(int));
	rlq_dump(&rlq);
	rlq_statistics(&rlq);

	SEPARATOR();

	bzero(buf, RLQ_SIZE);
	printf("rlq_dequeue(&rlq, buf, sizeof(struct student))\n\n");
	rlq_dequeue(&rlq, buf, sizeof(struct student));
	rlq_dump(&rlq);
	rlq_statistics(&rlq);
	rlq_free(&rlq);

	return 0;
}
