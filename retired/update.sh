grep -rli '](/retired/retired' --include "*.md"  | xargs -i@ sed -i 's/](\/retired\/retired\//](\/retired\//g' @
