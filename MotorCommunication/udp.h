#ifndef UDP_H
#define UDP_H


#include <QUdpSocket>
#include <QThread>
#include <QTimer>
#include <QCoreApplication>
class udp : public QThread
{
    Q_OBJECT
public:
    udp(QHostAddress h,quint16 p);
    ~udp();

    enum RECEIVE_TYPE  {ON_SERVO = 0x00, OFF_SERVO = 0x01, GET_POSITION = 0x02, GET_PULSE = 0x03, WRITE_POSITION = 0x04, WRITE_PUSLE = 0x05,
                        SELECT_JOB = 0x06, START_JOB = 0x07,HOME_POS = 0x08,SAVE_FILE = 0x09,LOAD_FILE = 0x0A,DELETE_FILE = 0x0B,
                        GET_VARPOS =0x0C,WRITE_VARPOS = 0x0D, WRITE_BYTE = 0x0E};

//--------BOOL---------------------------
    bool ConnectMotoman();
    bool DisconnectMotoman();
    bool OnServo();
    bool OffServo();
    bool SendData(char* buffer, int lenght);
    bool SendDataFile (char* buffer, int lenght);
    bool HomePos();
    bool GetCartasianPos();
    bool GetPulsePos();
    bool WritePosCar(int32_t speed,int32_t X,int32_t Y,int32_t Z,int32_t RX,int32_t RY,int32_t RZ);
    bool WritePosPulse(int32_t speed,int32_t R1,int32_t R2,int32_t R3,int32_t R4,int32_t R5,int32_t R6);

    bool SelectJob(char* jobname);
    bool StartJob();

    bool SAVEFILE(char *name, int length);
    bool FileBlockNoReceive(int blockNo);

    bool FileBlockNoSend(int blockNo);

    bool LOADFILE_REQUEST(char *name, int length);
    bool TransmitData(char data[], int blockNo, int length);

    bool DELETEFILE(char *name,int length);


    bool GetVarPosition(uint16_t index);
    bool WriteVarPosition(uint16_t index, std::vector<int32_t> pos);
    bool WriteByte(uint16_t index, uint8_t data);
    bool GetByte(uint16_t index);



    bool StopReadPos; // lua chon dang Position hien thi

    bool StopBothPos; // ngung doc hai vi tri




//---------------------------------------
    uint16_t INSTANCE;
    uint16_t INSTANCE2;
    int32_t ByteArray2Int32 (QByteArray* buffer,int start, int number);

//--------QString------------------------
     QString SendCommand(QByteArray buffer);
     QString ByteArray2Hex(QByteArray buffer);
     QString tx_data;
     QString rx_data;
     QString rx_dataFile;
     QString HEX2ASCII(QString rxdataFile);
//---------------------------------------

//-------QByteArray----------------------
     QByteArray Hex2ByteArray (QString s);
     QByteArray *Get_rx_buffer();
     QByteArray* Get_rx_bufferFile();
     QByteArray Int32ToByteArray(int32_t value);

//---------------------------------------

//--------Pointer------------------------
      QUdpSocket* client;

//---------------------------------------

    double Pulse2Joint(int32_t pulse, int i);
//------Void-----------------------------
    void ReceiveData();
    void ReceiveDataFile();
    void run();
    void convert_hexa(char*  input, char* output);
//---------------------------------------
signals:
    void ReadPos_cons();
    void SigReadPulse();
    void SigReadCartasian();
    void SigWriteCartasian();

private:
    QHostAddress _HostAddress;
    quint16 _port;
    QByteArray *rx_buffer;
    QByteArray *rx_bufferFile;
    struct TxData;
    struct FrameTrans;
    struct TxDataWritePosition;
    struct TxDataWritePulse;
    struct TxDataFile;
    struct TxDataWriteVarPosition;


    QByteArray WritePos;

    bool isStop;
protected:
     static const QString ON_SERVO_CMD;
     static const QString OFF_SERVO_CMD;
     static const QString GET_POS_CMD;
     static const QString GET_POS_PULSE;

     static const QString HOME_POSITION;
     static const QString WRITE_POS_HEADER;


     static const double PULSE_PER_DEGREE_S ;
     static const double PULSE_PER_DEGREE_L ;
     static const double PULSE_PER_DEGREE_U ;
     static const double PULSE_PER_DEGREE_RBT ;





};

#endif // UDP_H
