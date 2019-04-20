//-----------------------------------------------------------------------------
//! @file R_W_Color_in_from_file.h
//! @mainpage
//! @p ������ �������
//!    - @ref ReadFromFile_Color ()
//!    - @ref WriteToFile_Color  ()
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
//! ������ �������� ����� �� �����
//!
//! @param   file_uzer  ��� �����, �� �������� �������� �������� �����.
//!
//! @return  ����.
//!
//! @see     WriteToFile_Color()
//!
//! @p ������ ������������� @code
//!         FILE *file = fopen ("color.txt", "r");
//!         COLORREF color = ReadFromFile_Color (file);
//!         fclose (file);
//! @endcode
//-----------------------------------------------------------------------------

COLORREF ReadFromFile_Color (FILE *file_uzer);
int WriteToFile_Color (COLORREF color, FILE *file_uzer);

//-----------------------------------------------------------------------------
const COLORREF RED_COLOR   = RGB (225, 0, 0);
const COLORREF GREEN_COLOR = RGB (0, 225, 0);
const COLORREF BLUE_COLOR  = RGB (0, 0, 225);

//-----------------------------------------------------------------------------

COLORREF ReadFromFile_Color (FILE *file_uzer)
    {
    int r_color = 0, g_color = 0, b_color =0;
    char color[50] = "";


    char c = 0;
    if (!((fscanf (file_uzer, "color %c", &c) == 1) && (c == '=')))
        {
        printf ("������ ����� � ����� �������� �� ���������");
        return CLR_INVALID;
        }

    //printf("������� ������ ����� color = (%s)\n", fgets (color, sizeof(color) - 1, file_uzer));

    if (fscanf (file_uzer, " RGB ( %d , %d , %d )", &r_color, &g_color, &b_color) == 3)
        {
        if ((r_color < 0) || (r_color > 225) ||
            (g_color < 0) || (g_color > 225) ||
            (b_color < 0) || (b_color > 225))
           {
           printf ("���� RGB(%d, %d, %d) - ����� �� ���������", r_color, g_color, b_color);
           return CLR_INVALID;
           }

        return RGB(r_color, g_color, b_color);
        }

    if (fscanf (file_uzer, "%s", color) == 1)
        {
        if (strcmp (color, "RED_COLOR") == 0)
            {
            printf ("���� = RGB(225, 0 ,0)");
            return RGB(225, 0 ,0);
            }
        if (strcmp (color, "GREEN_COLOR") == 0)
            {
            printf ("���� = RGB(0, 225 ,0)");
            return RGB(0, 225 ,0);
            }
        if (strcmp (color, "BLUE_COLOR") == 0)
            {
            printf ("���� = RGB(0, 0 ,225)");
            return RGB(0, 0 ,225);
            }

        printf ("���� %s �� ������", color);
        return CLR_INVALID;
        }

    else
        {
        printf ("�������� ����� � ����� �����������");
        return CLR_INVALID;
        }
    }

//-----------------------------------------------------------------------------

int WriteToFile_Color (COLORREF color, FILE *file_uzer)
    {
    switch (color)
        {
        case RED_COLOR:
            fprintf (file_uzer, " color = %s", "RED_COLOR");
            break;
        case GREEN_COLOR:
            fprintf (file_uzer, " color = %s", "GREEN_COLOR");
            break;
        case BLUE_COLOR:
            fprintf (file_uzer, " color = %s", "BLUE_COLOR");
            break;
        default:
            fprintf (file_uzer, " color = RGB (%3d, %3d, %3d)", txExtractColor (color, TX_RED),
                                                                txExtractColor (color, TX_GREEN),
                                                                txExtractColor (color, TX_BLUE));
        }
    return 1;
    }
