#include "calculator.h"

/* Function prototypes */
/* Feel free to add your own helper functions */
void process_directory(const char *dir_path);
int count_files_in_directory(const char *dir_path);

int main(int argc, char *argv[]) {
    /* TODO: Task 1 - Argument parsing */
    if (argc != 2) {
        fprintf(stderr, "Usage: %s PATH_TO_DIR\n", argv[0]);
        exit(1);
    }
    
    const char *dir_path = argv[1];
    /* TODO: Get the path to the directory from command line options */ 
    DIR *dir = opendir(dir_path);
    if (dir==NULL){
        printf("ERROR %S directory does not exist /n");
        return -1;
    }
    closedir(dir);
    /* TODO: Process the directory */
    process_directory(dir_path);
    
    return 0;
}

void process_directory(const char *dir_path) {
    /* TODO: Task 1 - Directory handling */
        
    /* Open directory */
    struct dirent *entry;
    DIR *dir = opendir(dir_path);
    if (dir==NULL){
        printf("ERROR opening directory /n");
        return ;
    }

    printf("Files in directory '%s':\n", dir_path);

    while((entry = readdir(dir)) != NULL) {
        if((strcmp(entry->d_name, ".") == 0) || (strcmp(entry->d_name, "..") == 0))
            continue;
        
        
    }
    closedir(dir);
        
    /* Count files first to allocate memory */
    int num_files = count_files_in_directory(dir_path);
        
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

    return count;
}

