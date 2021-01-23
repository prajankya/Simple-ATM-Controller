

set(CPP_SOURCE
  supporting_classes/Transaction.cpp
  supporting_classes/AccountType.cpp
  supporting_classes/Account.cpp)

add_library(my_lib ${CPP_SOURCE})


add_executable(${PROJECT_NAME} main.cpp)

target_link_libraries(${PROJECT_NAME}
  PRIVATE
    my_lib)

if(PACKAGE_TESTS)
  enable_testing()

  add_subdirectory(tests)
endif(PACKAGE_TESTS)
