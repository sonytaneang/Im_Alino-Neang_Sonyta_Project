#ifndef ANIMAL_H
#define ANIMAL_H

#include "mainmenu.h"
#include "struct.h"
#include "activity_log.h"
#include "clear.h"
#include "pagination.h"

void Print_Animal_Function(Animal_Info animal[], int index){
    int width = 40;
    printf("\n\xE2\x95\x94");
    for(int i = 0; i < width; i++) printf("\xE2\x95\x90");
    printf("\xE2\x95\x97\n");
    printf("    Name : %s\n", animal[index].name);
    printf("    ID : %s\n", animal[index].id);
    printf("    Species : %s\n", animal[index].species);
    printf("    Zone : %c\n", animal[index].zone);
    printf("\xE2\x95\x9A");
    for(int i = 0; i < width; i++) printf("\xE2\x95\x90");
    printf("\xE2\x95\x9D\n");
}
Animal_Info* paginate_animal_ptr = NULL;
int animal_paginate_match_indices[max_animal];

void Print_Animal_Match_For_Paginate(int i) {
    // i here is 0,1,2... (the "page index"), NOT the real staff index
    int real_index = animal_paginate_match_indices[i];
    Print_Animal_Function(paginate_animal_ptr, real_index);
}

void Print_Animal_For_Paginate(int i) {
    Print_Animal_Function(paginate_animal_ptr, i);
}

//Save the animals data after program is closed
void Save_Animal_Data(Animal_Info animal[], int* current_animal_count){
    FILE *fp = fopen("animals.txt", "w");
    if(fp == NULL){
        printf("Error While Opening File");
        return;
    }
    for(int i = 0; i < *current_animal_count; i++){
        fprintf(fp, "%s,%s,%c,%d,%s,%s,%c,%s,%s,%s,%s,%s,%s,%s,%d/%d/%d,%d/%d/%d,%s,%d:%d:%d,%d:%d:%d\n",            
            animal[i].name, 
            animal[i].id,
            animal[i].sex,
            animal[i].age,
            animal[i].species,
            animal[i].natural_habitat,
            animal[i].zone,
            animal[i].origin,
            animal[i].food_category,
            animal[i].class,

            animal[i].health.height,
            animal[i].health.weight,
            animal[i].health.health_condition,
            animal[i].health.breeding_status,

            animal[i].health.last_checkup_date.day,
            animal[i].health.last_checkup_date.month,
            animal[i].health.last_checkup_date.year,

            animal[i].health.next_checkup_date.day,
            animal[i].health.next_checkup_date.month,
            animal[i].health.next_checkup_date.year,

            animal[i].feeding.feeding_status,

            animal[i].feeding.last_feeding.hour,
            animal[i].feeding.last_feeding.min,
            animal[i].feeding.last_feeding.sec,
            animal[i].feeding.next_feeding.hour,
            animal[i].feeding.next_feeding.min,
            animal[i].feeding.next_feeding.sec);
    }
    fclose(fp);
    printf("Animal's Data Saved.\n");
}
//Call load function in main when the program starts, if not the data in the program will be
//reset (lost)
void Load_Animal_Data(Animal_Info animal[], int* current_animal_count){
    FILE* fp = fopen("animals.txt", "r");
    if (fp == NULL){
        printf("No saved data found.\n");
        return;
    }
    int i = 0;

    while (i < max_animal &&
        (fscanf(fp, "%29[^,],%9[^,],%c,%d,%49[^,],%49[^,],%c,%49[^,],%14[^,],%14[^,],%4[^,],%4[^,],%49[^,],%9[^,],%d/%d/%d,%d/%d/%d,%9[^,],%d:%d:%d,%d:%d:%d\n",
        animal[i].name, 
        animal[i].id, 
        &animal[i].sex, 
        &animal[i].age, 
        animal[i].species,
        animal[i].natural_habitat, 
        &animal[i].zone, 
        animal[i].origin, 
        animal[i].food_category,
        animal[i].class, 

        animal[i].health.height, 
        animal[i].health.weight,
        animal[i].health.health_condition, 
        animal[i].health.breeding_status,

        &animal[i].health.last_checkup_date.day, 
        &animal[i].health.last_checkup_date.month,
        &animal[i].health.last_checkup_date.year, 

        &animal[i].health.next_checkup_date.day,
        &animal[i].health.next_checkup_date.month, 
        &animal[i].health.next_checkup_date.year,

        animal[i].feeding.feeding_status, 

        &animal[i].feeding.last_feeding.hour,
        &animal[i].feeding.last_feeding.min, 
        &animal[i].feeding.last_feeding.sec,

        &animal[i].feeding.next_feeding.hour, 
        &animal[i].feeding.next_feeding.min,
        &animal[i].feeding.next_feeding.sec)) == 27){
            i++;
    }
    *current_animal_count = i;
    printf("Loaded %d animal records.\n", *current_animal_count);
    fclose(fp);
}

