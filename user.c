#include "header.h"
//vérifie que le mot de passe est sécurisé//
void verifMdp( User * a){
    char mdp[100];
    bool Maj = false;
    bool spe = false;
    bool nb = false;
    int taille;
    while(Maj != true || spe != true || nb != true){
        printf("Type in your password ?(It needs to be 10 character max and needs to have and uppercase,special charcter and a number)\n");
        scanf("%s", mdp);
        taille = strlen(mdp);
        for(int i=0; i<taille; i++){
            //chack if there is at least one uppercase//
            if (mdp[i] <= 'Z' && mdp[i] >= 'A'){
                Maj = true;
            }
            //check if ther is at least one number//
            if(mdp[i] <= '9' && mdp[i] >= '0'){
                nb = true;
            }
            //check if ther is at least one special character//
            if ((mdp[i] <= '/' && mdp[i] >= '!') || (mdp[i] <= '@' && mdp[i] >= ':') || (mdp[i] <= '`' && mdp[i] >= '[') || (mdp[i] <= '~' && mdp[i] >= '{')){
                spe = true;
            }
        }
        if (Maj == false || spe == false || nb == false){
            printf("The password doesn't respect the stated condtions\nPlease enter a new password.\n");
        }
    }
    printf("password respects the conditons\n");
     a->MDP=malloc(sizeof(char)*(taille+1));
        strcpy(a->MDP, mdp );
}

//fonction qui vérifie que les identifiants n'existent pas déjà
void verifUser(User * a){
    char sautligne[10000];
    char tempFstName[1000];
    char tempSndName[1000];
    char tempsMdp[100];
    int length, count1, count2;
    FILE* fichier = NULL;
     fichier = fopen("texte.txt","r+");
    if(fichier == NULL){
        printf("erreur d'ouverture");
        connexion_user();
    }
    length = checkfilelength(fichier);
    rewind(fichier);
    for(int i=0;i<length-1;i++){
        fgets(sautligne, 9999, fichier);
        fscanf(fichier, "%s", tempFstName);
        fscanf(fichier, "%s", tempSndName);
        fscanf(fichier, "%s", tempsMdp);
        if(strcmp(tempFstName, a->nom) == 0 && strcmp(tempSndName, a->prenom) == 0){
            printf("This profil exits already\n");
            exit(1);
        }
    } 
    fclose(fichier);
}

//fonction qui construit les nouveaux utilisateurs//
User build_user(){
    User user1;
    printf("What is your last name ?\n");
    scanf("%s", user1.nom );
    printf("What is your first name ?\n");
    scanf("%s", user1.prenom );
    verifMdp(&user1);
    while(1!=2){
        printf("What is your occupation in this university (0 student et 1 profossor) ?\n");
        user1.role=read_int(0,1);
        if(user1.role != 0 && user1.role != 1){
            printf("Please enter a valid occupation\n");
        }
        else{
            break;
        }
    }
    verifUser(&user1);
    return user1;
}

//procédure qui vérifie les noms, prénoms et mots de passe des utilisateurs//
int login(char testnom[1000], char testprenom[1000], char testmdp[100], int connect){
    FILE* fichier = NULL;
    char sautligne[10000];
    char tempFstName[1000];
    char tempSndName[1000];
    char tempsMdp[100];
    int length, count1 = 0, count2 = 0, ligne;
    fichier = fopen("texte.txt","r+");
    if(fichier == NULL){
        printf("erreur d'ouverture");
        exit(1);
    }
    length = checkfilelength(fichier);
    rewind(fichier);
    for(int i=0;i<length-1;i++){
        fgets(sautligne, 99, fichier);
        fscanf(fichier, "%s", tempFstName);
        fscanf(fichier, "%s", tempSndName);
        fscanf(fichier, "%s", tempsMdp);
        if(strcmp(tempFstName, testnom) != 0 || strcmp(tempSndName, testprenom) != 0){
            count1 = count1 + 1;        //compte le nombre de fois où le nom et le prénom sont différents de ceux rentrés//
        }
        else{
            if(strcmp(tempsMdp,testmdp) != 0){
                count2 = count2 + 1;    //compte le nombre de fois où le mot de passe associé aux nom et prénom est différent de celui rentré//
            }
        }
    }
    if(count1 != length-2){
        printf("User name is incorrect\n\n");
        connect = 2;
    }
    else{
        if(count2 != 0){
            printf("Wrong password\n\n");
            connect = 2;
        }
        else{
            connect = 0;
        }  
    }
    fclose(fichier);
    return connect;
}

int recupUser(char testnom[1000], char testprenom[1000]){
    FILE* fichier = NULL;
    fichier = fopen("texte.txt","r+");
    if(fichier == NULL){
        printf("erreur d'ouverture\n");
        exit(1);
    }
    char sautligne[10000];
    char tempFstName[1000];
    char tempSndName[1000];
    int length, ligne = 1;
    length = checkfilelength(fichier);
    rewind(fichier);
    for(int i=0;i<length-1;i++){
        fgets(sautligne, 9999, fichier);
        fscanf(fichier, "%s", tempFstName);
        fscanf(fichier, "%s", tempSndName);
        ligne++;
        if(strcmp(tempFstName, testnom) == 0 && strcmp(tempSndName, testprenom) == 0){
            break;
        }
    }
    fclose(fichier);
    return ligne;
}

//procédure qui enregistre les utilisateurs dans la base de donnée//
void SaveUser(char nom[1000], char prenom[1000] , char* mdp , int role){
    FILE* fichier = NULL;
    fichier = fopen("texte.txt","a+");
    if(fichier == NULL){
        printf("erreur d'ouverture");
        exit(1);
    }
    //enregistre les données rentrées lors de l'inscription dans un fichier texte//
    fputs("\n", fichier);
    fprintf(fichier,"%s", nom);
    fprintf(fichier,"%c", ' ');
    fprintf(fichier,"%s", prenom);
    fprintf(fichier, "%c", ' ');
    fprintf(fichier, "%s", mdp);
    fprintf(fichier, "%c", ' ');
    if(role == 1){
        fprintf(fichier, "1" );
    }
    else{
        fprintf(fichier, "0");
    }
    fclose(fichier);
}

//fonction qui connecte l'utilisateur a la bibliothèque//
int connexion_user(){
    int ligne,  end1 = 0, connect = 2;
    User a;
    char testnom[1000];
    char testprenom[1000];
    char testmdp[100];
    while(end1 !=1){
        while(connect !=0){
            printf("\nWelcome to our library !\nDo you want to:\n0.Sign in\n1.Sign up\n");
            connect=read_int(0,1); 
            if (connect == 1){
                a = build_user();
                SaveUser(a.nom, a.prenom, a.MDP, a.role);
                connect = 1;
            }
            if(connect != 1 && connect != 0){
                printf("You teasing me you naughty naughty ( ͡° ͜ʖ ͡°) \n");
                connexion_user();
            }
        
        } 
        printf("Please enter your last name\n");
        scanf("%s",testnom);
        printf("Please enter your fist name\n");
        scanf("%s",testprenom);
        printf("Please enter your password\n");
        scanf("%s",testmdp);
        connect = login(testnom, testprenom, testmdp, end1);
        if(connect == 0){
            ligne = recupUser(testnom, testprenom);
            end1 = 1;
        }
    }
    return ligne;    
}