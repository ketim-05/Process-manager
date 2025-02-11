This project is a simple command-line tool for monitoring and managing processes on a Unix-based system. It provides functionalities to list processes, monitor them in real-time, and manage processes by pausing, resuming, or terminating them.

Features
List Processes: Displays a list of all running processes with their PID, name, CPU usage, and memory usage.

Monitor Processes: Monitors processes in real-time with a user-defined interval.

Pause Process: Pauses a specified process using its PID.

Resume Process: Resumes a paused process using its PID.

Terminate Process: Terminates a specified process using its PID.

Usage
List Processes: Select option 1 to list all running processes.

Monitor Processes: Select option 2 to monitor processes in real-time. Enter the monitoring interval in seconds.

Pause Process: Select option 3 and enter the PID of the process you want to pause.

Resume Process: Select option 4 and enter the PID of the process you want to resume.

Terminate Process: Select option 5 and enter the PID of the process you want to terminate.

Exit: Select option 6 to exit the program.

Key Functions
list_processes(): Lists all running processes.

kbhit(): Detects keypress for interactive monitoring.

manage_process(pid_t pid, const char *action): Manages processes based on the specified action (pause, resume, terminate).

monitor_processes(int interval): Monitors processes in real-time with a specified interval.

process_action(const char *action): Handles process actions with an option to return to the main menu.
