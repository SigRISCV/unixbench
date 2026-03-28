#include<stdio.h>
#include<stdlib.h>
#include<time.h>

typedef struct task{
    const char* task_name;
    const char* program_path;
    const char* program_args;
    const int sample_number;
    const char* log_filename;
}* Task;

void execute_task(Task task){
    char command_buf[100];
    sprintf(command_buf, "%s %s", task->program_path, task->program_args);
    __raw FILE* log_fp = fopen(task->log_filename, "a+");
    printf("execute %s\n", task->task_name);
    fprintf(log_fp, "execute %s\n", task->task_name);

    struct timespec start, end;
    timespec_get(&start, TIME_UTC);
    for(int i=0;i<task->sample_number;i++){
        printf("pass %d\n", i);
        system(command_buf);
    }
    timespec_get(&end, TIME_UTC);

    double elapsed = (end.tv_sec - start.tv_sec) + (end.tv_nsec - start.tv_nsec) / 1e9;
    printf("Elapsed time: %.3f seconds\n", elapsed);
    fprintf(log_fp, "Elapsed time: %.3f seconds\n", elapsed);
    fclose(log_fp);
}

#define TASK_NUM 9

int main(){
    setenv("UB_BINDIR", ".", 1);
    struct task task_list[TASK_NUM] = {
        {
            .task_name = "dhrystone",
            .program_path = "./dhry2reg",
            .program_args = "10",
            .sample_number = 8,
            .log_filename = "./unixbench.log"
        },
        {
            .task_name = "whetstone",
            .program_path = "./whetstone-double",
            .program_args = "2>&1",
            .sample_number = 8,
            .log_filename = "./unixbench.log"
        },
        {
            .task_name = "execl",
            .program_path = "./execl",
            .program_args = "30",
            .sample_number = 3,
            .log_filename = "./unixbench.log"
        },
        {
            .task_name = "pipe",
            .program_path = "./pipe",
            .program_args = "10",
            .sample_number = 8,
            .log_filename = "./unixbench.log"
        },
        {
            .task_name = "context",
            .program_path = "./context1",
            .program_args = "10",
            .sample_number = 8,
            .log_filename = "./unixbench.log"
        },
        {
            .task_name = "spawn",
            .program_path = "./spawn",
            .program_args = "30",
            .sample_number = 3,
            .log_filename = "./unixbench.log"
        },
        {
            .task_name = "syscall",
            .program_path = "./syscall",
            .program_args = "10",
            .sample_number = 8,
            .log_filename = "./unixbench.log"
        },
        {
            .task_name = "shell1",
            .program_path = "./looper",
            .program_args = "60 ./multi.sh 1",
            .sample_number = 3,
            .log_filename = "./unixbench.log"
        },
        {
            .task_name = "shell8",
            .program_path = "./looper",
            .program_args = "60 ./multi.sh 8",
            .sample_number = 3,
            .log_filename = "./unixbench.log"
        },
    };
    for(int i=0;i<TASK_NUM;i++){
        execute_task(&task_list[i]);
    }
}
