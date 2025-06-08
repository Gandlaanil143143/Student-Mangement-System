#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Student {
    int roll_no;
    char name[50];
    float marks;
};

void addStudent() {
    struct Student s;
    FILE *fp = fopen("students.dat", "ab"); // append in binary mode
    if (fp == NULL) {
        printf("Error opening file!\n");
        return;
    }

    printf("Enter Roll Number: ");
    scanf("%d", &s.roll_no);
    printf("Enter Name: ");
    scanf(" %[^\n]s", s.name);
    printf("Enter Marks: ");
    scanf("%f", &s.marks);

    fwrite(&s, sizeof(s), 1, fp);
    fclose(fp);
    printf("Student added successfully!\n");
}

void displayStudents() {
    struct Student s;
    FILE *fp = fopen("students.dat", "rb");
    if (fp == NULL) {
        printf("No records found!\n");
        return;
    }

    printf("\n%-10s %-30s %-10s\n", "Roll No", "Name", "Marks");
    printf("-----------------------------------------------\n");

    while (fread(&s, sizeof(s), 1, fp)) {
        printf("%-10d %-30s %-10.2f\n", s.roll_no, s.name, s.marks);
    }

    fclose(fp);
}

void searchStudent() {
    int roll;
    struct Student s;
    int found = 0;

    printf("Enter Roll Number to search: ");
    scanf("%d", &roll);

    FILE *fp = fopen("students.dat", "rb");
    if (fp == NULL) {
        printf("No records found!\n");
        return;
    }

    while (fread(&s, sizeof(s), 1, fp)) {
        if (s.roll_no == roll) {
            printf("\nStudent Found:\n");
            printf("Roll No : %d\n", s.roll_no);
            printf("Name    : %s\n", s.name);
            printf("Marks   : %.2f\n", s.marks);
            found = 1;
            break;
        }
    }

    if (!found) {
        printf("Student with Roll No %d not found.\n", roll);
    }

    fclose(fp);
}

void deleteStudent() {
    int roll;
    struct Student s;
    int found = 0;

    printf("Enter Roll Number to delete: ");
    scanf("%d", &roll);

    FILE *fp = fopen("students.dat", "rb");
    FILE *temp = fopen("temp.dat", "wb");

    if (fp == NULL || temp == NULL) {
        printf("File error!\n");
        return;
    }

    while (fread(&s, sizeof(s), 1, fp)) {
        if (s.roll_no != roll) {
            fwrite(&s, sizeof(s), 1, temp);
        } else {
            found = 1;
        }
    }

    fclose(fp);
    fclose(temp);

    remove("students.dat");
    rename("temp.dat", "students.dat");

    if (found)
        printf("Student deleted successfully.\n");
    else
        printf("Student with Roll No %d not found.\n", roll);
}

int main() {
    int choice;

    while (1) {
        printf("\n===== Student Management System =====\n");
        printf("1. Add Student\n");
        printf("2. Display All Students\n");
        printf("3. Search Student by Roll Number\n");
        printf("4. Delete Student by Roll Number\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: addStudent(); break;
            case 2: displayStudents(); break;
            case 3: searchStudent(); break;
            case 4: deleteStudent(); break;
            case 5: exit(0);
            default: printf("Invalid choice. Please try again.\n");
        }
    }

    return 0;
}