int Search_Animal_ID(Animal_Info animal[], int* current_animal_count, char search_id[]){
    int found_index = -1;
    for (int i = 0; i < *current_animal_count; i++){
        if(strcmp(search_id, animal[i].id) == 0){
            found_index = i;
            break;
        }
    }
    if(found_index == -1){
        printf("No Animal Found.\n");
    }
    return found_index;
}
//Search By ID is a speified search print -> All Data
void search_by_ID(Animal_Info animal[], int* current_animal_count){
    char answer;
    char search_id[10];

    printf("\n===== Search Animal By ID =====\n");
    printf("Enter Search ID : ");
    scanf("%9s",search_id);
    printf("\n");

    printf("Search ID is : %s", search_id);
    printf("\n");

    int index = Search_Animal_ID(animal, current_animal_count, search_id);

    if (index == -1){
        return;
    }

    printf("Animal Found!\n");
    printf("Do you want to print the Animal's Information? (Y/N): ");
    scanf(" %c", &answer);
    if (answer == 'Y' || answer == 'y'){
        int width = 40;
        printf("\n\xE2\x95\x94");
        for(int i = 0; i < width; i++) printf("\xE2\x95\x90");
        printf("\xE2\x95\x97\n");

        printf("    ID : %s\n",animal[index].id);
        printf("    Name : %s\n",animal[index].name);
        printf("    Species : %s\n",animal[index].species);
        printf("    Sex : %c\n",animal[index].sex);
        printf("    Age : %d\n",animal[index].age);
        printf("    Natural Habitat : %s\n",animal[index].natural_habitat);
        printf("    Zone : %c\n",animal[index].zone);
        printf("    Origin : %s\n",animal[index].origin);
        printf("    Food Category : %s\n",animal[index].food_category);
        printf("    Class : %s\n",animal[index].class);
        printf("    Height : %s\n",animal[index].health.height);
        printf("    Weight : %s\n",animal[index].health.weight);
        printf("    Health Condition : %s\n",animal[index].health.health_condition);
        printf("    Check Up Date : %d/%d/%d\n",animal[index].health.last_checkup_date.day, animal[index].health.last_checkup_date.month,animal[index].health.last_checkup_date.year);
        printf("    Next Check Up : %d/%d/%d\n",animal[index].health.next_checkup_date.day, animal[index].health.next_checkup_date.month,animal[index].health.next_checkup_date.year);
        printf("    Feeding Status : %s\n",animal[index].feeding.feeding_status);
        printf("    Last Feeding : %d:%d:%d\n",animal[index].feeding.last_feeding.hour, animal[index].feeding.last_feeding.min,animal[index].feeding.last_feeding.sec);
        printf("    Next Feeding : %d:%d:%d\n",animal[index].feeding.next_feeding.hour, animal[index].feeding.next_feeding.min,animal[index].feeding.next_feeding.sec);

        printf("\xE2\x95\x9A");
        for(int i = 0; i < width; i++) printf("\xE2\x95\x90");
        printf("\xE2\x95\x9D\n");

    }
}

