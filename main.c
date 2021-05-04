#include <stdio.h>
#include <stdlib.h>
#define MAXSIZE 10

// global variables
int tick = 0;
int capture_process = 0;										// Detect whether process is assigned or not.
int capture_burst = 0;
int pointProcess = 0;											// Pointing current process
int index = 0;
int compare_index = -1;											// index��


typedef struct Process {
	int p_id;
	int p_arrival;
	int p_burst;
	int p_allocated;
	int p_finish;
	int p_used;													// Process ��� ����: ������(-1), �����(1)
	int p_remainBurst;											// SRTF, RR�� ����� ���� bursttime����� ����
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
	}Priority;
}readyQueue;


int isEmpty(readyQueue* _Q) {
	if (_Q->method == 1) {
		return (_Q->Normal.front == _Q->Normal.rear);
	}
	else if (_Q->method == 2) {
		return (_Q->Priority.front == _Q->Priority.rear);
	}
	else if (_Q->method == 3) {
		return (_Q->Priority.front == _Q->Priority.rear);
	}
	else {
		return (_Q->Priority.front == _Q->Priority.rear); // �ӽ�
	}
}

int isFull(readyQueue* _Q) {
	if (_Q->method == 1) {
		return (_Q->capacity == MAXSIZE);
	}
	else if (_Q->method == 2) {
		return (_Q->capacity == MAXSIZE);
	}
	else if (_Q->method == 3) {
		return (_Q->capacity == MAXSIZE);
	}
	else {
		return 1; // (_Q.Priority.front == _Q.Priority.rear); // �ӽ�
	}
}


void initQueue(readyQueue* _Q) {
	capture_process = 0;										// Initialize global variable (capture_process): FALSE.
	_Q->capacity = 0;

	if (_Q->method == 1) {
		_Q->Normal.front = 0;
		_Q->Normal.rear = 0;
	}
	else if (_Q->method == 2) {
		_Q->Priority.front = 0;
		_Q->Priority.rear = 0;
	}
	else if (_Q->method == 3) {
		_Q->Priority.front = 0;
		_Q->Priority.rear = 0;
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
		if (isFull(_Q)) {
			printf("d\n", "Error: FULL!");
			return;
		}
		_Q->Priority.queue[_Q->Priority.rear] = _P;
		_Q->Priority.rear++;
		_Q->capacity++;
	}
	else if (_Q->method == 3) {
		if (isFull(_Q)) {
			printf("d\n", "Error: FULL!");
			return;
		}
		_Q->Priority.queue[_Q->Priority.rear] = _P;
		_Q->Priority.rear++;
		_Q->capacity++;
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
		if (isEmpty(_Q)) {
			printf("d\n", "Error: EMPTY!");
			exit(1);
		}
		Process temp = _Q->Priority.queue[_Q->Priority.front];
		_Q->capacity--;
		_Q->Priority.front++;
		return temp;
	}
	else if (_Q->method == 3) {
		if (isEmpty(_Q)) {
			printf("d\n", "Error: EMPTY!");
			exit(1);
		}
		Process temp = _Q->Priority.queue[_Q->Priority.front];
		_Q->capacity--;
		_Q->Priority.front++;
		return temp;
	}
	else {
		//
	}
}


struct readyQueue Scheduler;									// Main Scheduler
Process temp;													// Variable for contiaining process in ready queue.

int pickProcess(readyQueue* _Q, int _tick) {
	int burst = 1000;
	int result = -1;
	for (int i = 0; i < _Q->capacity; i++) {
		if (_Q->Priority.queue[i].p_used == -1) {				// ������ ���μ����� ������ �������� ���
			//if ((_Q->Priority.queue[i].p_arrival <= _tick) && (_Q->Priority.queue[i].p_burst <= burst))
			if (_Q->Priority.queue[i].p_arrival <= _tick) {
				if (_Q->Priority.queue[i].p_burst < burst) {
					burst = _Q->Priority.queue[i].p_burst;
					result = i;
				}
				else {
					continue;
				}
			}
			else {
				continue;
			}
		}
		else {													// ������ ���μ����� �̹� ���� ���
			continue;
		}
	}
	return result;
}


