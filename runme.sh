make clean
python3 ./create_A_file.py
make
./t1 A B
gzip -k A
gzip -k B
gzip -cd B.gz | ./t1 C
./t1 A D -b 100
stat -c "Filename: %n. Size: %s. Blocks: %b. Bytes in block: %B" A >> result.txt
stat -c "Filename: %n. Size: %s. Blocks: %b. Bytes in block: %B" A.gz >> result.txt
stat -c "Filename: %n. Size: %s. Blocks: %b. Bytes in block: %B" B >> result.txt
stat -c "Filename: %n. Size: %s. Blocks: %b. Bytes in block: %B" B.gz >> result.txt
stat -c "Filename: %n. Size: %s. Blocks: %b. Bytes in block: %B" C >> result.txt
stat -c "Filename: %n. Size: %s. Blocks: %b. Bytes in block: %B" D >> result.txt