void search_by_Species(Animal_Info animal[], int* current_animal_count){
    char search_species[50];
    bool found = false;
    int species_member = 0;

    printf("\n===== Search Animal By Species =====\n");
    printf("Enter Species : ");
    scanf(" %49[^\n]", search_species);
    printf("\n");

    printf("Search Species : %s", search_species);
    printf("\n");

    int match_count = 0;

    for(int i = 0; i < *current_animal_count; i++){
        if(strcmp(search_species,animal[i].species) == 0){
            found = true;
            animal_paginate_match_indices[match_count] = i;
            match_count++;
            species_member++;
        }
    }

    paginate_animal_ptr = animal;
    Paginate(match_count, Print_Animal_Match_For_Paginate);

    printf("Species Member : %d \n",species_member);
    if(!found){
        printf("No Animals Found\n");
    }

}

void search_by_Habitat_Zone(Animal_Info animal[], int* current_animal_count){
    char search_zone;
    int zone_member = 0;
    bool found = false;

    printf("\n===== Search Animal By Habitat Zone =====\n");
    printf("Enter Search Zone : ");
    scanf(" %c", &search_zone);
    printf("\n");

    printf("Search Zone : %c", search_zone);
    printf("\n");

    int match_count = 0;

    for(int i = 0; i < *current_animal_count; i++){
        if(search_zone == animal[i].zone){
            found = true;
            animal_paginate_match_indices[match_count] = i;
            match_count++;
            zone_member++;
        }
    }
    paginate_animal_ptr = animal;
    Paginate(match_count, Print_Animal_Match_For_Paginate);
    printf("Zone Member : %d\n", zone_member);
    if (!found){
        printf("No Animals Found\n");
    }
    
}

void search_by_Food_Category(Animal_Info animal[], int* current_animal_count){
    char search_food_category[15];
    bool found = false;
    int food_category_member = 0 ;

    printf("\n===== Search Animal By Food Category =====\n");
    printf("Enter Food Category : ");
    scanf("%14s", search_food_category);
    printf("\n");

    printf("Search Food Category : %s", search_food_category);
    printf("\n");

    int match_count = 0;

    for(int i = 0; i < *current_animal_count; i++){
        if(strcmp(search_food_category,animal[i].food_category) == 0){
            found = true;
            animal_paginate_match_indices[match_count] = i;
            match_count++;
            food_category_member++;
        }
    }
    paginate_animal_ptr = animal;
    Paginate(match_count, Print_Animal_Match_For_Paginate);

    printf("Food Category Member : %d\n",food_category_member);

    if(!found){
        printf("No Animals Found\n");
    }
    
}

void search_by_Natural_Habitat(Animal_Info animal[], int* current_animal_count){
    char search_natural_habitat[50];
    bool found = false;
    int natural_habitat_member = 0;

    printf("\n===== Search Animal By Natural Habitat =====\n");
    printf("Enter Natural Habitat : ");
    scanf(" %49[^\n]", search_natural_habitat);
    printf("\n"); 

    printf("Search Natural Habitat : %s", search_natural_habitat);
    printf("\n");
    
    int match_count = 0;
    
    for(int i = 0; i < *current_animal_count; i++){
        if(strcmp(search_natural_habitat, animal[i].natural_habitat) == 0){
            found = true;
            animal_paginate_match_indices[match_count] = i;
            match_count++;
            natural_habitat_member++;
        }
    }
    paginate_animal_ptr = animal;
    Paginate(match_count, Print_Animal_Match_For_Paginate);

    printf("Natural Habitat Member : %d\n",natural_habitat_member);

    if(!found){
        printf("No Animals Found\n");
    }
    

}

