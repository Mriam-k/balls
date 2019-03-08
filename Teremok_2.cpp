#include "TXLib.h"

const double Global_Sleep = txQueryPerformance () * 100;
const double Window_X = GetSystemMetrics (SM_CXSCREEN);
const double Window_Y = GetSystemMetrics (SM_CYSCREEN);

//-----------------------------------------------------------------------------

// прототипы функций
void Pause ();
void DrawBackground ();
void DrawGrass_foundation (int x, int y, int move_x);
void MoveGrass    (int move_x);
void DrawSun      ();
void DrawCloud    (int x, int y, double size = 1,   COLORREF cvetTucha = RGB (255, 255, 255));
void DrawHouse    (int x, int y, double size = 1,   COLORREF lightWindow = RGB (255, 255, 185));
void DrawMouse    (int x, int y, double size_x = 1, double size_y = 1, int tail = 0, int nose = 0, int mustache = 0, int head = 0, int eyeR = 0, int eyeL = 0, COLORREF bodyColor = RGB (204, 156, 130));
void DrawFrog     (int x, int y, double size = 1,   int shoulderL = 0, int shoulderR = 0, int forearmL = 0, int forearmR = 0, int handL = 0, int handR = 0, int hipL = 0, int hipR = 0, int shinL = 0, int shinR = 0, int footL = 0, int footR = 0, int tummy = 0, int lips = 1, int eyeL = 0, int eyeR = 0);
void DrawHeadFrog (int x, int y, double size = 1, int lips = 1, int eyeL = 0, int eyeR = 0);
void DrawRabbit   (int x, int y, double size_x = 1, double size_y = 1, double earsL = 0, double earsR = 0, double nose = 0, double eye = 0, double mustache = 0, double paw = 0, double tail = 0, double legs = 0);
void DrawFox      (int x, int y, double size_x = 1, double size_y = 1, int tail = 0, int ears = 0, int nose = 0, int eyes = 0);
void DrawWolf     (int x, int y, double size = 1,   int tail = 0, int jaw = 0, int eye = 0, int nose = 0, int ears = 0);
void DrawBear     ();
void MoveCaptions_first  ();
void MoveAuthor_speech   ();
void MoveMouse_in_field  ();
void MoveMouse_in_house  ();
void RechMouse           ();
void MoveFrog_in_field   ();
void RechFrog            ();
void MoveFrog_in_house   ();
void MoveRabbit_in_field ();
void RechRabbit ();
void MoveRabbit_in_house ();
void MoveFox_in_field    ();
void RechFox             ();
void MoveFox_in_house    ();
void MoveWolf_in_field   ();
void RechWolf            ();

void MoveCaptions_end    ();

//-----------------------------------------------------------------------------

int main ()
    {
    //double speed = txQueryPerformance ();
    //printf ("скорость данного компьютера = %lf", speed);
    //return 0;

    txCreateWindow (Window_X, Window_Y);

    txBegin ();

    MoveCaptions_first ();

    MoveAuthor_speech ();

    MoveMouse_in_field ();
    RechMouse          ();
    MoveMouse_in_house ();

    MoveFrog_in_field ();
    RechFrog          ();
    MoveFrog_in_house ();

    MoveRabbit_in_field ();
    RechRabbit          ();
    MoveRabbit_in_house ();

    MoveFox_in_field ();
    RechFox          ();
    MoveFox_in_house ();

    MoveWolf_in_field ();
    RechWolf          ();

    MoveCaptions_end ();

    txEnd ();

    return 0;
    }

// Определения функций:
//-----------------------------------------------------------------------------

void DrawBackground ()
    {
    txSetColor (TX_ORANGE, 2);
    txSetFillColor (RGB (145, 200, 255));
    txRectangle (2, 2, 1448, 778);

    txSetColor (RGB (164, 255, 72));
    txArc (2,    380, 100,  490, 0, 180);
    txArc (100,  380, 300,  490, 0, 180);
    txArc (300,  380, 600,  490, 0, 180);
    txArc (600,  380, 1200, 490, 0, 180);
    txArc (1200, 380, 1350, 490, 0, 180);
    txArc (1350, 380, 1446, 490, 0, 180);

    txSetFillColor (RGB (164, 255, 72));
    txFloodFill (50, 750);
    }

//-----------------------------------------------------------------------------

void MoveGrass (int move_x)
    {
    int x = 50;

    while (x <= 1450)
        {
        DrawGrass_foundation (x, 450, move_x);
        DrawGrass_foundation (x, 650, move_x);
        DrawGrass_foundation (x, 850, move_x);

        x = x + 200;
        }
    }

//-----------------------------------------------------------------------------

void DrawGrass_foundation (int x, int y, int move_x)
    {
    txSetColor (RGB (0, 176, 45), 2);

    txLine (x,        y,        (x + move_x),             y - 20);
    txLine (x,        y,        (x + move_x) - 5,         y - 15);
    txLine (x,        y,        (x + move_x) + 8,         y - 25);

    txLine (x + 100,  y,        (x + move_x) + 100,       y - 20);
    txLine (x + 100,  y,        (x + move_x) + 100  - 5,  y - 15);
    txLine (x + 100,  y,        (x + move_x) + 100  + 8,  y - 25);

    txLine (x + 50,   y + 100,  (x + move_x) + 50,        y + 100 - 20);
    txLine (x + 50,   y + 100,  (x + move_x) + 50   - 5,  y + 100 - 15);
    txLine (x + 50,   y + 100,  (x + move_x) + 50   + 8,  y + 100 - 25);

    txLine (x + 150,  y + 100,  (x + move_x) + 150,       y + 100 - 20);
    txLine (x + 150,  y + 100,  (x + move_x) + 150  - 5,  y + 100 - 15);
    txLine (x + 150,  y + 100,  (x + move_x) + 150  + 8,  y + 100 - 25);
    }

//-----------------------------------------------------------------------------

void DrawSun ()
    {
    txSetColor     (TX_ORANGE);
    txSetFillColor (TX_ORANGE);
    txCircle (35, 35, 30);

    POINT ray1[3] = {{34, 120}, {27, 68}, {42, 68}};
    txPolygon (ray1, 3);
    POINT ray2[3] = {{55, 62},  {64, 53}, {98, 98}};
    txPolygon (ray2, 3);
    POINT ray3[3] = {{68, 28},  {68, 42}, {120, 35}};
    txPolygon (ray3, 3);
    }

