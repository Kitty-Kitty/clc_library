#! /bin/bash

shell_path=$(cd `dirname $0`; pwd)
application_file_name="vdu_simple_demo";
application_bin_path="${shell_path}/bin"
application_library_path="${shell_path}/lib/arm-hisiv400";
application_source_files="${shell_path}/src/files";
#application_platform_file="${shell_path}/tools/arm-hisiv400/sample_hifb_1080p";
application_platform_file="${shell_path}/tools/arm-hisiv400/sample_hifb_4k";


if [ -z $1 ]; then
    echo "usage: sh start.sh [platform | demo]"
    echo "first: "
    echo "     1: sh start.sh platform"
    echo "     2: select 4"
    echo "second: "
    echo "     1: sh start.sh demo"
    exit 0;
fi

case $1 in 
    "platform" )
        #run_platform;
        export LD_LIBRARY_PATH=${application_library_path}:${LD_LIBRARY_PATH}
        chmod +x ${application_platform_file};
        ${application_platform_file};
    ;;
    "demo" )
        #run_demo;
        #check app 
        if [ ! -f ${application_bin_path}/${application_file_name} ]; then
            echo "not found [${application_bin_path}/${application_file_name}] error."
            echo "make it before..."
            exit 0;
        fi

        if [ ! -d ${application_source_files} ]; then
            echo "lost path [ ${application_source_files} ] error";
            exit 0;
        else
            cp -rf ${application_source_files} ${application_bin_path};
        fi

        export LD_LIBRARY_PATH=${application_library_path}:${LD_LIBRARY_PATH}
        export QT_QPA_PLATFORM_PLUGIN_PATH="${application_library_path}/plugins"
        #export QT_QPA_PLATFORM=linuxfb:fb=/dev/fb0:size=800x600:mmSize=800x600:offset=0x0
        #export QT_QPA_PLATFORM=linuxfb:fb=/dev/fb0:size=1920x1080:mmSize=1920x1080:offset=0x0
        #export QT_QPA_PLATFORM=linuxfb:fb=/dev/fb0:size=3840x2160:mmSize=3840x2160:offset=0x0
        export QT_QPA_PLATFORM=linuxfb:tty=/dev/fb0
	export QT_QPA_PLATFORM=eglfs
	export QT_QPA_EGLFS_PHYSICAL_WIDTH=3840
	export QT_QPA_EGLFS_PHYSICAL_HEIGHT=2160
	#export XDG_RUNTIME_DIR=${shell_path}
	export XDG_RUNTIME_DIR=/tmp/runtime-root
	
	export LD_PRELOAD=${application_library_path}/preloadable_libiconv.so

        cd ${application_bin_path}
        chmod +x ${application_file_name}
        ./${application_file_name}
    ;;
    * )
        #print_usage
        echo "usage: sh start.sh [platform | demo]"
        echo "first: "
        echo "     1: sh start.sh platform"
        echo "     2: select 4"
        echo "second: "
        echo "     1: sh start.sh demo"
        exit 0;
    ;;
esac;

exit 0
