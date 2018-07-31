#include "vision.h"
//#include <QtCore>
#include <fstream>
#include <time.h>

using namespace std;
using namespace cv;


Vision::Vision(QObject *parent): QThread(parent)
{
    running = false;
    virtualField =  imread("CampoTamanhoTela.png");
}

void Vision::run()
{
    getRawFrame();
    visionFrame = preProcessing(rawFrame, GAUSSIAN, 7, MATCH_FIELD_FALSE, USE_LUT_TRUE);
}

void Vision::Play()
{
    Vision::run();
}

/*
 * Funcao que abre a câmera
 */
void Vision::openCamera()
{
    int id = getCameraId();
    cap.open(id);

    if( cap.isOpened() )
    {
        // abriu a câmera
        cout << "Camera opened succefully" << endl;

    }else
    {
        // não conseguiu abrir a câmera
        cout << "Unable to open the camera" << endl;
    }
}

/*
 * Funcao que fecha a câmera
 */
void Vision::closeCamera()
{
    int id = getCameraId();
    cap.release();

    if( cap.isOpened() )
    {
        // abriu a câmera
        cout << "Unable to close the camera" << endl;

    }else
    {
        // não conseguiu abrir a câmera
        cout << "Camera closed succefully" << endl;
    }
}

/*
 * Funcao que pega imagem da câmera
 */
void Vision::getRawFrame()
{
    if( cap.isOpened() )
    {
        // se a câmera ta aberta
        cap.read(rawFrame);
        //cout << "Got the frame" << endl;

    }else
    {
        // se a câmera não ta aberta
        cout << "Unable to get the frame" << endl;
    }
}

/*
 * Funcao que atualiza a tabela de cores HSV com base nas cores selcionadas no Set Colors
 */
void Vision::updateLUT()
{
    // valores RGB de referência
    int r, g, b;
    int cont = 0;

    // variáveis usadas para converter o RGB de ref em HSV
    Mat3f src_HSV;
    float h, s, v;
    unsigned int index;

    // arquivo de texto para salvar a tabela
    fstream file;
    file.open("LUT.txt", ofstream::out);

    cout << "Updating LUT..." << endl;

    // percorre todas as combinações possíveis de R, G e B
    for(r = 0; r<256; r++){
        for(g = 0; g<256; g++){
            for(b = 0; b<256; b++){
                Mat3f src( Vec3f(b, g, r) );
                // Calcula o índice na tabela
                index = (unsigned int) (b + g*256 + r*256*256);

                // Cout de controle
                if(index%(256*256*256/10) == 0){
                    cout << cont*10 << "%" << endl;
                    cont++;
                }

                // converte o RGB atual para HSV
                cvtColor( src, src_HSV, COLOR_BGR2HSV );

                // Deixa 0 <= H <= 180 (padrão OpenCV)
                h = (float) src_HSV.at<float>(0, 0)/2;
                // Deixa o S entre 0 <= S <= 255 (padrão OpenCV)
                s = (float) src_HSV.at<float>(0, 1)*100;
                // Deixa o V entre 0 <= S <= 255 (padrão OpenCV)
                v = (float) src_HSV.at<float>(0, 2);

                Mat3f min, max, ref;

                // Por padrão, a cor não de interesse, logo: fundo preto
                LUT[index][0] = (unsigned char) 0;
                LUT[index][1] = (unsigned char) 0;
                LUT[index][2] = (unsigned char) 0;

                // percorre o vetor de cores configuradas no Set Colors
                for(int k = 0; k < refColors.size(); k++)
                {
                    min = minColorsRange.at(k);
                    max = maxColorsRange.at(k);
                    ref = refColors.at(k);

                    // Se o RGB atual está na faixa de interesse da cor configurada, recebe seu valor de referência
                    if( (h >= min.at<float>(0,0) && h <= max.at<float>(0,0)) &&
                            (s >= min.at<float>(0,1) && s <= max.at<float>(0,1)) &&
                            (v >= min.at<float>(0,2) && v <= max.at<float>(0,2)) ){

                        LUT[index][0] = (unsigned char) ref.at<float>(0,0);
                        LUT[index][1] = (unsigned char) ref.at<float>(0,1);
                        LUT[index][2] = (unsigned char) ref.at<float>(0,2);
                    }
                }
                // Salva valor atual de RGB no arquivo de texto
                file << LUT[index][0] << " " << LUT[index][1] << " " << LUT[index][2] << endl;
            }
        }
    }
    file.close();
}

/*
 * Funcao que carrega a tabela de um arquivo de texto para o programa
 */
