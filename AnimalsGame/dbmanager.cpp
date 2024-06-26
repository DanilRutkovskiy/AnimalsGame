#include "dbmanager.h"

#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlError>
#include <QDebug>
#include <QMessageBox>

namespace DBManagerSin{
DBManager* db_manager = nullptr;
}

DBManager::DBManager() {}

DBManager::~DBManager()
{
    auto db = QSqlDatabase::addDatabase("QPSQL");
    db.close();
}

DBManager* DBManager::instance(){
    if(DBManagerSin::db_manager == nullptr){
        DBManagerSin::db_manager = new DBManager;
    }

    return DBManagerSin::db_manager;
}


void DBManager::connectToAnimalsDB(){
    auto db = QSqlDatabase::addDatabase("QPSQL", "Animals");
    db.setHostName("127.0.0.1");
    db.setDatabaseName("Animals");
    db.setUserName("postgres");
    db.setPassword("secret");
    db.setPort(5432);

    if(!db.open()){
        qDebug() << "No database connection";
        assert(0);
        return;
    }

    initAnimalsDB();
}

std::vector<std::tuple<int, std::string, std::string>> DBManager::getUsers()
{
    auto db = QSqlDatabase::database("Animals");
    std::vector<std::tuple<int, std::string, std::string> > ret;
    if(!db.isOpen()){
        qDebug() << "No database connection";
        assert(0);
        return ret;
    }

    QSqlQuery query(db);

    if(!query.exec("SELECT id, nickname, password FROM public.users")){
        qDebug() << "Query error:" <<  query.lastError().text();
        assert(0);
        return ret;
    }

    while(query.next()){
        int id = query.value(0).toInt();
        std::string nickname = query.value(1).toString().toStdString();
        std::string password = query.value(2).toString().toStdString();
        ret.emplace_back(id, nickname, password);
    }

    return std::move(ret);
}

void DBManager::initAnimalsDB()
{
    auto db = QSqlDatabase::database("Animals");

    if(!db.open()){
        qDebug() << "NO DB Connection";
        assert(0);
        return;
    }

     QSqlQuery query(db);

    QString s_query = "create table if not exists public.users(id serial primary key, nickname text not null, password text not null);";

    if(!query.exec(s_query)){
        qDebug() << QString::fromLocal8Bit(query.lastError().text().toStdString().c_str());
        assert(0);
        return;
    }

    s_query = "create table if not exists public.questions_tree(id serial primary key, data text);";

    if(!query.exec(s_query)){
        qDebug() << QString::fromLocal8Bit(query.lastError().text().toStdString().c_str());
        assert(0);
        return;
    }

    s_query = "SELECT * FROM public.questions_tree;";

    if(!query.exec(s_query)){
        qDebug() << QString::fromLocal8Bit(query.lastError().text().toStdString().c_str());
        assert(0);
        return;
    }

    int c = 0;
    while(query.next()){
        c++;
        break;
    }

    if(c == 0){
        s_query = "INSERT INTO public.questions_tree (id, data) VALUES (1, '');";
    }

    if(!query.exec(s_query)){
        qDebug() << QString::fromLocal8Bit(query.lastError().text().toStdString().c_str());
        assert(0);
        return;
    }

    if (!query.isActive()) {
        qDebug() << "Не удалось инициализировать базу данных.";
        assert(0);
        return;
    }
}


void DBManager::addNewUser(const std::string &nickname, const std::string &password)
{
    auto db = QSqlDatabase::database("Animals");

    if(!db.isOpen()){
        qDebug() << "No database connection";
        assert(0);
        return;
    }

    QSqlQuery query(db);

    query.prepare("INSERT INTO public.users (nickname, password) VALUES(?, ?);");

    query.bindValue(0, QString::fromStdString(nickname));
    query.bindValue(1, QString::fromStdString(password));

    if(!query.exec()){
        qDebug() << QString::fromLocal8Bit(query.lastError().text().toStdString().c_str());
        assert(0);
        return;
    }

    if (!query.isActive()) {
        qDebug() << "Can initialize database";
        assert(0);
        return;
    }
}

void DBManager::saveTreeData(const std::string &tree_data)
{
    auto db = QSqlDatabase::database("Animals");

    if(!db.isOpen()){
        qDebug() << "No database connection";
        assert(0);
        return;
    }

    QSqlQuery query(db);

    query.prepare("UPDATE public.questions_tree SET data = ? WHERE id = 1");

    query.bindValue(0, QString::fromStdString(tree_data));

    if(!query.exec()){
        qDebug() << QString::fromLocal8Bit(query.lastError().text().toStdString().c_str());
        assert(0);
        return;
    }

    if (!query.isActive()) {
        qDebug() << "Can initialize database";
        assert(0);
        return;
    }
}

std::string DBManager::getTreeData()
{
    auto db = QSqlDatabase::database("Animals");

    if(!db.isOpen()){
        qDebug() << "No database connection";
        assert(0);
        return "";
    }

    QSqlQuery query(db);

    QString s_query = "SELECT data FROM public.questions_tree WHERE id = 1;";

    if(!query.exec(s_query)){
        qDebug() << QString::fromLocal8Bit(query.lastError().text().toStdString().c_str());
        assert(0);
        return "";
    }

    QString ret = "";
    while(query.next()){
        ret = query.value(0).toString();
    }

    return ret.toStdString();
}

void DBManager::makeBackup()
{
    auto db = QSqlDatabase::database("Animals");

    if(!db.isOpen()){
        qDebug() << "No database connection";
        assert(0);
        return ;
    }

    QSqlQuery query(db);

    QString s_query = "SELECT data FROM public.questions_tree WHERE id = 1;";

    if(!query.exec(s_query)){
        qDebug() << QString::fromLocal8Bit(query.lastError().text().toStdString().c_str());
        assert(0);
        return;
    }

    QString ret = "";
    while(query.next()){
        ret = query.value(0).toString();
    }

    s_query = "SELECT data FROM public.questions_tree WHERE id = 2;";

    if(!query.exec(s_query)){
        qDebug() << QString::fromLocal8Bit(query.lastError().text().toStdString().c_str());
        assert(0);
        return;
    }

    bool exists = false;
    while(query.next()){
        exists = true;
    }

    if(exists){
        query.prepare("UPDATE public.questions_tree SET data = ? WHERE id = 2");

        query.bindValue(0, ret);
    }
    else{
        query.prepare("INSERT INTO public.questions_tree (id, data) VALUES(2, ?);");

        query.bindValue(0, ret);
    }

    if(!query.exec()){
        qDebug() << QString::fromLocal8Bit(query.lastError().text().toStdString().c_str());
        assert(0);
        return;
    }
}

bool DBManager::isConnectedToAnimalsDB()
{
    auto db = QSqlDatabase::database("Animals");

    return db.isOpen();
}
