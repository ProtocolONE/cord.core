#include <Core/System/HardwareId.h>

#include <gtest/gtest.h>

TEST(HardwareIdTest, getValue)
{
  QString hwid1 = P1::Core::System::HardwareId::value();
  QString hwid2 = P1::Core::System::HardwareId::value();
  ASSERT_FALSE(hwid1.isEmpty());
  ASSERT_FALSE(hwid2.isEmpty());
  ASSERT_EQ(hwid1, hwid2);
}