void search_by_Class(Animal_Info animal[], int* current_animal_count){
    char search_class[15];
    bool found = false;
    int class_member = 0;

    printf("\n===== Search Animal By Class =====\n");
    printf("Enter Class : ");
    scanf("%14s", search_class);
    printf("\n");

    printf("Search class : %s\n", search_class);
    printf("\n");

    int match_count = 0;

    for(int i = 0; i < *current_animal_count; i++){
        if(strcmp(search_class, animal[i].class) == 0){
            found = true;
            animal_paginate_match_indices[match_count] = i;
            match_count++;
            class_member++;
        }
    }
    paginate_animal_ptr = animal;
    Paginate(match_count, Print_Animal_Match_For_Paginate);


    printf(" Class Member : %d\n", class_member);

    if(!found){
        printf("No Animals Found\n");
    }
    
}

void Search_Animal(Animal_Info animal[], int* current_animal_count){
    int running = 1;
    while (running == 1){
        int animal_search_choice = Animal_Search_Menu();
        clearScreen(); 
        switch (animal_search_choice){
            case 1 : 
                clearScreen(); 
                search_by_ID(animal, current_animal_count);
                pauseAndClear();
                break;
            case 2 :
                clearScreen(); 
                search_by_Species(animal, current_animal_count);
                clearScreen(); 
                break;
            case 3 :
                clearScreen(); 
                search_by_Class(animal, current_animal_count);
                clearScreen(); 
                break;
            case 4 : 
                clearScreen(); 
                search_by_Food_Category(animal, current_animal_count);
                clearScreen(); 
                break;
            case 5 :
                clearScreen(); 
                search_by_Natural_Habitat(animal, current_animal_count);
                clearScreen(); 
                break;
            case 6 :
                clearScreen(); 
                search_by_Habitat_Zone(animal, current_animal_count);
                clearScreen(); 
                break;
            case 7 :
                printf("Exited The System Successfully!\n");
                running = 0;
                break;
            default : 
                printf("Invalid Choice.\n");
                break;
        }
    }
}

