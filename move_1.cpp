#include "TXLib.h"
#include <stdio.h>
#include "R_W_Color_in_from_file.h"

const double GLOBAL_SLEEP = txQueryPerformance () * 100;

const int CAPTURE_BALL = 1;
const int FREE_BALL    = 0;

const int N_BALLS = 7;

const int BUTTON_USERNAME        = 0;
const int BUTTON_COLOR_RED       = 2;
const int BUTTON_COLOR_GREEN     = 3;
const int BUTTON_COLOR_BLUE      = 4;
const int BUTTON_RADIUS_BALLS_25 = 5;
const int BUTTON_RADIUS_BALLS_30 = 6;

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

struct Button
    {
    RECT area;
    COLORREF color;
    char text[50];

    void Drow_Button ();
    };

//-----------------------------------------------------------------------------

void     MoveBalls                (char* name_user, int* continue_game, COLORREF* ball_0_color, int* r_ball, int* sign_color_change);
void     DrawBackground           ();
void     Count                    (int* balli, int* level, int* counter, Ball balls[]);
void     CalculateBalli           (Ball balls[], int* balli);
double   CalculateDistance        (Ball *b1, Ball *b2);

int      ReadFromFile             (int* balli, int* level, Ball balls[], char* name_user);
int      WriteToFile              (int* balli, int* level, Ball balls[], char* name_user);

int      Menu_test2               (Button buttons[], int N_Button);

int      DialogueWithUser_Username(char* name_user, int* continue_game);

//---
void     Menu                     (char* name_user, int* continue_game, COLORREF* ball_0_color);
void     Menu_test                (char* name_user, int* continue_game, COLORREF* ball_0_color);
//--

int      Pause                    ();
bool     In_area                  (POINT mouse_pos, RECT area);
void     Rect_Area_Button         (RECT area, COLORREF color, const char text[]);

//-----------------------------------------------------------------------------

