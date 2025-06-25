cmake_minimum_required(VERSION 3.31)
project(GamePong)

set(CMAKE_CXX_STANDARD 20)

set(SFML_DIR "C:/SFML-2.6.2/lib/cmake/SFML")
find_package(SFML 2.6 COMPONENTS graphics audio window system REQUIRED)

add_executable(GamePong src/main.cpp
        src/Paddle.cpp
        include/Paddle.h
        src/Ball.cpp
        include/Ball.h
        src/GameManager.cpp
        include/GameManager.h
        include/Utils.h
        src/Texte.cpp
        include/Texte.h
        src/Button.cpp
        include/Button.h
        src/Menu.cpp
        include/Menu.h
        src/GameState.cpp
        include/GameState.h
        src/MultiState.cpp
        include/MultiState.h
        src/NetworkManager.cpp
        include/NetworkManager.h
)

include_directories("C:/SFML-2.6.2/include")

target_link_libraries(GamePong sfml-graphics sfml-window sfml-system sfml-audio)

set_target_properties(GamePong PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")

# Différencier les DLL selon la configuration (Debug/Release)
if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    # DLL nécessaires en mode Debug
    add_custom_command(TARGET GamePong POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy_directory
            "${CMAKE_SOURCE_DIR}/assets"
            "$<TARGET_FILE_DIR:GamePong>/assets"
            COMMAND ${CMAKE_COMMAND} -E copy_if_different
            "C:/SFML-2.6.2/bin/sfml-graphics-d-2.dll"
            "$<TARGET_FILE_DIR:GamePong>"
            COMMAND ${CMAKE_COMMAND} -E copy_if_different
            "C:/SFML-2.6.2/bin/sfml-window-d-2.dll"
            "$<TARGET_FILE_DIR:GamePong>"
            COMMAND ${CMAKE_COMMAND} -E copy_if_different
            "C:/SFML-2.6.2/bin/sfml-system-d-2.dll"
            "$<TARGET_FILE_DIR:GamePong>"
            COMMAND ${CMAKE_COMMAND} -E copy_if_different
            "C:/SFML-2.6.2/bin/sfml-audio-d-2.dll"
            "$<TARGET_FILE_DIR:GamePong>"
            COMMAND ${CMAKE_COMMAND} -E copy_if_different
            "C:/mingw64-13/bin/libstdc++-6.dll"
            "$<TARGET_FILE_DIR:GamePong>"
            COMMAND ${CMAKE_COMMAND} -E copy_if_different
            "C:/mingw64-13/bin/libgcc_s_seh-1.dll"
            "$<TARGET_FILE_DIR:GamePong>"
            COMMAND ${CMAKE_COMMAND} -E copy_if_different
            "C:/mingw64-13/bin/libwinpthread-1.dll"
            "$<TARGET_FILE_DIR:GamePong>"
    )
elseif(CMAKE_BUILD_TYPE STREQUAL "Release")
    # DLL nécessaires en mode Release
    add_custom_command(TARGET GamePong POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy_directory
            "${CMAKE_SOURCE_DIR}/assets"
            "$<TARGET_FILE_DIR:GamePong>/assets"
            COMMAND ${CMAKE_COMMAND} -E copy_if_different
            "C:/SFML-2.6.2/bin/sfml-graphics-2.dll"
            "$<TARGET_FILE_DIR:GamePong>"
            COMMAND ${CMAKE_COMMAND} -E copy_if_different
            "C:/SFML-2.6.2/bin/sfml-window-2.dll"
            "$<TARGET_FILE_DIR:GamePong>"
            COMMAND ${CMAKE_COMMAND} -E copy_if_different
            "C:/SFML-2.6.2/bin/sfml-system-2.dll"
            "$<TARGET_FILE_DIR:GamePong>"
            COMMAND ${CMAKE_COMMAND} -E copy_if_different
            "C:/SFML-2.6.2/bin/sfml-audio-2.dll"
            "$<TARGET_FILE_DIR:GamePong>"
            COMMAND ${CMAKE_COMMAND} -E copy_if_different
            "C:/mingw64-13/bin/libstdc++-6.dll"
            "$<TARGET_FILE_DIR:GamePong>"
            COMMAND ${CMAKE_COMMAND} -E copy_if_different
            "C:/mingw64-13/bin/libgcc_s_seh-1.dll"
            "$<TARGET_FILE_DIR:GamePong>"
            COMMAND ${CMAKE_COMMAND} -E copy_if_different
            "C:/mingw64-13/bin/libwinpthread-1.dll"
            "$<TARGET_FILE_DIR:GamePong>"
    )
endif()
