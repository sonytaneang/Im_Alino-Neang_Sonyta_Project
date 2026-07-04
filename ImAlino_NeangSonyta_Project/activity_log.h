#ifndef ACTIVITY_LOG_H
#define ACTIVITY_LOG_H
#include "pagination.h"

#define MAX_LOG_LINES 1000

void Activity_Log(const char* staff_name, const char* staff_id, const char* action, const char* target) {
    FILE* fp = fopen("activity_log.txt", "a");
    if (fp == NULL) {
        printf("Warning: Could not write to activity log.\n");
        return;
    }

    time_t now = time(NULL); // time_t now holds the number of seconds from 1 Jan 1970 (epoch ), raw computer friendly time
    struct tm* t = localtime(&now); //converts it to human readable time

    fprintf(fp, "[%04d-%02d-%02d %02d:%02d:%02d] %s (%s) | %s | %s\n",
        t->tm_year + 1900, //1900+126
        t->tm_mon  + 1,
        t->tm_mday,
        t->tm_hour,
        t->tm_min,
        t->tm_sec,
        staff_name,
        staff_id,
        action,
        target);

    fclose(fp);
}

char log_lines[MAX_LOG_LINES][512];
int lineCount = 0;

void Print_Log_Line_For_Paginate(int i){
    printf("%s", log_lines[i]);
}



void View_Activity_Log(int compare_position) {
    if (compare_position == 0){
        FILE *fp = fopen("activity_log.txt", "r");
        if (fp == NULL) {
            printf("No activity log found or Error while opening file.\n");
            return;
        }
        lineCount = 0;
        while (lineCount < MAX_LOG_LINES && fgets(log_lines[lineCount], sizeof(log_lines[lineCount]), fp) != NULL){
            lineCount++;
        }
        fclose(fp);
        
        if (lineCount == 0){
            printf("Log is empty.\n");
        }
        printf("\n========== ACTIVITY LOG ==========\n");
        Paginate(lineCount, Print_Log_Line_For_Paginate);
        printf("===================================\n");
    }else {
        printf("Authorized Access Only!\n");
        return;
    }
}
#endif
