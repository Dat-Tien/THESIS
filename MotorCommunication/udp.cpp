#include "udp.h"

#include <QUdpSocket>
#include <QString>
#include <QByteArray>
#include <QThread>
#include <QTimer>
#include <QDebug>
#include <QObject>
#include <mainwindow.h>
#include <QString>

//-----------Create UDP Socket------------------------------------------------------
udp::udp(QHostAddress h,quint16 p  )
{
    _HostAddress = h;
    _port = p;
    rx_buffer = new QByteArray;
    rx_bufferFile = new QByteArray;
}
udp::~udp()
{
    delete [] rx_buffer;
}
//----------------------------------------------------------------------------------

//------------Struct--------------------------------------------------------------
struct udp::TxData
{
    const char identifier[4] = {'Y','E','R','C'};
    const uint16_t header_size = 32;
    uint16_t data_size;
    const uint8_t reserve1 = 3;
    const uint8_t processing_division = 1;
    const uint8_t ack = 0;
    uint8_t id;
    const uint32_t block_no = 0;
    const char reserve2[8] = {'9','9','9','9','9','9','9','9'};
    uint16_t command_no;
    uint16_t instance;
    uint8_t attribute;
    uint8_t service;
    const uint16_t padding = 0;

   // QByteArray data;
};
struct udp::TxDataFile
{
    const char identifier[4] = {'Y','E','R','C'};
    const uint16_t header_size = 32;
    uint16_t data_size;
    const uint8_t reserve = 3;
    const uint8_t processing_division = 2;
    uint8_t ack;
    uint8_t id;
    uint32_t block_no;
    const char reserve2[8] = {'9','9','9','9','9','9','9','9'};
    uint16_t command_no;
    uint16_t instance;
    uint8_t attribute;
    uint8_t service;
    const uint16_t padding = 0;
};
struct udp::TxDataWritePosition
{
  const uint32_t control_group_robot = 1;
  const uint32_t control_group_station = 0;
  const uint32_t classification_in_speed = 0;
  uint32_t speed;
  const uint32_t coordinate = 0x10;
  int32_t x;
  int32_t y;
  int32_t z;
  int32_t rx;
  int32_t ry;
  int32_t rz;
  const uint32_t reservation1 = 0;
  const uint32_t reservation2 = 0;
  const uint32_t type = 0;
  const uint32_t expanded_type = 0;
  const uint32_t tool_no = 0;
  const uint32_t user_coordinate_no = 0;
  const uint32_t base_1_position = 0;
  const uint32_t base_2_position = 0;
  const uint32_t base_3_position = 0;
  const uint32_t station_1_position = 0;
  const uint32_t station_2_position = 0;
  const uint32_t station_3_position = 0;
  const uint32_t station_4_position = 0;
  const uint32_t station_5_position = 0;
  const uint32_t station_6_position = 0;
};
struct udp::TxDataWritePulse
{
  const uint32_t control_group_robot = 1;
  const uint32_t control_group_station = 0;
  const uint32_t classification_in_speed = 0;
  uint32_t speed;
  int32_t r1;
  int32_t r2;
  int32_t r3;
  int32_t r4;
  int32_t r5;
  int32_t r6;
  int32_t r7;
  int32_t r8;
  const uint32_t tool_no = 0;
  const uint32_t base_1_position = 0;
  const uint32_t base_2_position = 0;
  const uint32_t base_3_position = 0;
  const uint32_t station_1_position = 0;
  const uint32_t station_2_position = 0;
  const uint32_t station_3_position = 0;
  const uint32_t station_4_position = 0;
  const uint32_t station_5_position = 0;
  const uint32_t station_6_position = 0;
};


//------------------------------------------------------------------------


