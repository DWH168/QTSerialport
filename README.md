**QT的串口通信助手C++代码开源**
![在这里插入图片描述](https://img-blog.csdnimg.cn/20200422213908881.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L2R3aDEzMTQ=,size_16,color_FFFFFF,t_70)
Qt是一种基于C++的跨平台图形用户界面应用程序开发框架
本次使用QT的版本是5.6
![在这里插入图片描述](https://img-blog.csdnimg.cn/20200422214030184.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L2R3aDEzMTQ=,size_16,color_FFFFFF,t_70)
需要在pro文件里面添加

 QT += serialport
 ![在这里插入图片描述](https://img-blog.csdnimg.cn/20200422214140518.png)
添加库文件
![在这里插入图片描述](https://img-blog.csdnimg.cn/20200422214223665.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L2R3aDEzMTQ=,size_16,color_FFFFFF,t_70)
布局界面

```cpp
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
```
界面的初始化
把设置串口的数据加载进去。

```cpp
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
```
![在这里插入图片描述](https://img-blog.csdnimg.cn/2020042213381780.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L2R3aDEzMTQ=,size_16,color_FFFFFF,t_70)
更多资料关注公众号:**智慧小巷**

