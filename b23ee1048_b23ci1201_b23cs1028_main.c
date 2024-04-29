#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#include<time.h>
#include<math.h>

#define MAX_STRING_LENGTH 100
#define MAX_WORD_LENGTH 50
#define MAX_LINE_LENGTH 1000

void count_words(){
    FILE *fptr = NULL; 
    printf("Enter text file name: ");
    char txtfile[35];
    scanf("%s", txtfile);
    fptr = fopen(txtfile, "r");
    if(fptr == NULL) {
        printf("Error opening file!");
        exit(1);
    } else {
        int count = 0;
        int in_word = 0;
        char c;
        while ((c = fgetc(fptr)) != EOF) {
            if (isspace(c) || ispunct(c)) {
                in_word = 0;
            } else if (!in_word) {
                in_word = 1;
                count++;
            }
        }
        printf("The number of words is %d\n", count);
    }
    fclose(fptr);

}
void count_lines(){
    FILE *fptr = NULL; 
    printf("Enter text file name: ");
    char txtfile[35];
    scanf("%s", txtfile);
    fptr = fopen(txtfile, "r");
    if(fptr == NULL) {
        printf("Error opening file!");
        exit(1);
    } else {
        int count = 0;
        char c;
        while ((c = fgetc(fptr)) != EOF) {
            if (c == '\n') {
                count++;
            }
        }
        // If the last line doesn't end with a newline character, we should increment count
        if (count > 0) {
            count++;
        }
        printf("The number of lines is %d\n", count);
    }
    fclose(fptr);
}
void insert_emoji_last() {
    char txtfile[35];
    printf("Enter the name of the text file: ");
    scanf("%s", txtfile);

    FILE *file = fopen(txtfile, "r+");
    if (file == NULL) {
        printf("Error opening file.\n");
        exit(1);
    }

    char emoji[MAX_STRING_LENGTH];
    int choice;
    printf("Choose an emoji to insert:\n");
    printf("1. Thumbs up\n");
    printf("2. Heart\n");
    printf("3. Smiley face\n");
    printf("4. Snowman\n");
    printf("5. Fire\n");
    printf("6. Rocket\n");
    printf("7. Unicorn\n");
    printf("8. Rainbow\n");
    printf("Enter your choice: ");
    scanf("%d", &choice);

    switch (choice) {
        case 1:
            strcpy(emoji, "\xF0\x9F\x91\x8D"); // Thumbs up emoji
            break;
        case 2:
            strcpy(emoji, "\xE2\x9D\xA4"); // Heart emoji
            break;
        case 3:
            strcpy(emoji, "\xF0\x9F\x98\x81"); // Smiley face emoji
            break;
        case 4:
            strcpy(emoji, "\xE2\x9B\x84"); // Snowman emoji
            break;
        case 5:
            strcpy(emoji, "\xF0\x9F\x94\xA5"); // Fire emoji
            break;
        case 6:
            strcpy(emoji, "\xF0\x9F\x9A\x80"); // Rocket emoji
            break;
        case 7:
            strcpy(emoji, "\xF0\x9F\xA6\x84"); // Unicorn emoji
            break;
        case 8:
            strcpy(emoji, "\xF0\x9F\x8C\x88"); // Rainbow emoji
            break;
        default:
            printf("Invalid choice.\n");
            exit(1);
    }

    fseek(file, 0, SEEK_END); // Move to the end of the file

    // Insert the emoji at the end of the file
    fputs(emoji, file);

    fclose(file);
    printf("Emoji inserted successfully.\n");
}

