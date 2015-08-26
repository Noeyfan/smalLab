#include "init_window.h"

int main(int argc, char** argv) {
    QApplication app (argc, argv);
    InitWindow init_window;
    init_window.show();
    return app.exec();
}
