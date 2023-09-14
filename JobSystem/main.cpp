#include <iostream>
#include <string>

#include "jobsystem.h"
#include "renderjob.h"
#include "compilejob.h"

int main(void)
{
    std::cout << "Creating Job System" << std::endl;

    JobSystem *js = JobSystem::CreateOrGet();

    std::cout << "Creating Worker Threads" << std::endl;

    js->CreateWorkerThread("Thread1", 0xFFFFFFFF);
    js->CreateWorkerThread("Thread2", 0xFFFFFFFF);
    js->CreateWorkerThread("Thread3", 0xFFFFFFFF);
    js->CreateWorkerThread("Thread4", 0xFFFFFFFF);
    js->CreateWorkerThread("Thread5", 0xFFFFFFFF);
    js->CreateWorkerThread("Thread6", 0xFFFFFFFF);
    js->CreateWorkerThread("Thread7", 0xFFFFFFFF);
    js->CreateWorkerThread("Thread8", 0xFFFFFFFF);
    js->CreateWorkerThread("Thread9", 0xFFFFFFFF);

    std::cout << "Creating Jobs" << std::endl;

    std::vector<Job *> jobs;

    CompileJob *cjb = new CompileJob(0XFFFFFFFF, 1);
    jobs.push_back(cjb);

    for (int j = 0; j < 10; j++)
    {
        RenderJob *rjb = new RenderJob(0xFFFFFFFF, 1);
        for (int i = 0; i < 1000; i++)
        {
            rjb->data.push_back(i + j);
        }
    }

    return 0;
}