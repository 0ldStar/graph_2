//
// Created by 777 on 14.09.2021.
//

#ifndef UNTITLED14_LINES_H
#define UNTITLED14_LINES_H

#include <QWidget>

#include <vector>
#include "SpinBox.h"
#include "sizes.h"

using namespace std;

class Lines : public QWidget {

public:
    Lines(int width, int height, int count, vector<vector<int>> &arr, vector<vector<int>> &buf,
          vector<vector<int>> &map);

protected:
    void paintEvent(QPaintEvent *event);

    void keyPressEvent(QKeyEvent *event);

    void drawLines(QPainter &painter);

    void drawLines2(QPainter &painter);

    void updateData();

    void drawCDA(QPainter &painter);

    void drawBrezenham(QPainter &painter);

    void drawAxes(QPainter &painter) const;

    void drawGrid(QPainter &painter) const;

    void drawRealLine(QPainter &painter) const;

    void decardToDigital(int x, int y, int &X, int &Y) const;

    void mapClean();

    void drawMediumPixel(int x, int y, QPainter &painter);

    void drawMap(QPainter &painter);

    void drawBigPixel(int x, int y, int weight, QPainter &painter);

    static void decardToDigital1(int x, int y, int &X, int &Y, int width, int height);


private:
    sizes size;
    // filters filter;
    int flag;
    vector<vector<int>> &filter;
    vector<vector<int>> &buf;
    vector<vector<int>> &map;
    //QPainter &painter;
    SpinBox *spinBox;
    int count;
};

#endif //UNTITLED14_LINES_H