//-----------------------------------------------------------------------------

void DrawHouse (int x, int y, double size, COLORREF lightWindow)
    {
    txRectangle (x, y - 151 * size, x + 200 * size, y);
    txSetFillColor (RGB(204, 156, 130));
    txFloodFill (x + 60 * size, y - 120 * size);

    txSetFillColor (RGB (183, 117, 81));
    txSetColor     (RGB (183, 117, 81));
    txCircle (x,               y - 140 * size,  12 * size);
    txCircle (x,               y - 118 * size,  12 * size);
    txCircle (x,               y - 96  * size,  12 * size);
    txCircle (x,               y - 74  * size,  12 * size);
    txCircle (x,               y - 52  * size,  12 * size);
    txCircle (x,               y - 30  * size,  12 * size);
    txCircle (x,               y - 8   * size,  12 * size);
    txCircle (x + 200 * size,  y - 140 * size,  12 * size);
    txCircle (x + 200 * size,  y - 118 * size,  12 * size);
    txCircle (x + 200 * size,  y - 96  * size,  12 * size);
    txCircle (x + 200 * size,  y - 74  * size,  12 * size);
    txCircle (x + 200 * size,  y - 52  * size,  12 * size);
    txCircle (x + 200 * size,  y - 30  * size,  12 * size);
    txCircle (x + 200 * size,  y - 8   * size,  12 * size);


    txSetFillColor (RGB (123, 77, 51));
    POINT krisha[3] = {{x,                       y - ROUND (151 * size)},
                       {x + ROUND (200 * size),  y - ROUND (151 * size)},
                       {x + ROUND (100 * size),  y - ROUND (221 * size)}};
    txPolygon (krisha, 3);


    txSetFillColor (lightWindow);
    txCircle    (x + 100 * size, y - 186 * size, 15 * size);
    txRectangle (x + 75 * size,  y - 80 * size,  x + 125 * size, y - 40 * size);
    txLine      (x + 95 * size,  y - 80 * size,  x + 95 * size,  y - 40 * size);
    txLine      (x + 95 * size,  y - 65 * size,  x + 75 * size,  y - 65 * size);
    }

//-----------------------------------------------------------------------------

void DrawMouse (int x,    int y,    double size_x, double size_y,    int tail, int nose, int mustache,
                int head, int eyeR, int eyeL,      COLORREF bodyColor)
    {
    txSetFillColor (bodyColor);
    txSetColor     (bodyColor);


    POINT mouseBody[3] = {{x + ROUND (15 * size_x),        y - ROUND (70 * size_y)},
                          {x - ROUND (20 * size_x),        y                      },
                          {x + ROUND (40 * size_x),        y + ROUND (10 * size_y)}};
    txPolygon (mouseBody, 3);
    POINT mouseHead[3] = {{x + head,                       y - ROUND (75 * size_y)},
                          {x + ROUND (40 * size_x + head), y - ROUND (100 * size_y)},
                          {x + ROUND (40 * size_x + head), y - ROUND (55 * size_y)}};
    txPolygon (mouseHead, 3);


    // ушки
    txCircle (x - 11 * size_x + head, y - 79  * size_y,  12 * size_x);
    txCircle (x + 38 * size_x + head, y - 111 * size_y,  12 * size_x);

    // внутренние ушки
    txSetFillColor (RGB(255, 174, 201));
    txCircle (x - 8  * size_x + head,  y - 79  * size_y,  7 * size_x);
    txCircle (x + 38 * size_x + head,  y - 108 * size_y,  7 * size_x);

    // глазки
    txSetFillColor (RGB (0, 0, 130));
    txCircle (x + 15 * size_x + head, y - 78 * size_y, 4 * size_x + eyeR);
    txCircle (x + 29 * size_x + head, y - 87 * size_y, 4 * size_x + eyeL);

    // усики
    txSetColor (RGB (136, 0, 21));
    txLine (x + 40 * size_x + head, y - 55 * size_y, x + 60 * size_x, y - 75 * size_y + mustache);
    txLine (x + 40 * size_x + head, y - 55 * size_y, x + 60 * size_x, y - 65 * size_y + mustache);
    txLine (x + 40 * size_x + head, y - 55 * size_y, x + 20 * size_x, y - 55 * size_y + mustache);
    txLine (x + 40 * size_x + head, y - 55 * size_y, x + 20 * size_x, y - 40 * size_y + mustache);

    // носик
    txSetColor     (RGB (183, 117, 81));
    txSetFillColor (RGB (183, 117, 81));
    txCircle (x + 40 * size_x + head, y - 55 * size_y, 4 * size_x + nose);

    // хвост
    txSetColor (bodyColor, 3);
    txLine (x - 12 * size_x, y - 20 * size_y, x - 40 * size_x, y - 35 * size_y + tail);
    }

//-----------------------------------------------------------------------------

