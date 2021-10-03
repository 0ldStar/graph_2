//
// Created by 777 on 14.09.2021.
//

#ifndef UNTITLED14_LINES_H
#define UNTITLED14_LINES_H

#include "sizes.h"
#include "SpinBox.h"
#include <QWidget>


class Lines : public QWidget {

public:
    Lines(int width, int height, int count);

protected:
    void paintEvent(QPaintEvent *event);

    void keyPressEvent(QKeyEvent *event);

    void drawLines(QPainter &painter);

    void drawLines2(QPainter &painter);

    void updateDate();

    void drawCDA(QPainter &painter);

    void drawBrezenham(QPainter &painter);

    void drawAxes(QPainter &painter);

    void drawGrid(QPainter &painter);

    void drawPixel(int x, int y, QPainter &painter);

    void drawRealLine(QPainter &painter);

    void decardToDigital(int x, int y, int &X, int &Y);

    static void decardToDigital1(int x, int y, int &X, int &Y, int width, int height);

    void digitalToDecard(int x, int y, int &X, int &Y, int width, int height);

private:
    sizes size;
    int flag;
    //QPainter &painter;
    SpinBox *spinBox;
};

#endif //UNTITLED14_LINES_H
