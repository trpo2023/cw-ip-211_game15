#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "record.h"

int CompareLeaders(const void* a, const void* b)
{
    const Record* record_a = (const Record*)a;
    const Record* record_b = (const Record*)b;
    return record_b->score - record_a->score;
}

void LoadLeaders(Record* records, int* num_records, char* leader_path)
{
    FILE* file = fopen("leader_path.txt", "r");
    char name[MAX_NAME_LENGTH];
    int score;
    if (file) {
        *num_records = 0;
        while ((*num_records < MAX_NUM_RECORDS)
               && (fscanf(file, "%s %d", name, &score) == 2)) {
            Record new_record;
            strcpy(new_record.name, name);
            new_record.score = score;
            records[*num_records] = new_record;
            (*num_records)++;
        }
        fclose(file);
    } else
        printf("\nCan't open leaderboard!\n");
}

void SaveLeaders(Record* records, int num_records, char* leader_path)
{
    FILE* file = fopen(leader_path, "w");
    if (file) {
        for (int i = 0; i < num_records; i++) {
            fprintf(file, "%s %d\n", records[i].name, records[i].score);
        }
        fclose(file);
    }
}

void AddLeader(Record* records, int* num_records, char* name, int score)
{
    Record new_record;
    strcpy(new_record.name, name);
    new_record.score = score;
    if (*num_records < MAX_NUM_RECORDS) {
        records[*num_records] = new_record;
        (*num_records)++;
    } else {
        int insert_index = -1;
        for (int i = 0; i < MAX_NUM_RECORDS; i++) {
            if (new_record.score > records[i].score) {
                insert_index = i;
            }
        }
        if (insert_index != -1) {
            for (int i = MAX_NUM_RECORDS - 1; i > insert_index; i--) {
                records[i] = records[i - 1];
            }
            records[insert_index] = new_record;
        }
    }
    qsort(records, *num_records, sizeof(Record), CompareLeaders);
}
