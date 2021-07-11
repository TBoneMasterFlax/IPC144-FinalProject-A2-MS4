/*
    ==================================================
    Assignment #2 Milestone #4:
    ==================================================
    Name   : Tuan Nguyen
    ID     : 109062166
    Email  : tnguyen140@myseneca.ca
    Section: NFF
*/

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include "commonHelpers.h"
#include "account.h"
#include "accountTicketingUI.h"
#include <string.h>
#include <stdlib.h>

// -----------------------------------------
// Function Definitions

// Function to define a new Account
void getAccount(struct Account* account, int highestNumber)
{
    // ---------------------------------------------------------
    // Account Data: get user input
    // ---------------------------------------------------------
    printf("New Account Data (Account#:%d)\n", highestNumber);
    printf("----------------------------------------\n");

    // Add the necessary code to get user input for each Account member:
    account->account_number = highestNumber;
    printf("Enter the account type (A=Agent | C=Customer): ");
    account->account_type = getCharOption("AC");
    putchar('\n');
}

// Function to define a new UserLogin
void getUserLogin(struct UserLogin* login)
{
    char spaceCheck[11], passwordCheck[9];
    // ---------------------------------------------------------
    // UserLogin Data: get user input
    // ---------------------------------------------------------
    printf("User Login Data Input\n");
    printf("----------------------------------------\n");

    // Add the necessary code to get user input for each UserLogin member:
    do
    {
        printf("Enter user login (10 chars max): ");
        getCString(spaceCheck, 1, 10);
        validateLoginName(login->login_name, spaceCheck);
    } while (strcmp(login->login_name, spaceCheck) != 0);
    printf("Enter the display name (30 chars max): ");
    getCString(login->display_name, 1, 30);
    do
    {
        printf("Enter the password (must be 8 chars in length): ");
        getCString(passwordCheck, 8, 8);
        validatePassword(login->password, passwordCheck);
    } while (strcmp(login->password, passwordCheck) != 0);
    putchar('\n');
}

// Function to define a new Demographic
void getDemographic(struct Demographic* demographic)
{
    // ---------------------------------------------------------
    // Demographic Data: get user input
    // ---------------------------------------------------------
    printf("Demographic Data Input\n");
    printf("----------------------------------------\n");

    // Add the necessary code to get user input for each Demographic member:
    printf("Enter birth year (current age must be between 18 and 110): ");
    demographic->birth_year = getIntFromRange(currentYear() - 110, currentYear() - 18);
    printf("Enter the household Income: $");
    demographic->income = getPositiveDouble();
    printf("Enter the country (30 chars max.): ");
    getDemographicCountry(demographic->country, 1, 30);
    putchar('\n');
}

// Function to update an existing Account
void updateAccount(struct Account* account)
{
    int selection;
    int flag = 1;
    do
    {
        printf("Account: %d - Update Options\n", account->account_number);
        printf("----------------------------------------\n");
        printf("1) Update account type (current value: %c)\n", account->account_type);
        printf("2) Login\n");
        printf("3) Demographics\n");
        printf("0) Done\n");
        printf("Selection: ");
        selection = getIntFromRange(0, 3);
        switch (selection)
        {
        case 0:
            flag = 0;
            break;
        case 1:
            putchar('\n');
            printf("Enter the account type (A=Agent | C=Customer): ");
            account->account_type = getCharOption("AC");
            break;
        case 2:
            updateUserLogin(&account->user_login);
            break;
        case 3:
            updateDemographic(&account->demographic);
            break;
        default:
            break;
        }
    } while (flag);
}

// Function to update an existing UserLogin
void updateUserLogin(struct UserLogin* login)
{
    char passwordCheck[9];
    int selection;
    int flag = 1;
    do
    {
        printf("\nUser Login: %s - Update Options\n", login->login_name);
        printf("----------------------------------------\n");
        printf("1) Display name (current value: %s)\n", login->display_name);
        printf("2) Password\n");
        printf("0) Done\n");
        printf("Selection: ");
        selection = getIntFromRange(0, 2);
        switch (selection)
        {
        case 0:
            putchar('\n');
            flag = 0;
            break;
        case 1:
            putchar('\n');
            printf("Enter the display name (30 chars max): ");
            getCString(login->display_name, 1, 30);
            break;
        case 2:
            putchar('\n');
            do
            {
                printf("Enter the password (must be 8 chars in length): ");
                getCString(passwordCheck, 8, 8);
                validatePassword(login->password, passwordCheck);
            } while (strcmp(login->password, passwordCheck) != 0);

            break;
        default:
            break;
        }
    } while (flag);
}

