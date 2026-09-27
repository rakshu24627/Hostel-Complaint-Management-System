 #include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_COMPLAINTS 100

typedef struct {
    int id;
    char studentName[50];
    char roomNo[20];
    char category[30];
    char description[200];
    char status[20];
} Complaint;

Complaint complaints[MAX_COMPLAINTS];
int complaintCount = 0;
int nextId = 1;

void saveComplaints() {
    FILE *file = fopen("complaints.dat", "wb");

    if (file == NULL) {
        printf("\nError: Could not save data.\n");
        return;
    }

    fwrite(&complaintCount, sizeof(int), 1, file);
    fwrite(&nextId, sizeof(int), 1, file);
    fwrite(complaints, sizeof(Complaint), complaintCount, file);

    fclose(file);
}

void loadComplaints() {
    FILE *file = fopen("complaints.dat", "rb");

    if (file == NULL) {
        return;
    }

    fread(&complaintCount, sizeof(int), 1, file);
    fread(&nextId, sizeof(int), 1, file);
    fread(complaints, sizeof(Complaint), complaintCount, file);

    fclose(file);
}

void addComplaint() {
    if (complaintCount >= MAX_COMPLAINTS) {
        printf("\nComplaint limit reached.\n");
        return;
    }

    Complaint c;
    c.id = nextId++;

    printf("\nEnter student name: ");
    scanf(" %49[^\n]", c.studentName);

    printf("Enter room number: ");
    scanf(" %19[^\n]", c.roomNo);

    printf("Enter category (Electricity/Water/Cleaning/Room/Other): ");
    scanf(" %29[^\n]", c.category);

    printf("Enter complaint description: ");
    scanf(" %199[^\n]", c.description);

    strcpy(c.status, "Pending");

    complaints[complaintCount++] = c;

    saveComplaints();

    printf("\nComplaint added successfully! Complaint ID: %d\n", c.id);
}

void viewComplaints() {
    if (complaintCount == 0) {
        printf("\nNo complaints found.\n");
        return;
    }

    printf("\n========== ALL COMPLAINTS ==========\n");

    for (int i = 0; i < complaintCount; i++) {
        printf("\nComplaint ID : %d", complaints[i].id);
        printf("\nStudent Name : %s", complaints[i].studentName);
        printf("\nRoom Number  : %s", complaints[i].roomNo);
        printf("\nCategory     : %s", complaints[i].category);
        printf("\nDescription  : %s", complaints[i].description);
        printf("\nStatus       : %s\n", complaints[i].status);
        printf("------------------------------------\n");
    }
}

void searchComplaint() {
    int id;
    int found = 0;

    printf("\nEnter complaint ID to search: ");
    scanf("%d", &id);

    for (int i = 0; i < complaintCount; i++) {
        if (complaints[i].id == id) {
            printf("\nComplaint Found!");
            printf("\nStudent Name : %s", complaints[i].studentName);
            printf("\nRoom Number  : %s", complaints[i].roomNo);
            printf("\nCategory     : %s", complaints[i].category);
            printf("\nDescription  : %s", complaints[i].description);
            printf("\nStatus       : %s\n", complaints[i].status);

            found = 1;
            break;
        }
    }

    if (!found) {
        printf("\nComplaint not found.\n");
    }
}

void updateStatus() {
    int id;
    int found = 0;

    printf("\nEnter complaint ID: ");
    scanf("%d", &id);

    for (int i = 0; i < complaintCount; i++) {
        if (complaints[i].id == id) {
            printf("Enter new status (Pending/In Progress/Resolved): ");
            scanf(" %19[^\n]", complaints[i].status);

            saveComplaints();

            printf("\nComplaint status updated successfully.\n");

            found = 1;
            break;
        }
    }

    if (!found) {
        printf("\nComplaint not found.\n");
    }
}

void deleteComplaint() {
    int id;
    int found = 0;

    printf("\nEnter complaint ID to delete: ");
    scanf("%d", &id);

    for (int i = 0; i < complaintCount; i++) {
        if (complaints[i].id == id) {
            for (int j = i; j < complaintCount - 1; j++) {
                complaints[j] = complaints[j + 1];
            }

            complaintCount--;
            saveComplaints();

            printf("\nComplaint deleted successfully.\n");

            found = 1;
            break;
        }
    }

    if (!found) {
        printf("\nComplaint not found.\n");
    }
}

int main() {
    int choice;

    loadComplaints();

    while (1) {
        printf("\n\n====================================");
        printf("\n   HOSTEL COMPLAINT MANAGEMENT");
        printf("\n====================================");
        printf("\n1. Add Complaint");
        printf("\n2. View All Complaints");
        printf("\n3. Search Complaint");
        printf("\n4. Update Complaint Status");
        printf("\n5. Delete Complaint");
        printf("\n6. Exit");
        printf("\n------------------------------------");
        printf("\nEnter your choice: ");

        scanf("%d", &choice);

        switch (choice) {
            case 1:
                addComplaint();
                break;

            case 2:
                viewComplaints();
                break;

            case 3:
                searchComplaint();
                break;

            case 4:
                updateStatus();
                break;

            case 5:
                deleteComplaint();
                break;

            case 6:
                printf("\nThank you for using the system!\n");
                return 0;

            default:
                printf("\nInvalid choice. Please try again.\n");
        }
    }
}
