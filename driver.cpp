#include "driver.h"

#include <QApplication>
#include <QQmlExpression>
#include <QDebug>

Driver::Driver(QObject *parent)
    : QQmlApplicationEngine(parent)
{
}

bool Driver::takeScreenshot(QString path, int window)
{
    if (window < 0 || rootObjects().length() <= window) {
        qWarning() << "window index is out of range";
        return false;
    }

    return qobject_cast<QQuickWindow*>(rootObjects()[window])->grabWindow().save(path);
}

QVariant Driver::evaluate(QString expression, QObject *object)
{
    if (!object) {
        object = rootObjects().first();
    }

    QQmlExpression exp(contextForObject(object), object, expression);
    QVariant result = exp.evaluate();
    if (result == QVariant::Invalid) {
        qWarning() << exp.error();
    }

    return result;
}
