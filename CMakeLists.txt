project (lvfs-db)

# Project header
project_cxx_library_header_default ()

# 3rdparty
list (APPEND ${PROJECT_NAME}_LIBS brolly)
list (APPEND ${PROJECT_NAME}_LIBS efc)
list (APPEND ${PROJECT_NAME}_LIBS lvfs)
list (APPEND ${PROJECT_NAME}_LIBS liquiddb)

# Sources
add_subdirectory (src)

# Target - lvfs-db
add_library(lvfs-db SHARED ${${PROJECT_NAME}_SOURCES})
target_link_libraries (lvfs-db ${${PROJECT_NAME}_LIBS})

# Version
build_version_file (lvfs-db 0.0.1)

# Documentation
add_documentation ("LVFS-DB" 0.0.1 "LVFS Plugin for database of files")

# Install rules
install_header_files (lvfs-db "src/lvfs_db_IStorage.h:IStorage")
install_target (lvfs-db)
