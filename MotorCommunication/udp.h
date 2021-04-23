#ifndef UDP_H
#define UDP_H


#include <QUdpSocket>
#include <QThread>
#include <QObject>
#include <QTimer>

class udp : public QThread
{
public:
    udp(QHostAddress h,quint16 p);
    ~udp();

    enum RECEIVE_TYPE  {ON_SERVO = 0x00, OFF_SERVO = 0x01, GET_POSITION = 0x02, GET_PULSE = 0x03, WRITE_POSITION = 0x04, WRITE_PUSLE = 0x05};


//--------BOOL---------------------------
    bool ConnectMotoman();
    bool DisconnectMotoman();
    bool OnServo();
    bool OffServo();
    bool GetPosCar();
    bool GetPosPul();
    bool SendData(char* buffer, int lenght);
    bool SendDataFile (char* buffer, int lenght);
    bool HomePos();
    bool WritePosCar(int32_t speed,int32_t X,int32_t Y,int32_t Z,int32_t RX,int32_t RY,int32_t RZ);
    bool WritePosPulse(int32_t speed,int32_t R1,int32_t R2,int32_t R3,int32_t R4,int32_t R5,int32_t R6);

    bool SelectJob(char* jobname);
    bool StartJob();

    bool SAVEFILE(char *name, int length);
    bool FILEACK(int blockNo);

    bool LOADFILE_REQUEST(char name[], int length);
    bool TransmitData(char data[], int blockNo, int length);

    bool DELETEFILE(char name[],int length);


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
     QString HEX2ASCII();
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

//------Void-----------------------------
    void ReceiveData();
    void ReceiveDataFile();
    void run();
    void convert_hexa(char*  input, char* output);
//---------------------------------------


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


    bool isStop;
    QByteArray WritePos;
protected:
     static const QString ON_SERVO_CMD;
     static const QString OFF_SERVO_CMD;
     static const QString GET_POS_CMD;
     static const QString GET_POS_PULSE;

     static const QString HOME_POSITION;
     static const QString WRITE_POS_HEADER;
     static const QString SAVE_FILE;
     static const QString START_JOB;

private slots:
     void ReadPos();


};

#endif // UDP_H
