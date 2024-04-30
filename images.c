#include <stdio.h>

#define MAX_SIZE 500

void displayMenu();
void loadNewImage(int image[MAX_SIZE][MAX_SIZE], int *size);
void displayImage(int image[MAX_SIZE][MAX_SIZE], int size);
void editImage(int image[MAX_SIZE][MAX_SIZE], int size);
void cropImage(int image[MAX_SIZE][MAX_SIZE], int *size);
void dimImage(int image[MAX_SIZE][MAX_SIZE], int size);
void brightenImage(int image[MAX_SIZE][MAX_SIZE], int size);
void saveImage(int image[MAX_SIZE][MAX_SIZE], int size);
void rotateImage90Degrees(int image[MAX_SIZE][MAX_SIZE], int size);

int main() {
    int image[MAX_SIZE][MAX_SIZE];
    int size = 0;
    int choice;

    do {
        displayMenu();
        scanf("%d", &choice);
        getchar();

        switch (choice) {
            case 1:
                loadNewImage(image, &size);
                break;
            case 2:
                displayImage(image, size);
                break;
            case 3:
                editImage(image, size);
                break;
            case 4:
                printf("Exiting program...\n");
                break;
            default:
                printf("Invalid choice! Please try again.\n");
        }
    } while (choice != 4);

    return 0;
}

void displayMenu() {
    printf("\nMain Menu:\n");
    printf("1. Load a new image\n");
    printf("2. Display the current image\n");
    printf("3. Edit the current image\n");
    printf("4. Exit\n");
    printf("Enter your choice: ");
}

void loadNewImage(int image[MAX_SIZE][MAX_SIZE], int *size) {
    FILE *file;
    char filename[100];
    char ch;
    int row = 0, col = 0;

    printf("Enter the filename: ");
    scanf("%s", filename);

    file = fopen(filename, "r");
    if (file == NULL) {
        printf("Error opening file.\n");
        perror("Error");
        return;
    }

    // Read the image data from the file character by character
    while ((ch = fgetc(file)) != EOF && row < MAX_SIZE) {
        if (ch >= '0' && ch <= '4') {
            // Populate the image array
            image[row][col++] = ch - '0';
        }

        // Move to the next row if newline character encountered
        if (ch == '\n') {
            // Update the size if the current row length exceeds the previous maximum
            if (col > *size) {
                *size = col;
            }
            // Move to the next row
            row++;
            // Reset column index for the next row
            col = 0;
        }
    }

    fclose(file);

    printf("\nImage loaded successfully.\n");
}


void displayImage(int image[MAX_SIZE][MAX_SIZE], int size) {
    int i, j;
    int last_row = 0;

    // Find the index of the last row with content
    for (i = size - 1; i >= 0; i--) {
        for (j = 0; j < size; j++) {
            if (image[i][j] != 0) {
                last_row = i;
                break;
            }
        }
        if (last_row != 0) {
            break;
        }
    }

    printf("Current Image:\n");
    for (i = 0; i <= last_row; i++) {
        for (j = 0; j < size; j++) {
            if (image[i][j] == 0) {
                printf(" ");
            } else if (image[i][j] == 1) {
                printf("o");
            } else if (image[i][j] == 2) {
                printf(".");
            } else if (image[i][j] == 3) {
                printf("O");
            } else if (image[i][j] == 4) {
                printf("0");
            }
            printf(" ");
        }
        printf("\n");
    }
}




void editImage(int image[MAX_SIZE][MAX_SIZE], int size) {
    int choice;

    do {
        printf("\nEdit Menu:\n");
        printf("1. Crop image\n");
        printf("2. Dim image\n");
        printf("3. Brighten image\n");
        printf("4. Rotate the image 90 degrees to the right\n");
        printf("5. Save edited image\n");
        printf("6. Back to main menu\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        getchar(); 

        switch (choice) {
            case 1:
                cropImage(image, &size);
                displayImage(image, size);
                break;
            case 2:
                dimImage(image, size);
                displayImage(image, size);
                break;
            case 3:
                brightenImage(image, size);
                displayImage(image, size);
                break;
            case 4:
                rotateImage90Degrees(image, size);
                displayImage(image, size);
                break;
            case 5:
                saveImage(image, size);
                displayImage(image, size);
                break;
            case 6:
                printf("Returning to main menu...\n");
                break;
            default:
                printf("Invalid choice! Please try again.\n");
        }
    } while (choice != 6);
}



