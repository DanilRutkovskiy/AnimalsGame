#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include "animalstree.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , m_game{std::make_unique<TheGame>()}
{
    ui->setupUi(this);

    init();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::init()
{
    initConnects();
}

void MainWindow::initConnects()
{
    QObject::connect(ui->exitBtn, &QPushButton::clicked, this, [&](){this->onExitBtnClicked();});
}

void MainWindow::onExitBtnClicked()
{
    QApplication::closeAllWindows();
}
