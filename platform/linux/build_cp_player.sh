#! /bin/sh



str_src_path="/home/f/Project/jenkins_workspace/cp_player";
str_build_path_name="build";
int_is_debug_mode=0;


function build_cp_player()
{
    local tmp_src_path=$1;
    local tmp_platform=$2;
    local tmp_is_debug_mode=$3;
    local tmp_build_path=${tmp_src_path}/${str_build_path_name};
    
    
    if [ ! -d ${tmp_build_path} ]; then
        echo "not found build path[${tmp_build_path}]";
        return 1;
    fi
    
    cd ${tmp_build_path};
    
    if [ ${tmp_is_debug_mode} -eq 0 ]; then
        cmake -DPLATFORM="${tmp_platform}" ..
    else
        cmake -DPLATFORM="${tmp_platform}" -DDEBUG_MODE=ON ..
    fi
    
    make
}


if [ -z $1 -o -z $2 -o -z $3 ]; then
    echo 'usage: build_cp_player.sh $1 $2 $3';
    echo "usage: build_cp_player.sh work_space platform is_debug_mode";
    echo "example: build_cp_player.sh /opt/jenkins/jenkins_data/workspace/cp_player x86 0";
    echo "parameters:";
    echo '          $1: work_space';
    echo '          $2: platform, value list["x86" "hisiv100" "hisiv400" "hisiv500" "raspberry_pi3" "cpptestscan"]';
    echo '          $3: is_debug_mode, 0:release; 1...other:debug';
    
    return 1;
fi


echo "runing : build_cp_player.sh $1 $2 $3";
build_cp_player "$1" "$2" "$3";