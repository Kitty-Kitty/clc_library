#!/bin/sh

#批量转换源代码文件编码格式


shell_path=$(cd `dirname $0`; pwd);
current_path=$pwd;

source_code="ISO-8859"
dest_code="UTF-8"

source_root_path="$1";
dest_root_path="$2";
file_extents=("*.h" "*.hpp" "*.c" "*.cpp" "*.txt");

echo "start process..."
echo "source path[${source_code}] --> dest path[${dest_code}] ";
echo "[${source_code}] --> [${dest_code}] ";
echo ""
echo ""


for tmp_file_extent in ${file_extents[@]}
do
	for tmp_file in `find ${source_root_path} -name "${tmp_file_extent}" -type f`
	do
		tmp_third_part=`echo ${tmp_file} | grep "third-party"`;
		if [ "-${tmp_third_part}" != "-" ]; then
			echo "don't iconv third-party file[${tmp_file}]."
			continue;
		fi

		tmp_dest_file="${dest_root_path}/${tmp_file}";
		tmp_dest_path="${dest_root_path}/${tmp_file%/*}";
		if [ ! -d ${tmp_dest_path}  ]; then
			mkdir -p ${tmp_dest_path};
			echo "mkdir dest path[${tmp_dest_path}]."
		fi
		
		tmp_code=`file ${tmp_file} | awk '{print $4}'`;
		case ${tmp_code} in
			"${source_code}")
				iconv -f GBK -t UTF-8 ${tmp_file} >> ${tmp_dest_file};

				echo "    iconv [${source_code}] souce file[${tmp_file}]";
				echo "    ----->dest file[${tmp_dest_file}]";
			;;
			"UTF-8")
				tmp_utf_bom=`file ${tmp_file} | grep "BOM"`;
				if [ "-${tmp_utf_bom}" != "-" ]; then
					cat ${tmp_file} > ${tmp_dest_file};
					sed -i '1s/^\xef\xbb\xbf//' ${tmp_dest_file};

					echo "    iconv [UTF-8] souce file[${tmp_file}]";
					echo "    ----->dest file[${tmp_dest_file}]";
				fi
			;;
			*)
				echo "[${tmp_code}] not [${source_code}] [${tmp_file}]."
			;;
		esac
	done
done


echo ""
echo "stop process!!!"

