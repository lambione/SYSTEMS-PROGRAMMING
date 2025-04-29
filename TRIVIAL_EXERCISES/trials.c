#include <stdio.h>

int main(int argc, char *argv[]) {
    // Check if there are at least three command-line arguments
    if (argc >= 3) {
        // Print the value of the second command-line argument (index 2)
        printf("Parameter %s : %s\n", argv[1], argv[2]);
    } else {
        // Print an error message if there are not enough arguments
        printf("Error: Insufficient command-line arguments\n");
    }

    return 0;
}