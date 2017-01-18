# nRF52_FM_Shield
MML-based FM Synthesizer sequencer for Nordic nRF52 ported from https://github.com/lipoyang/FM_Shield

## Preparation

Setup Nordic's nRF5x SDK and its related tools. I checked with SDK on Windows10.
Please refer to the official instruction in https://devzone.nordicsemi.com/tutorials/7/

## To build with gcc

First, modify the part of linker related description in Makefile.common at (nRF5x_SDK_Dir)/components/toolchain/gcc like this below to
link C++ generated objects;
(Change "-" line to "+")

    # Link object files
    %.out:
    	@echo Linking target: $@
    -	$(NO_ECHO)$(CC) -Wl,-Map=$(@:.out=.map) $(LDFLAGS) $^ $(LIB_FILES) -lm -o $@
    +	$(NO_ECHO)$(CXX) -Wl,-Map=$(@:.out=.map) $(LDFLAGS) $^ $(LIB_FILES) -lm -o $@
    	-@echo ''
    	$(NO_ECHO)$(SIZE) $@
    	-@echo ''

Next, place the directory nRF52_MMLPlayer under (nRF5x_SDK_Dir)\examples\peripheral\

And just build like other examples in the SDK.




