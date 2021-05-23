# Добавьте сюда исполняемые файлы с примерами работы со структурой данных
add_executable(example example.cpp)
target_link_libraries(example PRIVATE project_paths project_warnings ${PROJECT_NAME})