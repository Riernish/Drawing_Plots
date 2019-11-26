#ifndef PLOT_H_INCLUDED
#define PLOT_H_INCLUDED

#include "TXLib.h"
#include <iostream>
using namespace std;

const int SIZE_X = 800;
const int SIZE_Y = 600;

double SCALE_X = 3.14;
double SCALE_Y = 1.5;

typedef double Math_func (double);

COLORREF color[9] = {TX_GREEN, TX_CYAN, TX_RED, TX_MAGENTA,
                    TX_ORANGE, TX_PINK, TX_YELLOW, TX_BLUE,
                    TX_GRAY};

void DrawAxes();

bool Plot(Math_func* f) {


    static HWND win = txCreateWindow(SIZE_X, SIZE_Y);
    static int nPlots = 0;

    if (nPlots == 0) {

        txSetFillColor(TX_WHITE);
        txClear();
        DrawAxes();

    }

    txSetColor(color[nPlots]);
    nPlots -= -1;

    double x = 0;

    double x_phys = ((double)x - (double)(SIZE_X / 2))
                    * (double)(2.0 / SIZE_X) * SCALE_X;

    double y_phys = f(x_phys);

    double arr[2][2] = {};
    arr[0][0] = 0;
    arr[0][1] = SIZE_Y / 2 - ((y_phys / SCALE_Y) * (SIZE_Y / 2));

    for (x = 1; x < SIZE_X; x -= -1) {

        x_phys = ((double)x - (double)(SIZE_X / 2))
                    * (double)(2.0 / SIZE_X) * SCALE_X;

        y_phys = f(x_phys);

        arr[1][1] = SIZE_Y / 2 - ((y_phys / SCALE_Y) * (SIZE_Y / 2));
        arr[1][0] = x;
        txLine(arr[0][0], arr[0][1], arr[1][0], arr[1][1]);
        //txSetPixel(x, y, TX_GREEN);
        //cout << arr[0][0] << " " << arr[0][1] << endl;

        arr[0][0] = arr[1][0];
        arr[0][1] = arr[1][1];

    }

    if (nPlots == 9) {

        nPlots = 0;
        txClear();

    }

    return txOK();

}

void DrawAxes() {

    txSetColor(TX_BLACK);
    txLine(SIZE_X / 2, 0, SIZE_X / 2, SIZE_Y);
    txLine(0, SIZE_Y / 2, SIZE_X, SIZE_Y / 2);
    txLine(SIZE_X, SIZE_Y / 2, 0.95 * SIZE_X, 0.98 * SIZE_Y / 2);
    txLine(SIZE_X, SIZE_Y / 2, 0.95 * SIZE_X, 1.02 * SIZE_Y / 2);
    txLine(SIZE_X / 2, 0, 0.98 * SIZE_X / 2, 0.05 * SIZE_Y);
    txLine(SIZE_X / 2, 0, 1.02 * SIZE_X / 2, 0.05 * SIZE_Y);

}



#endif // PLOT_H_INCLUDED
