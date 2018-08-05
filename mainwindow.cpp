#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QApplication>
#include <QMessageBox>

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <stdio.h>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include "opencv2/opencv.hpp"
#include <iostream>
#include <QString>
#include <QApplication>

#include <iomanip>
#include <sstream>
#include <string>
#include <vector>

using namespace cv;
using namespace std;

bool cameraFlag_clicked = true;
bool gaussianFlag_clicked = true, blurringFlag_clicked = true, barinoFlag_clicked = true;
bool changeflag;


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    qRegisterMetaType<Mat>("Mat");

    vision = new Vision;

    //setVisibleIcons(false,false,false,false);
    ui->cameragbx->setVisible(false);
    ui->filtergbx->setVisible(false);
    ui->colorgbx->setVisible(false);
    ui->robotgbx->setVisible(false);
    ui->perpectivegbx->setVisible(false);

    QStringList text = readText("config/colors");
    for(int i = 0; i < text.size()-1;i = i+7)
    {
        ui->editColorcmb->addItem(text.at(i).toLocal8Bit().constData());
    }
    vision->loadColorRanges(text);

    ui->miniwindowswt->setCurrentIndex(0);

    connect(vision, SIGNAL(emit_segmentationImage(Mat)), this, SLOT(updateSegmentaionImage(Mat)), Qt::QueuedConnection);
    connect(vision, SIGNAL(emit_fieldImage(Mat)), this, SLOT(updateFieldImage(Mat)), Qt::QueuedConnection);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_idckb_currentIndexChanged(int index)
{
    vision->setCameraId(index);
}

void MainWindow::on_onoffbtn_clicked()
{
    if(cameraFlag_clicked)
    {
        QPixmap onPM(":/icons/on.png");
        QIcon onI(onPM);
        ui->onoffbtn->setIcon(onI);
        cameraFlag_clicked = false;
        vision->openCamera();
        vision->running = true;
        vision->start();
    }
    else
    {
        QPixmap offPM(":/icons/off.png");
        QIcon offI(offPM);
        ui->onoffbtn->setIcon(offI);
        cameraFlag_clicked = true;
        vision->running = false;
        vision->closeCamera();

    }
}

void MainWindow::on_pushButton_clicked(bool clicked)
{
    //funcao nao utilizada
}

void MainWindow::on_onoffbtn_2_clicked()
{
    if(gaussianFlag_clicked)
    {
        QPixmap onPM(":/icons/on.png");
        QIcon onI;

        onI.addPixmap(onPM);
        ui->onoffbtn_2->setIcon(onI);
        gaussianFlag_clicked = false;
    }
    else
    {
        QPixmap offPM(":/icons/off.png");
        QIcon offI;

        offI.addPixmap(offPM);
        ui->onoffbtn_2->setIcon(offI);
        gaussianFlag_clicked = true;
    }
}

void MainWindow::on_onoffbtn_3_clicked()
{
    if(blurringFlag_clicked)
    {
        QPixmap onPM(":/icons/on.png");
        QIcon onI;

        onI.addPixmap(onPM);
        ui->onoffbtn_3->setIcon(onI);
        blurringFlag_clicked = false;
    }
    else
    {
        QPixmap offPM(":/icons/off.png");
        QIcon offI;

        offI.addPixmap(offPM);
        ui->onoffbtn_3->setIcon(offI);
        blurringFlag_clicked = true;
    }
}

void MainWindow::on_onoffbtn_4_clicked()
{
    if(barinoFlag_clicked)
    {
        QPixmap onPM(":/icons/on.png");
        QIcon onI;

        onI.addPixmap(onPM);
        ui->onoffbtn_4->setIcon(onI);
        barinoFlag_clicked = false;
    }
    else
    {
        QPixmap offPM(":/icons/off.png");
        QIcon offI;

        offI.addPixmap(offPM);
        ui->onoffbtn_4->setIcon(offI);
        barinoFlag_clicked = true;
    }
}

