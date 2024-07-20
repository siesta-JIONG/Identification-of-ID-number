#ifndef CARD_H
#define CARD_H

#include <QObject>
#include<QDebug>
#include<QString>
#include<vector>
#include<opencv2/opencv.hpp>
#include<opencv2/ml.hpp>
#include <QQueue>
#include<string>
#include <QImage>
#include <QPixmap>


using namespace std;
using namespace cv;
using namespace cv::ml;

class Card :public QObject
{
    Q_OBJECT
public:
    Card();
    QQueue<QString> send_queue;
    QQueue<QString> num_queue;
    QQueue<QPixmap> pixmap1_queue; //图像数据队列
    QQueue<QPixmap> pixmap2_queue;


    void detect(const string path);
    void setTrain_SVM(const string path);
    void getFielNames(string path,vector<string>& files );
    void clear();//清空前一张检测的东西;


private slots:


signals:
    void send_text();
    void num_text();
    void send_img();
    void send_img2();

private:
    Ptr<SVM>svm;
    Mat idcard, img;//按照顺序执行，反复调用麻烦，定义为成员
    vector<RotatedRect>rotateRects;//包含号码矩形detect_ROI
    Mat num_img;//二值化过后图片，为了后面直接从这里提取号码区域num_id使用
    vector<Mat>numbers;//18张号码图
    vector<int>num;//记录svm预测的结果是数字几

    void dispaly();
    void preDeal();//预处理|双边滤波|灰度化|形态学操作|二值化
    void detect_ROI();//拿到号码所在的区域
    void num_id();//拿到单个数字
    void detect_svm();

    QImage MatToQImage(const cv::Mat& mat);
};

#endif // CARD_H
