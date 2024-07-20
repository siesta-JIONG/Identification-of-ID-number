#include "Card.h"
#include<conio.h>
#include<io.h>

void Card::preDeal()
{
    //双边滤波
    bilateralFilter(idcard, img, 7, 10, 5);
    //灰度化
    cvtColor(img, img, COLOR_BGR2GRAY);//灰度化

    // 形态学边缘检测
    //连接图像中的断裂部分或者关闭小的空洞;
    // 矩形结构元素，尺寸为 7x7
    Mat tmp = img.clone();								// 临时存储空间
    morphologyEx(										// 形态学运算
        img,											// 输入图像
        tmp,											// 输出图像
        MORPH_CLOSE,									// 指定闭运算 连通破碎区域
        getStructuringElement(MORPH_RECT, Size(7, 7))	// 获取结构核
        );
    img = tmp - img;		// 作差得到边缘信息
    tmp.release();

    //二值化
    threshold(img, img, 0, 255, THRESH_OTSU);	//OTSU 方法自动确定最优阈值进行二值化->包含黑白图
    num_img = img.clone();//这张高清图片保存后面为后面区域检测用
}

void Card::detect_ROI()
{
    // 闭运算 形成连通区域
    morphologyEx(										// 形态学运算
        img,											// 输入图像
        img,											// 输出图像
        MORPH_CLOSE,									// 指定闭运算 连通号码区域
        getStructuringElement(MORPH_RECT, Size(21, 13))	// 获取结构核
        );

    // 查找轮廓
    vector<vector<Point>> contours;						// 保存轮廓点
    vector<Vec4i> hierarchy;							// 轮廓的层级关系
    findContours(										// 查找轮廓
        img,											// 参数代表找外轮廓
        contours,										// 输入轮廓
        hierarchy,										// 层级关系 此处只需一个占位
        RETR_TREE,										// 树形式保存
        CHAIN_APPROX_NONE								// 存储所有的轮廓点，不进行压缩轮廓点
        );
    img.release();										// 清空 img 占用的内存
    vector<Vec4i>().swap(hierarchy);					// 清空 hierarchy 占用的内存

    // 筛选轮廓
    vector<vector<Point>> contours_number;				// 保存可能的号码区域
    for (auto itr = contours.begin(); itr != contours.end(); itr++)
        if (itr->size() > 400)							// 保留轮廓点数多于 400 的
            contours_number.push_back(*itr);			// 保存该轮廓
    vector<vector<Point>>().swap(contours);				// 释放 contours 占用的内存

    //最小包围矩阵框
    for (auto itr = contours_number.begin(); itr != contours_number.end(); itr++)
    {
        RotatedRect rotatedRect = minAreaRect(*itr);	//从点集求出最小包围矩形
        const float width = rotatedRect.size.width;		//长
        const float height = rotatedRect.size.height;	//宽
        const float k = height / width;					//比值
        if (width < 15 || height < 15 || (0.1 < k && k < 10))		//矩形形状小而且不是大长条
            continue;
        rotateRects.push_back(rotatedRect);
    }
    vector<vector<Point>>().swap( contours_number);

    if (rotateRects.empty())
    {
        send_queue.enqueue("身份证号码区域提起为空！detect_roi");
        emit send_text();
        qDebug()<<"身份证号码区域提起为空！detect_roi";
    }
    else{
        Point2f temp_p[4];
        Mat temp_img3 = idcard.clone();
        for (auto dbg_rotatedRect : rotateRects)
        {
            dbg_rotatedRect.points(temp_p);
            for (int temp = 0; temp < 4; temp++)
                // 绘制图像		起点		终点永远是起点
                line(temp_img3, temp_p[temp], temp_p[(temp + 1) % 4], Scalar(0, 255,0 ), 2, 8);
        }
        //imshow("身份证号码ROI获取", temp_img3);
        QImage tt = MatToQImage(temp_img3);
        pixmap1_queue.enqueue(QPixmap::fromImage(tt));
        emit send_img();
    }

}

