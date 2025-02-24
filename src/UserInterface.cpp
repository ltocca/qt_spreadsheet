#include "UserInterface.h"

UserInterface::UserInterface(QWidget *parent) : QMainWindow(parent)
{
    createToolbar();
    createCentralWidget();
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

    connect(button1, &QPushButton::clicked, this, [this]() {auto* formula = new Sum(spreadsheet->getSelectedCell()); onFormulaClicked(formula); }, Qt::QueuedConnection);

	//connect(button1, &QPushButton::clicked, this, &UserInterface::onSumClicked);
	connect(button2, &QPushButton::clicked, this, &UserInterface::onMaxClicked);
	connect(button3, &QPushButton::clicked, this, &UserInterface::onMinClicked);
	connect(button4, &QPushButton::clicked, this, &UserInterface::onMeanClicked);
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

void UserInterface::onSumClicked() {
    bool ok;
    QString text = QInputDialog::getText(this, tr("Enter Cell Coordinates"), tr("Cells (comma-separated, e.g., 00,01):"), QLineEdit::Normal, "", &ok);
    if (ok && !text.isEmpty()) {
        QStringList coordinates = text.split(",");
        std::list<Cell*> cells;

        for (const QString& coord : coordinates) {
            int row = coord[0].digitValue();
            int col = coord[1].digitValue();
            cells.push_back(spreadsheet->getCell(row, col));
        }

        auto* formula = new Sum(spreadsheet->getSelectedCell());
        for (Cell* cell : cells) {
            formula->addCell(cell);
        }
        formula->calculate();
    }
}

void UserInterface::onMeanClicked() {
    bool ok;
    QString text = QInputDialog::getText(this, tr("Enter Cell Coordinates"), tr("Cells (comma-separated, e.g., 00,01):"), QLineEdit::Normal, "", &ok);
    if (ok && !text.isEmpty()) {
        QStringList coordinates = text.split(",");
        std::list<Cell*> cells;

        for (const QString& coord : coordinates) {
            int row = coord[0].digitValue();
            int col = coord[1].digitValue();
            cells.push_back(spreadsheet->getCell(row, col));
        }

        auto* formula = new Mean(spreadsheet->getSelectedCell());
        for (Cell* cell : cells) {
            formula->addCell(cell);
        }
        formula->calculate();
    }
}

void UserInterface::onMaxClicked() {
    bool ok;
    QString text = QInputDialog::getText(this, tr("Enter Cell Coordinates"), tr("Cells (comma-separated, e.g., 00,01):"), QLineEdit::Normal, "", &ok);
    if (ok && !text.isEmpty()) {
        QStringList coordinates = text.split(",");
        std::list<Cell*> cells;

        for (const QString& coord : coordinates) {
            int row = coord[0].digitValue();
            int col = coord[1].digitValue();
            cells.push_back(spreadsheet->getCell(row, col));
        }

        auto* formula = new Max(spreadsheet->getSelectedCell());
        for (Cell* cell : cells) {
            formula->addCell(cell);
        }
        formula->calculate();
    }
}

void UserInterface::onMinClicked() {
    bool ok;
    QString text = QInputDialog::getText(this, tr("Enter Cell Coordinates"), tr("Cells (comma-separated, e.g., 00,01):"), QLineEdit::Normal, "", &ok);
    if (ok && !text.isEmpty()) {
        QStringList coordinates = text.split(",");
        std::list<Cell*> cells;

        for (const QString& coord : coordinates) {
            int row = coord[0].digitValue();
            int col = coord[1].digitValue();
            cells.push_back(spreadsheet->getCell(row, col));
        }

        auto* formula = new Min(spreadsheet->getSelectedCell());
        for (Cell* cell : cells) {
            formula->addCell(cell);
        }
        formula->calculate();
    }
}

void UserInterface::onFormulaClicked(Formula *formula) {
    bool ok;
    QString text = QInputDialog::getText(this, tr("Enter Cell Coordinates"), tr("Cells (comma-separated, e.g., 00,01):"), QLineEdit::Normal, "", &ok);
    if (ok && !text.isEmpty()) {
        QStringList coordinates = text.split(",");
        std::list<Cell*> cells;

        for (const QString& coord : coordinates) {
            int row = coord[0].digitValue();
            int col = coord[1].digitValue();
            cells.push_back(spreadsheet->getCell(row, col));
        }

        //auto* formula = new Sum(spreadsheet->getSelectedCell());
        for (Cell* cell : cells) {
            formula->addCell(cell);
        }
        formula->calculate();
    }
}
