#include "calculator.h"

/* Function prototypes */
/* Feel free to add your own helper functions */
void process_directory(const char *dir_path);
int count_files_in_directory(const char *dir_path);

int main(int argc, char *argv[]) {
    /* TODO: Task 1 - Argument parsing */
    //Joseline's code
    if (argc != 2) {
        fprintf(stderr, "Usage: %s PATH_TO_DIR\n", argv[0]);
        exit(1);
    }

    const char *dir_path = argv[1];
    /* TODO: Get the path to the directory from command line options */ 

    DIR *dir = opendir(dir_path);
    if (dir==NULL){
        printf("ERROR %s directory does not exist \n");
        return -1;
    }
    closedir(dir);
    /* TODO: Process the directory */
    process_directory(dir_path);

    return 0;
}



void process_directory(const char *dir_path) {
/* TODO: Task 1 - Directory handling */
//Joseline's code
/* Open directory */
    struct dirent *entry;
    DIR *dir = opendir(dir_path);
    if (dir==NULL){
        printf("ERROR opening directory\n");
        return ;
    }

    //printf("Files in directory '%s':\n", dir_path);

//Peytons code
//First count files so we can create pid array
    int num_files = count_files_in_directory(dir_path);
    if (num_files == 0) {
        closedir(dir);
        return;
    }

    pid_t pids[num_files];
    int file_index = 0;

// Reset directory stream so we can read files again
    rewinddir(dir);


//Joseline code
    while((entry = readdir(dir)) != NULL) {
        if((strcmp(entry->d_name, ".") == 0) || (strcmp(entry->d_name, "..") == 0))
            continue;
//Peyton's Code
        char filepath[1024];
        snprintf(filepath, sizeof(filepath), "%s/%s", dir_path, entry->d_name);

        pid_t pid = fork();
        if (pid < 0) {
            perror("fork");
            exit(1);
        } else if (pid == 0) {
            // Child process exec's child program
            execl("./child", "child", filepath, NULL);
            perror("execl");  // exec only returns on error
            exit(1);
        } else {
            // Parent saves child pid
            pids[file_index++] = pid;
        }
    }
    closedir(dir);

    // Wait for all children to finish
    for (int i = 0; i < file_index; i++) {
        int status;
        waitpid(pids[i], &status, 0);
    }

/* Count files first to allocate memory */
//int num_files = count_files_in_directory(dir_path);

/* TODO: Allocate memory for results */

/* Phase 2: Create pipes for communication */
/* TODO: Task 4 - Create pipes here */

/* Read directory entries */

/* TODO: Task 2 - Wait for all child processes to complete */

/* TODO: Close directory here */

/* Calculate and print final results */

/* TODO: Remember to deallocate any memory */
}

int count_files_in_directory(const char *dir_path) {
    int count = 0;
//Peyton's code
    struct dirent *entry;
    DIR *dir = opendir(dir_path);
    if (dir == NULL) {
        perror("opendir");
        return 0;
    }

    while ((entry = readdir(dir)) != NULL) {
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0)
            continue;
        count++;
    }

    closedir(dir);
    return count;
}