//----------Convert data------------------------------------------------------------
QString udp::SendCommand(QByteArray buffer)
{

    client->writeDatagram(buffer,buffer.length(),_HostAddress,_port+1);
    return ByteArray2Hex(buffer);
}
QString udp::ByteArray2Hex(QByteArray buffer)
{
    QString s;
    for (int i = 0; i < buffer.size(); i++)
    {
        QString c = QString::number(buffer.at(i),16);
        if(c.size()<2)
        {
            s.push_back('0');
            s.push_back(c);
        }
        else{
            s.push_back(c.at(c.size()-2));
            s.push_back(c.at(c.size()-1));
        }
        s.push_back(' ');
    }
    s = s.toUpper();
    return s;
}
QByteArray udp::Hex2ByteArray (QString s)
{
    QByteArray buffer;
    for (int i = 0; i < s.size(); i = i+3)
    {
        QString temp;
        temp.push_back(s.at(i));
        temp.push_back(s.at(i+1));
        bool ok;
        char x = temp.toInt(&ok,16);
        if(ok == 1)
        {
            buffer.push_back(x);
        }
        else
            return 0;
    }
    return buffer;
}
QByteArray udp::Int32ToByteArray (int32_t value)
{
    QByteArray buffer;
    for (uint i = 0;i < sizeof (int32_t); i++) {
        char u = (value>>8*i) & 0xFF;
        buffer.push_back(u);
    }
    return buffer;
}
int32_t udp::ByteArray2Int32 (QByteArray* buffer,int start, int number)
{
    int32_t value = 0;
    for (int i = start;i < start+number; i++) {
        int32_t temp = (unsigned char) buffer->at(i) ;
        value += temp << 8*(i-start);
    }
    return value;

}
//----------------------------------------------------------------------------------

//-----------Send Resquest UDP------------------------------------------------------
bool udp::SendData (char* buffer, int lenght)
{

  client->writeDatagram(buffer,lenght,_HostAddress,_port);
  return 1;
}
bool udp::SendDataFile (char* buffer, int lenght)
{

  client->writeDatagram(buffer,lenght,_HostAddress,_port);
  return 1;
}
//----------------------------------------------------------------------------------

//-----------Receive UDP Answer-----------------------------------------------------
void udp::ReceiveData()
{
    rx_buffer->resize(client->pendingDatagramSize());
    client->readDatagram(rx_buffer->data(),rx_buffer->size());
    rx_data = ByteArray2Hex(*rx_buffer);
}
QByteArray* udp::Get_rx_buffer()
{
    return rx_buffer;
}

void udp::ReceiveDataFile()
{
    rx_bufferFile->resize(client->pendingDatagramSize());
    client->readDatagram(rx_bufferFile->data(),rx_bufferFile->size());
    rx_dataFile = ByteArray2Hex(*rx_bufferFile);
}

QByteArray* udp::Get_rx_bufferFile()
{
    return rx_bufferFile;
}
//----------------------------------------------------------------------------------

//----------Connected/Disconnected--------------------------------------------------
bool udp::ConnectMotoman()
{
    client = new QUdpSocket;
    client->bind();
    isStop = false;
    return 1;
}
bool udp::DisconnectMotoman()
{
    client ->close();
    delete client;
    isStop = true;
    return 1;

}
//----------------------------------------------------------------------------------

//-----------On/Off Servo-----------------------------------------------------------
bool udp::OnServo()
{
    TxData sent_data;
    uint32_t data = 1;
    sent_data.id = RECEIVE_TYPE::ON_SERVO;
    sent_data.command_no = 0x83;
    sent_data.instance = 2;
    sent_data.attribute = 1;
    sent_data.service = 0x10;
    uint16_t data_length = sizeof (data);
    uint16_t total_length = 32 + data_length;
    sent_data.data_size = data_length;
    char* buffer = new char[total_length];
    memcpy(buffer,&sent_data,32);
    memcpy(buffer+32,&data,data_length);
    SendData(buffer,total_length);
    delete [] buffer;
//    SendCommand(Hex2ByteArray(ON_SERVO_CMD));
//    tx_data = ON_SERVO_CMD;
    return 1;
}
bool udp::OffServo()
{
    TxData sent_data;
    uint32_t data = 2;
    sent_data.id = RECEIVE_TYPE::OFF_SERVO;
    sent_data.command_no = 0x83;
    sent_data.instance = 2;
    sent_data.attribute = 1;
    sent_data.service = 0x10;
    uint16_t data_length = sizeof (data);
    uint16_t total_length = 32 + data_length;
    sent_data.data_size = data_length;
    char* buffer = new char[total_length];
    memcpy(buffer,&sent_data,32);
    memcpy(buffer+32,&data,data_length);
    SendData(buffer,total_length);
    delete [] buffer;
  //    SendCommand(Hex2ByteArray(OFF_SERVO_CMD));
  //    tx_data = OFF_SERVO_CMD;
      return 1;
}
//----------------------------------------------------------------------------------

