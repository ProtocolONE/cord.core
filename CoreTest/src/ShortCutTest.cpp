#include <Core/System/Shell/ShortCut.h>

#include <QtCore/QString>
#include <QtCore/QFile>
#include <QtCore/QCoreApplication>

#include <gtest/gtest.h>
#include <windows.h>

#define ARGS QString::fromUtf16(L"arg1 arg2 arg3 русский")
#define DESCRIPTION QString::fromUtf16(L"the description на русском")
#define WORKINGDIR QString::fromUtf16(L"x:\\mega pa th\\с русскими\\буквами")
#define PATH QString::fromUtf16(L"c:\\русский\\megafile.xpp")

TEST(ShortCutTest, SaveLoad)
{
  QString appPath = QCoreApplication::applicationDirPath();
  QString lnkPath = appPath + "/file.lnk";
  
  QFile::remove(lnkPath);
 
  GGS::Core::System::Shell::ShortCut object;
  
  object.setArguments(ARGS);
  object.setDescription(DESCRIPTION);
  object.setShowCmd(GGS::Core::System::Shell::ShortCut::MinNoActive);
  object.setWorkingDirectory(WORKINGDIR);
  object.setPath(PATH);
  object.setIconLocation(appPath + "/fixtures/system/shell/icon.ico");
  object.setIconIndex(2);
  ASSERT_TRUE(object.save(lnkPath));

  GGS::Core::System::Shell::ShortCut secondObject;
  ASSERT_TRUE(secondObject.load(lnkPath));
  EXPECT_EQ(object.arguments(), secondObject.arguments());
  EXPECT_EQ(object.description(), secondObject.description());
  EXPECT_EQ(object.showCmd(), secondObject.showCmd());
  EXPECT_EQ(object.workingDirectory().toLower(), secondObject.workingDirectory().toLower());
  EXPECT_EQ(object.path().toLower(), secondObject.path().toLower());
  EXPECT_EQ(object.iconLocation().toLower(), secondObject.iconLocation().toLower());
  EXPECT_EQ(object.iconIndex(), secondObject.iconIndex());
}