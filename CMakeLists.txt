cmake_minimum_required(VERSION 3.4)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

option(BUILD_MAIN "Build main" ON)

project(lab04)

# Основное тело для 
if (BUILD_MAIN)
	set(ADDSOURCES ${PROJECT_NAME}Sources)
	set(MAIN_NAME ${PROJECT_NAME}Main)

	add_library(
		${ADDSOURCES}
		STATIC
		${CMAKE_CURRENT_SOURCE_DIR}/sources/BrokerSearcher.cpp
	)
	target_include_directories(
	  ${ADDSOURCES}
	  PUBLIC
	  ${CMAKE_CURRENT_SOURCE_DIR}/include
	)

	add_executable(${CMAKE_PROJECT_NAME}Main ${CMAKE_CURRENT_SOURCE_DIR}/sources/main.cpp)

	target_include_directories(${MAIN_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
	target_link_libraries(${MAIN_NAME} ${ADDSOURCES})
endif()