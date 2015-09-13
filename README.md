Usage
-------

``` c++
int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    Driver driver;
    driver.load(QUrl(QStringLiteral("qrc:/main.qml")));

    driver.evaluate("message = 'ok'");
    driver.takeScreenshot("/path/to/file.jpg");

    auto textarea = driver.findElementById<QQuickItem*>("textArea1");
    textarea->setProperty("text", QString("helloworld"));
    qDebug() << textarea->property("text");

    auto button1 = driver.findElementById<QQuickItem*>("button1");
    button1->setProperty("text", QString("PRESS ME 1"));

    return app.exec();
}
```