void MainWindow::on_cambtn_clicked()
{
    //setVisibleIcons(true,false,false,false);
    ui->cameragbx->setVisible(true);
    ui->filtergbx->setVisible(false);
    ui->colorgbx->setVisible(false);
    ui->robotgbx->setVisible(false);
    ui->perpectivegbx->setVisible(false);
    ui->miniwindowswt->setCurrentIndex(7);
    ui->camerainfolbl->setVisible(true);
    ui->filterinfolbl->setVisible(false);
    ui->mapinfolbl->setVisible(false);
    ui->colorinfolbl->setVisible(false);
    ui->robotinfolbl->setVisible(false);
}

void MainWindow::on_filterbtn_clicked()
{
    ui->cameragbx->setVisible(false);
    ui->filtergbx->setVisible(true);
    ui->colorgbx->setVisible(false);
    ui->robotgbx->setVisible(false);
    ui->perpectivegbx->setVisible(false);
    ui->miniwindowswt->setCurrentIndex(7);
    ui->camerainfolbl->setVisible(false);
    ui->filterinfolbl->setVisible(true);
    ui->mapinfolbl->setVisible(false);
    ui->colorinfolbl->setVisible(false);
    ui->robotinfolbl->setVisible(false);
}

void MainWindow::on_colorbtn_clicked()
{
    ui->cameragbx->setVisible(false);
    ui->filtergbx->setVisible(false);
    ui->colorgbx->setVisible(true);
    ui->robotgbx->setVisible(false);
    ui->perpectivegbx->setVisible(false);
    ui->miniwindowswt->setCurrentIndex(7);
    ui->camerainfolbl->setVisible(false);
    ui->filterinfolbl->setVisible(false);
    ui->mapinfolbl->setVisible(false);
    ui->colorinfolbl->setVisible(true);
    ui->robotinfolbl->setVisible(false);
}

void MainWindow::on_robotbtn_clicked()
{
    ui->cameragbx->setVisible(false);
    ui->filtergbx->setVisible(false);
    ui->colorgbx->setVisible(false);
    ui->robotgbx->setVisible(true);
    ui->perpectivegbx->setVisible(false);
    ui->miniwindowswt->setCurrentIndex(7);
    ui->camerainfolbl->setVisible(false);
    ui->filterinfolbl->setVisible(false);
    ui->mapinfolbl->setVisible(false);
    ui->colorinfolbl->setVisible(false);
    ui->robotinfolbl->setVisible(true);
}

void MainWindow::on_addnewColorbtn_clicked()
{
    ui->miniwindowswt->setCurrentIndex(3);
    vision->setVisionMode(SET_COLORS_MODE);
}

void MainWindow::on_cancelColorbtn_clicked()
{
    ui->mainButtongbx->setVisible(true);
}

void MainWindow::on_mapsbtn_clicked()
{
    ui->cameragbx->setVisible(false);
    ui->filtergbx->setVisible(false);
    ui->colorgbx->setVisible(false);
    ui->robotgbx->setVisible(false);
    ui->perpectivegbx->setVisible(true);
    ui->miniwindowswt->setCurrentIndex(7);
    ui->camerainfolbl->setVisible(false);
    ui->filterinfolbl->setVisible(false);
    ui->mapinfolbl->setVisible(true);
    ui->colorinfolbl->setVisible(false);
    ui->robotinfolbl->setVisible(false);


}

void MainWindow::on_perspetivebtn_clicked()
{
    ui->miniwindowswt->setCurrentIndex(1);
    QImage img = QImage( (uchar*) vision->virtualField.data, vision->virtualField.cols, vision->virtualField.rows, vision->virtualField.step, QImage::Format_RGB888);
    ui->camPerspetctivelbl->setPixmap(QPixmap::fromImage(img));
    ui->camPerspetctivelbl->setScaledContents(true);
    ui->camPerspetctivelbl->show();
}

void MainWindow::on_selectFieldsbtn_clicked()
{
    ui->miniwindowswt->setCurrentIndex(2);
    ui->allySideSelectFieldbtn_2->setVisible(false);
    ui->enemySideSelectFieldsbtn_2->setVisible(false);
    QPixmap map(":/icons/campoTela.png");
    ui->camPerspetctivelbl->setPixmap(map);
    ui->camPerspetctivelbl->setScaledContents(true);
}

