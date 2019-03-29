#include "TXLib.h"
#include <stdio.h>

const double Global_Sleep = txQueryPerformance () * 100;
const int Capture_Ball = 1;
const int Free    = 0;
const int N_Ball = 7;

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

void MoveBalls (char* name_user, int* continue_game);
void DrawBackground ();
void Count (int* balli, int* level, int* counter, Ball balls[]);
void CalculateBalli (Ball balls[], int* balli);
double CalculateDistance (Ball *b1, Ball *b2);
int ReadFromFile (int* balli, int* level, Ball balls[], char* name_user);
int WriteToFile (int* balli, int* level, Ball balls[], char* name_user);
int DialogueWithUser(char* name_user, int* continue_game);

//-----------------------------------------------------------------------------

int main ()
    {
    txCreateWindow (900, 700);

    char name_user[100] = "user";
    int continue_game = 0;
    DialogueWithUser(name_user, &continue_game);

    txBegin ();

    MoveBalls (name_user, &continue_game);

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

void MoveBalls (char* name_user, int* continue_game)
    {
    Ball balls[N_Ball] = {{320, 110, 0, 0, 20, RGB (0,   255, 50 ), RGB (0,   128, 0  ), 4},
                     {360, 150, 2, 2, 20, RGB (63,  72,  204), RGB (63,  0,   170), 6},
                     {390, 190, 3, 6, 20, RGB (128, 0,   255), RGB (128, 0,   255)   },
                     {420, 230, 4, 1, 20, RGB (128, 0,   64 ), RGB (170, 0,   85 ), 4},
                     {450, 260, 5, 7, 20, RGB (255, 255, 0  ), RGB (255, 255, 100), 5},
                     {490, 300, 3, 2, 20, RGB (255, 255, 255), RGB (255, 255, 255)   },
                     {510, 600, 2, 5, 20, RGB (240, 96,  0  ), RGB (255, 127, 39 ), 3}};

    int  balli = 0;
    int  level = 1;
    int  dt = 2;
    int  counter = 0;

    txSetTextAlign (TA_CENTER);

    if (*continue_game == 1) ReadFromFile (&balli, &level, balls, name_user);

    while (!txGetAsyncKeyState (VK_ESCAPE))
        {
        txSetFillColor (RGB (0, 0, 0));
        txClear ();

        DrawBackground ();

        balls[0].Drive ();

        Count (&balli, &level, &counter, balls);

        for (int i = 0; i < N_Ball; i++) balls[i].MoveStrategiya (dt);

        CalculateBalli (balls, &balli);

        for (int i = 0; i < N_Ball; i++) balls[i].Drow ();

        char print [100] = "";
        txSetColor (RGB(128, 255, 39), 10);
        sprintf (print, "����� ����� ������ = %d, ������� ���� %d       \r", balli, level);
        txTextOut (txGetExtentX()/2, 5, print);

        txSleep (Global_Sleep);
        }

    WriteToFile (&balli, &level, balls, name_user);

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

int ReadFromFile (int* balli, int* level, Ball balls[], char* name_user)
    {
    FILE *file_uzer = fopen (name_user, "r");

    if (file_uzer == NULL) return 1;

    if (fscanf (file_uzer, "����� = %d\n ������� ���� = %d", balli, level) != 2)
            {
            printf ("\n ������ ��� ������ ������ ��� ������ � ����� uzer.txt\n");

            fclose  (file_uzer);
            return 0;
            }

        for (int str = 3; !feof (file_uzer); str++)
            {
            int n = 0;

            if (fscanf (file_uzer, " [%d] ", &n) != 1)
                {
                printf ("\n ������ ��� ������ ������ ������ � ����� uzer.txt � ������ %d\n", str);
                break;
                }

            if (!(0 <= n && n < N_Ball))
                {
                printf ("\n �� ���������� ����� ������ %d � ����� uzer.txt � ������ %d\n", n, str);
                break;
                }

            if (fscanf (file_uzer, "x = %d, y = %d, vx = %d, vy = %d", &balls[n].x, &balls[n].y, &balls[n].vx, &balls[n].vy) != 4)
                {
                printf ("\n ������ ��� ������ ��������� ��� ��������� � ����� uzer.txt � ������ %d\n", str);
                break;
                }

            if (balls[n].x < 205) balls[n].x = 205;
            if (balls[n].x > 675) balls[n].x = 675;
            if (balls[n].y < 95 ) balls[n].y = 95;
            if (balls[n].y > 575) balls[n].y = 575;
            if (30 < balls[n].vx || balls[n].vx < -30) balls[n].vx = 3;
            if (30 < balls[n].vy || balls[n].vy < -30) balls[n].vy = 3;
            }

    fclose (file_uzer);

    return 1;
    }

//-----------------------------------------------------------------------------

int WriteToFile (int* balli, int* level, Ball balls[], char* name_user)
    {
    FILE *file_uzer = fopen (name_user, "w");

    if (file_uzer == NULL)
        {
        printf ("��������� ���� �� ��������");
        return 0;
        }

    fprintf (file_uzer, "����� = %d\n"
                        "������� ���� = %d", *balli, *level);

    for (int i = 0; i < N_Ball; i++)
        {
        fprintf (file_uzer, "\n[%d] ", i);
        fprintf (file_uzer, "x  = %d, y  = %d, ", balls[i].x,  balls[i].y);
        fprintf (file_uzer, "vx = %d, vy = %d",   balls[i].vx, balls[i].vy);
        }

    fclose  (file_uzer);

    return 1;
    }

//-----------------------------------------------------------------------------

int DialogueWithUser(char* name_user, int* continue_game)
    {
    printf ("\n������� ���� ���\n");
    scanf ("%90s", name_user);
    printf ("����������� ���� %s\n", name_user);

    strcat (name_user, ".txt");

    printf ("���� ������ ������ ���� ������, �����: 0, ���� ����������: 1\n");
    scanf ("%d", continue_game);

    if (*continue_game == 0)
        printf ("�������� ����� ����\n");
    else
        {
        if (*continue_game == 1)
            printf ("���������� ����\n");
        else
            {
            printf ("�� ���� �� ������ �������, �������� ���� � ������\n");

            *continue_game = 0;

            txSleep (Global_Sleep);
            txClearConsole ( );

            return 1;
            }
        }

    txSleep (Global_Sleep);
    txClearConsole ( );

    return 0;
    }
