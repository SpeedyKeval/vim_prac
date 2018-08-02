/******************************************************************************
* This system deals with hospital management system for the patient details
******************************************************************************/

/***********************************************************
*	@file		Hospital.c
*	@author		Keval Vora
*	@func.		Store data, update, edit and delete 
*			data. and store it in a file at any
*			point of exit. Forcefull exit should 
*			also be able to store data into file.
*	@date		26/07/2018
***********************************************************/

/*****************************************************************************
*	Patient Details
*	
*	1) Name
*	2) Age
*	3) Address
*	4) Symptoms	( 4 Max )
*****************************************************************************/

/*****************************************************************************
*		FUNCTIONALITIES OF THIS SYSTEM
*
*	1) edit
*	2) update
*	3) add
*	4) delete
*	5) store the data into file, at any type of exit(forced or normal).
*****************************************************************************/

/****************************************************************************
*		CONSTRAINTS
*
*	- name can have maximum 30 characters
*	- address can have maximum 100 characters
*	- symptoms a patient can have is 4 maximum
*	- symptoms can be added through update functionalities
****************************************************************************/

/****************************
*	HEADER 
****************************/

#include<string.h>
#include<stdio.h>
#include<stdlib.h>
#include<signal.h>
#include<ctype.h>

/***************************
*	MACROS
***************************/
#define NAMEMAX 30	// max character for name
#define ADDRESSMAX 100	// max character for address
#define SYM_MAX 4	// max number of symptoms

/**************************
*	STRUCTURES
**************************/

struct patient // patient details
{
	char name[NAMEMAX]; 		// patient name
	unsigned int age;		// patient age
	char address[ADDRESSMAX];		// address of patient
	char symptoms[SYM_MAX][NAMEMAX];	// symptoms of patient //max 4
};

struct record // register
{
	struct patient *sr_no;
	struct record *next;
};

struct record *head; // first record

struct sigaction controlcpressed; // to handle ctrl^c interrupt in c

/*************************
*	PROTOTYPES
*************************/

struct patient *newrecord();	// create new record
int add_record();		// add new record
int delete_record(char[]);	// delete the entire record of patient

int edit(char[], int);
void exit();
void show_record(void);		// test case, whether system is working
void store_file();
void signal_handler(int);
void buffer_clear();		// clear the buffer

/****************************
*	@function	main
*	@brief		main function of system
*	@date		26/07/2018
*	@param		void
*	@return		int
****************************/

int main()
{
	int user_choice, isDigit, result;
	// catch signal
	struct sigaction signalfound;

	// allocate memory to signalfound
	memset(&signalfound, 0, sizeof(signalfound));

	signalfound.sa_handler = &signal_handler;

	sigaction(SIGINT, &signalfound, &controlcpressed);
	
	// Menu for the System

	while (1)
	{

		printf("\n1) Add Record");
		printf("\n2) Delete Record");
		printf("\n3) Edit Record");
		printf("\n4) Exit");
		printf("\n5) Test Data:	");
		printf("\nEnter your choice operation: ");	
		// user input for choice
		isDigit = scanf("%d",&user_choice);
		if (isDigit == 1)
		{	
			switch(user_choice)
			{
				case 1:		// add record to list
				{
					result = add_record();
					if (result == 1)
					{
						printf("Record Added\n");
					}
					else
					{
						printf("Error\n");
					}
					break;
				}
				case 2:		// delete a record from list as per user input name
				{
					char  name[30];
					// user input for name
					printf("\nEnter Name of Patient for whom record in to be deleted: ");
					scanf(" %[^\n]s",name);
					result = delete_record(name);
					if (result == 1)
					{
						printf("Record Deleted\n");
					}
					else
					{
						printf("ERROR\n");
					}
					break;
				}
				case 3:		// edit function call
				{
					char name_change[30];
					int choice;
					printf("\n1) Edit name");
					printf("\n2) Edit age");
					printf("\n3) Edit address");
					printf("\n4) Edit symptoms\n");
					printf("\n Enter your choice: ");

					// enter choice for edit the record
					scanf("%d",&choice);
					
					if (choice > 4)
					{
						break;
					}
					// enter name of the patient for which record is to be modified
					printf("\n Enter name: ");
					scanf(" %[^\n]s",name_change);
					edit(name_change,choice);
					break;
				}
				case 4:
				{
				
					atexit(store_file);
					exit(2);
					break;
				}
				case 5:
				{
					show_record();
					break;
				}
				default:
				{
					printf("\nInvalid Choice && Enter digit only\n");
					buffer_clear();
					break;
				}
			}
			if (!flag)
			{
				break;
			}
		}
		else
		{
			printf("\nBad Input\nPlease insert number\n");
			buffer_clear();
		}
	}
}

