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



void LetTheHungerGamesBegin(Person** first);
void InitTheHungerGames(Person** first);
void AddPerson(Person* newPerson, Person** first);
void FreeAll(Person** first);
void FreePerson(Person* person);

//void Print(Person* person);



int main()
{
	Person* firstPerson = NULL;
	InitTheHungerGames(&firstPerson);
	LetTheHungerGamesBegin(&firstPerson);

	return 0;
}

void InitTheHungerGames(Person** first)
{
	int choice;

	Person* head = *first;
	printf("Add a person to the game? 1 for yes, 0 for no\n");
	scanf("%d", &choice);
	if (!choice)
		exit(0);
	while (choice)
	{
		Person* newPerson = (Person*)malloc(sizeof(Person));
		if (newPerson == NULL)
		{
			FreeAll(first);
			exit(1);
		}
		AddPerson(newPerson,first);
		if (head == NULL)
		{
			head = newPerson;
			*first = newPerson;
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
	head->nextPerson = *first;
	//Print(first);

	return;
}

void AddPerson(Person* newPerson, Person** first)
{
	char cBuff[80];
	int iBuff, i;
	printf("name:\n");
	scanf("%s", cBuff);
	newPerson->name = (char*)malloc(strlen(cBuff)+1);
	if (newPerson->name == NULL)
	{
		FreeAll(first);
		exit(1);
	}
	strcpy(newPerson->name, cBuff);
	printf("id:\n");
	scanf("%d", &iBuff);
	newPerson->id = iBuff;
	printf("num of kids:\n");
	scanf("%d", &iBuff);
	if (iBuff > 0)
	{
		newPerson->kids = (char**)malloc((iBuff + 1) * sizeof(char*));
		if (newPerson->kids == NULL)
		{
			FreeAll(first);
			exit(1);
		}
		for (i = 0;i < iBuff;i++)
		{
			printf("kid number %d name:\n", i + 1);
			scanf("%s", cBuff);
			newPerson->kids[i] = (char*)malloc(strlen(cBuff) + 1);
			if (newPerson->kids[i] == NULL)
			{
				FreeAll(first);
				exit(1);
			}
			strcpy(newPerson->kids[i], cBuff);
		}
		newPerson->kids[iBuff] = NULL;
	}
	else
		newPerson->kids = NULL;
}




void LetTheHungerGamesBegin(Person** first)
{
	Person* current = *first;
	Person* next = current->nextPerson;
	Person* temp;
	while (current->nextPerson != current)
	{
		int i = 0;
		printf("%s kills %s", current->name, next->name);
		if (next->kids != NULL)
		{
			while (next->kids[i] != NULL)
			{
				printf(" and %s", next->kids[i++]);
			}
		}
		printf("\n");
		temp = next;
		current->nextPerson = next->nextPerson;
		current = next->nextPerson;
		next = current->nextPerson;
		FreePerson(temp);
	}
	printf("%s stayin alive!!\n", current->name);
	FreePerson(current);
}

void FreeAll(Person** first)
{
	Person* person = *first;
	do
	{
		free(person->name);
		if (person->kids != NULL)
		{
			int i;
			while (person->kids[i] != NULL)
			{
				free(person->kids[i++]);
			}
			free(person->kids);
		}
		free(person);
	} while (person->nextPerson != person || person->nextPerson == NULL);
}

void FreePerson(Person* person)
{
	free(person->name);
	if (person->kids != NULL)
	{
		int i = 0;
		while (person->kids[i] != NULL)
		{
			free(person->kids[i++]);
		}
		free(person->kids);
	}
	free(person);
}

/* For linked list debugging purposes only. NOT part of the program.

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
				printf("kid %d: %s\n", i + 1, person->kids[i++]);
			}
		}
		person = person->nextPerson;

	} while (person != firstPerson);
}*/