void MainWindow::on_editColorbtn_clicked()
{
    ui->miniwindowswt->setCurrentIndex(4);
    vision->updateLUT();

}

void MainWindow::on_addnewRobotbtn_clicked()
{
    ui->miniwindowswt->setCurrentIndex(5);
}

void MainWindow::on_editRobotbtn_clicked()
{
    ui->miniwindowswt->setCurrentIndex(6);
}

void MainWindow::on_cancelPerspectivebtn_clicked()
{
    if(changeflag)
    {
        QMessageBox::StandardButton question;
        question = QMessageBox::question(this,"Warning","Do you want to quit, without saving the changes?",QMessageBox::Yes|QMessageBox::No);
        if(question == QMessageBox::Yes)
        {
            ui->miniwindowswt->setCurrentIndex(0);
        }
    }
    else
    {
        ui->miniwindowswt->setCurrentIndex(0);
    }
}

void MainWindow::on_cancelSelectFieldbtn_2_clicked()
{
    if(changeflag)
    {
        QMessageBox::StandardButton question;
        question = QMessageBox::question(this,"Warning","Do you want to quit, without saving the changes?",QMessageBox::Yes|QMessageBox::No);
        if(question == QMessageBox::Yes)
        {
            ui->miniwindowswt->setCurrentIndex(0);
        }
    }
    else
    {
        ui->miniwindowswt->setCurrentIndex(0);
    }
}

void MainWindow::on_cancelAddNewColorbtn_2_clicked()
{
    if(changeflag)
    {
        QMessageBox::StandardButton question;
        question = QMessageBox::question(this,"Warning","Do you want to quit, without saving the changes?",QMessageBox::Yes|QMessageBox::No);
        if(question == QMessageBox::Yes)
        {
            ui->miniwindowswt->setCurrentIndex(0);
        }
    }
    else
    {
        ui->miniwindowswt->setCurrentIndex(0);
    }
    vision->setVisionMode(DO_NOTHING);
}

void MainWindow::on_cancelEditColorbtn_4_clicked()
{
    if(changeflag)
    {
        QMessageBox::StandardButton question;
        question = QMessageBox::question(this,"Warning","Do you want to quit, without saving the changes?",QMessageBox::Yes|QMessageBox::No);
        if(question == QMessageBox::Yes)
        {
            ui->miniwindowswt->setCurrentIndex(0);
        }
    }
    else
    {
        ui->miniwindowswt->setCurrentIndex(0);
    }
    vision->setVisionMode(DO_NOTHING);
}

void MainWindow::on_cancelEditbtn_clicked()
{
    if(changeflag)
    {
        QMessageBox::StandardButton question;
        question = QMessageBox::question(this,"Warning","Do you want to quit, without saving the changes?",QMessageBox::Yes|QMessageBox::No);
        if(question == QMessageBox::Yes)
        {
            ui->miniwindowswt->setCurrentIndex(0);
        }
    }
    else
    {
        ui->miniwindowswt->setCurrentIndex(0);
    }
}

void MainWindow::on_cancelAddNewRobotbtn_2_clicked()
{
    if(changeflag)
    {
        QMessageBox::StandardButton question;
        question = QMessageBox::question(this,"Warning","Do you want to quit, without saving the changes?",QMessageBox::Yes|QMessageBox::No);
        if(question == QMessageBox::Yes)
        {
            ui->miniwindowswt->setCurrentIndex(0);
        }
    }
    else
    {
        ui->miniwindowswt->setCurrentIndex(0);
    }
}

void MainWindow::on_cancelEditRobotsbtn_clicked()
{
    if(changeflag)
    {
        QMessageBox::StandardButton question;
        question = QMessageBox::question(this,"Warning","Do you want to quit, without saving the changes?",QMessageBox::Yes|QMessageBox::No);
        if(question == QMessageBox::Yes)
        {
            ui->miniwindowswt->setCurrentIndex(0);
        }
    }
    else
    {
        ui->miniwindowswt->setCurrentIndex(0);
    }
}

