#ifndef NMSOCKETWINDOW_H
#define NMSOCKETWINDOW_H

#include <QWidget>
#include <QVBoxLayout>
#include <QTextEdit>
#include <QPushButton>
#include <QLocalSocket>

//#include "qlocalsocket.h"

class NmSocketWindow : public QWidget
{

Q_OBJECT

private:
    static constexpr int NM_MAXBUF = 8192;
    QLocalSocket* nmdSocket;
    QTextEdit* textCommand;
    QTextEdit* textResult;
    QPushButton* sendCommand;
    char buf[NM_MAXBUF];

public:
    NmSocketWindow(QString);
    ~NmSocketWindow();

private slots:
    void slotReadyRead();
    void slotError(QLocalSocket::LocalSocketError error);
    void slotSendToServer();
    void slotConnected();
};

#endif // NMSOCKETWINDOW_H
