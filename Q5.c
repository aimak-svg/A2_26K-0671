#include <stdio.h>
#include <string.h>

void displayMenu()
{
    printf("1. Member Registration\n");
    printf("2. Display Available Books\n");
    printf("3. Borrow a Book\n");
    printf("4. Return a Book\n");
    printf("5. Display Member Record\n");
    printf("6. Exit\n");
}

void registerMember(char name[], int *studentID, int *memberType)
{
    int type;

    printf("\nEnter member name: ");
    scanf(" %30[^\n]", name);

    printf("Enter student ID: ");
    scanf("%d", studentID);

    printf("Membership Type (1. Student, 2. Faculty):\n");
    scanf("%d", &type);

    while (type!=1 && type!=2)
    {
        printf("Invalid membership type. Enter 1 or 2: ");
        scanf("%d", &type);
    }

    *memberType=type;
}

void displayBooks(int bookIDs[], char bookTitles[][50],int availableCopies[], int totalBooks)
{
    int i;

    printf("\n===== AVAILABLE BOOKS =====\n");
    printf("Book ID\tTitle\t\t\tAvailable Copies\n");

    for (i=0; i<totalBooks; i++)
    {
        printf("%d\t%-25s %d\n", bookIDs[i], bookTitles[i], availableCopies[i]);
    }
}

void borrowBook(int bookIDs[], char bookTitles[][50], int availableCopies[], int totalBooks, int borrowedBookIDs[], int *borrowedCount, int memberType)
{
    int id, i, found=0, days;

    if (*borrowedCount >= 3)
    {
        printf("You cannot borrow more than 3 books at a time\n");
        return;
    }

    printf("Enter the book ID you want to borrow: ");
    scanf("%d", &id);

    for (i=0; i<totalBooks; i++)
    {
        if (bookIDs[i] == id)
        {
            found=1;
            break;
        }
    }

    if (found == 0)
    {
        printf("Invalid book ID\n");
        return;
    }

    if (availableCopies[i] <= 0)
    {
        printf("No copies of this book are available\n");
        return;
    }

    if (memberType == 1)
        days=14;
    else
        days=30;

    printf("You can keep this book for %d days\n", days);

    borrowedBookIDs[*borrowedCount] =id;
    (*borrowedCount)++;
    availableCopies[i]--;

}

float returnBook(int bookIDs[], int availableCopies[], int totalBooks, int borrowedBookIDs[], int *borrowedCount, int memberType, float *totalFine)
{
    int id, actualDays, allowedDays, i, j, found=0, bookIndex=-1, borrowedIndex=-1;
    float fine=0, finePayable=0;
    char code[10];

    if (*borrowedCount == 0)
    {
        printf("You have no books to return.\n");
        return 0;
    }

    printf("Enter the book ID you want to return: ");
    scanf("%d", &id);

    for (i=0; i<*borrowedCount; i++)
    {
        if (borrowedBookIDs[i] == id)
        {
            found=1;
            borrowedIndex=i;
            break;
        }
    }

    if (found == 0)
    {
        printf("You have not borrowed this book\n");
        return 0;
    }

    for (i=0; i<totalBooks; i++)
    {
        if (bookIDs[i] == id)
        {
            bookIndex=i;
            break;
        }
    }

    printf("Enter the number of days the book was kept: ");
    scanf("%d", &actualDays);

    while (actualDays <= 0)
    {
        printf("Enter the number of days greater than 0: ");
        scanf("%d", &actualDays);
    }

    if (memberType == 1)
        allowedDays=14;
    else
        allowedDays=30;

    if (actualDays>allowedDays)
    {
        if (memberType == 1)
            fine= (actualDays-allowedDays)*20;
        else
            fine = (actualDays-allowedDays)*10;

    }
    finePayable=fine;

    if (fine>0)
    {
        printf("Fine before waiver: Rs. %.2f\n", fine);

        printf("Enter membership code for 50 percent waiver: ");
        scanf("%9s", code);

        if (strcmp(code, "LIB2026") == 0)
        {
            finePayable = fine*0.5;
            printf("50 percent waiver applied\n");
        }
        else
            printf("Incorrect code. No waiver applied\n");

    }

    *totalFine = *totalFine+fine;
    availableCopies[bookIndex]++;

    for (j=borrowedIndex; j<*borrowedCount-1; j++)
    {
        borrowedBookIDs[j]= borrowedBookIDs[j+1];
    }

    (*borrowedCount)--;

    printf("Book returned\n");
    printf("Fine: Rs. %.2f\n", finePayable);

    return finePayable;
}

void displayMemberRecord(char name[], int studentID, int memberType, int borrowedBookIDs[], int borrowedCount, float totalFine, float fineAfterWaiver)
{
    int i;

    printf("\n===== MEMBER RECORD =====\n");
    printf("Name: %s\n", name);
    printf("Student ID: %d\n", studentID);

    if (memberType == 1)
        printf("Membership Type: Student\n");
    else
        printf("Membership Type: Faculty\n");

    printf("Currently borrowed books: ");
    if (borrowedCount == 0)
    {
        printf("None\n");
    }
    else
    {
        for (i=0; i<borrowedCount; i++)
        {
            printf("%d ", borrowedBookIDs[i]);
        }
    }

    printf("Total fine before waivers: Rs. %.2f\n", totalFine);
    printf("Final fine after waivers: Rs. %.2f\n", fineAfterWaiver);
}

int main()
{
    int bookIDs[5] = {101, 102, 103, 104, 105};
    char bookTitles[5][50] = {"Programming in C", "Data Structures", "Database Systems", "Computer Networks", "Operating Systems"};
    int availableCopies[5]={3, 4, 2, 5, 3};
    char name[50]="";
    int studentID=0, memberType=0, borrowedBookIDs[3], borrowedCount=0, choice, registered=0, totalBooks=5;
    float totalFine=0, fineAfterWaiver=0;

    do
    {
        displayMenu();
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
            case 1: registerMember(name, &studentID, &memberType);
                    registered=1;
                    break;

            case 2: displayBooks(bookIDs, bookTitles, availableCopies, totalBooks);
                    break;

            case 3: if (registered == 0)
                        printf("Please register first\n");
                    else
                        borrowBook(bookIDs, bookTitles, availableCopies, totalBooks, borrowedBookIDs, &borrowedCount, memberType);
                    
                    break;

            case 4: if (registered == 0)
                        printf("Please register first\n");
                    else
                        fineAfterWaiver += returnBook(bookIDs, availableCopies, totalBooks, borrowedBookIDs, &borrowedCount, memberType, &totalFine);
                
                    break;

            case 5: if (registered == 0)
                        printf("Please register first\n");
                    else
                        displayMemberRecord(name, studentID, memberType, borrowedBookIDs, borrowedCount, totalFine, fineAfterWaiver);
                
                    break;

            case 6: printf("Exiting\n");
                    break;

            default: printf("Invalid choice. Try again\n");
        }

    } while (choice!=6);

    return 0;
}
