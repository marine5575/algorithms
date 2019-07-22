#include <cstdio>
#define div 100000

using namespace std;

int map[101][101][2][2];	// map[i][j][0 or 1][0 or 1] : (i, j) 위치에 (동 or 북) 방향으로부터 (두 번 이상 or 1번) 움직여서 들어온 개수


int main(void) {
	int w, h; // 가로, 세로

	scanf("%d %d", &w, &h);

        // x축은 언제든 위로 꺾일 준비가 되어 있음
	for (int i = 1; i < w; i++) map[i][0][0][0] = 1;
        // y축도 언제든 오른쪽으로 꺾일 준비가 됨
	for (int i = 1; i < h; i++) map[0][i][1][0] = 1;

        // 모든 지점에 대해 갱신
	for (int x = 1; x < w; x++) {
		for (int y = 1; y < h; y++) {
                        // (x, y) 지점이 동쪽으로 2번 이상 간 상태 = 이전 노드에서 2번 이상 간 상태 + 이전 노드에서 1번 간 상태
                        // 중간에 자료형 넘치지 않도록 미리 모듈러 연산
			map[x][y][0][0] = (map[x - 1][y][0][0] + map[x - 1][y][0][1]) % div;
                        // (x, y) 지점이 동쪽으로 1번 간 상태 = 이전 노드에서 북쪽으로 2번 이상 간 상태
			map[x][y][0][1] = map[x - 1][y][1][0];
                        // (x, y) 지점이 북쪽으로 2번 이상 간 상태 = 이전 노드에서 북쪽으로 2번 이상 간 상태 + 이전 노드에서 북쪽으로 1번 간 상태
                        // 마찬가지로 자료형 범위때문에 모듈러 연산 값 저장
			map[x][y][1][0] = (map[x][y - 1][1][0] + map[x][y - 1][1][1]) % div;
                        // (x, y) 지점이 북쪽으로 1번 간 상태 = 이전 노드에서 동쪽으로 2번 이상 간 상태
			map[x][y][1][1] = map[x][y - 1][0][0];
		}
	}

        // 정답은 모든 경우의 수를 더함
	int ans = map[w - 1][h - 1][0][0] + map[w - 1][h - 1][0][1] + map[w - 1][h - 1][1][0] + map[w - 1][h - 1][1][1];

	printf("%d\n", ans % div);  // 모듈러 연산 결과를 물었으므로

	return 0;
}
