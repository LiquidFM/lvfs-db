project (lvfs-db)

# Project header
project_library_header_default ()

# 3rdparty
find_package (LiquidDb REQUIRED)
include_directories (${LIQUIDDB_INCLUDE})

find_package (Lvfs-Core REQUIRED)
include_directories (${LVFS_CORE_INCLUDE})

list (APPEND ${PROJECT_NAME}_LIBS ${EFC_LIB})
list (APPEND ${PROJECT_NAME}_LIBS ${LVFS_LIB})
list (APPEND ${PROJECT_NAME}_LIBS ${LIQUIDDB_LIB})
list (APPEND ${PROJECT_NAME}_LIBS ${QT_LIBRARIES})
list (APPEND ${PROJECT_NAME}_LIBS ${LVFS_CORE_LIB})

# Sources
add_subdirectory (src)
QT4_WRAP_CPP (${PROJECT_NAME}_MOC_SOURCES ${${PROJECT_NAME}_HEADERS} OPTIONS "-nw")
list (APPEND ${PROJECT_NAME}_SOURCES ${${PROJECT_NAME}_MOC_SOURCES})

# Target - lvfs-db
add_library (lvfs-db SHARED ${${PROJECT_NAME}_SOURCES})
target_link_libraries (lvfs-db ${${PROJECT_NAME}_LIBS})

# Documentation
add_documentation ("LVFS-DB" 0.0.1 "LVFS Plugin for database of files")

# Install rules
install_header_files (lvfs-db "src/lvfs_db_IStorage.h:IStorage")
install_target (lvfs-db)
