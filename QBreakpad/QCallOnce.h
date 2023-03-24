#pragma once
#include <QtGlobal>
#include <QAtomicInt>
#include <QMutex>
#include <QWaitCondition>
#include <QThreadStorage>
#include <QThread>

namespace CallOnce
{
    enum ECallOnce
    {
        CO_Request,
        CO_InProgress,
        CO_Finished
    };

    Q_GLOBAL_STATIC(QThreadStorage<QAtomicInt*>, once_flag)
}

template <class Function>
inline static void QCallOnce(Function func, QBasicAtomicInt& flag)
{
    using namespace CallOnce;

#if QT_VERSION < QT_VERSION_CHECK(5, 0, 0)
    int protectFlag = flag.fetchAndStoreAcquire(flag);
#elif QT_VERSION >= QT_VERSION_CHECK(5, 14, 0)
    int protectFlag = flag.fetchAndStoreAcquire(flag.loadRelaxed());
#else
    int protectFlag = flag.fetchAndStoreAcquire(flag.load());
#endif

    if (protectFlag == CO_Finished)
        return;
    if (protectFlag == CO_Request && flag.testAndSetRelaxed(protectFlag,
        CO_InProgress))
    {
        func();
        flag.fetchAndStoreRelease(CO_Finished);
    }
    else
    {
        do
        {
            QThread::yieldCurrentThread();
        } while (!flag.testAndSetAcquire(CO_Finished, CO_Finished));
    }
}

template <class Function>
inline static void QCallOncePerThread(Function func)
{
    using namespace CallOnce;
    if (!once_flag()->hasLocalData())
    {
        once_flag()->setLocalData(new QAtomicInt(CO_Request));
        qCallOnce(func, *once_flag()->localData());
    }
}
