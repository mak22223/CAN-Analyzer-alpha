#ifndef ADAPTERCONNECTOR_H
#define ADAPTERCONNECTOR_H

#define DEBUG

#include <QDebug>

#include <Windows.h>
#include <QTime>
#include <QList>
#include <QSerialPort>
#include <QSerialPortInfo>

struct CanFrame {
    unsigned long id;
    unsigned char data[8];
};

namespace CAN {
    enum {
        NoError = 0,
        NoAdapterConn,
        NoCANConn,
        NoCorrectAdapter
    };
}

class AdapterConnector : public QObject {
    Q_OBJECT
public:
    AdapterConnector(QObject *parent = nullptr);
    ~AdapterConnector();
    int resetSettings();
    int getCurrentSettings(QSerialPortInfo &port, qint32 &baudrate);
    int setCurrentSettings(const QSerialPortInfo *port, const qint32 baudrate);
    int openConnection();
    void closeConnection();

signals:
    void frameReceived(CanFrame frame);

private slots:
    void newDataReceived();

private:
    QSerialPort *serial;

};



#endif // ADAPTERCONNECTOR_H
