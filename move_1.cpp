#include "TXLib.h"
#include <stdio.h>

const double Global_Sleep = txQueryPerformance () * 100;
const int Capture_Ball = 1;
const int Free    = 0;

//-----------------------------------------------------------------------------

struct Ball
    {
    int x, y;
    int vx, vy;
    int r;
    COLORREF color_contour, color_ball;
    int thickness_contour;
    int state_ball;

    void Drow ();
    void Drive ();
    void MoveStrategiya (int dt);
    void Level_game ();
    };

//-----------------------------------------------------------------------------

void MoveBalls ();
void DrawBackground ();
void Count (int* balli, int* level, int* counter, Ball balls[]);
void CalculateBalli (Ball balls[], int* balli);
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
    Ball balls[7] = {{320, 110, 0, 0, 20, RGB (0,   255, 50 ), RGB (0,   128, 0  ), 4},
                     {360, 150, 2, 2, 20, RGB (63,  72,  204), RGB (63,  0,   170), 6},
                     {390, 190, 3, 6, 20, RGB (128, 0,   255), RGB (128, 0,   255)   },
                     {420, 230, 4, 1, 20, RGB (128, 0,   64 ), RGB (170, 0,   85 ), 4},
                     {450, 260, 5, 7, 20, RGB (255, 255, 0  ), RGB (255, 255, 100), 5},
                     {490, 300, 3, 2, 20, RGB (255, 255, 255), RGB (255, 255, 255)   },
                     {510, 600, 2, 5, 20, RGB (240, 96,  0  ), RGB (255, 127, 39 ), 3}};

    int balli = 0;
    int level = 1;
    int dt = 2;
    int counter = 0;

    txSetTextAlign (TA_CENTER);

    FILE *file_uzer = fopen ("uzer.txt", "r");

    if (file_uzer != NULL)
        {
        fscanf (file_uzer, "Баллы = %d\n Уровень игры = %d\n"
                           "vx[0] = %d, vy[0] = %d\n"
                           "vx[1] = %d, vy[1] = %d\n"
                           "vx[2] = %d, vy[2] = %d\n"
                           "vx[3] = %d, vy[3] = %d\n"
                           "vx[4] = %d, vy[4] = %d\n"
                           "vx[5] = %d, vy[5] = %d\n"
                           "vx[6] = %d, vy[6] = %d\n"
                           "x[0] = %d, y[0] = %d\n"
                           "x[1] = %d, y[1] = %d\n"
                           "x[2] = %d, y[2] = %d\n"
                           "x[3] = %d, y[3] = %d\n"
                           "x[4] = %d, y[4] = %d\n"
                           "x[5] = %d, y[5] = %d\n"
                           "x[6] = %d, y[6] = %d\n",
                           &balli, &level,
                           &balls[0].vx, &balls[0].vy,
                           &balls[1].vx, &balls[1].vy,
                           &balls[2].vx, &balls[2].vy,
                           &balls[3].vx, &balls[3].vy,
                           &balls[4].vx, &balls[4].vy,
                           &balls[5].vx, &balls[5].vy,
                           &balls[6].vx, &balls[6].vy,
                           &balls[0].x, &balls[0].y,
                           &balls[1].x, &balls[1].y,
                           &balls[2].x, &balls[2].y,
                           &balls[3].x, &balls[3].y,
                           &balls[4].x, &balls[4].y,
                           &balls[5].x, &balls[5].y,
                           &balls[6].x, &balls[6].y);
        }

    fclose  (file_uzer);

    while (!txGetAsyncKeyState (VK_ESCAPE))
        {
        txSetFillColor (RGB (0, 0, 0));
        txClear ();

        DrawBackground ();

        balls[0].Drive ();

        Count (&balli, &level, &counter, balls);

        for (int i = 0; i < 7; i++) balls[i].MoveStrategiya (dt);

        CalculateBalli (balls, &balli);

        for (int i = 0; i < 7; i++) balls[i].Drow ();

        char print [100] = "";
        txSetColor (RGB(128, 255, 39), 10);
        sprintf (print, "Общая сумма баллов = %d, уровень игры %d       \r", balli, level);
        txTextOut (txGetExtentX()/2, 5, print);

        txSleep (Global_Sleep);
        }

    file_uzer = fopen ("uzer.txt", "w");

    if (file_uzer == NULL) printf ("Результат игры не сохранён");
    else
        {
        fprintf (file_uzer, "Баллы = %d\n"
                            "Уровень игры = %d\n", balli, level);
        for (int i = 0; i < 7; i++) fprintf (file_uzer, "vx[%d] = %d, vy[%d] = %d\n", i, balls[i].vx, i, balls[i].vy);
        for (int i = 0; i < 7; i++) fprintf (file_uzer, "x[%d] = %d, y[%d] = %d\n", i, balls[i].x, i, balls[i].y);
        }

    fclose  (file_uzer);
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

void Count (int* balli, int* level, int* counter, Ball balls[])
    {
    if ((*balli) % 500 == 0 && ((*balli) > (*counter)))
        {
        (*level) ++;
        *counter = *balli;

        for (int i = 1; i < 7; i++) balls[i].Level_game ();
        }
    }

//-----------------------------------------------------------------------------

void CalculateBalli (Ball balls[], int* balli)
    {
    for (int i = 1; i < 7; i++)
        {
        if (CalculateDistance (&balls[0], &balls[i]) <= balls[0].r + balls[i].r)
            {
            if (balls[0].state_ball == Free)
                {
                balls[0].vx = 0;
                balls[0].vy = 0;

                *balli = *balli - 10;
                if (*balli < 0) *balli = 0;
                }
            balls[0].state_ball = Capture_Ball;
            return;
            }
        }

    *balli = *balli + 1;
    balls[0].state_ball = Free;
    }

//-----------------------------------------------------------------------------

double CalculateDistance (Ball *b1, Ball *b2)
    {
    double r_r = sqrt ((b1->y - b2->y) * (b1->y - b2->y) + (b1->x - b2->x) * (b1->x - b2->x));
    return r_r;
    }

//-----------------------------------------------------------------------------