void Vision::loadLUT()
{
    int cont = 0;
    cout << "Reading LUT..." << endl;
    // Arquivo de texto contendo a última tabela salva
    ifstream file;
    file.open("LUT.txt", fstream::in);

    // Se não conseguiu abrir
    if(!file){
        cout << "Couldn't read LUT from file!" << endl;
        return;
    }
    // Vai para o seu início
    file.clear();
    file.seekg(0, ios::beg);

    // para todas as linhas do arquivo
    for(int i = 0; i<256*256*256; i++)
    {
        // Cout de controle
        if(i%(256*256*256/10) == 0){
            cout << cont*10 << "%" << endl;
            cont++;
        }
        // salva os valores das três colunas nas três colunas da tabela
        file >> LUT[i][0] >> LUT[i][1] >> LUT[i][2];
    }
    file.close();
}

/*
 * Funcao que aplica a tranformação da tablea à imagem, pixel a pixel
 */
void Vision::applyLUT(Mat frame)
{
    // Percorre todos os pixels da imagem, executando a função dada
    frame.forEach<Pixel>([&](Pixel &p, const int* position) -> void {
        // calcula o índice da tablea correspondente à cor do pixel a processar
        int index = (int) double(p.x) + double(p.y)*256 + double(p.z)*256*256;
        // Substitui pelo valor da tabela
        p.x = LUT[index][0];
        p.y = LUT[index][1];
        p.z = LUT[index][2];

    });
}

/*
 * Funcao que aplica a pré procesamento da imagem
 */
Mat Vision::preProcessing(Mat src, int filter, int kernelSize, bool matchField, bool useLUT)
{
    Mat output;
    src.copyTo(output);

    // ajusta a perspectiva da imagem, para "dar match" no campo real com o virtual
    if(matchField){
        warpPerspective(output, output, fieldHomography1, cv::Point(640,480));
    }

    // aplica filtro
    switch (filter) {
    case GAUSSIAN:
        GaussianBlur(output, output, Size(kernelSize, kernelSize), 0, BORDER_CONSTANT);
        break;
    case BILATERAL:
        output.copyTo(src);
        bilateralFilter(src, output, kernelSize, kernelSize*2, kernelSize/2, BORDER_CONSTANT );
        break;
    default:
        medianBlur(output, output, kernelSize);
        break;
    }

    // faz a transformação de cores
    if(useLUT){
        applyLUT(output);
    }else{
        cvtColor(output, output, COLOR_BGR2HSV);
    }
    //cout << "Preprocessed" << endl;
    return output;
}

/*
 * Funcao que salva a matrix de transformação para corrigir perspectiva
 */
void Vision::setPerspectiveTransformation(vector<Point> realFieldPoints)
{
    // pontos de destino. Fixos: campo virtual
    vector<Point> pts_dst;
    int xRefi = 103, yRefi = 113, xReff = 537, yReff = 367;
    // Adiciona os pontos de referência do campo virtual ao vetor de pontos de destino
    pts_dst.push_back(Point(xRefi,yRefi));
    pts_dst.push_back(Point(xReff,yRefi));
    pts_dst.push_back(Point(xReff,yReff));
    pts_dst.push_back(Point(xRefi,yReff));

    // Calcula a matriz de transformação com base nos pontos acima e os recebidos pelo usuário
    fieldHomography1 = findHomography(realFieldPoints, pts_dst);
}

/*
 * Funcao que aplica a transformação de pixel para metro em um ponto
 */
Point2f Vision::px2meter(Point pxPoint)
{
    // relação de conversão m/px nos eixos x e y
    // distancia dos Points 1 e 2 em metros = 1.2
    // distancia dos Points 3 e 4 em metros = 0.7
    float xRatio = 1.2/(X_REF_F - X_REF_I);
    float yRatio = 0.7/(Y_REF_I - Y_REF_F);

    //subtracao é a mudanca de referencial de imagem para cartesiana é a multiplicacao conversao
    float xm = (pxPoint.x - X_0)*xRatio;
    float ym = (pxPoint.y - Y_0)*yRatio;

    Point meterPoint;
    meterPoint.x = xm;
    meterPoint.y = ym;

    return meterPoint;
}

/*
 * Funcao que blablabla
 */
Mat Vision::getFieldHomography(int side)
{
    if(side == 1 )  return this->fieldHomography1;
    if(side == 2 )  return this->fieldHomography2;
}

int Vision::getCameraId()
{
    return this->cameraId;
}

void Vision::setCameraId(int index)
{
    this->cameraId = index;
}

void Vision::addColor(Mat3f colorMin, Mat3f colorMax)
{
    minColorsRange.push_back(colorMin);
    maxColorsRange.push_back(colorMax);
    refColors.push_back((colorMax+colorMin)/2);

    cout << "Min color vector: " << endl;
    for(int i = 0; i<refColors.size(); i++)
    {
        cout << minColorsRange.at(i) << endl;
    }

    cout << "Max color vector: " << endl;
    for(int i = 0; i<refColors.size(); i++)
    {
        cout << maxColorsRange.at(i) << endl;
    }
    cout << " " << endl;
}
