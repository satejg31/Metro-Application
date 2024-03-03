#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "metro.h"

int main(void)
{
	struct station_node *p_metro = NULL;
	int ret = 0;
	char destination[20];
	char arrival[20];
	int station_num = 1;
	int passengers = 0;
	int adults = 0;
	int children = 0;
	int choice = 0;
	double amount = 0.0;

	p_metro = create_metro();

	ret = insert_end(p_metro, "CST", 0, station_num);
	assert(ret == 1);

	station_num++;
	ret = insert_end(p_metro, "Thane", 22, station_num);
	assert(ret == 1);

	station_num++;
	ret = insert_end(p_metro, "Mulund", 5, station_num);
	assert(ret == 1);

	station_num++;
	ret = insert_end(p_metro, "Kalyan", 10, station_num);
	assert(ret == 1);

	station_num++;
	ret = insert_end(p_metro, "Dombivali", 6, station_num);
	assert(ret == 1);

	printf("Enter the Arrival Station : ");
	scanf("%[^\n]", &arrival);

	printf("Enter the Destination Station : ");
	scanf(" %[^\n]", &destination);

	ret = is_station_present(p_metro, destination);
	if(ret != 1)
		printf("Station is not present\n");

	printf("Please enter the number of passengers travelling : ");
	scanf("%d", &passengers);

	printf("Please enter the number of adults : ");
	scanf("%d", &adults);

	printf("Please enter the number of children : ");
	scanf("%d", &children);

	if(passengers != (adults + children))
	{
		printf("The entered number of Adults and Children do not match\n");
		printf("Please enter the valid number\n");
		exit(EXIT_FAILURE);
	}

	printf("Please enter the category you want : ");
	printf("\n1. First Class\n");
	printf("2. Second Class\n");
	printf("3. General Class\n");

	printf("Category : ");
	scanf("%d", &choice);

	switch(choice)
	{
		case 1:
			amount = first_class(p_metro, arrival, destination, adults, children);
			printf("Total = %lf\n", amount);
			break;

		case 2:
			amount = second_class(p_metro, arrival, destination, adults, children);
			printf("Total = %lf\n", amount);
			break;

		case 3:
			amount = general_class(p_metro, arrival, destination, adults, children);
			printf("Total = %lf\n", amount);
			break;

		default:
			printf("Please enter a valid choice\n");
			break;
	}


	ret = destroy_metro(&p_metro);
	assert(ret == 1);

	exit(EXIT_SUCCESS);
}

