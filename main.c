#include <stdio.h>
#include <stdlib.h>
#define MAXSIZE 10

// global variables
int tick = 0;
int capture_process = 0;										// Detect whether process is assigned or not.
int capture_burst = 0;
int pointProcess = 0;											// Pointing current process



typedef struct Process {
	int p_id;
	int p_arrival;
	int p_burst;
	int p_allocated;
	int p_finish;
}Process;

typedef struct readyQueue {
	int method;
	int capacity;
	
	struct NormalType {
		struct Process queue[MAXSIZE];
		int front, rear;
	}Normal;

	struct CircularType {
		struct Process queue[MAXSIZE];
		int front, rear;
	}Circular;

	struct PriorityType {
		struct Process queue[MAXSIZE];
		int front, rear;
		int prior;
	}Priority;
}readyQueue;


int isEmpty(readyQueue* _Q) {
	if (_Q->method == 1) {
		return (_Q->Normal.front == _Q->Normal.rear);    // 임시
	}
	else if (_Q->method == 2) {
		return (_Q->Circular.front == _Q->Circular.rear); // 임시
	}
	else if (_Q->method == 3) {
		return (_Q->Priority.front == _Q->Priority.rear); // 임시
	}
	else {
		return (_Q->Priority.front == _Q->Priority.rear); // 임시
	}
}

int isFull(readyQueue* _Q) {
	if (_Q->method == 1) {
		return (_Q->capacity == MAXSIZE);    // 임시
	}
	else if (_Q->method == 2) {
		return 1; //(_Q.Circular.front == _Q.Circular.rear); // 임시
	}
	else if (_Q->method == 3) {
		return 1; //(_Q.Priority.front == _Q.Priority.rear); // 임시
	}
	else {
		return 1; // (_Q.Priority.front == _Q.Priority.rear); // 임시
	}
}


void initQueue(readyQueue* _Q) {
	capture_process = 0;										// Initialize global variable (capture_process): FALSE.
	_Q->capacity = 0;										

	if (_Q->method == 1) {
		_Q->Normal.front = 0;
		_Q->Normal.front = 0;
	}
	else if (_Q->method == 2) {
		//
	}
	else if (_Q->method == 3) {
		//
	}
	else {
		//
	}
}


void enQueue(readyQueue* _Q, Process _P) {
	if (_Q->method == 1) {
		if (isFull(_Q)) {
			printf("d\n", "Error: FULL!");
			return;
		}
		_Q->Normal.queue[_Q->Normal.rear] = _P;
		_Q->Normal.rear++;
		_Q->capacity++;
	}
	else if (_Q->method == 2) {
		//
	}
	else if (_Q->method == 3) {
		//
	}
	else {
		//
	}
}


Process deQueue(readyQueue* _Q) {
	if (_Q->method == 1) {
		if (isEmpty(_Q)) {
			printf("d\n", "Error: EMPTY!");
			exit(1);
		}
		Process temp = _Q->Normal.queue[_Q->Normal.front];
		_Q->capacity--;
		_Q->Normal.front++;
		return temp;
	}
	else if (_Q->method == 2) {
		//
	}
	else if (_Q->method == 3) {
		//
	}
	else {
		//
	}
}


struct readyQueue Scheduler;									// Main Scheduler
Process temp;													// Variable for contiaining process in ready queue.


void set_schedule(int method) {
	if (method == 1) {
		printf("Scheduling method:  FCFS: First Come First Served (Non-preemptive) \n");
		Scheduler.method = 1;
		initQueue(&Scheduler);
	}
	else if (method == 2) {
		printf("Scheduling method: SJF: Shortest Job First (Non-preemptive) \n");
		Scheduler.method = 2;
		initQueue(&Scheduler);
	}
	else if (method == 3) {
		printf("Scheduling method: SRTF: Shortest Remaining Time First (Preemptive) \n");
		Scheduler.method = 3;
		initQueue(&Scheduler);
	}
	else if (method == 4) {
		printf("Scheduling method: RR: Round Robin (Preemptive) \n");
		Scheduler.method = 4;
		initQueue(&Scheduler);
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
	Process p_element;											// The process for containing information.

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

		p_element.p_id = p_id;
		p_element.p_arrival = p_arrival;
		p_element.p_burst = p_burst;
		p_element.p_allocated = -1;
		p_element.p_finish = -1;

		enQueue(&Scheduler, p_element);                          // 여기 &안해서 오류날수도!!
		//printf("%d %d %d\n", p_id, p_arrival, p_burst);
	}
	fclose(file);



	// 저장 출력 확인용도
	/*
	for (int j = 0; j < count; j++) {
		Process print = Scheduler.Normal.queue[j];
		printf("%d %d %d %d %d\n", print.p_id, print.p_arrival, print.p_burst, print.p_allocated, print.p_finish);
	}
	*/
}


