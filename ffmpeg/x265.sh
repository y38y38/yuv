./ffmpeg -y -i $1 -c:v libx265 -b:v $2  -preset veryslow  -an -f mp4 $1_$2_x265.mkv
./ffmpeg -y -i  $1_$2_x265.mkv -c:v yuv4 $1_$2_x265.yuv
