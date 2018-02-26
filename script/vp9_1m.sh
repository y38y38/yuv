../../../ffmpeg/ffmpeg.exe -y -i $1 -c:v libvpx-vp9 -b:v 1m -threads 1 -speed 0 -tile-columns 0 -frame-parallel 0 -auto-alt-ref 1 -lag-in-frames 25 -g 9999 -aq-mode 0 -an -f webm tmp.mkv
../../../ffmpeg/ffmpeg.exe -y -i tmp.mkv -c:v yuv4 $2