void insert_emoji_nth_char() {
    char txtfile[35];
    printf("Enter the name of the text file: ");
    scanf("%s", txtfile);

    FILE *file = fopen(txtfile, "r+");
    if (file == NULL) {
        printf("Error opening file.\n");
        exit(1);
    }

    int n;
    printf("Enter the position of the character to insert the emoji after: ");
    scanf("%d", &n);

    // Move the file pointer to the insertion point
    fseek(file, n, SEEK_SET);

    // Read the text after the insertion point
    char buffer[512];
    size_t bytesRead = fread(buffer, 1, sizeof(buffer), file);
    if (bytesRead == 0) {
        printf("Error reading file.\n");
        fclose(file);
        exit(1);
    }

    // Move the file pointer back to the insertion point
    fseek(file, n, SEEK_SET);

    // Predefined emojis
    char emojis[8][MAX_STRING_LENGTH] = {
        "\xF0\x9F\x91\x8D",  // Thumbs up emoji
        "\xE2\x9D\xA4",      // Heart emoji
        "\xF0\x9F\x98\x81",  // Smiley face emoji
        "\xF0\x9F\x98\x8E",  // Smiling face with sunglasses emoji
        "\xF0\x9F\x98\xA2",  // Crying face emoji
        "\xF0\x9F\x98\xA0",  // Angry face emoji
        "\xF0\x9F\x98\x84",  // Smiling face with open mouth and smiling eyes emoji
        "\xF0\x9F\x98\x8D"   // Smiling face with heart-eyes emoji
    };

    // Prompt the user to select one emoji
    printf("Choose an emoji to insert:\n");
    printf("1. Thumbs up\n");
    printf("2. Heart\n");
    printf("3. Smiley face\n");
    printf("4. Smiling face with sunglasses\n");
    printf("5. Crying face\n");
    printf("6. Angry face\n");
    printf("7. Smiling face with open mouth and smiling eyes\n");
    printf("8. Smiling face with heart-eyes\n");
    int choice;
    printf("Enter your choice: ");
    scanf("%d", &choice);

    // Validate user input
    if (choice < 1 || choice > 8) {
        printf("Invalid choice.\n");
        fclose(file);
        exit(1);
    }

    // Insert the chosen emoji
    fprintf(file, "%s", emojis[choice - 1]);

    // Write back the previously read text
    fwrite(buffer, 1, bytesRead, file);

    fclose(file);
    printf("Emoji inserted successfully after the %dth character.\n", n);
}
int countOccurrences(FILE *fptr, const char *word) {
    char line[MAX_LINE_LENGTH];
    int count = 0;
    size_t wordLen = strlen(word);

    // Read each line from the file
    while (fgets(line, sizeof(line), fptr) != NULL) {
        char *pos = line;

        // Search for the word in the line
        while ((pos = strstr(pos, word)) != NULL) {
            // Check if the word exists as a separate word
            if ((pos == line || !isalpha(*(pos - 1))) && !isalpha(*(pos + wordLen))) {
                count++;
            }
            // Move pos pointer to the next character
            pos++;
        }
    }

    return count;
}
// Function to encrypt a character using a simple Caesar cipher
char encryptChar(char old_ch, int shift) {
    // Apply the encryption logic
    char ch = old_ch + shift;

    // Check if the character is a lowercase letter and adjust if necessary
    if (islower(old_ch)) {
        if (ch > 'z') {
            ch = ch - 26;
        } else if (ch < 'a') {
            ch = ch + 26;
        }
    }
    // Check if the character is an uppercase letter and adjust if necessary
    else if (isupper(old_ch)) {
        if (ch > 'Z') {
            ch = ch - 26;
        } else if (ch < 'A') {
            ch = ch + 26;
        }
    }
    return ch;
}

