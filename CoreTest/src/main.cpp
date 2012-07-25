
#include <gtest/gtest.h>
#include <QtCore/QCoreApplication>

#ifdef VLD_CHECK_ENABLED
#include <vld.h>
#pragma comment(lib, "vld.lib")
#endif

#include <Windows.h>
#include <BugTrap\BugTrap.h>

void initBugTrap()
{
  BT_SetAppName(TEXT("AutoRunHelperSample"));
  BT_SetAppVersion(TEXT("1.0.0.0"));
  BT_SetSupportEMail(TEXT("support@gamenet.ru"));
  BT_SetSupportURL(TEXT("https://support.gamenet.ru"));
  BT_SetFlags(BTF_DETAILEDMODE | BTF_ATTACHREPORT | BTF_SCREENCAPTURE);
  BT_SetSupportServer(TEXT("fs1.gamenet.ru"), 9999);
  BT_InstallSehFilter();
}

int main(int argc, char *argv[])
{
    initBugTrap();
    QCoreApplication a(argc, argv);
    testing::InitGoogleTest(&argc, argv);
    int r = RUN_ALL_TESTS();
    return r;
}