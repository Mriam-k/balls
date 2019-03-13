#include "TXLib.h"
#include <stdio.h>

const double Global_Sleep = txQueryPerformance () * 100;

//-----------------------------------------------------------------------------

struct Ball
    {
    int x, y;
    int vx, vy;
    int r;
    COLORREF color_contour, color_ball;
    int thickness_contour;
    };

//-----------------------------------------------------------------------------

void MoveBalls ();
void DrawBackground ();
void DrowBall (Ball *b_drow);
void MoveStrategiyaBall (Ball *b_Strategiya, int dt);
void Level_game (Ball *b_level);
void Count (int* balli, int* level, int* counter, Ball *b1, Ball *b2, Ball *b3, Ball *b4, Ball *b5, Ball *b6);
void Drive_ball (Ball *b_drive);
void CalculateDistance_R_R (double* r_r1, double* r_r2, double* r_r3, double* r_r4, double* r_r5, double* r_r6,
                            Ball *b, Ball *b1, Ball *b2, Ball *b3, Ball *b4, Ball *b5, Ball *b6,
                            int* balli);

//-----------------------------------------------------------------------------

int main ()
    {
    txCreateWindow (900, 700);

    txBegin ();

    MoveBalls ();

    txEnd ();

    return 0;
    }

//-----------------------------------------------------------------------------

void DrawBackground ()
    {
    txSetColor     (TX_ORANGE, 5);
    txSetFillColor (TX_NULL);
    txRectangle (180, 70, 700, 600);
    }

//-----------------------------------------------------------------------------

void MoveBalls ()
    {
    Ball ball  = {320, 110, 0, 0, 20, RGB (0,   255, 50 ), RGB (0,   128, 0  ), 4};
    Ball ball1 = {360, 150, 2, 2, 20, RGB (63,  72,  204), RGB (63,  0,   170), 6};
    Ball ball2 = {390, 190, 3, 6, 20, RGB (128, 0,   255), RGB (128, 0,   255)   };
    Ball ball3 = {420, 230, 4, 1, 20, RGB (128, 0,   64 ), RGB (170, 0,   85 ), 4};
    Ball ball4 = {450, 260, 5, 7, 20, RGB (255, 255, 0  ), RGB (255, 255, 100), 5};
    Ball ball5 = {490, 300, 3, 2, 20, RGB (255, 255, 255), RGB (255, 255, 255)   };
    Ball ball6 = {510, 600, 2, 5, 20, RGB (240, 96,  0  ), RGB (255, 127, 39 ), 3};

    int dt = 2;
    int balli = 0;
    int counter = 0, level = 1;
    double r_r1 = 100, r_r2 = 100, r_r3 = 100, r_r4 = 100, r_r5 = 100, r_r6 = 100;

    txSetTextAlign (TA_CENTER);

    while (!txGetAsyncKeyState (VK_ESCAPE))
        {
        txSetFillColor (RGB (0, 0, 0));
        txClear ();

        DrawBackground ();

        Drive_ball (&ball);

        Count (&balli, &level, &counter, &ball1, &ball2, &ball3, &ball4, &ball5, &ball6);

        MoveStrategiyaBall (&ball,  dt);
        MoveStrategiyaBall (&ball1, dt);
        MoveStrategiyaBall (&ball2, dt);
        MoveStrategiyaBall (&ball3, dt);
        MoveStrategiyaBall (&ball4, dt);
        MoveStrategiyaBall (&ball5, dt);
        MoveStrategiyaBall (&ball6, dt);

        CalculateDistance_R_R (&r_r1, &r_r2, &r_r3, &r_r4, &r_r5, &r_r6,
                               &ball, &ball1, &ball2, &ball3, &ball4, &ball5, &ball6,
                               &balli);

        DrowBall (&ball);
        DrowBall (&ball1);
        DrowBall (&ball2);
        DrowBall (&ball3);
        DrowBall (&ball4);
        DrowBall (&ball5);
        DrowBall (&ball6);

        char print [100] = "";
        txSetColor (RGB(128, 255, 39), 10);
        sprintf (print, "Общая сумма баллов = %d, уровень игры %d       \r", balli, level);
        txTextOut (txGetExtentX()/2, 5, print);

        txSleep (Global_Sleep);
        }
    }

//-----------------------------------------------------------------------------

void DrowBall (Ball *b_drow)
    {
    txSetColor     (b_drow -> color_contour, b_drow -> thickness_contour);
    txSetFillColor (b_drow -> color_ball);
    txCircle (b_drow -> x, b_drow -> y, b_drow -> r);
    }

//-----------------------------------------------------------------------------

