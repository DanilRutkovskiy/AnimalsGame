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

namespace MainWindowNs{
enum class Mode{
    MainMenu,
    Game,
};
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void changeMode(MainWindowNs::Mode mode);

private:
    void init();
    void initConnects();
    void onAnswer(const std::string& str);

private slots:
    void onExitBtnClicked();
    void onNewGameBtnClicked();
    void onYesBtnClicked();
    void onNoBtnClicked();

private:
    Ui::MainWindow *ui;
    std::unique_ptr<TheGame> m_game;
    MainWindowNs::Mode m_mode;
};
#endif // MAINWINDOW_H
