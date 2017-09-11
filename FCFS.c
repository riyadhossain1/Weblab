#include<stdio.h>

typedef struct {
    int pid;
    int arrival_time;
    int waiting_time;
    int burst_time;
    int start_time;
    int turn_around_time;
} process;

process p[100009], tmp;
int pos[100009];
int chk[100009];
int st[100009];

int main() {
    int n, i, j, sum_waiting_time, sum_turn_around_time, cur, flag;
    double avg_waiting_time, avg_turn_around_time;
    while(1) {
        for(i = 1; i < 100009; i++){
            st[i] = 0;
            chk[i] = 0;
        }
        printf("Number of process(enter 0 for last experiment) = ");
        scanf("%d", &n);

        if(n == 0) break;
        for(i = 1; i <= n; i++) {
            p[i].pid = i;
            printf("Enter the arrival time for process P%d = ", i);
            scanf("%d", &p[i].arrival_time);
            printf("Enter the burst time for process P%d = ", i);
            scanf("%d", &p[i].burst_time);
        }

        for(i = 1; i < n; i++) {
            for(j = i + 1; j <= n; j++) {
                if(p[i].arrival_time > p[j].arrival_time) {
                    tmp.pid = p[i].pid;
                    tmp.arrival_time = p[i].arrival_time;
                    tmp.burst_time = p[i].burst_time;

                    p[i].pid = p[j].pid;
                    p[i].arrival_time = p[j].arrival_time;
                    p[i].burst_time = p[j].burst_time;

                    p[j].pid = tmp.pid;
                    p[j].arrival_time = tmp.arrival_time;
                    p[j].burst_time = tmp.burst_time;
                }
            }
        }

        for(i = 1, sum_waiting_time = 0, sum_turn_around_time = 0, cur = 0; i <= n; i++) {
            if(p[i].arrival_time - cur < 0) {
                p[i].waiting_time = cur - p[i].arrival_time;
                p[i].start_time = cur;
            }
            else {
                p[i].waiting_time = 0;
                p[i].start_time = p[i].arrival_time;
                cur += (p[i].arrival_time - cur);
            }
            chk[p[i].start_time] = 1;
            st[p[i].start_time] = p[i].pid;
            cur += p[i].burst_time;

            p[i].turn_around_time = cur;

            sum_waiting_time += p[i].waiting_time;
            sum_turn_around_time += p[i].turn_around_time;
        }

        avg_waiting_time = (sum_waiting_time*1.0)/(n*1.0);
        avg_turn_around_time = (sum_turn_around_time*1.0)/(n*1.0);

                                                 /// ***** DISPLAY THE TABLE  ***** ////

        printf("\n\n");
        printf("                                       Process Information Table                                \n");
        printf("       +---------+---------------+--------------+--------------+------------+------------------+\n");
        printf("       | Process |  Arrival Time |  Start Time  | Waiting Time | Burst Time | Turn Around Time |\n");
        printf("       +---------+---------------+--------------+--------------+------------+------------------+\n");
        for(i = 1; i <= n; i++) {
            printf("       |    P%d   |      %3d      |     %3d      |     %3d      |     %3d    |      %3d         |\n", p[i].pid, p[i].arrival_time, p[i].start_time,  p[i].waiting_time, p[i].burst_time, p[i].turn_around_time);
            printf("       +---------+---------------+--------------+--------------+------------+------------------+\n");
        }
        printf("\n\n");


        printf("\n\nTotal Waiting Time = %d\n\n", sum_waiting_time);
        printf("Average Waiting Time = %0.2lf\n\n\n\n", avg_waiting_time);
        printf("Total Turn Around Time = %d\n\n", sum_turn_around_time);
        printf("Average Turn Around Time = %0.2lf\n\n\n\n", avg_turn_around_time);

        i = 1;
        while(p[i].start_time == 0 && p[i].turn_around_time == 0){
            i++;
        }
        pos[1] = p[i].start_time;
        pos[2] = p[i].turn_around_time;
        i++;
        for(j = 3; i <= n; i++) {
            if(p[i].start_time == pos[j - 1]) {
                pos[j++] = p[i].turn_around_time;
            }
            else {
                pos[j++] = p[i].start_time;
                pos[j++] = p[i].turn_around_time;
            }
        }

        printf("       Gantt Chart\n");
        printf("       +");
        for(i = pos[1] + 1, j = 2; i <= p[n].turn_around_time; i++) {
            printf("----");
            if(i == pos[j]) {
                printf("+");
                j++;
            }
        }
        printf("\n");

        printf("       |");
        flag = 1;
        for(i = pos[1] + 1, j = 2; i <= p[n].turn_around_time; i++) {
            if(pos[j] - pos[j - 1] == 1 && st[pos[j - 1]]){
                printf(" P%d |", st[pos[j - 1]]);
                j++;
            }
            else if(i == (pos[j] + pos[j - 1])/2 && st[pos[j - 1]]) {
                printf(" P%d ", st[pos[j - 1]]);
            }
            else if(i == pos[j]) {
                printf("    |");
                j++;
            }
            else {
                printf("    ");
            }
        }
        printf("\n");

         printf("       +");
        for(i = pos[1] + 1, j = 2; i <= p[n].turn_around_time; i++) {
            printf("----");
            if(i == pos[j]) {
                printf("+");
                j++;
            }
        }
        printf("\n");

        printf("      %2d", pos[1]);
        for(i = pos[1] + 1, j = 2; i <= p[n].turn_around_time; i++) {
            if(i == pos[j]) {
                printf("   %2d", pos[j]);
                j++;
            }
            else {
                printf("    ");
            }
        }
        printf("\n\n");
    }
    return 0;
}
