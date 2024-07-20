#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QFileDialog>
#include"Card.h"
#include <QMap>//映射

QT_BEGIN_NAMESPACE
namespace Ui {
class Widget;
}
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();
    void beautiful();


private slots:
    void on_btn_path_clicked();

    void on_btn_clicked();

    void on_train_clicked();

    void on_test_clicked();

    void rec_text();

    void rec_img();
    void rec_img2();

    void diaplay()const;

private:
    Ui::Widget *ui;
    Card *card;

    void is_ui_visiable(bool state);
};
#endif // WIDGET_H
