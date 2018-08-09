#/bin/bash
# Creating the docs

#jupyter nbconvert ../../matty/20180310a/20180310a-CalibGain.ipynb --to markdown --output-dir ./gitbook/notebooks/


cd doc/
python createStats.py
cd ../

python makedoc.py

# Cleaning the links to github
cd gitbook
grep -rli '](/bomanz' * | xargs -i@ sed -i 's/](\/bomanz\//](https\:\/\/github.com\/kelu124\/bomanz\/tree\/master\//g' @
grep -rli '](/' * | xargs -i@ sed -i 's/](\//](https\:\/\/github.com\/kelu124\/echomods\/tree\/master\//g' @
cd ..

# Cleaning leftovers from pushing

grep -rli '](/mogaba/' --include "*.md"  | xargs -i@ sed -i 's/](\/mogaba\//](\/retired\/mogaba\//g' @
grep -rli '](/oneeye/' --include "*.md"  | xargs -i@ sed -i 's/](\/oneeye\//](\/retired\/oneeye\//g' @
grep -rli '](/sleepy/' --include "*.md"  | xargs -i@ sed -i 's/](\/sleepy\//](\/retired\/sleepy\//g' @
grep -rli '](/toadkiller/' --include "*.md"  | xargs -i@ sed -i 's/](\/toadkiller\//](\/retired\/toadkiller\//g' @

# Committing github pages modifications
cd gh-pages/
./createMD.sh
./makeprez
git add * -v
git commit -m "Commit of generated files on `date +'%Y-%m-%d %H:%M:%S'`";
git push

# Committing gitbook modifications
cd ../gitbook/
git add * -v
git commit -m "Commit of generated files on `date +'%Y-%m-%d %H:%M:%S'`";
git push

cd ../../bomanz/
#git add * -v
#git commit -m "Autopush"
#git push

# Committing echomods modifications
cd ../echomods/
git add * -v
git commit -m "Commit of generated files on `date +'%Y-%m-%d %H:%M:%S'`";
git push

cd ../oup/
#python do.py
#git add * -v
#git commit -m "Commit of generated files on `date +'%Y-%m-%d %H:%M:%S'`";
#git push

## fdsfds
cd ../echomods/
cp matty/news/*.md ../un0rick/gh-pages/_posts #copying blog posts
cd ../un0rick/gh-pages/
git add * -v
git commit -m "Commit of generated files on `date +'%Y-%m-%d %H:%M:%S'`";
git push






