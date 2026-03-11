#pragma once
#include <string>
using namespace std;

#pragma once
#include<iostream>
using namespace std;

class ProjectSystem
{
private:
    int projectID;
    int* numberOfDevelopers;
    int* deadlineTimer;
    int* projectComplexity;

public:
    ProjectSystem();
    ProjectSystem(int projectID, int developers, int deadlineTimer);
    ProjectSystem(const ProjectSystem& other);
    void addDevelopers(int count);
    void reduceDevelopers(int count);
    void requirementChange(int increase);
    int getDeveloperCount() const;
    int getDeadlineTimer() const;
    void simulateProject(int days);
    void displayProjectStatus() const;
    ~ProjectSystem();
    friend void optimizeDeadline(ProjectSystem& p, int newTimer);
};

void optimizeDeadline(ProjectSystem& p, int newTimer);