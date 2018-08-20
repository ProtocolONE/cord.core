#include <Core/System/TaskList/TaskManager.h>
#include <Core/System/TaskList/TaskItem.h>

#include <QtCore/QCoreApplication>
#include <gtest/gtest.h>

using namespace P1::Core::System::TaskList;

TEST(TaskListTest, TaskListTestCreation)
{
  TaskManager* manager = new TaskManager();
  manager->setGuid("{F29F85E0-4FF9-1068-AB91-08002B27B3D2}");

  TaskItem item;
  
  int id = manager->addCategory("TestCategory");
  int item1 = manager->addItem(id, item);
  int item2 = manager->addTask(item);

  ASSERT_TRUE(id > 0);
  ASSERT_FALSE(item1 > item2);    

  int errorItem = manager->addItem(65535, item);
  ASSERT_EQ(errorItem, -1);
}