void MainWindow::on_upperhuesld_2_sliderMoved(int position)
{
    ui->maxhuelcd_2->display(position);
    updateSliderState(SET_COLORS_MODE);

}

void MainWindow::on_lowhuesld_2_sliderMoved(int position)
{
    ui->minhuelcd_2->display(position);
    updateSliderState(SET_COLORS_MODE);
}

void MainWindow::on_uppersaturationsld_2_actionTriggered(int action)
{
    //funcao nao faz nada
}

void MainWindow::on_lowsaturationsld_2_sliderMoved(int position)
{
    ui->lowsaturationlcd_2->display(position);
    updateSliderState(SET_COLORS_MODE);
}

void MainWindow::on_uppervaluesld_2_sliderMoved(int position)
{
    ui->uppervaluelcd_2->display(position);
    updateSliderState(SET_COLORS_MODE);
}

void MainWindow::on_lowvaluesld_2_sliderMoved(int position)
{
    ui->lowvaluelcd_2->display(position);
    updateSliderState(SET_COLORS_MODE);
}

void MainWindow::on_uppersaturationsld_2_sliderMoved(int position)
{
    ui->uppersaturationlcd_2->display(position);
    updateSliderState(SET_COLORS_MODE);
}

void MainWindow::on_upperhuesld_4_sliderMoved(int position)
{
    ui->maxhuelcd_4->display(position);
    updateSliderState(EDIT_COLORS_MODE);

}

void MainWindow::on_lowhuesld_4_sliderMoved(int position)
{
    ui->minhuelcd_4->display(position);
    updateSliderState(EDIT_COLORS_MODE);
}

void MainWindow::on_lowsaturationsld_4_sliderMoved(int position)
{
    ui->lowsaturationlcd_4->display(position);
    updateSliderState(EDIT_COLORS_MODE);
}

void MainWindow::on_uppervaluesld_4_sliderMoved(int position)
{
    ui->uppervaluelcd_4->display(position);
    updateSliderState(EDIT_COLORS_MODE);
}

void MainWindow::on_lowvaluesld_4_sliderMoved(int position)
{
    ui->lowvaluelcd_4->display(position);
    updateSliderState(EDIT_COLORS_MODE);
}

void MainWindow::on_uppersaturationsld_4_sliderMoved(int position)
{
    ui->uppersaturationlcd_4->display(position);
    updateSliderState(EDIT_COLORS_MODE);
}

void MainWindow::on_confirmNameAddNewColorbtn_2_clicked()
{
    color newColor;
    Vec3i min( ui->minhuelcd_2->value(), ui->lowsaturationlcd_2->value(), ui->lowvaluelcd_2->value());
    Vec3i max(ui->maxhuelcd_2->value(), ui->uppersaturationlcd_2->value(), ui->uppervaluelcd_2->value());

    newColor.name = ui->nameColorled_2->text().toUtf8().constData();
    newColor.minHSV = min;
    newColor.maxHSV = max;

    vision->addColor(newColor);
    
    // adicionar ao arquivo de texto
    
    
    changeflag = false;
    QMessageBox::warning(this,tr(":)"),tr("the changes have been saved"));
    ui->miniwindowswt->setCurrentIndex(0);
}

void MainWindow::on_confirmPerspectivebtn_clicked()
{
    changeflag = false;
    QMessageBox::warning(this,tr(":)"),tr("the changes have been saved"));
    ui->miniwindowswt->setCurrentIndex(0);
}

void MainWindow::on_confirmSelectFieldbtn_2_clicked()
{
    changeflag = false;
    QMessageBox::warning(this,tr(":)"),tr("the changes have been saved"));
    ui->miniwindowswt->setCurrentIndex(0);
}

void MainWindow::on_confirmEditbtn_clicked()
{
    changeflag = false;
    QMessageBox::warning(this,tr(":)"),tr("the changes have been saved"));
    ui->miniwindowswt->setCurrentIndex(0);
}

void MainWindow::on_confirmAddNewRobotbtn_2_clicked()
{
    changeflag = false;
    QMessageBox::warning(this,tr(":)"),tr("the changes have been saved"));
    ui->miniwindowswt->setCurrentIndex(0);
}

