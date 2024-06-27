#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QMessageBox>
#include <QInputDialog>

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
        ui->mainTextEdit->clear();
        m_game->saveProgress();
        ui->mainTextEdit->appendPlainText("Игра \"Загадай животное\". Ваша задача загать животное, а игра должна его угадать.");
    }
    else if(m_mode == MainWindowNs::Mode::Game){
        ui->exitBtn->show();
        ui->newGameBtn->hide();
        ui->yesBtn->show();
        ui->noBtn->show();
        ui->newQuestionTextEdit->hide();
        ui->mainTextEdit->clear();
        m_game->newGame();
        onAnswer();
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

void MainWindow::onAnswer()
{
    std::string str = "";
    NodeType type = m_game->currentState(str);

    if (type == NodeType::Null){
        ui->mainTextEdit->appendPlainText("Животное не найдено.\nНапишите животное, которое вы загадали, а затем введите вопрос, который поможет его отгадать.");
    }
    else if (type == NodeType::Answer){
        str += "?";
        ui->mainTextEdit->appendPlainText(str.c_str());
        QMessageBox msg;
        msg.setText(QString::fromStdString(str));
        msg.setInformativeText("");
        msg.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
        msg.setDefaultButton(QMessageBox::Yes);

        if(msg.exec() == QMessageBox::Yes){
            changeMode(MainWindowNs::Mode::MainMenu);
        }
        else{
            QString new_animal, new_question;
            QInputDialog dlg;
            dlg.setInputMode(QInputDialog::TextInput);
            dlg.setLabelText("Пожалуйста напишите животное, которое вы загадали");
            if(dlg.exec() == QDialog::Accepted){
                new_animal = dlg.textValue();
            }
            else{
                changeMode(MainWindowNs::Mode::MainMenu);
                return;
            }

            dlg.setLabelText("Пожалуйста, напишите вопрос, который поможет отгадать данное животное");
            if(dlg.exec() == QDialog::Accepted){
                new_question = dlg.textValue();
            }
            else{
                changeMode(MainWindowNs::Mode::MainMenu);
                return;
            }

            if(new_animal == "" || new_question == ""){
                QMessageBox msg;
                msg.setText("Неверно введены данные, попробовать еще раз?");
                msg.setInformativeText("");
                msg.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
                msg.setDefaultButton(QMessageBox::Yes);

                if(msg.exec() == QMessageBox::Yes){
                    onAnswer();
                }
                else{
                    changeMode(MainWindowNs::Mode::MainMenu);
                    return;
                }
            }
            else{
                m_game->addNewQuestion(new_question.toStdString(), new_animal.toStdString());
                changeMode(MainWindowNs::Mode::MainMenu);
            }
        }
    }
    else if (type == NodeType::Question){
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
    onAnswer();
}

void MainWindow::onNoBtnClicked()
{
    m_game->answerNo();
    onAnswer();
}
