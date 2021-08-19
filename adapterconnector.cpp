#include "adapterconnector.h"

AdapterConnector::AdapterConnector(QObject *parent) : QObject(parent)
{
    serial = new QSerialPort(this);

    serial->setPort(QSerialPortInfo::availablePorts().first());
    serial->setParity(QSerialPort::NoParity);
    serial->setDataBits(QSerialPort::Data8);
    serial->setStopBits(QSerialPort::OneStop);

    connect(serial, SIGNAL(readyRead()), this, SLOT(newDataReceived()));
}

AdapterConnector::~AdapterConnector() {

}

void AdapterConnector::newDataReceived() {

}

int AdapterConnector::openConnection() {
    int status = 0;

    if (!serial->open(QIODevice::ReadWrite)) {
        #ifdef DEBUG
        qDebug() << serial->errorString() << "Ошибка открытия порта.";
        #endif
        return CAN::NoAdapterConn;
    }
    #ifdef DEBUG
    qDebug() << "Начал ожидать ответ в " << QTime::currentTime().toString();
    #endif
    if (!serial->waitForReadyRead(5000)) {
        #ifdef DEBUG
        qDebug() << "Не дождался ответа :(";
        #endif
        serial->close();
        return CAN::NoCorrectAdapter;
    }

    #ifdef DEBUG
    qDebug() << "Получил первый ответ в " << QTime::currentTime().toString();
    #endif
    char code;
    int i = 0;
    do {
        serial->waitForReadyRead(150);
        serial->read(&code, 1);
        #ifdef DEBUG
        qDebug() << "Code:" << (int)code;
        #endif
        ++i;
    }
    while (code == 20 && i < 20);

    switch (code) {
    case 10: status = CAN::NoError; break;
    case 20: status = CAN::NoCANConn; break;
    default: status = CAN::NoCorrectAdapter; break;
    }

    if (status != CAN::NoError) {
        serial->close();
    }
    return status;
}

void AdapterConnector::closeConnection() {
    serial->close();
}

int AdapterConnector::getCurrentSettings(QSerialPortInfo &port, qint32 &baudrate) {
    port = QSerialPortInfo(serial->portName());
    baudrate = serial->baudRate();
    return 0;
}

int AdapterConnector::setCurrentSettings(const QSerialPortInfo *port, const qint32 baudrate) {
    serial->setPort(QSerialPortInfo(*port));
    serial->setBaudRate(baudrate);
    return 0;
}