void Add_Animal(Animal_Info animal[], int* current_animal_count, char* logged_in_name, char* logged_in_id){
    bool isDuplicate;
    if (*current_animal_count == max_animal){
        printf("Zoo Is At Full Capacity.");
        return;
    }
    printf("\n===== Adding New Animal =====\n");
    printf("\n===Basic Information===\n");
    printf("\n");

    printf("Enter name : ");
    scanf(" %29[^\n]",animal[*current_animal_count].name);
    printf("\n");

    do {
            printf("Enter ID : ");
            scanf("%9s", animal[*current_animal_count].id);
            isDuplicate = false;

            for (int i = 0; i < *current_animal_count; i++){
                if (strcmp(animal[*current_animal_count].id, animal[i].id) == 0){
                    printf("ID already exists. Please enter a different ID.\n");
                    isDuplicate = true;
                    break;
                }
            }
        }while (isDuplicate);

    printf("Enter sex (F/M): ");
    scanf(" %c",&animal[*current_animal_count].sex);
    printf("\n");

    printf("Enter age : ");
    scanf("%d",&animal[*current_animal_count].age);
    printf("\n");

    printf("Enter Species : ");
    scanf(" %49[^\n]",animal[*current_animal_count].species);
    printf("\n");

    printf("Enter Natural Habitat : ");
    scanf(" %49[^\n]",animal[*current_animal_count].natural_habitat);
    printf("\n");

    printf("Enter Zone : ");
    scanf(" %c",&animal[*current_animal_count].zone);
    printf("\n");
    printf("Enter Origin : ");
    scanf(" %49[^\n]",animal[*current_animal_count].origin);
    printf("\n");

    printf("Enter Food Category : ");
    scanf("%14s",animal[*current_animal_count].food_category);
    printf("\n");

    printf("Enter Class : ");
    scanf("%14s",animal[*current_animal_count].class);
    printf("\n");

    printf("\n===Health Information===\n");
    printf("\n");

    printf("Enter Height : ");
    scanf("%4s",animal[*current_animal_count].health.height);
    printf("\n");

    printf("Enter Weight : ");
    scanf("%4s",animal[*current_animal_count].health.weight);
    printf("\n");
    
    printf("Enter Health Condition : ");
    scanf(" %49[^\n]",animal[*current_animal_count].health.health_condition);
    printf("\n");

    printf("Enter Breeding Status : ");
    scanf("%9s",animal[*current_animal_count].health.breeding_status);
    printf("\n");

    printf("Enter Last Check Up Date : ");
    scanf("%d/%d/%d", &animal[*current_animal_count].health.last_checkup_date.day
                    , &animal[*current_animal_count].health.last_checkup_date.month
                    , &animal[*current_animal_count].health.last_checkup_date.year);
    printf("\n");

    printf("Enter Next Check Up Date : ");
    scanf("%d/%d/%d", &animal[*current_animal_count].health.next_checkup_date.day
                    , &animal[*current_animal_count].health.next_checkup_date.month
                    , &animal[*current_animal_count].health.next_checkup_date.year);   
    printf("\n");

    printf("\n===Feeding Information===\n");
    printf("\n");

    printf("Enter Feeding Status (Fed/Unfed): ");
    scanf("%9s",animal[*current_animal_count].feeding.feeding_status);
    printf("\n");

    printf("Enter Last Feeding Time : ");
    scanf("%d:%d:%d", &animal[*current_animal_count].feeding.last_feeding.hour
                    , &animal[*current_animal_count].feeding.last_feeding.min
                    , &animal[*current_animal_count].feeding.last_feeding.sec);
    printf("\n");
   
    printf("Enter Next Feeding Time : ");
    scanf("%d:%d:%d", &animal[*current_animal_count].feeding.next_feeding.hour
                    , &animal[*current_animal_count].feeding.next_feeding.min
                    , &animal[*current_animal_count].feeding.next_feeding.sec);
    printf("\n");
    
    (*current_animal_count)++;
    Save_Animal_Data(animal, current_animal_count);  
    Activity_Log(logged_in_name, logged_in_id, "Added Animal", animal[*current_animal_count - 1].id);
}