void DrawFrog (int x,     int y,     double size,  int shoulderL, int shoulderR, int forearmL, int forearmR,
               int handL, int handR, int hipL,     int hipR,      int shinL,     int shinR,
               int footL, int footR, int tummy,    int lips,      int eyeL,      int eyeR)
    {
    txSetFillColor (RGB (0, 196, 0));
    txSetColor     (RGB (0, 196, 0));
    POINT FrogHead[4] = {{x + ROUND (80 * size),  y - ROUND (130 * size)},
                         {x + ROUND (105 * size), y - ROUND (110 * size)},
                         {x + ROUND (80 * size),  y - ROUND (90 * size)},
                         {x + ROUND (55 * size),  y - ROUND (110 * size)}};
    txPolygon (FrogHead, 4);


    // туловище
    txCircle (x + 80 * size, y - 64 * size, 27 * size);

    txSetColor     (RGB (0, 196, 0), 3);


    // лапка верхняя слева
    txLine               (x + 58 * size,                             y - 80 * size,
                          x + 30 * size + shoulderL,                 y - 52 * size + shoulderL);
    txLine               (x + 30 * size + shoulderL,                 y - 52 * size + shoulderL,
                          x + 20 * size + forearmL,                  y - 65 * size + forearmL);
    POINT FrogArm1[3] = {{x + ROUND (20 * size) + forearmL,          y - ROUND (65 * size) + forearmL},
                         {x + ROUND (8 * size) + forearmL + handL,   y - ROUND (55 * size) + forearmL + handL},
                         {x + ROUND (12 * size) + forearmL + handL,  y - ROUND (77 * size) + forearmL + handL}};
    txPolygon (FrogArm1, 3);


    // лапка верхняя справа
    txLine               (x + 83 * size,                             y - 80 * size,
                          x + 136 * size + shoulderR,                y - 74 * size + shoulderR);
    txLine               (x + 136 * size + shoulderR,                y - 74 * size + shoulderR,
                          x + 140 * size + forearmR,                 y - 85 * size + forearmR);
    POINT FrogArm2[3] = {{x + ROUND (140 * size) + forearmR,         y - ROUND (85 * size) + forearmR},
                         {x + ROUND (154 * size) + forearmR + handR, y - ROUND (90 * size) + forearmR + handR},
                         {x + ROUND (140 * size) + forearmR + handR, y - ROUND (102 * size) + forearmR + handR}};
    txPolygon (FrogArm2, 3);


    // лапка нижняя справа
    txLine               (x + 83 * size,                  y - 48 * size,
                          x + 136 * size + hipR,          y - 40 * size + hipR);
    txLine               (x + 136 * size + hipR,          y - 40 * size + hipR,
                          x + 140 * size + shinR,         y - 20 * size + shinR);
    POINT FrogLeg1[3] = {{x + ROUND (140 * size) + shinR, y - ROUND (20 * size) + shinR},
                         {x + ROUND (159 * size) + footR, y - ROUND (20 * size) + footR},
                         {x + ROUND (142 * size) + footR, y - ROUND (12 * size) + footR}};
    txPolygon (FrogLeg1, 3);


    // лапка нижняя слева
    txLine               (x + 58 * size,                  y - 48 * size,
                          x + 9 * size + hipL,            y - 30 * size + hipL);
    txLine               (x + 9 * size + hipL,            y- 30 * size + hipL,
                          x + 13 * size + shinL,          y - 10 * size + shinL);
    POINT FrogLeg2[3] = {{x + ROUND (13 * size) + shinL,  y - ROUND (10 * size) + shinL},
                         {x + footL,                      y + footL},
                         {x - ROUND (3 * size) + footL,   y - ROUND (20 * size) + footL}};
    txPolygon (FrogLeg2, 3);


    txSetColor     (RGB (0, 196, 0));

    // животик
    txSetFillColor (RGB (60, 255, 108));
    txCircle (x + 80 * size + tummy,  y - 60 * size + tummy,  14 * size);
    txSetFillColor (RGB (0, 196, 0));
    txCircle (x + 80 * size + tummy,  y - 60 * size + tummy,  2 * size);

    // губы
    txSetFillColor (RGB (255, 4, 4));
    POINT FrogLips[4] = {{x + ROUND (80 * size), y - ROUND (111 * size)},
                         {x + ROUND (90 * size), y - ROUND (107 * size)},
                         {x + ROUND (80 * size), y - ROUND (103 * size)},
                         {x + ROUND (70 * size), y - ROUND (107 * size)}};
    txPolygon (FrogLips, 4);
    txSetFillColor (RGB (0, 196, 0));
    txSetColor     (RGB (0, 196, 0), lips);
    txLine (x + ROUND (90 * size), y - ROUND (107 * size), x + ROUND (70 * size), y - ROUND (107 * size));
    txSetColor     (RGB (0, 196, 0));

    // носик
    txSetFillColor (RGB(79, 79, 0));
    txCircle (x + 83 * size, y - 113 * size, 3 * size);
    txCircle (x + 77 * size, y - 113 * size, 3 * size);

    // глазки
    txSetFillColor (RGB (0, 196, 0));
    txCircle (x + 92 * size,        y - 131 * size, 9 * size);
    txCircle (x + 68 * size,        y - 131 * size, 9 * size);
    txLine   (x + 92 * size,        y - 122 * size, x + 99 * size,  y - 156 * size);
    txLine   (x + 92 * size,        y - 122 * size, x + 107 * size, y - 156 * size);
    txLine   (x + 68 * size,        y - 122 * size, x + 60 * size,  y - 156 * size);
    txLine   (x + 68 * size,        y - 122 * size, x + 52 * size,  y - 156 * size);
    txSetFillColor (RGB (0, 54, 108));
    txCircle (x + 91 * size + eyeR, y - 128 * size, 6.5 * size);
    txCircle (x + 68 * size + eyeL, y - 128 * size, 6.5 * size);
    }

//-----------------------------------------------------------------------------

void DrawHeadFrog (int x, int y, double size, int lips, int eyeL, int eyeR)
    {
    txSetFillColor (RGB (0, 196, 0));
    txSetColor     (RGB (0, 196, 0));
    POINT FrogHead[4] = {{x + ROUND (80 * size),  y - ROUND (130 * size)},
                         {x + ROUND (105 * size), y - ROUND (110 * size)},
                         {x + ROUND (80 * size),  y - ROUND (90 * size)},
                         {x + ROUND (55 * size),  y - ROUND (110 * size)}};
    txPolygon (FrogHead, 4);

    // губы
    txSetFillColor (RGB (255, 4, 4));
    POINT FrogLips[4] = {{x + ROUND (80 * size), y - ROUND (111 * size)},
                         {x + ROUND (90 * size), y - ROUND (107 * size)},
                         {x + ROUND (80 * size), y - ROUND (103 * size)},
                         {x + ROUND (70 * size), y - ROUND (107 * size)}};
    txPolygon (FrogLips, 4);
    txSetFillColor (RGB (0, 196, 0));
    txSetColor     (RGB (0, 196, 0), lips);
    txLine (x + ROUND (90 * size), y - ROUND (107 * size), x + ROUND (70 * size), y - ROUND (107 * size));
    txSetColor     (RGB (0, 196, 0));

    // носик
    txSetFillColor (RGB(79, 79, 0));
    txCircle (x + 83 * size, y - 113 * size, 3 * size);
    txCircle (x + 77 * size, y - 113 * size, 3 * size);

    // глазки
    txSetFillColor (RGB (0, 196, 0));
    txCircle (x + 92 * size,        y - 131 * size, 9 * size);
    txCircle (x + 68 * size,        y - 131 * size, 9 * size);
    txLine   (x + 92 * size,        y - 122 * size, x + 99 * size,  y - 156 * size);
    txLine   (x + 92 * size,        y - 122 * size, x + 107 * size, y - 156 * size);
    txLine   (x + 68 * size,        y - 122 * size, x + 60 * size,  y - 156 * size);
    txLine   (x + 68 * size,        y - 122 * size, x + 52 * size,  y - 156 * size);
    txSetFillColor (RGB (0, 54, 108));
    txCircle (x + 91 * size + eyeR, y - 128 * size, 6.5 * size);
    txCircle (x + 68 * size + eyeL, y - 128 * size, 6.5 * size);
    }


