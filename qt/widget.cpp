#include "widget.h"
#include "ui_widget.h"
#include<QGraphicsDropShadowEffect>

#include<QIODevice>
#include<QFile>
#include<QCoreApplication>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    card = new Card();//加入card类
    ui->lineEdit->setText(QDir::currentPath()+"/"); //当前路径显示
    beautiful();


    connect(card,&Card::send_text,this,&Widget::rec_text);
    connect(card,&Card::num_text,this,&Widget::diaplay);
    connect(card,&Card::send_img,this,&Widget::rec_img);
    connect(card,&Card::send_img2,this,&Widget::rec_img2);
    //初始按钮不可以点集
    is_ui_visiable(false);
}

Widget::~Widget()
{
    //qDebug()<<"释放";
    delete card;
    delete ui;
}

void Widget::beautiful()
{
    QFile f;
    QString str = ui->lineEdit->text();
    qDebug()<<"str="<<str;
    f.setFileName(str+"i_qt.css");
    qDebug() << "Trying to open file:" << f.fileName();
    //f.open(QIODevice::ReadOnly);
    if (!f.open(QIODevice::ReadOnly)) {
        qWarning() << "Cannot open file:" << f.fileName() << "; Error:" << f.errorString();
        return;
    }
    QString  strQSS= f.readAll();
    this->setStyleSheet(strQSS);

    f.close();

    ui->btn->setCursor(Qt::PointingHandCursor); // 设置鼠标指针为手形
    ui->btn_path->setCursor(Qt::PointingHandCursor);
    ui->train->setCursor(Qt::PointingHandCursor);
    ui->test->setCursor(Qt::PointingHandCursor);

    // 创建阴影效果
    QGraphicsDropShadowEffect *shadowEffect = new QGraphicsDropShadowEffect;
    shadowEffect->setBlurRadius(10); // 将阴影设为内阴影
    shadowEffect->setOffset(-3, -3); // 设置阴影偏移量
    shadowEffect->setColor(QColor(0, 0, 0, 128)); // 设置阴影颜色
    ui->img->setGraphicsEffect(shadowEffect);
    ui->img->setStyleSheet("border-radius: 6;background-color:#ECF0F1;");
    QGraphicsDropShadowEffect *shadowEffects = new QGraphicsDropShadowEffect;
    shadowEffects->setBlurRadius(10); // 设置阴影模糊半径
    shadowEffects->setOffset(3, 3); // 设置阴影偏移量
    shadowEffects->setColor(QColor(0, 0, 0, 128)); // 设置阴影颜色
    ui->img_num->setGraphicsEffect(shadowEffects); // 将阴影效果应用到标
    ui->img_num->setStyleSheet("border-radius: 6;background-color:#7F8C8D;");
}



//结果展示
void Widget::diaplay() const
{
    //识别结果
    QString result = card->num_queue.dequeue();
    qDebug()<<"结果"<<result;
    ui->num_id->setText(result);//身份证号码

    QMap<QString, QString> provinceMap = {
                                        {"11", "北京市"}, {"12", "天津市"},{"13", "河北省"}, {"14","山西省"},{"15","内蒙古自治区"},
                                        {"21","辽宁省"},{"22","吉林省"},{"23","黑龙江省"},
        {"31","上海市"},{"32","江苏省"},{"33","浙江省"},{"34","安徽省"},{"35","福建省"},{"36","江西省"},{"37","山东省"},{"41","河南省"},
        {"42","湖北省"},{"43","湖南省"},{"44","广东省"},{"45","广西壮族自治区"},{"46","海南省"},
        {"50","重庆市"},{"51","四川省"},{"52","贵州省"},{"53","云南省"},{"54","西藏藏族自治区"},
        {"61","陕西省"},{"62","甘肃"},{"63","青海省"},{"64","宁夏"},{"65","新疆"},{"71","台湾"},{"81","香港"},{"82","澳门"}
    };
    //提取省份
    QString provin = result.mid(0,2);
    QString province = provinceMap.value(provin, "未知省份");
    ui->provin->setText(province);
    //提取出生日期
    QString birthYear = result.mid(6, 4);
    QString birthMonth = result.mid(10, 2);
    QString birthDay = result.mid(12, 2);
    QString birthDate = birthYear + "-" + birthMonth + "-" + birthDay;
    ui->birthday->setText(birthDate);
    // 提取性别
    int genderCode = result.mid(16, 1).toInt();
    QString gender = (genderCode % 2 == 0) ? "女" : "男";
    ui->sex->setText(gender);

    //总的
    QString resultText = QString("id: %1\n省份: %2\n出生日期: %3\n性别：%4")
                             .arg(result)
                             .arg(province)
                             .arg(birthDate)
                             .arg(gender);
    ui->reult_edit->append(resultText);
}

