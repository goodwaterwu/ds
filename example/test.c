#include <stdio.h>
#include <stdlib.h>
#include "jjwu_dllist.h"

#define NUM 8

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
	s[num].dllist.self = (struct test*)&s[num];
	num++;
	s[num].name = "Victor";
	s[num].number = num;
	s[num].dllist.self = (struct test*)&s[num];
	num++;
	s[num].name = "Joseph";
	s[num].number = num;
	s[num].dllist.self = (struct test*)&s[num];
	num++;
	s[num].name = "Stephen";
	s[num].number = num;
	s[num].dllist.self = (struct test*)&s[num];
	num++;
	s[num].name = "Allen";
	s[num].number = num;
	s[num].dllist.self = (struct test*)&s[num];
	num++;
	s[num].name = "Joanna";
	s[num].number = num;
	s[num].dllist.self = (struct test*)&s[num];
	num++;
	s[num].name = "Allison";
	s[num].number = num;
	s[num].dllist.self = (struct test*)&s[num];
	num++;
	s[num].name = "Selina";
	s[num].number = num;
	s[num].dllist.self = (struct test*)&s[num];

	for (num = 0 ; num != NUM ; num++)
	{
		if (num % 2 == 0)
			dllist_addnode(&dllist, &s[num].dllist);
		else
			dllist_addnode_tail(&dllist, &s[num].dllist);
	}

	printf("dllist_for_each_node(&dllist, node):\n");

	dllist_for_each_node(&dllist, node)
	{
		struct test *d = (struct test*)dllist_node(node);

		printf("d->name=%s\n", d->name);
		printf("d->number=%d\n", d->number);
	}

	printf("--------------------------------------------------\n");
	printf("dllist_for_each_node_prior(&dllist, node):\n");

	dllist_for_each_node_prior(&dllist, node)
	{
		struct test *d = (struct test*)dllist_node(node);

		printf("d->name=%s\n", d->name);
		printf("d->number=%d\n", d->number);
	}

	printf("--------------------------------------------------\n");
	printf("dllist_for_each_node_next:\n");

	dllist_for_each_node_next(&dllist, node)
	{
		struct test *d = (struct test*)dllist_node(node);

		printf("d->name=%s\n", d->name);
		printf("d->number=%d\n", d->number);
	}

	printf("--------------------------------------------------\n");
	printf("dllist_for_each_entry(&dllist, node, data):\n");

	dllist_for_each_entry(&dllist, node, data)
	{
		printf("data->name=%s\n", data->name);
		printf("data->number=%d\n", data->number);
	}

	printf("--------------------------------------------------\n");
	printf("dllist_for_each_entry_prior(&dllist, node, data):\n");

	dllist_for_each_entry_prior(&dllist, node, data)
	{
		printf("data->name=%s\n", data->name);
		printf("data->number=%d\n", data->number);
	}

	printf("--------------------------------------------------\n");
	printf("dllist_for_each_entry_next(&dllist, node, data):\n");

	dllist_for_each_entry_next(&dllist, node, data)
	{
		printf("data->name=%s\n", data->name);
		printf("data->number=%d\n", data->number);
	}

	printf("--------------------------------------------------\n");
	printf("dllist_deletenode(&u->dllist):\n");

	dllist_deletenode(&s[0].dllist);

	dllist_for_each_entry(&dllist, node, data)
	{
		printf("data->name=%s\n", data->name);
		printf("data->number=%d\n", data->number);
	}

	printf("--------------------------------------------------\n");
	printf("dllist_movenode(&sec_dllist, &s[1]->dllist):\n");

	dllist_movenode(&sec_dllist, &s[1].dllist);

	printf("dllist:\n");

	dllist_for_each_entry(&dllist, node, data)
	{
		printf("data->name=%s\n", data->name);
		printf("data->number=%d\n", data->number);
	}

	printf("sec_dllist:\n");

	dllist_for_each_entry(&sec_dllist, node, data)
	{
		printf("data->name=%s\n", data->name);
		printf("data->number=%d\n", data->number);
	}

	printf("--------------------------------------------------\n");
	printf("dllist_movenode(&sec_dllist, &s[2]->dllist):\n");

	dllist_movenode(&sec_dllist, &s[2].dllist);

	printf("dllist:\n");

	dllist_for_each_entry(&dllist, node, data)
	{
		printf("data->name=%s\n", data->name);
		printf("data->number=%d\n", data->number);
	}

	printf("sec_dllist:\n");

	dllist_for_each_entry(&sec_dllist, node, data)
	{
		printf("data->name=%s\n", data->name);
		printf("data->number=%d\n", data->number);
	}

	printf("--------------------------------------------------\n");
	printf("dllist_movenode_tail(&sec_dllist, &s[3]->dllist):\n");

	dllist_movenode_tail(&sec_dllist, &s[3].dllist);

	printf("dllist:\n");

	dllist_for_each_entry(&dllist, node, data)
	{
		printf("data->name=%s\n", data->name);
		printf("data->number=%d\n", data->number);
	}

	printf("sec_dllist:\n");

	dllist_for_each_entry(&sec_dllist, node, data)
	{
		printf("data->name=%s\n", data->name);
		printf("data->number=%d\n", data->number);
	}

	printf("--------------------------------------------------\n");
	printf("dllist_movenode_next(&sec_dllist, &s[4]->dllist):\n");

	dllist_movenode_next(&sec_dllist, &s[4].dllist);

	printf("dllist:\n");

	dllist_for_each_entry(&dllist, node, data)
	{
		printf("data->name=%s\n", data->name);
		printf("data->number=%d\n", data->number);
	}

	printf("sec_dllist:\n");

	dllist_for_each_entry(&sec_dllist, node, data)
	{
		printf("data->name=%s\n", data->name);
		printf("data->number=%d\n", data->number);
	}

	printf("--------------------------------------------------\n");

	printf("dllist_empty(&dllist): %d\n", dllist_empty(&dllist));

	printf("--------------------------------------------------\n");

	free(s);

	return 0;
}
