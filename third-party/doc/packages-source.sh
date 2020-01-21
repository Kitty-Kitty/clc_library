#!/bin/sh

#批量修改库文件的名称
#将boost库中的的vc140修改为vc141


shell_path=$(cd `dirname $0`; pwd);
current_path=$pwd;


#third_party_source_path="$1";
third_party_source_path="/home/f/project/c/cp_player/third-party/src";

echo "start process..."
echo ""
echo ""


cd ${third_party_source_path};
echo -e "\tbegin process[${third_party_source_path}]."

for tmp_library_path in `ls ./`
do
	echo -e "\t\t start archive [${tmp_library_path}]"
	tmp_library_name="${tmp_library_path}-source";

	echo -e "\t\t\t tar cvf ${tmp_library_name}.tar ${tmp_library_path} ";
	tar cvf ${tmp_library_name}.tar ${tmp_library_path};
	echo -e "\t\t\t xz ${tmp_library_name}.tar";
	xz ${tmp_library_name}.tar;
	echo -e "\t\t stop archive [${tmp_library_path}]"
done

echo -e "\tend process[${third_party_source_path}]."

echo ""
echo "stop process!!!"

