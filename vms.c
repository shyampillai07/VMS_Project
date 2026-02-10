/**
 * PROJECT: KARNATAKA STATE VOTER MANAGEMENT SYSTEM
 * VERSION: 1.0 
 * AUTHOR: Shyam Pillai
 * DESCRIPTION: Handles Voter Registration, Bulk Data Generation, and Analytics.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>

// ====================================================
//                SYSTEM CONFIGURATION
// ====================================================
#define MAX_VOTERS 5000
#define DB_FILE "sec_database.csv"
#define CURRENT_YEAR 2024

// --- Data Structure ---
typedef struct {
    char voterID[20];       // Unique ID (e.g., KA-BLR-1001)
    char name[50];
    char fatherName[50];
    char gender[10];        // Male, Female
    char dob[15];           // DD/MM/YYYY
    char address[100];      // House No, Area
    int age;                // Calculated from DOB
    int hasVoted;           // 0 = No, 1 = Yes
} Voter;

// --- Global System State ---
Voter database[MAX_VOTERS];
int totalRecords = 0;

// ====================================================
//                FUNCTION PROTOTYPES
// ====================================================
// Core Operations
void registerVoter();
void generateBulkData();     
void removeVoter();
void resetDatabase();        
void searchVoter();
void viewAllVoters();
void castVote();
void electionAnalytics();

// File Handling
void loadDatabase();
void saveDatabase();

// Utilities
int calculateAge(char *dob);
void printHeader(char *title);
void printSeparator();

// ====================================================
//                   MAIN CONTROLLER
// ====================================================
int main() {
    int choice;
    srand(time(0)); // Seed random number generator
    loadDatabase(); // Auto-load data

    while (1) {
        // Professional Line-by-Line Menu
        printf("\n");
        printf("==============================================================\n");
        printf("         KARNATAKA STATE ELECTION COMMISSION (SEC)            \n");
        printf("==============================================================\n");
        printf("  [1] Register New Voter (Manual Entry)\n");
        printf("  [2] Generate Sample Data (Bulk Import 250+)\n");
        printf("  [3] Cast Vote (Polling Station Mode)\n");
        printf("  [4] Search Voter Database\n");
        printf("  [5] Remove Single Voter\n");
        printf("  [6] Reset Database (Bulk Delete)\n");
        printf("  [7] View All Registered Voters\n");
        printf("  [8] View Election Analytics & Stats\n");
        printf("  [9] Save & Exit System\n");
        printf("==============================================================\n");
        printf("  >> Enter Your Choice: ");
        
        scanf("%d", &choice);
        while(getchar() != '\n'); // Clear input buffer

        switch (choice) {
            case 1: registerVoter(); break;
            case 2: generateBulkData(); break;
            case 3: castVote(); break;
            case 4: searchVoter(); break;
            case 5: removeVoter(); break;
            case 6: resetDatabase(); break;
            case 7: viewAllVoters(); break;
            case 8: electionAnalytics(); break;
            case 9: 
                saveDatabase();
                printf("\n  [SYSTEM] Shutting down... Goodbye.\n");
                exit(0);
            default: printf("\n  [ERROR] Invalid Selection.\n");
        }
    }
    return 0;
}

// ====================================================
//                 CORE FUNCTIONS
// ====================================================

// 1. Register Voter
void registerVoter() {
    if (totalRecords >= MAX_VOTERS) {
        printf("\n  [ERROR] Database Full.\n"); return;
    }

    Voter v;
    printHeader("NEW VOTER REGISTRATION");

    // Auto-ID
    sprintf(v.voterID, "KA-SEC-%04d", totalRecords + 1001);
    printf("  [SYSTEM] Generated ID   : %s\n", v.voterID);

    printf("  Enter Full Name         : ");
    fgets(v.name, 50, stdin); v.name[strcspn(v.name, "\n")] = 0;

    printf("  Enter Father's Name     : ");
    fgets(v.fatherName, 50, stdin); v.fatherName[strcspn(v.fatherName, "\n")] = 0;

    printf("  Enter Gender (M/F)      : ");
    fgets(v.gender, 10, stdin); v.gender[strcspn(v.gender, "\n")] = 0;

    printf("  Enter DOB (DD/MM/YYYY)  : ");
    fgets(v.dob, 15, stdin); v.dob[strcspn(v.dob, "\n")] = 0;

    // Logic: Calculate Age
    v.age = calculateAge(v.dob);
    if (v.age < 18) {
        printf("\n  [REJECTED] Applicant is %d years old (Min: 18).\n", v.age);
        return;
    }

    printf("  Enter Address           : ");
    fgets(v.address, 100, stdin); v.address[strcspn(v.address, "\n")] = 0;

    v.hasVoted = 0;
    database[totalRecords++] = v;
    printf("\n  [SUCCESS] Registration Complete.\n");
    saveDatabase();
}

// 2. Generate Bulk Data (250+ Records)
void generateBulkData() {
    int count;
    printf("\n  Enter number of records to generate (e.g., 250): ");
    scanf("%d", &count);

    if (totalRecords + count > MAX_VOTERS) {
        printf("  [ERROR] Not enough space in database.\n"); return;
    }

    // Dataset Banks
    char *firstNames[] = {"Ramesh", "Suresh", "Ganesh", "Priya", "Lakshmi", "Rahul", "Aditi", "Karthik", "Sneha", "Anil"};
    char *lastNames[] = {"Gowda", "Patil", "Reddy", "Rao", "Shetty", "Hegde", "Kumar", "Bhat", "Deshpande", "Nair"};
    char *fathers[] = {"Shankar", "Narayan", "Krishna", "Venkatesh", "Ram", "Shiv", "Govind", "Mohan"};
    char *areas[] = {"Indiranagar", "Jayanagar", "Whitefield", "Koramangala", "MG Road", "Hebbal", "Malleshwaram"};

    printf("  [SYSTEM] Generating data... Please wait.\n");

    for (int i = 0; i < count; i++) {
        Voter v;
        sprintf(v.voterID, "KA-SEC-%04d", totalRecords + 1001);
        
        // Random Name Construction
        sprintf(v.name, "%s %s", firstNames[rand() % 10], lastNames[rand() % 10]);
        sprintf(v.fatherName, "%s %s", fathers[rand() % 8], lastNames[rand() % 10]);
        
        // Random Gender
        if (rand() % 2 == 0) strcpy(v.gender, "Male");
        else strcpy(v.gender, "Female");

        // Random DOB (Age 18 to 80)
        int year = CURRENT_YEAR - (18 + rand() % 62);
        sprintf(v.dob, "%02d/%02d/%d", 1 + rand()%28, 1 + rand()%12, year);
        v.age = CURRENT_YEAR - year;

        // Random Address
        sprintf(v.address, "#%d, %s, Bangalore", rand()%999, areas[rand()%7]);

        v.hasVoted = (rand() % 100 < 60) ? 1 : 0; // 60% chance voted

        database[totalRecords++] = v;
    }
    printf("  [SUCCESS] Added %d records. Total Database: %d\n", count, totalRecords);
    saveDatabase();
}

// 3. Reset Database (Bulk Delete)
void resetDatabase() {
    char confirm;
    printf("\n  [WARNING] This will DELETE ALL %d records. Irreversible.\n", totalRecords);
    printf("  Are you sure? (y/n): ");
    scanf(" %c", &confirm);
    
    if (confirm == 'y' || confirm == 'Y') {
        totalRecords = 0;
        remove(DB_FILE); // Delete the actual file
        printf("  [SUCCESS] Database wiped clean.\n");
    } else {
        printf("  [CANCELLED] Operation aborted.\n");
    }
}

// 4. Remove Single Voter
void removeVoter() {
    char id[20];
    printf("\n  Enter Voter ID to Delete: ");
    scanf("%s", id);

    int found = -1;
    for (int i = 0; i < totalRecords; i++) {
        if (strcmp(database[i].voterID, id) == 0) {
            found = i;
            break;
        }
    }

    if (found != -1) {
        // Shift Array Logic
        for (int i = found; i < totalRecords - 1; i++) {
            database[i] = database[i+1];
        }
        totalRecords--;
        printf("  [SUCCESS] Voter %s removed.\n", id);
        saveDatabase();
    } else {
        printf("  [ERROR] ID not found.\n");
    }
}

// 5. Analytics
void electionAnalytics() {
    
    if (totalRecords == 0) { printf("\n  [INFO] No Data.\n"); return; }
    
    int male = 0, female = 0, voted = 0;
    int youth = 0, adult = 0, senior = 0;

    for (int i = 0; i < totalRecords; i++) {
        if (strcasecmp(database[i].gender, "Male") == 0) male++;
        else female++;

        if (database[i].hasVoted) voted++;

        if (database[i].age <= 30) youth++;
        else if (database[i].age <= 60) adult++;
        else senior++;
    }

    printHeader("ELECTION ANALYTICS REPORT");
    printf("  [1] TURNOUT\n");
    printf("      Total Registered    : %d\n", totalRecords);
    printf("      Votes Polled        : %d\n", voted);
    printf("      Turnout %%           : %.2f%%\n", (float)voted/totalRecords * 100);
    printf("\n  [2] DEMOGRAPHICS (AGE)\n");
    printf("      Youth (18-30)       : %d\n", youth);
    printf("      Adult (31-60)       : %d\n", adult);
    printf("      Senior (60+)        : %d\n", senior);
    printf("\n  [3] GENDER RATIO\n");
    printf("      Male                : %d\n", male);
    printf("      Female              : %d\n", female);
    printSeparator();
}

// 6. View All
void viewAllVoters() {
    printHeader("VOTER REGISTRY");
    printf("  %-15s | %-20s | %-6s | %-12s | %-10s\n", "VOTER ID", "NAME", "AGE", "GENDER", "STATUS");
    printSeparator();
    for (int i = 0; i < totalRecords; i++) {
        printf("  %-15s | %-20s | %-6d | %-12s | %-10s\n", 
            database[i].voterID, database[i].name, database[i].age, 
            database[i].gender, database[i].hasVoted ? "VOTED" : "OPEN");
    }
    printSeparator();
}

// 7. Cast Vote
void castVote() {
    char id[20];
    printf("\n  Enter Voter ID: ");
    scanf("%s", id);

    for (int i = 0; i < totalRecords; i++) {
        if (strcmp(database[i].voterID, id) == 0) {
            if (database[i].hasVoted) printf("  [ALERT] Already Voted!\n");
            else {
                database[i].hasVoted = 1;
                printf("  [SUCCESS] Vote Recorded for %s.\n", database[i].name);
                saveDatabase();
            }
            return;
        }
    }
    printf("  [ERROR] ID Not Found.\n");
}

// 8. Search
void searchVoter() {
    char key[50];
    printf("\n  Enter Name or ID: ");
    fgets(key, 50, stdin); key[strcspn(key, "\n")] = 0;

    printHeader("SEARCH RESULTS");
    int found = 0;
    for (int i = 0; i < totalRecords; i++) {
        if (strstr(database[i].voterID, key) || strstr(database[i].name, key)) {
            printf("  ID: %s | Name: %s | Father: %s | Addr: %s\n", 
                database[i].voterID, database[i].name, database[i].fatherName, database[i].address);
            found = 1;
        }
    }
    if (!found) printf("  No records match your query.\n");
    printSeparator();
}

// ====================================================
//                  UTILITIES
// ====================================================

int calculateAge(char *dob) {
    int day, month, year;
    sscanf(dob, "%d/%d/%d", &day, &month, &year);
    return CURRENT_YEAR - year;
}

void loadDatabase() {
    FILE *fp = fopen(DB_FILE, "r");
    if (!fp) return;
    char buffer[512];
    totalRecords = 0;
    fgets(buffer, 512, fp); // Skip header
    while (fgets(buffer, 512, fp)) {
        Voter v;
        sscanf(buffer, "%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%d,%d\n", 
            v.voterID, v.name, v.fatherName, v.gender, v.dob, v.address, &v.age, &v.hasVoted);
        database[totalRecords++] = v;
    }
    fclose(fp);
}

void saveDatabase() {
    FILE *fp = fopen(DB_FILE, "w");
    if (!fp) return;
    fprintf(fp, "ID,Name,Father,Gender,DOB,Address,Age,Voted\n");
    for (int i = 0; i < totalRecords; i++) {
        fprintf(fp, "%s,%s,%s,%s,%s,%s,%d,%d\n", 
            database[i].voterID, database[i].name, database[i].fatherName, 
            database[i].gender, database[i].dob, database[i].address, database[i].age, database[i].hasVoted);
    }
    fclose(fp);
}

void printHeader(char *title) {
    printf("\n");
    printf("  /// %s ///\n", title);
    printf("  --------------------------------------------------------------\n");
}

void printSeparator() {
    printf("  --------------------------------------------------------------\n");
}