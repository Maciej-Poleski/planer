set(QT_USE_IMPORTED_TARGETS TRUE)
find_package(Qt4 4.7.4 REQUIRED QtCore QtGui)
include(${QT_USE_FILE})
find_package(Wt REQUIRED)
include_directories( ${Wt_INCLUDE_DIR} ${CMAKE_CURRENT_BINARY_DIR} )

set(INPUT_HEADERS subjectwidget.hxx categorywidget.hxx slotwidget.hxx groupwidget.hxx playground.hxx subject.hxx category.hxx group.hxx slot.hxx calendar.hxx)
set(INPUT_SOURCES subjectwidget.cxx categorywidget.cxx slotwidget.cxx groupwidget.cxx playground.cxx subject.cxx category.cxx group.cxx slot.cxx calendar.cxx)

set(CMAKE_AUTOMOC TRUE)

add_library(PlanerCore ${INPUT_SOURCES})

add_executable(planer main.cxx)
target_link_libraries(planer ${QT_LIBRARIES} ${Wt_LIBRARIES} PlanerCore)
