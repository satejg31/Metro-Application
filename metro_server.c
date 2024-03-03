#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "metro.h"

/* Interface routines */
struct station_node *create_metro()
{	
	struct station_node *p_new_node = NULL;
	p_new_node = get_station_node("\0", -1, 0);

	p_new_node->prev = p_new_node;
	p_new_node->next = p_new_node;
	
	return (p_new_node);
}

int insert_end(struct station_node *p_station, char* station_name, int new_distance, int station_num)
{
	generic_insert(p_station->prev, 
					get_station_node(station_name, new_distance, station_num),
					p_station);

	return (1);
}

int destroy_metro(struct station_node **pp_metro)
{
	struct station_node *p_metro = *pp_metro;
	struct station_node *p_run = NULL;
	struct station_node *p_run_next = NULL;

	for(p_run = p_metro->next;
		p_run != p_metro;
		p_run = p_run->next)
	{
		p_run_next = p_run->next;
		free(p_run);
	}

	free(p_metro);
	pp_metro = NULL;
	return (1);
}

double first_class(struct station_node *p_metro, char *arrival, char *destination, int nr_adults, int nr_children)
{	
	struct station_node *p_arrival = NULL;
	struct station_node *p_destination = NULL;
	struct station_node *p_run = NULL;
	int total_distance = 0;
	double total = 0.0;
	
	p_arrival = locate_station(p_metro, arrival);
	p_destination = locate_station(p_metro, destination);
		
	if(p_arrival->station_number < p_destination->station_number)
	{
		p_run = p_arrival;
		while(p_run != p_destination->next)
		{
			total_distance += p_run->distance;
			p_run = p_run->next;
		}
	}

	else
	{
		p_run = p_arrival;
		while(p_run != p_destination)
		{
			total_distance += p_run->distance;
			p_run = p_run->prev;
		}
	}

	total = (((nr_adults * FIRSTCLASS_ADULT + nr_children * FIRSTCLASS_CHILD) * total_distance) / 10.0);
	return (total);
}

double second_class(struct station_node *p_metro, char *arrival, char *destination, int nr_adults, int nr_children)
{
	struct station_node *p_arrival = NULL;
	struct station_node *p_destination = NULL;
	struct station_node *p_run = NULL;
	int total_distance = 0;
	double total = 0.0;

	p_arrival = locate_station(p_metro, arrival);
	p_destination = locate_station(p_metro, destination);
		
	if(p_arrival->station_number < p_destination->station_number)
	{
		p_run = p_arrival;
		while(p_run != p_destination->next)
		{
			total_distance += p_run->distance;
			p_run = p_run->next;
		}
	}

	else
	{
		p_run = p_arrival;
		while(p_run != p_destination)
		{
			printf("%s\n", p_run->station_name);
			total_distance += p_run->distance;
			p_run = p_run->prev;
		}
	}

	
	total = (((nr_adults * SECONDCLASS_ADULT + nr_children * SECONDCLASS_CHILD) * total_distance) / 10.0);
	return (total);
}

double general_class(struct station_node *p_metro, char *arrival, char *destination, int nr_adults, int nr_children)
{
	struct station_node *p_arrival = NULL;
	struct station_node *p_destination = NULL;
	struct station_node *p_run = NULL;
	int total_distance = 0;
	double total = 0.0;
	
	p_arrival = locate_station(p_metro, arrival);
	p_destination = locate_station(p_metro, destination);
		
	if(p_arrival->station_number < p_destination->station_number)
	{
		p_run = p_arrival;
		while(p_run != p_destination->next)
		{
			total_distance += p_run->distance;
			p_run = p_run->next;
		}
	}

	else
	{
		p_run = p_arrival;
		while(p_run != p_destination)
		{
			printf("%s\n", p_run->station_name);
			total_distance += p_run->distance;
			p_run = p_run->prev;
		}
	}

	total = (((nr_adults * GENERALCLASS_ADULT + nr_children * GENERALCLASS_CHILD) * total_distance) / 10.0);
	return (total);
}

void show_metro(struct station_node *p_metro, const char* msg)
{	
	struct station_node *p_run = NULL;
	if(msg)
	{
		puts(msg);
	}

	printf("[START]<->");
	for(p_run = p_metro->next;
			p_run != p_metro;
			p_run = p_run->next)
	{
		printf("[Station = %s Distance = %d num = %d]<->\n",p_run->station_name, 
										p_run->distance, p_run->station_number);
	}


	puts("[END]\n");
}

int is_station_present(struct station_node *p_metro, char* s_station)
{
	if(locate_station(p_metro, s_station) != NULL)
		return 1;
	else
		return 0;
}

/* Auxillary routines */
static void generic_insert(struct station_node *p_beg, struct station_node *p_mid, struct station_node *p_end)
{
	p_mid->next = p_end;
	p_mid->prev = p_beg;
	p_beg->next = p_mid;
	p_end->prev = p_mid;
}

static struct station_node *locate_station(struct station_node *p_metro, char* search_name)
{
	struct station_node *p_run = NULL;

	for(p_run = p_metro->next;
		p_run != p_metro;
		p_run = p_run->next)
	{
		if(strcmp(p_run->station_name, search_name) == 0)
			return (p_run);
	}

	return (NULL);
}

static struct station_node *get_station_node(char *new_name, int new_distance, int station_num)
{
	
	struct station_node *p_new_node = NULL;
	p_new_node = (struct station_node *)xmalloc(sizeof(struct station_node));
		
	strcpy(p_new_node->station_name, new_name);
	p_new_node->distance = new_distance;
	p_new_node->station_number = station_num;
	p_new_node->prev = NULL;
	p_new_node->next = NULL;

	return (p_new_node);

}

static void* xmalloc(size_t size_in_bytes)
{
	
	void *p = NULL;
	p = malloc(size_in_bytes);

	if(p == NULL)
	{
		fprintf(stderr, "Out of memory : Terminating program");
		exit(EXIT_FAILURE);
	}
	
	return (p);
}
