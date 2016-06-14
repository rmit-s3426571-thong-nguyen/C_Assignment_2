#include "addressbook.h"

int main(int argc, char ** argv)
{
	FILE *fp;
	int id;
	char name[20];
	char telephone[15];
	int moves = 0;
	char fileInName[100];
	char *readin;
	char *token;
	char load[80];
	struct telephoneBookList * list;
	TelephoneBookNode * nodeID;
	showStudentInfo();
	if (argc > 0)
	{
		if ((fp = fopen(argv[1],"r")) != NULL)
		{
			strcpy(fileInName,argv[1]);
			printf("> File name specified through the command-line argument.\n");
			list = commandLoad(fileInName);
		}
	}
	while(TRUE){
		printf("Enter your command: ");	
		readin = fgets(load,100,stdin);
		load[strlen(readin) - 1] = '\0';
		token = strtok(readin,DELIMS);
		if (token == NULL)
		{
			printf("> Invalid input\n");
			continue;	
		}
		else
		{
			if (strcmp(token,COMMAND_LOAD) == 0)
			{
				token = strtok(NULL,DELIMS);
				if (token == NULL)
				{
					printf("> Invalid input\n");
					printf("> Usage: load filename.txt\n");
					continue;	
				}
				strncpy(fileInName,token,100);
				fp = fopen(fileInName,"r");
				list = commandLoad(fileInName);
			}
			else if (strcmp(token,COMMAND_DISPLAY) == 0 && (fp != NULL))	
			{
				commandDisplay(list);

			}
			else if (strcmp(token,COMMAND_UNLOAD) == 0 && (fp != NULL))
			{
				commandUnload(list);
			}
			else if (strcmp(token,COMMAND_FORWARD) == 0 && (fp != NULL))
			{
				token = strtok(NULL,DELIMS);
				if (token == NULL)
				{
					printf("> Invalid input\n");
					printf("> Usage: forward <a number>\n");
					continue;	
				}
				moves = atoi(token);
				commandForward(list,moves);
			}
			else if (strcmp(token,COMMAND_BACKWARD) == 0 && (fp != NULL))
			{
				token = strtok(NULL,DELIMS);
				if (token == NULL)
				{
					printf("> Invalid input\n");
					printf("> Usage: backward <a number>\n");
					continue;	
				}
				moves = atoi(token);
				commandBackward(list,moves);
			}
			else if(strcmp(token,COMMAND_INSERT) == 0 && (fp != NULL))
			{
				id = atoi(strtok(NULL,DELIMS));
				nodeID = findByID(list,id);
				if(nodeID) {
					printf("Sorry,please enter an unique ID.\n");
					continue;
				}
				else
				{
					token = strtok(NULL,DELIMS);
					strcpy(name,token);
					token = strtok(NULL,DELIMS);
					strcpy(telephone,token);
					commandInsert(list,id,name,telephone);
				}
			}
			else if(strcmp(token,COMMAND_FIND) == 0 && (fp != NULL))
			{
				token = strtok(NULL,DELIMS);
				if (token == NULL)
				{
					printf("> Invalid input\n");
					printf("> Usage: find name\n");
					continue;	
				}
				strcpy(name,token);
				commandFind(list,name);
			}
			else if(strcmp(token,COMMAND_DELETE) == 0 && (fp != NULL))
			{
				if(list->head == NULL)
				{
					printf("List is empty.\n");
				}
				else
				{
					commandDelete(list);
				}
				
			}
			else if(strcmp(token,COMMAND_REVERSE) == 0 && (fp != NULL))
			{
				commandReverse(list);
			}
			else if(strcmp(token,COMMAND_SORT_NAME) == 0 && (fp != NULL))
			{
				commandSortName(list);
			}
			else if(strcmp(token,COMMAND_SAVE) == 0 && (fp != NULL))
			{
				commandSave(list,fileInName);
			}
			else if(strcmp(token,COMMAND_QUIT) == 0 )
			{
				break;
			}
			else{
				printf(">Invalid input\n");
			}
		}
	}
	if(fp != NULL){
		fclose(fp);
	}
	printf("> Goodbye. \n\n");
	return EXIT_SUCCESS;
	
}


void showStudentInfo()
{
	printf("-------------------------------------------------------------------\n");
	printf("Student Name : %s\n",STUDENT_NAME);
	printf("Student ID : %s\n",STUDENT_ID);
	printf("%s\n",COURSE_INFO);
	printf("-------------------------------------------------------------------\n");
}

