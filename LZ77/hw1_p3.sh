g++ hw1_p3.cpp lz77.h lz77.cpp -o hw1_p3
./hw1_p3 -encode 2 2 256 < msg1.pgm
./hw1_p3 -decode 256 256 255 < image.enc
sleep 10s
./hw1_p3 -encode 1 3 256 -f < msg1.pgm
./hw1_p3 -decode 256 256 255 < image.enc
sleep 10s
./hw1_p3 -encode 3 3 256 < msg2.pgm
./hw1_p3 -decode 256 256 255 < image.enc
sleep 10s
./hw1_p3 -encode 1 3 256 -f < msg2.pgm
./hw1_p3 -decode 256 256 255 < image.enc
sleep 10s
./hw1_p3 -encode 3 3 256 < msg3.pgm
./hw1_p3 -decode 256 256 255 < image.enc
sleep 10s
./hw1_p3 -encode 1 3 256 -f < msg3.pgm
./hw1_p3 -decode 256 256 255 < image.enc
sleep 10s
./hw1_p3 -encode 1 3 256 < earth.pgm
./hw1_p3 -decode 256 256 255 < image.enc
sleep 10s
./hw1_p3 -encode 1 3 256 -f < earth.pgm
./hw1_p3 -decode 256 256 255 < image.enc
sleep 10s
./hw1_p3 -encode 1 3 256 < omaha.pgm
./hw1_p3 -decode 256 256 255 < image.enc
sleep 10s
./hw1_p3 -encode 1 3 256 -f < omaha.pgm
./hw1_p3 -decode 256 256 255 < image.enc
sleep 10s
./hw1_p3 -encode 1 3 256 < sena.pgm
./hw1_p3 -decode 256 256 255 < image.enc
sleep 10s
./hw1_p3 -encode 1 3 256 -f < sena.pgm
./hw1_p3 -decode 256 256 255 < image.enc
sleep 10s
./hw1_p3 -encode 1 3 256 < sensin.pgm
./hw1_p3 -decode 256 256 255 < image.enc
sleep 10s
./hw1_p3 -encode 1 3 256 -f < sensin.pgm
./hw1_p3 -decode 256 256 255 < image.enc
sleep 10s