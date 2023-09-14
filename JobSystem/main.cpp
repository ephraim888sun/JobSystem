#include <iostream>
#include <string>

#include "jobsystem.h"
#include "renderjob.h"
#include "compilejob.h"

int main(void)
{
    std::cout << "Creating Job System" << std::endl;

    JobSystem *js = JobSystem::CreateOrGet();

    return 0;
}