#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 256

// MAIN DATABASE
struct database
{
  char name[MAX];
  int key;
};
struct database data[MAX];

// Number of data entries
int data_number = 0;

/*                                            MENU FUNCTIONS                                                    */

// main menu
void menu(int user_input, int type);
// Function to extract key into digits for encryption
void extract_key(int key, int *extracted_key);
// main encryption and decryption function
void encrypt_decrypt_file(int tries, int code);

/*                                            Some Required Functions                                                */

// typing animation
void typewriter_print(char *str, unsigned int milliseconds, int colour_code);
// file name input checks
void input_file_name(int tries, char *name, int code);
// encryption key input checks
int input_key(int code);
// storing record in the main database
void store_record(struct database *s);
// checking of record to check if the key entered by the user during decryption is correct
void check_record(struct database *s);

// MAIN

int main()
{
  printf("                    ");
  typewriter_print("WELCOME TO FILE ENCRYPTION SYSTEM", 60, 197);
  printf("                                                 ");
  typewriter_print(" -created by Luv Valecha(B23CM1022)", 30, 27);
  typewriter_print("Choose Your Task:", 70, 208);
  typewriter_print("1. File Encryption", 70, 208);
  typewriter_print("2. File Decryption", 50, 208);
  typewriter_print("3. Exit", 70, 208);
  int user_input;
  int type = scanf("%d", &user_input);
  menu(user_input, type);

  return 0;
}

void menu(int user_input, int type)
{
  // variable 'tries' help in buffer clearing in encrypt file function
  int tries;
  switch (user_input)
  {
  case 1:
    tries = 0;
    encrypt_decrypt_file(tries, 1);
    break;
  case 2:
    tries = 0;
    encrypt_decrypt_file(tries, 2);
    break;
  case 3:
    typewriter_print("THANK YOU!", 70, 208);
    exit(0);
  default:
    typewriter_print("INVALID INPUT!", 5, 196);
    // If input type is not integer, clear the buffer
    if (type != 1)
    {
      int c;
      while ((c = getchar()) != '\n' && c != EOF)
        ;
    }
    main();
    break;
  }
}

void typewriter_print(char *str, unsigned int milliseconds, int colour_code)
{
  for (; *str != '\0'; str++)
  {
    printf("\x1b[38;5;%d;1m", colour_code);
    putchar(*str);
    fflush(stdout);
    usleep(milliseconds * 700);
    printf("\x1b[0m");
  }
  putchar('\n');
}

void store_record(struct database *s)
{
  FILE *record;
  int code=1;
  record = fopen("Encryption_Database.txt", "r");
  if (record == NULL)
  {
    code = 0;
  }
  if (code != 0)
  {
    // variable to check that the while loop does not run infinitely
    int infinite_loop_check = 0;
    char name[MAX]="";
    int key;
    // check if the file name already exists in the database
    while ((strcmp(name, s->name) != 0) && (infinite_loop_check != 10000))
    {
      fscanf(record, "%s %d", name, &key);
      infinite_loop_check++;
    }
    fclose(record);
    // if file already exists, update its key
    fseek(record, 0, SEEK_SET);
    if (infinite_loop_check != 10000)
    {
      char buffer[400];
      record = fopen("Encryption_Database.txt", "r+");
      while (fgets(buffer, sizeof(buffer), record) != NULL)
      {
        if (strstr(buffer, s->name) != NULL)
        {
          // bring cursor to that line where our required file is
          fseek(record, -strlen(buffer) - 1, SEEK_CUR);
          // data updation in that line
          fprintf(record, "%s %d\n", s->name, s->key);
          break;
        }
      }
      fclose(record);
    }
    // if file does not already exists, add a new entry in our database
    else if(infinite_loop_check==10000)
    {
      record = fopen("Encryption_Database.txt", "a");
      fprintf(record, "%s %d\n", s->name, s->key);
      fclose(record);
    }
  }
  else
  {
    record = fopen("Encryption_Database.txt", "a");
    fprintf(record, "%s %d\n", s->name, s->key);
    fclose(record);
  }
  typewriter_print("Your encrypted file has been created in the same location as the input file", 50, 226);
  typewriter_print("Make sure to delete your original file", 10, 226);
}

void check_record(struct database *s)
{
  FILE *record;
  record = fopen("Encryption_Database.txt", "r");
  if (record == NULL)
  {
    typewriter_print("No Database Exists!", 5, 196);
    main();
  }
  int key = 0;
  char name[MAX];
  // set cursor to start of the file
  fseek(record, 0, SEEK_SET);
  // variable to check that the while loop does not go into infinite loop
  int infinite_loop_check = 0;
  // check the name of the file and its associated key
  while ((strcmp(name, s->name) != 0) && (infinite_loop_check != 10000))
  {
    fscanf(record, "%s %d", name, &key);
    infinite_loop_check++;
  }
  // if key entered by the user and the stored key in database is same, decrypt the file
  if ((key == s->key) && (infinite_loop_check != 10000))
  {
    return;
  }
  // raise an error if the key is wrong or the file name does not exist in the database
  else
  {
    int c;
    while ((c = getchar()) != '\n')
    {
    };
    typewriter_print("Wrong Encryption Key or file is not encrypted!", 5, 196);
    encrypt_decrypt_file(1, 2);
  }
}

