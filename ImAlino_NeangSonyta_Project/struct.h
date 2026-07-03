#ifndef STRUCT_H
#define STRUCT_H

typedef struct {
    int day;
    int month;
    int year;
} Date;

typedef struct {
    int hour;
    int min;
    int sec;
} Time;

typedef struct {
    char height[5];
    char weight[5]; 
    char health_condition[50];
    char breeding_status[10]; //Young Mature Old
    Date last_checkup_date;
    Date next_checkup_date;
} Health;

typedef struct{
    char feeding_status[10]; //fed unfed 
    Time last_feeding;
    Time next_feeding;    
} Feeding;

typedef struct{
    char name[30];
    char id[10];
    char password[10];
    int age;
    char gender;
    char position[10]; //Manager Vet Keeper Staff
    Date check_in_date;
    Time check_in_time;
    Date check_out_date;
    Time check_out_time;
    int salary;
    char salary_status[10]; // Paid Unpaid
} Staff_Info;

typedef struct {
    char name[30];
    char id[10];
    char sex; // M F
    int age;
    char species[50];
    char natural_habitat[50];
    char zone; // A B C D E
    char origin[50];
    char food_category[15]; //Herbivore Omnivore Carnivore
    char class[15]; // Reptile Fish Mammal Ampibian Bird
    Health health;
    Feeding feeding;
} Animal_Info;

#endif
