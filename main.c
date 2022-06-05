#include "header.h"
int main(){
    printf("***********************************\n");
    printf("********     DigiLib       ********\n");
    printf("***********************************\n");
    currenttime();
    int numofbook;
    User user;
    //partie user
    int ligneUser; 
    //char nomUser[1000], prenomUser[1000], mdpUser[1000], roleUser[1000] ;
    ligneUser =  connexion_user();
    char sautligne[10000];
    char temp[10], temp2[11];
    FILE* fichier = NULL;
    fichier = fopen("texte.txt","r+");
    if(fichier == NULL){
        printf("Problem with openning the list of user!!\n");
        exit(1);
    }
    for(int i=0;i<ligneUser-1;i++){
        fgets(sautligne, 9999, fichier);
    }
    fscanf(fichier, "%s ", user.nom);
    fscanf(fichier, "%s ", user.prenom);
    fscanf(fichier, "%s ", temp2);
    fscanf(fichier, "%s ", temp);
    strcmp(user.MDP, temp2); 
    if(strcmp(temp, "1")==0){
        user.role = 1;
    }
    if(strcmp(temp, "0")==0){
        user.role = 0;
    }
    fclose(fichier);
    //printf("%s %s %s %s \n", user.nom, user.prenom, user.mdp, user.role);
    FILE *file=fopen("library.txt","r+");
    if (file==NULL){
       printf("Problem with openning the library!!\n");
       exit(1);
    }
    numofbook=checkfilelength(file);
    Book *book=NULL;
    book=malloc(sizeof(Book)*numofbook);
    if (book==NULL){
        printf("Memory allocation issue book!!\n");
        exit(1);
    }

    for(int i=0;i<numofbook;i++){
        book[i]=recuplivre(i+1);
        // printf("%s\n", book[i].author);
    }
    fclose(file);
    check_userbooks(user,book,numofbook); 
    int nextstep=0;
    int again=0;
    //printf("%d",user.role);
    while(again==0){
        if(user.role==1){
           while(nextstep<=0  || nextstep>4){
                printf("What do you want to do:\n");
                printf("1.Borrow a book.\n");
                printf("2.Return a book.\n");
                printf("3.Add a book\n");
                printf("4.Log out.\n");
                nextstep=read_int(1,4);
            }    
            if(nextstep==1){
                int id;
                if(user.amount<5){
                showbooks(book,numofbook);
                printf("which is the id of the book you want to borrow ?");
                scanf("%d", &id);
                book[id] = borrowbook(user,book[id]);
               /* for (int i = 0; i < numofbook; i++){
                    printf("%s %s %s %s %d %d %d\n", book[i].title, book[i].author, book[i].username, book[i].username2, book[i].status, book[i].category, book[i].id);
                }*/
                user.amount=user.amount+1;
            }
            else{
                printf("You reached the maximum number of books to borrow\n");
            }
                again=0;
                nextstep = 0;
            }
            if(nextstep==2){
                int id;
                printf("Which book do you wanna return(type in one the id of the books shown to you when you signed in)\n");
                id=read_int(1,numofbook);
                book[id]=return_book(book[id]);
                again=0;
                nextstep = 0;
            }
            if(nextstep==3){
                addbook(user);
                numofbook=checkfilelength(file);
                book=malloc(sizeof(Book)*numofbook);
                if (book==NULL){
                    printf("Memory allocation issue book!!\n");
                   exit(1);
                }   
                for(int i=0;i<numofbook;i++){
                    book[i]=recuplivre(i+1);
                }
                again=0;
                nextstep = 0;
           }
            if(nextstep==4){
                 //soit exit(1) soit login encore
                 again=1; 
           }
     
           
    
       }
       if(user.role==0){
           while(nextstep<=0  || nextstep>3){
                printf("What do you want to do:\n");
                printf("1.Borrow a book.\n");
                printf("2.Return a book.\n");
                printf("3.Log ou.\n");
                nextstep=read_int(1,3);
            if(nextstep==1){
                int id;
                if(user.amount<3){
                showbooks(book,numofbook);
                printf("which is the id of the book you want to borrow ?");
                scanf("%d", &id);
                book[id] = borrowbook(user,book[id]);
                for (int i = 0; i < numofbook; i++){
                    printf("%s %s %s %s %d %d %d\n", book[i].title, book[i].author, book[i].username, book[i].username2, book[i].status, book[i].category, book[i].id);
                }
                
                user.amount=user.amount+1;
            }
            else{
                printf("You reached the maximum number of books to borrow\n");
            }
                again=0;
                nextstep = 0;
            }
            if(nextstep==2){
                int id;
                printf("Which book do you wanna return(type in one the id of the books shown to you when you signed in)\n");
                id=read_int(1,numofbook);
                book[id]=return_book(book[id]);
                again=0;
                nextstep = 0;
            }

           }
            if(nextstep==3){
                 //soit exit(1) soit login encore
                 again=1; 
           }
     
           }           
       }
    
    new_library(book,numofbook);
    return 0;
    
}