//更改路径
void Widget::on_btn_path_clicked()
{
    if(ui->btn->text().toUtf8() == "开始训练"){
        QString filePath = QFileDialog::getExistingDirectory(this, "请选择文件训练路径…", "./");
        if(filePath.isEmpty()) filePath = ".";
        ui->lineEdit->setText(filePath+"/");
    }
    else{
        QString filePath=QFileDialog::getOpenFileName(this,"请选择检测的图片","./", "Images (*.png *.xpm *.jpg)");
        if(filePath.isEmpty()) filePath = ".";
        ui->lineEdit->setText(filePath);
    }

}

//开始训练或者开始检测
void Widget::on_btn_clicked()
{
    if(ui->btn->text().toUtf8() == "开始训练")
    {
        QString path = ui->lineEdit->text();
        qDebug()<<path;
        ui->reult_edit->append("开始训练数据集！");
        ui->btn->setStyleSheet("background-color: #2ecc71");
        ui->lineEdit->setStyleSheet("color:#343a40");
        ui->btn->setText("正在训练");
        string path1=path.toStdString();
        //要训练svm
        TickMeter trainTime;//记录训练时间
        trainTime.reset();
        trainTime.start();
        card->setTrain_SVM(path1);
        trainTime.stop();
        double timeInSeconds = trainTime.getTimeSec(); // 获取秒数
        QString time = QString::number(timeInSeconds, 'f', 2); // 将double转换为QString，保留两位小数
        QString res = "训练结束，用时"+time+"s!";
        ui->reult_edit->append(res); // 将时间添加到文本编辑器
        ui->btn->setText("训练结束");
        is_ui_visiable(false);//控件不可以用
        ui->btn->setStyleSheet("color: white;background-color: #bdc3c7;");
    }
    else{
        QString path = ui->lineEdit->text();
        qDebug()<<path;
        //ui->btn->setStyleSheet("background-color: #2ecc71");
        ui->lineEdit->setStyleSheet("color:#343a40");
        //ui->reult_edit->append("开始检测！");
        TickMeter trainTime;//记录训练时间
        trainTime.reset();
        trainTime.start();

        ui->btn->setText("正在检测");
        string path1=path.toStdString();
        card->detect(path1);
        trainTime.stop();
        double timeInSeconds = trainTime.getTimeSec(); // 获取秒数
        QString time = QString::number(timeInSeconds, 'f', 2); // 将double转换为QString，保留两位小数
        QString res = "检查结束，用时"+time+"s!";
        ui->reult_edit->append(res); // 将时间添加到文本编辑器
        ui->btn->setText("开始检测");
        //ui->btn->setStyleSheet("color: #2ecc71");
    }
}

//训练SVM
void Widget::on_train_clicked()
{
    ui->btn->setText("开始训练");
    is_ui_visiable(true);
    ui->btn->setStyleSheet("QPushButton {color: white;}"
                            "QPushButton {background-color: #34495e;}"
                           "QPushButton:hover { color: #fff;;background-color:#dc3545; }"
                           );
}

//进行检测
void Widget::on_test_clicked()
{
    ui->btn->setText("开始检测");
    is_ui_visiable(true);
    ui->btn->setStyleSheet("QPushButton {color: white;}"
                           "QPushButton {background-color: #34495e;}"
                           "QPushButton:hover { color: #D35400; background-color:#2ecc71;}"
                           );
}

//一些日志
void Widget::rec_text()
{
    ui->reult_edit->append(card->send_queue.dequeue());//图片处理过程有问题会调用
}

//原图显示
void Widget::rec_img()
{
    QPixmap pix = card->pixmap1_queue.dequeue();//取出队列里的，并删除
    QPixmap scaledPixmap = pix.scaled(ui->img->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation);
    ui->img->setPixmap(scaledPixmap);
}

//号码区域显示
void Widget::rec_img2()
{
    QPixmap pix = card->pixmap2_queue.dequeue();//取出队列里的，并删除
    // 调整pixmap的大小以适应label的大小
    QPixmap scaledPixmap = pix.scaled(ui->img_num->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation);
    ui->img_num->setPixmap(scaledPixmap);
}


//控件按钮
void Widget::is_ui_visiable(bool state)
{
    ui->btn->setEnabled(state);//按钮不可以开始
    ui->lineEdit->setEnabled(state);//路径不可以显示
    ui->btn_path->setEnabled(state);//不可以更改路径
}

