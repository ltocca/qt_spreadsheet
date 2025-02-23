#ifndef USERINTERFACE_H
#define USERINTERFACE_H


#pragma once

#include <QMainWindow>
#include <QPushButton>
#include <QInputDialog>
#include <QVBoxLayout>
#include <QMenuBar>
#include <QMenu>
#include <QAction>
#include <QToolBar>
#include "Spreadsheet.h"
#include "Sum.h"
#include "Mean.h"
#include "Max.h"
#include "Min.h"


class UserInterface final : public QMainWindow
{
    Q_OBJECT
public:
    explicit UserInterface(QWidget *parent = nullptr);

private slots:
    void onFormulaClicked(Formula *formula);

private:
    Spreadsheet *spreadsheet;
    QPushButton *button1;
    QPushButton *button2;
    QPushButton *button3;
    QPushButton *button4;

    //void createMenu();
    void createToolbar();
    void createCentralWidget();

    // TODO: Improve onFormulaClicked

    void onSumClicked();
    void onMaxClicked();
    void onMinClicked();
    void onMeanClicked();

};


#endif //USERINTERFACE_H
