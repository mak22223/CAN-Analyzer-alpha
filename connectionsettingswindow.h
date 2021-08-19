#ifndef CONNECTIONSETTINGSWINDOW_H
#define CONNECTIONSETTINGSWINDOW_H

#include <QDialog>
#include <QMessageBox>
#include "adapterconnector.h"

namespace Ui {
class ConnectionSettingsWindow;
}

class ConnectionSettingsWindow : public QDialog
{
    Q_OBJECT

public:
    explicit ConnectionSettingsWindow(QWidget *parent = nullptr, AdapterConnector *adapterConnector = nullptr);
    ~ConnectionSettingsWindow();

private slots:
    void on_okBtn_clicked();
    void on_cancelBtn_clicked();
    void on_applyBtn_clicked();

private:
    virtual void showEvent(QShowEvent *);
    bool applyNewPortSettings();
    Ui::ConnectionSettingsWindow *ui;
    AdapterConnector *adapterConnector;
};

#endif // CONNECTIONSETTINGSWINDOW_H
