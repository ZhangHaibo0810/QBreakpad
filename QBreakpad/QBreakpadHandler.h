#pragma once

#include "QBreakpadDllExport.h"

#include <QString>
#include <QUrl>
#include "QSingleton.h"

namespace google_breakpad
{
    class ExceptionHandler;
    class MinidumpDescriptor;
}

class QBreakpadHandlerPrivate;

class QBREAKPAD_EXPORT QBreakpadHandler : public QObject
{
    Q_OBJECT
public:
    static QString version();

    QBreakpadHandler();
    ~QBreakpadHandler();

    QString uploadUrl() const;
    QString dumpPath() const;
    QStringList dumpFileList() const;

    void setDumpPath(const QString& path);
    void setUploadUrl(const QUrl& url);

public slots:
    void sendDumps();

private:
    QBreakpadHandlerPrivate* d;
};
#define QBreakpadInstance QSingleton<QBreakpadHandler>::instance()
