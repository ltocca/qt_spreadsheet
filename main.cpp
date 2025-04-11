#include <QApplication>
#include "src/UserInterface.h"

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    UserInterface ui;
    ui.resize(1100, 450);
    ui.show();
    return QApplication::exec();
}