void Update_Animal(Animal_Info animal[], int* current_animal_count, char* logged_in_name, char* logged_in_id){
    char search_id[10];
    printf("\n===== Update Animal =====\n");
    printf("Enter Search ID : ");
    scanf("%9s",search_id);
    printf("\n");

    printf("Search ID is : %s", search_id);
    printf("\n");

    int index = Search_Animal_ID(animal, current_animal_count, search_id);

    if (index == -1){
        return;
    }

    int running = 1;
    while (running == 1){
        int animal_update_choice = Update_Animal_Menu();
        clearScreen();
        
        switch (animal_update_choice){
            case 1 : 
                int running1 = 1;
                while (running1 == 1){
                    int gen_info_choice = Update_General_Information_Menu();
                    clearScreen();
                    printf("\n===== Update Animal's General Information =====\n");
                        switch (gen_info_choice){
                            case 1 : 
                                printf("Enter New Name : ");
                                scanf(" %29[^\n]",animal[index].name);
                                printf("\n");
                                printf("Update Successfully!\n");
                                Save_Animal_Data(animal, current_animal_count);
                                Activity_Log(logged_in_name, logged_in_id, "Updated Animal's Name", animal[index].id);
                                break;
                            case 2 :
                                printf("Enter New ID : ");
                                char new_id[10];
                                bool isDuplicate;
                                do {
                                    scanf("%9s", new_id);
                                    isDuplicate = false;
                                    for (int i = 0; i < *current_animal_count; i++){
                                        if (i != index && strcmp(new_id, animal[i].id) == 0){
                                            printf("ID already exists. Please enter a different ID : ");
                                            isDuplicate = true;
                                            break;
                                        }
                                    }
                                } while (isDuplicate);
                                strcpy(animal[index].id, new_id);
                                printf("\n");
                                printf("Update Successfully!\n");
                                Save_Animal_Data(animal, current_animal_count);
                                Activity_Log(logged_in_name, logged_in_id, "Updated Animal's ID", animal[index].id);
                                break;
                            case 3:
                                printf("Enter New Sex (F/M): ");
                                scanf(" %c",&animal[index].sex);
                                printf("\n");
                                printf("Update Successfully!\n");
                                Save_Animal_Data(animal, current_animal_count);
                                Activity_Log(logged_in_name, logged_in_id, "Updated Animal's Sex", animal[index].id);
                                break;
                            case 4:
                                printf("Enter New Age : ");
                                scanf("%d",&animal[index].age);
                                printf("\n");
                                printf("Update Successfully!\n");
                                Save_Animal_Data(animal, current_animal_count);
                                Activity_Log(logged_in_name, logged_in_id, "Updated Animal's Age", animal[index].id);
                                break;
                            case 5:
                                printf("Enter New Species : ");
                                scanf(" %49[^\n]",animal[index].species);
                                printf("\n");
                                printf("Update Successfully!\n");
                                Save_Animal_Data(animal, current_animal_count);
                                Activity_Log(logged_in_name, logged_in_id, "Updated Animal's Species", animal[index].id);
                                break;
                            case 6:
                                printf("Enter New Natural Habitat : ");
                                scanf(" %49[^\n]",animal[index].natural_habitat);
                                printf("\n");
                                printf("Update Successfully!\n");
                                Save_Animal_Data(animal, current_animal_count);
                                Activity_Log(logged_in_name, logged_in_id, "Updated Animal's Natural Habitat", animal[index].id);
                                break;
                            case 7:
                                printf("Enter New Zone : ");
                                scanf(" %c",&animal[index].zone);
                                printf("\n");
                                printf("Update Successfully!\n");
                                Save_Animal_Data(animal, current_animal_count);
                                Activity_Log(logged_in_name, logged_in_id, "Updated Animal's Zone", animal[index].id);
                                break;
                            case 8:
                                printf("Enter New Origin : ");
                                scanf(" %49[^\n]",animal[index].origin);
                                printf("\n");
                                printf("Update Successfully!\n");
                                Save_Animal_Data(animal, current_animal_count);
                                Activity_Log(logged_in_name, logged_in_id, "Updated Animal's Origin", animal[index].id);
                                break;
                            case 9:
                                printf("Enter New Food Category : ");
                                scanf("%14s",animal[index].food_category);
                                printf("\n");
                                printf("Update Successfully!\n");
                                Save_Animal_Data(animal, current_animal_count);
                                Activity_Log(logged_in_name, logged_in_id, "Updated Animal's Food Category", animal[index].id);
                                break;
                            case 10:
                                printf("Enter New Class : ");
                                scanf("%14s",animal[index].class);
                                printf("\n");
                                printf("Update Successfully!\n");
                                Save_Animal_Data(animal, current_animal_count);
                                Activity_Log(logged_in_name, logged_in_id, "Updated Animal's Class", animal[index].id);
                                break;
                            case 11:
                                clearScreen();
                                printf("Exited The System Successfully!\n");
                                running1  = 0;
                                break;
                            default :
                                clearScreen(); 
                                printf("Invalid Choice.\n");
                                break;
                        }
                    }
                break;
            case 2 : 
                int running2 = 1;
                while (running2 == 1){
                    int health_info_choice = Update_Health_Information_Menu();
                    clearScreen();
                    printf("\n===== Update Animal's Health Information =====\n");
                        switch (health_info_choice){
                            case 1 :
                                printf("Enter New Height : ");
                                scanf("%4s",animal[index].health.height);
                                printf("\n");
                                printf("Update Successfully!\n");
                                Save_Animal_Data(animal, current_animal_count);
                                Activity_Log(logged_in_name, logged_in_id, "Updated Animal's Height", animal[index].id);
                                break;
                            case 2 :
                                printf("Enter New Weight : ");
                                scanf("%4s",animal[index].health.weight);
                                printf("\n");
                                printf("Update Successfully!\n");
                                Save_Animal_Data(animal, current_animal_count);
                                Activity_Log(logged_in_name, logged_in_id, "Updated Animal's Weight", animal[index].id);
                                break;
                            case 3:   
                                printf("Enter New Health Condition : ");
                                scanf(" %49[^\n]",animal[index].health.health_condition);
                                printf("\n");
                                printf("Update Successfully!\n");
                                Save_Animal_Data(animal, current_animal_count);
                                Activity_Log(logged_in_name, logged_in_id, "Updated Animal's Health Condition", animal[index].id);
                                break;
                            case 4 :
                                printf("Enter New Breeding Status : ");
                                scanf("%9s",animal[index].health.breeding_status);
                                printf("\n");
                                printf("Update Successfully!\n");
                                Save_Animal_Data(animal, current_animal_count);
                                Activity_Log(logged_in_name, logged_in_id, "Updated Animal's Breeding Status", animal[index].id);
                                break;
                            case 5:
                                printf("Enter Last Check Up Date : ");
                                scanf("%d/%d/%d", &animal[index].health.last_checkup_date.day
                                                , &animal[index].health.last_checkup_date.month
                                                , &animal[index].health.last_checkup_date.year);
                                printf("\n");
                                printf("Update Successfully!\n");
                                Save_Animal_Data(animal, current_animal_count);
                                Activity_Log(logged_in_name, logged_in_id, "Updated Animal's Last Checkup Date", animal[index].id);
                                break;
                            case 6 :
                                printf("Enter Next Check Up Date : ");
                                scanf("%d/%d/%d", &animal[index].health.next_checkup_date.day
                                                , &animal[index].health.next_checkup_date.month
                                                , &animal[index].health.next_checkup_date.year);   
                                printf("\n");
                                printf("Update Successfuly!\n");
                                Save_Animal_Data(animal, current_animal_count);
                                Activity_Log(logged_in_name, logged_in_id, "Updated Animal's Next Checkup Date", animal[index].id);
                                break;
                            case 7 :
                                clearScreen();
                                printf("Exited The System Successfully!\n");
                                running2 = 0;
                                break;
                            default :
                                clearScreen();
                                printf("Invalid Choice.\n");
                                break;
                        }
                    }
                break;
            case 3 : 
                int running3 = 1;
                while (running3 == 1){
                    int feeding_info_choice = Update_Feeding_Information_Menu();
                    clearScreen();
                    printf("\n===== Update Animal's Feeding Information =====\n");
                        switch(feeding_info_choice){
                            case 1 :
                                printf("Enter Feeding Status (Fed/Unfed): ");
                                scanf("%9s",animal[index].feeding.feeding_status);
                                printf(":\n");
                                printf("Update Successfully!\n");
                                Save_Animal_Data(animal, current_animal_count);
                                Activity_Log(logged_in_name, logged_in_id, "Updated Animal's Feeding Status", animal[index].id);
                                break;
                            case 2 :
                                printf("Enter Last Feeding Time : ");
                                scanf("%d:%d:%d", &animal[index].feeding.last_feeding.hour
                                                , &animal[index].feeding.last_feeding.min
                                                , &animal[index].feeding.last_feeding.sec);
                                printf("\n");
                                printf("Update Successfully!\n");
                                Save_Animal_Data(animal, current_animal_count);
                                Activity_Log(logged_in_name, logged_in_id, "Updated Animal's Last Feeding Time", animal[index].id);
                                break;
                            case 3 :
                                printf("Enter Next Feeding Time : ");
                                scanf("%d:%d:%d", &animal[index].feeding.next_feeding.hour
                                                , &animal[index].feeding.next_feeding.min
                                                , &animal[index].feeding.next_feeding.sec);
                                printf("\n");
                                printf("Update Successfully!\n");
                                Save_Animal_Data(animal, current_animal_count);
                                Activity_Log(logged_in_name, logged_in_id, "Updated Animal's Next Feeding Time", animal[index].id);
                                break;
                            case 4 :
                                clearScreen();
                                printf("Exited The System Successfully!\n");
                                running3 = 0;
                                break;
                            default :
                            clearScreen(); 
                            printf("Invalid Choice.\n");
                            break;
                        }
                    }
                break;
            case 4 :
                printf("Exited The System Successfully!\n");
                running = 0;
                break;
            default :
                printf("Invalid Choice.\n");
                break;
        }
    }
}

