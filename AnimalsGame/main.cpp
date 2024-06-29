#include "mainwindow.h"
#include <QApplication>
#include <QMessageBox>

#include "Dlg/registrationdlg.h"

#include "dbmanager.h"
#include <QDebug>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    auto db_manager = DBManager::instance();
    db_manager->connectToAnimalsDB();
    auto users = db_manager->getUsers();

    if(db_manager->isConnectedToAnimalsDB()){
        RegistrationDlg dlg{users};
        if(QDialog::Accepted  == dlg.exec()){
            //TODO добавить код для обработки выбранного пользователя
        }
    }

    MainWindow w;
    w.show();
    return a.exec();
}
