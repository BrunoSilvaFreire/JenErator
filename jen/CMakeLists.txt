include(${CMAKE_HOME_DIRECTORY}/cmake/Jen.cmake)

set(JEN_ALL include/jen/jen.h include/jen/parsing.h include/jen/cpp/cpp.h src/jen/cpp/cpp.cpp include/jen/cpp/base.h include/jen/cpp/members.h src/jen/cpp/base.cpp src/jen/cpp/members.cpp include/jen/cpp/invocation.h src/jen/parsing.cpp tests/dummy.cpp src/jen/tokenization.cpp)
add_module(jen "${JEN_ALL}")
add_subdirectory(tests)
add_compile_definitions(_GLIBCXX_USE_CXX11_ABI=1

        )