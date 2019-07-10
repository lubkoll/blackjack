project(blackjack)
cmake_minimum_required(VERSION 3.8)

find_package(Threads REQUIRED)

add_library(blackjack_lib
    include/blackjack/BettingStrategy.cpp
    include/blackjack/Card.cpp
    include/blackjack/CompareStandingWithDrawing.cpp
    include/blackjack/ComputeProbability.cpp
    include/blackjack/Decision.cpp
    include/blackjack/Draw.cpp
    include/blackjack/Expectation.cpp
    include/blackjack/Game.cpp
    include/blackjack/Player.cpp
    include/blackjack/PointCount.cpp
    include/blackjack/Strategy.cpp
    include/blackjack/ZenCount.cpp
)
target_link_libraries(blackjack_lib PRIVATE Threads::Threads)
target_include_directories(blackjack_lib PUBLIC
    $<INSTALL_INTERFACE:include>
    $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
)
target_compile_features(blackjack_lib PUBLIC cxx_std_14)

add_executable(${PROJECT_NAME} include/blackjack/main.cpp)
target_link_libraries(${PROJECT_NAME} blackjack_lib)


option(BuildTests "build tests" ON)
if(BuildTests)
    find_package(GTest REQUIRED)
    aux_source_directory(test TST_LIST)
    add_executable(tests ${TST_LIST})
    target_link_libraries(tests blackjack_lib GTest::GTest GTest::Main Threads::Threads)
endif()
