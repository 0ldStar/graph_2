//
// Created by 777 on 14.09.2021.
//

#ifndef UNTITLED14_LINES_H
#define UNTITLED14_LINES_H

#include "sizes.h"
#include "SpinBox.h"
#include <QWidget>

void drawCDA(const sizes &size, QPainter &painter);

void drawBrezenham(const sizes &size, QPainter &painter);

void drawAxes(sizes &size, QPainter &painter);

void drawGrid(sizes &size, QPainter &painter);

void drawPixel(int x, int y, const sizes &size, QPainter &painter);

void drawRealLine(sizes &size, QPainter &painter);

void decardToDigital(int x, int y, int &X, int &Y, const sizes &size);

void decardToDigital1(int x, int y, int &X, int &Y, int width, int height);

void digitalToDecard(int x, int y, int &X, int &Y, int width, int height);

class Lines : public QWidget {

public:
    Lines(int x1, int x2, int y1, int y2, int width, int height, int count);

protected:
    void paintEvent(QPaintEvent *event);

    void keyPressEvent(QKeyEvent *event);

    void drawLines(QPainter &painter);

    void drawLines2(QPainter &painter);

    void updateDate();

private:
    sizes size;
    int flag;
    SpinBox *spinBox;
};

#endif //UNTITLED14_LINES_H
