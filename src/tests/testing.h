#pragma once

#include <functional>
#include <vector>
#include <string>

namespace test {
    enum class ResultCode {
        kFailed,
        kPass,
    };

    struct Result {
        ResultCode m_code = ResultCode::kPass;
        std::string m_message = "";
    };

    class Test;
    typedef std::function<void(Test*)> TestFunc;

    class Test {
    public:
        Test(const char* name, TestFunc function) : m_name(name), m_function(function) {}

        void execute() {
            m_function(this);
        }

        void pass() {
            m_result.m_code = ResultCode::kPass;
            m_result.m_message = "";
        }

        void fail(const char* message) {
            m_result.m_code = ResultCode::kFailed;
            m_result.m_message = message;
        }

        void snprint(char* dest, size_t max) {
            if (m_result.m_code == ResultCode::kPass) {
                snprintf(dest, max, "%s -- PASS", m_name);
            }
            else {
                snprintf(dest, max, "%s -- FAILED: %s", m_name, m_result.m_message.c_str());
            }
        }

    private:
        TestFunc m_function;
        Result m_result;
        const char* m_name;
    };

    struct TestDescriptor {
        const char* m_name;
        TestFunc m_function;
    };

    class Harness {
    public:
        Harness operator+=(const TestDescriptor& descriptor) {
            m_tests.push_back(Test(descriptor.m_name, descriptor.m_function));
        }

        void operator() {
            for (auto test : m_tests) {
                test.execute();
                char buffer[256];
                test.snprint(buffer, 256);
                printf("%s\n", buffer);
            }
        }

    private:
        std::vector<Test> m_tests;
    };
}