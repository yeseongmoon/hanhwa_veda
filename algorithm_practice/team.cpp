#include <algorithm>
#include <bitset>
#include <iostream>

using namespace std;

constexpr int N = 11;
int board[N][N];
int maxScore;

void dfs(int position, bitset<N> used, int currentScore) {
  if (position == N) {
    maxScore = max(maxScore, currentScore);
    return;
  }

  for (int player = 0; player < N; ++player) {
    if (!used[player] && board[player][position] > 0) {
      used.set(player);
      dfs(position + 1, used, currentScore + board[player][position]);
      used.reset(player);
    }
  }
}

int main() {
  ios::sync_with_stdio(0);
  cin.tie(0);

  int T;
  cin >> T;

  while (T--) {
    for (int i = 0; i < N; ++i)
      for (int j = 0; j < N; ++j)
        cin >> board[i][j];

    maxScore = 0;
    dfs(0, bitset<N>(), 0);
    cout << maxScore << '\n';
  }

  return 0;
}
