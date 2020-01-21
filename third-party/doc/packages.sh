#!/bin/sh

#批量修改库文件的名称
#将boost库中的的vc140修改为vc141


shell_path=$(cd `dirname $0`; pwd);
current_path=$pwd;


#third_party_lib_path="$1";
third_party_lib_path="/home/f/project/c/cp_player/third-party/lib";

package_list=("arm-hisiv100nptl:arm-hisiv100nptl-linux" \
	, "arm-hisiv400:arm-hisiv400-linux" \
	, "arm-hisiv500:arm-hisiv500-linux" \
	, "arm-hisiv600:arm-hisiv600-linux" \
	, "linux_x86:linux-i686" \
	, "raspberry_pi3_gcc4.9.2:raspberry_pi3_gcc4.9.2-linux" \
	, "Win32_x86/v120/Debug:win-i686-v120" \
	, "Win32_x86/v140/Debug:win-i686-v140" \
	);


echo "start process..."
echo ""
echo ""

for tmp_platform_path in ${package_list[*]}
do
	tmp_lib_package_name=`echo ${tmp_platform_path} | awk -F ":" '{print $1}'`;
	tmp_lib_package_extent_name=`echo ${tmp_platform_path} | awk -F ":" '{print $2}'`;

	tmp_whole_path="${third_party_lib_path}/${tmp_lib_package_name}";
	if [ ! -d ${tmp_whole_path} ]; then
		echo "ERROR: not directory path[${tmp_whole_path}].";
		continue;
	fi

	cd ${tmp_whole_path};
	echo -e "\tbegin process[${tmp_whole_path}]."

	for tmp_library_path in `ls ./`
	do
		echo -e "\t\t start archive [${tmp_library_path}]"
		tmp_library_name="${tmp_library_path}-${tmp_lib_package_extent_name}";

		echo -e "\t\t\t tar cvf ${tmp_library_name}.tar ${tmp_library_path} ";
		tar cvf ${tmp_library_name}.tar ${tmp_library_path};
		echo -e "\t\t\t xz ${tmp_library_name}.tar";
		xz ${tmp_library_name}.tar;
		echo -e "\t\t stop archive [${tmp_library_path}]"
	done

	echo -e "\tend process[${tmp_whole_path}]."
done

echo ""
echo "stop process!!!"