int do_schedule(int tick)
/*
	tick은 전역변수로 0부터 시작
	스케줄러 time은 tick과 같이 흘러가지
	tick 0이다. 
	if p1의 arrival time이 0이다.
	
	tick 1이다
	if p1의 arrival time이 tick보다 작고, burst time이 남았다 -> burst time을 1씩 감소
	burst time이 0이되면 dequeue한다
	--> 게시판 전역 변수 구조체를 만들어서 저장해놨다가 print performance에 써야겠다...

	만약 capacity가 0이 되면 return 0
	그 외에는 1

*/
{
	

	//printf("[tick: %d] New Process (ID: %d) newly joins to ready queue", tick, temp.p_id);
	//printf("[tick: %d] Dispatch to Process (ID: %d)", tick, temp.p_id);
	//printf("[tick: %d] All processes are terminated.", tick);

	int numProcess = Scheduler.capacity;				// the number of process in ready queue.
	

	if (Scheduler.method == 1) {
		// 스케줄러에 저장된 큐의 arrival time을 tick과 비교하여 확인하자
		for (int i = 0; i < numProcess; i++) {
			if (Scheduler.Normal.queue[i].p_arrival == tick) {
				printf("[tick: %d] New Process (ID: %d) newly joins to ready queue\n", tick, Scheduler.Normal.queue[i].p_id);
			}
		}

		// FCFS
		if (capture_process == 0) {							// 지금 잡힌게 없다
			if (pointProcess < numProcess) {				// 스케줄러에는 프로세스가 남아있다.
				temp = Scheduler.Normal.queue[pointProcess];// 임시 프로세스 저장
				if (temp.p_arrival <= tick) {				// 해당 프로세스의 arrival이 tick보다 작으면
					capture_process = 1;					// 프로세스 잡았다.
					Scheduler.Normal.queue[pointProcess].p_allocated = tick;	// cpu 할당 시간 입력
					capture_burst = temp.p_burst;			// burst 복사
					printf("[tick: %d] Dispatch to Process (ID: %d)\n", tick, temp.p_id);
				}
				else {
					return 1;								// arrival을 기다린다.
				}
			}
			else {											// 스케줄러에는 프로세스가 남아있지 않다.
				printf("[tick: %d] All processes are terminated.\n", tick);
				return 0;									// res를 0으로 만들면서 종료.
			}
		}
		else {												// 지금 잡힌게 있고 allocated 된 상태이다.
			capture_burst--;										// burst time을 1줄인다.
			if (capture_burst > 0) {						// 만약 burst time이 소진되면
				return 1;
			}
			else {											// 만약 burst time이 남아있는 경우.
				Scheduler.Normal.queue[pointProcess].p_finish = tick;						// process의 finish 시간을 저장.
				pointProcess++;								// 가리키는 프로세스를 이동.
				capture_process = 0;						// 현재 잡고있는 프로세스 놓아줌.
				if (pointProcess < numProcess) {
					temp = Scheduler.Normal.queue[pointProcess];
					if (temp.p_arrival <= tick) {
						capture_process = 1;
						Scheduler.Normal.queue[pointProcess].p_allocated = tick;
						capture_burst = temp.p_burst;
						printf("[tick: %d] Dispatch to Process (ID: %d)\n", tick, temp.p_id);

					}
					else {
						return 1;
					}
				}
				else {
					printf("[tick: %d] All processes are terminated.\n", tick);
					return 0;
				}
				return 1;
			}
		}
	}
	else if (Scheduler.method == 2) {					//SJF
		return 1; //임시
	}
	else if (Scheduler.method == 3) {					//SRTF
		return 1; //임시
	}
	else {												//RR
		return 1; //임시
	}
}

/*
while(1){
		int res = do_schedule(tick);
		if (res == 0 || tick > 100) break;
		tick++;
	}
*/

void print_performance()
{
	int numProcess = Scheduler.capacity;
	double totalTAT = 0;
	double totalWT = 0;
	double totalRT = 0;
	printf("%s\n", "=================================================================================================================");
	printf("%10s  %10s  %10s  %10s  %20s  %18s  %18s\n", "PID", "arrival", "finish", "burst", "Turn around Time", "Wating time", "Response time");
	printf("%s\n", "=================================================================================================================");
	for (int j = 0; j < numProcess; j++) {
		Process print = Scheduler.Normal.queue[j];
		int TAT = print.p_finish - print.p_arrival;
		int WT = print.p_finish - print.p_arrival - print.p_burst;
		int RT = print.p_allocated - print.p_arrival;
		totalTAT = totalTAT + TAT;
		totalWT = totalWT + WT;
		totalRT = totalRT + RT;
		printf("%10d  %10d  %10d  %10d  %20d  %18d  %18d\n", print.p_id, print.p_arrival, print.p_finish, print.p_burst, TAT, WT, RT);
	}
	printf("%s\n", "-----------------------------------------------------------------------------------------------------------------");
	printf("%10s  %30s  %20f %18f %18f\n", "Average", " ", totalTAT/numProcess, totalWT/numProcess, totalRT/numProcess);
	printf("%s\n", "=================================================================================================================");

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


	while(1){
		int res = do_schedule(tick);
		if (res == 0 || tick > 100) break;
		tick++;
	}
	// 최종 확인용!! 지워야함!
	// 아이디 도착시간 실행시간 할당시간 종료시간
	/*
	for (int j = 0; j < 4; j++) {
		Process print = Scheduler.Normal.queue[j];
		printf("%d %d %d %d %d\n", print.p_id, print.p_arrival, print.p_burst, print.p_allocated, print.p_finish);
	}
	*/


	print_performance();
	
	return 0;
}