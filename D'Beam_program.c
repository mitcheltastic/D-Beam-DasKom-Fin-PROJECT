#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

FILE *UserDataList;
FILE *UserDataListAE; //After Erasing
FILE *AdminData;
FILE *UserHistory;

const char *green = "\033[32m";

struct User{
    char username[100], password[100];
    int balance, rideCount;
}user[100];
struct Admin{
    char name[100], review[200];
    int Income, userRating;
}admin[500];
struct History{
    char name[100], ridingHistory[1000]; 
    int userRideCount;
}history[500];

char usernameUser[100], passwordUser[100];
int initialDisplaycount = 0;

void print_colored(const char *text, const char *color_code){
    printf("%s%s\033[0m", color_code, text);
}
void header(){
    printf("Developers:                                                                                    \n");
    printf("1. Mitchel Mohamad Affandi\t\t\t\t\t\t\t\t\t       ___ _  ___  _______   __  ___           \n");
    printf("2. Bagas Maharda Wisesa\t\t\t\t\t\t\t\t\t  ____________/ _ ( )/ _ )/ __/ _ | /  |/  /___________\n");
    printf("3. Abraham Benedick\t\t\t\t\t\t\t\t\t /___/___/___/ // /// _  / _// __ |/ /|_/ /___/___/___/\n");
    printf("4. Muhammad Rafi Edra Zen\t\t\t\t\t\t\t        /___/___/___/____/ /____/___/_/ |_/_/  /_/___/___/___/ \n");
    printf("5. Noer Moehammad Farhan Imansjah\n\n--> Created by: Group 2 - (TT-47-INT) <--\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t     Beta version...\n");
    printf("=============================================================================================================================================================================================================================================\n");
}
void adminSeeUser(){
    void adminMenu();
    char toDelete[30], choice;
    int num;
    UserDataList = fopen("User List.dat", "rb");
    UserDataListAE = fopen("User List temp.dat", "wb");
    printf("\n============== D'BEAM USERS' LIST ==============\n");
    while (fread(&user, sizeof(user), 1, UserDataList) == 1){
        printf("=============");
        printf("\nUser %d", num + 1);
        printf("\nName: %s\n", user->username);
        num++;
    }
    fseek(UserDataList, 0, SEEK_SET);
    printf("\n================================================\nDo you want to delete a user?(y/n): "); getchar();
    scanf("%c", &choice);
    if(choice == 'y'){
        printf("==> Please Input the name of User to be deleted: ");getchar();
        gets(toDelete);

        while (fread(&user, sizeof(user), 1, UserDataList) == 1){
            if (strcmp(user->username, toDelete) != 0){
                fwrite(&user, sizeof(user), 1, UserDataListAE);
            }
        }
        printf("==>'%s' has been deleted from the database<==\n\n", toDelete);
    }
    else{
        while (fread(&user, sizeof(user), 1, UserDataList) == 1){
            fwrite(&user, sizeof(user), 1, UserDataListAE);
        }
    }
    fclose(UserDataList);
    fclose(UserDataListAE);
    remove("User List.dat");
    rename("User List temp.dat", "User List.dat");
    system("pause");
    adminMenu();
}

 void adminSeeIncome(){
    void adminMenu();
    int total = 0;
    int num = 1;
    AdminData = fopen("AdminIncome.dat","rb");
    printf("======================INCOME FROM USER======================\n");
    while(fread(&admin,sizeof(admin),1,AdminData)==1){
        printf("%d. Income From '%s': Rp.%d,00\n",num++, admin->name, admin->Income);
        total += admin->Income;
        printf("==================================");
        printf("\n");
    }
    fclose(AdminData);
    printf("Total Income: Rp.%d,00\n", total);
    system("pause");
    adminMenu();
 }
void adminSeeRating(){
    void adminMenu();
    int num = 1;
    AdminData = fopen("AdminRate&Review.dat","rb");
    printf("======================RATING FROM USER======================\n");
    while(fread(&admin,sizeof(admin),1,AdminData)==1){
        printf("%d. Rating from %s: %d/10\n",num++, admin->name, admin->userRating);
        printf("Review: %s", admin->review);
        printf("\n==================================\n");
    }
    fclose(AdminData);
    system("pause");
    adminMenu();
}
void adminMenu(){ //ADMIN MENU
    int adminMenuChoice;
    void adminStart();
    void adminSeeUser();
    void adminMenu();
    void adminSeeIncome();
    void adminSeeRating();
    void header();
    void print_colored();
    system("cls");
    header();
    printf("====================== ADMIN MAIN MENU ======================");
    print_colored("\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t*YOU ARE LOGGED IN AS ADMIN!*\n", green);
    printf("| What would you like to do as admin?                       |\n");
    printf("| 1. Check & Delete Users' Data                             |\n");
    printf("| 2. Check Income                                           |\n");
    printf("| 3. See Ratings from Users                                 |\n");
    printf("| 4. Return                                                 |\n");
    printf("=============================================================\n");
    printf("==> Input (for example: '1'): ");
    scanf("%d", &adminMenuChoice);

    switch (adminMenuChoice){
        case(1):
            adminSeeUser(); //Feature-1
            break;
        case(2):
            adminSeeIncome(); //Feature-2
            break;
        case(3):
            adminSeeRating(); //Feature-3
            break;
        case(4):
            adminStart(); //Feature-4
            break;
        default:
            printf("Invalid choice.\n");
            adminMenu();
            break;
    }
}

