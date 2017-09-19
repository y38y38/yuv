../../../ffmpeg/ffmpeg.exe -y -i $1 -c:v libx264 -b:v 1m -threads 1 -preset veryslow -an -f mp4 tmp.mkv
../../../ffmpeg/ffmpeg.exe -y -i tmp.mkv -c:v yuv4 $2
