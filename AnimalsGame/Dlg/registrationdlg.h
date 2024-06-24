#ifndef REGISTRATIONDLG_H
#define REGISTRATIONDLG_H

#include <QDialog>

#include <vector>
#include <tuple>

typedef std::vector<std::tuple<int, std::string, std::string>> users_t;
enum class DlgMode{
    LogIn = 0,
    Registration = 1,
};

namespace Ui {
class RegistrationDlg;
}

class RegistrationDlg : public QDialog
{
    Q_OBJECT

public:
    explicit RegistrationDlg(users_t& users, QWidget *parent = nullptr);
    ~RegistrationDlg();

public:
    void changeMode(DlgMode mode);

private slots:
    void onAcceptBtnClicked();

    void onExitBtnClicked();

    void onRegistrationBtnClicked();

private:
    void init();
    void initConnects();

private:
    users_t m_users;
    DlgMode m_mode;

private:
    Ui::RegistrationDlg *ui;
};

#endif // REGISTRATIONDLG_H