/**************************
*	@function	newrecord
*	@brief		creates new instance of patient structure
*	@date		26/07/2018
*	@param		void
*	@return		return struct patient
***************************/

struct patient *newrecord()
{
	struct patient *new;
	int num, lvari, check;
	int age_add;
	char sentence[100];

	// memory allocation for "new"
	new = (struct patient*) malloc(sizeof(struct patient));
 
	// name of patient
	printf("Name: ");
	scanf(" %[^\n]s",new->name);

	// age of patient
	printf("\nAge: ");
	check = scanf("%d",&age_add);
	if (check != 1)
	{
		printf("\nPlease enter digits instead of characters\n");
		
		free (new);
		buffer_clear();
		return 0;
	}
	new->age = age_add;

	// address of patient
	printf("\nAddress: ");
	scanf(" %[^\n]s",new->address);

	// Number for symptoms
	printf("\nEnter number of symptoms to add(max 4): ");
	scanf("%d",&num);
	
	if (num < SYM_MAX+1)
	{
	// enter symptoms 
		for (lvari=0;lvari<num;lvari++)
		{
			scanf(" %[^\n]s",new->symptoms[lvari]);
		}
	}
	else
	{
		printf("please enter number below 5");
		return NULL;
	}
	return new;
}

/****************************
*	@function	add_record
*	@brief		adds new record
*	@date		26/07/2018
*	@param		void
*	@return		int 0 no data added; 1 data added
****************************/

int add_record()
{
	struct patient  *new;
	struct record *previous, *nextn;
	
	// assign head, to previous
	previous = head;

	// new record
	new = newrecord();

	if (new == NULL)
	{
		return 0;
	}
	else if (previous == NULL)
	{
		head = (struct record*)malloc(sizeof(struct record));
		head->sr_no = new;
		head->next = NULL;
		return 1;
	}
	else
	{
		nextn = (struct record*) malloc (sizeof(struct record));
		nextn->sr_no = new;
		while (previous->next != NULL)
		{
			previous = previous->next;
		}
		previous->next = nextn;
		return 1;
	}
}

/**************************
*	@function	show_record
*	@date		26/07/2018
*	@brief		show records for all patients
*	@param		void
*	@return		void
**************************/

void show_record()
{
	struct record *previous, *nextn;

	if (head != NULL)
	{
		previous = head;
		while (previous->next != NULL)
		{
			printf("%s\n",previous->sr_no->name);
			previous = previous->next;
		}
		printf("%s\n",previous->sr_no->name);
	}
}

/**************************
*	@function	delete_record
*	@date		26/07/2018
*	@brief		given name of patient record will be deleted
*	@param		char array - name
*	@return		void
*************************/

void delete_record(char name_change[NAMEMAX])
{
	char result[NAMEMAX] = {'0'};
	struct record *prev, *nextn, *pres;

	if (head == NULL)
	{
		printf("No record with %s found to delete", name_change);
	}
	else
	{
		prev = pres = head;

		while (strcmp(pres->sr_no->name,name_change))
		{
			if (pres->next == NULL)
			{
				printf("Name not found to Delete");
				break;
			}

			prev = pres;			//present change to previous
			
			pres = pres->next;		//next change to present
		
			if (pres->next == NULL)
			{
				break;
			}
			nextn = pres->next;		//next change to nextn


		}
		
		if (pres == head)
		{
			
			if (pres->next == NULL) // first and last record
			{
				free(pres->sr_no);
				head = NULL;
			}
			else // head but having members in record
			{
				nextn = prev->next;
				head = nextn;
				free(pres->sr_no);
				free(pres);
			}
		}
		else
		{
			if (pres->next == NULL) // last node
			{
				prev->next = NULL;
				free(pres->sr_no);
				
			}
			else // node between first and last 
			{
				prev->next = nextn;
				printf("This node");
				free(pres->sr_no);
				free(pres);
			}
		}
	}

}

