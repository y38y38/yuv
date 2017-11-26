./ffmpeg.exe -y -i $1  -c:v libvpx -b:v $2 -quality best -cpu-used 0 -threads 1 -speed 0 -auto-alt-ref 1 -lag-in-frames 25 -an -f webm $1_$2_vp8.mkv
./ffmpeg -y -i  $1_$2_vp8.mkv -c:v yuv4 $1_$2_vp8.yuv
