cd _posts
find . -type f -name '*.html' -print0 | while IFS= read -r -d '' line; do
	filename="${line%.htm*}"
	NAME=$(echo "${filename}"."md")
	pandoc -s -r html "$line" -o "$NAME"
done

find . -type f -name '*.md' -print0 | while IFS= read -r -d '' line; do
	sed -i '/^####/d' "$line"
done

rm *.html
