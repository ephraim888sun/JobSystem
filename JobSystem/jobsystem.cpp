#include <iostream>

#include "jobsystem.h"
#include "jobworkerthread.h"

JobSystem *JobSystem::s_jobSystem = nullptr;

typedef void (*JobCallback)(Job *completedJob);

JobSystem::JobSystem()
{
    m_jobHistory.reserve(256 * 1024);
}

JobSystem::~JobSystem()
{
    m_workerThreadsMutex.lock();
    int numWorkerThreads = (int)m_workerThreads.size();

    // First, tell each worker thread to stop picking up jobs

    for (int i = 0; i < numWorkerThreads; i++)
    {
        m_workerThreads[i]->ShutDown();
    }

    while (!m_workerThreads.empty())
    {
        delete m_workerThreads.back();
        m_workerThreads.pop_back();
    }

    m_workerThreadsMutex.unlock();
};

JobSystem *JobSystem::CreateOrGet()
{
    if (!s_jobSystem)
    {
        s_jobSystem = new JobSystem();
    }
    return s_jobSystem;
};

void JobSystem::Destroy()
{
    if (s_jobSystem)
    {
        delete s_jobSystem;
        s_jobSystem = nullptr;
    }
}

void JobSystem::CreateWorkerThread(const char *uniqueName, unsigned long workerJobChannels)
{
    JobWorkerThread *newWorker = new JobWorkerThread(uniqueName, workerJobChannels, this);

    m_workerThreadsMutex.lock();
    m_workerThreads.push_back(newWorker);
    m_workerThreadsMutex.lock();

    m_workerThreads.back()->StartUp();
};