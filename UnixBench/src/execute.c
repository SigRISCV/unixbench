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
    char command_buf[256];
    snprintf(command_buf, sizeof(command_buf), "%s %s", task->program_path, task->program_args);
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

int main(){
    setenv("UB_BINDIR", ".", 1);
    struct task task_list_user[] = {
        {
            .task_name = "dhrystone",
            .program_path = "./dhry2reg",
            .program_args = "10",
            .sample_number = 6,
            .log_filename = "./unixbench.log"
        },
        {
            .task_name = "whetstone",
            .program_path = "./whetstone-double",
            .program_args = "2>&1",
            .sample_number = 6,
            .log_filename = "./unixbench.log"
        },
        {
            .task_name = "arithoh",
            .program_path = "./arithoh",
            .program_args = "10",
            .sample_number = 6,
            .log_filename = "./unixbench.log"
        },
        {
            .task_name = "register",
            .program_path = "./register",
            .program_args = "10",
            .sample_number = 6,
            .log_filename = "./unixbench.log"
        },
        {
            .task_name = "short",
            .program_path = "./short",
            .program_args = "10",
            .sample_number = 6,
            .log_filename = "./unixbench.log"
        },
        {
            .task_name = "int",
            .program_path = "./int",
            .program_args = "10",
            .sample_number = 6,
            .log_filename = "./unixbench.log"
        },
        {
            .task_name = "long",
            .program_path = "./long",
            .program_args = "10",
            .sample_number = 6,
            .log_filename = "./unixbench.log"
        },
        {
            .task_name = "float",
            .program_path = "./float",
            .program_args = "10",
            .sample_number = 6,
            .log_filename = "./unixbench.log"
        },
        {
            .task_name = "double",
            .program_path = "./double",
            .program_args = "10",
            .sample_number = 6,
            .log_filename = "./unixbench.log"
        },
        {
            .task_name = "hanoi",
            .program_path = "./hanoi",
            .program_args = "10",
            .sample_number = 6,
            .log_filename = "./unixbench.log"
        },
    };

    struct task task_list_kernel[] = {
        {
            .task_name = "execl",
            .program_path = "./execl",
            .program_args = "30",
            .sample_number = 6,
            .log_filename = "./unixbench.log"
        },
        {
            .task_name = "fstime",
            .program_path = "./fstime",
            .program_args = "-c -t 30 -d . -b 1024 -m 2000",
            .sample_number = 6,
            .log_filename = "./unixbench.log"
        },
        {
            .task_name = "fsdisk",
            .program_path = "./fstime",
            .program_args = "-c -t 30 -d . -b 4096 -m 8000",
            .sample_number = 6,
            .log_filename = "./unixbench.log"
        },
        {
            .task_name = "fsbuffer",
            .program_path = "./fstime",
            .program_args = "-c -t 30 -d . -b 256 -m 500",
            .sample_number = 6,
            .log_filename = "./unixbench.log"
        },
        {
            .task_name = "context",
            .program_path = "./context1",
            .program_args = "10",
            .sample_number = 6,
            .log_filename = "./unixbench.log"
        },
        {
            .task_name = "spawn",
            .program_path = "./spawn",
            .program_args = "10",
            .sample_number = 6,
            .log_filename = "./unixbench.log"
        },
        {
            .task_name = "syscall",
            .program_path = "./syscall",
            .program_args = "10",
            .sample_number = 6,
            .log_filename = "./unixbench.log"
        },
        {
            .task_name = "sysexec",
            .program_path = "./syscall",
            .program_args = "10 exec",
            .sample_number = 6,
            .log_filename = "./unixbench.log"
        },
    };

    int TASK_NUM_USER = sizeof(task_list_user) / sizeof(struct task);
    for(int i=0;i<TASK_NUM_USER;i++){
        execute_task(&task_list_user[i]);
    }
    int TASK_NUM_KERNEL = sizeof(task_list_kernel) / sizeof(struct task);
    for(int i=0;i<TASK_NUM_KERNEL;i++){
        execute_task(&task_list_kernel[i]);
    }
}
