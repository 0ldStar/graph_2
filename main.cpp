#include <QApplication>
#include <QOpenGLWidget>
#include <QTranslator>
#include <iostream>
#include "Lines.h"
#include "SpinBox.h"

#define WIDTH 830
#define HEIGHT 600
#define COUNT 50

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    Lines window(0, 100, 0, -200, WIDTH, HEIGHT, COUNT);
    window.resize(WIDTH, HEIGHT);
    window.setWindowTitle("Lines");
    window.show();
    return a.exec();
}
