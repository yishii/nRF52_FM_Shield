# nRF52_FM_Shield
MML-based FM Synthesizer sequencer for Nordic nRF52 ported from https://github.com/lipoyang/FM_Shield


* To build with gcc

Modify the part of linker of Makefile.common in <nRF5x_SDK_Dir>/components/toolchain/gcc like this below to
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


Place the directory nRF52_MMLPlayer under <nRF5x_SDK_Dir> examples\peripheral\

And just build like other examples in the SDK.




