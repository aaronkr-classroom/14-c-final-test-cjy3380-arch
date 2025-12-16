#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 100
#define FILENAME "student.dat"

typedef struct {
    int id;
    char name[20];
    int kor, eng, math;
    int total;
    float avg;
    int rank;
} Student;

/* 함수 선언 */
void load_file(Student* s, int* count);
void save_file(Student* s, int count);
void input_student(Student* s, int* count);
void calc_rank(Student* s, int count);
void print_student(Student* s, int count);

int main(void) {
    Student students[MAX];
    int count = 0;
    int menu;

    while (1) {
        /* ===== 메뉴 출력 (요구사항 그대로) ===== */
        printf("\n[Menu]\n");
        printf("1. .dat 파일에서 데이터 읽기\n");
        printf("2. 추가 학생 정보 입력\n");
        printf("3. .dat 파일 저장\n");
        printf("4. 성적 확인 (평균 계산 등)\n");
        printf("5. 종료\n");
        printf("-------------------\n");
        printf("선택(1~5): ");

        scanf("%d", &menu);

        switch (menu) {
        case 1:
            load_file(students, &count);
            break;
        case 2:
            input_student(students, &count);
            break;
        case 3:
            save_file(students, count);
            break;
        case 4:
            print_student(students, count);
            break;
        case 5:
            printf("프로그램을 종료합니다.\n");
            return 0;
        default:
            printf("1~5 사이의 숫자를 입력하세요.\n");
        }
    }
}

/* ================= 함수 구현 ================= */

void load_file(Student* s, int* count) {
    FILE* fp = fopen(FILENAME, "rb");
    if (fp == NULL) {
        printf("파일이 존재하지 않습니다.\n");
        return;
    }

    *count = fread(s, sizeof(Student), MAX, fp);
    fclose(fp);

    calc_rank(s, *count);
    printf("%d명의 학생 데이터를 읽었습니다.\n", *count);
}

void save_file(Student* s, int count) {
    FILE* fp = fopen(FILENAME, "wb");
    if (fp == NULL) {
        printf("파일 저장 실패\n");
        return;
    }

    fwrite(s, sizeof(Student), count, fp);
    fclose(fp);

    printf("데이터가 파일에 저장되었습니다.\n");
}

void input_student(Student* s, int* count) {
    if (*count >= MAX) {
        printf("더 이상 입력할 수 없습니다.\n");
        return;
    }

    Student* p = &s[*count];

    printf("학번: ");
    scanf("%d", &p->id);

    printf("이름: ");
    scanf("%s", p->name);

    printf("국어 점수: ");
    scanf("%d", &p->kor);

    printf("영어 점수: ");
    scanf("%d", &p->eng);

    printf("수학 점수: ");
    scanf("%d", &p->math);

    p->total = p->kor + p->eng + p->math;
    p->avg = p->total / 3.0f;

    (*count)++;
    calc_rank(s, *count);

    printf("학생 정보가 추가되었습니다.\n");
}

void calc_rank(Student* s, int count) {
    for (int i = 0; i < count; i++) {
        s[i].rank = 1;
        for (int j = 0; j < count; j++) {
            if (s[i].total < s[j].total)
                s[i].rank++;
        }
    }
}

void print_student(Student* s, int count) {
    if (count == 0) {
        printf("출력할 데이터가 없습니다.\n");
        return;
    }

    printf("\n학번  이름     국어 영어 수학  총점   평균  등수\n");
    printf("------------------------------------------------\n");

    for (int i = 0; i < count; i++) {
        printf("%4d %-8s %4d %4d %4d %5d %6.1f %4d\n",
            s[i].id, s[i].name,
            s[i].kor, s[i].eng, s[i].math,
            s[i].total, s[i].avg, s[i].rank);
    }
}
