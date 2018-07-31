#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "vision.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_pushButton_clicked(bool checked);

    void on_onoffbtn_clicked();

    void on_onoffbtn_2_clicked();

    void on_onoffbtn_3_clicked();

    void on_onoffbtn_4_clicked();

    void on_cambtn_clicked();

    void on_filterbtn_clicked();

    void on_colorbtn_clicked();

    void on_robotbtn_clicked();

    void on_addnewColorbtn_clicked();

    void on_cancelColorbtn_clicked();

    void on_mapsbtn_clicked();

    void on_perspetivebtn_clicked();

    void on_selectFieldsbtn_clicked();

    void on_editColorbtn_clicked();

    void on_addnewRobotbtn_clicked();

    void on_editRobotbtn_clicked();

    void on_cancelPerspectivebtn_clicked();

    void on_cancelSelectFieldbtn_2_clicked();

    void on_cancelAddNewColorbtn_2_clicked();

    void on_cancelEditbtn_clicked();

    void on_cancelAddNewRobotbtn_2_clicked();

    void on_cancelEditRobotsbtn_clicked();

    void on_upperhuesld_2_sliderMoved(int position);

    void on_lowhuesld_2_sliderMoved(int position);

    void on_uppersaturationsld_2_actionTriggered(int action);

    void on_lowsaturationsld_2_sliderMoved(int position);

    void on_uppervaluesld_2_sliderMoved(int position);

    void on_lowvaluesld_2_sliderMoved(int position);

    void on_uppersaturationsld_2_sliderMoved(int position);

    void on_confirmNameAddNewColorbtn_2_clicked();

    void on_confirmPerspectivebtn_clicked();

    void on_confirmSelectFieldbtn_2_clicked();

    void on_confirmEditbtn_clicked();

    void on_confirmAddNewRobotbtn_2_clicked();

    void on_confirmEditRobotsbtn_clicked();

    void on_selectFieldSelectFieldsbtn_2_clicked();

    void on_allySideSelectFieldbtn_2_clicked();

    void on_enemySideSelectFieldsbtn_2_clicked();

    void on_selectPointFieldbtn_2_clicked();

    void on_selectPerspectivebtn_clicked();

    void on_idckb_currentIndexChanged(int index);

private:
    Ui::MainWindow *ui;
    Vision *vision;
};

#endif // MAINWINDOW_H
