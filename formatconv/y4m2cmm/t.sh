for file_name in ../../../../Videos/sample/*.y4m ;do
    OUT_NAME=`basename $file_name`
	./y4m2cmm $file_name ${OUT_NAME}.yuv
done
