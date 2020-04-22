#ifndef SERIALPORT_H
#define SERIALPORT_H
#pragma execution_character_set("utf-8")
#include <QWidget>
#include<QSerialPortInfo>
#include<QSerialPort>
#include <QTimer>
namespace Ui {
class Serialport;
}

class Serialport : public QWidget
{
    Q_OBJECT

public:
    explicit Serialport(QWidget *parent = 0);
    ~Serialport();

private slots:
    void on_search_btn_clicked();

    void on_open_btn_clicked();

    void on_send_btn_clicked();

    void on_claer_btn_clicked();

private:
    Ui::Serialport *ui;
    QSerialPort MySerial;//创建一个可操作的串口
    QTimer *MyTimer;//定义一个定时器
};

#endif // SERIALPORT_H
