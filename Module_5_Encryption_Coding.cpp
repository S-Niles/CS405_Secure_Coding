// Encryption.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <cassert>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <ctime>

// Encrypts or decrypts the input string using XOR encryption with the provided key
std::string encrypt_decrypt(const std::string& source, const std::string& key) {
    const auto key_length = key.length();
    const auto source_length = source.length();

    assert(key_length > 0);
    assert(source_length > 0);

    std::string output = source;

    // Perform XOR operation for each character in the source string with the corresponding key character
    for (size_t i = 0; i < source_length; ++i) {
        output[i] = source[i] ^ key[i % key_length]; // Use modulo operation to loop over key characters
    }

    assert(output.length() == source_length);
    return output;
}

// Reads the entire contents of a file into a string
std::string read_file(const std::string& filename) {
    std::ifstream file(filename);
    std::string file_text, line;

    // Check if file is opened successfully
    if (file.is_open()) {
        while (getline(file, line)) { // Read file line by line
            file_text += line + "\n"; // Append each line to the file_text string
        }
        file.close(); // Close the file after reading
    }
    else {
        std::cerr << "Unable to open file: " << filename << std::endl;
    }

    return file_text;
}

std::string get_student_name(const std::string& string_data)
{
  std::string student_name;

  // find the first newline
  size_t pos = string_data.find('\n');
  // did we find a newline
  if (pos != std::string::npos)
  { // we did, so copy that substring as the student name
    student_name = string_data.substr(0, pos);
  }

  return student_name;
}

// Saves data to a file with the specified format
void save_data_file(const std::string& filename, const std::string& student_name, const std::string& key, const std::string& data) {
    std::ofstream file(filename);

    // Check if file is opened successfully
    if (file.is_open()) {
        // Get current time
        std::time_t t = std::time(nullptr);
        std::tm tm;

        // Securely convert time_t to tm struct using localtime_s 
        localtime_s(&tm, &t);

        // Use stringstream to format the date as yyyy-mm-dd
        std::ostringstream oss;
        oss << std::put_time(&tm, "%Y-%m-%d");
        std::string timestamp = oss.str();

        file << student_name << "\n" << timestamp << "\n" << key << "\n" << data;

        // Close the file after writing
        file.close();
    }
    else {
        // Output an error message if the file cannot be opened
        std::cerr << "Unable to open file for writing: " << filename << std::endl;
    }
}


int main() {
    std::cout << "Encryption Decryption Test!" << std::endl;

    const std::string file_name = "inputdatafile.txt";
    const std::string encrypted_file_name = "encrypteddatafile.txt";
    const std::string decrypted_file_name = "decrypteddatafile.txt";
    const std::string key = "password";

    // Read the original data from the file
    const std::string source_string = read_file(file_name);
    // Extract the student name from the data
    const std::string student_name = source_string.substr(0, source_string.find('\n'));

    // Encrypt the source string
    const std::string encrypted_string = encrypt_decrypt(source_string, key);
    // Save the encrypted data to a file
    save_data_file(encrypted_file_name, student_name, key, encrypted_string);

    // Decrypt the encrypted string
    const std::string decrypted_string = encrypt_decrypt(encrypted_string, key);
    // Save the decrypted data to a file
    save_data_file(decrypted_file_name, student_name, key, decrypted_string);

    std::cout << "Read File: " << file_name << " - Encrypted To: " << encrypted_file_name << " - Decrypted To: " << decrypted_file_name << std::endl;

    return 0;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu
