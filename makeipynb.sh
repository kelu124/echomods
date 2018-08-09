#/bin/bash
# Creating the docs


find . -name "*.ipynb" -not -path "*checkpoints*"  -print0 | 
while IFS= read -r -d '' file; do
    jupyter nbconvert "$file" --to markdown --output-dir ./gitbook/notebooks/ 
done

#
