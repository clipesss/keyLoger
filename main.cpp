#include <QCoreApplication>
#include <iostream>
#include <Windows.h>
#include <QtNetwork/QNetworkAccessManager>
#include <QJsonObject>
#include <QJsonDocument>
#include <QNetworkReply>
using namespace std;

void SendMessageToDiscord(QUrl url,QString message)
{
    QNetworkAccessManager *manager = new QNetworkAccessManager();

    QJsonObject jo;
    jo["content"] = message;

    QJsonDocument jd(jo);
    QByteArray qba = jd.toJson();

    QNetworkRequest request(url);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    QNetworkReply *reply = manager->post(request,qba);

    QObject::connect(reply, &QNetworkReply::finished, [reply]() {
        if (reply->error() == QNetworkReply::NoError) {
            qDebug() << "Сообщение успешно отправлено!";
        } else {
            qDebug() << "Ошибка отправки:" << reply->errorString();
        }
        reply->deleteLater();
    });
}
int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    QUrl url("https://discord.com/api/webhooks/1334728253625204746/xPIsCj5CQsMCMb6Wog5bNbvWW39Xk6gTCH46p1mTP7RZ1gay_q96jBD4iF9mJ5WbD6c8");
    QString message = "hello, discord!";
    cout << "Welcome to btc finding software...\tLoading..." << endl;
    SendMessageToDiscord(url,message);

    return a.exec();
}
