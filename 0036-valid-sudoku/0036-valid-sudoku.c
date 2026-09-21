bool isValidSudoku(char** board, int boardSize, int* boardColSize) {
    int rows[9][10] = {0};
    int cols[9][10] = {0};
    int boxes[9][10] = {0};

    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {

            if (board[i][j] == '.')
                continue;

            int num = board[i][j] - '0';
            int box = (i / 3) * 3 + (j / 3);

            if (rows[i][num] || cols[j][num] || boxes[box][num])
                return false;

            rows[i][num] = 1;
            cols[j][num] = 1;
            boxes[box][num] = 1;
        }
    }

    return true;
}
