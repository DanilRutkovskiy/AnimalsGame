#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include "animalstree.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    AnimalsTreeNode node(NodeType::Question, "123");

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
