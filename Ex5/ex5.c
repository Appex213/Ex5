#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>


typedef struct {
	char* name;
	char** kids;
	int id;
	struct Person* nextPerson;
} Person;




void InitTheHungerGames(Person* first);
void AddPerson(Person* newPerson);
void Print(Person* person);



int main()
{
	Person* firstPerson = NULL;
	InitTheHungerGames(firstPerson);
	LetTheHungerGamesBegin(firstPerson);

	return 0;
}

void InitTheHungerGames(Person* first)
{
	int choice;

	Person* head = first;
	printf("Add a person to the game? 1 for yes, 0 for no\n");
	scanf("%d", &choice);
	if (!choice)
		exit(0);
	while (choice)
	{
		Person* newPerson = (Person*)malloc(sizeof(Person));
		if (newPerson == NULL)
			exit(1);
		AddPerson(newPerson);
		if (head == NULL)
		{
			head = newPerson;
			first = newPerson;
			head->nextPerson = NULL;
		}
		else
		{
			head->nextPerson = newPerson;
			head = newPerson;
			head->nextPerson = NULL;
		}
		printf("Add a person to the game? 1 for yes, 0 for no\n");
		scanf("%d", &choice);

	}
	Print(first);

	return;
}

void AddPerson(Person* newPerson)
{
	char cBuff[80];
	int iBuff, i;
	printf("name:\n");
	scanf("%s", cBuff);
	newPerson->name = (char*)malloc(strlen(cBuff));
	if (newPerson->name == NULL)
		exit(1);
	strcpy(newPerson->name, cBuff);
	printf("id:\n");
	scanf("%d", &iBuff);
	newPerson->id = iBuff;
	printf("num of kids:\n");
	scanf("%d", &iBuff);
	if (iBuff > 0)
	{
		newPerson->kids = (char**)malloc(iBuff * sizeof(char*));
		for (i = 0;i < iBuff;i++)
		{
			printf("kid number %d name:\n", i+1);
			scanf("%s", cBuff);
			newPerson->kids[i] = (char*)malloc(strlen(cBuff));
			strcpy(newPerson->kids[i], cBuff);
		}
		newPerson->kids[iBuff] = NULL;
	}
	


}




void LetTheHungerGamesBegin(Person* first)
{


}

void Print(Person* person)
{
	Person* firstPerson = person;

	do
	{
		int i = 0;
		printf("name: %s\n", person->name);
		printf("id: %d\n", person->id);
		if (person->kids != NULL)
		{
			while (person->kids[i] != NULL)
			{
				printf("kid %d: %s\n", i + 1, person->kids[i]);
				i++;
			}
		}
		person = person->nextPerson;

	} while (person != NULL);
}
