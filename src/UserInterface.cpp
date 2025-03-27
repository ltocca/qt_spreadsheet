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
}

void UserInterface::createToolbar()
{
    auto *toolBar = new QToolBar;
    addToolBar(toolBar);

    button1 = new QPushButton("Sum");
    toolBar->addWidget(button1);

    button2 = new QPushButton("Maxiumum");
    toolBar->addWidget(button2);

    button3 = new QPushButton("Minimum");
    toolBar->addWidget(button3);

    button4 = new QPushButton("Mean");
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
    QString text = QInputDialog::getText(this, tr("Enter Spreadsheet Dimensions:"), tr("Number of rows and columns (comma-separated, e.g., 10,5):"), QLineEdit::Normal, "", &ok);
    if (ok && !text.isEmpty()) {
        QStringList coordinates = text.split(",");
            spreadsheet = new Spreadsheet(coordinates[0].toInt(), coordinates[1].toInt());

        }
    else if (text.isEmpty()) {

    }
    //spreadsheet = new Spreadsheet(rows, cols);
    auto *centralWidget = new QWidget;
    setCentralWidget(centralWidget);

    auto *layout = new QVBoxLayout;
    centralWidget->setLayout(layout);

    layout->addWidget(spreadsheet);
}

std::list<Cell*> UserInterface::getCoordinates(const QString& text) const {
    const QRegularExpression delimiter("[,:]");
    bool hasComma = text.contains(",");
    bool hasColon = text.contains(":");
    std::list<Cell*> cells;
    if (hasComma && !hasColon) {
        QStringList coordinates = text.split(",");
        for (const QString& coord : coordinates) {
            int row = coord[0].digitValue();
            int col = coord[1].digitValue();
            cells.push_back(spreadsheet->getCell(row, col));
        }
    }
    else if (!hasComma && hasColon) {
        QStringList coordinates = text.split(":");
        if (coordinates.size() == 2 && coordinates[0].size()>=2 && coordinates[1].size()>=2) {
            int firstRow = coordinates[0][0].digitValue();
            int firstCol = coordinates[0][1].digitValue();
            int lastRow = coordinates[1][0].digitValue();
            int lastCol = coordinates[1][1].digitValue();

            if (firstRow > lastRow || firstCol > lastCol) {
                // TODO: row and column dimension error handling
            }

            for (int row = firstRow; row <= lastRow; row++) {
                for (int col = firstCol; col <= lastCol; col++) {
                    cells.push_back(spreadsheet->getCell(row, col));
                }
            }
        }
    }
    else {
        // TODO: syntax error handling
    }
    return cells;

}

void UserInterface::onFormulaClicked(Formula *formula) {
    bool ok;
    QString text = QInputDialog::getText(this, tr("Enter Cell Coordinates"), tr("Cells (comma-separated, e.g., 00,01) or an interval (colon-separated, e.g., 00:11:"), QLineEdit::Normal, "", &ok);
    if (ok && !text.isEmpty()) {
        for (const std::list<Cell*> cells = getCoordinates(text); Cell* cell : cells) {
            formula->addCell(cell);
            cell->setFormula(formula);
        }
        formula->calculate();
    }
    Cell* cell = spreadsheet->getSelectedCell();
    cell->setFormula(formula);
}

void UserInterface::onResetClicked() { // TODO: check if is needed to keep the cell in the formula if the selected cell is not a "formula".
    Cell* cell = spreadsheet->getSelectedCell();
    if (!cell) return;
    cell->resetCell();
    if (cell->hasFormula()) {
        auto* f = cell->getFormula();
        delete f;
    }

}