/**************************
*	@function	edit
*	@date		26/07/2018
*	@brief		edit the record, it may be name, symptoms, age
*			or address
*	@param		char array - name
*			int option which details to changed or edited
*	@return		void
**************************/

void edit(char change_name[], int option)
{

	if (head == NULL)
	{
		printf("No Record Found");
		return;
	}
	
	struct record *prev;
	
	prev = head;

	// loop till name not found
	while (strcmp(prev->sr_no->name,change_name))
	{
		if (prev->next == NULL)
		{
			return;
		}
		prev = prev->next;
	}

	switch(option)
	{
		case 1:
		{
			char new_name[NAMEMAX];
			printf("\nEnter name: ");
			scanf("%s",new_name);
			strcpy (prev->sr_no->name,new_name);
			break;
		}
		case 2:
		{
			int new_age, check, count;
			printf("\nEnter age: ");
			count = 1;
			check = scanf("%d", &new_age);

			while (check != 1 )
			{
				printf("Please enter digits instead of characters\n ");
				check = scanf("%d",&new_age);
				count ++;
			}
		 	prev->sr_no->age = new_age;

			break;
		}
		case 3:
		{
			char new_address[ADDRESSMAX];
			printf("\nEnter address: ");
			scanf("%s",new_address);
			strcpy (prev->sr_no->address,new_address);

			break;
		}
		case 4:
		{
			int var, ch;
			char symptom[30];
			printf("Which one of the following you wish to edit: ");
			for (var=0;var<4;var++)
			{
				printf("\n%d. %s",(var+1),prev->sr_no->symptoms[var]);
			}
			scanf("%d",&ch);

			printf("\nEnter symptoms: ");
			scanf(" %[^\n]s",symptom);
			strcpy(prev->sr_no->symptoms[ch-1],symptom);
			break;
		}
		default:
		{
			printf("Option Invalid");
			break;
		}
	}
}

/************************
*	@function	store_file
*	@date		26/07/2018
*	@brief		on exit store the record into one file
*	@param		void
*	@return		void
************************/

void store_file()
{
	struct record *pres, *next;
	
	FILE *fp;

	int count;

	count = 1;

	
	pres = head;

	if (head == NULL)
	{
		return ;
	}
	else
	{
		fp = fopen("patient_register.csv","w");

		// write into file using fpintf
		while (pres->next != NULL)
		{
			fprintf(fp,"%d \t %s \t %d \t %s \t %s \t  %s \t %s \t  %s \t %s\n",count,pres->sr_no->name, pres->sr_no->age,pres->sr_no->address,pres->sr_no->symptoms[0],pres->sr_no->symptoms[1],pres->sr_no->symptoms[2],pres->sr_no->symptoms[3]);
			printf("\n\nData Inserted %d\n",count);
			count ++;

			free(pres->sr_no);
			pres = pres->next;
					}
		fprintf(fp,"%d \t %s \t %d \t %s \t %s \t  %s \t %s \t  %s \t %s\n",count,pres->sr_no->name, pres->sr_no->age,pres->sr_no->address,pres->sr_no->symptoms[0],pres->sr_no->symptoms[1],pres->sr_no->symptoms[2],pres->sr_no->symptoms[3]);
		free(pres->sr_no);
		fclose(fp);
		free(pres);
	}
	
}

/************************
*	@function	signal_handler
*	@date		30/07/2018
*	@brief		interrupt signal handling
*	@param		int sig_no
*	@return		void
************************/

void signal_handler(int sig_no)
{
	store_file();
	sigaction(SIGINT, &controlcpressed, NULL);
	kill(0,SIGINT);
}


/***********************
*	@function	buffer_clear
*	@date		2/08/2018
*	@brief		to clear extra characters in buffer
*	@param		void
*	@return		void
**********************/

void buffer_clear()
{
	while((getchar()) != '\n');
}
