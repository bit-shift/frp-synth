#pragma once

#include <chrono>
#include <thread>

#include <QObject>

class AudioEngine : public QObject
{
    Q_OBJECT
public:
    explicit AudioEngine(QObject* root, QObject *parent = 0);
    ~AudioEngine();

signals:

public slots:
    void start();
    void stop();

    void startStop();


private:
    std::unique_ptr<std::thread> m_thread = nullptr;
    QObject* m_root;

    bool m_running = false;
};