// Function to encrypt a text file using a simple Caesar cipher
void encryptFile(const char *inp_txtfile, const char *out_txtfile, int shift) {
    // Open the input file for reading
    FILE *inputFile = fopen(inp_txtfile, "r");
    if (inputFile == NULL) {
        printf("Error opening input file.\n");
        return;
    }

    // Open the output file for writing
    FILE *outputFile = fopen(out_txtfile, "w");
    if (outputFile == NULL) {
        printf("Error opening output file.\n");
        fclose(inputFile);
        return;
    }

    // Read and encrypt each character from the input file
    int old_ch;
    while ((old_ch = fgetc(inputFile)) != EOF) {
        // Encrypt the character
        char ch = encryptChar(old_ch, shift);
        // Write the encrypted character to the output file
        fputc(ch, outputFile);
    }

    // Close the input and output files
    fclose(inputFile);
    fclose(outputFile);

    printf("File encrypted successfully.\n");
}
// Function to encrypt or decrypt a character using a simple Caesar cipher
char DecryptChar(char old_ch, int shift) {
    // Apply the encryption/decryption logic
    char ch = old_ch + shift;

    // Check if the character is a lowercase letter and adjust if necessary
    if (islower(old_ch)) {
        if (ch > 'z') {
            ch = ch - 26;
        } else if (ch < 'a') {
            ch = ch + 26;
        }
    }
    // Check if the character is an uppercase letter and adjust if necessary
    else if (isupper(old_ch)) {
        if (ch > 'Z') {
            ch = ch - 26;
        } else if (ch < 'A') {
            ch = ch + 26;
        }
    }
    return ch;
}

