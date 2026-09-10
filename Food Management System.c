#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_FOODS 100
#define MAX_NAME_LENGTH 50


typedef struct
{
    char name[MAX_NAME_LENGTH];
    int quantity;
    char expiryDate[MAX_NAME_LENGTH];
} Food;

void displayMenu();
void login();
void writeData();
void readData();
void sortData();
void searchData();
void deleteData();
void editData();

Food foodList[MAX_FOODS];
int foodCount = 0;

int main()
{
    login();
    int choice;

    do
        {
        displayMenu();
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
            case 1:
                writeData();
                break;
            case 2:
                readData();
                break;
            case 3:
                sortData();
                break;
            case 4:
                searchData();
                break;
            case 5:
                deleteData();
                break;
            case 6:
                editData();
                break;
            case 7:
                printf("Exiting the program...\n");
                exit(0);
            default:
                printf("Invalid choice. Please try again.\n");
        }
    } while (1);

    return 0;
}

void displayMenu()
{
    printf("\n---## Food Management System ##---\n");
    printf("1. Add food item\n");
    printf("2. Display all food items\n");
    printf("3. Sort food items by name\n");
    printf("4. Search for a food item\n");
    printf("5. Delete a food item\n");
    printf("6. Edit a food item\n");
    printf("7. Exit\n");
}

void login()
{
    char username[50];
    char password[50];

    printf("|^|^|^| Login |^|^|^|\n");
    printf("Username: ");
    scanf("%s", username);
    printf("Password: ");
    scanf("%s", password);
}

void writeData()
{
    if (foodCount >= MAX_FOODS)
    {
        printf("Maximum food limit reached.\n");
        return;
    }

    Food food;
    printf("Enter food name: ");
    scanf("%s", food.name);
    printf("Enter quantity: ");
    scanf("%d", &food.quantity);
    printf("Enter expiry date: ");
    scanf("%s", food.expiryDate);

    foodList[foodCount++] = food;

    FILE *file = fopen("food_data.txt", "a");
    if (file == NULL)
    {
        printf("Error opening file.\n");
        return;
    }

    fprintf(file, "%s %d %s\n", food.name, food.quantity, food.expiryDate);

    fclose(file);

    printf("Food item added successfully.\n");
}

void readData()
{
    FILE *file = fopen("food_data.txt", "r");
    if (file == NULL)
    {
        printf("Error opening file.\n");
        return;
    }

    Food food;
    printf("\n--- Food Items ---\n");
    while (fscanf(file, "%s %d %s", food.name, &food.quantity, food.expiryDate) != EOF)
    {
        printf("Name: %s, Quantity: %d, Expiry Date: %s\n", food.name, food.quantity, food.expiryDate);
    }

    fclose(file);
}

void sortData()
{
    if (foodCount == 0)
    {
        printf("No food items found.\n");
        return;
    }

    int i, j;
    for (i = 0; i < foodCount - 1; i++)
        {
        for (j = 0; j < foodCount - i - 1; j++)
        {
            if (strcmp(foodList[j].name, foodList[j + 1].name) > 0)
            {
                Food temp = foodList[j];
                foodList[j] = foodList[j + 1];
                foodList[j + 1] = temp;
            }
        }
    }

    printf("Food items sorted by name.\n");
    readData();
}

void searchData()
{
    if (foodCount == 0)
    {
        printf("No food items found.\n");
        return;
    }

    char searchName[MAX_NAME_LENGTH];
    printf("Enter the food name to search for: ");
    scanf("%s", searchName);

    int found = 0;
    for (int i = 0; i < foodCount; i++)
        {
        if (strcmp(foodList[i].name, searchName) == 0)
        {
            printf("Name: %s, Quantity: %d, Expiry Date: %s\n", foodList[i].name, foodList[i].quantity,
                   foodList[i].expiryDate);
            found = 1;
        }
    }

    if (!found)
    {
        printf("Food item not found.\n");
    }
}

void deleteData()
{
    if (foodCount == 0)

    {
        printf("No food items found.\n");
        return;
    }

    char searchName[MAX_NAME_LENGTH];
    printf("Enter the food name to delete: ");
    scanf("%s", searchName);

    int found = 0;
    for (int i = 0; i < foodCount; i++)
    {
        if (strcmp(foodList[i].name, searchName) == 0) {
            for (int j = i; j < foodCount - 1; j++) {
                foodList[j] = foodList[j + 1];
            }
            foodCount--;
            found = 1;
            break;
        }
    }

    if (found)
        {
        FILE *file = fopen("food_data.txt", "w");
        if (file == NULL) {
            printf("Error opening file.\n");
            return;
        }

        for (int i = 0; i < foodCount; i++)
        {
            fprintf(file, "%s %d %s\n", foodList[i].name, foodList[i].quantity, foodList[i].expiryDate);
        }

        fclose(file);

        printf("Food item deleted successfully.\n");
    } else
    {
        printf("Food item not found.\n");
    }
}

void editData()
{
    if (foodCount == 0)
    {
        printf("No food items found.\n");
        return;
    }

    char searchName[MAX_NAME_LENGTH];
    printf("Enter the food name to edit: ");
    scanf("%s", searchName);

    int found = 0;
    for (int i = 0; i < foodCount; i++)
    {
        if (strcmp(foodList[i].name, searchName) == 0)
        {
            printf("Enter new quantity: ");
            scanf("%d", &foodList[i].quantity);
            printf("Enter new expiry date: ");
            scanf("%s", foodList[i].expiryDate);
            found = 1;
            break;
        }
    }

    if (found)
        {
        FILE *file = fopen("food_data.txt", "w");
        if (file == NULL) {
            printf("Error opening file.\n");
            return;
        }

        for (int i = 0; i < foodCount; i++) {
            fprintf(file, "%s %d %s\n", foodList[i].name, foodList[i].quantity, foodList[i].expiryDate);
        }

        fclose(file);

        printf("Food item edited successfully.\n");
    } else
    {
        printf("Food item not found.\n");
    }
}
