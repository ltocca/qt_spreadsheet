#ifndef USERINTERFACE_H
#define USERINTERFACE_H


#pragma once

#include <QMainWindow>
#include <QPushButton>
#include <QInputDialog>
#include <QRegularExpression>
#include <QVBoxLayout>
#include <QMenuBar>
#include <QMessageBox>
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
    ~UserInterface() override;

private slots:
    void onFormulaClicked(Formula *formula);

private:
    Spreadsheet *spreadsheet;
    QPushButton *button1;
    QPushButton *button2;
    QPushButton *button3;
    QPushButton *button4;
    QPushButton *button5;

    //void createMenu();
    void createToolbar();
    void createCentralWidget();

    bool comma_split(const QString &text, std::list<Cell *> & cells) const;
    bool colon_split(const QString &text, std::list<Cell *> & cells) const;

    [[nodiscard]] std::pair<bool, std::list<Cell*>> getCoordinates(const QString& text) const; // handles cells "selection"

    void onResetClicked() const;

};


#endif //USERINTERFACE_H
