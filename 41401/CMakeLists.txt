

cmake_minimum_required(VERSION 3.16)

project(41401 VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 1. 查找 Qt5（因为你只用 Qt5）
find_package(Qt5 REQUIRED COMPONENTS Core Quick)

# 2. 配置本地 Google Test（关闭多余选项）
set(gtest_build_samples OFF CACHE BOOL "" FORCE)
set(gtest_build_tests OFF CACHE BOOL "" FORCE)
set(BUILD_GMOCK OFF CACHE BOOL "" FORCE)

# 添加本地 GTest 子项目（请确认路径正确）
add_subdirectory(E:/googletest/googletest-main ${CMAKE_BINARY_DIR}/googletest-build)

# 启用 CMake 测试支持
enable_testing()



# 3. 主应用程序源文件（修正：只写一次 listctr.cpp，头文件不需要列在 add_executable 中）
set(PROJECT_SOURCES
    main.cpp
    qml.qrc
    listctr.cpp
    listctr.h
)

# 创建主可执行文件（Qt5 标准方式）
add_executable(41401 ${PROJECT_SOURCES})

# 链接 Qt5 库
target_link_libraries(41401
    PRIVATE
    Qt5::Core
    Qt5::Quick
)

# 让主程序能找到自定义类的头文件（listctr.h 在当前目录）
target_include_directories(41401 PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

# 可选：macOS/iOS 属性设置（不需要可删除）
if(APPLE)
    set_target_properties(41401 PROPERTIES
        MACOSX_BUNDLE TRUE
        MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
        MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    )
endif()

# 安装规则（可选）
include(GNUInstallDirs)
install(TARGETS 41401
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
)

# ==================== 4. 单元测试部分 ====================

# 注意：GTest 编译出的库名通常是 gtest 和 gtest_main
add_executable(unit_tests
    test_listctr.cpp
    listctr.cpp
)

# 链接 GTest 库和 Qt5::Core（如果 listctr 使用了 QString 等）
target_link_libraries(unit_tests
    PRIVATE
    GTest::gtest
    GTest::gtest_main
    Qt5::Core
)

# 让测试程序能找到 listctr.h
target_include_directories(unit_tests PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

# 让 CMake 自动发现并注册测试用例（需要 GoogleTest 包）
# include(GoogleTest)
# gtest_discover_tests(unit_tests)

# 手动将测试程序注册到 CTest
add_test(NAME unit_tests COMMAND unit_tests)