// Function to encrypt or decrypt a text file using a simple Caesar cipher
void DecryptFile(const char *inputFileName, const char *outputFileName, int shift) {
    // Open the input file for reading
    FILE *inputFile = fopen(inputFileName, "r");
    if (inputFile == NULL) {
        printf("Error opening input file.\n");
        return;
    }

    // Open the output file for writing
    FILE *outputFile = fopen(outputFileName, "w");
    if (outputFile == NULL) {
        printf("Error opening output file.\n");
        fclose(inputFile);
        return;
    }

    // Read and encrypt/decrypt each character from the input file
    int old_ch;
    while ((old_ch = fgetc(inputFile)) != EOF) {
        // Encrypt or decrypt the character
        char ch = DecryptChar(old_ch, shift);
        // Write the encrypted/decrypted character to the output file
        fputc(ch, outputFile);
    }

    // Close the input and output files
    fclose(inputFile);
    fclose(outputFile);

    printf("File decrypted successfully.\n");
}
// Function to add multiple files together
void addFiles(int numFiles, char **fileNames, const char *outputFileName) {
    // Open the output file for writing
    FILE *outputFile = fopen(outputFileName, "w");
    if (outputFile == NULL) {
        printf("Error opening output file.\n");
        return;
    }

    // Loop through each input file
    for (int i = 0; i < numFiles; i++) {
        // Open the input file for reading
        FILE *inputFile = fopen(fileNames[i], "r");
        if (inputFile == NULL) {
            printf("Error opening input file: %s\n", fileNames[i]);
            fclose(outputFile);
            return;
        }

        // Read and write the content of the input file to the output file
        int ch;
        while ((ch = fgetc(inputFile)) != EOF) {
            fputc(ch, outputFile);
        }

        // Close the input file
        fclose(inputFile);
    }

    // Close the output file
    fclose(outputFile);

    printf("Files added successfully.\n");
}
void print_date_time(){
    // Get the current date and time
    time_t currentTime;
    time(&currentTime);
    char *dateTimeString = ctime(&currentTime);

    // Input file name
    char txtfile[35];
    printf("Enter the name of the input file: ");
    scanf("%s", txtfile);

    // Open the file for reading
    FILE *file = fopen(txtfile, "r");
    if (file == NULL) {
        printf("Error opening file.\n");
        exit(1);
    }

    // Count the number of lines in the file
    int lineCount = 0;
    char ch;
    while ((ch = fgetc(file)) != EOF) {
        if (ch == '\n') {
            lineCount++;
        }
    }

    // Close the file
    fclose(file);

    // Check if the desired line number is valid
    int nthLine;
    printf("Enter the line number to insert the date and time: ");
    scanf("%d", &nthLine);

    if (nthLine < 1 || nthLine > lineCount + 1) {
        printf("Invalid line number.\n");
        exit(1);
    }

    // Open the file for reading and writing
    file = fopen(txtfile, "r+");
    if (file == NULL) {
        printf("Error opening file.\n");
        exit(1);
    }

    // Move to the nth line
    for (int i = 1; i < nthLine; i++) {
        while ((ch = fgetc(file)) != '\n' && ch != EOF) {
            // Move to the end of the current line
        }
    }

    // Get the current position in the file
    long position = ftell(file);

    // Read the remaining content of the file
    char buffer[1000]; // Adjust buffer size as needed
    size_t bytesRead = fread(buffer, 1, sizeof(buffer), file);
    if (bytesRead == 0 && ferror(file)) {
        printf("Error reading file.\n");
        fclose(file);
        exit(1);
    }

    // Move back to the position where we want to insert the date and time
    fseek(file, position, SEEK_SET);

    // Print the date and time into the file
    fprintf(file, " %s", dateTimeString);

    // Write the remaining content back to the file
    fwrite(buffer, 1, bytesRead, file);

    // Close the file
    fclose(file);

    printf("Date and time inserted at line %d.\n", nthLine);


}
// Comparison function for qsort
int compare(const void *a, const void *b) {
    return (*(int*)a - *(int*)b);
}
// Function to delete a line from a file
void delete_Line(const char *txtfile, int lineToDelete) {
    // Open the file in read mode
    FILE *file = fopen(txtfile, "r");
    if (file == NULL) {
        printf("Error opening file.\n");
        return;
    }

    // Create a temporary file to store the modified content
    FILE *tempFile = fopen("temp.txt", "w");
    if (tempFile == NULL) {
        printf("Error creating temporary file.\n");
        fclose(file);
        return;
    }

    char buffer[512];
    int lineNum = 1;

    // Read each line from the original file
    while (fgets(buffer, sizeof(buffer), file)) {
        // If the current line is not the one to delete, write it to the temporary file
        if (lineNum != lineToDelete) {
            fputs(buffer, tempFile);
        }
        lineNum++;
    }

    // Close both files
    fclose(file);
    fclose(tempFile);

    // Remove the original file
    remove(txtfile);

    // Rename the temporary file to the original file name
    rename("temp.txt", txtfile);

    printf("Line %d deleted successfully.\n", lineToDelete);
}
// Function to display the content of a specific line in a file
void display_LineContent(const char *txtfile, int lineNumber) {
    // Open the file in read mode
    FILE *file = fopen(txtfile, "r");
    if (file == NULL) {
        printf("Error opening file.\n");
        return;
    }

    char buffer[550];
    int currentLine = 1;

    // Read each line from the file until reaching the desired line
    while (fgets(buffer, sizeof(buffer), file)) {
        if (currentLine == lineNumber) {
            printf("Content of line %d: \n%s\n", lineNumber, buffer);
            fclose(file);
            return;
        }
        currentLine++;
    }

    // If the desired line is not found
    printf("Line %d not found in the file.\n", lineNumber);
    fclose(file);
}
void display_FileContent(const char *txtfile) {
    // Open the file in read mode
    FILE *file = fopen(txtfile, "r");
    if (file == NULL) {
        printf("Error opening file.\n");
        return;
    }

    char buffer[512];

    // Read each line from the file and print it
    while (fgets(buffer, sizeof(buffer), file)) {
        printf("%s", buffer);
    }

    // Close the file
    fclose(file);
}
void replaceText(const char *txtfile, const char *search, const char *replace) {
    FILE *inputFile = fopen(txtfile, "r");
    FILE *tempFile = fopen("temp.txt", "w");
    char buffer[512];
    int found = 0; // Flag to indicate if search text was found

    if (inputFile == NULL || tempFile == NULL) {
        printf("Error opening files.\n");
        return;
    }

    int searchLen = strlen(search);

    while (fgets(buffer, sizeof(buffer), inputFile)) {
        char *pos = buffer;
        char *temp;

        // Repeat until search string is found
        while ((temp = strstr(pos, search)) != NULL) {
            found = 1; // Set found flag to true
            // Write the portion before the search string to the temporary file
            fwrite(pos, 1, temp - pos, tempFile);
            // Write the replacement text to the temporary file
            fputs(replace, tempFile);
            // Move the position after the search string
            pos = temp + searchLen;
        }
        // Write the rest of the line (or the whole line if search string is not found) to the temporary file
        fputs(pos, tempFile);
    }

    fclose(inputFile);
    fclose(tempFile);

    if (!found) {
        printf("Search text '%s' not found in the file.\n", search);
        remove("temp.txt"); // Remove the temporary file
        return;
    }

    remove(txtfile);
    rename("temp.txt", txtfile);

    printf("Text replaced successfully.\n");
}
// Function to compare two strings for qsort
int compareStrings(const void *a, const void *b) {
    return strcmp(*(const char **)a, *(const char **)b);
}

