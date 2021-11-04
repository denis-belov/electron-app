project("test-cpp")

# global
# include_directories(${CMAKE_JS_INC})

file(GLOB SOURCE_FILES "src/test.cpp")

add_library(${PROJECT_NAME} SHARED ${SOURCE_FILES} ${CMAKE_JS_SRC})

set_target_properties(${PROJECT_NAME} PROPERTIES PREFIX "" SUFFIX ".node")

target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_JS_INC} "${CMAKE_SOURCE_DIR}/node_modules/node-addon-api")

target_link_libraries(${PROJECT_NAME} ${CMAKE_JS_LIB} /home/denis/reps/denis-belov/xgk-test/build/gcc-x64/output/a/xgk-test.a)

add_custom_target(xgk-test WORKING_DIRECTORY /home/denis/reps/denis-belov/xgk-test/src COMMAND cd /home/denis/reps/denis-belov/xgk-test && genmake gcc-x64)
add_custom_target(xgk-math WORKING_DIRECTORY /home/denis/reps/denis-belov/xgk-math/src COMMAND cd /home/denis/reps/denis-belov/xgk-test && genmake gcc-x64)
add_custom_target(xgk-aux WORKING_DIRECTORY /home/denis/reps/denis-belov/xgk-aux/src COMMAND cd /home/denis/reps/denis-belov/xgk-test && genmake gcc-x64)

add_dependencies(${PROJECT_NAME} xgk-test)
add_dependencies(${PROJECT_NAME} xgk-math)
add_dependencies(${PROJECT_NAME} xgk-aux)