void Card::num_id()
{
    //提取到的区域包括了号码在的，也有其他的，先想去掉
    Mat temp;
    vector<vector<Point>> contours;//存储轮廓
    for (auto itr = rotateRects.begin(); itr != rotateRects.end(); itr++)//对这些矩形一个一个的进行筛查
    {
        qDebug()<<"宽："<<itr->size.width;
        qDebug() << "高：" << itr->size.height;
        if ((itr->size.width) < (itr->size.height))
        {
            qDebug()<<"进行旋转处理！";
            double t = itr->size.width;
            itr->size.width = itr->size.height;
            itr->size.height = t;
            qDebug() << "宽：" << itr->size.width;
            qDebug() << "高：" << itr->size.height;
        }
        Size newSize(itr->size.width + 16, itr->size.height + 10);

        getRectSubPix(num_img, newSize, itr->center, temp);

        // 使用形态学开运算去除小的噪声点
        Mat element = getStructuringElement(MORPH_RECT, Size(3, 3)); // 创建一个3x3的结构元素
        morphologyEx(temp, temp, MORPH_OPEN, element); // 执行开运算


        findContours(temp, contours, RETR_EXTERNAL, CHAIN_APPROX_NONE);//查找轮廓

        if (contours.size() == 18)//是18个轮廓才是号码区域
        {
            QImage tt = MatToQImage(temp);
            pixmap2_queue.enqueue(QPixmap::fromImage(tt));
            emit send_img2();
            break;
        }
    }

    vector<RotatedRect>().swap(rotateRects);//找到要的区域，之前的矩形没用了

    if (contours.size() != 18)
    {
        qDebug() << "！！！没有找到身份证号码在的区域num_id";
        send_queue.enqueue(QString("！！！没有找到身份证号码在的区域num_id"));
        emit send_text();
    }

    //输出是乱序，没有按顺序排列
    //-------------排序-----------------
    sort(contours.begin(), contours.end(), [](vector<Point>l, vector<Point>r) {
        return boundingRect(l).br().x < boundingRect(r).br().x;
    });
    //--------------------------------
    // string n_self = "身份证号码第";
    // int n_selfi = 1;
    for (auto itr = contours.begin(); itr != contours.end(); itr++)
    {
        Rect rect = boundingRect(*itr);	//单个数字
        Mat temp_img = temp(Rect(rect)).clone();
        cv::resize(temp_img,temp_img, Size(28, 28));
        numbers.push_back(temp_img);
    }
}

void Card::detect_svm()
{
    svm = SVM::load("E:\\data\\res\\svm.xml");// 读取模型

    //检测
    for (auto itr = numbers.begin(); itr!=numbers.end(); itr++)
    {
        itr->convertTo(img, CV_32FC1);
        float res = svm->predict(img.reshape(0, 1));
        num.push_back(res);
        qDebug() << "预测结果为：" << res;
        //send_queue.enqueue(QString("预测结果："+QString::number(res)));
        //emit send_text();
    }
    img.release();
    svm->clear();

    //校验
    int sum = 0;
    int w[]= { 7, 9, 10, 5, 8, 4, 2, 1, 6, 3, 7, 9, 10, 5, 8, 4, 2, 1 };	// 权重
    for (int i = 0; i <18; i++)
        sum += num[i] * w[i];
    sum %= 11;

    if (sum == 1 || (sum == 10 && num.back() == 10))
    {
        qDebug() << "预测结果不错！模型符合";
        //send_queue.enqueue("预测结果不错！模型符合");
        //emit send_text();
    }

}

