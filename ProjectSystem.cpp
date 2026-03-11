#include<iostream>
#include"25i3113_Lab07_3.h"
using namespace std;


ProjectSystem::ProjectSystem()
{
    projectID = 0;

    numberOfDevelopers = new int(0);
    deadlineTimer = new int(0);
    projectComplexity = new int(1);
}

ProjectSystem::ProjectSystem(int projectID, int developers, int deadlineTimer)
{
    this->projectID = projectID;

    numberOfDevelopers = new int(developers);
    this->deadlineTimer = new int(deadlineTimer);
    projectComplexity = new int(1);
}

ProjectSystem::ProjectSystem(const ProjectSystem& other)
{
    projectID = other.projectID;

    numberOfDevelopers = new int(*other.numberOfDevelopers);
    deadlineTimer = new int(*other.deadlineTimer);
    projectComplexity = new int(*other.projectComplexity);
}

void ProjectSystem::addDevelopers(int count)
{
    *numberOfDevelopers += count;
}

void ProjectSystem::reduceDevelopers(int count)
{
    *numberOfDevelopers -= count;
}

void ProjectSystem::requirementChange(int increase)
{
    *projectComplexity += increase;
}

int ProjectSystem::getDeveloperCount() const
{
    return *numberOfDevelopers;
}

int ProjectSystem::getDeadlineTimer() const
{
    return *deadlineTimer;
}

void ProjectSystem::simulateProject(int days)
{
    *deadlineTimer -= days;

    if (*deadlineTimer < 0)
        *deadlineTimer = 0;
}

void ProjectSystem::displayProjectStatus() const
{
    cout << "Project ID: " << projectID << endl;
    cout << "Developers: " << *numberOfDevelopers << endl;
    cout << "Deadline: " << *deadlineTimer << endl;
    cout << "Complexity: " << *projectComplexity << endl;
}

ProjectSystem::~ProjectSystem()
{
    delete numberOfDevelopers;
    delete deadlineTimer;
    delete projectComplexity;

    cout << "Project system destroyed\n";
}

void optimizeDeadline(ProjectSystem& p, int newTimer)
{
    *p.deadlineTimer = newTimer;
}