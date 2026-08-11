#include <raylib.h>


class Tictactoe{
    private:
        int board[3][3];
        int currentPlayer;
        int cellsize;
        bool gameover;

    public:
        void Reset(){
            for(int i=0; i < 3; i++){
                for(int j=0; j<3; j++){
                    board[i][j] = 0;
                }
            }
            currentPlayer = 1;
            gameover = false;
        }

        Tictactoe(int windowsize){
            cellsize = windowsize/ 3;
            Reset();
        }
        
        void checkwin(){
            for(int i=0; i< 3; i++){
                if(board[i][0] != 0 && board[i][0] == board[i][1] && board[i][1] == board[i][2]) gameover = true;
                if(board[0][i] != 0 && board[0][i] == board[1][i] && board[1][i] == board[2][i]) gameover = true;
            }

            if(board[0][0] != 0 && board[0][0] == board[1][1] && board[1][1] == board[2][2]) gameover = true;
            if(board[0][2] != 0 && board[0][2] == board[1][1] && board[1][1] == board[2][0]) gameover = true;

            if(!gameover) {
                bool hasempty = false;
                for(int i=0; i<3; i++){
                    for(int j=0; j<3; j++){
                        if(board[i][j] == 0) hasempty = true;
                    }
                }
                if(!hasempty)gameover = true;
            }
        }

        void update(){
            if(gameover){
                if(IsKeyPressed(KEY_SPACE)) Reset();
                return;
            }

            if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){
                Vector2 mousePos = GetMousePosition();

                int col = mousePos.x / cellsize;
                int row = mousePos.y / cellsize;

                if(row >=0 && row <= 3 && col >=0 && col <= 3 && board[row][col] == 0 ){
                    board[row][col] = currentPlayer;

                    checkwin();

                    if(!gameover){
                        currentPlayer = (currentPlayer == 1) ? 2 : 1;
                    }
                }
            }
        }

         void Draw() {
        for (int i = 1; i < 3; i++) {
            DrawLine(i * cellsize, 0, i * cellsize, cellsize * 3, LIGHTGRAY);
            DrawLine(0, i * cellsize, cellsize * 3, i * cellsize, LIGHTGRAY);
        }

        for (int row = 0; row < 3; row++) {
            for (int col = 0; col < 3; col++) {
                int centerX = col * cellsize + cellsize / 2;
                int centerY = row * cellsize + cellsize / 2;

                if (board[row][col] == 1) {
                    DrawLine(centerX - 40, centerY - 40, centerX + 40, centerY + 40, RED);
                    DrawLine(centerX + 40, centerY - 40, centerX - 40, centerY + 40, RED);
                } 
                else if (board[row][col] == 2) {
                    DrawCircleLines(centerX, centerY, 40, BLUE);
                }
            }
        }

        if (gameover) {
            DrawRectangle(0, cellsize * 3 / 2 - 50, cellsize * 3, 100, Fade(BLACK, 0.8f));
            DrawText("GAME OVER! Press SPACE to restart", 40, cellsize * 3 / 2 - 15, 24, WHITE);
        }
    }

};

int main() {
    const int windowSize = 900;

    InitWindow(windowSize, windowSize, "Tic-Tac-Toe Game");
    SetTargetFPS(60);

    Tictactoe game(windowSize);

    while (!WindowShouldClose()) {
        game.update();

        BeginDrawing();
        ClearBackground(RAYWHITE);

        game.Draw();

        EndDrawing();
    }

    CloseWindow();
}