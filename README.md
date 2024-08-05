# File Encryption System

This project is a simple file encryption and decryption system written in C. The system allows users to encrypt and decrypt text files using a user-defined key. This README file provides an overview of the project's features, usage instructions, and the structure of the code.

## Table of Contents

1. [Features](#features)
2. [Code Structure](#code-structure)
3. [Usage Instructions](#usage-instructions)
4. [Main Menu](#main-menu)
   1. [File Encryption](#file-encryption)
   2. [File Decryption](#file-decryption)
   3. [Exit](#exit)
5. [Notes](#notes)
6. [Future Enhancements](#future-enhancements)

## Features

1. **File Encryption**:
   - Encrypts a given text file using a four-digit key.
   - Stores the encrypted file with a new name in the same location as the original file.
   - The encrypted file is named as `original_filename_encrypted.txt`.

2. **File Decryption**:
   - Decrypts a given encrypted text file using the same four-digit key used for encryption.
   - Stores the decrypted file with a new name in the same location as the original file.
   - The decrypted file is named as `original_filename_decrypted.txt`.

3. **Database Management**:
   - Maintains a record of encrypted files and their associated keys in a text file named `Encryption_Database.txt`.
   - Updates the key if a file is encrypted again with a different key.
   - Checks the key during decryption to ensure it matches the one used during encryption.

4. **User-Friendly Interface**:
   - Provides a main menu for users to choose between encryption, decryption, or exiting the program.
   - Displays messages using a typewriter effect with color coding for enhanced user experience.
   - Allows users to return to the main menu at any point.

## Code Structure

The main components of the project are:

1. **Main Function**:
   - Displays the welcome message and main menu.
   - Handles user input to navigate to encryption, decryption, or exit.

2. **Menu Function (`menu`)**:
   - Processes the user's choice from the main menu.
   - Calls the appropriate function for encryption, decryption, or exiting the program.

3. **Typewriter Print Function (`typewriter_print`)**:
   - Displays messages with a typewriter effect and color coding.

4. **Input Functions**:
   - `input_file_name`: Prompts the user to input a file name and validates the input.
   - `input_key`: Prompts the user to input a four-digit key and validates the input.

5. **Key Extraction Function (`extract_key`)**:
   - Extracts individual digits from the four-digit key for use in encryption/decryption.

6. **Encryption/Decryption Function (`encrypt_decrypt_file`)**:
   - Handles the encryption and decryption process based on the provided key.
   - Creates new files for encrypted or decrypted content.

7. **Database Functions**:
   - `store_record`: Stores or updates the record of encrypted files and keys in the database.
   - `check_record`: Checks the record to validate the key during decryption.

## Usage Instructions

1. **Compile the Program**:
   ```bash
   gcc -o file_encryption_system file_encryption_system.c

2. **Run the Program**:
   ```bash
   ./file_encryption_system

## Main Menu:

Choose the desired task:
1. File Encryption
2. File Decryption
3. Exit

### File Encryption:

- Enter the name of the text file to be encrypted.
- Set a four-digit encryption key (must be >= 1000).
- The encrypted file will be created in the same location with `_encrypted` suffix.

### File Decryption:

- Enter the name of the encrypted text file.
- Enter the four-digit key used during encryption.
- The decrypted file will be created in the same location with `_decrypted` suffix.

### Exit:

Choose option 3 to exit the program.

## Notes

- Ensure that the original text file exists in the same directory as the program.
- Remember the encryption key used, as it is required for decryption.
- The system handles basic validation of inputs, such as file existence and key format.

## Future Enhancements

- Add support for encrypting/decrypting other file types.
- Improve error handling and user feedback.
- Implement a more secure encryption algorithm.
- Add a graphical user interface (GUI) for better user experience.

This project was created by Luv Valecha as a demonstration of file encryption and decryption in C. Thank you for using this file encryption system!