//----------Get Postion Caresian/Pulse----------------------------------------------
bool udp::GetPosCar()
{
    TxData sent_data;
    char* buffer = new char[sizeof (sent_data)];
    sent_data.id = 3;
    sent_data.command_no = 0x75;
    sent_data.instance = 0x65;
    sent_data.attribute = 0;
    sent_data.service = 0x01;
    sent_data.data_size = 0;
    memcpy(buffer,&sent_data,sizeof (sent_data));
    SendData(buffer,sizeof (sent_data));
    delete [] buffer;
    qDebug()<<"Position";
    return 1;
}
bool udp::GetPosPul()
{
    TxData sent_data;
    char* buffer = new char[sizeof (sent_data)];
    sent_data.id = 4;
    sent_data.command_no = 0x75;
    sent_data.instance = 0x01;
    sent_data.attribute = 0;
    sent_data.service = 0x01;
    sent_data.data_size = 0;

    memcpy(buffer,&sent_data,sizeof (sent_data));
    SendData(buffer,sizeof (sent_data));
    delete [] buffer;
    qDebug()<<"Pulse";
    return 1;
}
//----------------------------------------------------------------------------------
void udp::run()
{
    if(isStop == false)
    {
        if(INSTANCE == 0x65)
        {
            TxData sent_data;
            char* buffer = new char[sizeof (sent_data)];
            sent_data.id = RECEIVE_TYPE::GET_POSITION;
            sent_data.command_no = 0x75;
            sent_data.instance = 0x65;
            sent_data.attribute = 0;
            sent_data.service = 0x01;
            sent_data.data_size = 0;
          //  sent_data.data.resize(0);
            memcpy(buffer,&sent_data,sizeof (sent_data));
            SendData(buffer,sizeof (sent_data));
            delete [] buffer;
          //    SendCommand(Hex2ByteArray(GET_POS_CMD));
          //    tx_data = GET_POS_CMD;

        }
        if(INSTANCE == 0x01)
        {
            TxData sent_data;
            char* buffer = new char[sizeof (sent_data)];
            sent_data.id = RECEIVE_TYPE::GET_PULSE;
            sent_data.command_no = 0x75;
            sent_data.instance = 0x01;
            sent_data.attribute = 0;
            sent_data.service = 0x01;
            sent_data.data_size = 0;

            memcpy(buffer,&sent_data,sizeof (sent_data));
            SendData(buffer,sizeof (sent_data));
            delete [] buffer;
//            qDebug()<<"Pulse";

        }

    }
}

//----------------------------------------------------------------------------------

//---------Home Position------------------------------------------------------------
bool udp::HomePos()
{
    TxData Header;
    Header.command_no = 0x8A;
    Header.instance = 0x01;
    Header.attribute = 1;
    Header.service = 0x02;
    Header.id = 7;


    TxDataWritePosition Pos;
    Pos.speed = 1000;
    Pos.x = 182231;
    Pos.y = 1503;
    Pos.z = 86230;
    Pos.rx = 1799577;
    Pos.ry = -9132;
    Pos.rz = -54698;
    Header.data_size = sizeof (Pos);

    int total_length = sizeof (Header) + sizeof (Pos);
    char *buffer = new char[total_length];
    memcpy(buffer,&Header,sizeof (Header));
    memcpy(buffer + sizeof (Header),&Pos, total_length);
    SendData(buffer,sizeof (Header) + sizeof (Pos));
    delete [] buffer;
    qDebug()<<"Homing";
   // tx_data = ByteArray2Hex(Header)+ ByteArray2Hex(Pos);
    return 1;
}
//----------------------------------------------------------------------------------

