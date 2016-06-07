cd _posts
find . -type f -name '*.html' -print0 | while IFS= read -r -d '' line; do
	filename="${line%.htm*}"
	NAME=$(echo "${filename}"."md")
	echo $NAME
	pandoc -s -r html "$line" -o "$NAME"
done

rm *.html
