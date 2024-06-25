#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <memory>

#include "thegame.h"


QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    void init();
    void initConnects();

private slots:
    void onExitBtnClicked();

private:
    Ui::MainWindow *ui;
    std::unique_ptr<TheGame> m_game;
};
#endif // MAINWINDOW_H
