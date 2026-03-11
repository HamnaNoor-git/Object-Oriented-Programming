#include "pch.h"
#include"../25i3113_Lab07/25i3113_Lab07_1.cpp"
#include"../25i3113_Lab07/25i3113_Lab07_2.cpp"
#include"../25i3113_Lab07/25i3113_Lab07_3.cpp"

// Task 1 ParkingSlot

TEST(ParkingSlotTest, DefaultConstructor)
{
    ParkingSlot p;

    EXPECT_EQ(p.getParkingHours(), 0);
}

TEST(ParkingSlotTest, ParameterizedConstructor)
{
    ParkingSlot p(200, "Ali");

    EXPECT_EQ(p.getParkingHours(), 0);
}

TEST(ParkingSlotTest, AddParkingHours)
{
    ParkingSlot p(201, "Ahmed");

    p.addParkingHours(3);

    EXPECT_EQ(p.getParkingHours(), 3);
}

TEST(ParkingSlotTest, MultipleParkingHours)
{
    ParkingSlot p(202, "Sara");

    p.addParkingHours(2);
    p.addParkingHours(5);

    EXPECT_EQ(p.getParkingHours(), 7);
}

TEST(ParkingSlotTest, ParkRemoveVehicle)
{
    ParkingSlot p(203, "Tom");

    p.parkVehicle();
    p.removeVehicle();

    SUCCEED();
}
// Task 2 BankAccount

TEST(BankAccountTest, ConstructorInitialization)
{
    BankAccount acc(1, "Ali", "Savings");

    EXPECT_EQ(acc.getBalance(), 0);
}

TEST(BankAccountTest, DepositMoney)
{
    BankAccount acc(2, "Sara", "Current");

    acc.deposit(500);

    EXPECT_EQ(acc.getBalance(), 500);
}

TEST(BankAccountTest, WithdrawMoney)
{
    BankAccount acc(3, "Ahmed", "Savings");

    acc.deposit(1000);
    acc.withdraw(200);

    EXPECT_EQ(acc.getBalance(), 800);
}

TEST(BankAccountTest, FullWithdraw)
{
    BankAccount acc(4, "John", "Current");

    acc.deposit(400);
    acc.withdraw(400);

    EXPECT_EQ(acc.getBalance(), 0);
}

TEST(BankAccountTest, MultipleTransactions)
{
    BankAccount acc(5, "Emma", "Savings");

    acc.deposit(500);
    acc.deposit(200);
    acc.withdraw(100);

    EXPECT_EQ(acc.getBalance(), 600);
}

// Task 3 Project System

// Test Default Constructor
TEST(ProjectSystemTest, DefaultConstructor)
{
    ProjectSystem p;

    EXPECT_EQ(p.getDeveloperCount(), 0);
    EXPECT_EQ(p.getDeadlineTimer(), 0);
}

// Test Parameterized Constructor
TEST(ProjectSystemTest, ParameterizedConstructor)
{
    ProjectSystem p(101, 5, 30);

    EXPECT_EQ(p.getDeveloperCount(), 5);
    EXPECT_EQ(p.getDeadlineTimer(), 30);
}

// Test Adding Developers
TEST(ProjectSystemTest, AddDevelopers)
{
    ProjectSystem p(101, 5, 30);

    p.addDevelopers(3);

    EXPECT_EQ(p.getDeveloperCount(), 8);
}

// Test Reducing Developers
TEST(ProjectSystemTest, ReduceDevelopers)
{
    ProjectSystem p(101, 10, 30);

    p.reduceDevelopers(4);

    EXPECT_EQ(p.getDeveloperCount(), 6);
}

// Test Requirement Change (Complexity Increase)
TEST(ProjectSystemTest, RequirementChange)
{
    ProjectSystem p(101, 5, 30);

    p.requirementChange(2);

    // No getter for complexity, so just ensure program runs
    EXPECT_EQ(p.getDeveloperCount(), 5);
}

// Test Simulation (Deadline Reduction)
TEST(ProjectSystemTest, SimulateProject)
{
    ProjectSystem p(101, 5, 30);

    p.simulateProject(5);

    EXPECT_EQ(p.getDeadlineTimer(), 25);
}

// Test Copy Constructor (Deep Copy)
TEST(ProjectSystemTest, CopyConstructor)
{
    ProjectSystem p1(101, 5, 30);

    ProjectSystem p2 = p1;

    p1.addDevelopers(5);

    EXPECT_EQ(p1.getDeveloperCount(), 10);
    EXPECT_EQ(p2.getDeveloperCount(), 5); // Should not change if deep copy
}

// Test Optimize Deadline Function
TEST(ProjectSystemTest, OptimizeDeadline)
{
    ProjectSystem p(101, 5, 30);

    optimizeDeadline(p, 20);

    EXPECT_EQ(p.getDeadlineTimer(), 20);
}