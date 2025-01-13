echo "-------- Bonus Correct Output1 -----------"
#期待される本家の挙動
echo "Expected:"
<input.txt grep a1 | wc -w |  > output.txt
cat output.txt

#output.txtを削除
rm -f output.txt
touch output.txt

#オリジナルpipexの挙動
echo "\\npipex:"
valgrind --leak-check=full -q ./pipex input.txt "grep a1" "wc -w" output.txt
cat output.txt

echo "-------- Bonus Correct Output2 -----------"
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
