#include "types.h"
#include "stat.h"
#include "user.h"


#define PNUM 3  // 생성할 프로세스의 개수

int main(void) {
    int pid, i;
    printf(1, "start scheduler_test\n");

    for (i = 0; i < PNUM; i++) {
        pid = fork();
        if (pid < 0) {
            printf(1, "fork failed\n");
            exit();
        }

        if (pid == 0) {  // 자식 프로세스
            // 자식 프로세스의 PID 기반으로 우선순위 설정
            if (i == 0) {
                set_sche_info(1, 110);  // 첫 번째 프로세스 우선순위 설정
            } else if (i == 1) {
                set_sche_info(10, 60); // 두 번째 프로세스 우선순위 설정
            } else if (i == 2) {
                set_sche_info(11,60); // 세 번째 프로세스 우선순위 설정
            }

            int count = 0;
            while (count < 31) {
                printf(1, "PID:%d, priority:%d, proc_tick:%d ticks, total_cpu_usage:%d ticks\n",
                       getpid());
                count++;
                sleep(10);  // CPU 사용 시간을 증가시킴
            }
            printf(1, "PID:%d terminated\n", getpid());
            exit();
        }
    }

    for (i = 0; i < PNUM; i++) {
        wait();
    }

    printf(1, "end of scheduler_test\n");
    exit();
}
