for i in ../../../../Videos/sample/*.y4m ; do
	BASE_NAME=`basename ${i%.y4m}`
	echo $i ${BASE_NAME}_4096x2160_422_10.cmm
	../y4m2cmm/y4m2cmm $i ${BASE_NAME}_4096x2160_422_10.cmm
	../cmm_resize/cmm2_resize ${BASE_NAME}_4096x2160_422_10.cmm ${BASE_NAME}_1920x1080_422_10.cmm 4096 2160 1920 1080
done