//-----------------------------------------------------------------------------

void DrawRabbit (int x, int y, double size_x, double size_y, double earsL, double earsR, double nose, double eye, double mustache,
                 double paw,   double tail, double legs)
    {
    // ушки
    txSetFillColor (RGB (255, 198, 226));
    txSetColor     (RGB (145, 145, 145), 2);
    txEllipse (x + 50 * size_x + earsL, y - 138 * size_y, x + 40 * size_x + earsL, y - 98 * size_y);
    txEllipse (x + 57 * size_x + earsR, y - 138 * size_y, x + 47 * size_x + earsR, y - 98 * size_y);

    // нос
    txSetFillColor (RGB (128, 64, 0));
    txSetColor     (RGB (128, 64, 0));
    txCircle (x + 18 * size_x, y - 87 * size_y, 5 * size_x + nose);

    txSetFillColor (RGB (145, 145, 145));
    txSetColor     (RGB (145, 145, 145));
    txCircle  (x + 40 * size_x, y - 40 * size_y,       30 * size_x);       //тело
    txCircle  (x + 40 * size_x, y - 88 * size_y,       20 * size_x);       // голова
    txCircle  (x + 8  * size_x, y - 47 * size_y + paw, 10 * size_x);       // лапки
    txCircle  (x + 65 * size_x, y - 17 * size_y,       6  * size_x + tail);       // хвостик

    txEllipse (x + 2 * size_x + legs, y - 15 * size_y, x + 55 * size_x + legs, y + 8 * size_y); //ножки

    // щека и усики
    txSetFillColor (RGB (255, 215, 215));
    txCircle (x + 40 * size_x, y - 78 * size_y, 10 * size_x);
    txSetColor     (RGB (128, 0, 64));
    txLine (x + 36 * size_x, y - 78 * size_y, x + 65 * size_x, y - 83 * size_y + mustache);
    txLine (x + 36 * size_x, y - 78 * size_y, x + 65 * size_x, y - 78 * size_y + mustache);
    txLine (x + 36 * size_x, y - 78 * size_y, x + 65 * size_x, y - 73 * size_y + mustache);

    // глаз
    txSetFillColor (RGB (226, 245, 250));
    txSetColor     (RGB (226, 245, 250));
    txEllipse (x + 28 * size_x,       y - 100 * size_y, x + 49 * size_x,       y - 92 * size_y);
    txSetFillColor (RGB (0, 64, 128));
    txSetColor     (RGB (0, 64, 128));
    txEllipse (x + 28 * size_x + eye, y - 100 * size_y, x + 40 * size_x + eye, y - 92 * size_y);
    }

//-----------------------------------------------------------------------------

void DrawFox (int x, int y, double size_x, double size_y, int tail, int ears, int nose, int eyes)
    {
    txSetFillColor (RGB (255, 127, 39));
    txSetColor     (RGB (255, 127, 39));


    POINT foxBody[3] = {{x + ROUND (10 * size_x),        y - ROUND (70 * size_y)},
                        {x - ROUND (20 * size_x),        y             },
                        {x + ROUND (40 * size_x),        y}};
    txPolygon (foxBody, 3);
    POINT foxHead[3] = {{x + ROUND (10 * size_x),        y - ROUND (69  * size_y)},
                        {x - ROUND (20 * size_x),        y - ROUND (93  * size_y)},
                        {x - ROUND (50 * size_x),        y - ROUND (45  * size_y)}};
    txPolygon (foxHead, 3);


    txSetColor     (RGB (251, 100, 0));
    POINT foxEarR[3] = {{x + ROUND (10 * size_x),        y - ROUND (70  * size_y)},
                        {x + ROUND (20 * size_x) + ears, y - ROUND (86  * size_y) },
                        {x - ROUND (5  * size_x),        y - ROUND (80  * size_y)}};
    txPolygon (foxEarR, 3);
    POINT foxEarL[3] = {{x - ROUND (20 * size_x),        y - ROUND (93  * size_y)},
                        {x + ROUND (8  * size_x) + ears, y - ROUND (100 * size_y)},
                        {x - ROUND (5  * size_x),        y - ROUND (82  * size_y)}};
    txPolygon (foxEarL, 3);


    POINT foxTail[3] = {{x + ROUND (40 * size_x),        y},
                        {x + ROUND (40 * size_x) + tail, y - ROUND (50  * size_y) + tail },
                        {x + ROUND (65 * size_x) + tail, y - ROUND (60  * size_y) + tail}};
    txPolygon (foxTail, 3);


    txSetFillColor (RGB (0, 0, 242));
    txSetColor     (RGB (0, 0, 242));
    txCircle (x - 20 * size_x, y - 78 * size_y, 4 * size_x + eyes);
    txCircle (x - 8  * size_x, y - 68 * size_y, 4 * size_x + eyes);

    txSetFillColor (RGB (140, 46, 0));
    txSetColor     (RGB (140, 46, 0));
    txCircle (x - 49 * size_x, y - 45 * size_y, 4 * size_x + nose);
    }

//-----------------------------------------------------------------------------

