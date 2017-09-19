../../../ffmpeg/ffmpeg.exe -y -i $1  -c:v libvpx -b:v 1m -quality best -cpu-used 0 -threads 1 -speed 0 -auto-alt-ref 1 -lag-in-frames 25 -an -f webm tmp.mkv
../../../ffmpeg/ffmpeg.exe -y -i tmp.mkv -c:v yuv4 $2

