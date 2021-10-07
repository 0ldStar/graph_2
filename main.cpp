#include <QApplication>
#include <QOpenGLWidget>
#include <QTranslator>
#include <iostream>
#include "Lines.h"
#include <vector>

#define WIDTH 600
#define HEIGHT 600
#define COUNT 60
using namespace std;

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    vector<vector<int>> arr{{1, 2, 1},
                            {2, 4, 2},
                            {1, 2, 1}};
    vector<vector<int>> buf;
    vector<vector<int>> map;
    Lines window(WIDTH, HEIGHT, COUNT, arr, buf, map);
    window.setWindowTitle("Lines");
    window.show();
    return a.exec();
}
