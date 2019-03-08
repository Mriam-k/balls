#include "TXLib.h"
#include <stdio.h>

const double Global_Sleep = txQueryPerformance () * 100;

//-----------------------------------------------------------------------------

struct Ball
    {
    int x, y;
    int vx, vy;
    };

//-----------------------------------------------------------------------------

void MoveBalls ();
void DrawBackground ();
void DrowBall (int x, int y, int r, COLORREF color_circuit, COLORREF color_ball);
void MoveStrategiyaBall (int* x, int* y, int* vx, int* vy, int dt);
void Level_game (int* vx, int* vy);
void Count (int* counter, int* level, int* vx1, int* vy1, int* vx2, int* vy2, int* vx3, int* vy3,
              int* vx4, int* vy4, int* vx5, int* vy5);
void Drive_ball (int* vx, int* vy);
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
    Ball ball = {320, 110, 0, 0}, ball1 = {360, 150, 2, 2};

    int x2 = 390, x3 = 420, x4 = 450, x5 = 490;
    int y2 = 190, y3 = 230, y4 = 260, y5 = 300;
    int dt = 2;
    int vx2 = 3, vy2 = 6, vx3 = 4, vy3 = 1, vx4 = 5, vy4 = 7, vx5 = 3, vy5 = 2;
    int balli = 0;
    int counter = 0, level = 1;
    double r_r1 = 100, r_r2 = 100, r_r3 = 100, r_r4 = 100, r_r5 = 100;

    txSetTextAlign (TA_CENTER);

    while (!txGetAsyncKeyState (VK_ESCAPE))
        {
        txSetFillColor (RGB (0, 0, 0));
        txClear ();

        DrawBackground ();

        Drive_ball (&ball.vx, &ball.vy);

        Count (&counter, &level, &ball1.vx, &ball1.vy, &vx2, &vy2, &vx3, &vy3, &vx4, &vy4, &vx5, &vy5);

        MoveStrategiyaBall (&ball.x,  &ball.y,  &ball.vx,  &ball.vy,  dt);
        MoveStrategiyaBall (&ball1.x, &ball1.y, &ball1.vx, &ball1.vy, dt);
        MoveStrategiyaBall (&x2, &y2, &vx2, &vy2, dt);
        MoveStrategiyaBall (&x3, &y3, &vx3, &vy3, dt);
        MoveStrategiyaBall (&x4, &y4, &vx4, &vy4, dt);
        MoveStrategiyaBall (&x5, &y5, &vx5, &vy5, dt);

        CalculateDistance_R_R (&r_r1, &r_r2, &r_r3, &r_r4, &r_r5,
                               &ball.y, &ball1.y, &y2, &y3, &y4, &y5,
                               &ball.x, &ball1.x, &x2, &x3, &x4, &x5,
                               &ball.vx, &ball.vy, &balli);

        DrowBall (ball.x,  ball.y,  20, RGB (0,   255, 50 ), RGB (0,   128, 0  ));
        DrowBall (ball1.x, ball1.y, 20, RGB (63,  72,  204), RGB (63,  0,   255));
        DrowBall (x2, y2, 20, RGB (128, 0,   255), RGB (128, 0,   255));
        DrowBall (x3, y3, 20, RGB (128, 0,   64 ), RGB (170, 0,   85 ));
        DrowBall (x4, y4, 20, RGB (255, 255, 0  ), RGB (255, 255, 50 ));
        DrowBall (x5, y5, 20, RGB (255, 255, 255), RGB (255, 255, 255));

        char print [100] = "";
        sprintf (print, "����� ����� ������ = %d, ������� ���� %d       \r", balli, level);
        txTextOut (txGetExtentX()/2, 5, print);

        txSleep (Global_Sleep);
        }
    }

//-----------------------------------------------------------------------------

void DrowBall (int x, int y, int r, COLORREF color_circuit, COLORREF color_ball)
    {
    txSetColor     (color_circuit, 3);
    txSetFillColor (color_ball);
    txCircle (x, y, r);
    }

//-----------------------------------------------------------------------------

void MoveStrategiyaBall (int* x, int* y, int* vx, int* vy, int dt)
    {
    *x  = *x  + *vx  * dt;
    *y  = *y  + *vy  * dt;

    if (*x >= 675)   *vx = -*vx,   *x = 675;
    if (*y >= 575)   *vy = -*vy,   *y = 575;
    if (*x <= 205)   *vx = -*vx,   *x = 205;
    if (*y <= 95)    *vy = -*vy,   *y = 95;
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

void Drive_ball (int* vx, int* vy)
    {
    if (GetAsyncKeyState (VK_RIGHT)) *vx =  4, *vy =  0;
    if (GetAsyncKeyState (VK_LEFT))  *vx = -4, *vy =  0;
    if (GetAsyncKeyState (VK_UP))    *vx =  0, *vy = -4;
    if (GetAsyncKeyState (VK_DOWN))  *vx =  0, *vy =  4;

    if (GetAsyncKeyState (VK_SHIFT))
        {
        if (*vx != 0)
            {
            if (*vx > 0) *vx = *vx + 4;
            else         *vx = *vx - 4;
            }
        else
            {
            if (*vy > 0) *vy = *vy + 4;
            else         *vy = *vy - 4;
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
