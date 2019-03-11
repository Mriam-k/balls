#include "TXLib.h"
#include <stdio.h>

const double Global_Sleep = txQueryPerformance () * 100;

//-----------------------------------------------------------------------------

struct Ball
    {
    int x, y;
    int vx, vy;
    int r;
    COLORREF color_circuit, color_ball;
    };

//-----------------------------------------------------------------------------

void MoveBalls ();
void DrawBackground ();
void DrowBall (Ball *b);
void MoveStrategiyaBall (Ball *b, int dt);
void Level_game (int* vx, int* vy);
void Count (int* counter, int* level, int* vx1, int* vy1, int* vx2, int* vy2, int* vx3, int* vy3,
              int* vx4, int* vy4, int* vx5, int* vy5);
void Drive_ball (Ball *b);
void CalculateDistance_R_R (double* r_r1, double* r_r2, double* r_r3, double* r_r4, double* r_r5,
                            int* y, int* y1, int* y2, int* y3, int* y4, int* y5,
                            int* x, int* x1, int* x2, int* x3, int* x4, int* x5,
                            int* vx, int* vy, int* balli);

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
    Ball ball  = {320, 110, 0, 0, 20, RGB (0,   255, 50 ), RGB (0,   128, 0  )};
    Ball ball1 = {360, 150, 2, 2, 20, RGB (63,  72,  204), RGB (63,  0,   255)};
    Ball ball2 = {390, 190, 3, 6, 20, RGB (128, 0,   255), RGB (128, 0,   255)};
    Ball ball3 = {420, 230, 4, 1, 20, RGB (128, 0,   64 ), RGB (170, 0,   85 )};
    Ball ball4 = {450, 260, 5, 7, 20, RGB (255, 255, 0  ), RGB (255, 255, 50 )};
    Ball ball5 = {490, 300, 3, 2, 20, RGB (255, 255, 255), RGB (255, 255, 255)};

    int dt = 2;
    int balli = 0;
    int counter = 0, level = 1;
    double r_r1 = 100, r_r2 = 100, r_r3 = 100, r_r4 = 100, r_r5 = 100;

    txSetTextAlign (TA_CENTER);

    while (!txGetAsyncKeyState (VK_ESCAPE))
        {
        txSetFillColor (RGB (0, 0, 0));
        txClear ();

        DrawBackground ();

        Drive_ball (&ball);

        Count (&counter, &level, &ball1.vx, &ball1.vy, &ball2.vx, &ball2.vy, &ball3.vx, &ball3.vy, &ball4.vx, &ball4.vy, &ball5.vx, &ball5.vy);

        MoveStrategiyaBall (&ball,  dt);
        MoveStrategiyaBall (&ball1, dt);
        MoveStrategiyaBall (&ball2, dt);
        MoveStrategiyaBall (&ball3, dt);
        MoveStrategiyaBall (&ball4, dt);
        MoveStrategiyaBall (&ball5, dt);

        CalculateDistance_R_R (&r_r1, &r_r2, &r_r3, &r_r4, &r_r5,
                               &ball.y, &ball1.y, &ball2.y, &ball3.y, &ball4.y, &ball5.y,
                               &ball.x, &ball1.x, &ball2.x, &ball3.x, &ball4.x, &ball5.x,
                               &ball.vx, &ball.vy, &balli);

        DrowBall (&ball);
        DrowBall (&ball1);
        DrowBall (&ball2);
        DrowBall (&ball3);
        DrowBall (&ball4);
        DrowBall (&ball5);

        char print [100] = "";
        sprintf (print, "����� ����� ������ = %d, ������� ���� %d       \r", balli, level);
        txTextOut (txGetExtentX()/2, 5, print);

        txSleep (Global_Sleep);
        }
    }

//-----------------------------------------------------------------------------

void DrowBall (Ball *b)
    {
    txSetColor     (b -> color_circuit, 3);
    txSetFillColor (b -> color_ball);
    txCircle (b -> x, b -> y, b -> r);
    }

//-----------------------------------------------------------------------------

void MoveStrategiyaBall (Ball *b, int dt)
    {
    b -> x  = (b -> x) + (b -> vx) * dt;
    b -> y  = (b -> y) + (b -> vy) * dt;

    if ((b -> x) >= 675)   (b -> vx) = -b -> vx,   b -> x = 675;
    if ((b -> y) >= 575)   (b -> vy) = -b -> vy,   b -> y = 575;
    if ((b -> x) <= 205)   (b -> vx) = -b -> vx,   b -> x = 205;
    if ((b -> y) <= 95)    (b -> vy) = -b -> vy,   b -> y = 95;
    }

//-----------------------------------------------------------------------------

void Level_game (int* vx, int* vy)
    {
    if (*vx > 0) *vx = *vx + 1;
    else         *vx = *vx - 1;
    if (*vy > 0) *vy = *vy + 1;
    else         *vy = *vy - 1;
    }

//-----------------------------------------------------------------------------

void Count (int* counter, int* level, int* vx1, int* vy1, int* vx2, int* vy2, int* vx3, int* vy3,
              int* vx4, int* vy4, int* vx5, int* vy5)
    {
    (*counter) ++;

    if (*counter == 1000)
        {
        (*level) ++;
        *counter = 0;

        Level_game (vx1, vy1);
        Level_game (vx2, vy2);
        Level_game (vx3, vy3);
        Level_game (vx4, vy4);
        Level_game (vx5, vy5);
        }
    }

 //-----------------------------------------------------------------------------

void Drive_ball (Ball *b)
    {
    if (GetAsyncKeyState (VK_RIGHT)) (*b).vx =  4, (*b).vy =  0;
    if (GetAsyncKeyState (VK_LEFT))  b -> vx = -4, b -> vy =  0;
    if (GetAsyncKeyState (VK_UP))    b -> vx =  0, b -> vy = -4;
    if (GetAsyncKeyState (VK_DOWN))  b -> vx =  0, b -> vy =  4;

    if (GetAsyncKeyState (VK_SHIFT))
        {
        if (b -> vx != 0)
            {
            if (b -> vx > 0) b -> vx = b -> vx + 4;
            else         b -> vx = b -> vx - 4;
            }
        else
            {
            if (b -> vy > 0) b -> vy = b -> vy + 4;
            else         b -> vy = b -> vy - 4;
            }
        }
    }

//-----------------------------------------------------------------------------

void CalculateDistance_R_R (double* r_r1, double* r_r2, double* r_r3, double* r_r4, double* r_r5,
                            int* y, int* y1, int* y2, int* y3, int* y4, int* y5,
                            int* x, int* x1, int* x2, int* x3, int* x4, int* x5,
                            int* vx, int* vy, int* balli)
    {
    *r_r1 = sqrt((*y - *y1) * (*y - *y1) + (*x - *x1) * (*x - *x1));
    *r_r2 = sqrt((*y - *y2) * (*y - *y2) + (*x - *x2) * (*x - *x2));
    *r_r3 = sqrt((*y - *y3) * (*y - *y3) + (*x - *x3) * (*x - *x3));
    *r_r4 = sqrt((*y - *y4) * (*y - *y4) + (*x - *x4) * (*x - *x4));
    *r_r5 = sqrt((*y - *y5) * (*y - *y5) + (*x - *x5) * (*x - *x5));

    if (*r_r1 <= 40 || *r_r2 <= 40 || *r_r3 <= 40 || *r_r4 <= 40 || *r_r5 <= 40)
        {
        *vx = 0;
        *vy = 0;
        *balli = *balli - 10;
        }
    else *balli = *balli + 1;
    }
