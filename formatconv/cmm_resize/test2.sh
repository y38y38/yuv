./cmm2_resize in_1920x1080.yuv out_1920x1080.yuv 1920 1080 1920 1080
#./cmm2_resize in_1920x1080.yuv out_1920x1080.yuv 1920 1080 1920 1080
#gdb --args ./cmm2_resize in_128x16.yuv out_128x16.yuv 128 16 128 16
# ./cmm2_resize in_128x16.yuv out_128x16.yuv 128 16 128 16

diff in_1920x1080.yuv out_1920x1080.yuv
hexdump -C ./in_1920x1080.yuv > in.txt
hexdump -C ./out_1920x1080.yuv > out.txt
diff -u in.txt out.txt > diff.txt

