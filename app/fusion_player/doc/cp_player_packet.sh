#!/bin/bash



#defined global parament
str_package_version="V0.1.0";

str_version_date="2015-10-19 14:52";
str_version_value="";
str_version_flag="ad";
str_application_name="cp_player";
str_app_name="player";
str_date=`date '+%Y%m%dT%H%M%S'`;
pwd=$PWD;
str_packet_dir="packet";
str_program_host="192.168.1.19";
str_program_path="/home/fzm/pjp/css_device/css_player";
str_platform_name="raspberrypi3";
str_user_name="fzm";
str_packet_type_list=("zip" "tar.gz");
str_package_name="cp_player_V0.3.0ad.raspberrypi3-20170407T110900.tar.gz";


#获取版本信息
#install modules
#$1	project root path
#$2     project release/build path
#$3	path name
#$4	app name
function get_app_version()
{
    #get version from *.h file; example:dev_media_server.h
    tmp_version_flag="cp_$4_version";
    tmp_version_file="$1/app/$3/include/${tmp_version_flag}.h";
    tmp_uppercase_version_flag=$(echo "${tmp_version_flag}" | tr '[a-z]' '[A-Z]');
    tmp_application_version="V0.0.0";
    
    if [ -e "${tmp_version_file}" ]; then
            tmp_application_version=`grep "${tmp_uppercase_version_flag}" ${tmp_version_file} -m 1 | awk '{print $3}' | awk -F '"' '{print $2}'`;
            if [ ! -z ${tmp_application_version} ]; then
                    echo "notice-->get app[ $4 ] version: ${tmp_application_version}";
                    echo ${tmp_application_version}
                    return;
            else
                    echo "warning-->not found app[ $4 ] version from [${tmp_version_file}]";
            fi
    fi
	
    echo "-";
}


#打印错误信息
function print_error_info()
{
    echo "please input application workspace and packet type!  usage:./cp_player_packet.sh /opt/jenkins/jenkins_data/workspace/css_player tar.gz";
    echo "packet type [ ${str_packet_type_list[*]} ]";
}


#判断输入参数是否正确
if [ "-$1" == "-" -o "-$2" == "-" ]; then
    print_error_info;
    exit 1;
fi

if [ ! -d $1 ]; then
    echo "input parament[1] error. path[$1] not exist...";
    print_error_info;
    exit 1;
fi

#判断打包方式是否合法
case $2 in
    "${str_packet_type_list[0]}" || "${str_packet_type_list[1]}" )
        echo "used packet type[$2]";
    ;;
    * )
        echo "input parament[2] error. packet type [ ${str_packet_type_list[*]} ]";
        print_error_info;
        exit 1;
    ;;
esac

#获取版本准备进行打包操作
str_version_value=$(get_app_version $1 " " ${str_app_name} ${str_app_name} );
if [ "-" == "${str_version_value}" ]; then
    echo "get app[ ${str_app_name} ] version error.";
    print_error_info;
    exit 1;
fi

#打印打包信息
str_package_version="${str_version_value}.${str_version_flag}.${str_platform_name}";
str_package_name="${str_application_name}_${str_package_version}-${str_date}.$2";
echo "ready to packet app[ ${str_package_version} ], packet [ ${str_package_name} ]...";



echo "css_player version:${str_version_value}"