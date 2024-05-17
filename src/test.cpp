#include "test.hpp"

#include <exception>
#include <string>

void Test::run() const {
    logger->log("Running test for: " + name);
    testFunction();
}

void TestCase::run() const {
    if (expected != output) {
        const std::string logText = "Expected: \"" + expected +
                                    "\", Output: \"" + output + "\"";
        this->logger->log(logText);
        assert(expected == output);
    }
}

void Tester::addTest(const std::string& name, std::function<void()> testFunction) {
    tests.emplace_back(name, testFunction);
}

void Tester::addTestCase(const std::string& expected, const std::string& output) {
    testCases.emplace_back(expected, output);
}

Tester::~Tester() {
    if (!tests.empty()) {
        logger->log("Running tests");
        for (const auto& test : tests) {
            try {
                test.run();
                logger->log("Test \"" + test.getName() + "\" is successful\n");
            } catch (const std::exception& e) {
                logger->log("Test \"" + test.getName() + "\" failed: " + e.what() + "\n");
            }
        }
    }

    if (!testCases.empty()) {
        logger->log("Running test cases");
        for (std::size_t c = 0; c < testCases.size(); c++) {
            testCases.at(c).run();
            logger->log("Test case " + std::to_string(c + 1) + " is successful");
        }
    }
}
