#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtWidgets>
#include "connectionsettingswindow.h"
#include "adapterconnector.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

protected:

    ConnectionSettingsWindow *connectionSettingsWindow;
    AdapterConnector *adapterConnector;

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void showConnectionSettingsWindow();
    void openAdapterConnection();
    void closeAdapterConnection();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
