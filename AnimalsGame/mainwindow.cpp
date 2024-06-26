#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , m_game{std::make_unique<TheGame>()}
    , m_mode(MainWindowNs::Mode::MainMenu)
{
    ui->setupUi(this);

    init();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::changeMode(MainWindowNs::Mode mode)
{
    m_mode = mode;
    if(m_mode == MainWindowNs::Mode::MainMenu){
        ui->exitBtn->show();
        ui->newGameBtn->show();
        ui->yesBtn->hide();
        ui->noBtn->hide();
        ui->newQuestionTextEdit->hide();
    }
    else if(m_mode == MainWindowNs::Mode::Game){
        ui->exitBtn->show();
        ui->newGameBtn->hide();
        ui->yesBtn->show();
        ui->noBtn->show();
        ui->newQuestionTextEdit->hide();
        ui->mainTextEdit->clear();
        ui->mainTextEdit->appendPlainText(m_game->getQuestion().c_str());
    }
    else{
        assert(0);
    }
}

void MainWindow::init()
{
    changeMode(MainWindowNs::Mode::MainMenu);
    initConnects();
}

void MainWindow::initConnects()
{
    QObject::connect(ui->exitBtn, &QPushButton::clicked, this, [&](){this->onExitBtnClicked();});
    QObject::connect(ui->newGameBtn, &QPushButton::clicked, this, [&](){this->onNewGameBtnClicked();});
    QObject::connect(ui->yesBtn, &QPushButton::clicked, this, [&](){this->onYesBtnClicked();});
    QObject::connect(ui->noBtn, &QPushButton::clicked, this, [&](){this->onNoBtnClicked();});
}

void MainWindow::onAnswer(const std::string &str)
{
    ui->mainTextEdit->clear();
    if(str.empty()){
        ui->mainTextEdit->appendPlainText("Животное не найдено.\n Напишите животное, которое вы загадали, а затем введите вопрос, который поможет его отгадать.");
    }else{
        ui->mainTextEdit->appendPlainText(str.c_str());
    }
}

void MainWindow::onExitBtnClicked()
{
    if(m_mode == MainWindowNs::Mode::Game){
        changeMode(MainWindowNs::Mode::MainMenu);
    }
    else if(m_mode == MainWindowNs::Mode::MainMenu){
        QApplication::closeAllWindows();
    }
    else{
        assert(0);
    }
}

void MainWindow::onNewGameBtnClicked()
{
    changeMode(MainWindowNs::Mode::Game);
}

void MainWindow::onYesBtnClicked()
{
    m_game->answerYes();
    onAnswer(m_game->getQuestion());
}

void MainWindow::onNoBtnClicked()
{
    m_game->answerNo();
    onAnswer(m_game->getQuestion());
}