void DrawCloud (int x, int y, double size, COLORREF cvetTucha)
    {
    txSetColor     (cvetTucha);
    txSetFillColor (cvetTucha);

    txArc (x,             y - 50 * size, x + 100 * size, y + 30 * size, 0,   180);
    txArc (x + 70 * size, y - 25 * size, x + 130 * size, y + 45 * size, 250, 220);
    txArc (x + 10 * size, y + 10 * size, x + 100 * size, y + 60 * size, 170, 200);
    txArc (x - 15 * size, y - 30 * size, x + 60  * size, y + 45 * size, 100, 200);

    txFloodFill (x + 70 * size, y - 25 * size);
    }

//-----------------------------------------------------------------------------

void DrawWolf (int x, int y, double size, int tail, int jaw, int eye, int nose, int ears)
    {
    // челюсть
    txSetColor     (RGB (128, 64, 0), 4);
    txLine                 (x + 96  * size,          y - 73  * size,
                            x + 125  * size,         y - 57  * size + jaw);
    txSetColor     (RGB (255, 255, 255));
    txSetFillColor (RGB (255, 255, 255));

    txSetColor     (RGB (128, 64, 0));
    txSetFillColor (RGB (128, 64, 0));

    txCircle    (x + 70 * size, y - 83 * size, 28 * size);                      // голова
    txRectangle (x,             y - 56 * size, x + 73  * size, y - 20  * size); // туловище
    txRectangle (x + 96 * size, y - 93 * size, x + 128 * size, y - 73  * size); // морда


    POINT wolfEar_L[3] = {{x + ROUND (54  * size),        y - ROUND (106  * size)},
                          {x + ROUND (61  * size),        y - ROUND (121  * size)},
                          {x + ROUND (68  * size),        y - ROUND (111  * size)}};
    txPolygon (wolfEar_L, 3);
    POINT wolfEar_R[3] = {{x + ROUND (70  * size) + ears, y - ROUND (107  * size)},
                          {x + ROUND (78  * size) + ears, y - ROUND (121  * size)},
                          {x + ROUND (85  * size) + ears, y - ROUND (106  * size)}};
    txPolygon (wolfEar_R, 3);


    POINT wolfPaw_L1[3] = {{x + ROUND (4   * size),       y - ROUND (23  * size)},
                           {x,                            y},
                           {x + ROUND (8   * size),       y}};
    txPolygon (wolfPaw_L1, 3);
    POINT wolfPaw_L2[3] = {{x + ROUND (14  * size),       y - ROUND (23  * size)},
                           {x + ROUND (10  * size),       y},
                           {x + ROUND (18  * size),       y}};
    txPolygon (wolfPaw_L2, 3);
    POINT wolfPaw_R1[3] = {{x + ROUND (69  * size),       y - ROUND (23  * size)},
                           {x + ROUND (65  * size),       y},
                           {x + ROUND (73  * size),       y}};
    txPolygon (wolfPaw_R1, 3);
    POINT wolfPaw_R2[3] = {{x + ROUND (59  * size),       y - ROUND (23  * size)},
                           {x + ROUND (55  * size),       y},
                           {x + ROUND (63  * size),       y}};
    txPolygon (wolfPaw_R2, 3);


    POINT wolfTail[4] =    {{x + ROUND (3 * size),        y - ROUND (55  * size)},
                            {x - ROUND (15  * size),      y - ROUND (75  * size) + tail},
                            {x - ROUND (30  * size),      y - ROUND (83  * size) + tail},
                            {x - ROUND (17  * size),      y - ROUND (67  * size) + tail}};
    txPolygon (wolfTail, 4);


    // носик
    txSetColor     (RGB (64, 0, 0));
    txSetFillColor (RGB (64, 0, 0));
    txCircle (x + 128  * size, y - 93  * size, 4  * size + nose);

    // глазик
    txSetColor     (RGB (255, 255, 255));
    txSetFillColor (RGB (255, 255, 255));
    txCircle (x + 80  * size,       y - 93  * size, 8  * size);
    txSetColor     (RGB (0, 0, 128));
    txSetFillColor (RGB (0, 0, 128));
    txCircle (x + 83  * size + eye, y - 93  * size, 5  * size);
    }

//-----------------------------------------------------------------------------

void DrawBear ()
    {
    txSetColor     (RGB (98, 0, 0));
    txSetFillColor (RGB (98, 0, 0));

    txCircle    (400, 100, 30);       // голова
    txRectangle (367, 129, 433, 200); // туловище

    txSetFillColor (RGB (64, 0, 0));
    txCircle       (367, 129, 10);
    }

//-----------------------------------------------------------------------------

void MoveCaptions_first ()
    {
    txSelectFont ("Comic Sans MS", 300);

    int t = 0;

    while (t < 55)
        {
        if (GetAsyncKeyState (VK_ESCAPE)) break;

        Pause ();

        DrawBackground ();
        MoveGrass ((t % 2) * 5);
        DrawSun ();
        DrawHouse (660, 690, 2.3, RGB (0, 45, 89));

        DrawCloud ((3 * t),        100,  1.5);
        DrawCloud ((8 * t + 300),  170,  1,  RGB (236, 236, 255));

        txSetColor     (TX_ORANGE);
        txSetFillColor (TX_ORANGE);
        txTextOut (250, (-t*t/3 + 700), "ТЕРЕМОК");

        t += 1;
        txSleep (Global_Sleep);
        }
    }

//-----------------------------------------------------------------------------

void MoveAuthor_speech ()
    {
    txSelectFont ("Comic Sans MS", 70);

    int t = 0;

    while (t < 200)
        {
        if (GetAsyncKeyState (VK_ESCAPE)) break;

        Pause ();

        DrawBackground ();
        MoveGrass ((t % 2) * 5);
        DrawSun ();
        DrawHouse (660, 690, 2.3, RGB (0, 45, 89));

        DrawCloud (3 * t,       100, 1.5);
        txTextOut (3 * t + 200, 100, "Стоит в поле Теремок");
        DrawCloud (3 * t + 750, 100, 1, RGB (236, 236, 255));

        t += 5;
        txSleep (Global_Sleep);
        }
    }

//-----------------------------------------------------------------------------