//---------Write Cartesian/Pulse Postion--------------------------------------------
bool udp::WritePosCar(int32_t speed,int32_t X,int32_t Y,int32_t Z,int32_t RX,int32_t RY,int32_t RZ)
{
    TxData sent_data;
    sent_data.id = RECEIVE_TYPE::WRITE_POSITION;
    sent_data.command_no = 0x8A;
    sent_data.instance = 0x01;
    sent_data.attribute = 01;
    sent_data.service = 0x02;

    TxDataWritePosition position;
    position.x = X;
    position.y = Y;
    position.z = Z;
    position.rx = RX;
    position.ry = RY;
    position.rz = RZ;
    position.speed = speed;

    sent_data.data_size = sizeof(position);
    char* buffer = new char[sizeof(sent_data)+sizeof (position)];
    memcpy(buffer,&sent_data,sizeof (sent_data));
    memcpy(buffer+sizeof (sent_data),&position,sizeof (position));
    SendData(buffer,sizeof(sent_data)+sizeof (position));
    delete [] buffer;

   return 1;
}

bool udp::WritePosPulse(int32_t speed,int32_t R1,int32_t R2,int32_t R3,int32_t R4,int32_t R5,int32_t R6)
{
    TxData sent_data;
    sent_data.id = RECEIVE_TYPE::WRITE_PUSLE;
    sent_data.command_no = 0x8B;
    sent_data.instance = 0x01;
    sent_data.attribute = 01;
    sent_data.service = 0x02;

    TxDataWritePulse position;
    position.r1 = R1;
    position.r2 = R2;
    position.r3 = R3;
    position.r4 = R4;
    position.r5 = R5;
    position.r6 = R6;
    position.speed = speed;

    sent_data.data_size = sizeof(position);
    char* buffer = new char[sizeof(sent_data)+sizeof (position)];
    memcpy(buffer,&sent_data,sizeof (sent_data));
    memcpy(buffer+sizeof (sent_data),&position,sizeof (position));
    SendData(buffer,sizeof(sent_data)+sizeof (position));
    delete [] buffer;
    return 1;
}
//----------------------------------------------------------------------------------



//---------Start Job----------------------------------------------------------------
bool udp::SelectJob(char* jobname)
{
    uint32_t line_number=0;
    TxData sent_data;
    sent_data.id = 0x0A;
    sent_data.command_no = 0x87;
    sent_data.instance = 1;
    sent_data.attribute = 1;
    sent_data.service = 0x02;
    uint16_t data_length = 36;
    uint16_t total_length = 32 + data_length;
    sent_data.data_size = data_length;
    char* buffer = new char[total_length];

    memcpy(buffer,&sent_data,32);
    memcpy(buffer+32,jobname,32);
    memcpy(buffer+32+32,&line_number,4);
    SendData(buffer,total_length);
    delete [] buffer;
    return 1;
}
bool udp::StartJob()
{
    SendCommand(Hex2ByteArray(START_JOB));
    return 1;
}
//----------------------------------------------------------------------------------


//--------------FILE---------------------------------------------------------
bool udp::SAVEFILE(char *name, int length)
{
   TxDataFile dataFile;
   dataFile.data_size = length;
   dataFile.ack = 0;
   dataFile.id = 0;
   dataFile.block_no = 0;
   dataFile.command_no = 0x00;
   dataFile.attribute = 0;
   dataFile.instance = 0;
   dataFile.service = 0x16;
   char *buffer = new  char[sizeof (dataFile)+ length];
   memcpy(buffer,&dataFile,sizeof (dataFile));
   memcpy(buffer + sizeof(dataFile),name,length);
   SendDataFile(buffer,sizeof(dataFile)+length);

   delete [] buffer;
   return 1;
}
bool udp::LOADFILE(char name[], int length)
{
    TxDataFile dataFile;
    dataFile.data_size = length;
    dataFile.ack = 0;
    dataFile.id = 0;
    dataFile.block_no = 0;
    dataFile.command_no = 0x15;
    dataFile.attribute = 0;
    dataFile.service = 0;
    char *buffer = new  char[sizeof (dataFile)+ length];
    memcpy(buffer,&dataFile,sizeof (dataFile));
    memcpy(buffer + sizeof(dataFile),&name,length);
    SendDataFile(buffer,sizeof(dataFile)+length);
    delete [] buffer;
    return 1;
}
bool udp::DELETEFILE(char name[], int length)
{
    TxDataFile dataFile;
    dataFile.data_size = length;
    dataFile.ack = 0;
    dataFile.id = 0;
    dataFile.block_no = 0;
    dataFile.command_no = 0x09;
    dataFile.attribute = 0;
    dataFile.service = 0;
    char *buffer = new  char[sizeof (dataFile)+ length];
    memcpy(buffer,&dataFile,sizeof (dataFile));
    memcpy(buffer + sizeof(dataFile),&name,length);
    SendDataFile(buffer,sizeof(dataFile)+length);
    delete [] buffer;
    return 1;
}
bool udp::TransmitData(char data[],int blockNo, int length)
{
    TxDataFile dataFile;
    dataFile.data_size = length;
    dataFile.ack = 0;
    dataFile.id = 0;
    dataFile.block_no = blockNo;
    dataFile.command_no = 0x15;
    dataFile.attribute = 0;
    dataFile.service = 0;
    char *buffer = new  char[sizeof (dataFile)+ length];
    memcpy(buffer,&dataFile,sizeof (dataFile));
    memcpy(buffer + sizeof(dataFile),&data,length);
    SendDataFile(buffer,sizeof(dataFile)+length);
    delete [] buffer;
    return 1;
}

