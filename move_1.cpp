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

    void Drow ();
    void Drive ();
    void MoveStrategiya (int dt);
    void Level_game ();
    };

//-----------------------------------------------------------------------------

void MoveBalls ();
void DrawBackground ();
void Count (int* balli, int* level, int* counter, Ball *b1, Ball *b2, Ball *b3, Ball *b4, Ball *b5, Ball *b6);
void CalculateBalli (Ball *b, Ball *b1, Ball *b2, Ball *b3, Ball *b4, Ball *b5, Ball *b6, int* balli);
double CalculateDistance (Ball *b1, Ball *b2);

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

    txSetTextAlign (TA_CENTER);

    while (!txGetAsyncKeyState (VK_ESCAPE))
        {
        txSetFillColor (RGB (0, 0, 0));
        txClear ();

        DrawBackground ();

        ball.Drive ();

        Count (&balli, &level, &counter, &ball1, &ball2, &ball3, &ball4, &ball5, &ball6);

        ball.MoveStrategiya (dt);
        ball1.MoveStrategiya (dt);
        ball2.MoveStrategiya (dt);
        ball3.MoveStrategiya (dt);
        ball4.MoveStrategiya (dt);
        ball5.MoveStrategiya (dt);
        ball6.MoveStrategiya (dt);

        CalculateBalli (&ball, &ball1, &ball2, &ball3, &ball4, &ball5, &ball6,
                        &balli);

        ball.Drow  ();
        ball1.Drow ();
        ball2.Drow ();
        ball3.Drow ();
        ball4.Drow ();
        ball5.Drow ();
        ball6.Drow ();

        char print [100] = "";
        txSetColor (RGB(128, 255, 39), 10);
        sprintf (print, "Общая сумма баллов = %d, уровень игры %d       \r", balli, level);
        txTextOut (txGetExtentX()/2, 5, print);

        txSleep (Global_Sleep);
        }
    }

//-----------------------------------------------------------------------------

void Ball::Drive ()
    {
    if (GetAsyncKeyState (VK_RIGHT)) this->vx =  4, this->vy =  0;
    if (GetAsyncKeyState (VK_LEFT))  this->vx = -4, this->vy =  0;
    if (GetAsyncKeyState (VK_UP))    this->vx =  0, this->vy = -4;
    if (GetAsyncKeyState (VK_DOWN))  this->vx =  0, this->vy =  4;

    if (GetAsyncKeyState (VK_SHIFT))
        {
        if (this->vx != 0)
            {
            if (this->vx > 0) this->vx = this->vx + 4;
            else              this->vx = this->vx - 4;
            }
        else
            {
            if (this->vy > 0) this->vy = this->vy + 4;
            else              this->vy = this->vy - 4;
            }
        }
    }

//-----------------------------------------------------------------------------

void Ball::Drow ()
    {
    txSetColor     (this->color_contour, this->thickness_contour);
    txSetFillColor (color_ball);
    txCircle (x, y, r);
    }

//-----------------------------------------------------------------------------

void Ball::MoveStrategiya (int dt)
    {
    this->x  = (this->x) + (this->vx) * dt;
    this->y  = (this->y) + (this->vy) * dt;

    if (this->x >= 675)   this->vx = -this->vx,   this->x = 675;
    if (this->y >= 575)   this->vy = -this->vy,   this->y = 575;
    if (this->x <= 205)   this->vx = -this->vx,   this->x = 205;
    if (this->y <= 95)    this->vy = -this->vy,   this->y = 95;
    }

//-----------------------------------------------------------------------------

void Ball::Level_game ()
    {
    if (this->vx > 0) this->vx = this->vx + 1;
    else              this->vx = this->vx - 1;
    if (this->vy > 0) this->vy = this->vy + 1;
    else              this->vy = this->vy - 1;
    }

//-----------------------------------------------------------------------------

void Count (int* balli, int* level, int* counter, Ball *b1, Ball *b2, Ball *b3, Ball *b4, Ball *b5, Ball *b6)
    {
    if ((*balli) % 500 == 0 && ((*balli) > (*counter)))
        {
        (*level) ++;
        *counter = *balli;

        b1->Level_game ();
        b2->Level_game ();
        b3->Level_game ();
        b4->Level_game ();
        b5->Level_game ();
        b6->Level_game ();
        }
    }

//-----------------------------------------------------------------------------

void CalculateBalli (Ball *b, Ball *b1, Ball *b2, Ball *b3, Ball *b4, Ball *b5, Ball *b6, int* balli)
    {
    double r_r1 = CalculateDistance (b, b1);
    double r_r2 = CalculateDistance (b, b2);
    double r_r3 = CalculateDistance (b, b3);
    double r_r4 = CalculateDistance (b, b4);
    double r_r5 = CalculateDistance (b, b5);
    double r_r6 = CalculateDistance (b, b6);

    if (r_r1 <= b->r + b1->r ||
        r_r2 <= b->r + b2->r ||
        r_r3 <= b->r + b3->r ||
        r_r4 <= b->r + b4->r ||
        r_r5 <= b->r + b5->r ||
        r_r6 <= b->r + b6->r)
        {
        b -> vx = 0;
        b -> vy = 0;

        *balli = *balli - 10;
        if (*balli < 0) *balli = 0;
        }
    else
        *balli = *balli + 1;
    }

//-----------------------------------------------------------------------------

double CalculateDistance (Ball *b1, Ball *b2)
    {
    double r_r = sqrt ((b1->y - b2->y) * (b1->y - b2->y) + (b1->x - b2->x) * (b1->x - b2->x));
    return r_r;
    }

//-----------------------------------------------------------------------------
