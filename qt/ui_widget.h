/********************************************************************************
** Form generated from reading UI file 'widget.ui'
**
** Created by: Qt User Interface Compiler version 6.5.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WIDGET_H
#define UI_WIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Widget
{
public:
    QLabel *img;
    QLabel *img_num;
    QWidget *gridLayoutWidget;
    QGridLayout *gridLayout;
    QLabel *sex;
    QLabel *label_2;
    QLabel *label_3;
    QLabel *label;
    QLabel *provin;
    QLabel *birthday;
    QLabel *label_7;
    QLabel *num_id;
    QWidget *gridLayoutWidget_2;
    QGridLayout *gridLayout_2;
    QRadioButton *test;
    QRadioButton *train;
    QPushButton *btn_path;
    QLineEdit *lineEdit;
    QTextEdit *reult_edit;
    QPushButton *btn;

    void setupUi(QWidget *Widget)
    {
        if (Widget->objectName().isEmpty())
            Widget->setObjectName("Widget");
        Widget->resize(729, 483);
        Widget->setStyleSheet(QString::fromUtf8(""));
        img = new QLabel(Widget);
        img->setObjectName("img");
        img->setGeometry(QRect(40, 50, 321, 211));
        img->setStyleSheet(QString::fromUtf8("background-color: rgb(0, 255, 255);"));
        img_num = new QLabel(Widget);
        img_num->setObjectName("img_num");
        img_num->setGeometry(QRect(40, 310, 321, 41));
        img_num->setStyleSheet(QString::fromUtf8("background-color: rgb(85, 255, 0);"));
        gridLayoutWidget = new QWidget(Widget);
        gridLayoutWidget->setObjectName("gridLayoutWidget");
        gridLayoutWidget->setGeometry(QRect(430, 40, 271, 151));
        gridLayout = new QGridLayout(gridLayoutWidget);
        gridLayout->setObjectName("gridLayout");
        gridLayout->setContentsMargins(0, 0, 0, 0);
        sex = new QLabel(gridLayoutWidget);
        sex->setObjectName("sex");
        QFont font;
        font.setPointSize(15);
        font.setBold(true);
        sex->setFont(font);
        sex->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(sex, 3, 1, 1, 1);

        label_2 = new QLabel(gridLayoutWidget);
        label_2->setObjectName("label_2");
        QFont font1;
        font1.setPointSize(13);
        label_2->setFont(font1);
        label_2->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(label_2, 2, 0, 1, 1);

        label_3 = new QLabel(gridLayoutWidget);
        label_3->setObjectName("label_3");
        label_3->setFont(font1);
        label_3->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(label_3, 3, 0, 1, 1);

        label = new QLabel(gridLayoutWidget);
        label->setObjectName("label");
        label->setFont(font1);
        label->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(label, 1, 0, 1, 1);

        provin = new QLabel(gridLayoutWidget);
        provin->setObjectName("provin");
        QFont font2;
        font2.setPointSize(13);
        font2.setBold(true);
        provin->setFont(font2);
        provin->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(provin, 1, 1, 1, 1);

        birthday = new QLabel(gridLayoutWidget);
        birthday->setObjectName("birthday");
        QFont font3;
        font3.setPointSize(12);
        font3.setBold(true);
        font3.setItalic(false);
        birthday->setFont(font3);
        birthday->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(birthday, 2, 1, 1, 1);

        label_7 = new QLabel(gridLayoutWidget);
        label_7->setObjectName("label_7");
        label_7->setFont(font1);
        label_7->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(label_7, 0, 0, 1, 1);

        num_id = new QLabel(gridLayoutWidget);
        num_id->setObjectName("num_id");
        QFont font4;
        font4.setPointSize(11);
        font4.setBold(true);
        num_id->setFont(font4);
        num_id->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(num_id, 0, 1, 1, 1);

        gridLayoutWidget_2 = new QWidget(Widget);
        gridLayoutWidget_2->setObjectName("gridLayoutWidget_2");
        gridLayoutWidget_2->setGeometry(QRect(440, 360, 211, 101));
        gridLayout_2 = new QGridLayout(gridLayoutWidget_2);
        gridLayout_2->setObjectName("gridLayout_2");
        gridLayout_2->setContentsMargins(0, 0, 0, 0);
        test = new QRadioButton(gridLayoutWidget_2);
        test->setObjectName("test");

        gridLayout_2->addWidget(test, 1, 1, 1, 1);

        train = new QRadioButton(gridLayoutWidget_2);
        train->setObjectName("train");

        gridLayout_2->addWidget(train, 1, 0, 1, 1);

        btn_path = new QPushButton(gridLayoutWidget_2);
        btn_path->setObjectName("btn_path");
        QFont font5;
        font5.setPointSize(12);
        font5.setBold(true);
        btn_path->setFont(font5);

        gridLayout_2->addWidget(btn_path, 2, 1, 1, 1);

        lineEdit = new QLineEdit(gridLayoutWidget_2);
        lineEdit->setObjectName("lineEdit");

        gridLayout_2->addWidget(lineEdit, 2, 0, 1, 1);

        reult_edit = new QTextEdit(Widget);
        reult_edit->setObjectName("reult_edit");
        reult_edit->setGeometry(QRect(430, 200, 261, 141));
        QFont font6;
        font6.setPointSize(12);
        reult_edit->setFont(font6);
        reult_edit->setStyleSheet(QString::fromUtf8("background-color: rgb(240, 240, 240);"));
        reult_edit->setFrameShape(QFrame::NoFrame);
        btn = new QPushButton(Widget);
        btn->setObjectName("btn");
        btn->setGeometry(QRect(110, 400, 111, 51));
        QFont font7;
        font7.setPointSize(17);
        font7.setBold(true);
        font7.setItalic(true);
        btn->setFont(font7);

        retranslateUi(Widget);

        QMetaObject::connectSlotsByName(Widget);
    } // setupUi

    void retranslateUi(QWidget *Widget)
    {
        Widget->setWindowTitle(QCoreApplication::translate("Widget", "Widget", nullptr));
        img->setText(QCoreApplication::translate("Widget", "TextLabel", nullptr));
        img_num->setText(QCoreApplication::translate("Widget", "TextLabel", nullptr));
        sex->setText(QCoreApplication::translate("Widget", "sex", nullptr));
        label_2->setText(QCoreApplication::translate("Widget", "\345\207\272\347\224\237\346\227\245\346\234\237\357\274\232", nullptr));
        label_3->setText(QCoreApplication::translate("Widget", "\346\200\247\345\210\253\357\274\232", nullptr));
        label->setText(QCoreApplication::translate("Widget", "\347\234\201\344\273\275\357\274\232", nullptr));
        provin->setText(QCoreApplication::translate("Widget", "\344\272\221\345\215\227", nullptr));
        birthday->setText(QCoreApplication::translate("Widget", "2024", nullptr));
        label_7->setText(QCoreApplication::translate("Widget", "\350\272\253\344\273\275\350\257\201\345\217\267\347\240\201\357\274\232", nullptr));
        num_id->setText(QCoreApplication::translate("Widget", "\345\217\267\347\240\201", nullptr));
        test->setText(QCoreApplication::translate("Widget", "\346\243\200\346\265\213", nullptr));
        train->setText(QCoreApplication::translate("Widget", "VIM\350\256\255\347\273\203", nullptr));
        btn_path->setText(QCoreApplication::translate("Widget", "\346\233\264\346\224\271\350\267\257\345\276\204", nullptr));
        btn->setText(QCoreApplication::translate("Widget", "\345\274\200\345\247\213", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Widget: public Ui_Widget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WIDGET_H