void adminStart(){
    void main();
    void adminMenu();
    void header();
    char username[20], password[20];
    int  loginAttempt = 4;
    int switcher;
    system("cls");

    header();
    printf("====================== !ADMIN INITIALIZATION! ======================\n");
    printf("| Do you want to log in as admin?                                  |\n");
    printf("| 1. Log In                                                        |\n");
    printf("| 2. Return                                                        |\n");
    printf("====================================================================\n");
    printf("==> Choose (for example: '1'): ");
    scanf("%d", &switcher);printf("\n");
    switch(switcher){
    case(1):
        do{
        printf("============================ ADMIN LOGIN ===========================\n");
        printf("| -> Insert username: ");
        scanf("%s", username);

        printf("| -> Insert password: ");
        scanf("%s", password);

        if(strcmp(username, "admin") == 0 && strcmp(password, "admin12345") == 0){
            printf("You are Logged In!\n");
            adminMenu();
            break;
        }else{
            loginAttempt--;
            system("cls");
            printf("Username or Password is incorrect.\n");
            printf("You have '%d' trials left.\n", loginAttempt);
        }
        }while(loginAttempt > 0);

        if(loginAttempt == 0){
        system("cls");
        printf("You have run out of trials, this app will be closed.\n");
        }
        break;
    case(2):
        main();
        break;
    default:
        printf("Invalid choice.\n");
        system("pause");
        adminStart();
        break;
    }
}
void userSignUp(){
    void userStart();
    int loop, data;
    char temp[100];
    FILE *UserDataList;
    getchar();
    loop = 1;
    UserDataList = fopen("User List.dat", "ab");
    printf("============================ SIGN UP ===========================\n");
    while (loop > 0){
        printf("=> !Create a Username! <=\n");
        printf("|-> Username: ");
        gets(usernameUser);
        printf("|-> Confirm username: ");
        gets(temp);
        if (strcmp(usernameUser, temp) != 0){
            printf("\nPlease re-enter the username");
        }
        else{
            loop--;
        }
    }
    loop = 1;
    while (loop > 0){
        printf("================================================================\n");
        printf("=> !Create a Password! <=\n");
        printf("|-> Password: ");
        gets(passwordUser);
        printf("|-> Confirm password: ");
        gets(temp);
        if (strcmp(passwordUser, temp) != 0){
            printf("\nPlease re-enter the password\n");
        }
        else{
            loop--;
        }
    }
    strcpy(user->username, usernameUser);
    strcpy(user->password, passwordUser);
    user->balance = 0;

    fwrite(&user, sizeof(user), 1, UserDataList);
    fclose(UserDataList);
    userStart();
}
void userLogIn(){
    void userMenu();
    int repeat;
    
    for (repeat = 3; repeat > 0; repeat--){
        UserDataList = fopen("User List.dat", "rb");
        printf("============================= LOG IN ============================\n");
        fflush(stdin);
        printf("Username : ");
        gets(usernameUser);
        printf("Password : ");
        gets(passwordUser);
        while (fread(&user, sizeof(user), 1, UserDataList)){
            if (strcmp(usernameUser, user->username) == 0 && strcmp(passwordUser, user->password) == 0){
            system("cls");
            fclose(UserDataList);
            userMenu();
            return;
            }
        
        }
    if(repeat > 1){
            printf("!! Username or Password is incorrect !!\n");
            printf("!! You Have %d Trials left !!\n", repeat - 1);
        }
    else{
            printf("!! You're no longer able to log in !!\n");
            fclose(UserDataList);
        }
    }
}

