//(txMouseButtons() & 1)

#include "TXLib.h"

//-----------------------------------------------------------------------------

int main ()
    {
    txCreateWindow (900, 700);

    while (!txGetAsyncKeyState (VK_ESCAPE))
        {
        if (txMouseButtons() == 1) printf (" �����");
        if (txMouseButtons() == 2) printf (" ������");
        if (txMouseButtons() == 4) printf (" �������");
        }
    }
