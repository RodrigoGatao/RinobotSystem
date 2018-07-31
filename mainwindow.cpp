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

void onMouse(int event, int x,int y, int flags, void *userdata); //funtion who get the points

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    vision = new Vision;

    //setVisibleIcons(false,false,false,false);
    ui->cameragbx->setVisible(false);
    ui->filtergbx->setVisible(false);
    ui->colorgbx->setVisible(false);
    ui->robotgbx->setVisible(false);
    ui->perpectivegbx->setVisible(false);

    QPixmap alye ("/icons/allyIcon.png");
    QPixmap enemy("/icons/enemyIcon.png");
    QPixmap ball("/icons/ballIcon.png");
    QPixmap goalkepper("/icons/taffarelIcon.jpg");
    QPixmap defenser("/icons/zagueiro.png");
    QPixmap attacker("/icons/romarioIcon.png");

    ui->allyEditlbl->setPixmap(alye);
    ui->enemyEditlbl->setPixmap(enemy);
    ui->ballEditlbl->setPixmap(ball);
    ui->goalkeeperEditlbl->setPixmap(goalkepper);
    //ui->goalkeeperEditlbl->setScaledContents(true);
    ui->defenserEditlbl->setPixmap(defenser);
    ui->attackerEditlbl->setPixmap(attacker);
    //ui->attackerEditlbl->setScaledContents(true);
    ui->miniwindowswt->setCurrentIndex(0);
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
        QPixmap onPM("/icons/on.png");
        QIcon onI;

        onI.addPixmap(onPM);
        ui->onoffbtn->setIcon(onI);
        cameraFlag_clicked = false;
        vision->openCamera();
    }
    else
    {
        QPixmap offPM("/icons/off.png");
        QIcon offI;

        offI.addPixmap(offPM);
        ui->onoffbtn->setIcon(offI);
        cameraFlag_clicked = true;
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
        QPixmap onPM("/icons/on.png");
        QIcon onI;

        onI.addPixmap(onPM);
        ui->onoffbtn_2->setIcon(onI);
        gaussianFlag_clicked = false;
    }
    else
    {
        QPixmap offPM("/icons/off.png");
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
        QPixmap onPM("/icons/on.png");
        QIcon onI;

        onI.addPixmap(onPM);
        ui->onoffbtn_3->setIcon(onI);
        blurringFlag_clicked = false;
    }
    else
    {
        QPixmap offPM("/icons/off.png");
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
        QPixmap onPM("/icons/on.png");
        QIcon onI;

        onI.addPixmap(onPM);
        ui->onoffbtn_4->setIcon(onI);
        barinoFlag_clicked = false;
    }
    else
    {
        QPixmap offPM("/icons/off.png");
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
    QPixmap map("/icons/campoTela.png");
    ui->camAddNewColorlbl->setPixmap(map);
    ui->camAddNewColorlbl->setScaledContents(true);
    ui->miniwindowswt->setCurrentIndex(3);
    Mat image2show;

    QImage image1 = QImage( (uchar*) image2show.data, image2show.cols, image2show.rows, image2show.step, QImage::Format_RGB888);
    ui->camAddNewColorlbl->setPixmap(QPixmap::fromImage(image1));
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
    QPixmap map("/icons/campoTela.png");
    ui->camSelectFieldlbl_2->setPixmap(map);
    ui->camSelectFieldlbl_2->setScaledContents(true);
}

void MainWindow::on_selectFieldsbtn_clicked()
{
    ui->miniwindowswt->setCurrentIndex(2);
    ui->allySideSelectFieldbtn_2->setVisible(false);
    ui->enemySideSelectFieldsbtn_2->setVisible(false);
    QPixmap map("/icons/campoTela.png");
    ui->camPerspetctivelbl->setPixmap(map);
    ui->camPerspetctivelbl->setScaledContents(true);
}

void MainWindow::on_editColorbtn_clicked()
{
    ui->miniwindowswt->setCurrentIndex(4);
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
}

void MainWindow::on_lowhuesld_2_sliderMoved(int position)
{
    ui->minhuelcd_2->display(position);
}

void MainWindow::on_uppersaturationsld_2_actionTriggered(int action)
{
    //funcao nao faz nada
}

void MainWindow::on_lowsaturationsld_2_sliderMoved(int position)
{
    ui->lowsaturationlcd_2->display(position);
}

void MainWindow::on_uppervaluesld_2_sliderMoved(int position)
{
    ui->uppervaluelcd_2->display(position);
}

void MainWindow::on_lowvaluesld_2_sliderMoved(int position)
{
    ui->lowvaluelcd_2->display(position);
}

void MainWindow::on_uppersaturationsld_2_sliderMoved(int position)
{
    ui->uppersaturationlcd_2->display(position);
}

void MainWindow::on_confirmNameAddNewColorbtn_2_clicked()
{
    Mat3f min( Vec3f( ui->minhuelcd_2->value(), ui->lowsaturationlcd_2->value(), ui->lowvaluelcd_2->value() ) );
    Mat3f max( Vec3f( ui->maxhuelcd_2->value(), ui->uppersaturationlcd_2->value(), ui->uppervaluelcd_2->value() ) );

    vision->addColor(min, max);
    // fazer algo com o nome da cor, por favor
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

std::vector<cv::Point> showCamera()
{
    Mat imgCamera; //matrix who keep the image who is produced by the camera
    std::vector<cv::Point> points; //the points who correct the perpective
    VideoCapture cam(0); //the frame of the camera
    int i; //number of points clickeds
    while(1)
    {
        cam.read(imgCamera);
        i = 0;
        for(auto it=points.begin() ; it != points.end() ; ++it) //every frame it draw the points clickeds in the image
        {
            cv::circle(imgCamera, *it, 0.1, Scalar(0,0,255), 5);
            i++;
        }
        imshow("Set the points, to exit press ESC",imgCamera);
        setMouseCallback("Set the points, to exit press ESC", onMouse, (void*)&points);
        if((waitKey(1) == 27)||(i>=4))
        {
            break;
        }
    }
    destroyWindow("Set the points, to exit press ESC");
    cam.release();
    return points;
}

void onMouse(int event, int x, int y, int flags, void *userdata)
{
    std::vector<cv::Point> *ptPtr = (std::vector<cv::Point>*)userdata;
    if(event == EVENT_LBUTTONDOWN) //if the left button is clicked
    {
        ptPtr->push_back(cv::Point(x,y));
        std::cout<<"x: "<<x<<"y: "<<y<<std::endl;
    }else if(event == EVENT_RBUTTONDOWN) //if the right button is clicked
    {
        if(!ptPtr->empty())
            ptPtr->erase(ptPtr->end());
    }
}

void MainWindow::on_selectPerspectivebtn_clicked()
{
    VideoCapture cam(0);
    std::vector<cv::Point> point = showCamera();
    vision->setPerspectiveTransformation(point);
    /*
    Mat im_src, im_out;
    im_src = vision->getFrame();
    warpPerspective(im_src, im_out, vision->getFieldHomography(1), cv::Point(640,480));

    QImage imgIn = QImage((uchar*) im_out.data, im_out.cols,im_out.rows,im_out.step, QImage::Format_RGB888);

    ui->camPerspetctivelbl->setPixmap(QPixmap::fromImage(imgIn));
    */
}


