#include <QApplication>
#include <QPushButton>
#include "src/UserInterface.h"

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    //QPushButton button("Hello world!", nullptr);
    //button.resize(200, 100);
    //button.show();
    //return QApplication::exec();
    UserInterface ui;
    ui.resize(1100, 450);
    ui.show();
    return QApplication::exec();
}
