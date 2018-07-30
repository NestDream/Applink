#ifndef USER_H
#define USER_H
#include <QDialog>

class User
{
public:
    User(char* name,double time);
    ~User();
    char* Get_Name() const;
    double Get_Time() const;
    void point(char* Name,double Time);
    void Game_End(QString qname, double now_time);
    void set_name(char* Name);
    void set_time(double Time);
    QString qname;
private:
    char* name;
    double time;
};

class eUser{
public:
    static User user;
};

#endif // USER_H
