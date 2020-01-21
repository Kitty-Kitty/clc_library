#! /bin/sh



str_src_path="/home/f/Project/jenkins_workspace/cp_player";
str_build_path_name="build";
str_packet_path_name="cp_player";
str_player_path_name="app/player";
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
}

function packet_cp_player()
{
    local tmp_src_path=$1;
    local tmp_platform_flag=$2;
    local tmp_is_debug_mode=$3;
    local tmp_build_path=${tmp_src_path}/${str_build_path_name};
    local tmp_packet_path=${tmp_src_path}/${str_packet_path_name};
    
    
    if [ ! -d ${tmp_build_path} ]; then
        echo "not found build path[${tmp_build_path}]";
        return 1;
    fi
    
    if [ ! -d ${tmp_packet_path} ]; then
        echo "not found packet path[${tmp_packet_path}]";
        mkdir -p ${tmp_packet_path};
    fi
    
    cd ${tmp_build_path};
    
    if [ ${tmp_is_debug_mode} -eq 0 ]; then
        cmake -DPLATFORM="${tmp_platform}" ..
    else
        cmake -DPLATFORM="${tmp_platform}" -DDEBUG_MODE=ON ..
    fi
}