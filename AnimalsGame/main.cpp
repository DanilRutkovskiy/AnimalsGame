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

    RegistrationDlg dlg{users};
    if(QDialog::Accepted  == dlg.exec()){
        MainWindow w;
        w.show();
        return a.exec();
    }

    return 0;
}
