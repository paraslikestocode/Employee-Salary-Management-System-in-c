#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Employee {
    int id;
    char name[50];
    float basicSalary, hra, da, totalSalary;
};

// Salary calculation
void calculateSalary(struct Employee *e) {
    e->hra = e->basicSalary * 0.20;
    e->da  = e->basicSalary * 0.10;
    e->totalSalary = e->basicSalary + e->hra + e->da;
}

// Add Employee
void addEmployee() {
    FILE *fp = fopen("employee.csv", "a+");
    struct Employee e;

    if (fp == NULL) {
        printf("Error opening file!\n");
        return;
    }

    // Add header if file is empty
    fseek(fp, 0, SEEK_END);
    if (ftell(fp) == 0) {
        fprintf(fp, "ID,Name,Basic,HRA,DA,Total\n");
    }

    printf("\nEnter Employee ID: ");
    scanf("%d", &e.id);

    printf("Enter Name: ");
    scanf(" %[^\n]", e.name);

    printf("Enter Basic Salary: ");
    scanf("%f", &e.basicSalary);

    calculateSalary(&e);

    fprintf(fp, "%d,%s,%.2f,%.2f,%.2f,%.2f\n",
            e.id, e.name, e.basicSalary, e.hra, e.da, e.totalSalary);

    fclose(fp);
    printf("\nEmployee Added Successfully!\n");
}

// Display Employees
void displayEmployees() {
    FILE *fp = fopen("employee.csv", "r");
    struct Employee e;
    char line[200];

    if (fp == NULL) {
        printf("\nNo records found!\n");
        return;
    }

    printf("\n--- Employee List ---\n");

    fgets(line, sizeof(line), fp); // skip header

    while (fscanf(fp, "%d,%49[^,],%f,%f,%f,%f\n",
                  &e.id, e.name, &e.basicSalary,
                  &e.hra, &e.da, &e.totalSalary) == 6) {

        printf("\nID: %d", e.id);
        printf("\nName: %s", e.name);
        printf("\nBasic Salary: %.2f", e.basicSalary);
        printf("\nHRA: %.2f", e.hra);
        printf("\nDA: %.2f", e.da);
        printf("\nTotal Salary: %.2f\n", e.totalSalary);
    }

    fclose(fp);
}

// Search Employee
void searchEmployee() {
    FILE *fp = fopen("employee.csv", "r");
    struct Employee e;
    int id, found = 0;
    char line[200];

    if (fp == NULL) {
        printf("\nNo records found!\n");
        return;
    }

    printf("\nEnter Employee ID to Search: ");
    scanf("%d", &id);

    fgets(line, sizeof(line), fp); // skip header

    while (fscanf(fp, "%d,%49[^,],%f,%f,%f,%f\n",
                  &e.id, e.name, &e.basicSalary,
                  &e.hra, &e.da, &e.totalSalary) == 6) {

        if (e.id == id) {
            printf("\nEmployee Found!\n");
            printf("Name: %s\n", e.name);
            printf("Total Salary: %.2f\n", e.totalSalary);
            found = 1;
            break;
        }
    }

    if (!found)
        printf("\nEmployee Not Found!\n");

    fclose(fp);
}

// Delete Employee
void deleteEmployee() {
    FILE *fp = fopen("employee.csv", "r");
    FILE *temp = fopen("temp.csv", "w");

    struct Employee e;
    int id, found = 0;
    char line[200];

    if (fp == NULL) {
        printf("\nNo records found!\n");
        return;
    }

    printf("\nEnter Employee ID to Delete: ");
    scanf("%d", &id);

    // Copy header
    fgets(line, sizeof(line), fp);
    fprintf(temp, "%s", line);

    while (fscanf(fp, "%d,%49[^,],%f,%f,%f,%f\n",
                  &e.id, e.name, &e.basicSalary,
                  &e.hra, &e.da, &e.totalSalary) == 6) {

        if (e.id != id) {
            fprintf(temp, "%d,%s,%.2f,%.2f,%.2f,%.2f\n",
                    e.id, e.name, e.basicSalary,
                    e.hra, e.da, e.totalSalary);
        } else {
            found = 1;
        }
    }

    fclose(fp);
    fclose(temp);

    remove("employee.csv");
    rename("temp.csv", "employee.csv");

    if (found)
        printf("\nEmployee Deleted Successfully!\n");
    else
        printf("\nEmployee Not Found!\n");
}

// Main Function
int main() {
    int choice;

    while (1) {
        printf("\n===== Employee Management System (CSV) =====\n");
        printf("1. Add Employee\n");
        printf("2. Display Employees\n");
        printf("3. Search Employee\n");
        printf("4. Delete Employee\n");
        printf("5. Exit\n");

        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: addEmployee(); break;
            case 2: displayEmployees(); break;
            case 3: searchEmployee(); break;
            case 4: deleteEmployee(); break;
            case 5: exit(0);
            default: printf("\nInvalid Choice!\n");
        }
    }

    return 0;
}
