include(${CMAKE_HOME_DIRECTORY}/cmake/Jen.cmake)
set(
        JEN_COMMON
        include/jen/jen.h
        include/jen/parsing.h
        include/jen/utilities/strings.h
)
set(
        JEN_CPP
        include/jen/cpp/base.h
        include/jen/cpp/cpp.h
        include/jen/cpp/invocation.h
        include/jen/cpp/members.h
        include/jen/cpp/preprocessors.h
)
set(
        JEN_DEFINITIONS
        src/jen/jen.cpp
        src/jen/parsing.cpp
        src/jen/tokenization.cpp
        src/jen/cpp/base.cpp
        src/jen/cpp/cpp.cpp
        src/jen/cpp/members.cpp
        src/jen/utilities/strings.cpp
)
set(JEN_HEADERS ${JEN_COMMON} ${JEN_CPP})
set(JEN_ALL ${JEN_HEADERS} ${JEN_DEFINITIONS})
add_module(jen "${JEN_ALL}")
add_subdirectory(tests)
