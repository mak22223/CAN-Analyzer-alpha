#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    adapterConnector = new AdapterConnector(this);

    ui->setupUi(this);

    connectionSettingsWindow = new ConnectionSettingsWindow(this, adapterConnector);

    // connecting menuBar buttons
    connect(ui->menuBarConnectionPropertiesButton, SIGNAL(triggered()), this, SLOT(showConnectionSettingsWindow()));
    connect(ui->menuBarExitButton, SIGNAL(triggered()), this, SLOT(close()));
    connect(ui->menuBarConnectButton, SIGNAL(triggered()), this, SLOT(openAdapterConnection()));
    connect(ui->menuBarDisconnectButton, SIGNAL(triggered()), this, SLOT(closeAdapterConnection()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::showConnectionSettingsWindow() {
    connectionSettingsWindow->show();
}

void MainWindow::openAdapterConnection() {
    ui->menuBarConnectButton->setEnabled(false);
    int status = adapterConnector->openConnection();
    if (status != CAN::NoError) {
        QString errorMsg;
        switch (status) {
        case CAN::NoAdapterConn : errorMsg = "Не удалось установить соединение с адаптером."; break;
        case CAN::NoCANConn : errorMsg = "Не удалось установить соединение с CAN-шиной."; break;
        case CAN::NoCorrectAdapter : errorMsg = "Не удалось распознать адаптер, подключенный к заданному порту."; break;
        }
        QMainWindow::statusBar()->showMessage("Ошибка соединения.", 5000);
        QMessageBox::warning(this, "Ошибка", errorMsg);
        ui->menuBarConnectButton->setEnabled(true);
    } else {
        QMainWindow::statusBar()->showMessage("Соединение успешно установлено.", 5000);
        ui->menuBarDisconnectButton->setEnabled(true);
    }
}

void MainWindow::closeAdapterConnection() {
    ui->menuBarDisconnectButton->setEnabled(false);
    adapterConnector->closeConnection();

    QMainWindow::statusBar()->showMessage("Соединение успешно закрыто.", 5000);
    ui->menuBarConnectButton->setEnabled(true);
}
