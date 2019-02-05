#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "graphwidget.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow() override;

private:
    Ui::MainWindow *ui;
    GraphWidget* widget;
    void processAnimations();
    // QWidget interface
protected:
    void keyPressEvent(QKeyEvent *event) override;
private slots:
    void on_action_exit_triggered();
    void addAnimations();
};

#endif // MAINWINDOW_H
