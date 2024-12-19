#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_BOOKS 100

struct Book {
    char title[50];
    char author[50];
    int year;
    float price;
    int fine;
};

void addBook();
void displayBooks();
void searchBook();
void deleteBook();
void penalty();

int main() {
    int choice;

    while(1)
	 {
        system("cls");
    	printf("\n*****Library Management System Menu*****\n");
    	printf("1. Add a Book\n");
    	printf("2. Display Books\n");
    	printf("3. Search for a Book\n");
    	printf("4. Delete a Book\n");
        printf("5. Fine for Books\n");
    	printf("6. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                addBook();
                break;
            case 2:
                displayBooks();
                break;
            case 3:
                searchBook();
                break;
            case 4:
                deleteBook();
                break;
            case 5:
                penalty();
                break;
            case 6:
                exit(0);
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }

     	printf("\n\nPress Any Key To Continue...");
     	getch();
	}

    return 0;
}
	
void addBook() {
    FILE *file = fopen("library.txt", "a");

    if (file == NULL) {
        printf("Error opening the file.\n");
        return;
    }

    struct Book newBook;

    printf("Enter Book Title: ");
    scanf(" %[^\n]s", newBook.title);
    printf("Enter Author: ");
    scanf(" %[^\n]s", newBook.author);
    printf("Enter Publication Year: ");
    scanf("%d", &newBook.year);
    printf("Enter Price: ");
    scanf("%f", &newBook.price);

    fprintf(file, "%s|%s|%d|%.2f\n", newBook.title, newBook.author, newBook.year, newBook.price);

    fclose(file);

    printf("Book added successfully!\n");
}

void displayBooks() {
    FILE *file = fopen("library.txt", "r");

    if (file == NULL) {
        printf("Error opening the file.\n");
        return;
    }

    struct Book book;
    printf("\nList of Books:\n");

    while (fscanf(file, "%[^|]|%[^|]|%d|%f\n", book.title, book.author, &book.year, &book.price) != EOF) {
        printf("Title: %s\nAuthor: %s\nYear: %d\nPrice: %.2f\n\n", book.title, book.author, book.year, book.price);
    }

    fclose(file);
}


void searchBook() {
    FILE *file = fopen("library.txt", "r");

    if (file == NULL) {
        printf("Error opening the file.\n");
        return;
    }

    char searchTitle[50];
    int found = 0;

    printf("Enter the title to search: ");
    scanf(" %[^\n]s", searchTitle);

    struct Book book;

    while (fscanf(file, "%[^|]|%[^|]|%d|%f\n", book.title, book.author, &book.year, &book.price) != EOF) {
        if (strcmp(book.title, searchTitle) == 0) {
            printf("Book Found!\n");
            printf("Title: %s\nAuthor: %s\nYear: %d\nPrice: %.2f\n\n", book.title, book.author, book.year, book.price);
            found = 1;
            break;
        }
    }

    if (!found) {
        printf("Book not found.\n");
    }

    fclose(file);
}

void deleteBook() {
    FILE *file = fopen("library.txt", "r");
    FILE *tempFile = fopen("temp.txt", "w");

    if (file == NULL || tempFile == NULL) {
        printf("Error opening the file.\n");
        return;
    }

    char deleteTitle[50];
    int found = 0;

    printf("Enter the title to delete: ");
    scanf(" %[^\n]s", deleteTitle);

    struct Book book;

    while (fscanf(file, "%[^|]|%[^|]|%d|%f\n", book.title, book.author, &book.year, &book.price) != EOF) {
        if (strcmp(book.title, deleteTitle) == 0) {
            printf("Book Deleted!\n");
            found = 1;
        } else {
            fprintf(tempFile, "%s|%s|%d|%.2f\n", book.title, book.author, book.year, book.price);
        }
    }

    if (!found) {
        printf("Book not found.\n");
    }

    fclose(file);
    fclose(tempFile);

    remove("library.txt");
    rename("temp.txt", "library.txt");
}


void penalty(){
    int days,fine;
    int fine_per_late_day = 10;
    printf("****FINE PER LATE DAY = 10 RUPPEES****");
    printf("\nNumber of extra Days:");
    scanf("%d",&days);
    if(days<30)
	{
    fine = days * fine_per_late_day;
    printf("Please pay the fine amount:%d",fine);
    }
    else
    {
        printf("\n\nBOOKS IS NOT RETURNED FOR 1 MONTH\n\n");
        printf("\n\nPlease pay respected fine with cost of book\n\n");
        int price;
        printf("Cost of book:");
        scanf("%d",&price);
        fine = (days * fine_per_late_day)+price;
        printf("YOU HAVE TO PAY FINE AMOUNT OF:%d Rs",fine );
    }
}







