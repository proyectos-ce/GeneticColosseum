cmake_minimum_required(VERSION 3.5C)
project(GeneticColosseum)

set(CMAKE_CXX_STANDARD 14)


set(SOURCE_FILES main.cpp dna.cpp dna.h gladiator.h gladiator.cpp populationmanager.h populationmanager.cpp entity.h entity.cpp animation.h animation.cpp gladiatorManager.h gladiatorManager.cpp screen.h screens.h menu.h menu.cpp Grid.cpp Grid.h Cell.cpp Cell.h tower.h tower.cpp stats.cpp stats.h http.cpp http.h picojson.h)

set(EXECUTABLE_NAME "GeneticColosseum")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/bin")


#add_definitions(-DRES="Resources/")
add_executable(${PROJECT_NAME} ${SOURCE_FILES})


set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake_modules" ${CMAKE_MODULE_PATH})
find_package(SFML 2 REQUIRED system window graphics network audio)
if(SFML_FOUND)
    include_directories(${SFML_INCLUDE_DIR})
    target_link_libraries(${EXECUTABLE_NAME} ${SFML_LIBRARIES})
endif()
