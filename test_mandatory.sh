echo "-------- Mandatory Error1 Invalid argument number-----------"
#オリジナルpipexの挙動のみ
echo "\\npipex: argument number is 3"
valgrind --leak-check=full -q ./pipex input_no_exist.txt "grep a1" output.txt
cat output.txt

echo "-------- Mandatory Error2 No command-----------"
#期待される本家の挙動
echo "Expected:"
<input.txt  > output.txt

#output.txtを削除
rm -f output.txt
touch output.txt

#オリジナルpipexの挙動
echo "\\npipex:"
valgrind --leak-check=full -q ./pipex input.txt output.txt
cat output.txt


echo "\\n-------- Mandatory Error3 No command-----------"
#期待される本家の挙動
echo "Expected:"
<input.txt  "" | "" > output.txt

#output.txtを削除
rm -f output.txt
touch output.txt

#オリジナルpipexの挙動
echo "\\npipex:"
valgrind --leak-check=full -q ./pipex input.txt "" "" output.txt
cat output.txt


echo "\\n-------- Mandatory Error4 Invalid Command-----------"
#期待される本家の挙動
echo "Expected:"
<input.txt  grep a1 | jdsifo > output.txt

#output.txtを削除
rm -f output.txt
touch output.txt

#オリジナルpipexの挙動
echo "\\npipex:"
valgrind --leak-check=full -q ./pipex input.txt "grep a1" "jdsifo" output.txt
cat output.txt


echo "\\n-------- Mandatory Error5 Second is Empty-----------"
#期待される本家の挙動
echo "Expected:"
<input.txt  "cat" | "" > output.txt

#output.txtを削除
rm -f output.txt
touch output.txt

#オリジナルpipexの挙動
echo "\\npipex:"
valgrind --leak-check=full -q ./pipex input.txt "cat" "" output.txt
cat output.txt


echo "-------- Mandatory Correct Output1 -----------"
#期待される本家の挙動
echo "Expected:"
<input.txt "cat" | "wc" > output.txt
cat output.txt

#output.txtを削除
rm -f output.txt
touch output.txt

#オリジナルpipexの挙動
echo "\\npipex:"
valgrind --leak-check=full -q ./pipex input.txt "cat" "wc" output.txt
cat output.txt


echo "-------- Mandatory Correct Output2 -----------"
#期待される本家の挙動
echo "Expected:"
<input.txt ls -l | wc -l > output.txt
cat output.txt

#output.txtを削除
rm -f output.txt
touch output.txt

#オリジナルpipexの挙動
echo "\\npipex:"
valgrind --leak-check=full -q ./pipex input.txt "ls -l" "wc -l" output.txt
cat output.txt


echo "-------- Mandatory Correct Output3 No output file-----------"
#期待される本家の挙動
echo "Expected:"
rm -f output.txt
<input.txt grep a1 | wc -w > output.txt
cat output.txt

#output.txtを削除
rm -f output.txt

#オリジナルpipexの挙動
echo "\\npipex:"
valgrind --leak-check=full -q ./pipex input.txt "grep a1" "wc -w" output.txt
cat output.txt
