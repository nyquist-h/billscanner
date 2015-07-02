#ifndef MAIN_H
#define MAIN_H

#include <QMainWindow>

namespace Ui {
  class mainWindow;
}

class MainWindow : public QMainWindow
{
  Q_OBJECT

  public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

  private slots:
      void on_load_btn_clicked();
  private:
    Ui::mainWindow *ui;
    QImage m_displayedImage;
};

#endif // MAIN_H
