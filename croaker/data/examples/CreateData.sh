mv raw_data/*.data ./
mv raw_data/baseline ./

for F in ./*.data; do
  python CreateCSV.py "$F";
done	

mv ./baseline raw_data/ 
mv ./*.data ./raw_data/
rm ./*DEC1.png

for F in ./*.csv; do
  python CreateSC.py "$F";
done	



