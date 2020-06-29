#Assignment-1:: Create a address book using shell commands and perform following operations on it
#1.Create
#2.insert
#3.view
#4.delete
#5.modify
#!/bin/sh
n=0
while [ $n -ne 6 ]
do
echo "Menu"
echo "1.Create the Address Book \n2.Insert\n3.View\n4.Delete\n5.Modify\n6.Exit\nEnter ur Choice::";
read ch
case $ch in
1)	
	echo "Enter the filename"
	read addr
	touch $addr
	echo "Address Book created"
	n=1;;

2) 
	echo "\nEnter the name:"
	read name
	echo "\nEnter the address:"
	read address
	touch temp.txt
	echo "|$name	|$address	" | cat >> $addr
	sort -n $addr >temp.txt
	mv temp.txt $addr
	echo "Record inserted Successfully"
	n=2;;

3)	echo "|Name		|Address	"
	cat $addr
	n=3 ;;
	
4)	echo "\nEnter the name to be deleted from address book::"
	read delkey
	touch temp.txt
	grep -v "$delkey" $addr > temp.txt
	sort -n temp.txt > $addr
	echo "Record deleted Successfully"	
	n=4 ;;
	
5)	echo "\nEnter the name of the record to be modified::"
	read modkey
	touch temp.txt
	grep -v "$modkey" $addr > temp.txt
	mv temp.txt $addr
	echo "\nEnter the new name::"
	read newname
	echo "\nEnter the new address::"
	read newaddress
	echo "|$newname	|$newaddress	" | cat >> $addr
	sort -n $addr >temp.txt
	mv temp.txt $addr
	echo "Record modified Successfully"	
	n=5 ;;
	
6)	exit ;;			
esac	
done		
