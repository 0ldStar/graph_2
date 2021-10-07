#include <QPainter>
#include <iostream>
#include <QTimer>
#include <QKeyEvent>
#include <windows.h>
#include "Lines.h"


Lines::Lines(int width, int height, int count, vector<vector<int>> &arr, vector<vector<int>> &buf,
             vector<vector<int>> &map)
        : size{0, 0, 0, 0, width, height, count}, filter(arr), buf(buf), map(map) {
    int arrSize = filter.size();
    spinBox = new SpinBox(this, count);
    flag = 0;
    buf.resize(arrSize);
    for (int i = 0; i < arrSize; ++i) buf[i].resize(arrSize);
    map.resize(count + 1);
    for (int i = 0; i <= count; ++i) map[i].resize(count + 1);

    for (int i = 0; i < arrSize; ++i) {
        for (int j = 0; j < arrSize; ++j) {
            filter[i][j] = arr[i][j];
            buf[i][j] = 0;
        }
    }
    resize(width, height);
}

void Lines::keyPressEvent(QKeyEvent *event) {

    if (event->key() == Qt::Key_Escape) {
        flag++;
        flag = flag % 3;
        update();
    }
}

void Lines::paintEvent(QPaintEvent *e) {

    Q_UNUSED(e);
    updateData();
    QPainter qp(this);
    drawLines(qp);
    drawMap(qp);
    if (flag == 0) drawLines(qp);
    else if (flag == 1) drawLines2(qp);
    else if (flag == 2) {
        drawLines(qp);
        drawMap(qp);
        drawLines2(qp);
    }
    drawMap(qp);
    drawRealLine(qp);
    drawGrid(qp);
    drawAxes(qp);
}

void Lines::drawMap(QPainter &painter) {
    int filterSize = filter.size();
    int bigPixelCount = size.count / filterSize;
    for (int i = 0; i < bigPixelCount; ++i) {
        for (int j = 0; j < bigPixelCount; ++j) {
            int weight = 0;
            for (int k = i * filterSize, o = 0; k < i * filterSize + filterSize; ++k, ++o) {
                for (int l = j * filterSize, p = 0; l < j * filterSize + filterSize; ++l, ++p) {
                    weight += map[k][l + 1] * filter[o][p];
                }
            }
            if (weight != 0) {
                drawBigPixel(i, j, weight, painter);
            }
        }
    }
    mapClean();
}

void Lines::drawBigPixel(int x, int y, int weight, QPainter &painter) {
    int bigPixelCount = size.count / filter.size();
    double dx = (float) size.width / (float) bigPixelCount;
    double dy = (float) size.height / (float) bigPixelCount;
    QColor color(weight * 25 + 25, 10, 0);
    painter.setBrush(QBrush(color));
    painter.setPen(color);
    painter.drawRect(x * dx, y * dy, dx, dy);
}

void Lines::mapClean() {
    for (int i = 0; i <= size.count; ++i) {
        for (int j = 0; j <= size.count; ++j) {
            map[i][j] = 0;
        }
    }
}

void Lines::updateData() {
    size.x1 = spinBox->getX1();
    size.x2 = spinBox->getX2();
    size.y1 = spinBox->getY1();
    size.y2 = spinBox->getY2();
}

void Lines::drawLines2(QPainter &painter) {
    drawCDA(painter);
}


void Lines::drawLines(QPainter &painter) {
    painter.setBrush(QBrush(Qt::darkBlue));
    painter.setPen(Qt::darkBlue);
    drawBrezenham(painter);
}

void Lines::drawRealLine(QPainter &painter) const {
    int x1, x2, y1, y2;
    double dx = (float) size.width / (float) size.count;
    double dy = (float) size.height / (float) size.count;
    QPen pen;
    pen.setWidth(3);
    pen.setColor("cyan");
    painter.setPen(pen);
    painter.setBrush(QBrush(Qt::green));
    decardToDigital1(size.x1 * dx, size.y1 * dy, x1, y1, size.width, size.height);
    decardToDigital1(size.x2 * dx, size.y2 * dy, x2, y2, size.width, size.height);
    painter.drawLine(x1, y1, x2, y2);
}

