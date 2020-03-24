#include "req.h"
/*!
* Lib to perform Json's APIs consumption (GET, PUT and POST)
*
* @Author Lucas C. Mendes
*/

/*!
* Constructor gets the adress of the API
* @param QString
*/
req::req(QString adress)
{
    this.adress = adress;
}
/*!
* perform a POST request to the API server in the desired route
*@param QJsonObject , the posted object
*@param QString , the route
*/
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
/*!
* Returns a QJsonDocument with the JSON of the inserted route
* @param QString, the route
* @return QJsonDocument, the Json document of the inserted route
*/
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
/*!
* Perform a PUT request in the JSON of the desired route
* @param QJsonObject, the new object with the alterations
* @param Qstring, the route
*/
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

