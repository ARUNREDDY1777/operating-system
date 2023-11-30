#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define RECORD_SIZE 50 // Assuming each record is of size 50 bytes

// Structure defining a record
typedef struct {
    int recordId;
    char data[RECORD_SIZE - sizeof(int)]; // Account for the size of recordId
} Record;

// Function to write a record to a file
void writeRecord(FILE *file, const Record *record) {
    fwrite(record, sizeof(Record), 1, file);
}

// Function to read all records from the file up to a given record ID
void readRecords(FILE *file, int targetRecordId) {
    Record readRecord;
    fseek(file, 0, SEEK_SET); // Move to the beginning of the file

    while (!feof(file)) {
        fread(&readRecord, sizeof(Record), 1, file);
        if (readRecord.recordId == targetRecordId) {
            printf("Found Record ID: %d, Data: %s\n", readRecord.recordId, readRecord.data);
            return;
        }
        printf("Reading Record ID: %d, Data: %s\n", readRecord.recordId, readRecord.data);
    }

    printf("Record ID %d not found!\n", targetRecordId);
}

int main() {
    FILE *file;
    Record records[5]; // Example: Array of 5 records

    // Initialize records with sample data
    for (int i = 0; i < 5; ++i) {
        records[i].recordId = i + 1;
        snprintf(records[i].data, sizeof(records[i].data), "Record %d Data", i + 1);
    }

    // Write records to a file
    file = fopen("records.bin", "wb"); // Open file in binary write mode
    if (file == NULL) {
        perror("Error opening file");
        return 1;
    }

    for (int i = 0; i < 5; ++i) {
        writeRecord(file, &records[i]);
    }

    fclose(file);

    // Read records from the file based on record ID
    file = fopen("records.bin", "rb"); // Open file in binary read mode
    if (file == NULL) {
        perror("Error opening file");
        return 1;
    }

    // Simulate accessing specific records
    readRecords(file, 3); // Access record with ID 3
    readRecords(file, 6); // Access record with ID 6 (not present)

    fclose(file);

    return 0;
}

