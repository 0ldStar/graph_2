//
// Created by 777 on 20.09.2021.
//
#include <QPainter>
#include <iostream>
#include <QWidget>
#include "Brezenhem.h"

/*
Brezenhem::Brezenham(int x1, int x2, int y1, int y2, int width, int height, int count)
        : size{x1, x2, y1, y2, width, height, count} {}
*/
Brezenhem::Brezenhem(QWidget *parent) : QWidget(parent) {}

void Brezenhem::paintEvent(QPaintEvent *e) {

    Q_UNUSED(e);

    QPainter qp(this);
    drawLines(&qp);
}