int monitProcess(readyQueue* _Q, int _tick) {
	int burst = 1000;
	int result = -1;
	for (int i = 0; i < _Q->capacity; i++) {
		if (_Q->Priority.queue[i].p_used != 1) {				// �ش� ���μ����� �����(-1), �����(0), �����(1), �� ������ ���� ���� ã�´�.
			if (_Q->Priority.queue[i].p_arrival <= _tick) {
				if (_Q->Priority.queue[i].p_remainBurst < burst) {
					burst = _Q->Priority.queue[i].p_remainBurst;
					result = i;
				}
				else {
					continue;
				}
			}
			else {
				continue;
			}
		}
		else {
			continue;
		}
	}
	return result;
}

void set_schedule(int method) {
	if (method == 1) {
		printf("Scheduling method:  FCFS: First Come First Served (Non-preemptive) \n\n");
		Scheduler.method = 1;
		initQueue(&Scheduler);
	}
	else if (method == 2) {
		printf("Scheduling method: SJF: Shortest Job First (Non-preemptive) \n\n");
		Scheduler.method = 2;
		initQueue(&Scheduler);
	}
	else if (method == 3) {
		printf("Scheduling method: SRTF: Shortest Remaining Time First (Preemptive) \n\n");
		Scheduler.method = 3;
		initQueue(&Scheduler);
	}
	else if (method == 4) {
		printf("Scheduling method: RR: Round Robin (Preemptive) \n\n");
		Scheduler.method = 4;
		initQueue(&Scheduler);
	}
	else {
		printf("Error: Method number is incorrect!\n");
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
	//printf("%d\n", count);									// count ��� Ȯ�ο�
	for (int i = 0; i < count; i++) {
		fscanf(file, "%d %d %d", &p_id, &p_arrival, &p_burst);

		p_element.p_id = p_id;
		p_element.p_arrival = p_arrival;
		p_element.p_burst = p_burst;
		p_element.p_allocated = -1;
		p_element.p_finish = -1;
		p_element.p_used = -1;
		p_element.p_remainBurst = p_burst;

		enQueue(&Scheduler, p_element);                          // ���� &���ؼ� ����������!!
		//printf("%d %d %d\n", p_id, p_arrival, p_burst);
	}
	fclose(file);



	// ���� ��� Ȯ�ο뵵
	/*
	for (int j = 0; j < count; j++) {
		Process print = Scheduler.Normal.queue[j];
		printf("%d %d %d %d %d\n", print.p_id, print.p_arrival, print.p_burst, print.p_allocated, print.p_finish);
	}
	*/
}


int do_schedule(int tick)
/*
	tick�� ���������� 0���� ����
	�����ٷ� time�� tick�� ���� �귯����
	tick 0�̴�.
	if p1�� arrival time�� 0�̴�.

	tick 1�̴�
	if p1�� arrival time�� tick���� �۰�, burst time�� ���Ҵ� -> burst time�� 1�� ����
	burst time�� 0�̵Ǹ� dequeue�Ѵ�
	--> �Խ��� ���� ���� ����ü�� ���� �����س��ٰ� print performance�� ��߰ڴ�...

	���� capacity�� 0�� �Ǹ� return 0
	�� �ܿ��� 1

*/
{
	int numProcess = Scheduler.capacity;				// the number of process in ready queue.


	if (Scheduler.method == 1) {
		// �����ٷ��� ����� ť�� arrival time�� tick�� ���Ͽ� Ȯ������
		for (int i = 0; i < numProcess; i++) {
			if (Scheduler.Normal.queue[i].p_arrival == tick) {
				printf("[tick: %d] New Process (ID: %d) newly joins to ready queue\n", tick, Scheduler.Normal.queue[i].p_id);
			}
		}

		// FCFS
		if (capture_process == 0) {							// ���� ������ ����
			if (pointProcess < numProcess) {				// �����ٷ����� ���μ����� �����ִ�.
				temp = Scheduler.Normal.queue[pointProcess];// �ӽ� ���μ��� ����
				if (temp.p_arrival <= tick) {				// �ش� ���μ����� arrival�� tick���� ������
					capture_process = 1;					// ���μ��� ��Ҵ�.
					Scheduler.Normal.queue[pointProcess].p_allocated = tick;	// cpu �Ҵ� �ð� �Է�
					capture_burst = temp.p_burst;			// burst ����
					printf("[tick: %d] Dispatch to Process (ID: %d)\n", tick, temp.p_id);
				}
				else {
					return 1;								// arrival�� ��ٸ���.
				}
			}
			else {											// �����ٷ����� ���μ����� �������� �ʴ�.
				printf("[tick: %d] All processes are terminated.\n", tick);
				return 0;									// res�� 0���� ����鼭 ����.
			}
		}
		else {												// ���� ������ �ְ� allocated �� �����̴�.
			capture_burst--;										// burst time�� 1���δ�.
			if (capture_burst > 0) {						// ���� burst time�� �����Ǹ�
				return 1;
			}
			else {											// ���� burst time�� �����ִ� ���.
				Scheduler.Normal.queue[pointProcess].p_finish = tick;						// process�� finish �ð��� ����.
				pointProcess++;								// ����Ű�� ���μ����� �̵�.
				capture_process = 0;						// ���� ����ִ� ���μ��� ������.
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
		for (int i = 0; i < numProcess; i++) {
			if (Scheduler.Priority.queue[i].p_arrival == tick) {
				printf("[tick: %d] New Process (ID: %d) newly joins to ready queue\n", tick, Scheduler.Priority.queue[i].p_id);
			}
		}

		if (capture_process == 0) {
			if (pointProcess < numProcess) {									// pointProcess�� �����ٷ� ���μ��� ��� ���� üũ
				index = pickProcess(&Scheduler, tick);						// ������ ���μ����� ã��
				if (index != -1) {												// ������ ���μ����� ã�� ���
					temp = Scheduler.Priority.queue[index];
					capture_process = 1;
					Scheduler.Priority.queue[index].p_allocated = tick;
					capture_burst = temp.p_burst;
					printf("[tick: %d] Dispatch to Process (ID: %d)\n", tick, temp.p_id);
				}
				else {															// ������ ���μ����� ã�� ���� ���
					return 1;													// �ð��� ������.
				}
			}
			else {																// �����ٷ� ���μ��� �� ���.
				printf("[tick: %d] All processes are terminated.\n", tick);
				return 0;														// res�� 0���� ����鼭 ����.
			}
		}
		else {
			capture_burst--;
			if (capture_burst > 0) {
				return 1;
			}
			else {
				Scheduler.Priority.queue[index].p_finish = tick;
				Scheduler.Priority.queue[index].p_used = 1;						// �ش� ���μ����� �� ����ߴٴ� ���� ǥ��
				pointProcess++;													// ����� ���μ����� ������ ǥ��
				capture_process = 0;
				if (pointProcess < numProcess) {								// ��� ���μ����� �� ������� ���� ���
					index = pickProcess(&Scheduler, tick);						// ������ ���μ����� ã��
					if (index != -1) {												// ������ ���μ����� ã�� ���
						temp = Scheduler.Priority.queue[index];
						capture_process = 1;
						Scheduler.Priority.queue[index].p_allocated = tick;
						capture_burst = temp.p_burst;
						printf("[tick: %d] Dispatch to Process (ID: %d)\n", tick, temp.p_id);
					}
					else {															// ������ ���μ����� ã�� ���� ���
						return 1;													// �ð��� ������.
					}
				}
				else {															// ��� ���μ����� �� ����� ���
					printf("[tick: %d] All processes are terminated.\n", tick);
					return 0;														// res�� 0���� ����鼭 ����.
				}
			}
		}
	}
	else if (Scheduler.method == 3) {					//SRTF
		int dispatch = 0;															// dispatch �ƴϸ�(0), ������(1)
		for (int i = 0; i < numProcess; i++) {
			if (Scheduler.Priority.queue[i].p_arrival == tick) {
				printf("[tick: %d] New Process (ID: %d) newly joins to ready queue\n", tick, Scheduler.Priority.queue[i].p_id);
			}
		}

		if (pointProcess < numProcess) {												// �����ٷ��� ���μ����� �����ִ�
			index = monitProcess(&Scheduler, tick);										// ������ ���μ����� ã�´�.
			if (compare_index == -1) {													// �� index�� �ʱ�ȭ�� �Ǿ��ִ� ����
				compare_index = index;
			}
			else {																		// �� index�� �Ҵ�Ǿ��ִ� ����
				if (compare_index == index) {											// ���μ����� �ٲ��� �ʾҴ�.
					dispatch = 0;
				}
				else {																	// ���μ����� �ٲ����.
					dispatch = 1;
					compare_index = index;												// �ٲ������ �״��� �񱳸� ���� ��������
				}
			}

			if (index != -1) {															// ������ ���μ����� ã�� ���
				temp = Scheduler.Priority.queue[index];
				if (temp.p_used == -1) {												// ó�� ���õ� ���μ����� ���
					Scheduler.Priority.queue[index].p_used = 0;							// ����� ���۵Ǿ����� ǥ��
					Scheduler.Priority.queue[index].p_allocated = tick;					// �Ҵ�� �ð��� ǥ��
					Scheduler.Priority.queue[index].p_remainBurst--;					// ���� burst�ð��� �ٿ��ֱ�
					printf("[tick: %d] Dispatch to Process (ID: %d)\n", tick, temp.p_id);// dispatch
					if (Scheduler.Priority.queue[index].p_remainBurst > 0) {			// ���� burst�ð��� ������
						return 1;
					}
					else {																// ���� burst�ð��� ������
						Scheduler.Priority.queue[index].p_used = 1;						// �ش� ���μ����� �� ���Ǿ����� ǥ��
						Scheduler.Priority.queue[index].p_finish = tick + 1;				// ����� �ð� �Ҵ�
						pointProcess++;													// ���� ���μ��� ���� ����
						return 1;
					}
				}
				else {																	// �������� ���� ���μ����� ���
					if (dispatch == 1) {
						printf("[tick: %d] Dispatch to Process (ID: %d)\n", tick, temp.p_id);// dispatch
					}
					Scheduler.Priority.queue[index].p_remainBurst--;
					if (Scheduler.Priority.queue[index].p_remainBurst > 0) {			// ���� burst�ð��� ������
						return 1;
					}
					else {																// ���� burst�ð��� ������
						Scheduler.Priority.queue[index].p_used = 1;						// �ش� ���μ����� �� ���Ǿ����� ǥ��
						Scheduler.Priority.queue[index].p_finish = tick + 1;				// ����� �ð� �Ҵ�
						pointProcess++;													// ���� ���μ��� ���� ����
						return 1;
					}
				}
			}
			else {																		// ������ ���μ����� ã�� ���� ���
				return 1;
			}
		}
		else {																			// �����ٷ��� ���μ����� �� ���
			printf("[tick: %d] All processes are terminated.\n", tick);
			return 0;
		}



	}
	else {												//RR
		return 1; //�ӽ�
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
	printf("\n%s\n", "=================================================================================================================");
	printf("%10s  %10s  %10s  %10s  %20s  %18s  %18s\n", "PID", "arrival", "finish", "burst", "Turn around Time", "Wating time", "Response time");
	printf("%s\n", "=================================================================================================================");
	for (int j = 0; j < numProcess; j++) {
		Process print;
		if (Scheduler.method == 1) {
			print = Scheduler.Normal.queue[j];
		}
		else if (Scheduler.method == 2) {
			print = Scheduler.Priority.queue[j];
		}
		else if (Scheduler.method == 3) {
			print = Scheduler.Priority.queue[j];
		}
		else {
			print = Scheduler.Priority.queue[j];
		}
		int TAT = print.p_finish - print.p_arrival;
		int WT = print.p_finish - print.p_arrival - print.p_burst;
		int RT = print.p_allocated - print.p_arrival;
		totalTAT = totalTAT + TAT;
		totalWT = totalWT + WT;
		totalRT = totalRT + RT;
		printf("%10d  %10d  %10d  %10d  %20d  %18d  %18d\n", print.p_id, print.p_arrival, print.p_finish, print.p_burst, TAT, WT, RT);
	}
	printf("%s\n", "-----------------------------------------------------------------------------------------------------------------");
	printf("%10s  %30s  %20f %18f %18f\n", "Average", " ", totalTAT / numProcess, totalWT / numProcess, totalRT / numProcess);
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


	while (1) {
		int res = do_schedule(tick);
		if (res == 0 || tick > 100) break;
		tick++;
	}
	// ���� Ȯ�ο�!! ��������!
	// ���̵� �����ð� ����ð� �Ҵ�ð� ����ð�

	for (int j = 0; j < 4; j++) {
		Process print = Scheduler.Priority.queue[j];
		printf("%d %d %d %d %d %d\n", print.p_id, print.p_arrival, print.p_burst, print.p_allocated, print.p_finish, print.p_used);
	}



	print_performance();

	return 0;
}