/********************/
// BOJ 17825 주사위 윷놀이
// 핵심: DFS (브루트 포스)
/********************/
#include <stdio.h>
#define TURN_MAX 11
#define MAX			 33
#define PAWN_MAX 6
#define END 		 32

int ans;	// 정답 
int dice[TURN_MAX], place[MAX], at[PAWN_MAX];	// 주사위에서 나올 수, 말판 위에 있는 말의 개수, 말이 있는 위치 
// map[i][0 / 1 ~ 5] = a: i번 위치의 값 (0) / 말이 i번 위치에 있을 때 다음 위치 (1 ~ 5) 
int map[MAX][PAWN_MAX] = {
			{0, 1, 2, 3, 4, 5},\
			{2, 2, 3, 4, 5, 6},\
			{4, 3, 4, 5, 6, 7},\
			{6, 4, 5, 6, 7, 8},\
			{8, 5, 6, 7, 8, 9},\
			{10, 21, 22, 23, 24, 25},\
			{12, 7, 8, 9, 10, 11},\
			{14, 8, 9, 10, 11, 12},\
			{16, 9, 10, 11, 12, 13},\
			{18, 10, 11, 12, 13, 14},\
			{20, 27, 28, 24, 25, 26},\
			{22, 12, 13, 14, 15, 16},\
			{24, 13, 14, 15, 16, 17},\
			{26, 14, 15, 16, 17, 18},\
			{28, 15, 16, 17, 18, 19},\
			{30, 29, 30, 31, 24, 25},\
			{32, 17, 18, 19, 20, 32},\
			{34, 18, 19, 20, 32, 32},\
			{36, 19, 20, 32, 32, 32},\
			{38, 20, 32, 32, 32, 32},\
			{40, 32, 32, 32, 32, 32},\
			{13, 22, 23, 24, 25, 26},\
			{16, 23, 24, 25, 26, 20},\
			{19, 24, 25, 26, 20, 32},\
			{25, 25, 26, 20, 32, 32},\
			{30, 26, 20, 32, 32, 32},\
			{35, 20, 32, 32, 32, 32},\
			{22, 28, 24, 25, 26, 20},\
			{24, 24, 25, 26, 20, 32},\
			{28, 30, 31, 24, 25, 26},\
			{27, 31, 24, 25, 26, 20},\
			{26, 24, 25, 26, 20, 32},\
			{0, 32, 32, 32, 32, 32}
			};
			
void dfs(int cnt, int sum) {
	// (cnt + 1)번째 주사위 던질 때 말을 선택하는 함수
	// 지금까지의 합은 sum
	
	// 도착함 
	if(cnt == 10) {
		// 최대값 갱신 
		if(ans < sum) ans = sum;
		
		return;
	}
	
	for(int i = 1; i <= 4; i++) {
		// 이미 도착점이면 통과 
		if(at[i] == END) continue;
		
		int next = map[at[i]][dice[cnt]];	// 다음 위치 
		
		// 이동을 마치는 칸이 도착칸이 아닌데 다른 말이 있음 => 통과 
		if(place[next] && next && next != END) continue;
		
		int value = map[next][0];	// 값 
		int prev = at[i];	// 현재 위치 
		
		// 방문 체크 
		at[i] = next;
		place[prev]--; place[next]++;
		
		dfs(cnt + 1, sum + value);
		
		// 방문 해제 
		at[i] = prev;
		place[next]--; place[prev]++;
	}
}


int main(void) {
	for(int i = 0; i < 10; i++) {
		scanf("%d", &dice[i]);
	}
	
	place[0] = 4;
	
	dfs(0, 0);
	
	printf("%d\n", ans);
	
	return 0;
}