void topUpUser(){
    void userMenu();
    FILE *userData;
    int money;

    userData = fopen("User List.dat", "rb+");

    printf("============================= TOP UP ============================\n");
    printf("|-> Add Balance : Rp.");
    scanf("%d", &money);

    while (fread(&user, sizeof(user), 1, userData) == 1) {
        if (strcmp(usernameUser, user->username) == 0){
            user->balance += money;
            fseek(userData, -(long)sizeof(user), SEEK_CUR);
            fwrite(&user, sizeof(user), 1, userData);
            printf("|-> Your Balance: Rp.%d,00\n", user->balance);
            printf("================================================================\n");
            system("pause");
            break;
        }
    }
    fclose(userData);
    userMenu();
}

void userCheckBalance(){
    void userMenu();
    FILE *userData;
    userData = fopen("User List.dat", "rb");
    printf("========================== CHECK BALANCE ========================\n");
    while (fread(&user, sizeof(user), 1, userData) == 1) {
        if (strcmp(usernameUser, user->username) == 0){
            printf("Your Balance: Rp.%d,00\t\t\t\t\t|\n", user->balance);
            break;
        }
    }
    printf("=================================================================\n");
    fclose(userData);
    system("pause");
    userMenu();
}
void userGiveRate(){
    FILE *userData;
    FILE *AdminData;
    char reviewuser[200];
    int rate;
    system("cls");
    printf("\n========RATE YOUR RIDE========\n");
    printf("|-> Please rate your ride :D!\n");
    printf("|-> In the scale of (1-10): ");
    scanf("%d", &rate);
    printf("|-> Review\t          : ");getchar();
    gets(reviewuser);
    userData = fopen("User List.dat", "rb");
    AdminData = fopen("AdminRate&Review.dat", "ab");
    while (fread(&user, sizeof(user), 1, userData) == 1) {
        if (strcmp(usernameUser, user->username) == 0){
            admin->userRating = rate;
            strcpy(admin->name,usernameUser);
            strcpy(admin->review, reviewuser);
            fseek(userData, 0, SEEK_SET);
            fwrite(&admin, sizeof(admin), 1, AdminData);
            break;
        }
    }
    fclose(AdminData);
    fclose(userData);
}

