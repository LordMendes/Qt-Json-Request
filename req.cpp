#include "req.h"

req::req(QString adress)
{
    this.adress = adress;
}

void req::post(QJsonObject object, QString rota){
    QNetworkAccessManager man;
    QJsonObject json;
    QNetworkRequest req(QUrl(this.adress+rota));
    req.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    QNetworkReply *reply = man.post(req, QJsonDocument(object).toJson());
    while (!reply->isFinished())
    {
        qApp->processEvents();
    }

    if(!reply->error()){
        qDebug()<<"POST was a sucess!";
    }else{
        qDebug()<< "Error : "<<reply->errorString();
    }
}

QJsonDocument req::get(QString rota){
    QNetworkAccessManager man;
    QJsonObject json;
    QNetworkRequest req(QUrl(this.adress+rota));
    req.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    QNetworkReply *reply = man.get(req);
    while (!reply->isFinished())
    {
        qApp->processEvents();
    }

    QByteArray response_data = reply->readAll();

    QJsonDocument jsonDoc = QJsonDocument::fromJson(response_data);
    json = jsonDoc.object();

    if(!reply->error()){
        qDebug()<<"GET was a sucess!";
    }else{
        qDebug()<< "Error : "<<reply->error();
    }

    return jsonDoc;
}

void req::put(QJsonObject object, QString rota){
    QNetworkAccessManager man;
    QJsonObject json;
    QNetworkRequest req(QUrl(this.adress+rota));
    req.setHeader(QNetworkRequest::ContentTypeHeader, QString("application/json"));

    QNetworkReply *reply = man.put(req, QJsonDocument(object).toJson());
    while (!reply->isFinished())
    {
        qApp->processEvents();
    }

    if(!reply->error()){
        qDebug()<<"PUT was a sucess!";
    }else{
        qDebug()<< "Error : "<<reply->error();
    }
}

