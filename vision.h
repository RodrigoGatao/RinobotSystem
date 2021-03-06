#ifndef VISION_H
#define VISION_H

#include <QObject>
#include <QThread>

#include <iostream>
#include <vector>
#include <fstream>
#include <opencv2/core.hpp>
#include <opencv2/opencv.hpp>
#include <opencv2/imgproc.hpp>


#define GAUSSIAN 1
#define BILATERAL 2

#define X_REF_I 120   //x referencial inicial
#define Y_REF_I 131   //y referencial inicial
#define X_REF_F 600   //x referencial final
#define Y_REF_F 408   //y referencial final
#define X_0 61       //x referencial para a origem desejada
#define Y_0 528      //y referencial para a nova origem desejada
#define USE_LUT_TRUE 1
#define USE_LUT_FALSE 0
#define MATCH_FIELD_TRUE 1
#define MATCH_FIELD_FALSE 0
#define SET_COLORS_MODE 1
#define PLAY_MODE 2
#define PERSPECTIVE_MODE 3

typedef cv::Point3_<uint8_t> Pixel;

using namespace std;
using namespace cv;

class Vision: public QThread
{
    Q_OBJECT
private:
    VideoCapture cap;                   // Câmera
    Mat rawFrame;                       // Imagens: capturada, usada no processamento
    Mat visionFrame;
    uint8_t LUT[256*256*256][3];        // Tabela de conversão BGR->HSV
    Vec3f currentMinHSV;
    Vec3f currentMaxHSV;
    vector<Mat3f> minColorsRange;       // Vetor com minimos HSV das cores de interesse
    vector<Mat3f> maxColorsRange;       // Vetor com maximos HSV das cores de interesse
    vector<Mat3f> refColors;            // Vetor com cores de referência
    vector<Point> realFieldPoints;      //the points who correct the perpective
    vector<int> robotColorIndex;
    Mat fieldHomography1, fieldHomography2;
    int team1ColorIndex;
    int team2ColorIndex;
    int ballColorIndex;
    int cameraId;
    int visionMode;

    // Funções
    void getRawFrame();
    void loadLUT();
    void updateLUT();
    void applyLUT(Mat frame);    

    Mat preProcessing(Mat src, int filter, int kernelSize, bool matchField, bool useLUT);
    Point2f px2meter(Point pxPoint);
    std::vector<cv::Point> showCamera(); //function to get the points to the correction perspective
    Mat colorSegmentation(Mat im_src, Vec3f minHSV, Vec3f maxHSV);



protected:
    void run();

public:
    bool running;
    Mat virtualField;                   // Campo de referência


    explicit Vision(QObject *parent = nullptr);
    int getCameraId();
    void openCamera();
    void closeCamera();
    void setPerspectiveTransformation(vector<Point> realFieldPoints);
    void setCameraId(int index);
    void addColor(Mat3f colorMin, Mat3f colorMax);
    void setPerspectivePoints();
    void setCurrentMinHSV(Vec3f min);
    void setCurrentMaxHSV(Vec3f max);
    void setVisionMode(int mode);

    Mat getFieldHomography(int side);
    Mat colorSegmentationInterface(Mat im_src);

signals:
    void emit_segmentationImage(Mat img);
    void emit_fieldImage(Mat img);


public slots:


};

#endif // VISION_H
