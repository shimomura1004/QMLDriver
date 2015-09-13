#ifndef DRIVER_H
#define DRIVER_H

#include <QObject>
#include <QQmlApplicationEngine>
#include <QQuickWindow>
#include <QQmlContext>

class Driver : public QQmlApplicationEngine
{
    Q_OBJECT

protected:

    template<typename T>
    inline T findElement_(QObject* obj, QString &name, QVariant &value)
    {
        int index = obj->metaObject()->indexOfProperty(name.toLatin1());
        if (index >= 0 && obj->metaObject()->property(index).read(obj) == value && qobject_cast<T>(obj)) {
            return qobject_cast<T>(obj);
        }
        else {
            foreach (auto child, obj->children()) {
                auto result = findElement_<T>(child, name, value);
                if (result && qobject_cast<T>(result)) {
                    return qobject_cast<T>(result);
                }
            }
        }
        return nullptr;
    }

    template<typename T>
    inline T findElementById_(QObject* obj, QString &id)
    {
        if (qobject_cast<QQmlContext*>(obj)) {
            return nullptr;
        }

        QQmlContext *context = contextForObject(obj);
        if (context && context->nameForObject(obj) == id && qobject_cast<T>(obj)) {
            return qobject_cast<T>(obj);
        }
        else {
            foreach (auto child, obj->children()) {
                auto result = findElementById_<T>(child, id);
                if (result) {
                    return result;
                }
            }
        }
        return nullptr;
    }

public:
    explicit Driver(QObject *parent = 0);

    bool takeScreenshot(QString path, int window = 0);
    QVariant evaluate(QString expression, QObject *obj = 0);

    template<typename T = QObject*>
    inline T findElement(QString name, QVariant value) {
        foreach (auto obj, rootObjects()) {
            auto result = findElement_<T>(obj, name, value);
            if (result && qobject_cast<T>(result)) {
                return qobject_cast<T>(result);
            }
        }
        return nullptr;
    }

    template<typename T = QObject*>
    inline T findElementById(QString id) {
        foreach (auto object, rootObjects()) {
            auto result = findElementById_<T>(object, id);
            if (result && qobject_cast<T>(result)) {
                return qobject_cast<T>(result);
            }
        }
        return nullptr;
    }

};

#endif // DRIVER_H
