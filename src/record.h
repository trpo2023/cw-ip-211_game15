#pragma once

#define MAX_NUM_RECORDS 10
#define MAX_NAME_LENGTH 8

typedef struct {
    char name[MAX_NAME_LENGTH];
    int score;
} Record;

void LoadLeaders(Record* records, int* num_records, char* leader_path);

void SaveLeaders(Record* records, int num_records, char* leader_path);

void AddLeader(Record* records, int* num_records, char* name, int score);

void PrintLeaderboard(Record* records, int num_records);
