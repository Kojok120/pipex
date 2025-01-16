echo "-------- Mandatory Error1 No input file-----------"
#期待される本家の挙動
echo "Expected:"
<input_no_exist.txt grep a1 | wc -w > output.txt
cat output.txt

#output.txtを削除
rm -f output.txt
touch output.txt

#オリジナルpipexの挙動
echo "\\npipex:"
./pipex input_no_exist.txt "grep a1" "wc -w" output.txt
cat output.txt

echo "\\n-------- Mandatory Error2 No command-----------"
#期待される本家の挙動
echo "Expected:"
<input.txt  "" "" > output.txt

#output.txtを削除
rm -f output.txt
touch output.txt

#オリジナルpipexの挙動
echo "\\npipex:"
./pipex input.txt "" "" output.txt
cat output.txt


echo "\\n-------- Mandatory Error3 Invalid argument number-----------"
#オリジナルpipexの挙動のみ
echo "\\npipex: no command"
./pipex input_no_exist.txt output.txt
cat output.txt

echo "\\n\\npipex: argument number is 3"
echo "Arguments: input_no_exist.txt  "grep a1"  output.txt\\n"
./pipex input_no_exist.txt "grep a1" output.txt
cat output.txt


echo "\\n-------- Mandatory Correct Output1 -----------"
#期待される本家の挙動
echo "Expected:"
<input.txt grep a1 | wc -w > output.txt
cat output.txt

#output.txtを削除
rm -f output.txt
touch output.txt

#オリジナルpipexの挙動
echo "\\npipex:"
./pipex input.txt "grep a1" "wc -w" output.txt
cat output.txt

echo "\\n-------- Mandatory Correct Output2 -----------"
#期待される本家の挙動
echo "Expected:"
<input.txt ls -l | wc -l > output.txt
cat output.txt

#output.txtを削除
rm -f output.txt
touch output.txt

#オリジナルpipexの挙動
echo "\\npipex:"
./pipex input.txt "ls -l" "wc -l" output.txt
cat output.txt


echo "\\n-------- Mandatory Correct Output3 No output file-----------"
#期待される本家の挙動
echo "Expected:"
rm -f output.txt
<input.txt grep a1 | wc -w > output.txt
cat output.txt

#output.txtを削除
rm -f output.txt

#オリジナルpipexの挙動
echo "\\npipex:"
./pipex input.txt "grep a1" "wc -w" output.txt
cat output.txt