void Print_All_Animal(Animal_Info animal[], int* current_animal_count){
    paginate_animal_ptr = animal;
    Paginate(*current_animal_count, Print_Animal_For_Paginate);
}

void Delete_Animal(Animal_Info animal[], int* current_animal_count, char* logged_in_name, char* logged_in_id){
    printf("\n===== Delete Animal =====\n");
    char search_id[10];
    char answer;

    printf("Enter Search ID : ");
    scanf("%9s",search_id);

    printf("Search ID is : %s\n", search_id);

    printf("Are you sure you want to delete this Animal with ID %s? (Y/N) : ", search_id);
    scanf(" %c", &answer);
    if (answer == 'Y' || answer == 'y'){
        int index = Search_Animal_ID(animal, current_animal_count, search_id);
        if (index == -1){
            return;
        }
        
        for (int i = index; i < *current_animal_count - 1; i++){
            animal[i] = animal[i+1];
        }
        (*current_animal_count)--;
        printf("Animal Deleted Successfully.\n");
        Save_Animal_Data(animal, current_animal_count);
        Activity_Log(logged_in_name, logged_in_id, "Deleted Animal", search_id);
    }else {
        return;
    }
}

void Animal_Management(Animal_Info animal[], int* current_animal_count, char* logged_in_name, char* logged_in_id){
    int running = 1;
    while (running == 1){
        int animal_management_choice = Animal_Management_Menu();
        clearScreen(); 
        switch(animal_management_choice){
            case 1 :
                clearScreen(); 
                Print_All_Animal(animal, current_animal_count);
                clearScreen(); 
                break;
            case 2 : 
                clearScreen();
                Search_Animal(animal, current_animal_count);
                break;
            case 3 :
                clearScreen();
                Add_Animal(animal, current_animal_count, logged_in_name, logged_in_id);
                pauseAndClear();
                break;
            case 4 :
                clearScreen();
                Update_Animal(animal, current_animal_count, logged_in_name, logged_in_id);
                break;
            case 5 :
                clearScreen();
                Delete_Animal(animal, current_animal_count, logged_in_name, logged_in_id);
                pauseAndClear();
                break;
            case 6 :
                printf("Exited The System Successfully!\n");
                running = 0;
                break;
            default : 
                printf("Invalid Choice.\n");
                break;
        }
    }
}

void Guest (Animal_Info animal[], int* current_animal_count){
    int running = 1;
    while (running == 1){
        int guest_menu_choice = Guest_Menu();
        clearScreen();
        switch(guest_menu_choice){
            case 1 :
                clearScreen(); 
                Print_All_Animal(animal, current_animal_count);
                clearScreen();
                break;
            case 2 :
                clearScreen();
                Search_Animal(animal, current_animal_count);
                break;
            case 3 :
                printf("Exited The System Successfully!\n");
                running = 0;
                break;
            default :
                printf("Invalid Choice.\n");
                break;
        }
    }
}
#endif