#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>


typedef struct {
	char* name;
	char** kids;
	int id;
} Person;

typedef struct {
	Person* person;
	int size;
	int topIndex;
} People;

void InitTheHungerGames(People* people);
void AddPerson(Person* person);


int main()
{
	People people;
	Person person;
	InitTheHungerGames(&people);

	return 0;
}

void InitTheHungerGames(People* people)
{
	int choice;
	Person* person = (Person*)malloc(10*sizeof(Person));
	people->person = person;
	people->size = 1;
	people->topIndex = -1;
	printf("Add a person to the game? 1 for yes, 0 for no\n");
	scanf("%d", &choice);
	while (choice)
	{
		AddPerson(people);
		printf("Add a person to the game? 1 for yes, 0 for no\n");
		scanf("%d", &choice);
	}



}

void AddPerson(People* peopleptr)
{
	Person* person = peopleptr->person;
	char cBuff[80];
	int iBuff, i;
	printf("name:\n");
	gets(cBuff);
	person->name = (char*)malloc(strlen(cBuff) + 1);
	printf("id:\n");
	scanf("%d", &iBuff);
	person->id = iBuff;
	printf("num of kids:\n");
	scanf("%d", &iBuff);
	if (iBuff > 0)
	{
		person->kids = (char**)malloc(iBuff * sizeof(char*));
		for (i = 1;i < iBuff;i++)
		{
			printf("kid number %d name:\n", i);
			gets(cBuff);
			person->kids[i] = (char*)malloc(strlen(cBuff));
			strcpy(person->kids[i], cBuff);
		}
	}

	


}



void LetTheHungerGamesBegin()
{

}

