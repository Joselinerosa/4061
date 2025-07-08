# Programming Assignment 1: Integer Sum and Average Calculation

## Team Information
1. Team members: Joseline Rosa & Peyton Tregembo
2. x500: Rosa0168 & Trege006
3. Division of tasks:
Task 1: Joseline
Task 2: Peyton
Task 3: Joseline & Peyton (mostly Joseline)
README.md: Peyton & Joseline (mostly Peyton)
5. Lab machine used: SSH trege006@csel-khl1260-17.cselabs.umn.edu 

## Design Specifications
Design meets requriments of directory traversal, process managment, file reading, and storing results. The implementation consists of two edited files (calculator.c- the main process AND child.c- the child process). The main process is responsible for parsing the directory, forking child processes and execution. The child process is responsible for reading the integers from the files,  computing the sum and count, and then writing those results to .results files. 
Used system calls reviewed in lectures to maintain compatibility with CSE lab Linux machines. 

### Phase 1 Design
- Process creation strategy: the main process (calculator.c)- opens the provided directory and iterates through all the entries. For each file, it uses fork() to create a child process. The child process immediatley calls execl() to run the separate child program (child.c) and passes the full file path as an argument. It skips "." and ".." entries.
  
- File handling approach: In child.c, the file is opened using fopen() in READ mode, integers are read line by line using fscanf(). We keep runnning count and sum of all integers and then after erading, the file is closed to avoid memory leaks.
  
- Results storage method: Each child process creates a .results file by appending the .results extention to the original file name. The .results file is written using fprintf() and includes the total number of intergers (on line 1), and the sum of the integers (on line 2). 

### Phase 2 Design
- Pipe communication strategy:
- Data transmission format:
- Synchronization approach:

## Challenges Faced
1.) Figuring out how to use GitHub 
2.) Debugging .results file outputs to make sure formatting was correct
3.) Figuring out the correct syntax for some of the functions

## AI Tools Usage
Peyton: I used AI to help fix my spacing for calculator.c

Joseline: I used AI to help with my syntax in child.c specifically task 3


## Additional Notes
[TODO: Any other information for the TA]
