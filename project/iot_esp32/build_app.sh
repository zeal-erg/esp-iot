# $1 : APP_NAME
# $2 : APP_VERSION
# $3 : APP_ARGVS
# 	all build and flash all bin
#	clean clean
#	none only build bin

#!/bin/bash
if [ -z "$1" ];then
	echo "please input the app name!!!"
	exit 1
else
	APP_BIN_NAME=$1
fi

if [ -z "$2" ];then
	echo "please input the app version(eg. 1.0.0)!!!"
	exit 1
else
	USER_SW_VER=$2
fi	

CHIP_NAME=esp32
PRJ_NAME=iot_$CHIP_NAME
TOP_DIR=$PWD/../..

OUTPUT_PATH=$TOP_DIR/out/$APP_BIN_NAME

if [ "iot_esp32" = $PRJ_NAME ];then
	TOOLCHAIN=xtensa-esp32-elf
else
	TOOLCHAIN=xtensa-lx106-elf
fi

#set xtensa toolchain path
PATH_TMP=$PATH
export PATH=$PATH_TMP:$TOP_DIR/tools/$TOOLCHAIN/bin

# check app path
if [ ! -d $PWD/iot_app/$APP_BIN_NAME ]; then
	echo "please input correct app name!!!"
	exit 1
fi

echo "APP_PATH=/iot_app/$APP_BIN_NAME"
echo "APP_NAME=$APP_BIN_NAME"
echo "APP_VERSION=$USER_SW_VER"

echo ""
echo "start..."
echo ""
set -e

if [ -e "./build/$PRJ_NAME.bin" ]; then
	rm ./build/$PRJ_NAME.bin
fi
if [ -e "./build/$PRJ_NAME.S" ]; then
	rm ./build/$PRJ_NAME.S
fi
if [ -d "./build/iot"  ]; then
	rm -r ./build/iot
fi

make_bin()
{
        make -j4 APP_BIN_NAME=$APP_BIN_NAME USER_SW_VER=$USER_SW_VER $1
        echo ""
        if [ "clean" != "$1" ];then
                if [ ! -d "$OUTPUT_PATH/$USER_SW_VER" ]; then
						echo "arrived"
                        mkdir -p $OUTPUT_PATH/$USER_SW_VER
                fi
        fi
}

if [ "all" = "$3" ]; then
        echo "***build and flash all bin***"
        make_bin
        ./flash_bin.sh all

elif [ "user1" = "$3" ]; then
        echo "***build and flash user1 bin***"
        make_bin 
        ./flash_bin.sh user1

else
        echo "***only build project***"
        make_bin $3
fi

if [ $? -ne 0 ]; then
    echo "build_app.sh failed"
    exit 1
else
    echo "build_app.sh succeed"
fi

echo '      ___           ___                        ___                                               ___                   '
echo '     /  /\         /  /\           ___        /  /\          __                      ___        /  /\          ___     '
echo '    /  /::\       /  /::|         /__/\      /  /::\        |  |\                   /__/\      /  /::\        /__/\    '
echo '   /  /:/\:\     /  /:|:|         \__\:\    /  /:/\:\       |  |:|                  \__\:\    /  /:/\:\       \  \:\   '
echo '  /  /::\ \:\   /  /:/|:|__   ___ /  /::\  /  /:/  \:\      |  |:|                  /  /::\  /  /:/  \:\       \__\:\  '
echo ' /__/:/\:\ \:\ /__/:/ |:| /\ /__/\  /:/\/ /__/:/ \__\:\     |__|:|__             __/  /:/\/ /__/:/ \__\:\      /  /::\ '
echo ' \  \:\ \:\_\/ \__\/  |:|/:/ \  \:\/:/~~  \  \:\ /  /:/     /  /::::\           /__/\/:/~~  \  \:\ /  /:/     /  /:/\:\'
echo '  \  \:\ \:\       |  |:/:/   \  \::/      \  \:\  /:/     /  /:/~~~~           \  \::/      \  \:\  /:/     /  /:/__\/'
echo '   \  \:\_\/       |__|::/     \__\/        \  \:\/:/     /__/:/                 \  \:\       \  \:\/:/     /__/:/     '
echo '    \  \:\         /__/:/                    \  \::/      \__\/                   \__\/        \  \::/      \__\/      '
echo '     \__\/         \__\/                      \__\/                                             \__\/                  '