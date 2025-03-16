#include <iostream>
#include <vector>

using namespace std;

// 定义棋盘的大小
const int N = 15;
int i;

// 定义棋盘数组，用于存储每个位置的棋子颜色
char board[N][N];

// 定义当前是黑子还是白子下棋
bool black = true;

// 定义输入函数，用于读入玩家输入的棋子坐标
void input(int &x, int &y) {
    cout << (black ? "黑子" : "白子") << "下棋，请输入棋子坐标：";
    cin >> x >> y;
}

// 定义输出函数，用于打印当前棋盘状态
void output() {
    cout << "  ";
    for (int i = 0; i < N; i++) {
        cout << i << " ";
    }
    cout << endl;

    for (int i = 0; i < N; i++) {
        cout << i << " ";
        for (int j = 0; j < N; j++) {
            cout << board[i][j] << " ";
        }
        cout << endl;
    }
}

// 定义胜负判断函数，用于判断当前局面是否有一方胜利
bool check(int x, int y) {
    // 横向检查
    int cnt = 1;
    for (int i = x - 1; i >= 0; i--) {
        if (board[i][y] == board[x][y]) {
            cnt++;
        } else {
            break;
        }
    }
    for (int i = x + 1; i < N; i++) {
        if (board[i][y] == board[x][y]) {
            cnt++;
        } else {
            break;
        }
    }
    if (cnt >= 5) {
        return true;
    }

    // 纵向检查
    cnt = 1;
    for (int j = y - 1; j >= 0; j--) {
        if (board[x][j] == board[x][y]) {
            cnt++;
        } else {
            break;
        }
    }
    for (int j = y + 1; j < N; j++)
    if (board[i][j] == board[x][y]) {
            cnt++;
        } else {
            break;
        }
    
    if (cnt >= 5) {
        return true;
    }

    // 左上到右下的对角线检查
    cnt = 1;
    for (int i = x - 1, j = y - 1; i >= 0 && j >= 0; i--, j--) {
        if (board[i][j] == board[x][y]) {
            cnt++;
        } else {
            break;
        }
    }
    for (int i = x + 1, j = y + 1; i < N && j < N; i++, j++) {
        if (board[i][j] == board[x][y]) {
            cnt++;
        } else {
            break;
        }
    }
    if (cnt >= 5) {
        return true;
    }

    // 右上到左下的对角线检查
    cnt = 1;
    for (int i = x - 1, j = y + 1; i >= 0 && j < N; i--, j++) {
        if (board[i][j] == board[x][y]) {
            cnt++;
        } else {
            break;
        }
    }
    for (int i = x + 1, j = y - 1; i < N && j >= 0; i++, j--) {
        if (board[i][j] == board[x][y]) {
            cnt++;
        } else {
            break;
        }
    }
    if (cnt >= 5) {
        return true;
    }

    return false;
}

int main() {
    // 初始化棋盘数组
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            board[i][j] = '.';
        }
    }

    // 游戏主循环
    while (true) {
        // 输出棋盘
        output();

        // 读入玩家输入的棋子坐标
        int x, y;
        input(x, y);

        // 如果输入的坐标无效，则重新输入
        while (board[x][y] != '.') {
            cout << "该位置已经有棋子，请重新输入：";
            input(x, y);
        }

        // 在棋盘上放置棋子
        board[x][y] = black ? 'X' : 'O';

        // 判断胜负
        if (check(x, y)) {
            cout << (black ? "黑子" : "白子") << "胜利！" << endl;
            break;
        }

        // 切换下棋方
        black = !black;
    }

    return 0;
}