QImage Card::MatToQImage(const Mat &mat)
{
    if(mat.type() == CV_8UC1)
    {
        QImage image(mat.cols, mat.rows, QImage::Format_Grayscale8);
        uchar *pSrc = mat.data;
        for(int row = 0; row < mat.rows; row ++)
        {
            uchar *pDest = image.scanLine(row);
            memcpy(pDest, pSrc, mat.cols);
            pSrc += mat.step;
        }
        return image;
    }
    else if(mat.type() == CV_8UC3)
    {
        const uchar *pSrc = (const uchar*)mat.data;
        QImage image(pSrc, mat.cols, mat.rows, mat.step, QImage::Format_RGB888);
        return image.rgbSwapped();
    }
    else if(mat.type() == CV_8UC4)
    {
        const uchar *pSrc = (const uchar*)mat.data;
        QImage image(pSrc, mat.cols, mat.rows, mat.step, QImage::Format_ARGB32);
        return image;
    }
    else
    {
        return QImage();
    }
}

Card::Card()
{

}

void Card::detect(const string path)
{
    clear();
    idcard = imread(path);
    if (idcard.empty())
        qDebug()<<"文件读取为空";
    img = idcard.clone();
    //尺寸调整,便于检测特定区域
    cv::resize(idcard, idcard, Size(1000, 600));

    preDeal();//预处理

    detect_ROI();//ROI号码区域提取

    num_id();//号码提取单个数字

    detect_svm();//svm识别

    dispaly();
}

//训练数据集
void Card::setTrain_SVM(const string path)
{
    Mat trainImages;	//训练数据图片
    vector<int> trainLabels;//打标---无需多言
    Mat img_svm;

    //初始化
    svm = SVM::create();
    svm->setType(SVM::C_SVC);
    svm->setTermCriteria(TermCriteria(TermCriteria::MAX_ITER, 100, 1e-6));

    int classes[] = { 0, 2, 3, 4, 6, 7, 8, 9 };
    vector<string> files;

    //读取文件
    for (const auto& x : classes)		//每一个文件夹里面训练所有图片
    {
        getFielNames(path + to_string(x), files);
        for (const auto& file : files)
        {
            img_svm = imread(file, 0);//读取灰度图	0->灰度图|1->彩色图[默认]|-1->原始数据
            if (img_svm.empty())
            {
                continue;
            }
            threshold(img_svm, img_svm, 10, 255, THRESH_OTSU);//二值化
            img_svm.convertTo(img_svm, CV_32FC1);//转化通道类型

            //这个文件夹下面的都是一种数据集，排成一行，对应当前的标签，方便训练
            trainImages.push_back(img_svm.reshape(0, 1));
            trainLabels.push_back(x);
        }
        files.clear();		//清空，遍历下一个数据
    }

    //进行训练
    svm->train(trainImages, ROW_SAMPLE, trainLabels);
    svm->save(path+"svm_qt.xml");
    svm->clear();
}

void Card::getFielNames(string path, vector<string> &files)
{
    intptr_t hFile = 0;
    struct _finddata_t fileinfo;//io.h

    string p;

    if ((hFile = _findfirst(p.assign(path).append("\\*").c_str(), &fileinfo)) != -1)
    {
        do
        {
            if ((fileinfo.attrib & _A_SUBDIR))//判断当前路径是否是一个文件夹----主要是SVM训练使用|&位运算
            {
                if (strcmp(fileinfo.name, ".") != 0 && strcmp(fileinfo.name, "..") != 0)//不在当前目录，也不在上级目录
                    getFielNames(p.assign(path).append("\\").append(fileinfo.name), files);
            }
            else
            {
                files.push_back(p.assign(path).append("/").append(fileinfo.name));//记录文件的完整路径
            }
        } while (_findnext(hFile, &fileinfo)==0);//全部找出
        _findclose(hFile);
    }
}

void Card::clear()
{
    idcard.release();
    img.release();
    num_img.release();
    vector<RotatedRect>().swap(rotateRects);
    vector<Mat>().swap(numbers);
    vector<int>().swap(num);
}

void Card::dispaly()
{
    string result;
    for (auto res : num)
    {
        result += (res == 10 ? "X" : to_string(res));
    }

    num_queue.enqueue(QString::fromStdString(result));
    emit num_text();
}
