/*
Project: Pinball
Name: main.c
Authors: macasal & sgalella
Description: main of the program
 */
#include <stdio.h>
#include <stdlib.h>
#include "pinball.h"

int main(int argc, char **argv){
	// Read board from file
	int rows, cols;
	FILE *fp = NULL;
	fp = fopen("boards/board50x50.txt", "r");
	fscanf(fp, "%d %d", &rows, &cols);
	int table[rows][cols];

	for (int i=0; i<rows; i++){
		for (int j=0; j<rows; j++){
			fscanf(fp, "%d", &table[i][j]);
		}
	}
	fclose(fp);

	int table_backup[50][50]; // creating a back up of the original table such that when can restor it after any modification
	backing_up(table,table_backup);
	int shots_position[10] = {1, 5, 14, 22, 37, 48, 43, 40, 28, 19}; //vector of positions of the 10 balls in 10 ball fall
	char shots_direction[10]= {'i','i','d','i','d','d','i','d','d','i'}; //vector of initial direction for the 10 balls in 10 ball fall
	int s[10],action=0; // s=vector of statistics, p=user action
	while (action!=5){ //while the user does not choose to exit, the program ask for an action
		action = menu();
		switch(action){
			case 1: //visualizing the table
				visualization(table,action,table_backup);
				break;
			case 2: //visualizing table statistics
				statistics(table,s);
				printf("The amount of vertical lines is %d \n", s[0]);
				printf("The amount of horizontal lines is %d \n", s[1]);
				printf("The total amount of diagonal lines from top-right to bottom-left is %d \n", s[2]);
				printf("The total amount of diagonal lines from top-left to bottom-right is %d \n", s[3]);
				printf("The longest vertical line dimension is %d \n", s[4]);
				printf("The longest horizontal line dimension is %d \n", s[5]);
				printf("The longest diagonal line from top-right to bottom-left has a dimension of %d \n", s[6]);
				printf("The longest diagonal line from top-left to bottom-right has a dimension of %d \n", s[7]);
				printf("The total amount of lines is %d \n", s[8]);
				printf("The global longest line dimension is %d \n", s[9]);
				break;
			case 3: //simulating 1 ball fall
				simulation1(table,action);
				//printing matrix after 1 ball fall with single ball position in each time step
				visualization(table,action,table_backup);
				break;
			case 4: //simulating 10 ball fall
				simulation10(table,shots_position,shots_direction,action);
				//printing ocupation matrix after 10 ball fall
				visualization(table,action,table_backup);
				break;
			case 5:
				printf("See you!\n");
				exit(-1);
			default: //if any of the previous action is selected it reminds the user what he or she can do
				printf("Please, choose a number from 1 to 5 \n");
				break;
		}
	}
}
