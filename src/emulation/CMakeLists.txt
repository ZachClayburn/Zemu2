set(
        emulation_SRC
        GameBoy.cpp
        Bus.cpp Bus.h
        PPU.cpp PPU.h
        CPU.cpp CPU.h
        Instruction.cpp Instruction.h
        BootRom.cpp BootRom.h
        AbstractRamBank.cpp AbstractRamBank.h
        RamBank.cpp RamBank.h
        RamEcho.cpp RamEcho.h
        BasicRegister.cpp BasicRegister.h
        Pallet.cpp Pallet.h
        LCDCRegister.cpp LCDCRegister.h
        STATRegister.cpp STATRegister.h
        bitUtils.cpp bitUtils.h
        CPURegisters.cpp CPURegisters.h
        Operations/Operation.cpp Operations/Operation.h
        OpTables.cpp OpTables.h
        IBus.cpp IBus.h
        Operations/DirectLoad.cpp Operations/DirectLoad.h
        Operations/LoadToRegister.cpp Operations/LoadToRegister.h
        Operations/NOP.cpp Operations/NOP.h
        Operations/IndirectLoadFromRegisterPair.cpp Operations/IndirectLoadFromRegisterPair.h
        Operations/IndirectLoadToRegisterPair.cpp Operations/IndirectLoadToRegisterPair.h
        Operations/LoadFromRegister.cpp Operations/LoadFromRegister.h
        Operations/IndirectLoadFromParameter.cpp Operations/IndirectLoadFromParameter.h
        Operations/IndirectLoadToParameter.cpp Operations/IndirectLoadToParameter.h
        Operations/IndirectLoadFromPrefixAndCRegister.cpp Operations/IndirectLoadFromPrefixAndCRegister.h
        Operations/IndirectLoadToPrefixAndCRegister.cpp Operations/IndirectLoadToPrefixAndCRegister.h
        Operations/IndirectLoadFromPrefixAndParameter.cpp Operations/IndirectLoadFromPrefixAndParameter.h
        Operations/IndirectLoadToPrefixAndParameter.cpp Operations/IndirectLoadToPrefixAndParameter.h
        Operations/LoadToRegisterPair.cpp Operations/LoadToRegisterPair.h
        Operations/DirectExtendedLoad.cpp Operations/DirectExtendedLoad.h
        Operations/LoadFromRegisterPair.cpp Operations/LoadFromRegisterPair.h
        Operations/IndirectLoadToParameterAndPlusOne.cpp Operations/IndirectLoadToParameterAndPlusOne.h
        Operations/DirectLoadAndAddAsSigned.cpp Operations/DirectLoadAndAddAsSigned.h
        Operations/Push.cpp Operations/Push.h
        Operations/Pop.cpp Operations/Pop.h
        Operations/Increment.cpp Operations/Increment.h
        Operations/Decrement.cpp Operations/Decrement.h
)
add_library(emulation ${emulation_SRC})
add_library(emulation_test ${emulation_SRC} MockBus.cpp MockBus.h)


target_include_directories(
        emulation PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        PRIVATE
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
)

target_include_directories(
        emulation_test PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
)

target_link_libraries(
        emulation PRIVATE
        project_options
        project_warnings
        CONAN_PKG::spdlog
        common
)

target_link_libraries(
        emulation_test PRIVATE
        project_options
        project_warnings
        CONAN_PKG::spdlog
        common
)