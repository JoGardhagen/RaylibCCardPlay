cmake_minimum_required(VERSION 3.10)

# Projektets namn
project(card_game)

# Ange C-standarden
set(CMAKE_C_STANDARD 99)

# Inkludera kataloger för header-filer
include_directories(${PROJECT_SOURCE_DIR}/include)
include_directories(/opt/homebrew/Cellar/raylib/5.0/include)

# Lägg till källfiler
set(SOURCES
    src/main.c
    src/deck.c
    src/card.c
    src/card_pile.c
    src/gameplay.c
)

# Skapa exekverbar fil
add_executable(card_game ${SOURCES})

# Länk bibliotek
# Leta efter Raylib-biblioteket i den angivna sökvägen
find_library(RAYLIB_LIBRARY NAMES raylib PATHS /opt/homebrew/Cellar/raylib/5.0/lib NO_DEFAULT_PATH)

# Om biblioteket hittades, länka mot det
if (RAYLIB_LIBRARY)
    target_link_libraries(card_game ${RAYLIB_LIBRARY})
else()
    message(FATAL_ERROR "Raylib library not found!")
endif()

# Om du använder andra bibliotek (som pthread), lägg till dem här
# target_link_libraries(card_game pthread)
