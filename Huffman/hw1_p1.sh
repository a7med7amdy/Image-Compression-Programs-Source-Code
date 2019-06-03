g++ hw1_p1.cpp huffman.cpp huffman.h -o hw1_p1
./hw1_p1 -entropy < msg1.pgm
./hw1_p1 -tree < msg1.pgm
./hw1_p1 -encode < msg1.pgm
./hw1_p1 -encode -diff < msg1.pgm
sleep 5s
./hw1_p1 -entropy < msg2.pgm
./hw1_p1 -tree < msg2.pgm
./hw1_p1 -encode < msg2.pgm
./hw1_p1 -encode -diff < msg2.pgm
sleep 5s
./hw1_p1 -entropy < msg3.pgm
./hw1_p1 -tree < msg3.pgm
./hw1_p1 -encode < msg3.pgm
./hw1_p1 -encode -diff < msg3.pgm
sleep 5s
./hw1_p1 -entropy < earth.pgm
./hw1_p1 -tree < earth.pgm
./hw1_p1 -encode < earth.pgm
./hw1_p1 -encode -diff < earth.pgm
sleep 5s
./hw1_p1 -entropy < omaha.pgm
./hw1_p1 -tree < omaha.pgm
./hw1_p1 -encode < omaha.pgm
./hw1_p1 -encode -diff < omaha.pgm
sleep 5s
./hw1_p1 -entropy < sena.pgm
./hw1_p1 -tree < sena.pgm
./hw1_p1 -encode < sena.pgm
./hw1_p1 -encode -diff < sena.pgm
sleep 5s
./hw1_p1 -entropy < sensin.pgm
./hw1_p1 -tree < sensin.pgm
./hw1_p1 -encode < sensin.pgm
./hw1_p1 -encode -diff < sensin.pgm
sleep 5s