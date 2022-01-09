#include "nmsocketwindow.h"

NmSocketWindow::NmSocketWindow(QString socket_name) : QWidget(0)
{
    nmdSocket = new QLocalSocket(this);
    connect(nmdSocket, QOverload<QLocalSocket::LocalSocketError>::of(&QLocalSocket::errorOccurred),
            this, &NmSocketWindow::slotError);
    nmdSocket->setServerName(socket_name);
    connect(nmdSocket, SIGNAL(connected()), SLOT(slotConnected()));
    connect(nmdSocket, SIGNAL(readyRead()), SLOT(slotReadyRead()));
    textCommand = new QTextEdit;
    QFontMetrics metrics(textCommand->font());
    QMargins margins = textCommand->contentsMargins ();
    textCommand->setFixedHeight(1.2*(metrics.lineSpacing()+margins.top()+margins.bottom()+textCommand->document()->documentMargin()));
    textCommand->setFixedWidth(16*metrics.maxWidth());
    textCommand->setLineWrapMode(QTextEdit::NoWrap);
    textCommand->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    textCommand->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    textResult = new QTextEdit;
    textResult->setFixedHeight(24*(metrics.lineSpacing()+margins.top()+margins.bottom()+textCommand->document()->documentMargin()));
    sendCommand = new QPushButton("Send command");
    connect(sendCommand, SIGNAL(clicked()), this, SLOT(slotSendToServer()));

    textResult->setReadOnly(true);
    QVBoxLayout* layout = new QVBoxLayout;
    layout->addWidget(textCommand);
    layout->addWidget(textResult);
    layout->addWidget(sendCommand);
    setLayout(layout);
    nmdSocket->connectToServer();
}

NmSocketWindow::~NmSocketWindow()
{
    nmdSocket->disconnect();
}

void NmSocketWindow::slotReadyRead()
{
    QDataStream in(nmdSocket);
    memset(buf, 0, sizeof(buf));
    textResult->clear();
    for(;;)
    {
        if(nmdSocket->bytesAvailable() < (int)sizeof(char))
            break;

        if(in.readRawData(buf, NM_MAXBUF) > 0)
        {
            textResult->append(QString(buf));
            memset(buf, 0, sizeof(buf));
        }
    }
}

void NmSocketWindow::slotError(QLocalSocket::LocalSocketError error)
{
    QString strError =
        "Error: " + (error == QLocalSocket::ServerNotFoundError ?
                     "The socket is not found." :
                     error == QLocalSocket::PeerClosedError ?
                     "The server has closed the connection." :
                     error == QLocalSocket::ConnectionRefusedError ?
                     "The connection was refused (check socket permissions)." :
                     QString(nmdSocket->errorString()));
    textResult->clear();
    textResult->append(strError);
}

void NmSocketWindow::slotSendToServer()
{
    memset(buf, 0, sizeof(buf));
    const char *ptr = nullptr;
    std::string str_cmd = textCommand->toPlainText().toStdString();
    ptr = str_cmd.c_str();
    strlcpy(buf,ptr,NM_MAXBUF);
    int len = (str_cmd.length()<NM_MAXBUF) ? str_cmd.length() : NM_MAXBUF-1;
    buf[len] = 0;
    nmdSocket->write(buf, len+1);
}

void NmSocketWindow::slotConnected()
{}

