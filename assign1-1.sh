#!/bin/sh
ch=0;

echo "Enter the filename to create"
read fname
touch $fname
while [ $ch -ne 5 ]
do	 
	echo "Menu"
	echo "1.insert"
	echo "2.view records"
	echo "3.modify"
	echo "4.delete"
	echo "enter ur choice"
	read ch
	case $ch in
		1)
			echo "enter the roll no"
			read roll
			echo "enter the name"
			read name
			echo "enter the college"
			read college
			echo "$roll $name $college"| cat >> $fname				
			;;
		2)
			cat $fname
			;;
			
		3)	echo "Enter the rollno whose data to modify"
			read modkey
			echo "Enter the data to be modified"
			echo "1 rollno"
			echo "2 name"
			echo "3 college"
			read d
			
			case $d in
			1)
				echo "enter new rollno"
				read new
				a="$(grep -n $modkey $fname | cut -d ':' -f1)"
				b="$(grep -w $modkey $fname | cut -d ' ' -f1)"
				#echo "$a $b"
				sed -i "$a s/$b/$new/" $fname
				 
				;;
			2)	
				echo "enter new name"
				read new
				a="$(grep -n "$modkey" $fname | cut -d ':' -f1)" 
				b="$(grep -w "$modkey" $fname | cut -d ' ' -f2)"
				#echo "$a $b"
				sed -i "$a s/$b/$new/" $fname
				;;
			
			3)	echo "enter new college"
				read new
				a="$(grep -n "$modkey" $fname | cut -d ':' -f1)"
				b="$(grep -w "$modkey" $fname | cut -d ' ' -f3)"
				#echo
				sed -i "$a s/$b/$new/" $fname
				;;	
			*)
				;;	
			esac	
			
			;;
		4)
				echo "enter the rollno whose data to be deleted"
				read delkey
				sed -i "/$delkey/d" $fname
				;;	
				
		*)
			echo "Invalid option"
			;;			
	esac	
done
