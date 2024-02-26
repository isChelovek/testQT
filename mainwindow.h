#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;

    enum {
        COLUMN_LAST_NAME,
        COLUMN_FIRST_NAME,
        COLUMN_MIDDLE_NAME,
        COLUMN_ACTION
    };

private slots:
    void onBtnClicked();

private:
    QWidget* createButtonWidget() const;
};
#endif // MAINWINDOW_H
