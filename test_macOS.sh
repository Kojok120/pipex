echo "-------- Mandatory Error Output1 No input file-----------"
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

echo "-------- Mandatory Error Output2 No command-----------"
#期待される本家の挙動
echo "Expected:"
<input.txt  > output.txt

#output.txtを削除
rm -f output.txt
touch output.txt

#オリジナルpipexの挙動
echo "\\npipex:"
./pipex input.txt "" "" output.txt
cat output.txt

echo "-------- Mandatory Correct Output1 -----------"
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
./pipex input.txt "ls -l" "wc -l" output.txt
cat output.txt