void addition(int cost){
    void userGiveRate();
    FILE *userData;
    FILE *AdminData;
    userData = fopen("User List.dat", "rb+");
    AdminData = fopen("AdminIncome.dat", "ab");

    if (userData == NULL) {
        printf("Error opening file.\n");
        return;
    }
    while (fread(&user, sizeof(user), 1, userData) == 1) {
        if (strcmp(usernameUser, user->username) == 0){
            user->balance -=cost;
            admin->Income = cost;
            strcpy(admin->name,usernameUser);
            fseek(userData, -(long)sizeof(user), SEEK_CUR);
            fwrite(&user, sizeof(user), 1, userData);
            fwrite(&admin, sizeof(admin), 1, AdminData);
            break;
        }
    }
    fclose(AdminData);
    fclose(userData);
    printf("!-> If you have arrived\n\n");
    system("pause");
    printf("\nCongratulations You have arrived\n");
    printf("You have Rp.%d,00 left in your account!\n", user->balance);
    system("pause");
    userGiveRate();
}
void historyOfUser(char route[]){
    FILE *userData;
    FILE *historyOfUser;
    userData = fopen("User List.dat", "rb");
    historyOfUser = fopen("History_User.dat", "ab");
    while (fread(&user, sizeof(user), 1, userData) == 1){
        if (strcmp(usernameUser, user->username) == 0){
            strcpy(history->name, usernameUser);
            strcpy(history->ridingHistory, route);
            fwrite(&history, sizeof(history), 1, historyOfUser);
        }
    }
    fclose(historyOfUser);
    fclose(userData);
}
void rentABike(){
    FILE *userData;
    void userMenu();
    void historyOfUser();
    void addition();
    int choice;
    int cost;
    system("cls");
    printf("\n!!! Please select the route that suits your trip !!!");
    printf("\n=========================== PRICE LIST ===========================");
    printf("\n[1]. FEB/FKB => TULT\t\t[Rp.2.000]\t\t\t |\n[2]. FEB/FKB => Rektorat\t[Rp.3.000]\t\t\t |\n[3]. FEB/FKB => GKU\t\t[Rp.2.000]\t\t\t |\n[4]. FEB/FKB => MSU\t\t[Rp.4.000]\t\t\t |\n");
    printf("[5]. TULT => FEB/FKB\t\t[Rp.2.000]\t\t\t |\n[6]. TULT => Rektorat\t\t[Rp.3.500]\t\t\t |\n[7]. TULT => GKU\t\t[Rp.2.000]\t\t\t |\n[8]. TULT => MSU\t\t[Rp.4.000]\t\t\t |\n");
    printf("[9]. Rektorat => FEB/FKB\t[Rp.3.000]\t\t\t |\n[10]. Rektorat => TULT\t\t[Rp.3.500]\t\t\t |\n[11]. Rektorat => GKU\t\t[Rp.1.500]\t\t\t |\n[12]. Rektorat => MSU\t\t[Rp.2.000]\t\t\t |\n");
    printf("[13]. GKU => FEB/FKB\t\t[Rp.2.000]\t\t\t |\n[14]. GKU => TULT\t\t[Rp.2.000]\t\t\t |\n[15]. GKU => Rektorat\t\t[Rp.1.500]\t\t\t |\n[16]. GKU => MSU\t\t[Rp.3.500]\t\t\t |\n");
    printf("[17]. MSU => FEB/FKB\t\t[Rp.4.000]\t\t\t |\n[18]. MSU => TULT\t\t[Rp.4.000]\t\t\t |\n[19]. MSU => Rektorat\t\t[Rp.2.000]\t\t\t |\n[20]. MSU => GKU\t\t[Rp.3.500]\t\t\t |\n");
    printf("==================================================================\n");
    printf("|-> Choose the number to select your journey (ex: '1'): ");
    scanf("%d", &choice);

    switch(choice){
        case(1):
            cost = 2000;
            char route1[] = "FEB/FKB => TULT";
            userData = fopen("User List.dat", "rb");
            while (fread(&user, sizeof(user), 1, userData) == 1){
                if (strcmp(usernameUser, user->username) == 0){
                    if(user->balance >= cost){
                        addition(cost);
                    break;
                    }
                else{
                    printf("\n==== SO SORRY! ====\n");
                    printf("Insufficient Balance\n");
                    printf("\n'You only have Rp.%d,00''\n", user->balance);
                    printf("\nGo Back to Main Menu...\n");
                    system("pause");
                    }
                }
            }
            historyOfUser(route1);
            fclose(userData);
            userMenu();
            break; 
        case(2):
            cost = 3000;
            char route2[] = "FEB/FKB => Rektorat";
            userData = fopen("User List.dat", "rb");
            while (fread(&user, sizeof(user), 1, userData) == 1){
                if (strcmp(usernameUser, user->username) == 0){
                    if(user->balance >= cost){
                        addition(cost);
                    break;
                    }
                else{
                    printf("\n==== SO SORRY! ====\n");
                    printf("Insufficient Balance\n");
                    printf("\n''You only have Rp.%d,00''\n", user->balance);
                    printf("\nGo Back to Main Menu...\n");
                    system("pause");
                    }
                }
            }
            historyOfUser(route2);
            fclose(userData);
            userMenu();
            break;
        case(3):
            cost = 2000;
            char route3[] = "FEB/FKB => GKU";
            userData = fopen("User List.dat", "rb");
            while (fread(&user, sizeof(user), 1, userData) == 1){
                if (strcmp(usernameUser, user->username) == 0){
                    if(user->balance >= cost){
                        addition(cost);
                    break;
                    }
                else{
                    printf("\n==== SO SORRY! ====\n");
                    printf("Insufficient Balance\n");
                    printf("\n''You only have Rp.%d,00''\n", user->balance);
                    printf("\nGo Back to Main Menu...\n");
                    system("pause");
                    }
                }
            }
            historyOfUser(route3);
            fclose(userData);
            userMenu();
            break;
        case(4):
            cost = 4000;
            char route4[] = "FEB/FKB => MSU";
            userData = fopen("User List.dat", "rb");
            while (fread(&user, sizeof(user), 1, userData) == 1){
                if (strcmp(usernameUser, user->username) == 0){
                    if(user->balance >= cost){
                        addition(cost);
                    break;
                    }
                else{
                    printf("\n==== SO SORRY! ====\n");
                    printf("Insufficient Balance\n");
                    printf("\n''You only have Rp.%d,00''\n", user->balance);
                    printf("\nGo Back to Main Menu...\n");
                    system("pause");
                    }
                }
            }
            historyOfUser(route4);
            fclose(userData);
            userMenu();
            break;
        case(5):
            cost = 2000;
            char route5[] = "TULT => FEB/FKB";
            userData = fopen("User List.dat", "rb");
            while (fread(&user, sizeof(user), 1, userData) == 1){
                if (strcmp(usernameUser, user->username) == 0){
                    if(user->balance >= cost){
                        addition(cost);
                    break;
                    }
                else{
                    printf("\n==== SO SORRY! ====\n");
                    printf("Insufficient Balance\n");
                    printf("\n''You only have Rp.%d,00''\n", user->balance);
                    printf("\nGo Back to Main Menu...\n");
                    system("pause");
                    }
                }
            }
            historyOfUser(route5);
            fclose(userData);
            userMenu();
            break;
        case(6):
            cost = 3500;
            char route6[] = "TULT => Rektorat";
            userData = fopen("User List.dat", "rb");
            while (fread(&user, sizeof(user), 1, userData) == 1){
                if (strcmp(usernameUser, user->username) == 0){
                    if(user->balance >= cost){
                        addition(cost);
                    break;
                    }
                else{
                    printf("\n==== SO SORRY! ====\n");
                    printf("Insufficient Balance\n");
                    printf("\n''You only have Rp.%d,00''\n", user->balance);
                    printf("\nGo Back to Main Menu...\n");
                    system("pause");
                    }
                }
            }
            historyOfUser(route6);
            fclose(userData);
            userMenu();
            break;
        case(7):
            cost = 2000;
            char route7[] = "TULT => GKU";
            userData = fopen("User List.dat", "rb");
            while (fread(&user, sizeof(user), 1, userData) == 1){
                if (strcmp(usernameUser, user->username) == 0){
                    if(user->balance >= cost){
                        addition(cost);
                    break;
                    }
                else{
                    printf("\n==== SO SORRY! ====\n");
                    printf("Insufficient Balance\n");
                    printf("\n''You only have Rp.%d,00''\n", user->balance);
                    printf("\nGo Back to Main Menu...\n");
                    system("pause");
                    }
                }
            }
            historyOfUser(route7);
            fclose(userData);
            userMenu();
            break;
        case(8):
            cost = 4000;
            char route8[] = "TULT => MSU";
            userData = fopen("User List.dat", "rb");
            while (fread(&user, sizeof(user), 1, userData) == 1){
                if (strcmp(usernameUser, user->username) == 0){
                    if(user->balance >= cost){
                        addition(cost);
                    break;
                    }
                else{
                    printf("\n==== SO SORRY! ====\n");
                    printf("Insufficient Balance\n");
                    printf("\n''You only have Rp.%d,00''\n", user->balance);
                    printf("\nGo Back to Main Menu...\n");
                    system("pause");
                    }
                }
            }
            historyOfUser(route8);
            fclose(userData);
            userMenu();
            break;
        case(9):
            cost = 3000;
            char route9[] = "Rektorat => FEB/FKB";
            userData = fopen("User List.dat", "rb");
            while (fread(&user, sizeof(user), 1, userData) == 1){
                if (strcmp(usernameUser, user->username) == 0){
                    if(user->balance >= cost){
                        addition(cost);
                    break;
                    }
                else{
                    printf("\n==== SO SORRY! ====\n");
                    printf("Insufficient Balance\n");
                    printf("\n''You only have Rp.%d,00''\n", user->balance);
                    printf("\nGo Back to Main Menu...\n");
                    system("pause");
                    }
                }
            }
            historyOfUser(route9);
            fclose(userData);
            userMenu();
            break;
        case(10):
            cost = 3500;
            char route10[] = "Rektorat => TULT";
            userData = fopen("User List.dat", "rb");
            while (fread(&user, sizeof(user), 1, userData) == 1){
                if (strcmp(usernameUser, user->username) == 0){
                    if(user->balance >= cost){
                        addition(cost);
                    break;
                    }
                else{
                    printf("\n==== SO SORRY! ====\n");
                    printf("Insufficient Balance\n");
                    printf("\n''You only have Rp.%d,00''\n", user->balance);
                    printf("\nGo Back to Main Menu...\n");
                    system("pause");
                    }
                }
            }
            historyOfUser(route10);
            fclose(userData);
            userMenu();
            break;
        case(11):
            cost = 1500;
            char route11[] = "Rektorat => GKU";
            userData = fopen("User List.dat", "rb");
            while (fread(&user, sizeof(user), 1, userData) == 1){
                if (strcmp(usernameUser, user->username) == 0){
                    if(user->balance >= cost){
                        addition(cost);
                    break;
                    }
                else{
                    printf("\n==== SO SORRY! ====\n");
                    printf("Insufficient Balance\n");
                    printf("\n''You only have Rp.%d,00''\n", user->balance);
                    printf("\nGo Back to Main Menu...\n");
                    system("pause");
                    }
                }
            }
            historyOfUser(route11);
            fclose(userData);
            userMenu();
            break;
        case(12):
            cost = 2000;
            char route12[] = "Rektorat => MSU";
            userData = fopen("User List.dat", "rb");
            while (fread(&user, sizeof(user), 1, userData) == 1){
                if (strcmp(usernameUser, user->username) == 0){
                    if(user->balance >= cost){
                        addition(cost);
                    break;
                    }
                else{
                    printf("\n==== SO SORRY! ====\n");
                    printf("Insufficient Balance\n");
                    printf("\n''You only have Rp.%d,00''\n", user->balance);
                    printf("\nGo Back to Main Menu...\n");
                    system("pause");
                    }
                }
            }
            historyOfUser(route12);
            fclose(userData);
            userMenu();
            break;
        case(13):
            cost = 2000;
            char route13[] = "GKU => FEB/FKB";
            userData = fopen("User List.dat", "rb");
            while (fread(&user, sizeof(user), 1, userData) == 1){
                if (strcmp(usernameUser, user->username) == 0){
                    if(user->balance >= cost){
                        addition(cost);
                    break;
                    }
                else{
                    printf("\n==== SO SORRY! ====\n");
                    printf("Insufficient Balance\n");
                    printf("\n''You only have Rp.%d,00''\n", user->balance);
                    printf("\nGo Back to Main Menu...\n");
                    system("pause");
                    }
                }
            }
            historyOfUser(route13);
            fclose(userData);
            userMenu();
            break;
        case(14):
            cost = 2000;
            char route14[] = "GKU => TULT";
            userData = fopen("User List.dat", "rb");
            while (fread(&user, sizeof(user), 1, userData) == 1){
                if (strcmp(usernameUser, user->username) == 0){
                    if(user->balance >= cost){
                        addition(cost);
                    break;
                    }
                else{
                    printf("\n==== SO SORRY! ====\n");
                    printf("Insufficient Balance\n");
                    printf("\n''You only have Rp.%d,00''\n", user->balance);
                    printf("\nGo Back to Main Menu...\n");
                    system("pause");
                    }
                }
            }
            historyOfUser(route14);
            fclose(userData);
            userMenu();
            break;
        case(15):
            cost = 1500;
            char route15[] = "GKU => Rektorat";
            userData = fopen("User List.dat", "rb");
            while (fread(&user, sizeof(user), 1, userData) == 1){
                if (strcmp(usernameUser, user->username) == 0){
                    if(user->balance >= cost){
                        addition(cost);
                    break;
                    }
                else{
                    printf("\n==== SO SORRY! ====\n");
                    printf("Insufficient Balance\n");
                    printf("\n''You only have Rp.%d,00''\n", user->balance);
                    printf("\nGo Back to Main Menu...\n");
                    system("pause");
                    }
                }
            }
            historyOfUser(route15);
            fclose(userData);
            userMenu();
            break;
        case(16):
            cost = 3500;
            char route16[] = "GKU => MSU";
            userData = fopen("User List.dat", "rb");
            while (fread(&user, sizeof(user), 1, userData) == 1){
                if (strcmp(usernameUser, user->username) == 0){
                    if(user->balance >= cost){
                        addition(cost);
                    break;
                    }
                else{
                    printf("\n==== SO SORRY! ====\n");
                    printf("Insufficient Balance\n");
                    printf("\n''You only have Rp.%d,00''\n", user->balance);
                    printf("\nGo Back to Main Menu...\n");
                    system("pause");
                    }
                }
            }
            historyOfUser(route16);
            fclose(userData);
            userMenu();
          break;
        case(17):
            cost = 4000;
            char route17[] = "MSU => FEB/FKB";
            userData = fopen("User List.dat", "rb");
            while (fread(&user, sizeof(user), 1, userData) == 1){
                if (strcmp(usernameUser, user->username) == 0){
                    if(user->balance >= cost){
                        addition(cost);
                    break;
                    }
                else{
                    printf("\n==== SO SORRY! ====\n");
                    printf("Insufficient Balance\n");
                    printf("\n''You only have Rp.%d,00''\n", user->balance);
                    printf("\nGo Back to Main Menu...\n");
                    system("pause");
                    }
                }
            }
            historyOfUser(route17);
            fclose(userData);
            userMenu();
            break;
        case(18):
            cost = 4000;
            char route18[] = "MSU => TULT";
            userData = fopen("User List.dat", "rb");
            while (fread(&user, sizeof(user), 1, userData) == 1){
                if (strcmp(usernameUser, user->username) == 0){
                    if(user->balance >= cost){
                        addition(cost);
                    break;
                    }
                else{
                    printf("\n==== SO SORRY! ====\n");
                    printf("Insufficient Balance\n");
                    printf("\n''You only have Rp.%d,00''\n", user->balance);
                    printf("\nGo Back to Main Menu...\n");
                    system("pause");
                    }
                }
            }
            historyOfUser(route1);
            fclose(userData);
            userMenu();
            break;
        case(19):
            cost = 2000;
            char route19[] = "MSU => Rektorat";
            userData = fopen("User List.dat", "rb");
            while (fread(&user, sizeof(user), 1, userData) == 1){
                if (strcmp(usernameUser, user->username) == 0){
                    if(user->balance >= cost){
                        addition(cost);
                    break;
                    }
                else{
                    printf("\n==== SO SORRY! ====\n");
                    printf("Insufficient Balance\n");
                    printf("\n''You only have Rp.%d,00''\n", user->balance);
                    printf("\nGo Back to Main Menu...\n");
                    system("pause");
                    }
                }
            }
            historyOfUser(route19);
            fclose(userData);
            userMenu();
            break;
        case(20):
            cost = 3500;
            char route20[] = "MSU => GKU";
            userData = fopen("User List.dat", "rb");
            while (fread(&user, sizeof(user), 1, userData) == 1){
                if (strcmp(usernameUser, user->username) == 0){
                    if(user->balance >= cost){
                        addition(cost);
                    break;
                    }
                else{
                    printf("\n==== SO SORRY! ====\n");
                    printf("Insufficient Balance\n");
                    printf("\n''You only have Rp.%d,00''\n", user->balance);
                    printf("\nGo Back to Main Menu...\n");
                    system("pause");
                    }
                }
            }
            historyOfUser(route20);
            fclose(userData);
            userMenu();
            break;
        default:
            printf("Invalid Choice");
            rentABike();
            break;
    }
}
void userCheckHistory() {
    void userMenu();
    FILE *historyOfUser;
    int num = 1;
    historyOfUser = fopen("History_User.dat", "rb");
    printf("\n========================= YOUR RIDING HISTORY =========================\n");
    while (fread(&history, sizeof(history), 1, historyOfUser) == 1) {
        if (strcmp(usernameUser, history->name) == 0){
                printf("%d. %s", num, history->ridingHistory);
                printf("\n==========================\n");
            num++;
        }
    }
    fclose(historyOfUser);
    system("pause");
    userMenu();
}
void userMenu(){ //USER MENU
    void userStart();
    void topUpUser();
    void userCheckBalance();
    void rentABike();
    void userCheckHistory();
    void header();
    system("cls");
    int userMenuChoice;
    header();
    
    printf("========================== !MAIN MENU! ==========================");
    printf("\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t*YOU ARE LOGGED IN AS: %s!*\n", usernameUser);
    printf("| WELCOME! What would you like to do today?                     |\n");
    printf("| 1. Add Balance                                                |\n");
    printf("| 2. Check Balance                                              |\n");
    printf("| 3. Rent a bike!!!                                             |\n");
    printf("| 4. Renting History                                            |\n");
    printf("| 5. Return                                                     |\n");
    printf("=================================================================\n");
    printf("==> Input (for example: '1'): ");
    scanf("%d", &userMenuChoice);

    switch (userMenuChoice){
        case (1):
            topUpUser(); //Feature 1
          break;
        case (2):
            userCheckBalance(); //Feature 2
          break;
        case (3):
            rentABike(); //Feature 3
          break;
        case (4):
            userCheckHistory(); //Feature 4
          break;
        case (5):
            userStart();
          break;
        default:
            printf("Invalid choice.\n");
            userMenu();
          break;
    }
}
void userStart(){
    void main();
    void userSignUp();
    void userLogIn();
    void header();
    int switcher;
    system("cls");
    header();
    
    printf("====================== !WELCOME TO D'BEAM! ======================\n");
    printf("| Hello there! Are you a new user? If yes, please sign up first!|\n");
    printf("| 1. Sign Up                                                    |\n");
    printf("| 2. Log In                                                     |\n");
    printf("| 3. Return                                                     |\n");
    printf("=================================================================\n");
    printf("==> Input (for example: '1'): ");
    scanf("%d", &switcher);

    switch (switcher){
    case(1):
        userSignUp();
        break;
    case(2):
        userLogIn();
        break;
    case(3):
        main();
        break;
    default:
        printf("Invalid choice.\n");
        userStart();
        break;
    }
    
}
void fillingAnimation(int duration, int barLength){
    int i, j;
    for (j = 0; j <= 100; j++){
        printf("\r[");
        for (i = 0; i < barLength; i++){
            if (i <= j * barLength / 100)
                printf("=");
            else
                printf(" ");
        }
        printf("] %d%%", j);
        fflush(stdout);
        usleep(duration * 500); // sleep for duration milliseconds
    }
    printf("\n");
}
void main(){
    system("cls");
    void adminStart();
    void userStart();
    void header();
    int duration = 50; // in milliseconds
    int barLength = 20;
    if(initialDisplaycount == 0){
        printf("                                                                                                                                                  \n");
        printf("\t\t\t\t\t\t                      ''''''                                                                                                          \n");
        printf("\t\t\t\t\t\tDDDDDDDDDDDDD         '::::'BBBBBBBBBBBBBBBBB   EEEEEEEEEEEEEEEEEEEEEE               AAA               MMMMMMMM               MMMMMMMM\n");
        printf("\t\t\t\t\t\tD::::::::::::DDD      '::::'B::::::::::::::::B  E::::::::::::::::::::E              A:::A              M:::::::M             M:::::::M\n");
        printf("\t\t\t\t\t\tD:::::::::::::::DD    ':::''B::::::BBBBBB:::::B E::::::::::::::::::::E             A:::::A             M::::::::M           M::::::::M\n");
        printf("\t\t\t\t\t\tDDD:::::DDDDD:::::D  ':::'  BB:::::B     B:::::BEE::::::EEEEEEEEE::::E            A:::::::A            M:::::::::M         M:::::::::M\n");
        printf("\t\t\t\t\t\t  D:::::D    D:::::D ''''     B::::B     B:::::B  E:::::E       EEEEEE           A:::::::::A           M::::::::::M       M::::::::::M\n");
        printf("\t\t\t\t\t\t  D:::::D     D:::::D         B::::B     B:::::B  E:::::E                       A:::::A:::::A          M:::::::::::M     M:::::::::::M\n");
        printf("\t\t\t\t\t\t  D:::::D     D:::::D         B::::BBBBBB:::::B   E::::::EEEEEEEEEE            A:::::A A:::::A         M:::::::M::::M   M::::M:::::::M\n");
        printf("\t\t\t\t\t\t  D:::::D     D:::::D         B:::::::::::::BB    E:::::::::::::::E           A:::::A   A:::::A        M::::::M M::::M M::::M M::::::M\n");
        printf("\t\t\t\t\t\t  D:::::D     D:::::D         B::::BBBBBB:::::B   E:::::::::::::::E          A:::::A     A:::::A       M::::::M  M::::M::::M  M::::::M\n");
        printf("\t\t\t\t\t\t  D:::::D     D:::::D         B::::B     B:::::B  E::::::EEEEEEEEEE         A:::::AAAAAAAAA:::::A      M::::::M   M:::::::M   M::::::M\n");
        printf("\t\t\t\t\t\t  D:::::D     D:::::D         B::::B     B:::::B  E:::::E                  A:::::::::::::::::::::A     M::::::M    M:::::M    M::::::M\n");
        printf("\t\t\t\t\t\t  D:::::D    D:::::D          B::::B     B:::::B  E:::::E       EEEEEE    A:::::AAAAAAAAAAAAA:::::A    M::::::M     MMMMM     M::::::M\n");
        printf("\t\t\t\t\t\tDDD:::::DDDDD:::::D         BB:::::BBBBBB::::::BEE::::::EEEEEEEE:::::E   A:::::A             A:::::A   M::::::M               M::::::M\n");
        printf("\t\t\t\t\t\tD:::::::::::::::DD          B:::::::::::::::::B E::::::::::::::::::::E  A:::::A               A:::::A  M::::::M               M::::::M\n");
        printf("\t\t\t\t\t\tD::::::::::::DDD            B::::::::::::::::B  E::::::::::::::::::::E A:::::A                 A:::::A M::::::M               M::::::M\n");
        printf("\t\t\t\t\t\tDDDDDDDDDDDDD               BBBBBBBBBBBBBBBBB   EEEEEEEEEEEEEEEEEEEEEEAAAAAAA                   AAAAAAAMMMMMMMM               MMMMMMMM\n");
        printf("=============================================================================================================================================================================================================================================Loading...\n");
        fillingAnimation(duration, barLength);
        system("pause");
        initialDisplaycount++;
    }
    system("cls");
    int loginChoice;
    header();
    printf("====================== WELCOME TO D'BEAM ======================\n");
    printf("| Please choose as Whom are you willing to use our app?       |\n");
    printf("| 1. Admin                                                    |\n");
    printf("| 2. User                                                     |\n");
    printf("| 3. Exit                                                     |\n");
    printf("===============================================================\n");
    printf("==> Choose (for example: '1'): ");
    scanf("%d", &loginChoice);
    switch (loginChoice){
        case 1:
            adminStart();
          break;
        case 2:
            userStart(); 
          break;
        case 3:
            printf("\nSaving your data\n");
            fillingAnimation(duration, barLength);
            system("cls");
            printf("===============>Thank You for Using our Service, JA MATANE!!!<===============\n\n");
            break;
        default:
            printf("Invalid choice.\n"); 
            main();
          break;
    }
}