#include "commands.h"
#include "assert.h"

TelephoneBookList * commandLoad(char * fileName)
{
	FILE * fp;
	char item[100];
	char * token;

	TelephoneBookNode * node;
	TelephoneBookList * list = createTelephoneBookList();
	
	assert(list != NULL);
	fp =fopen(fileName,"r");
	if (!fp)
	{
		return 0;
	}
	while(fgets(item,sizeof(item),fp))
	{
		if (item[0] != '#')
		{
			node = createTelephoneBookNode();
			assert(node != NULL);
			node->id = atoi(strtok(item,DELIMS));

			token = strtok(NULL,DELIMS);
			strcpy(node->name,token);

			token = strtok(NULL,DELIMS);
			strncpy(node->telephone,token,strlen(token)-1);

			node->nextNode = NULL;
			insert(list,node);
		}
		else{
			continue;
		}
	}
    openFileDesc(list,fileName);
	fclose(fp);
	return list;
}

void commandUnload(TelephoneBookList * list)
{
	freeTelephoneBookList(list);
}

void commandDisplay(TelephoneBookList * list)
{
	int serial = NODE_MINIMUM_ID;
	char * cur =" ";
	TelephoneBookNode * current = list->head;
	printf("--------------------------------------------\n");
	printf("|Pos|Serial|  ID  |   Name   |  Telephone  |\n");
	printf("--------------------------------------------\n");
	while(current != NULL )
	{
		if(current->id == list->current->id)
		{
			cur = "CUR";
		}
		else{
			cur = " ";
		}
		printf("|%3s|%6d|%6d|%10s|%13s|\n",cur,serial,current->id,
			current->name,
			current->telephone);
		current = current->nextNode;
		serial++;
	}
	printf("--------------------------------------------\n");
	printf("| Total phone book entries: %d             |\n",list->size);
	printf("--------------------------------------------\n");
	

}

void commandForward(TelephoneBookList * list, int moves)
{
	forward(list,moves);
}

void commandBackward(TelephoneBookList * list, int moves)
{
	backward(list,moves);
}

void commandInsert(TelephoneBookList * list, int id, char * name, char * telephone)
{
	TelephoneBookNode * newNode = createTelephoneBookNode();
	newNode->id = id;
	strcpy(newNode->name,name);
	strcpy(newNode->telephone,telephone);
	newNode->nextNode = NULL;
	insert(list,newNode);
}

void commandFind(TelephoneBookList * list, char * name)
{
	TelephoneBookNode * foundNameNode = findByName(list,name);

	if (foundNameNode != NULL)
	{
		list->current = foundNameNode;
	}
	else
	{
		printf("Unable to find [%s] in the list.\n",name);
	}
}

void commandDelete(TelephoneBookList * list)
{
	delete(list);
}

void commandReverse(TelephoneBookList * list)
{
	TelephoneBookNode * temp;
	TelephoneBookNode * current = list->head;

	while(current != NULL){
		temp = current->nextNode;
		current->nextNode = current->previousNode;
		current->previousNode = temp;
		current = temp;
	}
	temp = list->head;
	list->head = list->tail;
	list->tail = temp;
}

void commandSave(TelephoneBookList * list, char * fileName)
{
	FILE * file;
	TelephoneBookNode * current = list->head;

	file = fopen(fileName,"w+");
	while(current != NULL)
	{
		fprintf(file, "%d, %s, %s\n",current->id,current->name,current->telephone );
		current = current->nextNode;
	}

	fclose(file);
	
}

void commandSortName(TelephoneBookList * list)
{
	TelephoneBookNode * temp = NULL;
	TelephoneBookNode * head = list->head;
	TelephoneBookNode * headNext = list->head->nextNode;
	while(headNext != NULL){
		while(head != headNext){
			if(head->name[0] < headNext->name[0])
			{
				temp = head;
				printf("-1%s\n",temp->name);
				printf("2%s\n",head->name);
				printf("3%s\n",headNext->name);
				head = headNext;
				printf("-1%s\n",temp->name);
				printf("2%s\n",head->name);
				printf("3%s\n",headNext->name);
				headNext = temp;
				printf("-1%s\n",temp->name);
				printf("2%s\n",head->name);
				printf("3%s\n",headNext->name);
			}
			head = head->nextNode;
		}
		head = list->head;
		headNext = headNext->nextNode;
	}

}

void commandSortRandom(TelephoneBookList * list)
{

}

void openFileDesc(TelephoneBookList * list,char * fileName){
    printf("> Open the file %s.\n",fileName);
    printf("> Loading the file ... \n");
    printf("> %d phone book entries have been loaded from the file.\n",(*list).size);
    printf("> Closing the file.\n\n");
}
