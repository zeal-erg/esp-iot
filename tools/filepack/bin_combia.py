
import sys

COMBIA_BIN_OFFSET = 0x00
COMBIA_BIN_BOOTLOADER = 0x1000
COMBIA_BIN_PARTITION_SINGLEAPP_BIN = 0x8000
COMBIA_BIN_USER_APP = 0x10000

OFF_SET=0
outputbin = open(sys.argv[4],'wb')

get = open(sys.argv[1],'rb')
getread = get.read()
outputbin.write(b'\xff' * (COMBIA_BIN_BOOTLOADER))
outputbin.write(getread)
OFF_SET += len(getread)
get.close()

get = open(sys.argv[2],'rb')
getread = get.read()
outputbin.write(b'\xff' * (COMBIA_BIN_PARTITION_SINGLEAPP_BIN - OFF_SET))
outputbin.write(getread)
OFF_SET += len(getread)
get.close()

get = open(sys.argv[3],'rb')
getread = get.read()
outputbin.write(b'\xff' * (COMBIA_BIN_USER_APP - OFF_SET))
outputbin.write(getread)
OFF_SET += len(getread)
get.close()

print("****** iot_esp32 package success ******")
