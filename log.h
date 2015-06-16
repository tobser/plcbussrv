#ifndef LOG_H
#define LOG_H

#include <QDateTime>
#include <QTextStream>
#include <QDebug>

#define TS() QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss.zzz")

#define WARN(msg) QTextStream(stderr) << TS() << " W: " << msg << endl;
#define INFO(msg) QTextStream(stdout) << TS() << " I: " << msg << endl;
#define DEBUG(msg) QTextStream(stdout) << TS() << " D: " << msg << endl;

#endif