// Function to update an existing Demographic
void updateDemographic(struct Demographic* demographic)
{
    int selection;
    int flag = 1;
    do
    {
        printf("\nDemographic Update Options\n");
        printf("----------------------------------------\n");
        printf("1) Household Income (current value: $%.2lf)\n", demographic->income);
        printf("2) Country (current value: %s)\n", demographic->country);
        printf("0) Done\n");
        printf("Selection: ");
        selection = getIntFromRange(0, 2);
        switch (selection)
        {
        case 0:
            putchar('\n');
            flag = 0;
            break;
        case 1:
            putchar('\n');
            printf("Enter the household Income: $");
            demographic->income = getPositiveDouble();
            break;
        case 2:
            putchar('\n');
            printf("Enter the country (30 chars max.): ");
            getDemographicCountry(demographic->country, 1, 30);
            break;
        default:
            break;
        }
    } while (flag);
}

// Function to open the accounts.txt file, read a certain format of information,
// and store the appropriate variables into the pointer Account parameter
int loadAccounts(struct Account* account, int size)
{
    FILE* fp = NULL;
    int validAccounts = 0;
    char newLine;
    char separator1, separator2, separator3;
    fp = fopen("accounts.txt", "r");
    if (fp != NULL)
    {
        // When scanning the accounts.txt file, make sure the order of parameters and proper formating is being read correctly
        while (validAccounts < size && fscanf(fp, "%d~%c~%30[^~]%c%10[^~]%c%8[^~]%c%d~%lf~%30[^\n]%c", &account[validAccounts].account_number, &account[validAccounts].account_type, account[validAccounts].user_login.display_name, &separator1, account[validAccounts].user_login.login_name, &separator2, account[validAccounts].user_login.password, &separator3, &account[validAccounts].demographic.birth_year, &account[validAccounts].demographic.income, account[validAccounts].demographic.country, &newLine) == 12)
        {
            // If the initial location of separator1 and separator2 isn't a '|' character,
            if (separator1 != '~' || separator2 != '~' || separator3 != '~')
            {
                // Keep moving along the file until you reach a '|' character
                while (fgetc(fp) != '~');
            }
            // If the initial location of newLine isn't a '\n' character,
            else if (newLine != '\n')
            {
                // Keep moving along the file until you reach a '\n' character
                while (fgetc(fp) != '\n');
            }
            validAccounts++;
        }
        fclose(fp);
    }
    else
    {
        printf("Failed to open the accounts.txt file\n");
    }
    return validAccounts;
}

// Function to open the accounts.txt file and and rewrite its entire contents with information from the pointer Account parameter
int recreateAccountsFile(struct Account* account, int size)
{
    int i, validAccounts = 0;
    FILE* fp = fopen("accounts.txt", "w");
    if (fp != NULL)
    {
        for (i = 0; i < size; i++)
        {
            if (account[i].account_number != 0)
            {
                fprintf(fp, "%d~%c~%s~%s~%s~%d~%.2lf~%s\n", account[i].account_number, account[i].account_type, account[i].user_login.display_name, account[i].user_login.login_name, account[i].user_login.password, account[i].demographic.birth_year, account[i].demographic.income, account[i].demographic.country);
                validAccounts++;
            }
        }
        fclose(fp);
        fp = NULL;
    }
    else
        printf("Failed to open the file accounts.txt for writing\n");
    return validAccounts;
}

// Function to open the accounts_arc.txt file and append the contents of the pointer Account parameter onto the end
void archiveRemovedAccount(struct Account* account)
{
    FILE* fp = fopen("accounts_arc.txt", "a");
    if (fp != NULL)
    {
        fprintf(fp, "%d~%c~%s~%s~%s~%d~%.2lf~%s\n", account->account_number, account->account_type, account->user_login.display_name, account->user_login.login_name, account->user_login.password, account->demographic.birth_year, account->demographic.income, account->demographic.country);
        fclose(fp);
        fp = NULL;
    }
    else
    {
        printf("Failed to open the file accounts_arc.txt for writing\n");
    }
}

// Function to open the accounts_arc.txt file and view/read its contents
void viewArchivedAccounts()
{
    int i = 0, account_number;
    FILE* fp;
    fp = fopen("accounts_arc.txt", "r");
    if (fp != NULL)
    {
        while (fscanf(fp, "%d%*[^\n]", &account_number) != EOF)
        {
            i++;
        }
        fclose(fp);
        printf("\nThere are %d account(s) currently archived.\n\n", i);
        pauseExecution();
    }
    else
    {
        printf("Failed to open the accounts_arc.txt file\n");
    }
}