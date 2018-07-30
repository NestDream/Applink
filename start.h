#ifndef START_H
#define START_H
#include"user.h"
#include <QDialog>

class QLabel;
class QPushButton;
class QLineEdit;


class Enter : public QDialog
{
    Q_OBJECT

public:
    Enter(QWidget *parent = 0);
    QPushButton *startButton;
    User *user;
signals:
    void EnterGame(const QString &str,Qt::CaseSensitivity cs);
    void EnterPrevious(const QString &str,Qt::CaseSensitivity cs);

private slots:
    void enableFindButton(const QString &text);
    void startClicked();

private:
    QLabel *label;
    QLineEdit *lineEdit;
    QPushButton *returnButton;
};
#endif // START_H