int main ()
    {
    txCreateWindow (900, 700);

    //const int N_Button = 5;

    Button buttons[] = {{{180, 70,  365, 115}, RGB (255, 255, 128), "Username"      },
                        {{400, 70,  585, 115}, RGB (0  , 0  , 0  ), "Options balls:"},
                        {{400, 125, 585, 170}, RGB (255, 0,   0  ), "red"           },
                        {{400, 180, 585, 225}, RGB (0,   255, 0  ), "green"         },
                        {{400, 235, 585, 280}, RGB (0,   0,   255), "blue"          },
                        {{400, 290, 585, 335}, RGB (255, 255, 128), "radius 25"     },
                        {{400, 345, 585, 390}, RGB (255, 255, 128), "radius 30"     },
                        {{620, 70,  805, 115}, RGB (255, 255, 128), "Game Start"    }};

    char name_user[100] = "user";
    int continue_game = 0;
    int r_ball = 20;
    COLORREF ball_0_color = RGB (0, 128, 0);
    int sign_color_change = 0;

    //Menu (name_user, &continue_game, &ball_0_color);

    txBegin ();

    while (true)
        {
        int pressed_buttons = Menu_test2 (buttons, sizeof (buttons) / sizeof (buttons[0]));

        switch (pressed_buttons)
            {
            case BUTTON_USERNAME:
                txUpdateWindow (true);
                DialogueWithUser_Username(name_user, &continue_game);
                txUpdateWindow (false);
                break;

            case BUTTON_COLOR_RED:
                ball_0_color = RGB (255, 0, 0);
                sign_color_change = 1;
                printf ("red\n");
                txSetFillColor (TX_BLACK);
                txClear ();
                break;

            case BUTTON_COLOR_GREEN:
                ball_0_color = RGB (0, 255, 0);
                sign_color_change = 1;
                printf ("green\n");
                txSetFillColor (TX_BLACK);
                txClear ();
                break;

            case BUTTON_COLOR_BLUE:
                ball_0_color = RGB (0, 0, 255);
                sign_color_change = 1;
                printf ("blue\n");
                txSetFillColor (TX_BLACK);
                txClear ();
                break;

            case BUTTON_RADIUS_BALLS_25:
                r_ball = 25;
                printf ("radius balls = 25\n");
                txSetFillColor (TX_BLACK);
                txClear ();
                break;

            case BUTTON_RADIUS_BALLS_30:
                r_ball = 30;
                printf ("radius balls = 30\n");
                txSetFillColor (TX_BLACK);
                txClear ();
                break;

            default:
                break;
            }

        if (pressed_buttons == 7) break;
        }

    MoveBalls (name_user, &continue_game, &ball_0_color, &r_ball, &sign_color_change);

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

void MoveBalls (char* name_user, int* continue_game, COLORREF* ball_0_color, int* r_ball, int* sign_color_change)
    {
    Ball balls[N_BALLS] = {{320, 110, 0, 0, *r_ball, *ball_0_color,       *ball_0_color,       4},
                          {360, 150, 2, 2, *r_ball, RGB (63,  72,  204), RGB (63,  0,   170), 6},
                          {390, 190, 3, 6, *r_ball, RGB (128, 0,   255), RGB (128, 0,   255)   },
                          {420, 230, 4, 1, *r_ball, RGB (128, 0,   64 ), RGB (170, 0,   85 ), 4},
                          {450, 260, 5, 7, *r_ball, RGB (255, 255, 0  ), RGB (255, 255, 100), 5},
                          {490, 300, 3, 2, *r_ball, RGB (255, 255, 255), RGB (255, 255, 255)   },
                          {510, 600, 2, 5, *r_ball, RGB (240, 96,  0  ), RGB (255, 127, 39 ), 3}};

    int  balli = 0;
    int  level = 1;
    int  dt = 2;
    int  counter = 0;

    txSetTextAlign (TA_CENTER);

    if (*continue_game == 1)
        {
        ReadFromFile (&balli, &level, balls, name_user);
        if (*sign_color_change == 1)
            {
            balls[0].color_ball    = *ball_0_color;
            balls[0].color_contour = *ball_0_color;
            }
        }

    while (!txGetAsyncKeyState (VK_ESCAPE))
        {
        txSetFillColor (RGB (0, 0, 0));
        txClear ();

        DrawBackground ();

        balls[0].Drive ();

        Count (&balli, &level, &counter, balls);

        for (int i = 0; i < N_BALLS; i++) balls[i].MoveStrategiya (dt);

        CalculateBalli (balls, &balli);

        for (int i = 0; i < N_BALLS; i++) balls[i].Drow ();

        char print [100] = "";
        txSetColor (RGB(128, 255, 39), 10);
        sprintf (print, "����� ����� ������ = %d, ������� ���� %d       \r", balli, level);
        txTextOut (txGetExtentX()/2, 5, print);

        txSleep (GLOBAL_SLEEP);
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

    if (this->x >= (695 - r))   this->vx = -this->vx,   this->x = (695 - r);
    if (this->y >= (595 - r))   this->vy = -this->vy,   this->y = (595 - r);
    if (this->x <= (185 + r))   this->vx = -this->vx,   this->x = (185 + r);
    if (this->y <= (75  + r))   this->vy = -this->vy,   this->y = (75  + r);
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
            if (balls[0].state_ball == FREE_BALL)
                {
                balls[0].vx = 0;
                balls[0].vy = 0;

                *balli = *balli - 10;
                if (*balli < 0) *balli = 0;
                }
            balls[0].state_ball = CAPTURE_BALL;
            return;
            }
        }

    *balli = *balli + 1;
    balls[0].state_ball = FREE_BALL;
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

    if (fscanf (file_uzer, "����� = %d\n ������� ���� = %d\n", balli, level) != 2)
            {
            printf ("\n ������ ��� ������ ������ ��� ������ � ����� uzer.txt\n");

            fclose  (file_uzer);
            return 0;
            }

    for (int str = 3; !feof (file_uzer); str++)
            {
            int n = -1;

            if (fscanf (file_uzer, " [%d] ", &n) != 1)
                {
                printf ("\n ������ ��� ������ ������ ������ (%d) � ����� uzer.txt � ������ %d\n", n, str);
                break;
                }

            if (!(0 <= n && n < N_BALLS))
                {
                printf ("\n �� ���������� ����� ������ %d � ����� uzer.txt � ������ %d\n", n, str);
                break;
                }

            if (fscanf (file_uzer, "x = %d, y = %d, vx = %d, vy = %d, ", &balls[n].x, &balls[n].y, &balls[n].vx, &balls[n].vy) != 4)
                {
                printf ("\n ������ ��� ������ ��������� ��� ��������� � ����� uzer.txt � ������ %d\n", str);
                break;
                }

            if (n == 0)
                {
                balls[0].color_ball = ReadFromFile_Color (file_uzer);
                balls[0].color_contour = balls[0].color_ball;
                }
            else ReadFromFile_Color (file_uzer);

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
        printf ("��������� ���� �� �������");
        return 0;
        }

    fprintf (file_uzer, "����� = %d\n"
                        "������� ���� = %d", *balli, *level);

    for (int i = 0; i < N_BALLS; i++)
        {
        fprintf (file_uzer, "\n[%d] ", i);
        fprintf (file_uzer, "x  = %4d, y  = %4d, ", balls[i].x,  balls[i].y);
        fprintf (file_uzer, "vx = %4d, vy = %4d,",   balls[i].vx, balls[i].vy);
        WriteToFile_Color (balls[i].color_ball, file_uzer);
        }

    fclose  (file_uzer);

    return 1;
    }

