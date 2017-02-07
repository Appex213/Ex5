/******************************************
* Matan Ben Moshe
* 208583070
* 83-120-04
* ex5.c
******************************************/
/*-------------------------------------------------Github Commit RC1-------------------------------------------------*/
/*---Libraries---*/
// Standard library
#include <stdio.h>
// For exit() function
#include <stdlib.h>
// For string manipulation (mainly strcpy)
#include <string.h>
// Dynamic allocation library
#include <malloc.h>

/*---Struct definition---*/
typedef struct {
	char* name;
	char** kids;
	int id;
	struct Person* nextPerson;
} Person;

/*---Function Decleration---*/
void LetTheHungerGamesBegin(Person** first);
void InitTheHungerGames(Person** first);
void AddPerson(Person* newPerson, Person** first);
void FreeAll(Person** first);
void FreePerson(Person* person);


/*********************************************************************************************
Function name: Main
Input: none
Output: none
The function operation: Manages other functions.
**********************************************************************************************/
int main()
{
	// Pointer to first element
	Person* firstPerson = NULL;
	InitTheHungerGames(&firstPerson);
	// In case no people were added
	if (firstPerson == NULL)
		return 0;
	LetTheHungerGamesBegin(&firstPerson);

	return 0;
}

/*********************************************************************************************
Function name: InitTheHungerGames
Input: Pointer to pointer of first person in the list 
Output: none
The function operation: Initializes the game. Adds people to the list and calls to AddPerson to add data.
						In case of no people quits the game.
**********************************************************************************************/
void InitTheHungerGames(Person** first)
{
	int choice;
	// Last person (or head) of the list
	Person* head = *first;
	printf("Add a person to the game? 1 for yes, 0 for no\n");
	scanf("%d", &choice);
	// if choice is 0 - no people
	if (!choice)
		return;
	while (choice)
	{
		// Allocate memory for a person
		Person* newPerson = (Person*)malloc(sizeof(Person));
		// Allocation failure check
		if (newPerson == NULL)
		{
			FreeAll(first);
			exit(1);
		}
		// Add person data to the created person
		AddPerson(newPerson,first);
		// First person
		if (head == NULL)
		{
			head = newPerson;
			// Make first point to the first person
			*first = newPerson;
			head->nextPerson = NULL;
		}
		else
		{
			// Move the head foward
			head->nextPerson = newPerson;
			head = newPerson;
			head->nextPerson = NULL;
		}
		printf("Add a person to the game? 1 for yes, 0 for no\n");
		scanf("%d", &choice);
	}
	// "Tie" the ends together to create a circular list
	head->nextPerson = *first;
	return;
}

/*********************************************************************************************
Function name: AddPerson
Input: Pointers to newly added person and first person on the list
Output: 
The function operation: 
**********************************************************************************************/
void AddPerson(Person* newPerson, Person** first)
{
	char cBuff[80];
	int iBuff, i;
	printf("name:\n");
	scanf("%s", cBuff);
	// Allocate memory for name
	newPerson->name = (char*)malloc(strlen(cBuff)+1);
	// Allocation failure check
	if (newPerson->name == NULL)
	{
		FreeAll(first);
		exit(1);
	}
	// Copy name from buffer to allocated memory
	strcpy(newPerson->name, cBuff);
	printf("id:\n");
	scanf("%d", &iBuff);
	newPerson->id = iBuff;
	printf("num of kids:\n");
	scanf("%d", &iBuff);
	if (iBuff > 0)
	{
		// Create an array if strings (array of char* pointers)
		newPerson->kids = (char**)malloc((iBuff + 1) * sizeof(char*));
		// Allocation failure check
		if (newPerson->kids == NULL)
		{
			FreeAll(first);
			exit(1);
		}
		for (i = 0;i < iBuff;i++)
		{
			printf("kid number %d name:\n", i + 1);
			scanf("%s", cBuff);
			// Allocate memory for kid name
			newPerson->kids[i] = (char*)malloc(strlen(cBuff) + 1);
			// Allocation failure check
			if (newPerson->kids[i] == NULL)
			{
				FreeAll(first);
				exit(1);
			}
			// Copy name from buffer to allocated memory
			strcpy(newPerson->kids[i], cBuff);
		}
		// Make the pointer after the last kid nullptr (for future use)
		newPerson->kids[iBuff] = NULL;
	}
	else
		// In case of no kids - make kids point to NULL
		newPerson->kids = NULL;
	return;
}

/*********************************************************************************************
Function name: LetTheHungerGamesBegin
Input: Pointer to "first" person (added first)
Output: none
The function operation: Game logic function. Make first person kill the next, moves pointers along and repeat untill one person remains.
						Prints kill messages and winning message accordingly.
						Calls to FreePerson when a person is killed to release allocated memory.
**********************************************************************************************/
void LetTheHungerGamesBegin(Person** first)
{
	// Killer
	Person* current = *first;
	// The one who's about to die (killee?)
	Person* next = current->nextPerson;
	Person* temp;
	// While noone points to himself (one person remaining)
	while (current->nextPerson != current)
	{
		int i = 0;
		// i.e "man1 kills man2"
		printf("%s kills %s", current->name, next->name);
		// If kids pointer isn't NULL (=no kids, line 162)
		if (next->kids != NULL)
		{
			// Loop untill reaching NULL pointer (line 158)
			while (next->kids[i] != NULL)
			{
				// i.e "and kid1 and kid2", and then increment i
				printf(" and %s", next->kids[i++]);
			}
		}
		printf("\n");
		// Store address of killed person in temp
		temp = next;
		// Make killer point to the person after the dead person
		current->nextPerson = next->nextPerson;
		// Move killer pointer to the person after the killed person
		current = next->nextPerson;
		// Make soon-to-be-killed pointer point to the person after the next killer
		next = current->nextPerson;
		// Free allocated memory of address stored in temp (the dead guy)
		FreePerson(temp);
	}
	printf("%s stayin alive!!\n", current->name);
	// Free the winner
	FreePerson(current);
	return;
}

/*********************************************************************************************
Function name: FreeAll	
Input: Pointer to first person
Output: none
The function operation: In case of memory allocation failure, start from the first person and free everything so that the program can be terminated cleanly.
**********************************************************************************************/
void FreeAll(Person** first)
{
	Person* person = *first;
	Person* temp;
	// Free all dynamicly allocated memory in order:
	do
	{
		// Free name
		free(person->name);
		// If there are kids
		if (person->kids != NULL)
		{
			int i = 0;
			while (person->kids[i] != NULL)
			{
				// Free kids names in order
				free(person->kids[i++]);
			}
			// And then free kids name's array pointer
			free(person->kids);
		}
		// Store the address of the next person in the list
		temp = person->nextPerson;
		// Free the person struct itself
		free(person);
		// use the stored address to move person to the next person
		person = temp;
	// continue untll the end of the list
	} while (person->nextPerson == NULL);
	return;
}

/*********************************************************************************************
Function name: FreePerson
Input: Dead person pointer
Output: none
The function operation: When someone is killed, frees dynamicly allocated memory of that person. (also when someone wins)
**********************************************************************************************/
void FreePerson(Person* person)
{
	// Free name
	free(person->name);
	// If there are kids
	if (person->kids != NULL)
	{
		int i = 0;
		while (person->kids[i] != NULL)
		{
			// Free kids names in order
			free(person->kids[i++]);
		}
		// And then free kids name's array pointer
		free(person->kids);
	}
	// Free the person struct itself
	free(person);
	return;
}