void MoveStrategiyaBall (Ball *b_Strategiya, int dt)
    {
    b_Strategiya -> x  = (b_Strategiya -> x) + (b_Strategiya -> vx) * dt;
    b_Strategiya -> y  = (b_Strategiya -> y) + (b_Strategiya -> vy) * dt;

    if ((b_Strategiya -> x) >= 675)   (b_Strategiya -> vx) = -b_Strategiya -> vx,   b_Strategiya -> x = 675;
    if ((b_Strategiya -> y) >= 575)   (b_Strategiya -> vy) = -b_Strategiya -> vy,   b_Strategiya -> y = 575;
    if ((b_Strategiya -> x) <= 205)   (b_Strategiya -> vx) = -b_Strategiya -> vx,   b_Strategiya -> x = 205;
    if ((b_Strategiya -> y) <= 95)    (b_Strategiya -> vy) = -b_Strategiya -> vy,   b_Strategiya -> y = 95;
    }

//-----------------------------------------------------------------------------

void Level_game (Ball *b_level)
    {
    if ((*b_level).vx > 0) (*b_level).vx = (*b_level).vx + 1;
    else         (*b_level).vx = (*b_level).vx - 1;
    if ((*b_level).vy > 0) (*b_level).vy = (*b_level).vy + 1;
    else         (*b_level).vy = (*b_level).vy - 1;
    }

//-----------------------------------------------------------------------------

void Count (int* balli, int* level, int* counter, Ball *b1, Ball *b2, Ball *b3, Ball *b4, Ball *b5, Ball *b6)
    {
    if ((*balli) % 500 == 0 && ((*balli) > (*counter)))
        {
        (*level) ++;
        *counter = *balli;

        Level_game (b1);
        Level_game (b2);
        Level_game (b3);
        Level_game (b4);
        Level_game (b5);
        Level_game (b6);
        }
    }

 //-----------------------------------------------------------------------------

void Drive_ball (Ball *b_drive)
    {
    if (GetAsyncKeyState (VK_RIGHT)) (*b_drive).vx =  4, (*b_drive).vy =  0;
    if (GetAsyncKeyState (VK_LEFT))  b_drive -> vx = -4, b_drive -> vy =  0;
    if (GetAsyncKeyState (VK_UP))    b_drive -> vx =  0, b_drive -> vy = -4;
    if (GetAsyncKeyState (VK_DOWN))  b_drive -> vx =  0, b_drive -> vy =  4;

    if (GetAsyncKeyState (VK_SHIFT))
        {
        if (b_drive -> vx != 0)
            {
            if (b_drive -> vx > 0) b_drive -> vx = b_drive -> vx + 4;
            else         b_drive -> vx = b_drive -> vx - 4;
            }
        else
            {
            if (b_drive -> vy > 0) b_drive -> vy = b_drive -> vy + 4;
            else         b_drive -> vy = b_drive -> vy - 4;
            }
        }
    }

//-----------------------------------------------------------------------------

void CalculateDistance_R_R (double* r_r1, double* r_r2, double* r_r3, double* r_r4, double* r_r5, double* r_r6,
                            Ball *b, Ball *b1, Ball *b2, Ball *b3, Ball *b4, Ball *b5, Ball *b6,
                            int* balli)
    {
    *r_r1 = sqrt(((b -> y) - (b1 -> y)) * ((b -> y) - (b1 -> y)) + ((b -> x) - (b1 -> x)) * ((b -> x) - (b1 -> x)));
    *r_r2 = sqrt(((b -> y) - (b2 -> y)) * ((b -> y) - (b2 -> y)) + ((b -> x) - (b2 -> x)) * ((b -> x) - (b2 -> x)));
    *r_r3 = sqrt(((b -> y) - (b3 -> y)) * ((b -> y) - (b3 -> y)) + ((b -> x) - (b3 -> x)) * ((b -> x) - (b3 -> x)));
    *r_r4 = sqrt(((b -> y) - (b4 -> y)) * ((b -> y) - (b4 -> y)) + ((b -> x) - (b4 -> x)) * ((b -> x) - (b4 -> x)));
    *r_r5 = sqrt(((b -> y) - (b5 -> y)) * ((b -> y) - (b5 -> y)) + ((b -> x) - (b5 -> x)) * ((b -> x) - (b5 -> x)));
    *r_r6 = sqrt(((b -> y) - (b6 -> y)) * ((b -> y) - (b6 -> y)) + ((b -> x) - (b6 -> x)) * ((b -> x) - (b6 -> x)));

    if (*r_r1 <= 40 || *r_r2 <= 40 || *r_r3 <= 40 || *r_r4 <= 40 || *r_r5 <= 40 || *r_r6 <= 40)
        {
        b -> vx = 0;
        b -> vy = 0;
        *balli = *balli - 10;
        if (*balli < 0) *balli = 0;
        }
    else *balli = *balli + 1;
    }
