#include <XBus.hxx>

#include <gtest/gtest.h>

TEST(Knock, One)
{
    XBus::CreateClient("Client", "One");
    XBus::WaitClientInitialized("One");
    ASSERT_TRUE(XBus::IsClientInitialized("One"));

    XBus::Knock("One");
}

TEST(Knock, Speed)
{
    XBus::CreateClient("Client", "Speed");
    XBus::WaitClientInitialized("Speed");

    for(size_t idx = 1; idx < 1000000; ++idx)
    {
        auto res = XBus::Knock("Speed");
        ASSERT_EQ(idx, res.id());
    }
}

int main(int argc, char *argv[])
{

#ifdef XBUS_LITE_PLATFORM_WINDOWS
    XBus::ClientHostFilePath() = L"xbus_client_host\\knock_knock.exe";
    XBus::PythonRuntimeFilePath() = L"E:\\Python\\3.6\\x64\\python36.dll";
    // XBus::PythonRuntimeFilePath() = L"E:\\Python\\3.6\\x32\\python36.dll";
    // XBus::PythonRuntimeFilePath() = L"E:\\Python\\3.4\\x32\\python34.dll";
#else // Not On Windows
    XBus::ClientHostFilePath() = "xbus_client_host/knock_knock";
    XBus::PythonRuntimeFilePath() = "/usr/local/Cellar/python3/3.6.1/Frameworks/Python.framework/Versions/3.6/Python";
#endif // XBUS_LITE_PLATFORM_WINDOWS

    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