//-----------------------------------------------------------------------------

int DialogueWithUser_Username(char* name_user, int* continue_game)
    {
    printf ("\n\n\n\n\n\n\n����� ���� ���\n");
    scanf ("%90s", name_user);
    printf ("����������� ���� %s\n", name_user);

    strcat (name_user, ".txt");

    printf ("���� ������ ������ ���� ������, �����: 0, ���� ����������: 1\n");
    scanf ("%d", continue_game);

    if (*continue_game == 0)
        printf ("����� �������� ����� ����\n\n");
    else
        {
        if (*continue_game == 1)
            printf ("���� ����� ����������\n\n");
        else
            {
            printf ("�� ���� �� ������ �������, �������� ���� � ������\n\n");

            *continue_game = 0;

            txSleep (GLOBAL_SLEEP);
            txClearConsole ( );

            return 1;
            }
        }

    Pause ();
    txSleep (GLOBAL_SLEEP);
    txClearConsole ( );

    return 0;
    }
//-----------------------------------------------------------------------------
int Pause ()
    {
    while (!txGetAsyncKeyState (VK_SPACE))
        {
        txTextCursor (false);
        printf ("��� ����������� ������ � ����, ����� ������\r");
        }
    return 0;
    }

//-----------------------------------------------------------------------------
void Menu (char* name_user, int* continue_game, COLORREF* ball_0_color)
    {
    int button_status = 0;
    txSelectFont ("Comic Sans MS", 40);

    RECT area_start      = {620, 70, 805, 115};
    RECT area_name_user  = {180, 70, 365, 115};
    RECT area_ball_color = {400, 70, 585, 115};

    RECT area_red   = {400, 125, 585, 170};
    RECT area_green = {400, 180, 585, 225};
    RECT area_blue  = {400, 235, 585, 280};

    txBegin ();

    while (true)
        {
        txSetColor     (TX_ORANGE, 2);
        txSetFillColor (RGB (255, 255, 128));

        txRectangle (180, 70, 365, 115);
        txRectangle (400, 70, 585, 115);
        txRectangle (620, 70, 805, 115);

        txTextOut (200, 70, "Username");
        txTextOut (426, 70, "Ball Color");
        txTextOut (642, 70, "Game Start");

        POINT mouse_pos = txMousePos();

        txSleep (GLOBAL_SLEEP);

        if (txMouseButtons() != 1) continue;

        if (In_area (mouse_pos, area_start)) break;
        //(In_area (mouse_pos, buttons[i].area))

        if (In_area (mouse_pos, area_name_user))
            {
            txUpdateWindow (true);
            DialogueWithUser_Username(name_user, continue_game);
            txUpdateWindow (false);
            }

        if (In_area (mouse_pos, area_ball_color))
            {
            button_status = 1;

            txSetFillColor (RGB (255, 0, 0));
            txRectangle (400, 125, 585, 170);
            txTextOut (465, 125, "red");

            txSetFillColor (RGB (0, 255, 0));
            txRectangle (400, 180, 585, 225);
            txTextOut (458, 180, "green");

            txSetFillColor (RGB (0, 0, 255));
            txRectangle (400, 235, 585, 280);
            txTextOut (463, 235, "blue");
            }

        if (button_status == 1 && (In_area (mouse_pos, area_red)))
            {
            *ball_0_color = RGB (255, 0, 0);
            printf ("red\n");
            txSetFillColor (TX_BLACK);
            txClear ();
            button_status = 0;
            }

        if (button_status == 1 && (In_area (mouse_pos, area_green)))
            {
            *ball_0_color = RGB (0, 255, 0);
            printf ("green\n");
            txSetFillColor (TX_BLACK);
            txClear ();
            button_status = 0;
            }

        if (button_status == 1 && (In_area (mouse_pos, area_blue)))
            {
            *ball_0_color = RGB (0, 0, 255);
            printf ("blue\n");
            txSetFillColor (TX_BLACK);
            txClear ();
            button_status = 0;
            }
        }

    txEnd ();

    txClearConsole ( );
    }

