
#include <stdio.h>    // For input/output functions like printf and scanf
#include <stdlib.h>   // For general utilities like system() and exit()
#include <string.h>   // For string manipulation functions like strcmp()
#include <signal.h>   // For handling signals like SIGTERM, SIGSTOP, SIGCONT
#include <unistd.h>   // For POSIX functions like sleep()
#include <sys/types.h> // For data types like pid_t
#include <termios.h>  // For non-blocking keypress detection
#include <fcntl.h>    // For file control to enable non-blocking mode

// Function to list processes using the ps command
void list_processes() {
    printf("%-10s %-25s %-10s %-10s\n", "PID", "Name", "CPU %", "Memory %");
    printf("------------------------------------------------------------\n");
    fflush(stdout);
    system("ps -eo pid,comm,%cpu,%mem --sort=-%cpu");
}

// Function to detect keypress
int kbhit() {
    struct termios oldt, newt;
    int ch;
    int oldf;

    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);

    oldf = fcntl(STDIN_FILENO, F_GETFL, 0);
    fcntl(STDIN_FILENO, F_SETFL, oldf | O_NONBLOCK);

    ch = getchar();

    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    fcntl(STDIN_FILENO, F_SETFL, oldf);

    if (ch != EOF) {
        ungetc(ch, stdin);
        return 1;
    }

    return 0;
}

// Function to manage a process based on the given action
void manage_process(pid_t pid, const char *action) {
    if (strcmp(action, "pause") == 0) {
        if (kill(pid, SIGSTOP) == 0) {
            printf("Process %d paused.\n", pid);
        } else {
            perror("Error pausing process");
        }
    } else if (strcmp(action, "resume") == 0) {
        if (kill(pid, SIGCONT) == 0) {
            printf("Process %d resumed.\n", pid);
        } else {
            perror("Error resuming process");
        }
    } else if (strcmp(action, "terminate") == 0) {
        if (kill(pid, SIGTERM) == 0) {
            printf("Process %d terminated.\n", pid);
        } else {
            perror("Error terminating process");
        }
    } else {
        printf("Invalid action. Use 'pause', 'resume', or 'terminate'.\n");
    }
}

// Function to monitor processes live
void monitor_processes(int interval) {
    while (1) {
        system("clear");
        list_processes();
        printf("\nPress 'q' to quit monitoring or 'm' to return to the main menu.\n");
        sleep(interval);

        if (kbhit()) {
            char ch = getchar();
            if (ch == 'q') {
                printf("Exiting live monitoring.\n");
                break;
            } else if (ch == 'm') {
                return;
            }
        }
    }
}

// Function to handle process actions with return to main menu
void process_action(const char *action) {
    while (1) {
        pid_t pid;
        printf("Enter PID to %s (or enter -1 to return to main menu): ", action);
        if (scanf("%d", &pid) != 1) {
            printf("Invalid PID.\n");
            while (getchar() != '\n');
            continue;
        }
        if (pid == -1) return;
        manage_process(pid, action);
    }
}

int main() {
    while (1) {
        printf("\nProcess Monitor and Manager\n");
        printf("---------------------------\n");
        printf("1. List processes\n");
        printf("2. Monitor processes (live)\n");
        printf("3. Pause a process\n");
        printf("4. Resume a process\n");
        printf("5. Terminate a process\n");
        printf("6. Exit\n");

        int choice;
        printf("\nEnter your choice: ");
        if (scanf("%d", &choice) != 1) {
            printf("Invalid input. Please enter a number.\n");
            while (getchar() != '\n');
            continue;
        }


switch (choice) {
            case 1:
                list_processes();
                break;
            case 2: {
                int interval;
                printf("Enter monitoring interval (seconds): ");
                if (scanf("%d", &interval) != 1 || interval <= 0) {
                    printf("Invalid input. Please enter a positive number.\n");
                    while (getchar() != '\n');
                    continue;
                }
                monitor_processes(interval);
                break;
            }
            case 3:
                process_action("pause");
                break;
            case 4:
                process_action("resume");
                break;
            case 5:
                process_action("terminate");
                break;
            case 6:
                printf("Exiting program.\n");
                return 0;
            default:
                printf("Invalid choice. Please select a valid option.\n");
                break;
        }
    }

    return 0;
}



