set(QT_USE_IMPORTED_TARGETS TRUE)
find_package(Qt4 4.7.4 REQUIRED QtCore QtGui)
include(${QT_USE_FILE})
find_package(Wt REQUIRED)
include_directories( ${Wt_INCLUDE_DIR} )

set(INPUT_HEADERS playground.hxx subject.hxx category.hxx group.hxx slot.hxx calendar.hxx)
set(INPUT_SOURCES playground.cxx subject.cxx category.cxx group.cxx slot.cxx calendar.cxx)

qt4_wrap_cpp(MOC_SOURCES ${INPUT_HEADERS})

add_library(PlanerCore ${INPUT_SOURCES} ${MOC_SOURCES})
target_link_libraries(PlanerCore ${QT_LIBRARIES} ${Wt_LIBRARY})

add_executable(planer main.cxx)
target_link_libraries(planer ${QT_LIBRARIES} PlanerCore)
