#include <Core/System/FileInfo.h>

#include <QtCore/QCoreApplication>
#include <gtest/gtest.h>

TEST(FileVersionTest, getSelfVersion)
{
  QString selfExePath = QCoreApplication::applicationFilePath();
  QString selfVersion = P1::Core::System::FileInfo::version(selfExePath);
  ASSERT_EQ("1.2.3.4", selfVersion);

  int hiVersion = 0;
  int loVersion = 0;
  P1::Core::System::FileInfo::version(selfExePath, hiVersion, loVersion);

  ASSERT_EQ(MAKELONG(2, 1), hiVersion);
  ASSERT_EQ(MAKELONG(4, 3), loVersion);
}
