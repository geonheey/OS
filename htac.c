#include "types.h"
#include "stat.h"
#include "user.h"

char buf[4096];
int line = 0; // 전역변수 선언

void htac(int fd);

int main(int argc, char *argv[]) {
    int fd, i;

    if (argc <= 1) {
        htac(0);
        exit();
    }
    
    if ((fd = open(argv[2], 0)) < 0) {
        printf(2, "htac: cannot open %s\n", argv[2]);
        exit();
    }

    line = atoi(argv[1]); // 내가 입력한 줄 번호

    for (i = 2; i < atoi(argv[1]); i++) {
        htac(fd);
        line = 0; // 각 파일마다 line 초기화
    }
    close(fd);

    exit();
}

void htac(int fd) {
    int n, i, last_newline = -1;

    // read : 파일에서 데이터를 읽어와서 버퍼에 저장, 읽은 바이트 수를 반환
    while ((n = read(fd, buf, sizeof(buf))) > 0) {
        for (i = n - 1; i >= 0; i--) {
            if (buf[i] == '\n') {
                if(last_newline != -1) {
                    line--;
                }
                if (last_newline != -1 && line >= 0) {
                  //last_newline이 초기값이 아니고 
                  //line이 지정한 줄 번호 이하일 때 특정 범위의 텍스트를 표준 출력으로 출력
                    write(1, &buf[i + 1], last_newline - i - 1);
                    write(1, "\n", 1);
                }
                last_newline = i;
                if (line < 0) {
                    return; // 지정한 줄 번호까지 출력한 후 종료
                }
            }
        }
    }

    if (n < 0) {
        printf(2, "htac: read error\n");
        exit();
    }
}