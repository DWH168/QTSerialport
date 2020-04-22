#include "serialport.h"
#include "ui_serialport.h"
#include<QMessageBox>
/*
*
* 微信公众号：智慧小巷
* 获取更多资料
*/
Serialport::Serialport(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Serialport)
{
    ui->setupUi(this);
    setMaximumSize(570,460);
    setMinimumSize(570,460);
    QStringList baudList;//波特率
    QStringList parityList;//校验位
    QStringList dataBitsList;//数据位
    QStringList stopBitsList;//停止位

    baudList<<"1200"<<"2400"<<"4800"<<"9600"<<"38400"<<"115200";

    ui->Bound_cbx->addItems(baudList);//波特率
    ui->Bound_cbx->setCurrentIndex(3);//从0开始索引 9600

    parityList<<"无"<<"奇"<<"偶";

    ui->CheckBit_cbx->addItems(parityList);//校验位
    ui->CheckBit_cbx->setCurrentIndex(0);

    dataBitsList<<"5"<<"6"<<"7"<<"8";
    ui->DataBit_cbx->addItems(dataBitsList);//数据位
    ui->DataBit_cbx->setCurrentIndex(3);

    stopBitsList<<"1";
    stopBitsList<<"1.5";
    stopBitsList<<"2";

    ui->StopBit_cbx->addItems(stopBitsList);//停止位
    ui->StopBit_cbx->setCurrentIndex(0);
}

Serialport::~Serialport()
{
    delete ui;
}

void Serialport::on_search_btn_clicked()
{
     QList<QSerialPortInfo>  infos = QSerialPortInfo::availablePorts();
     if(infos.isEmpty())
     {
         ui->cbx_port->clear();
         ui->cbx_port->addItem("暂无可用串口");
         return;
     }
    foreach (QSerialPortInfo info, infos) {
//        my_serial_port_->setPortName(info.portName());
        ui->cbx_port->clear();
        ui->cbx_port->addItem(info.portName());
    }
}

void Serialport::on_open_btn_clicked()
{
    MySerial.setPortName(ui->cbx_port->currentText());//设置串口号;也就是说打开的是当前显示的串口
    if(ui->open_btn->text()=="打开串口")//打开串口
    {
        if(MySerial.open(QIODevice::ReadWrite))//读写方式打开,成功后设置串口
        {
            MySerial.setBaudRate(ui->Bound_cbx->currentText().toInt());//设置波特率
            switch(ui->DataBit_cbx->currentIndex())
            {
                case 0:
                        MySerial.setDataBits(QSerialPort::Data5);//设置数据位
                break;
                case 1:
                        MySerial.setDataBits(QSerialPort::Data6);//设置数据位
                break;
                case 2:
                        MySerial.setDataBits(QSerialPort::Data7);//设置数据位
                break;
                case 3:
                        MySerial.setDataBits(QSerialPort::Data8);//设置数据位
                break;
            }

            switch(ui->CheckBit_cbx->currentIndex())
            {
                case 0:
                        MySerial.setParity(QSerialPort::NoParity);//设置校验位
                break;
                case 1:
                         MySerial.setParity(QSerialPort::OddParity);//设置校验位
                break;
                case 2:
                        MySerial.setParity(QSerialPort::EvenParity);//设置校验位
                break;
            }
            switch(ui->StopBit_cbx->currentIndex())
            {
                case 0:
                        MySerial.setStopBits(QSerialPort::OneStop);//设置停止位
                break;
                case 1:
                         MySerial.setStopBits(QSerialPort::OneAndHalfStop);//设置停止位
                break;
                case 2:
                        MySerial.setStopBits(QSerialPort::TwoStop);//设置停止位
                break;
            }

            MySerial.setFlowControl(QSerialPort::NoFlowControl);//设置流控制
            ui->open_btn->setText("关闭串口");

            //使用定时器循环读取,接收的数据
            MyTimer = new QTimer(this);
            connect(MyTimer,&QTimer::timeout,[=](){

                QByteArray readData = MySerial.readAll();//读取串口数据

                if(!readData.isNull())//将读到的数据显示到数据接收区
                {
                    if(ui->ckb_hex_show->isChecked()==true)//选中HEX显示
                    {
                        readData=readData.toHex();//转为HEX
                        ui->re_edit->append(readData);
                    }
                    else//未选中HEX显示
                    {
                        ui->re_edit->append(QString::fromLocal8Bit(readData));
                    }
                    readData.clear();//清除接收缓存
                }
            });
            MyTimer->start(100);//100ms
            ui->set_seria->setEnabled(false);
        }
        else//串口打开失败
        {
            ui->open_btn->setText("打开失败");
            QMessageBox::about(NULL, "提示", "串口未打开");
            return ;
        }
    }
    else if(ui->open_btn->text()=="关闭串口")//关闭串口
    {
        ui->open_btn->setText("打开串口");
        MyTimer->stop();//关定时器
        MySerial.close();//关串口
    }
}

void Serialport::on_send_btn_clicked()
{
    QString SendData;
    QByteArray SendHex;//HEX发送
    if(ui->open_btn->text()=="关闭串口")//打开串口才可以发送数据
    {
        if(!ui->send_edit->toPlainText().isEmpty())//发送区不为空
        {
            SendData = ui->send_edit->toPlainText();//获取发送区的数据
            if(ui->ckb_hex_send->isChecked()==true)//SendCheckBox被选中HEX发送
            {
                SendHex.append(SendData).toHex();//转HEX存储
            }
            else//没有选中HEX发送
            {
                SendHex.append(SendData.toLocal8Bit());
                //qDebug()<<SendHex<<endl;
            }
            MySerial.write(SendHex,SendHex.length());//写入缓冲区
        }
        else//发送区为空
        {
            QMessageBox::about(NULL, "提示", "请输入发送内容");
        }
    }
    else//串口未打开
    {
        QMessageBox::about(NULL, "提示", "串口未打开!");
    }
}

void Serialport::on_claer_btn_clicked()
{
    ui->re_edit->clear();
}
