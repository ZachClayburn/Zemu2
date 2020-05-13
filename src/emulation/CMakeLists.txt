add_library(
        emulation
        GameBoy.cpp
        BootRom.cpp
        AbstractRamBank.cpp
        AbstractRamBank.h
        RamBank.cpp
        RamBank.h
        RamEcho.cpp
        RamEcho.h
        PPU.cpp
        PPU.h
        BasicRegister.cpp
        BasicRegister.h
        Pallet.cpp Pallet.h LCDCRegister.cpp LCDCRegister.h STATRegister.cpp STATRegister.h bitUtils.h Bus.cpp Bus.h)

target_include_directories(
        emulation PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
)

target_link_libraries(
        emulation PRIVATE
        project_options
        project_warnings
        CONAN_PKG::spdlog
        common
)