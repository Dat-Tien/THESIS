#include "udp.h"

#include <QUdpSocket>
#include <QString>
#include <QByteArray>
#include <QThread>
#include <QTimer>
#include <QDebug>
#include <QObject>
#include <QString>
#include <QTime>

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



void delay1(int n)
{
    QTime dieTime= QTime::currentTime().addMSecs(n);
    while (QTime::currentTime() < dieTime)
        QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
};

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
struct udp::TxDataWriteVarPosition
{
    uint32_t data_type;
    const uint32_t figure = 0;
    const uint32_t tool_no = 0;
    const uint32_t user_coodirnate_no = 0;
    const uint32_t extended_figure = 0;
    int32_t first_axis_position;
    int32_t second_axis_position;
    int32_t third_axis_position;
    int32_t fourth_axis_position;
    int32_t fifth_axis_position;
    int32_t sixth_axis_position;
    const int32_t seventh_axis_position = 0;
    const int32_t eighth_axis_position = 0;

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
    qDebug()<<"isStop: "<< isStop;
    return 1;
}
bool udp::DisconnectMotoman()
{
    client ->close();
    delete client;
    isStop = true;
    qDebug()<<"isStop: "<< isStop;
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

//----------------------------------------------------------------------------------
void udp::run()
{
    qDebug()<<"Thread da mo!!!";
    int i = 0,a = 0;
    while(!isStop){

//        if(!StopBothPos){
            if(StopReadPos){
                Q_EMIT SigReadPulse();
            }
            delay1(20);
            i++;
            a++;
            if(i == 4 ){
                if(!StopReadPos){
                    Q_EMIT SigReadCartasian();
                }
                i =0;
            }
            if(a == 6){
                if(!StopReadPos){
                    Q_EMIT SigWriteCartasian();
                }
                a =0;
            }
        }

}

//----------------------------------------------------------------------------------

//---------Home Position------------------------------------------------------------
bool udp::HomePos()
{
    TxData Header;
    Header.command_no = 0x8B;
    Header.instance = 0x01;
    Header.attribute = 1;
    Header.service = 0x02;
    Header.id = RECEIVE_TYPE::HOME_POS;

    TxDataWritePulse Pos;
    Pos.r1 = 0;
    Pos.r2 = 0;
    Pos.r3 = 0;
    Pos.r4 = 0;
    Pos.r5 = 0;
    Pos.r6 = 0;
    Pos.speed = 10*100;
    Header.data_size = sizeof (Pos);

    int total_length = sizeof (Header) + sizeof (Pos);
    char buffer[total_length];
    memcpy(buffer,&Header,sizeof (Header));
    memcpy(buffer + sizeof (Header),&Pos, total_length);
    SendData(buffer,sizeof (Header) + sizeof (Pos));
    return 1;
}
//----------------------------------------------------------------------------------

//--------------Get Pulse/Cartasian Position----------------------------------------
bool udp::GetCartasianPos()
{
    TxData sent_data;
    char* buffer = new char[sizeof (sent_data)];
    sent_data.id = RECEIVE_TYPE::GET_POSITION;
    sent_data.command_no = 0x75;
    sent_data.instance = 0x65;
    sent_data.attribute = 0;
    sent_data.service = 0x01;
    sent_data.data_size = 0;
    memcpy(buffer,&sent_data,sizeof (sent_data));
    SendData(buffer,sizeof (sent_data));
    delete [] buffer;
    return 1;
}
bool udp::GetPulsePos()
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
//--------Read and Write Var Position ----------------------------------------------
bool udp::GetVarPosition(uint16_t index)
{
    TxData header;
    header.instance = index;
    header.command_no = 0x7F;
    header.attribute = 0;
    header.data_size = 0;
    header.service = 0x0E;
    header.id = 0x0C;
    char buffer [sizeof (header)];
    memcpy(buffer,&header,sizeof(header));
    SendData(buffer,sizeof(header));
    return 1;
}
bool udp::WriteVarPosition(uint16_t index, std::vector<int32_t> pos)
{
    TxData Header;
    Header.command_no = 0x7F;
    Header.instance = index;
    Header.attribute = 0;
    Header.service = 0x02;
    Header.id = RECEIVE_TYPE::WRITE_VARPOS;

    TxDataWriteVarPosition position;
    position.data_type = 0x11;
    position.first_axis_position = pos.at(0);
    position.second_axis_position = pos.at(1);
    position.third_axis_position =pos.at(2);
    position.fourth_axis_position = pos.at(3);
    position.fifth_axis_position = pos.at(4);
    position.sixth_axis_position = pos.at(5);

    Header.data_size = sizeof(position);

    char buffer[sizeof(Header)+ sizeof(position)];
    memcpy(buffer,&Header, sizeof(Header));
    memcpy(buffer + sizeof(Header),&position,sizeof(position));
    SendData(buffer, sizeof(buffer));
    return 1;
}


bool udp::WriteByte(uint16_t index, uint8_t data)
{
    TxData header;
    header.id = RECEIVE_TYPE::WRITE_BYTE;
    header.command_no = 0x7A;
    header.attribute = 1;
    header.service = 0x10;
    header.instance = index;
    header.data_size = sizeof(data);

    char buffer[sizeof(header)+ sizeof(data)];
    memcpy(buffer,&header,sizeof(header));
    memcpy(buffer+ sizeof(header),&data, sizeof(data));
    SendData(buffer,sizeof(buffer));
    return 1;
}

bool udp::GetByte(uint16_t index)
{
    TxData header;
    header.id = RECEIVE_TYPE::WRITE_BYTE;
    header.command_no = 0x7A;
    header.attribute = 1;
    header.service = 0x0E;
    header.instance = index;
    header.data_size = 0;
    char buffer[sizeof(header)];
    memcpy(buffer,&header,sizeof(header));
    SendData(buffer,sizeof(buffer));
    return 1;
}
//----------------------------------------------------------------------------------


//---------Start Job----------------------------------------------------------------
bool udp::SelectJob(char* jobname)
{
    uint32_t line_number=0;
    TxData sent_data;
    sent_data.id = RECEIVE_TYPE::SELECT_JOB;
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
    TxData sent_data;
    sent_data.id = RECEIVE_TYPE::START_JOB;
    sent_data.command_no = 0x86;
    sent_data.instance = 1;
    sent_data.attribute = 1;
    sent_data.service = 0x10;
    uint32_t data = 1;
    sent_data.data_size = sizeof (data);
    char *buffer = new char[sizeof(sent_data)+ sizeof(data)];
    memcpy(buffer,&sent_data,sizeof (sent_data));
    memcpy(buffer+sizeof(sent_data),&data,sizeof(data));
    SendData(buffer,sizeof(sent_data)+sizeof(data));
    delete [] buffer;
    return 1;
}
//----------------------------------------------------------------------------------


//--------------FILE---------------------------------------------------------
bool udp::SAVEFILE(char *name, int length) // Save File from YERC
{
   TxDataFile dataFile;
   dataFile.data_size = length;
   dataFile.ack = 0;
   dataFile.id = RECEIVE_TYPE::SAVE_FILE;
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
bool udp::FileBlockNoReceive(int blockNo) //Block No for load file from YERC
{
    TxDataFile dataFile;
    dataFile.data_size = 0;
    dataFile.ack = 1;
    dataFile.id = RECEIVE_TYPE::SAVE_FILE;
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
//----------------------------------------------------------

bool udp::LOADFILE_REQUEST(char *name, int length) // Load File from PC
{
    TxDataFile dataFile;
    dataFile.data_size = length;
    dataFile.ack = 0;
    dataFile.id = RECEIVE_TYPE::LOAD_FILE;
    dataFile.block_no = 0;
    dataFile.command_no = 0x00;
    dataFile.attribute = 0;
    dataFile.instance = 0;
    dataFile.service = 0x15;
    char *buffer = new  char[sizeof (dataFile)+ length];
    memcpy(buffer,&dataFile,sizeof (dataFile));
    memcpy(buffer + sizeof(dataFile),name,length);
    SendDataFile(buffer,sizeof(dataFile)+length);

    delete [] buffer;
    return 1;
}
bool udp::TransmitData(char data[],int blockNo, int length) // Transmit Data from PC
{
    TxDataFile dataFile;
    dataFile.data_size = length;
    dataFile.ack = 1;
    dataFile.id = RECEIVE_TYPE::LOAD_FILE;
    dataFile.block_no = blockNo;
    dataFile.command_no = 0;
    dataFile.attribute = 0;
    dataFile.instance = 0;
    dataFile.service = 0x15;
    char *buffer = new char[sizeof (dataFile)+ length];
    memcpy(buffer,&dataFile,sizeof (dataFile));
    memcpy(buffer + sizeof(dataFile),&data,length);
    SendDataFile(buffer,sizeof(dataFile)+length);



    delete [] buffer;
    return 1;
}
bool udp::FileBlockNoSend(int blockNo) // Check Block no Transmit data from PC
{
    TxDataFile dataFile;
    dataFile.data_size = 0;
    dataFile.ack = 1;
    dataFile.id = 0;
    dataFile.block_no = blockNo;
    dataFile.command_no = 0x00;
    dataFile.attribute = 0;
    dataFile.instance = 0;
    dataFile.service = 0x15;
    char *buffer = new  char[sizeof (dataFile)];
    memcpy(buffer,&dataFile,sizeof (dataFile));
    SendDataFile(buffer,sizeof(dataFile));
    delete [] buffer;
    return 1;
}

//--------------------------------------------------------------------
bool udp::DELETEFILE(char *name, int length) //Delete File
{
    TxDataFile dataFile;
    dataFile.data_size = length;
    dataFile.ack = 0;
    dataFile.id = RECEIVE_TYPE::DELETE_FILE;
    dataFile.block_no = 0;
    dataFile.command_no = 0x00;
    dataFile.attribute = 0;
    dataFile.instance = 0;
    dataFile.service = 0x09;
    char *buffer = new  char[sizeof (dataFile)+ length];
    memcpy(buffer,&dataFile,sizeof (dataFile));
    memcpy(buffer + sizeof(dataFile),name,length);
    SendDataFile(buffer,sizeof(dataFile)+length);

    delete [] buffer;
    return 1;
}















QString udp::HEX2ASCII(QString rxdataFile)
{

//    QByteArray *buffer = rx_bufferFile;
//    QString strHex = QString::fromLocal8Bit(*buffer);
    QString str = rxdataFile;
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


    return strAscii;

}




void udp::convert_hexa(char* input, char* output)
{
   int loop=0;
   int i=0;
   while(input[loop] != '\0'){
      sprintf((char*)(output+i),"%02X", input[loop]);
      loop+=1;
      i+=2;
   }
  output[i++] = '\0';
}


//---------------------------------------------------------------------------


double udp::Pulse2Joint(int32_t pulse, int i)
{
    if(i==0)
      {
        return double(pulse)/PULSE_PER_DEGREE_S;
      }
      else if (i==1) {
        return double(pulse)/PULSE_PER_DEGREE_L;
      }
      else if (i==2) {
        return double(pulse)/PULSE_PER_DEGREE_U;
      }
      else {
        return double(pulse)/PULSE_PER_DEGREE_RBT;
      }
}

//-----------PLC--------------
struct udp::TxPLC
{
    const uint8_t command = 0x11;
    const uint8_t fix1 = 0;
    const uint16_t channel = 0;
    const uint16_t Reserved1 = 0;
    uint16_t Total_number;
    const uint32_t Reserved2 = 0;
    uint16_t MFC_length;
    const uint8_t MFC =0x20;
    const uint8_t SFC = 0x0B;
    const uint16_t cpu_number = 0x10;
    uint16_t reference;
    uint16_t register_number;
    uint16_t data[];
};

bool udp::PLC(QHostAddress host, uint port,uint16_t addr,uint16_t no_reg,std::vector<uint16_t> data)
{
    TxPLC txdata;
    txdata.MFC_length = 8 + 2*data.size();
    txdata.reference = addr;
    txdata.register_number = no_reg;
    txdata.Total_number = 14 + txdata.MFC_length;
    memcpy(txdata.data,data.data(),data.size());
    char buffer [txdata.Total_number];
    memcpy(buffer,&txdata,sizeof(txdata));
    client->writeDatagram(buffer,sizeof (txdata),host,port);
    return 1;

}





const QString udp::ON_SERVO_CMD =     "59 45 52 43 20 00 04 00 03 01 00 00 00 00 00 00 39 39 39 39 39 39 39 39 83 00 02 00 01 10 00 00 01 00 00 00";
const QString udp::OFF_SERVO_CMD =    "59 45 52 43 20 00 04 00 03 01 00 01 00 00 00 00 39 39 39 39 39 39 39 39 83 00 02 00 01 10 00 00 02 00 00 00";
const QString udp::GET_POS_CMD =      "59 45 52 43 20 00 00 00 03 01 00 02 00 00 00 00 39 39 39 39 39 39 39 39 75 00 65 00 00 01 00 00";
const QString udp::GET_POS_PULSE =    "59 45 52 43 20 00 00 00 03 01 00 03 00 00 00 00 39 39 39 39 39 39 39 39 75 00 01 00 00 01 00 00";
const QString udp::WRITE_POS_HEADER = "59 45 52 43 20 00 68 00 03 01 00 04 00 00 00 00 39 39 39 39 39 39 39 39 8A 00 01 00 01 02 00 00 01 00 00 00 00 00 00 00 00 00 00 00";
//const QString udp::SAVE_FILE =        "59 45 52 43 20 00 0A 00 03 02 00 0F 00 00 00 00 39 39 39 39 39 39 39 39 00 00 00 00 00 16 00 00 50 49 43 4B 41 39 2E 4A 42 49";
//const QString udp::START_JOB = "59 45 52 43 20 00 04 00 03 01 00 09 00 00 00 00 39 39 39 39 39 39 39 39 86 00 01 00 01 10 00 00 01 00 00 00";

const double udp::PULSE_PER_DEGREE_S = 34816/30;
const double udp::PULSE_PER_DEGREE_L = 102400/90;
const double udp::PULSE_PER_DEGREE_U = 51200/90;
const double udp::PULSE_PER_DEGREE_RBT = 10204/30;
