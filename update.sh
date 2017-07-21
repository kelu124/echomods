grep -rli '](/mogaba/' --include "*.md"  | xargs -i@ sed -i 's/](\/mogaba\//](\/retired\/mogaba\//g' @
grep -rli '](/oneeye/' --include "*.md"  | xargs -i@ sed -i 's/](\/oneeye\//](\/retired\/oneeye\//g' @
grep -rli '](/sleepy/' --include "*.md"  | xargs -i@ sed -i 's/](\/sleepy\//](\/retired\/sleepy\//g' @
grep -rli '](/toadkiller/' --include "*.md"  | xargs -i@ sed -i 's/](\/toadkiller\//](\/retired\/toadkiller\//g' @