void Lines::drawGrid(QPainter &painter) const {
    painter.setPen(Qt::black);
    painter.setPen(Qt::DotLine);


    for (int i = 0; i < size.count; ++i) {
        painter.drawLine((int) ((float) i / (float) size.count * (float) size.width), 0,
                         (int) ((float) i / (float) size.count * (float) size.width),
                         size.height);
    }
    for (int i = 0; i < size.count; ++i) {
        painter.drawLine(0, (int) ((float) i / (float) size.count * (float) size.height), size.width,
                         (int) ((float) i / (float) size.count * (float) size.height));
    }
}

void Lines::drawAxes(QPainter &painter) const {
    QPen pen;
    pen.setColor("red");
    pen.setWidth(3);
    painter.setPen(pen);
    int dx = (int) ((float) size.width / 2);
    int dy = (int) ((float) size.height / 2);

    painter.drawLine(dx, 0, dx, size.height);
    painter.drawLine(0, dy, size.width, dy);
}

int sign(double x) {
    if (x > 0) return 1;
    else if (x == 0) return 0;
    else
        return -1;
}


void Lines::drawMediumPixel(int x, int y, QPainter &painter) {
    double dx = (float) size.width / (float) size.count;
    double dy = (float) size.height / (float) size.count;
    QColor color(256, 0, 256);
    painter.setBrush(QBrush(color));
    painter.setPen(color);
    painter.drawRect(x * dx, y * dy - dy, dx, dy);
}

void Lines::drawCDA(QPainter &painter) {
    double dx, dy, l, x, y;
    int _x, _y;
    if (abs(size.x2 - size.x1) >= abs(size.y2 - size.y1)) l = abs(size.x2 - size.x1);
    else {
        l = abs(size.y2 - size.y1);
    }
    dx = (size.x2 - size.x1) / l;
    dy = (size.y2 - size.y1) / l;

    x = size.x1 + 0.5 * sign(dx);
    y = size.y1 + 0.5 * sign(dy);
    if (l == 0) return;
    for (int i = 0; i <= l; ++i) {
        decardToDigital(floor(x), floor(y), _x, _y);
        map[_x][_y] = 1;
        x = x + dx;
        y = y + dy;
    }
}

void Lines::drawBrezenham(QPainter &painter) {
    int a, b, e, dx, dy, sx, sy;

    int x = size.x1;
    int _x, _y;
    int y = size.y1;
    dx = abs(size.x2 - size.x1);
    dy = abs(size.y2 - size.y1);
    if ((size.x2 - size.x1) >= 0) sx = 1;
    else
        sx = -1;
    if ((size.y2 - size.y1) >= 0) sy = 1;
    else sy = -1;
    if (dy > dx) {
        a = dx;
        dx = dy;
        dy = a;
        b = 1;
    } else b = 0;
    e = 2 * dy - dx;
    if (dx == 0) return;
    if (sx < 0) x = size.x1 + sx;
    if (sy < 0)y = size.y1 + sy;
    for (int i = 0; i <= abs(dx); i++) {
        decardToDigital(x, y, _x, _y);
        map[_x][_y] = 1;
        while (e >= 0) {
            if (b == 1)x = x + sx;
            else y = y + sy;
            e = e - 2 * dx;
        }
        if (b == 1) y = y + sy;
        else x = x + sx;
        e = e + 2 * dy;

    }
}

void Lines::decardToDigital1(int x, int y, int &X, int &Y, int width, int height) {
    X = width / 2 + x;
    Y = height / 2 - y;

}


void Lines::decardToDigital(int x, int y, int &X, int &Y) const {
    X = (size.count / 2 + x);
    Y = (size.count / 2 - y);
}