// Function to arrange words in a file into alphabetical order
void arange_Words_Alphabeticaly(const char *txtfile) {
    FILE *file = fopen(txtfile, "r");
    if (file == NULL) {
        printf("Error opening file.\n");
        return;
    }

    // Count the number of words in the file
    int numWords = 0;
    char word[100]; // Assuming maximum word length as 100 characters
    while (fscanf(file, "%s", word) != EOF) {
        numWords++;
    }

    // Close and reopen the file to reset the file pointer
    fclose(file);
    file = fopen(txtfile, "r");
    if (file == NULL) {
        printf("Error reopening file.\n");
        return;
    }

    // Allocate memory for an array to store the words
    char **words = malloc(numWords * sizeof(char *));
    if (words == NULL) {
        printf("Memory allocation failed.\n");
        fclose(file);
        return;
    }

    // Read the words from the file and store them in the array
    for (int i = 0; i < numWords; i++) {
        fscanf(file, "%s", word);
        words[i] = strdup(word);
    }

    fclose(file);

    // Sort the array of words alphabetically
    qsort(words, numWords, sizeof(char *), compareStrings);

    // Write the sorted words back to the file
    file = fopen(txtfile, "w");
    if (file == NULL) {
        printf("Error opening file for writing.\n");
        return;
    }

    for (int i = 0; i < numWords; i++) {
        fprintf(file, "%s\n", words[i]);
        free(words[i]); // Free memory allocated for each word
    }

    fclose(file);
    free(words); // Free memory allocated for the array of words

    printf("Words arranged alphabetically in the file.\n");
}

