#ifndef _METRO_H
#define _METRO_H

#define FIRSTCLASS_ADULT 	50.00
#define FIRSTCLASS_CHILD	20.00

#define SECONDCLASS_ADULT 	40.00
#define SECONDCLASS_CHILD 	15.00

#define GENERALCLASS_ADULT 	25.00
#define GENERALCLASS_CHILD 	10.00

struct station_node
{	
	int station_number;
	char station_name[20];
	int distance;
	struct station_node *prev;
	struct station_node *next;

};

/* Interface routines */
struct station_node *create_metro();
int insert_end(struct station_node *p_station, char* station_name, int new_distance, int station_num);
int destroy_metro(struct station_node **pp_metro);
void show_metro(struct station_node *p_metro, const char* msg);

int is_station_present(struct station_node *p_metro, char* s_station);

double first_class(struct station_node *p_metro, char *arrival, char *destination, int nr_adults, int nr_children);
double second_class(struct station_node *p_metro, char *arrival, char *destination, int nr_adults, int nr_children);
double general_class(struct station_node *p_metro, char *arrival, char *destination, int nr_adults, int nr_children);

/* Auxillary routines */
static void generic_insert(struct station_node *p_beg, struct station_node *p_mid, struct station_node *p_end);
static struct station_node *locate_station(struct station_node *p_metro, char* search_name);
static struct station_node *get_station_node(char* new_name, int new_distance, int station_num);
static void* xmalloc(size_t size_in_bytes);

#endif 	/* _METRO_H */
