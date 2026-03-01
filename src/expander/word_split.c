/*
** word_split.c
**
** Word splitting is what happens to a variable AFTER it has been expanded,
** when that variable is NOT inside double quotes.
**
** This is one of the most subtle behaviors in shell programming.
** Most beginners dont know it exists until their shell fails a test.
**
** What is word splitting?
**   When a variable expands to a value that contains spaces, the shell
**   treats those spaces as separators and splits the result into
**   multiple separate arguments.
**
** Example:
**   export TEST="hello     world"
**   echo $TEST       <- word splitting happens, two args: "hello" "world"
**   echo "$TEST"     <- no word splitting, one arg: "hello     world"
**
** Why does this matter?
**   Because ls $TEST would run: ls hello world  (two arguments)
**   But   ls "$TEST" would run: ls "hello     world"  (one argument)
**
** How it works:
**   After expanding a variable that is outside quotes, we check if
**   the result contains whitespace. If it does, we split it at the
**   whitespace boundaries and create multiple separate arguments,
**   just like the user had typed them separated by spaces.
**
** Think of word splitting as the shell being helpful - if a variable
** contains what looks like multiple words, treat them as multiple words.
** But double quotes tell the shell "no, treat this as one single unit."
*/