#include <gtest/gtest.h>

#include <QtCore/QCoreApplication>

#include <Windows.h>

#ifdef CORE_STATIC_LIB
#include <Core/RegisterTypes.h>
#endif 

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

#ifdef CORE_STATIC_LIB
    P1::Core::registerTypes();
#endif

    testing::InitGoogleTest(&argc, argv);
    int r = RUN_ALL_TESTS();
    return r;
}

