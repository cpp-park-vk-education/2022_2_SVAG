#include "mainwindow.h"

MainWindow::MainWindow(QWidget* parent): QMainWindow(parent) {
    // Draw
    QWidget* centralWidget = Draw();
    setCentralWidget(centralWidget);

    QStringList settings;
    QComboBox* userSettings = findChild<QComboBox*>("userSettings");
    settings << tr("Профиль") << tr("Помощь") << tr("Выйти");

    for (int i = 0, sep = 1; i < settings.size(); ++i) {
        userSettings->addItem(settings[i]);
        userSettings->insertSeparator(sep);
        sep += 2;
    }

    userSettings->setCurrentIndex(-1);  // Не забыть сбрасывать при изменении

    QPushButton* createBoard = findChild<QPushButton*>("createBoard");
    connect(createBoard, &QPushButton::clicked, this, &MainWindow::onAddBoardClicked);
}

MainWindow::~MainWindow() {
    delete curWidget;
}

QWidget* MainWindow::Draw() const {
    // Central //
    QWidget* centralWidget = new QWidget();
    centralWidget->setObjectName("centralWidget");
    centralWidget->setContentsMargins(0, 0, 0, 0);

    QVBoxLayout* centralLayout = new QVBoxLayout(centralWidget);
    centralLayout->setObjectName("centralLayout");
    centralLayout->setContentsMargins(0, 0, 0, 0);
    centralLayout->setSpacing(0);

    // Main //
    QWidget* mainWidget = new QWidget();
    mainWidget->setObjectName("mainWidget");
    mainWidget->setContentsMargins(0, 0, 0, 0);

    QHBoxLayout* mainLayout = new QHBoxLayout(mainWidget);
    mainLayout->setObjectName("mainLayout");
    mainLayout->setContentsMargins(0, 0, 0, 0);
    mainLayout->setSpacing(0);

    // Add Navbar and Main //
    centralLayout->addWidget(navbar.Draw());
    centralLayout->addWidget(mainWidget);

    // Add to Main Layout
    mainLayout->addWidget(menu.Draw(), Qt::AlignLeft);
    mainLayout->addWidget(curWidget, Qt::AlignLeft);

    // Styles //
    centralWidget->setStyleSheet(QString::fromUtf8("* {\n"
                                                   "  font-family: \"Times New Roman\", Times, serif;\n"
                                                   "  font-size: 16px;\n"
                                                   "  font-weight: Normal;\n"
                                                   "}\n"
                                                   ""));

    return centralWidget;
}

void MainWindow::resizeEvent(QResizeEvent* event) {
    resize();
}

void MainWindow::resize() {
    // For Scroll Columns //
    QWidget* centralWidget = findChild<QWidget*>("centralWidget");
    QWidget* navbarWidget = findChild<QWidget*>("navbarWidget");
    QWidget* menuWidget = findChild<QWidget*>("menuWidget");

    QWidget* headerBoardWidget = findChild<QWidget*>("headerBoardWidget");

    QScrollArea* scrollAreaBoard = findChild<QScrollArea*>("scrollAreaBoard");

    if (scrollAreaBoard) {
        int height = centralWidget->size().height() - navbarWidget->size().height() -
                     headerBoardWidget->size().height();
        int width = centralWidget->size().width() - menuWidget->size().width();

        scrollAreaBoard->resize(width, height);

        // For Each Column Size //
        QVector<QWidget*> columnWidgets = findChildren<QWidget*>("columnWidget");

        foreach (QWidget* columnWidget, columnWidgets) {
            QVBoxLayout* cardsLayout = columnWidget->findChild<QVBoxLayout*>("cardsLayout");
            QScrollArea* scrollAreaCards = columnWidget->findChild<QScrollArea*>("scrollAreaCards");
            QWidget* addCardWidget = columnWidget->findChild<QWidget*>("addCardWidget");

            if (cardsLayout->sizeHint().height() != scrollAreaCards->size().height()) {
                columnWidget->setFixedSize(columnWidget->size().width(), height - 20);

                scrollAreaCards->setFixedSize(columnWidget->size().width() - 20,
                                              height - 75 - addCardWidget->size().height());
            }
        }
    }
}