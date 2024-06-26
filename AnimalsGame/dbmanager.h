#ifndef DBMANAGER_H
#define DBMANAGER_H

#include <QObject>

class DBManager
{
public:
    static DBManager* instance();
    void connectToAnimalsDB();

    std::vector<std::tuple<int, std::string, std::string>> getUsers();
    void addNewUser(const std::string& nickname, const std::string& password);
    void saveTreeData(const std::string& tree_data);
    std::string getTreeData();
private:
    DBManager();
    ~DBManager();
    DBManager(DBManager&) = delete;
    void operator=(DBManager&) = delete;
private:
    void initAnimalsDB();
};

namespace DBManagerSin{

}

#endif // DBMANAGER_H
