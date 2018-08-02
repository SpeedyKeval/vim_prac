
/*
    This Program is to demonstrate Selection Sort with c (demotration)
*/
/************************************************************************
*   @file   selectionsort.c
*   @author Keval Vora
*   @brief  Given an Array, elements are sorted in acessending or 
*           decending order as per user requirement.
*   @date   23/07/2018
*/
/***********************************************************************
*	This program will work as mentioned below
*		1) Take user input 
*		2) use pre-define array for demo sorting (testing)
*		
*		selection sort works as below:
*			- select an element from array and compare it with all other 
*			elements from array, if small found will swap element.
*********************************************************************/
/********
* HEADER
********/

#include<stdio.h>


/********
* MACRO
********/
#define MAX 20

/********
* Functions
********/

/*
*	@function		main
*	@brief			this function is main, whole follow starts from here
*	@param		args for command line argument
*	@return		0 for perfect execution
*						other non-perfect execution
*/

/************
* Prototype
************/

void selection_sort(int*,int);
void swap(int*,int*);

int main()
{
	int len;
	int sorting_array[MAX];
	int i;
	len = 7;
	for (i=0;i<len;i++)
	{
		scanf("%d",&sorting_array[i]);
	}
	selection_sort(&sorting_array,len);
	for (i=0;i<len;i++)
	{
		printf("\n%d",sorting_array[i]);
	}
}

/**************************************
*	@function	selection_sort
*	@brief		function performs selection sort over 
*			argument array
*	@param		int pointer array 
*			int variable for lenght
*	@return		int value 
*************************************/

void selection_sort(int* arr, int len)
{
	int min, index, lvariable,swapindex;
	min = arr[0];
	for (lvariable = 0; lvariable<len; lvariable++)
	{
		for(index = lvariable; index<len; index++)
		{
			if (min > arr[index])
			{
				
				min = arr[index];
				swapindex = index;
			}
		}
		if ( min != arr[lvariable] )
		{
			swap(&arr[lvariable],&arr[swapindex]);
		}
		min = arr[lvariable+1];
		printf("\n");
		for (index=0;index<len;index++)
		{
			printf("%d \t",arr[index]);
		}
		printf("\n");
	}
}

/*************************************
*	@function	swap
*	@brief		swaping of data
*	@param		int pointer, int pointer
*	@return		void
************************************/

void swap(int* a, int* b)
{
	int tmp;
	tmp = *a;
	*a = *b;
	*b = tmp;
}
