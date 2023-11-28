project(sailmidi CXX)
cmake_minimum_required(VERSION 3.5)

find_package (Qt5 COMPONENTS Core Network Qml Gui Quick REQUIRED)

include(FindPkgConfig)
pkg_search_module(SAILFISH sailfishapp REQUIRED)

set(CMAKE_AUTOMOC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

add_executable(sailmidi src/sailmidi.cpp)
target_compile_definitions(sailmidi PRIVATE
    $<$<OR:$<CONFIG:Debug>,$<CONFIG:RelWithDebInfo>>:QT_QML_DEBUG>
)
target_include_directories(sailmidi PRIVATE
    $<BUILD_INTERFACE:
    ${SAILFISH_INCLUDE_DIRS}
>)
target_link_libraries(sailmidi
    Qt5::Quick
    ${SAILFISH_LDFLAGS}
)

install(TARGETS sailmidi
    RUNTIME DESTINATION bin
)
install(DIRECTORY qml
    DESTINATION share/sailmidi
)
install(DIRECTORY translations
    DESTINATION share/sailmidi
    FILES_MATCHING PATTERN "*.qm"
)
install(FILES sailmidi.desktop
    DESTINATION share/applications
)
install(FILES icons/86x86/sailmidi.png
    DESTINATION share/icons/hicolor/86x86/apps
)
install(FILES icons/108x108/sailmidi.png
    DESTINATION share/icons/hicolor/108x108/apps
)
install(FILES icons/128x128/sailmidi.png
    DESTINATION share/icons/hicolor/128x128/apps
)
install(FILES icons/172x172/sailmidi.png
    DESTINATION share/icons/hicolor/172x172/apps
)

# Get the other files reachable from the project tree in Qt Creator
FILE(GLOB TsFiles "translations/*.ts")
add_custom_target(distfiles
    SOURCES
        sailmidi.desktop
        qml/sailmidi.qml
        qml/cover/CoverPage.qml
        qml/pages/FirstPage.qml
        qml/pages/SecondPage.qml
        rpm/sailmidi.changes.in
        rpm/sailmidi.changes.run.in
        rpm/sailmidi.spec
        rpm/sailmidi.yaml
        ${TsFiles})

# Tell Qt Creator where the application executable(s) would be located on the
# device.
#
# It is not necessary to list other deployables than executables (runtime
# targets) here. The deployment process of Sailfish OS projects is opaque to
# Qt Creator and the information contained in QtCreatorDeployment.txt is only
# used to locate the executable associated with the active run configuration
# on the device in order to run it.
#
# Search the Qt Creator Manual to learn about the QtCreatorDeployment.txt file
# format.
file(WRITE "${CMAKE_BINARY_DIR}/QtCreatorDeployment.txt"
    "${CMAKE_INSTALL_PREFIX}\n${CMAKE_BINARY_DIR}/sailmidi:bin\n")

