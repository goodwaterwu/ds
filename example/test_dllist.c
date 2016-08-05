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
#include "jjwu_dllist.h"

#define NUM 8
#define SEPARATOR() printf("\n--------------------------------------------------\n\n")

struct test
{
	char *name;
	int number;
	DLLIST dllist;
};

int main(int argc, const char *argv[])
{
	struct test *s = (struct test*)malloc(sizeof(struct test)*NUM);
	struct test *data = NULL;
	PDLLIST node = NULL;
	int num = 0;

	DLLIST_INIT(dllist);
	DLLIST_INIT(sec_dllist);

	s[num].name = "John";
	s[num].number = num;
	num++;
	s[num].name = "Victor";
	s[num].number = num;
	num++;
	s[num].name = "Joseph";
	s[num].number = num;
	num++;
	s[num].name = "Stephen";
	s[num].number = num;
	num++;
	s[num].name = "Allen";
	s[num].number = num;
	num++;
	s[num].name = "Joanna";
	s[num].number = num;
	num++;
	s[num].name = "Allison";
	s[num].number = num;
	num++;
	s[num].name = "Selina";
	s[num].number = num;

	SEPARATOR();

	for (num = 0 ; num != NUM ; num++)
	{
		if (num % 2 == 0)
		{
			dllist_addnode(&dllist, &s[num].dllist, &s[num]);
			printf("dllist_addnode(&dllist, &s[%d].dllist, &s[%d])\n", num, num);
		}
		else
		{
			dllist_addnode_tail(&dllist, &s[num].dllist, &s[num]);
			printf("dllist_addnode_tail(&dllist, &s[%d].dllist, &s[%d])\n", num, num);
		}
	}

	printf("\ndllist_for_each_node(&dllist, node):\n\n");

	dllist_for_each_node(&dllist, node)
	{
		struct test *d = (struct test*)dllist_entry(node);

		printf("d->name=%s\n", d->name);
		printf("d->number=%d\n", d->number);
	}

	SEPARATOR();

	printf("dllist_for_each_node_prior(&dllist, node):\n\n");

	dllist_for_each_node_prior(&dllist, node)
	{
		struct test *d = (struct test*)dllist_entry(node);

		printf("d->name=%s\n", d->name);
		printf("d->number=%d\n", d->number);
	}

	SEPARATOR();

	printf("dllist_for_each_node_next(&dllist, node):\n\n");

	dllist_for_each_node_next(&dllist, node)
	{
		struct test *d = (struct test*)dllist_entry(node);

		printf("d->name=%s\n", d->name);
		printf("d->number=%d\n", d->number);
	}

	SEPARATOR();

	printf("dllist_for_each_entry(&dllist, node, data):\n\n");

	dllist_for_each_entry(&dllist, node, data)
	{
		printf("data->name=%s\n", data->name);
		printf("data->number=%d\n", data->number);
	}

	SEPARATOR();

	printf("dllist_for_each_entry_prior(&dllist, node, data):\n\n");

	dllist_for_each_entry_prior(&dllist, node, data)
	{
		printf("data->name=%s\n", data->name);
		printf("data->number=%d\n", data->number);
	}

	SEPARATOR();

	printf("dllist_for_each_entry_next(&dllist, node, data):\n\n");

	dllist_for_each_entry_next(&dllist, node, data)
	{
		printf("data->name=%s\n", data->name);
		printf("data->number=%d\n", data->number);
	}

	SEPARATOR();

	dllist_deletenode(&s[0].dllist);

	printf("dllist_deletenode(&s[0]->dllist):\n");
	printf("\ndllist:\n\n");

	dllist_for_each_entry(&dllist, node, data)
	{
		printf("data->name=%s\n", data->name);
		printf("data->number=%d\n", data->number);
	}

	SEPARATOR();

	dllist_movenode(&sec_dllist, &s[1].dllist);

	printf("dllist_movenode(&sec_dllist, &s[1]->dllist):\n");
	printf("\ndllist:\n\n");

	dllist_for_each_entry(&dllist, node, data)
	{
		printf("data->name=%s\n", data->name);
		printf("data->number=%d\n", data->number);
	}

	printf("\nsec_dllist:\n\n");

	dllist_for_each_entry(&sec_dllist, node, data)
	{
		printf("data->name=%s\n", data->name);
		printf("data->number=%d\n", data->number);
	}

	SEPARATOR();

	dllist_movenode(&sec_dllist, &s[2].dllist);

	printf("dllist_movenode(&sec_dllist, &s[2]->dllist):\n");
	printf("\ndllist:\n\n");

	dllist_for_each_entry(&dllist, node, data)
	{
		printf("data->name=%s\n", data->name);
		printf("data->number=%d\n", data->number);
	}

	printf("\nsec_dllist:\n\n");

	dllist_for_each_entry(&sec_dllist, node, data)
	{
		printf("data->name=%s\n", data->name);
		printf("data->number=%d\n", data->number);
	}

	SEPARATOR();

	dllist_movenode_tail(&sec_dllist, &s[3].dllist);

	printf("dllist_movenode_tail(&sec_dllist, &s[3]->dllist):\n");
	printf("\ndllist:\n\n");

	dllist_for_each_entry(&dllist, node, data)
	{
		printf("data->name=%s\n", data->name);
		printf("data->number=%d\n", data->number);
	}

	printf("\nsec_dllist:\n\n");

	dllist_for_each_entry(&sec_dllist, node, data)
	{
		printf("data->name=%s\n", data->name);
		printf("data->number=%d\n", data->number);
	}

	SEPARATOR();

	dllist_movenode_next(&sec_dllist, &s[4].dllist);

	printf("dllist_movenode_next(&sec_dllist, &s[4]->dllist):\n");
	printf("\ndllist:\n\n");

	dllist_for_each_entry(&dllist, node, data)
	{
		printf("data->name=%s\n", data->name);
		printf("data->number=%d\n", data->number);
	}

	printf("\nsec_dllist:\n\n");

	dllist_for_each_entry(&sec_dllist, node, data)
	{
		printf("data->name=%s\n", data->name);
		printf("data->number=%d\n", data->number);
	}

	SEPARATOR();

	printf("dllist_empty(&dllist): %d\n", dllist_empty(&dllist));

	SEPARATOR();

	dllist_concat(&dllist, &sec_dllist);

	printf("dllist_concat(&dllist, &sec_dllist)\n");

	printf("\ndllist:\n\n");

	dllist_for_each_entry(&dllist, node, data)
	{
		printf("data->name=%s\n", data->name);
		printf("data->number=%d\n", data->number);
	}

	printf("\nsec_dllist:\n\n");

	dllist_for_each_entry(&sec_dllist, node, data)
	{
		printf("data->name=%s\n", data->name);
		printf("data->number=%d\n", data->number);
	}

	SEPARATOR();
	
	dllist_addnode(&sec_dllist, &s[0].dllist, &s[0]);
	dllist_movenode(&sec_dllist, &s[1].dllist);
	dllist_movenode(&sec_dllist, &s[2].dllist);
	dllist_movenode(&sec_dllist, &s[3].dllist);
	dllist_movenode(&sec_dllist, &s[4].dllist);

	printf("dllist_addnode(&sec_dllist, &s[0].dllist, &s[0])\n");
	printf("dllist_movenode(&sec_dllist, &s[1].dllist)\n");
	printf("dllist_movenode(&sec_dllist, &s[2].dllist)\n");
	printf("dllist_movenode(&sec_dllist, &s[3].dllist)\n");
	printf("dllist_movenode(&sec_dllist, &s[4].dllist)\n");

	printf("\ndllist:\n\n");

	dllist_for_each_entry(&dllist, node, data)
	{
		printf("data->name=%s\n", data->name);
		printf("data->number=%d\n", data->number);
	}

	printf("\nsec_dllist:\n\n");

	dllist_for_each_entry(&sec_dllist, node, data)
	{
		printf("data->name=%s\n", data->name);
		printf("data->number=%d\n", data->number);
	}

	SEPARATOR();

	dllist_concat_tail(&dllist, &sec_dllist);

	printf("dllist_concat_tail(&dllist, &sec_dllist)\n");

	printf("\ndllist:\n\n");

	dllist_for_each_entry(&dllist, node, data)
	{
		printf("data->name=%s\n", data->name);
		printf("data->number=%d\n", data->number);
	}

	printf("\nsec_dllist:\n\n");

	dllist_for_each_entry(&sec_dllist, node, data)
	{
		printf("data->name=%s\n", data->name);
		printf("data->number=%d\n", data->number);
	}

	SEPARATOR();

	dllist_movenode(&sec_dllist, &s[0].dllist);
	dllist_movenode(&sec_dllist, &s[1].dllist);
	dllist_movenode(&sec_dllist, &s[2].dllist);
	dllist_movenode(&sec_dllist, &s[3].dllist);
	dllist_movenode(&sec_dllist, &s[4].dllist);

	printf("dllist_movenode(&sec_dllist, &s[0].dllist)\n");
	printf("dllist_movenode(&sec_dllist, &s[1].dllist)\n");
	printf("dllist_movenode(&sec_dllist, &s[2].dllist)\n");
	printf("dllist_movenode(&sec_dllist, &s[3].dllist)\n");
	printf("dllist_movenode(&sec_dllist, &s[4].dllist)\n");

	printf("\ndllist:\n\n");

	dllist_for_each_entry(&dllist, node, data)
	{
		printf("data->name=%s\n", data->name);
		printf("data->number=%d\n", data->number);
	}

	printf("\nsec_dllist:\n\n");

	dllist_for_each_entry(&sec_dllist, node, data)
	{
		printf("data->name=%s\n", data->name);
		printf("data->number=%d\n", data->number);
	}

	SEPARATOR();

	printf("dllist_empty(&dllist):%d\n", dllist_empty(&dllist));
	printf("dllist_exist(&dllist, &s[0].dllist):%d\n", dllist_exist(&dllist, &s[0].dllist));
	printf("dllist_exist(&sec_dllist, &s[0].dllist):%d\n", dllist_exist(&sec_dllist, &s[0].dllist));

	SEPARATOR();

	free(s);

	return 0;
}
