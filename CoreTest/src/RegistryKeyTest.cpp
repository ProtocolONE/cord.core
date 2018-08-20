#include <Core/System/Registry/RegistryKey.h>

#include <gtest/gtest.h>

using namespace P1::Core::System::Registry;

TEST(RegistryKeyTest, ReadWriteTestString)
{
  RegistryKey reg(RegistryKey::HKCU, "SOFTWARE\\PONE\\TEST");
  ASSERT_TRUE(reg.isValid());
  QString paramName("RegistryKeyTestParam");
  QString value("RegistryKeyTestValue");
  ASSERT_TRUE(reg.setValue(paramName, value));
  
  RegistryKey reg2(RegistryKey::HKCU, "SOFTWARE\\PONE\\TEST");
  ASSERT_TRUE(reg2.isValid());

  QString value2;
  ASSERT_TRUE(reg2.value(paramName, value2));
  ASSERT_EQ(value, value2);

  QString value3;
  ASSERT_TRUE(reg.value(paramName, value3));
  ASSERT_EQ(value, value3);
}

TEST(RegistryKeyTest, ReadWriteTestDWORD)
{
  RegistryKey reg(RegistryKey::HKCU, "SOFTWARE\\PONE\\TEST");
  ASSERT_TRUE(reg.isValid());
  QString paramName("RegistryKeyTestParamDWORD");
  DWORD value = 0x12345678;
  ASSERT_TRUE(reg.setValue(paramName, value));

  RegistryKey reg2(RegistryKey::HKCU, "SOFTWARE\\PONE\\TEST");
  ASSERT_TRUE(reg2.isValid());

  DWORD value2;
  ASSERT_TRUE(reg2.value(paramName, value2));
  ASSERT_EQ(value, value2);

  DWORD value3;
  ASSERT_TRUE(reg.value(paramName, value3));
  ASSERT_EQ(value, value3);
}