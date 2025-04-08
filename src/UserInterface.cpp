#include "UserInterface.h"

UserInterface::UserInterface(QWidget *parent) : QMainWindow(parent)
{
    createToolbar();
    createCentralWidget();
}

UserInterface::~UserInterface() {
    for (int row = 0; row < spreadsheet->rowCount(); ++row) {
        for (int col = 0; col < spreadsheet->columnCount(); ++col) {
            if (const Cell* cell = spreadsheet->getCell(row, col)) {
                if (cell->hasFormula()) {
                    const auto* f = cell->getFormula();
                    delete f;
                }
            }
        }
    }
    delete spreadsheet;

}

void UserInterface::createToolbar(){
    auto *toolBar = new QToolBar;
    addToolBar(toolBar);

    button1 = new QPushButton("Sum");
    button1->setStyleSheet("background-color: blue;");
    toolBar->addWidget(button1);

    button2 = new QPushButton("Maximum");
    button2->setStyleSheet("background-color: green;");
    toolBar->addWidget(button2);

    button3 = new QPushButton("Minimum");
    button3->setStyleSheet("background-color: red;");
    toolBar->addWidget(button3);

    button4 = new QPushButton("Mean");
    button4->setStyleSheet("background-color: yellow;");
    toolBar->addWidget(button4);

    button5 = new QPushButton("Reset");
    toolBar->addWidget(button5);

    connect(button1, &QPushButton::clicked, this, [this] {auto* formula = new Sum(spreadsheet->getSelectedCell()); onFormulaClicked(formula); }, Qt::QueuedConnection);
    connect(button2, &QPushButton::clicked, this, [this] {auto* formula = new Max(spreadsheet->getSelectedCell()); onFormulaClicked(formula); }, Qt::QueuedConnection);
    connect(button3, &QPushButton::clicked, this, [this] {auto* formula = new Min(spreadsheet->getSelectedCell()); onFormulaClicked(formula); }, Qt::QueuedConnection);
    connect(button4, &QPushButton::clicked, this, [this] {auto* formula = new Mean(spreadsheet->getSelectedCell()); onFormulaClicked(formula); }, Qt::QueuedConnection);

    connect(button5, &QPushButton::clicked, this, &UserInterface::onResetClicked);
}

void UserInterface::createCentralWidget()
{
    bool ok;
    QString text;
    do {
        text = QInputDialog::getText(this, tr("Enter Spreadsheet Dimensions (max 10 rows and 10 columns):"), tr("Number of rows and columns (comma-separated, e.g., 10,5):"), QLineEdit::Normal, "", &ok);
        if (ok && !text.isEmpty()) {
            QStringList coordinates = text.split(",");
            const int rows = coordinates[0].toInt();
            const int columns = coordinates[1].toInt();
            if (rows <= 0 || columns <= 0){
                QMessageBox::critical(nullptr, "Error!", "Both values MUST be greater than 0! Try again");
            }
            else if (rows > 10 || columns > 10) {
                QMessageBox::critical(nullptr, "Error!", "Right now you can have a maximum of 10 rows and 10 columns! Try again");
            }
            else {
                spreadsheet = new Spreadsheet(rows, columns);
                break;
            }
        }
        else if (ok && text.isEmpty()) {
            QMessageBox::critical(nullptr, "Error", "Nothing was inserted!");
        }
    } while (ok);
    //spreadsheet = new Spreadsheet(rows, cols);
    auto *centralWidget = new QWidget;
    setCentralWidget(centralWidget);

    auto *layout = new QVBoxLayout;
    centralWidget->setLayout(layout);

    layout->addWidget(spreadsheet);
}

bool UserInterface::comma_split(const QString &text, std::list<Cell *>& cells) const {
    QStringList coordinates = text.split(",");
    bool finished = false;
    for (const QString& coord : coordinates) {
        int row = coord[0].digitValue();
        int col = coord[1].digitValue();
        if (row > spreadsheet->rowCount() || col > spreadsheet->columnCount()) {
            QMessageBox::critical(nullptr, "Error", "Inserted cell indexes are out of range! Try again");
            return finished;
        }
        cells.push_back(spreadsheet->getCell(row, col));
    }
    return finished = true;
}


