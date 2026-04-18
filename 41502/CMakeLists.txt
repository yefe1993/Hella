cmake_minimum_required(VERSION 3.16)

project(41502 VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Core Quick)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Core Quick)

# 2. 配置本地 Google Test（关闭多余选项）
set(gtest_build_samples OFF CACHE BOOL "" FORCE)
set(gtest_build_tests OFF CACHE BOOL "" FORCE)
set(BUILD_GMOCK OFF CACHE BOOL "" FORCE)

# 添加本地 GTest 子项目（请确认路径正确）
add_subdirectory(E:/googletest/googletest-main ${CMAKE_BINARY_DIR}/googletest-build)

# 启用 CMake 测试支持
enable_testing()

set(PROJECT_SOURCES
        main.cpp
        qml.qrc
        listctr.cpp
        listctr.h
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(41502
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
    )
# Define target properties for Android with Qt 6 as:
#    set_property(TARGET 41502 APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation
else()
    if(ANDROID)
        add_library(41502 SHARED
            ${PROJECT_SOURCES}
        )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(41502
          ${PROJECT_SOURCES}
        )
    endif()
endif()

target_link_libraries(41502
  PRIVATE Qt${QT_VERSION_MAJOR}::Core Qt${QT_VERSION_MAJOR}::Quick)

# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
if(${QT_VERSION} VERSION_LESS 6.1.0)
  set(BUNDLE_ID_OPTION MACOSX_BUNDLE_GUI_IDENTIFIER com.example.41502)
endif()
set_target_properties(41502 PROPERTIES
    ${BUNDLE_ID_OPTION}
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

include(GNUInstallDirs)
install(TARGETS 41502
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})


if(QT_VERSION_MAJOR EQUAL 6)
    qt_import_qml_plugins(41502)
    qt_finalize_executable(41502)
endif()

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
include(GoogleTest)
gtest_discover_tests(unit_tests)
