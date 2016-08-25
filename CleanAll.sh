
find . -type f -name 'my-directory-list.txt' -print0 | while IFS= read -r -d '' line; do
	rm "$line"
done