//-----------------------------------------------------------------------------

void Menu_test (char* name_user, int* continue_game, COLORREF* ball_0_color)
    {
    txSelectFont ("Comic Sans MS", 40);

    RECT area_start      = {620, 70, 805, 115};
    RECT area_name_user  = {180, 70, 365, 115};
    RECT area_red        = {400, 125, 585, 170};
    RECT area_green      = {400, 180, 585, 225};
    RECT area_blue       = {400, 235, 585, 280};

    txBegin ();

    while (true)
        {
        txSetColor     (TX_ORANGE, 2);
        txSetFillColor (RGB (255, 255, 128));

        Rect_Area_Button (area_name_user, RGB (255, 255, 128), "Username");
        Rect_Area_Button (area_start,     RGB (255, 255, 128), "Game Start");
        Rect_Area_Button (area_red,       RGB (255, 0,   0),   "red");
        Rect_Area_Button (area_green,     RGB (0,   255, 0),   "green");
        Rect_Area_Button (area_blue,      RGB (0,   0,   255), "blue");

        POINT mouse_pos = txMousePos();

        txSleep (GLOBAL_SLEEP);

        if (txMouseButtons() != 1) continue;

        if (In_area (mouse_pos, area_start)) break;

        if (In_area (mouse_pos, area_name_user))
            {
            txUpdateWindow (true);
            DialogueWithUser_Username(name_user, continue_game);
            txUpdateWindow (false);
            }

        if (In_area (mouse_pos, area_red))
            {
            *ball_0_color = RGB (255, 0, 0);
            printf ("red\n");
            txSetFillColor (TX_BLACK);
            txClear ();
            }

        if (In_area (mouse_pos, area_green))
            {
            *ball_0_color = RGB (0, 255, 0);
            printf ("green\n");
            txSetFillColor (TX_BLACK);
            txClear ();
            }

        if (In_area (mouse_pos, area_blue))
            {
            *ball_0_color = RGB (0, 0, 255);
            printf ("blue\n");
            txSetFillColor (TX_BLACK);
            txClear ();
            }
        }

    txEnd ();

    txClearConsole ( );
    }

//-----------------------------------------------------------------------------
int Menu_test2 (Button buttons[], int N_Button)
    {
    int button_pressed = -1;
    txSelectFont ("Comic Sans MS", 40);

    txBegin ();

    while (true)
        {
        txSetColor (TX_ORANGE, 2);

        for (int i = 0; i < N_Button; i++) buttons[i].Drow_Button ();

        POINT mouse_pos = txMousePos();

        txSleep (GLOBAL_SLEEP);

        if (txMouseButtons() != 1) continue;

        for (int i = 0; i < N_Button; i++)
            if (In_area (mouse_pos, buttons[i].area))
                 {
                 printf ("������ ����� %d\n", i);
                 button_pressed = i;

                 txEnd ();

                 txClearConsole ( );

                 return button_pressed;
                 }
        }
    }


//-----------------------------------------------------------------------------

void Button::Drow_Button ()
    {
    txSetFillColor (this->color);
    txRectangle (this->area.left, this->area.top, this->area.right, this->area.bottom);

    int centre = (this->area.right + this->area.left)/2;
    txSetTextAlign (TA_CENTER);
    txTextOut (centre, this->area.top, this->text);
    }

//-----------------------------------------------------------------------------

void Rect_Area_Button (RECT area, COLORREF color, const char text[])
    {
    txSetFillColor (color);
    txRectangle (area.left, area.top, area.right, area.bottom);

    int centre = (area.right + area.left)/2;
    txSetTextAlign (TA_CENTER);
    txTextOut (centre, area.top, text);
    }

//-----------------------------------------------------------------------------
bool In_area (POINT mouse_pos, RECT area)
    {
    return ((area.left <= mouse_pos.x) && (mouse_pos.x <= area.right ) &&
            (area.top  <= mouse_pos.y) && (mouse_pos.y <= area.bottom));
    }
