#include "schedule.h"


// process node, ready queue�� ����



void read_proc_list(const char* file_name)
/*
	fn: read_proc_list
	desc: read process file list
	param
	file_name: process list name
*/
{
	// read_proc_list���� �޾ƿ� ������ node�� �Է��ϰ� circular queue�� �Է��ؼ� �޾Ƴ���
}


void set_schedule(int method)
/*
	fn: set_schedule
	desc: set scheduling method

	param: method
	scheduling method
	1. FCFS (Nonpreemptive)
	2. Shortest Job First (Nonpreemptive)
	3. Shortest Remaining Time First (Prremptive)
	4. Round Robin : Time Quantum = 2 (Prremptive)
	return none
*/
{
	//Scheduler�� �����ϰ� �ش� ��ü�� property�� method�� ����
}


int do_schedule(int tick)
/*
	fn: do_schedule
	desc: scheduling function called every tick from main
	param
 	tick: time tick beginning from 0
	return
    0: when all process are terminated
    1: otherwise
*/
{

}


void print_performance()
/*
	fn: print_performance();
	desc: print system performance
*/
{

}