int main() {
    printf("******************************\n");
    printf("**********Welcome**********\n");
    printf("******************************\n");
    printf("Which functionality would you want :\n");
    printf("1.Count no. of Words in text file\n");
    printf("2.Count no. of lines in text file\n");
    printf("3.Insert an emoji at end of text file\n");
    printf("4.Insert emoji at nth character\n");
    printf("5.Count occurrences of a word\n");
    printf("6.Encrypt at text file\n");
    printf("7.Decrypt an encrypted file\n");
    printf("8.Adding multiple text files\n");
    printf("9.Inserting date and time at particular line\n");
    printf("10.Distribution analysis\n");
    printf("11.Delete a particular line\n");
    printf("12.Display content of a line\n");
    printf("13.Display content of a file\n");
    printf("14.Rename a file\n");
    printf("15.Replace text in a file\n");
    printf("16.Arrange words alphabetically a file\n");
    printf("17.Add content to the file\n");
    int inp;
    scanf("%d", &inp);
    if (inp ==1)
    {
        count_words();
    }
    if (inp ==2)
    {
        count_lines();
    }
    if(inp==3){
         insert_emoji_last();
    }
    if(inp==4)
    {
        insert_emoji_nth_char();
    }
    if(inp==5)
    {
    char txtfile[35];
    printf("Enter the name of the text file: ");
    scanf("%s", txtfile);

    FILE *fptr = fopen(txtfile, "r");
    if (fptr == NULL) {
        printf("Error opening file.\n");
        exit(1);
    }

    char word[MAX_WORD_LENGTH];
    printf("Enter the word to count occurrences: ");
    scanf("%s", word);

    // Count occurrences of the word
    int occurrences = countOccurrences(fptr, word);

    fclose(fptr);

    if (occurrences > 0) {
        printf("The word \"%s\" occurs %d time(s) in the file.\n", word, occurrences);
    } else {
        printf("The word \"%s\" does not exist in the file.\n", word);
    }
    }
    if (inp==6){
        // Input file name
    char inp_txtfile[100];
    printf("Enter the name of the input file: ");
    scanf("%s", inp_txtfile);

    // Output file name (encrypted)
    const char *outputFileName = "encrypted.txt";
    // Encryption shift (Caesar cipher)
    int shift = 3;

    // Encrypt the file
    encryptFile(inp_txtfile, outputFileName, shift);
    }
    if(inp==7){
        // Input file name (encrypted)
    char inp_txtfile[100];
    printf("Enter the name of the input file: ");
    scanf("%s", inp_txtfile);

    // Output file name (decrypted)
    const char *outputFileName = "decrypted.txt";
    // Decryption shift (Caesar cipher)
    int shift = -3; // Negative shift for decryption

    // Decrypt the file
    DecryptFile(inp_txtfile, outputFileName, shift);
   }
   if(inp==8){
    // Input the number of files
    int numFiles;
    printf("Enter the number of files to add: ");
    scanf("%d", &numFiles);

    // Allocate memory for storing file names
    char **fileNames = (char **)malloc(numFiles * sizeof(char *));
    if (fileNames == NULL) {
        printf("Memory allocation failed.\n");
        return 1;
    }

    // Input the file names
    for (int i = 0; i < numFiles; i++) {
        fileNames[i] = (char *)malloc(100 * sizeof(char)); // Assuming maximum filename length of 100
        if (fileNames[i] == NULL) {
            printf("Memory allocation failed.\n");
            return 1;
        }
        printf("Enter the name of file %d: ", i + 1);
        scanf("%s", fileNames[i]);
    }

    // Input the name of the output file
    char outputFileName[100];
    printf("Enter the name of the output file: ");
    scanf("%s", outputFileName);

    // Add the files together
    addFiles(numFiles, fileNames, outputFileName);

    // Free allocated memory
    for (int i = 0; i < numFiles; i++) {
        free(fileNames[i]);
    }
    free(fileNames);

   }
   if(inp ==9){
    print_date_time();
   }
   if(inp==10){
    char txtfile[35];

    // Input file name
    printf("Enter the name of the input file: ");
    scanf("%s", txtfile);

    // Open the file for reading
    FILE *file = fopen(txtfile, "r");
    if (file == NULL) {
        printf("Error opening file.\n");
        return 1;
    }

    // Read the array of numbers from the file
    char line[1000]; // Increase buffer size for longer lines
    if (fgets(line, sizeof(line), file) == NULL) {
        printf("Error reading file.\n");
        fclose(file);
        return 1;
    }
    line[strcspn(line, "\n")] = '\0'; // Ensure null-termination

    // Close the file
    fclose(file);

    // Parse the array of numbers
    int arr[100];
    int size = 0;
    char *token = strtok(line, "{}, \n");
    while (token != NULL) {
        arr[size++] = atoi(token);
        token = strtok(NULL, "{}, \n");
    }

    // Calculate sum, median, mean
    int sum = 0;
    double mean = 0.0;
    for (int i = 0; i < size; i++) {
        sum += arr[i];
    }
    mean = (double)sum / size;

    // Calculate standard deviation, variance, and range
    double variance = 0.0;
    double standardDeviation = 0.0;
   
    for (int i = 0; i < size; i++) {
        variance += pow(arr[i] - mean, 2);
    }
    variance /= size;
    standardDeviation = sqrt(variance);
    

    // Sort the array
    qsort(arr, size, sizeof(int), compare);

    // Open the file for appending
    file = fopen(txtfile, "a");
    if (file == NULL) {
        printf("Error opening file.\n");
        return 1;
    }

    // Write calculations to the file
    fprintf(file, "\nSum: %d\n", sum);
    fprintf(file, "Mean: %.3f\n", mean);
    fprintf(file, "Median: %d\n", arr[size / 2]);
    fprintf(file, "Standard Deviation: %.3f\n", standardDeviation);
    fprintf(file, "Variance: %.3f\n", variance);
    
    fprintf(file, "Ascending order:\n");
    for (int i = 0; i < size; i++) {
        fprintf(file, "%d", arr[i]);
        if (i < size - 1) fprintf(file, ",");
    }
    fprintf(file, "\nDescending order:\n");
    for (int i = size - 1; i >= 0; i--) {
        fprintf(file, "%d", arr[i]);
        if (i > 0) fprintf(file, ",");
    }

    // Close the file
    fclose(file);

    printf("Calculations appended to the file successfully.\n");

   }
   if(inp==11){
    char txtfile[35]; // Maximum filename length assumed as 100 characters
    int lineToDelete;

    printf("Enter the name of the file: ");
    scanf("%s", txtfile);

    printf("Enter the line number you want to delete: ");
    scanf("%d", &lineToDelete);

    // Call the deleteLine function
    delete_Line(txtfile, lineToDelete);
   }
   if(inp==12){
    char txtfile[35]; // Maximum filename length assumed as 100 characters
    int lineNumber;

    printf("Enter the name of the file: ");
    scanf("%s", txtfile);

    printf("Enter the line number you want to display: ");
    scanf("%d", &lineNumber);

    // Call the displayLineContent function
    display_LineContent(txtfile, lineNumber);

   }
   if(inp==13){
    char txtfile[35]; // Maximum filename length assumed as 100 characters

    printf("Enter the name of the file: ");
    scanf("%s", txtfile);

    // Call the displayFileContent function
    display_FileContent(txtfile);

   }
   if(inp==14){
    char old_File[35]; // Maximum filename length assumed as 100 characters
    char new_File[35];

    // Prompt the user to enter the old filename
    printf("Enter the current name of the file: ");
    scanf("%s", old_File);

    // Prompt the user to enter the new filename
    printf("Enter the new name of the file: ");
    scanf("%s", new_File);

    // Rename the file
    if (rename(old_File, new_File) == 0) {
        printf("File renamed successfully from %s to %s.\n", old_File, new_File);
    } else {
        printf("Error renaming file.\n");
    }

   }
   if(inp==15){
    char txtfile[35]; // Maximum filename length assumed as 100 characters
    char search[100];
    char replace[100];

    printf("Enter the name of the file: ");
    scanf("%s", txtfile);

    printf("Enter the text you want to replace: ");
    scanf("%s", search);

    printf("Enter the replacement text: ");
    scanf("%s", replace);

    replaceText(txtfile, search, replace);

   }
   if(inp==16){
    char txtfile[35]; // Maximum filename length assumed as 100 characters

    printf("Enter the name of the file: ");
    scanf("%s", txtfile);

    arange_Words_Alphabeticaly(txtfile);

   }
   if (inp ==17){
    FILE *fptr;
    char txtfile[50];
    char content[100];

    // Ask user for filename
    printf("Enter the filename: ");
    scanf("%s", txtfile);

    // Open file in append mode
    fptr = fopen(txtfile, "a");

    // Check if file opened successfully
    if (fptr == NULL) {
        printf("Unable to open file.\n");
        return 1;
    }

    // Ask user for content to append
    printf("Enter content to append: ");
    scanf(" %[^\n]", content);

    // Append content to file
    fprintf(fptr, "%s", content);

    // Close file
    fclose(fptr);

    printf("Content appended successfully.\n");

   }

    return 0;
}