bool UserInterface::colon_split(const QString &text, std::list<Cell *>& cells) const {
    bool finished = false;
    QStringList coordinates = text.split(":");
    if (coordinates.size() == 2 && coordinates[0].size()==2 && coordinates[1].size() == 2) { // right now we can work only with two digits
        // getting the single digits for the start and the end of the interval
        const int firstRow = coordinates[0][0].digitValue();
        const int firstCol = coordinates[0][1].digitValue();
        const int lastRow = coordinates[1][0].digitValue();
        const int lastCol = coordinates[1][1].digitValue();

        if (firstRow > lastRow || firstCol > lastCol) {
            QMessageBox::critical(nullptr, "Error", "You have inserted a wrong interval! Try again");
            return finished;
        }
        if (firstRow < 0 || firstCol < 0 || lastRow > spreadsheet->rowCount()-1 || lastCol > spreadsheet->columnCount()-1) {
            QMessageBox::critical(nullptr, "Error", "Inserted cell indexes are out of range! Try again");
            return finished;
        }
        for (int row = firstRow; row <= lastRow; row++) {
            for (int col = firstCol; col <= lastCol; col++) {
                cells.push_back(spreadsheet->getCell(row, col));
            }
        }
    }
    else {
        QMessageBox::critical(nullptr, "Error", "You have inserted a wrong interval! Try again");
    }
    finished = true;
    return finished;
}

std::pair<bool, std::list<Cell*>>  UserInterface::getCoordinates(const QString& text) const {
    const QRegularExpression delimiter("[,:]");
    const bool hasComma = text.contains(",");
    const bool hasColon = text.contains(":");
    const bool hasBoth = hasColon && hasComma;
    std::list<Cell*> cells;
    bool finished = false;
    if (!hasColon && hasComma) {
        finished = comma_split(text, cells);
    }
    else if (!hasComma && hasColon) {
        finished = colon_split(text, cells);
    }
    else if (hasBoth) {
        QMessageBox::critical(nullptr, "Error", "You have inserted an unsupported interval (right now)! Try again");
    }
    else {
        QMessageBox::critical(nullptr, "Error", "Please revise your coordinates! Remember that you can't insert single cells in a formula! Try again");
    }
    return {finished, cells};
}

void UserInterface::onFormulaClicked(Formula *formula) {
    bool ok;
    bool inputValid = false;
    do {
        QString text = QInputDialog::getText(this, tr("Enter Cell Coordinates"), tr("Cells (comma-separated, e.g., 00,01) or an interval (colon-separated, e.g., 00:11):"), QLineEdit::Normal, "", &ok);
        if (ok && !text.isEmpty()) {
            const auto [finished, cells] = getCoordinates(text);
            if (finished && !Formula::hasCircularReference(spreadsheet->getSelectedCell(), cells)) {
                for (Cell* cell : cells) {
                    formula->addCell(cell);
                }
                formula->calculate();
                inputValid = finished;
            }
            else if (Formula::hasCircularReference(spreadsheet->getSelectedCell(), cells)) {
                QMessageBox::critical(nullptr, "Error", "You can't add the selected cell into the formula!"); // Circular reference
            }
        }
        if (inputValid){
            spreadsheet->getSelectedCell()->setFormula(formula); // connect the formula and the cell where is located
        }
    }
    while (!inputValid && ok);
}

void UserInterface::onResetClicked() const {
    Cell* cell = spreadsheet->getSelectedCell();
    if (!cell) return;
    if (cell->getFormula()==nullptr && cell->getData()==0.00) {
        QMessageBox::critical(nullptr, "Error", "This cell is already empty!");
        return;
    }
    cell->resetCell();
    if (cell->hasFormula()) {
        const auto* f = cell->getFormula();
        delete f;
    }

}