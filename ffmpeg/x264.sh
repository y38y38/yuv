./ffmpeg -y -i $1 -c:v libx264 -b:v $2 -threads 1 -preset veryslow -an -f mp4 $1_$2_x264.mkv
./ffmpeg -y -i   $1_$2_x264.mkv -c:v yuv4 $1_$2_x264.yuv
