#include "registrationdlg.h"
#include "ui_registrationdlg.h"

#include <QComboBox>
#include <QMessageBox>

#include "../dbmanager.h"

RegistrationDlg::RegistrationDlg(users_t& users, QWidget *parent)
    : m_users(users), m_mode{DlgMode::LogIn}, QDialog(parent)
    , ui(new Ui::RegistrationDlg)
{
    ui->setupUi(this);

    init();
}

RegistrationDlg::~RegistrationDlg()
{
    delete ui;
}

void RegistrationDlg::changeMode(DlgMode mode)
{
    m_mode = mode;
    if(m_mode == DlgMode::Registration){
        ui->nicknameComboBox->hide();
        ui->headerLabel->setText("Регистрация нового пользователя");
        ui->registrationBtn->hide();
        ui->repeatPasswordLabel->show();
        ui->repeatPasswordEdit->show();
        ui->nicknameEdit->show();
    }
    else if(m_mode == DlgMode::LogIn){
        ui->nicknameComboBox->clear();
        ui->repeatPasswordLabel->hide();
        ui->repeatPasswordEdit->hide();
        ui->nicknameEdit->hide();
        for(const auto& user : m_users){
            std::string name = std::get<1>(user);
            std::string password = std::get<2>(user);
            ui->nicknameComboBox->addItem(QString::fromStdString(name), QString::fromStdString(password));
        }
    }
}

void RegistrationDlg::init()
{
    this->setWindowTitle("");
    initConnects();

    if(m_users.empty()){
        changeMode(DlgMode::Registration);

    }else{
        changeMode(DlgMode::LogIn);
    }
}

void RegistrationDlg::initConnects()
{
    QObject::connect(ui->acceptBtn, &QPushButton::clicked, this, [&](){this->onAcceptBtnClicked();});
    QObject::connect(ui->exitBtn, &QPushButton::clicked, this, [&](){this->onExitBtnClicked();});
    QObject::connect(ui->registrationBtn, &QPushButton::clicked, this, [&](){this->onRegistrationBtnClicked();});
}

void RegistrationDlg::onAcceptBtnClicked()
{
    if(m_mode == DlgMode::Registration){
        std::string nickname = ui->nicknameEdit->text().toStdString();
        std::string password = ui->passwordEdit->text().toStdString();
        std::string repeat_password = ui->repeatPasswordEdit->text().toStdString();

        if(password != repeat_password){
            QMessageBox msg;
            msg.setText("Пароли не совпадают!");
            msg.exec();
            return;
        }

        if(password == "" || nickname == ""){
            QMessageBox msg;
            msg.setText("Не все поля заполнены");
            msg.exec();
            return;
        }

        for (const auto& user : m_users){
            if(nickname == std::get<1>(user)){
                QMessageBox msg;
                msg.setText("Пользователь с таким никнэймом уже существует!");
                msg.exec();
                return;
            }
        }

        auto dbmanager = DBManager::instance();
        dbmanager->addNewUser(nickname, password);
        accept();
    }
    else if(m_mode == DlgMode::LogIn){
        std::string nickname = ui->nicknameComboBox->currentText().toStdString();
        std::string password = ui->passwordEdit->text().toStdString();

        std::tuple<int, std::string, std::string> found_user{-1,"",""};
        for(const auto& user : m_users){
            if(std::get<1>(user) == nickname){
                found_user = user;
            }
        }

        if(std::get<0>(found_user) == -1){
            QMessageBox msg;
            msg.setText("Пользователь не найден");
            msg.exec();
            return;
        }

        if(password == "" || nickname == ""){
            QMessageBox msg;
            msg.setText("Не все поля заполнены");
            msg.exec();
            return;
        }

        if(password != std::get<2>(found_user)){
            QMessageBox msg;
            msg.setText("Неправильный пароль");
            msg.exec();
            return;
        }
        accept();
    }
}

void RegistrationDlg::onExitBtnClicked()
{
    reject();
}

void RegistrationDlg::onRegistrationBtnClicked()
{
    changeMode(DlgMode::Registration);
}
