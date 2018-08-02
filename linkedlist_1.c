/*
	This program is for demonatration/practice of linked list and valgrind
*/

/******************************************************************************
*	Program has functionalites as below
*
*	A structure having two values
*		1) number
*		2) address of next node
*
*	- main function is used for menu of the program 
*	- linked list is create by create method, which has the most priority
*	- every functionality of the linked is well defined in different
*		methods. To avoid the conflit and give the best performance
*	- functionalities of Linked List are as below
*		1) Create a new linked list (It will destroy Linked List if 
*				exist)
*		2) Add new value at the end of Linked List
*		3) Add new value at the beginning of Linked List
*		4) Add new value after or before a value in Linked List
*		5) Delete value specified from Linked List
*		6) Delete value from beginning of Linked List
*		7) Delete value at end of Linked List
*
*	CONSTRAINTS
*		1) floating point value are not allowed
*		2) every operations can only be performed using structure of
*			Linked List 
******************************************************************************/

/*********************
*	HEADER
*********************/

#include<stdio.h>
#include<stdlib.h>

/*********************
*	MACRO
*********************/


/*********************
*      STRUCTURE
*********************/

struct list
{
	int value;
	int *link;
} *first;

/********************
*      PROTOTYPE
********************/

// create linked list
void create(void);

// insert element in linked list at beginning
int insert_begin(int);

// insert element in linked list at end
int insert_end(int);

// insert element before a value in linked list
int insert_before_value(int,int);

// insert element after a value in linked list
int insert_after_value(int,int);

// delete from beginning
int del_begin();

// delete from end
int del_end();

// delete a specified element
int del_value(int);

// show elements in list
void show_list(void);

/************************
*	@function	main
*	@brief		main function of the program
*	@param		void
*	@return		int value
************************/

int main()
{
	// First node or start of Linked List
	
	//first->link = NULL;
	int return_value;

	int ch,flag;
	flag = 1;
	while (1)
	{

		printf("Enter your choice for Linked List functionalities");
		printf("\n 1) Create Linked List");
		printf("\n 2) Insert element at the start of Linked List");
		printf("\n 3) Insert element at end of Linked List");
		printf("\n 4) Show the List");
		printf("\n 5) Insert element before a value");
		printf("\n 6) Insert element after a value");
		printf("\n 7) Delete element at end");
		printf("\n 8) Delete element at beginnig");
		printf("\n 9) Delete specified element");
		printf("\n");
		
		scanf("%d",&ch);
		switch(ch)
		{
			case 1:
			{
			 	create();
				break;
			}
			case 2:
			{
				int value;
				printf("Insert value for Linked List: ");
				scanf("%d",&value);
				return_value = insert_begin(value);
				break;
			}
			case 3:
			{
				int value;
				printf("Insert value for Linked List: ");
				scanf("%d",&value);
				return_value = insert_end(value);
				break;
			}
			case 4:
			{
				show_list();
				break;
			}
			case 5:
			{
				int value,beforevalue;
				printf("Insert value for Linked List: ");
				scanf("%d",&value);
				printf("Insert value before which you want to insert value: ");
				scanf("%d",&beforevalue);
				return_value = insert_before_value(beforevalue,value);
				break;
				
			}
			case 6:
			{
				int value,aftervalue;
				printf("Insert value for Linked List: ");
				scanf("%d",&value);
				printf("Insert value after which you want to insert value: ");
				scanf("%d",&aftervalue);
				return_value = insert_after_value(aftervalue,value);
				break;
			}
			case 7:
			{
				return_value = delete_begin();
				break;
			}
			case 8:
			{
				return_value = delete_end();
				break;
			}
			case 9:
			{
				int value;
				printf("Value which to delete: ");
				scanf("%d",value);
				return_value = delete_value(value);
				break;
			}
			case 10:
			{
				flag = 0;
				break;
			}
			default:
			{
				flag = 0;
				break;
			}
			
		}
		if (flag == 0)
		{
			break;
		}
	}
}

/***************************
*	@function	create
*	@brief		create a Linked List, Ignoring created previously
*	@param		void
*	@return		void
*****************************/

