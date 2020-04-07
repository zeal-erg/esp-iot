#
# "main" pseudo-component makefile.
#
# (Uses default behaviour of compiling all source files in directory, adding 'include' to include path.)

# compile Easylogger user

COMPONENT_ADD_INCLUDEDIRS += ./easylogger/inc
COMPONENT_SRCDIRS += ./easylogger/src	\
					./easylogger/port
