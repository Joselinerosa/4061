#include "calculator.h"

/* Function prototypes */
/* Feel free to add your own helper functions */
void process_file(const char *file_path, int pipe_fd);
void write_results_to_file(const char *original_path, int count, long sum);
void send_results_via_pipe(int pipe_fd, int count, long sum);

//for task 4
typedef struct {
    int count;
    long sum;
    char filename[256];
}PipeMessage;

const char *file_path= NULL;

int main(int argc, char *argv[]) {
    /* TODO: Task 3 - Receive file path from command line */
    /* Phase 1: Only file path is needed */
    /* Phase 2: Both file path and pipe fd are needed */
    if (argc < 2 || argc > 3) {
        fprintf(stderr, "Usage: %s FILE_PATH [PIPE_FD]\n", argv[0]);
        exit(1);
    }
   
    //const char *file_path = argv[1];
    file_path= argv[1]; //change to global
    int pipe_fd = -1;
    /* TODO: Get path to the file */ 

    /* TODO: Get the file descriptor from the command line in Phase 2 */
    if (argc==3){
        pipe_fd = atoi(argv[2]);
        if (pipe_fd < 0) {
            fprintf(stderr, "Invalid pipe file descriptor: %d\n", pipe_fd);
            exit(1);
        }
    } else {
        /* In Phase 1, we don't use the pipe */
        pipe_fd = -1; // No pipe in Phase 1
    }

    /* Process the file */
    process_file(file_path, pipe_fd);
    
    return 0;
}

void process_file(const char *file_path, int pipe_fd){
    int count=0;
    long sum=0;
    int num=0;
    /* TODO: Task 3 - Open file and extract numbers */
    /* Read integers from file, one per line */
    FILE *file =fopen(file_path, "r");
    if (file==NULL){
        perror("ERROR opening the file");
        exit(1);
    }

    while(fscanf(file, "%d", &num)==1){ //reads and writes it back to sum
        count++;
        sum+=num;
    }  
    
    /* Remember to close the file */

    fclose(file);
    
    /* Phase 1: Write results to .results file */
    if (pipe_fd==-1) {
        /* In Phase 1, we only write to the results file */
        write_results_to_file(file_path, count, sum);
    } else{
        /* In Phase 2, we write to the results file and send via pipe */
        send_results_via_pipe(pipe_fd, count, sum);
    }
    
    
    
    /* Phase 2: Send results via pipe */
    /* TODO: Task 4 - Implement pipe communication */
    /* send_results_via_pipe(pipe_fd, count, sum); */
}

void write_results_to_file(const char *original_path, int count, long sum) {
    /* TODO: Create .results filename */
    
char results_path[1024]; //buffer// Create .results filename
snprintf(results_path, sizeof(results_path), "%s.results", original_path);
    
    
    /* TODO: Write count and sum to results file */
    FILE *results= fopen(results_path, "w");
        if (results == NULL){
            perror("Error- results");
            exit(1);
        }
    fprintf(results, "%d\n%ld\n", count, sum);
    
    /* Remember to close files and release resources */
    fclose(results);
}

void send_results_via_pipe(int pipe_fd, int count, long sum){
    /* TODO: Task 4 - Send PipeMessage through pipe */
    /* This function will be implemented in Phase 2 */
    /* TODO: Write message to pipe */
    /* Hint: The pipe file descriptor should be passed somehow */

    PipeMessage msg; //need to create a MESSAGE to send through the pipe

    //store the number of integers and the total sum 
    msg.count = count; 
    msg.sum = sum;

    const char *filename = strrchr(file_path, '/'); //get file name from the file path, just want the file name NOT the whole path
    
    if (filename !=NULL){
        filename= filename +1; // If '/' was found, move one characterr forward to skip it 
    }else {
        filename = file_path; //if '/' was NOT found, the path is already just the file name
}
strncpy(msg.filename, filename, sizeof(msg.filename)); //COPY the file name into the message struct
msg.filename[sizeof(msg.filename) -1]='\0'; //need to make sure the string is properly NULL-TERMINATED

if (write(pipe_fd, &msg, sizeof(PipeMessage))==-1){ //WRITE the messgae into the pipe 
    perror("write"); //print error if writing FAILS 
    exit(1);
}
close(pipe_fd); //close the pipe file descriptor after sending 
}