void MoveMouse_in_field ()
    {
    txSelectFont ("Comic Sans MS", 70);

    int t = 0;

    while (t < 90 && !GetAsyncKeyState (VK_ESCAPE))
        {
        Pause ();

        txClear ();

        DrawBackground ();
        MoveGrass ((t % 2) * 5);
        DrawSun ();

        DrawCloud (3 * t + 80,   100, 1.5);
        txTextOut (3 * t + 280,  40, "Бежит мимо Мышка - Норушка,");
        txTextOut (3 * t + 280,  90, "увидела Теремок");
        DrawCloud (3 * t + 1060, 100, 1, RGB (236, 236, 255));

        DrawMouse (6 * t, 670, 1, 1, ((t % 2)? 10 : -20), 1, 0, 0);

        DrawHouse (660, 690, 2.3, RGB (0, 45, 89));

        t ++;

        txSleep (Global_Sleep);
        }
    }

//-----------------------------------------------------------------------------

void RechMouse ()
    {
    txSelectFont ("Comic Sans MS", 70);

    int t = 0;

    while (t < 50)
        {
        if (GetAsyncKeyState (VK_ESCAPE)) break;

        Pause ();

        txClear ();
        DrawBackground ();
        MoveGrass ((t % 2) * 5);
        DrawSun ();

        DrawCloud (t + 100,  100, 1.5);
        txTextOut (t + 300,  40,  "остановилась мышка и спрашивает: ");
        txTextOut (t + 300,  90,  "-Терем - Теремок, кто в тереме живёт?...");
        txTextOut (t + 300,  140, "Никто не отзывается");
        DrawCloud (t + 1260, 100, 1, RGB (236, 236, 255));

        DrawMouse (550, 670, 1, 1, 2, 1, ((t % 2) * -10));

        DrawHouse (660, 690, 2.3, RGB (0, 45, 89));

        t ++;

        txSleep (Global_Sleep);
        }
    }

//-----------------------------------------------------------------------------

void MoveMouse_in_house ()
    {
    txSelectFont ("Comic Sans MS", 70);

    int t = 0;

    while (t < 35)
        {
        if (GetAsyncKeyState (VK_ESCAPE)) break;

        Pause ();

        txClear ();
        DrawBackground ();
        MoveGrass ((t % 2) * 5);
        DrawSun ();

        DrawCloud (t + 100,  100,  1.5);
        txTextOut (t + 300,  40,   "Вошла мышка в теремок");
        txTextOut (t + 300,  90,   "и стала в нём жить");
        DrawCloud (t + 900,  100,  1, RGB (236, 236, 255));

        DrawMouse (7 * t + 550,  670,  1, 1, ((t % 2)? 10 : -20), 1, 0, 0);

        DrawHouse (660, 690, 2.3, RGB (255, 255, 130));

        t ++;

        txSleep (Global_Sleep);
        }
    }

//-----------------------------------------------------------------------------

void MoveFrog_in_field ()
    {
    txSelectFont ("Comic Sans MS", 70);

    int t = 0;

    while (t < 70)
        {
        if (GetAsyncKeyState (VK_ESCAPE)) break;

        Pause ();

        txClear ();
        DrawBackground ();
        MoveGrass ((t % 2) * 5);
        DrawSun ();

        DrawCloud (3 * t + 100, 100, 1.5);
        txTextOut (3 * t + 300, 40,  "Прискакала к Теремку");
        txTextOut (3 * t + 300, 90,  "Лягушка - Квакушка");
        DrawCloud (3 * t + 850, 100, 1, RGB (236, 236, 255));

        if (t % 2 == 0) DrawFrog (6 * t, 650, 1,  0,   0, 0, 0, 0,  0, 0,  0,  0,  0,  0, 0,  0, 2, -2, -2);
        else            DrawFrog (6 * t, 670, 1, -10, -5, 3, 5, 5, -3, 10, 10, 10, 10, 7, 7, -3, 2,  0,  0);

        // Второй вариант (вместо if), в данном случае менее удобный, менее читабельный:
        //
        //DrawFrog (6 * t, (650 - t % 15), 1, ((t % 2) * -10), ((t % 2) * -5), ((t % 2) * 3), ((t % 2) * 5),
        //         ((t % 2) * 5), ((t % 2) * -3), ((t % 2) * 10), ((t % 2) * 10), ((t % 2) * 10),
        //         ((t % 2) * 10), ((t % 2) * 7), ((t % 2) * 7), ((t % 2) * -3), 2, ((t % 2) * -2),
        //         ((t % 2) * -2));

        DrawHouse (660, 690, 2.3, RGB (255, 255, 130));

        t ++;

        txSleep (Global_Sleep);
        }
    }

//-----------------------------------------------------------------------------

void RechFrog ()
    {
    txSelectFont ("Comic Sans MS", 70);

    int t = 0;

    while (t < 60)
        {
        if (GetAsyncKeyState (VK_ESCAPE)) break;

        Pause ();

        txClear ();

        DrawBackground ();
        MoveGrass ((t % 2) * 5);
        DrawSun ();

        DrawFrog (440, 650, 1.1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, ((t % 2) * 3), 0, 0);

        DrawHouse (660, 690, 2.3, RGB (255, 255, 130));

        DrawCloud (t + 100,  100, 1.5);
        txTextOut (t + 300,  40,   "и спрашивает лягушка:");
        txTextOut (t + 300,  90,   "-Терем - Теремок, кто в тереме живёт?...");
        txTextOut (t + 300,  140,  "Я, Мышка - Норушка. А ты кто?");
        txTextOut (t + 300,  190,  "А я Лягушка - Квакушка");
        txTextOut (t + 300,  240,  "-Иди ко мне жить, сказала Мышка");
        DrawCloud (t + 1260, 100, 1, RGB (236, 236, 255));

        DrawMouse (900, 647, -1, 1, 0, 0, ((t % 2) * -10));

        t ++;

        txSleep (Global_Sleep);
        }
    }

//-----------------------------------------------------------------------------

