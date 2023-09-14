#pragma once
#include <mutex>
#include <map>
#include <vector>
#include <vector>
#include <thread>

class Job
{
    friend class JobSystem;
    friend class JobWorkerThread;

public:
    Job(unsigned long JobChannels = 0xFFFFFFFF, int jobType = -1) : m_jobChannels(JobChannels), m_jobType(jobType)
    {
        static int s_nextJobID = 0;
        m_jobID = s_nextJobID++;
    }

    virtual ~Job() {}

    virtual void Execute() = 0;
    virtual void JobCompleteCallback(){};
    int GetUniqueID() const { return m_jobID; }

private:
    int m_jobID = -1;
    int m_jobType = -1;

    unsigned long m_jobChannels = 0xFFFFFFFF;
};