#include "connectionsettingswindow.h"
#include "ui_connectionsettingswindow.h"

ConnectionSettingsWindow::ConnectionSettingsWindow(QWidget *parent, AdapterConnector *adapterConnector) :
    QDialog(parent),
    ui(new Ui::ConnectionSettingsWindow)
{
    this->adapterConnector = adapterConnector;

    ui->setupUi(this);
}

ConnectionSettingsWindow::~ConnectionSettingsWindow()
{
    delete ui;
}

void ConnectionSettingsWindow::showEvent(QShowEvent *e) {
//  нужно загружать текущие значения, установленнные в adapterConnector
//  есть возможность выбрать не актуальный порт, если отключить устройство после открытия окна
    QList<QSerialPortInfo> availablePorts = QSerialPortInfo::availablePorts();
    QList<qint32> baudrates = QSerialPortInfo::standardBaudRates();

    ui->COMPortComboBox->clear();
    ui->baudrateComboBox->clear();

    if (availablePorts.size() == 0) {
        QMessageBox::warning(this, "Предупреждение", "Не удалось обнаружить доступные COM-порты.");
    }

    for (int i = 0; i < availablePorts.size(); ++i) {
        ui->COMPortComboBox->addItem(availablePorts[i].portName(), availablePorts[i].portName());
    }
    for (int i = 0; i < baudrates.size(); ++i) {
        ui->baudrateComboBox->addItem(QString::number(baudrates[i]) + " бод", baudrates[i]);
    }

    QSerialPortInfo port;
    qint32 baudrate;
    adapterConnector->getCurrentSettings(port, baudrate);
    ui->COMPortComboBox->setCurrentText(port.portName());
    ui->baudrateComboBox->setCurrentText(QString::number(baudrate) + " бод");
}

bool ConnectionSettingsWindow::applyNewPortSettings() {
    QSerialPortInfo *newPort = new QSerialPortInfo(ui->COMPortComboBox->currentData().toString());
    qint32 baudrate = ui->baudrateComboBox->currentData().toInt();
    if (!newPort->isNull() && baudrate) {
        adapterConnector->setCurrentSettings(newPort, baudrate);
        delete newPort;
        return true;
    }
    QMessageBox::warning(this, "Предупреждение", "Не удалось установить новые параметры соединения.");
    delete newPort;
    return false;
}

void ConnectionSettingsWindow::on_okBtn_clicked() {
    if (applyNewPortSettings()) {
        this->close();
    }
}

void ConnectionSettingsWindow::on_cancelBtn_clicked() {
    this->close();
}

void ConnectionSettingsWindow::on_applyBtn_clicked() {
    applyNewPortSettings();
}
