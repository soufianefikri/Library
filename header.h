#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#define maxline 2000
typedef struct{
    char title[1000];
    char author[200];
    char username[1000];
    char username2[1000];
    int status;
    int category;
    int id;
    int hreturn;
    int minreturn;
}Book;
typedef struct{
    char prenom[1000];
    char nom[1000];
    char* MDP;
    int role;   // 0 = student et 1 = professor//
    int autorisation; // 0:cant borrow 1:can borrow
    int amount;
}User;
void currenttime();
int timeh();
int timem();
int checkfilelength(FILE*fichier);
int read_int(int min, int max);
void readline( int read_line, FILE *filemidd);
Book recuplivre(int num);
void tri_alphabetiquetitle(Book tab[],int taille);
void showbooks(Book book[],int taille);
Book borrowbook(User user, Book tab);
void addbook(User user);
void new_library(Book book[],int numofbook);
void check_userbooks(User user,Book book[], int numofbook);
void verifMdp( User * a);
void verifUser(User * a);
User build_user();
int login(char testnom[1000], char testprenom[1000], char testmdp[100], int connect);
int recupUser(char testnom[1000], char testprenom[1000]);
void SaveUser(char nom[1000], char prenom[1000] , char* mdp , int role);
int connexion_user();
Book return_book(Book book);
