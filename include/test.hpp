#ifndef TEST_HPP
#define TEST_HPP

#include <cassert>
#include <functional>
#include <iostream>
#include <memory>

#include "Logger.hpp"
#include "LoggingLevel.hpp"

class Test {
  public:
    Test(std::string name, std::function<void()> testFunction)
        : name(std::move(name)), testFunction(std::move(testFunction)), logger(new Logger(LoggingLevel::TESTING, "testing.txt", false, true)) {}
    ~Test() = default;

    // Disable
    Test(const Test &&o) noexcept : name(std::move(o.name)), testFunction(std::move(o.testFunction)) {}  // Move constructor
    Test(const Test &o) : name(std::move(o.name)), testFunction(std::move(o.testFunction)) {}            // Copy constructor
    Test &operator=(Test &&) = delete;                                                                   // Move assignment operator
    Test &operator=(Test &) = delete;                                                                    // Copy assignment operator

    void run() const;
    [[nodiscard]] std::string getName() const { return name; }

  private:
    std::string name;
    std::function<void()> testFunction;
    std::unique_ptr<Logger> logger;
};

class TestCase {
  public:
    TestCase(std::string expected, std::string output)
        : expected(std::move(expected)), output(std::move(output)), logger(new Logger(LoggingLevel::TESTING, "test.txt", false, true)) {}
    ~TestCase() = default;

    // Disable
    TestCase(const TestCase &&) = delete;       // Move constructor
    TestCase(const TestCase &) = delete;        // Copy constructor
    TestCase &operator=(TestCase &&) = delete;  // Move assignment operator
    TestCase &operator=(TestCase &) = delete;   // Copy assignment operator

    void run() const {
        if (expected != output) {
            const std::string logText = "Expected: " + expected +
                                        "\nOutput: " + output;
            this->logger->log(logText);
            assert(expected == output);
        }
    }

  private:
    std::string expected;
    std::string output;
    std::unique_ptr<Logger> logger;
};

class Tester {
  public:
    // Default constructor
    Tester() : logger(new Logger(LoggingLevel::TESTING, "testing.txt", false, true)) {}
    ~Tester();

    // Disable
    Tester(const Tester &&) = delete;       // Move constructor
    Tester(const Tester &) = delete;        // Copy constructor
    Tester &operator=(Tester &&) = delete;  // Move assignment operator
    Tester &operator=(Tester &) = delete;   // Copy assignment operator

    void addTest(const std::string &name, std::function<void()> testFunction);
    void addTestCase(const std::string &expected, const std::string &output);

  private:
    std::vector<Test> tests;
    std::vector<TestCase> testCases;
    std::unique_ptr<Logger> logger;
};

#endif  // TEST_HPP