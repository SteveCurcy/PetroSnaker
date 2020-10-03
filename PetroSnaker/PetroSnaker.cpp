#include <iostream>
#include "Sanke.h"

int main()
{
    system("mode con cols=120 lines=40");
    Snake ss;
    int timer = 0;
    while (true) {
        if (_kbhit()) {
            char InputChar = _getch();
            if (InputChar == -32) {
                InputChar = _getch();
                switch (InputChar)
                {
                case UP:
                    ss.TurnAround(UP);  ss.Move();  ss.ResetTimer();  break;
                case DOWN:
                    ss.TurnAround(DOWN);  ss.Move(); ss.ResetTimer(); break;
                case LEFT:
                    ss.TurnAround(LEFT);  ss.Move();  ss.ResetTimer(); break;
                case RIGHT:
                    ss.TurnAround(RIGHT);  ss.Move();  ss.ResetTimer(); break;
                }
            }
        }
        if (ss.IsAlive() == false) break;
        ss.Tick();
    }
    return 0;
}
