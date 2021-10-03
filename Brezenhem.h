//
// Created by 777 on 20.09.2021.
//

#ifndef UNTITLED14_BREZENHEM_H
#define UNTITLED14_BREZENHEM_H


class Brezenhem : public QWidget {
Q_OBJECT

public:
    Brezenhem(QWidget *parent = 0);


private:
    void paintEvent(QPaintEvent *event);

    void drawLines(QPainter *qp);
};


#endif //UNTITLED14_BREZENHEM_H