void MainWindow::on_confirmEditRobotsbtn_clicked()
{
    changeflag = false;
    QMessageBox::warning(this,tr(":)"),tr("the changes have been saved"));
    ui->miniwindowswt->setCurrentIndex(0);
}

void MainWindow::on_selectFieldSelectFieldsbtn_2_clicked()
{
    ui->allySideSelectFieldbtn_2->setVisible(true);
    ui->enemySideSelectFieldsbtn_2->setVisible(true);
}

void MainWindow::on_allySideSelectFieldbtn_2_clicked()
{
    changeflag = true;
    QMessageBox::warning(this,tr("Conclued"),tr("Left side choosen"));
}

void MainWindow::on_enemySideSelectFieldsbtn_2_clicked()
{
    changeflag = true;
    QMessageBox::warning(this,tr("Conclued"),tr("Right side choosen"));
}

void MainWindow::on_selectPointFieldbtn_2_clicked()
{
    ui->allySideSelectFieldbtn_2->setVisible(false);
    ui->enemySideSelectFieldsbtn_2->setVisible(false);
}

void MainWindow::on_selectPerspectivebtn_clicked()
{
    vision->setPerspectivePoints();
    vision->setVisionMode(PERSPECTIVE_MODE);
}

void MainWindow::updateSliderState(int mode)
{
    Vec3i min, max;
    if(mode == SET_COLORS_MODE){
        min = Vec3i( ui->minhuelcd_2->value(), ui->lowsaturationlcd_2->value(), ui->lowvaluelcd_2->value() );
        max = Vec3i( ui->maxhuelcd_2->value(), ui->uppersaturationlcd_2->value(), ui->uppervaluelcd_2->value() );
    }
    if(mode == EDIT_COLORS_MODE){
        min = Vec3i( ui->minhuelcd_4->value(), ui->lowsaturationlcd_4->value(), ui->lowvaluelcd_4->value() );
        min = Vec3i( ui->maxhuelcd_4->value(), ui->uppersaturationlcd_4->value(), ui->uppervaluelcd_4->value() );
    }
    vision->setCurrentMinHSV(min);
    vision->setCurrentMaxHSV(max);
}

void MainWindow::updateSegmentaionImage(Mat img)
{
    QImage image1 = QImage( (uchar*) img.data, img.cols, img.rows, img.step, QImage::Format_RGB888);

    ui->camAddNewColorlbl->setPixmap(QPixmap::fromImage(image1));
    ui->camAddNewColorlbl->show();
}

void MainWindow::updateFieldImage(Mat img)
{
    QImage image1 = QImage( (uchar*) img.data, img.cols, img.rows, img.step, QImage::Format_RGB888);

    ui->camPerspetctivelbl->setPixmap(QPixmap::fromImage(image1));
    ui->camPerspetctivelbl->show();
}


void MainWindow::on_editColorcmb_currentIndexChanged(int index)
{
    cout << index << endl;
    color currentColor = vision->getConfigColor(index);
    cout << currentColor.maxHSV[0] << endl;

    ui->lowhuesld_4->setValue(currentColor.minHSV[0]);
    ui->lowsaturationsld_4->setValue(currentColor.minHSV[1]);
    ui->lowvaluesld_4->setValue(currentColor.minHSV[2]);
    ui->upperhuesld_4->setValue(currentColor.maxHSV[0]);
    ui->uppersaturationsld_4->setValue(currentColor.maxHSV[1]);
    ui->uppervaluesld_4->setValue(currentColor.maxHSV[2]);

    ui->minhuelcd_4->display(currentColor.minHSV[0]);
    ui->lowsaturationlcd_4->display(currentColor.minHSV[1]);
    ui->lowvaluelcd_4->display(currentColor.minHSV[2]);
    ui->maxhuelcd_4->display(currentColor.maxHSV[0]);
    ui->uppersaturationlcd_4->display(currentColor.maxHSV[1]);
    ui->uppervaluelcd_4->display(currentColor.maxHSV[2]);

}


