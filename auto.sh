./prepare.sh
for i in $(seq 1 50);
do
	echo $i/50
	./run.sh
done
