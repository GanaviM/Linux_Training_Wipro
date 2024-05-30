#include <stdio.h>

int main() {
  struct data {
    int number;
    char name[20];
  };

  struct data data_to_write = {10, "Example Data"};
  struct data data_to_read;
  FILE *fp;

  // Open the file "my_data.bin" in binary write mode
  fp = fopen("my_data.bin", "wb");

  // Check if opening the file was successful
  if (fp == NULL) {
    perror("fopen (write)");
    return 1;
  } 

  // Write data to the file
  fwrite(&data_to_write, sizeof(data_to_write), 1, fp);

  if (ferror(fp)) {
    perror("fwrite");
    fclose(fp);
    return 1;
  }

  printf("Successfully wrote data to the file.\n");

  // Close the file for writing
  fclose(fp);

  // Open the file again in binary read mode
  fp = fopen("my_data.bin", "rb");

  // Check if opening the file was successful
  if (fp == NULL) {
    perror("fopen (read)");
    return 1;
  }

  // Read data from the file
  fread(&data_to_read, sizeof(data_to_read), 1, fp);
 
  if (ferror(fp)) {
    perror("fread");
    fclose(fp);
    return 1;
  }

  // Print the read data
  printf("Read data from the file:\n");
  printf("Number: %d\n", data_to_read.number);
  printf("Name: %s\n", data_to_read.name);

  // Close the file
  fclose(fp);

  return 0;
}
