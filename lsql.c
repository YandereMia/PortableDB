#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <dirent.h>
void dispatcher(const char *cmd);
char dbname[256];
#define MAX_DB 64
int main() {
  while(1) {
    printf("LSQL[%s]> ", dbname);
    char cmd[256];
    fgets(cmd, sizeof(cmd), stdin);
    cmd[strcspn(cmd, "\r\n")] = 0;
    dispatcher(cmd);
  }
}

void dispatcher(const char *cmd) {
  if (strncmp(cmd, "CREATE_DB ", 10) == 0) {
    if (strcmp(dbname, cmd+10) == 0) {
      printf("Database: %s already exists\n", dbname);
      return;
    }
    strcpy(dbname, cmd+10);
    char tmp[256];
    strcpy(tmp, dbname);
    strcat(tmp, ".db");
    FILE *fptr;
    fptr = fopen(tmp, "w");
	printf("created db: %s\n", cmd+10);
    fclose(fptr);
    return;
  }
  if (strncmp(cmd, "CREATE_USR ", 11) == 0) {
    if (strcmp(dbname, "") == 0) { printf("not in Database\n"); return;}
    FILE *fptr;
    char tmp[256];
    strcpy(tmp, dbname);
    strcat(tmp, ".db");
    fptr = fopen(dbname, "a");
    fprintf(fptr, "user: %s\n", cmd+11);
    printf("User: %s Written to DB: %s\n", cmd+11,dbname);
    fclose(fptr);
    return;
  }
  if (strcmp(cmd, "LIST_USR") == 0) {
    char tmp[256];
    strcpy(tmp, dbname);
    strcat(tmp, ".db");
    if (strcmp(dbname, "") == 0) { printf("not in Database\n"); return;}
    FILE *fptr;
    fptr = fopen(tmp, "r");
    char users[8192] = "";
    char line[256];
    while(fgets(line, sizeof(line), fptr)) {
      if (strncmp(line, "user: ", 6) == 0) {
        strcat(users, line + 6);
      }
    }
    printf("Users:\n%s", users);
    fclose(fptr);
    return;
  }
  if (strcmp(cmd, "LIST_DB") == 0) {
    DIR *d;
    struct dirent *dir;
    d = opendir(".");
    if (d) {
      printf("DB List:\n");
      while ((dir = readdir(d)) != NULL) {
        char *dot = strrchr(dir->d_name, '.');
        if (dot && !strcmp(dot, ".db")) {
          printf("%s\n", dir->d_name);
        }
      }
      closedir(d);
    }
    return;
  }
  if (strncmp(cmd, "USE ", 4) == 0) {
    FILE *fptr;
    char tmp[256];
    strcpy(tmp, cmd+4);
    strcat(tmp, ".db");
    fptr = fopen(tmp, "r");
    if (!fptr) {
      perror("No such Database");
      return;
    }
    fclose(fptr);
    strcpy(dbname, cmd+4);
    printf("Changed Database to: %s\n",dbname);
    return;
  }
  if (strcmp(cmd, "\\q") == 0) {
  	exit(0);
  }
  printf("invalid syntax: %s\n", cmd);
}
