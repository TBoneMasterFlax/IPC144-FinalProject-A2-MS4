/*
    ==================================================
    Assignment #2 Milestone #4:
    ==================================================
    Name   : Tuan Nguyen
    ID     : 109062166
    Email  : tnguyen140@myseneca.ca
    Section: NFF
*/

#ifndef ACCOUNT_H_
#define ACCOUNT_H_

// Structures
struct Demographic
{
    int birth_year;
    double income;
    char country[31];
};
struct UserLogin
{
    char display_name[31];
    char login_name[11];
    char password[9];
};
struct Account
{
    int account_number;
    char account_type;
    struct UserLogin user_login;
    struct Demographic demographic;
};

// -----------------------------------------
// Function Prototypes
void getAccount(struct Account* account, int highestNumber);
void getUserLogin(struct UserLogin* login);
void getDemographic(struct Demographic* demographic);
void updateAccount(struct Account* account);
void updateUserLogin(struct UserLogin* login);
void updateDemographic(struct Demographic* demographic);
int loadAccounts(struct Account* account, int size);
int recreateAccountsFile(struct Account* account, int size);
void archiveRemovedAccount(struct Account* account);
void viewArchivedAccounts();

#endif