project(blackjack)
cmake_minimum_required(VERSION 3.8)

add_library(blackjack_lib
    BettingStrategy.cpp
    Card.cpp
    ComputeProbability.cpp
    Player.cpp
    Strategy.cpp
)
target_include_directories(blackjack_lib PUBLIC ${PROJECT_SOURCE_DIR})
target_compile_features(blackjack_lib PUBLIC cxx_std_14)

add_executable(${PROJECT_NAME} main.cpp)
target_link_libraries(${PROJECT_NAME} blackjack_lib)


option(BuildTests "build tests" ON)
if(BuildTests)
    find_package(GTest REQUIRED)
    aux_source_directory(test TST_LIST)
    add_executable(tests ${TST_LIST})
    target_link_libraries(tests blackjack_lib GTest::GTest GTest::Main Threads::Threads)
endif()
