#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NAME_LENGTH 50
#define MAX_RECORDS 100

typedef struct {
    int empID;
    char empName[MAX_NAME_LENGTH];
    float empSalary;
} Employee;

void addEmployee(FILE *file) {
    Employee emp;
    printf("Enter employee ID: ");
    scanf("%d", &emp.empID);

    printf("Enter employee name: ");
    scanf("%s", emp.empName);

    printf("Enter employee salary: ");
    scanf("%f", &emp.empSalary);

    fseek(file, emp.empID * sizeof(Employee), SEEK_SET);
    fwrite(&emp, sizeof(Employee), 1, file);

    printf("Employee added successfully.\n");
}

void displayEmployee(FILE *file) {
    Employee emp;
    int empID;

    printf("Enter employee ID to display: ");
    scanf("%d", &empID);

    fseek(file, empID * sizeof(Employee), SEEK_SET);
    fread(&emp, sizeof(Employee), 1, file);

    if (emp.empID == 0) {
        printf("Employee with ID %d does not exist.\n", empID);
    } else {
        printf("Employee ID: %d\n", emp.empID);
        printf("Employee Name: %s\n", emp.empName);
        printf("Employee Salary: %.2f\n", emp.empSalary);
    }
}

int main() {
    FILE *employeeFile;
    employeeFile = fopen("employees.dat", "r+");

    if (employeeFile == NULL) {
        employeeFile = fopen("employees.dat", "w+");
        if (employeeFile == NULL) {
            printf("Error creating or opening file.\n");
            return 1;
        }
    }

    int choice;
    do {
        printf("\n1. Add Employee\n");
        printf("2. Display Employee Details\n");
        printf("3. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                addEmployee(employeeFile);
                break;
            case 2:
                displayEmployee(employeeFile);
                break;
            case 3:
                printf("Exiting...\n");
                break;
            default:
                printf("Invalid choice. Please enter a valid option.\n");
        }
    } while (choice != 3);

    fclose(employeeFile);
    return 0;
}