QString udp::HEX2ASCII()
{

//    QByteArray *buffer = rx_bufferFile;
//    QString strHex = QString::fromLocal8Bit(*buffer);
    QString str = rx_dataFile;
    char strChar[str.length()];
    char strCharSend[str.length()-32];
    strcpy(strChar,str.toStdString().c_str());
    for (int i = 96;i< str.length();i++)
    {
        strCharSend[i-96] = strChar[i];
    }
    QString Send = QString::fromLocal8Bit(strCharSend);
    Send = Send.remove(" ");
    QString strAscii = QByteArray::fromHex(Send.toLocal8Bit());

    qDebug()<<strCharSend;
    return strAscii;
}

bool udp::FILEACK(int blockNo)
{
    TxDataFile dataFile;
    dataFile.data_size = 0;
    dataFile.ack = 1;
    dataFile.id = 0;
    dataFile.block_no = blockNo;
    dataFile.command_no = 0x00;
    dataFile.attribute = 0;
    dataFile.instance = 0;
    dataFile.service = 0x16;
    char *buffer = new  char[sizeof (dataFile)];
    memcpy(buffer,&dataFile,sizeof (dataFile));
    SendDataFile(buffer,sizeof(dataFile));
    delete [] buffer;
    return 1;
}
//---------------------------------------------------------------------------









const QString udp::ON_SERVO_CMD =     "59 45 52 43 20 00 04 00 03 01 00 00 00 00 00 00 39 39 39 39 39 39 39 39 83 00 02 00 01 10 00 00 01 00 00 00";
const QString udp::OFF_SERVO_CMD =    "59 45 52 43 20 00 04 00 03 01 00 01 00 00 00 00 39 39 39 39 39 39 39 39 83 00 02 00 01 10 00 00 02 00 00 00";
const QString udp::GET_POS_CMD =      "59 45 52 43 20 00 00 00 03 01 00 02 00 00 00 00 39 39 39 39 39 39 39 39 75 00 65 00 00 01 00 00";
const QString udp::GET_POS_PULSE =    "59 45 52 43 20 00 00 00 03 01 00 03 00 00 00 00 39 39 39 39 39 39 39 39 75 00 01 00 00 01 00 00";
const QString udp::WRITE_POS_HEADER = "59 45 52 43 20 00 68 00 03 01 00 04 00 00 00 00 39 39 39 39 39 39 39 39 8A 00 01 00 01 02 00 00 01 00 00 00 00 00 00 00 00 00 00 00";
const QString udp::SAVE_FILE =        "59 45 52 43 20 00 0A 00 03 02 00 0F 00 00 00 00 39 39 39 39 39 39 39 39 00 00 00 00 00 16 00 00 50 49 43 4B 41 39 2E 4A 42 49";
const QString udp::START_JOB = "59 45 52 43 20 00 04 00 03 01 00 09 00 00 00 00 39 39 39 39 39 39 39 39 86 00 01 00 01 10 00 00 01 00 00 00";