void create()
{
	int num;
	// pointer to List structure 
	struct list *ptr, *cpt;
	
	first = (struct list*) malloc( sizeof(struct list));
	printf("Enter number of value are required in Linked List: ");
	scanf("%d",&num);
	if (num == 1)
	{
		int info;
		scanf("%d",&info);
		first->value = info;
		first->link = NULL;
	}
	else
	{
		int info;
		scanf("%d",&info);
		first->value = info;
		//ptr = (struct list*) malloc( sizeof(struct list));
		cpt = (struct list*) malloc(sizeof(struct list));
		ptr = first;
		//printf("%d",first->value);
		
		int lvariable;
		for (lvariable=1;lvariable<num;lvariable++)
		{
			scanf("%d",&info);
			cpt->value = info;
			ptr->link = cpt;
			//printf("%d %d\n",ptr->link,ptr->value);
			ptr = cpt;
			//printf("%d %d\n",cpt->link,ptr->value);
			cpt = (struct list*)malloc( sizeof(struct list));
		}
		ptr->link = NULL;
	}
}

/***************************
*	@function	insert_begin
*	@brief		insert an element at the beginning of linked list
*	@param		int number that is to be inserted
*	@return 	1 for complitaion of task
*			0 for error
**************************/

int insert_begin(int info)
{
	struct list *newnode;
	newnode = (struct node*)malloc(sizeof(struct list));
	newnode->value = info;
	newnode->link = first;
	first = newnode;
	return 1;
}

/**************************
*	@function	insert_end
*	@brief		insert an element at end of linked list
*	@param		int number that is to be inserted
*	@return		1 for compliation of task
*			0 for error
*************************/

int insert_end(int info)
{
	struct list *newnode, *temp;
	newnode = (struct list*) malloc(sizeof(struct list));
	//ptr = (struct List*) malloc (sizeof(struct List));
	newnode->value = info;
	newnode->link = NULL;
	temp = first;

	while (temp->link !=NULL)
	{
		temp = temp->link; 
	}
	temp->link = newnode;

	
	return 1;
}

/**************************
*	@function	insert_before_value
*	@brief		insert an element before a value given by user
*	@param		int number that is to be inserted
*			int number after which value is to be inserted
*	@return		1 for complitaion of task
*			0 for error
*************************/

int insert_before_value(int bvalue, int info)
{
	struct list *newnode, *next, *previous;
	newnode = (struct list*)malloc(sizeof(struct list));
	newnode->value = info; 
	next = first;
	//previous = next;
	printf("%d",next->value);
	while (next->value != info)
	{
		printf("%d",next->value);
		//previous = next;
		next = next->link;
	}
	printf("%d",next->value);
	//previous->link = NULL;
	//previous->link = newnode;
	//newnode->link = next;
}

/*************************
*	@function	insert_after_value
*	@brief		insert an element after a provided value
*	@param		int number that is to be inserted
*			int number before which value is to be inserted
*	@return		1 for complition of task
*			0 for error
*************************/

int insert_after_value(int avalue, int info)
{
	struct list *newnode, *ptr;
	newnode = (struct node*)malloc(sizeof(struct node*));
	newnode->value = info; 
	
}

/************************
*	@function	delete_begin
*	@brief		delete an elemenet from beginning of linked list
*	@param		void
*	@return		1 for complition of task
*			0 for error
************************/

int delete_begin()
{
	
}

/************************
*	@function	delete_end
*	@brief		delete an element from end of linked list
*	@param		void
*	@return		1 for complition of task
*			0 for error
************************/

int delete_end()
{
	
}

/***********************
*	@function	delete_value
*	@brief		delete an element specified by user from linked list
*	@param		int number to be deleted
*	@return		1 for complition of task
*			0 for error
***********************/

int delete_value(int info)
{
	struct list *newnode, *ptr;
	newnode = (struct node*)malloc(sizeof(struct node*));
	newnode->value = info; 
}


/***********************
*	@function	show_list
*	@brief		show every elements in the linked list
*	@param		void
*	@return		void
***********************/

void show_list(void)
{
	struct list *ptr, *cpt;
	
	ptr = (struct list*) malloc (sizeof(struct list));
	cpt = (struct list*) malloc (sizeof(struct list));
	ptr = first;
	printf("List is as below: \n");
	while (ptr->link != NULL)
	{
		printf("%d\n",ptr->value);
		//printf("%d\n",ptr->link);
		cpt = ptr->link;
		//printf("%d\n",cpt->link);
		ptr = cpt;
	}
	printf("%d\n\n\n\n",ptr->value);
}
