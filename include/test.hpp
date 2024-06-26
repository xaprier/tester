#ifndef TEST_HPP
#define TEST_HPP

#include <cassert>
#include <functional>
#include <memory>

#include "Logger.hpp"
#include "LoggingLevel.hpp"

class Test {
  public:
    Test(std::string name, std::function<void()> testFunction)
        : name(std::move(name)), testFunction(std::move(testFunction)), logger(std::make_shared<Logger>(LoggingLevel::TESTING, "testing.txt", false, true)) {}
    ~Test() = default;

    Test(const Test &&o) noexcept : name(std::move(o.name)), testFunction(std::move(o.testFunction)), logger(std::move(o.logger)) {}  // Move constructor
    Test(const Test &o) : name(o.name), testFunction(o.testFunction), logger(o.logger) {}                                             // Copy constructor
    Test &operator=(Test &&o) noexcept {
        if (this != &o) {
            name = std::move(o.name);
            testFunction = std::move(o.testFunction);
            logger = std::move(o.logger);
        }
        return *this;
    }
    Test &operator=(const Test &o) {
        if (this != &o) {
            name = o.name;
            testFunction = o.testFunction;
            logger = o.logger;
        }
        return *this;
    }

    void run() const;
    [[nodiscard]] std::string getName() const { return name; }

  private:
    std::string name;
    std::function<void()> testFunction;
    std::shared_ptr<Logger> logger;
};

class TestCase {
  public:
    TestCase(std::string expected, std::string output)
        : expected(std::move(expected)), output(std::move(output)), logger(std::make_shared<Logger>(LoggingLevel::TESTING, "test.txt", false, true)) {}
    ~TestCase() = default;

    TestCase(const TestCase &&o) noexcept : expected(std::move(o.expected)), output(std::move(o.output)), logger(std::move(o.logger)) {}  // Move constructor
    TestCase(const TestCase &o) : expected(o.expected), output(o.output), logger(o.logger) {}                                             // Copy constructor
    TestCase &operator=(TestCase &&o) noexcept {
        if (this != &o) {
            expected = std::move(o.expected);
            output = std::move(o.output);
            logger = std::move(o.logger);
        }
        return *this;
    }
    TestCase &operator=(const TestCase &o) {
        if (this != &o) {
            expected = o.expected;
            output = o.output;
            logger = o.logger;
        }
        return *this;
    }

    void run() const;

  private:
    std::string expected;
    std::string output;
    std::shared_ptr<Logger> logger;
};

class Tester {
  public:
    // Default constructor
    Tester() : logger(std::make_shared<Logger>(LoggingLevel::TESTING, "testing.txt", false, true)) {}
    ~Tester();

    Tester(const Tester &&o) noexcept : tests(std::move(o.tests)), testCases(std::move(o.testCases)), logger(std::move(o.logger)) {}  // Move constructor
    Tester(const Tester &o) : tests(o.tests), testCases(o.testCases), logger(o.logger) {}                                             // Copy constructor
    Tester &operator=(Tester &&o) noexcept {
        if (this != &o) {
            tests = std::move(o.tests);
            testCases = std::move(o.testCases);
            logger = std::move(o.logger);
        }
        return *this;
    }
    Tester &operator=(const Tester &o) {
        if (this != &o) {
            tests = o.tests;
            testCases = o.testCases;
            logger = o.logger;
        }
        return *this;
    }

    void addTest(const std::string &name, std::function<void()> testFunction);
    void addTestCase(const std::string &expected, const std::string &output);

  private:
    std::vector<Test> tests;
    std::vector<TestCase> testCases;
    std::shared_ptr<Logger> logger;
};

#endif  // TEST_HPP