void input_file_name(int tries, char *name, int code)
{
  typewriter_print("Enter Text File Name: (Enter menu for main menu)", 70, 226);
  // we need to clear the input buffer only the first time
  if (tries == 0)
  {
    while (getchar() != '\n')
      ;
  }
  fgets(name, MAX, stdin);
  // change the last character to null character instead of newline character
  name[strcspn(name, "\n")] = '\0';
  // basic error check
  if (strlen(name) >= MAX)
  {
    typewriter_print("NAME TOO LONG!", 5, 196);
    encrypt_decrypt_file(tries + 1, code);
  }
  else if (strcmp(name, "menu") == 0)
  {
    main();
  }
  FILE *fptr;
  fptr = fopen(name, "r");
  if (fptr == NULL)
  {
    typewriter_print("FILE DOES NOT EXIST!", 5, 196);
    encrypt_decrypt_file(tries + 1, code);
  }
  fclose(fptr);
}

int input_key(int code)
{
  int key;
  do
  {
    if (code == 1)
    {
      typewriter_print("Set Encryption Key of four digits (Enter 0 for main menu)", 70, 226);
    }
    else if (code == 2)
    {
      typewriter_print("Enter Encryption Key for this file (Enter 0 for main menu) ", 70, 226);
    }
    printf("\x1b[38;5;15;1m");
    if (code == 1)
    {
      printf("(Key should be greater than or equal to 1000): \n");
      printf("(Make sure to remember this key): ");
    }
    else if (code == 2)
    {
      printf("(Enter the Correct Key for this file): ");
    }
    printf("\x1b[0m");
    // take the return value of scanf also, if return value is not 1 then input value id is not of int type
    int type = scanf("%d", &key);
    if ((key == 0) && (type == 1))
    {
      main();
    }
    // keep asking the key of the key is not of four digits
    else if (key < 1000 || key >= 10000)
    {
      if (type != 1)
      {
        // clear buffer
        int c;
        while ((c = getchar()) != '\n' && c != EOF)
          ;
      }
      typewriter_print("KEY IS NOT OF FOUR DIGITS OR CORRECT DATA TYPE!, ENTER AGAIN ", 5, 196);
    }
  } while (key < 1000 || key >= 10000);
  return key;
}

void extract_key(int key, int *extracted_key)
{
  extracted_key += 3;
  while (key != 0)
  {
    *extracted_key = key % 10;
    key /= 10;
    extracted_key--;
  }
}

void encrypt_decrypt_file(int tries, int code)
{
  int sign;
  // code 1 means encryption, code 2 means decryption
  if (code == 1)
  {
    sign = -1;
  }
  else if (code == 2)
  {
    sign = 1;
  }
  char name[MAX];
  input_file_name(tries, name, code);
  data_number++;
  strcpy(data[data_number].name, name);
  int key = input_key(code);
  data[data_number].key = key;
  if (code == 2)
  {
    check_record(&data[data_number]);
  }
  int extracted_key[4];
  extract_key(data[data_number].key, extracted_key);
  //integer 6 causes problem while encrypting, so changing it to 7 internally (Substitue Control Character problem)
  for(int i=0;i<4;i++){
    if(extracted_key[i]==6){
      extracted_key[i]=7;
    }
  }
  FILE *fptr_source;
  FILE *fptr_target;
  fptr_source = fopen(data[data_number].name, "r");
  if (code == 1)
  {
    fptr_target = fopen(strcat(data[data_number].name, "_encrypted.txt"), "w");
  }
  else if (code == 2)
  {
    fptr_target = fopen(strcat(data[data_number].name, "_decrypted.txt"), "w");
  }
  char ch = fgetc(fptr_source);
  int digit = 0;
  while (ch != EOF)
  {
    char enc_ch = ((int)ch + (sign)*extracted_key[digit % 4]);
    fputc(enc_ch, fptr_target);
    ch = fgetc(fptr_source);
    digit++;
  }
  fclose(fptr_source);
  fclose(fptr_target);
  if (code == 1)
  {
    store_record(&data[data_number]);
  }
  else if (code == 2)
  {
    typewriter_print("Your decrypted file has been created in the same location as the encrypted file", 50, 226);
    typewriter_print("Do you want to read your file? (Y/N)", 50, 226);
    char input[MAX];
    while (getchar() != '\n')
      ;
    fgets(input, MAX, stdin);
    input[strcspn(input, "\n")] = '\0';
    if ((strcmp(input, "Yes") == 0) || (strcmp(input, "yes") == 0) || (strcmp(input, "Y") == 0) || (strcmp(input, "y") == 0))
    {
      FILE *reading;
      reading = fopen(data[data_number].name, "r");
      if (reading == NULL)
      {
        typewriter_print("Error opening the file, try again", 5, 196);
      }
      char c;
      while ((c = fgetc(reading)) != EOF)
      {
        printf("%c", c);
      }
      printf("\n");
      fclose(reading);
    }
  }
  typewriter_print("THANK YOU!", 80, 197);
  main();
}

/*********************************************************END**************************************************************************/