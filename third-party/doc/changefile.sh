#!/bin/sh

#批量修改库文件的名称
#将boost库中的的vc140修改为vc141


shell_path=$(cd `dirname $0`; pwd);
current_path=$pwd;


old_mscv_toolset="vc140";
new_mscv_toolset="vc141";

echo "start process..."
echo "[${old_mscv_toolset}] --> [${new_mscv_toolset}] ";
echo ""
echo ""

for tmp_file in `ls ${shell_path}`
do
	tmp_new_file=`echo ${tmp_file} | sed "s/${old_mscv_toolset}/${new_mscv_toolset}/g"`;
	mv ${tmp_file} ${tmp_new_file};
	echo "change[${tmp_file}] to [${tmp_new_file}].";
done

echo ""
echo "stop process!!!"

