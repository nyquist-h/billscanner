#ifndef MAIN_H
#define MAIN_H

#include <QMainWindow>

namespace Ui {
class Main;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::Main *ui;
};

#endif // MAIN_H
