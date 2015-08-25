#include "init_window.h"

int main(int argc, char** argv) {
    QApplication app (argc, argv);
    Init_Window init_window;
    init_window.show();
    return app.exec();
}