void MoveFrog_in_house ()
    {
    txSelectFont ("Comic Sans MS", 70);

    int t = 0;

    while (t < 35)
        {
        if (GetAsyncKeyState (VK_ESCAPE)) break;

        Pause ();

        txClear ();
        DrawBackground ();
        MoveGrass ((t % 2) * 5);
        DrawSun ();

        DrawCloud (t + 100,  100,  1.5);
        txTextOut (t + 300,  40,   "Лягушка прыгнула в Теремок,");
        txTextOut (t + 300,  90,   "и стали они вдвоём жить");
        DrawCloud (t + 1050,  100,  1, RGB (236, 236, 255));

        DrawFrog (7 * t + 550,  670);

        DrawHouse (660, 690, 2.3, RGB (255, 255, 130));

        t ++;

        txSleep (Global_Sleep);
        }
    }

//-----------------------------------------------------------------------------

void MoveRabbit_in_field ()
    {
    txSelectFont ("Comic Sans MS", 70);

    int t = 0;

    while (t < 80)
        {
        if (GetAsyncKeyState (VK_ESCAPE)) break;

        Pause ();

        txClear ();

        DrawBackground ();
        MoveGrass ((t % 2) * 5);
        DrawSun ();

        DrawCloud (3 * t + 80,   100, 1.5);
        txTextOut (3 * t + 280,  40, "Бежит мимо Зайчик - Попрыгайчик,");
        txTextOut (3 * t + 280,  90, "увидел Теремок");
        DrawCloud (3 * t + 1155, 100, 1, RGB (236, 236, 255));

        DrawRabbit (6 * t, (670 - (t % 15)), -1, 1, ((t % 2) * -6), 0, ((t % 2) * 2), 0, 0,
                   ((t % 2) * -3), 0, ((t % 2) * 6));

        DrawHouse (660, 690, 2.3, RGB (255, 255, 130));

        t ++;

        txSleep (Global_Sleep);
        }
    }

//-----------------------------------------------------------------------------

void RechRabbit ()
    {
    txSelectFont ("Comic Sans MS", 70);

    int t = 0;

    while (t < 60)
        {
        if (GetAsyncKeyState (VK_ESCAPE)) break;

        Pause ();

        txClear ();

        DrawBackground ();
        MoveGrass ((t % 2) * 5);
        DrawSun ();

        DrawRabbit (465, 650, -1, 1, 0, 0, (t % 2), 0, ((t % 2) * 4));

        DrawHouse (660, 690, 2.3, RGB (255, 255, 130));

        DrawCloud (t + 100,  100, 1.5);
        txTextOut (t + 300,  40,   "и спрашивает: кто в тереме живёт?");
        txTextOut (t + 300,  90,   "Я, Мышка - Норушка.");
        txTextOut (t + 300,  140,  "И я Лягушка - Квакушка. А ты кто?");
        txTextOut (t + 300,  190,  "А я Зайчик - Попрыгайчик");
        txTextOut (t + 300,  240,  "Иди к нам жить!");
        DrawCloud (t + 1165, 100, 1, RGB (236, 236, 255));

        DrawMouse (900, 647, -1, 1, 0, 0, ((t % 2) * -10));
        DrawHeadFrog (840, 358, 0.7, ((t % 2) * 3), -2, -2);

        t ++;

        txSleep (Global_Sleep);
        }
    }

//-----------------------------------------------------------------------------

void MoveRabbit_in_house ()
    {
    txSelectFont ("Comic Sans MS", 70);

    int t = 0;

    while (t < 35)
        {
        if (GetAsyncKeyState (VK_ESCAPE)) break;

        Pause ();

        txClear ();
        DrawBackground ();
        MoveGrass ((t % 2) * 5);
        DrawSun ();

        DrawCloud (t + 100,  100,  1.5);
        txTextOut (t + 300,  40,   "Заяц скок в Теремок,");
        txTextOut (t + 300,  90,   "и стали они втроем жить");
        DrawCloud (t + 970,  100,  1, RGB (236, 236, 255));

        DrawRabbit (7 * t + 550,  670, -1);

        DrawHouse (660, 690, 2.3, RGB (255, 255, 130));

        t ++;

        txSleep (Global_Sleep);
        }
    }

//-----------------------------------------------------------------------------

void MoveFox_in_field ()
    {
    txSelectFont ("Comic Sans MS", 70);

    int t = 0;

    while (t < 70)
        {
        if (GetAsyncKeyState (VK_ESCAPE)) break;

        Pause ();

        txClear ();

        DrawBackground ();
        MoveGrass ((t % 2) * 5);
        DrawSun ();

        DrawCloud (3 * t + 80,   100, 1.5);
        txTextOut (3 * t + 280,  40, "Бежит мимо Лисичка - Сестричка,");
        txTextOut (3 * t + 280,  90, "увидела Теремок");
        DrawCloud (3 * t + 1100, 100, 1, RGB (236, 236, 255));

        DrawFox (6 * t, 670, -1.5, 1.5, (t % 2) * -10);

        DrawHouse (660, 690, 2.3, RGB (255, 255, 130));

        t ++;

        txSleep (Global_Sleep);
        }
    }

//-----------------------------------------------------------------------------

void RechFox ()
    {
    txSelectFont ("Comic Sans MS", 70);

    int t = 0;

    while (t < 60)
        {
        if (GetAsyncKeyState (VK_ESCAPE)) break;

        Pause ();

        txClear ();

        DrawBackground ();
        MoveGrass ((t % 2) * 5);
        DrawSun ();

        DrawRabbit (520, 650, 1, 1, 0, 0, (t % 2), 0, ((t % 2) * 4));
        DrawFox (420, 650, -1.5, 1.5, (t % 2) * 10, 0, (t % 2));

        DrawHouse (660, 690, 2.3, RGB (255, 255, 130));

        DrawCloud (t + 100,  100, 1.5);
        txTextOut (t + 300,  20,   "и спрашивает: кто в тереме живёт?");
        txTextOut (t + 300,  70,   "Я, Мышка - Норушка.");
        txTextOut (t + 300,  120,  "Я Лягушка - Квакушка.");
        txTextOut (t + 300,  170,  "И я Зайчик - Попрыгайчик. А ты кто?");
        txTextOut (t + 300,  220,  "А я Лисичка - Сестричка");
        txTextOut (t + 300,  270,  "Иди к нам жить!");
        DrawCloud (t + 1240, 100, 1, RGB (236, 236, 255));

        DrawMouse (900, 647, -1, 1, 0, 0, ((t % 2) * -10));
        DrawHeadFrog (840, 358, 0.7, ((t % 2) * 3), -2, -2);

        t ++;

        txSleep (Global_Sleep);
        }
    }

