#include <stdio.h>
#include <stdlib.h>


typedef struct Process {
	int p_id;
	int p_arrival;
	int p_burst;
	int p_allocated;
};

typedef struct readyQueue {
	int method;
	struct Process* node;
};

// global variables
int tick = 0;
struct readyQueue Scheduler;

void set_schedule(int method) {
	if (method == 1) {
		printf("Scheduling method:  FCFS: First Come First Served (Non-preemptive) \n");
		Scheduler.method = 1;
	}
	else if (method == 2) {
		printf("Scheduling method: SJF: Shortest Job First (Non-preemptive) \n");
		Scheduler.method = 2;
	}
	else if (method == 3) {
		printf("Scheduling method: SRTF: Shortest Remaining Time First (Preemptive) \n");
		Scheduler.method = 3;
	}
	else if (method == 4) {
		printf("Scheduling method: RR: Round Robin (Preemptive) \n");
		Scheduler.method = 4;
	}
	else {
		printf("Error: Method number is incorrect!");
		Scheduler.method = -1;
		exit(1);
	}
}

void read_proc_list(const char* filename) {

	int count;													// The number of process in text file.
	int p_id;													// The id of process in text file.
	int p_arrival;												// The arrival time of process in text file.
	int p_burst;												// The burst time of process in text file.

	FILE* file = fopen(filename, "r");							// Open file
	if (file == NULL)											
	{
		printf("%s\n", "ERROR: Failed to read file");
		exit(1);
	}
	fscanf(file, "%d", &count);									
	printf("%d\n", count);
	for (int i = 0; i < count; i++) {
		fscanf(file, "%d %d %d", &p_id, &p_arrival, &p_burst);
		printf("%d %d %d\n", p_id, p_arrival, p_burst);
	}


	fclose(file);

}



int main(int argc, char* argv[])
{
	//char file_name[1024] = "proc_list.txt";
	//char file_name[1024] = "rr.txt";
	//int schedule_method = 4;

	char file_name[1024] = "";
	int schedule_method = -1;

	printf("Enter process file name:");
	scanf("%s", file_name);
	printf("Enter process scheduling mehtod \n");
	printf("1: FCFS: First Come First Served (Non-preemptive) \n");
	printf("2: SJF: Shortest Job First (Non-preemptive) \n");
	printf("3: SRTF: Shortest Remaining Time First (Preemptive) \n");
	printf("4: RR: Round Robin (Preemptive) \n");
	scanf("%d", &schedule_method);

	set_schedule(schedule_method);
	// set processes
	read_proc_list(file_name);

	/*
	while(1){
		int res = do_schedule(tick);
		if (res == 0 || tick > 100) break;
		tick++;
	}
	print_performance();
	*/
	return 0;

}