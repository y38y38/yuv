./ffmpeg.exe -y -i akiyo_cif.y4m -c:v libvpx -b:v 100k -quality best -cpu-used 0 -threads 1 -speed 0 -auto-alt-ref 1 -lag-in-frames 25 -an -f webm akiyo_cif_vp8_100k.mkv