//-----------------------------------------------------------------------------

void MoveFox_in_house ()
    {
    txSelectFont ("Comic Sans MS", 70);

    int t = 0;

    while (t < 35)
        {
        if (GetAsyncKeyState (VK_ESCAPE)) break;

        Pause ();

        txClear ();
        DrawBackground ();
        MoveGrass ((t % 2) * 5);
        DrawSun ();

        DrawCloud (t + 100,  100,  1.5);
        txTextOut (t + 300,  40,   "Забралась Лисичка в Теремок,");
        txTextOut (t + 300,  90,   "и стали они вчетвером жить");
        DrawCloud (t + 1020,  100,  1, RGB (236, 236, 255));

        DrawFox (7 * t + 550,  670, -1.5, 1.5, (t % 2) * -10);

        DrawHouse (660, 690, 2.3, RGB (255, 255, 130));

        t ++;

        txSleep (Global_Sleep);
        }
    }

//-----------------------------------------------------------------------------

void MoveWolf_in_field ()
    {
    txSelectFont ("Comic Sans MS", 70);

    int t = 0;

    while (t < 45)
        {
        if (GetAsyncKeyState (VK_ESCAPE)) break;

        Pause ();

        txClear ();

        DrawBackground ();
        MoveGrass ((t % 2) * 5);
        DrawSun ();

        DrawCloud (3 * t + 80,   100, 1.5);
        txTextOut (3 * t + 280,  40, "Прибежал Волчек - Серый бочок,");
        DrawCloud (3 * t + 1095, 100, 1, RGB (236, 236, 255));

        DrawWolf (6 * t, 670, 1.5, ((t % 2) * -30), 0, 0, (t % 2) * 2);

        DrawHouse (660, 690, 2.3, RGB (255, 255, 130));

        t ++;

        txSleep (Global_Sleep);
        }
    }

//-----------------------------------------------------------------------------

void RechWolf ()
    {
    txSelectFont ("Comic Sans MS", 70);

    int t = 0;

    while (t < 100)
        {
        if (GetAsyncKeyState (VK_ESCAPE)) break;

        Pause ();

        txClear ();

        DrawBackground ();
        MoveGrass ((t % 2) * 5);
        DrawSun ();

        DrawFox (525, 650, 1.5, 1.5, (t % 2) * 10, 0, (t % 2));
        DrawRabbit (420, 720, 1, 1, 0, 0, (t % 2), 0, ((t % 2) * 4));
        DrawWolf (250, 655, 1.5, ((t % 2) * -30), ((t % 2) * -10));

        DrawHouse (660, 690, 2.3, RGB (255, 255, 130));

        DrawCloud (t + 100,  100, 1.5);
        txTextOut (t + 300,  10,   "и спрашивает: кто в тереме живёт?");
        txTextOut (t + 300,  60,   "Я, Мышка - Норушка.");
        txTextOut (t + 300,  110,  "Я Лягушка - Квакушка.");
        txTextOut (t + 300,  160,  "Я Зайчик - Попрыгайчик.");
        txTextOut (t + 300,  210,  "Я Лисичка - Сестричка. А ты кто?");
        txTextOut (t + 300,  260,  "А я Волчек - Серый бочок");
        txTextOut (t + 300,  310,  "Иди к нам жить!");
        DrawCloud (t + 1120, 100, 1, RGB (236, 236, 255));

        DrawMouse (900, 647, -1, 1, 0, 0, ((t % 2) * -10));
        DrawHeadFrog (840, 358, 0.7, ((t % 2) * 3), -2, -2);

        t ++;

        txSleep (Global_Sleep * 1.5);
        }
    }

//-----------------------------------------------------------------------------

void MoveCaptions_end ()
    {

    int t = 0;

    while (t < 500)
        {
        if (GetAsyncKeyState (VK_ESCAPE)) break;

        Pause ();

        txClear ();

        txSetFillColor (RGB (0, 0, 77));
        txRectangle (2, 2, 1448, 778);

        DrawCloud (t + 100,      100,  1.5,  RGB (136, 136, 255));
        DrawCloud (4 * t + 20,   300,  1,    RGB (136, 136, 255));
        DrawCloud (2 * t + 70,   400,  1.2,  RGB (108, 108, 255));
        DrawCloud (8 * t + 300,  500,  2,    RGB (47,  47,  255));
        DrawCloud (t * t / 4,        650,  1,    RGB (128, 128, 192));

        txSetColor     (RGB (255, 255, 255));
        txSetFillColor (RGB (255, 255, 255));

        txSelectFont ("Comic Sans MS", 50);
        txTextOut (150,  ((-3 * t) + 700),  "Автор сего творения по мотивам русской народной сказки \"ТЕРЕМОК\":");
        txTextOut (260,  ((-3 * t) + 830),  "Мультфильм создан под руководством Профессора:");
        txTextOut (500,  ((-3 * t) + 960),  "вдохновившая Муза:");
        txTextOut (250,  ((-3 * t) + 1090), "Выражается благодарность за техническое обеспечение:");
        txTextOut (3,    ((-3 * t) + 1220), "Благодарность за замещение меня у колыбели, на время написания мультфильма:");
        txTextOut (500,  ((-3 * t) + 1350), "февраль 2019 г.");

        txSelectFont ("Comic Sans MS", 70);
        txTextOut (500,  ((-3 * t) + 730),  "Красавина Мария");
        txTextOut (400,  ((-3 * t) + 860),  "Дединский Илья Рудольфович");
        txTextOut (500,  ((-3 * t) + 990),  "сын Александр");
        txTextOut (500,  ((-3 * t) + 1120), "мужу Сергею");
        txTextOut (500,  ((-3 * t) + 1250), "бабушке Ирине");

        t ++;

        txSleep (Global_Sleep * 1.5);
        }
    }

//-----------------------------------------------------------------------------

void Pause()
    {
    while (GetAsyncKeyState (VK_SPACE))
        {
        txSleep (100);
        }
    }
