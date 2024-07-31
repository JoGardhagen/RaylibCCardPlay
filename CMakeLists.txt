cmake_minimum_required(VERSION 3.10)

# Projektets namn
project(card_game)

# Ange C-standarden
set(CMAKE_C_STANDARD 99)

# Inkludera katalog för header-filer
include_directories(${PROJECT_SOURCE_DIR}/include)

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

# Länk bibliotek (om du använder externa bibliotek, till exempel Raylib)
# target_link_libraries(card_game raylib m pthread) # Avkommentera och justera om Raylib eller andra bibliotek används
