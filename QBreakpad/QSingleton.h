#pragma once

#include <QtGlobal>
#include <QScopedPointer>
#include "QCallOnce.h"

template <class T>
class QSingleton
{
public:
    static T& instance()
    {
        QCallOnce(init, flag);
        return *tptr;
    }

    static void init()
    {
        tptr.reset(new T);
    }

private:
    QSingleton() {}
    ~QSingleton() {}
    Q_DISABLE_COPY(QSingleton)

    static QScopedPointer<T> tptr;
    static QBasicAtomicInt flag;
};

template<class T> QScopedPointer<T> QSingleton<T>::tptr(0);
template<class T> QBasicAtomicInt QSingleton<T>::flag = Q_BASIC_ATOMIC_INITIALIZER(CallOnce::CO_Request);
