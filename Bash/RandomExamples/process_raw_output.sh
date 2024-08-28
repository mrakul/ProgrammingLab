#!/bin/bash

session_id=1;
num_of_sessions=0;
session_info=""

file_to_process="$1"

echo "File to be processed is: $file_to_process"

# Get number of sessions
while $(grep -q "Id: $session_id" $file_to_process > /dev/null)
do
	#session_info=$(grep "Id: $session_id" $file_to_process);

    #if ["$session_info" == '']
	#then
    # 	break;
		#echo "Not Found";
 	#else
		num_of_sessions=$((num_of_sessions+1));
		session_id=$((session_id+1));
	#fi
done

#session_info="$(grep "Id:" $file_to_process)";
echo " ### Number of sessions: $num_of_sessions ###"

# Remove the file if exists
if [ -f ${file_to_process%.*}"_all_sessions.txt" ]
then
	echo "File $file_to_process exists. File is being removed ...";
	rm ${file_to_process%.*}"_all_sessions.txt";
fi

# Print out sessions concatenacting with everything related to it
if [ $num_of_sessions -ne 0 ]
then
	for ((cur_session=1; cur_session<=$num_of_sessions; cur_session++))
	do
		# session_info=$(grep "Id: $cur_session" $file_to_process);
		echo "Current session: $cur_session";
		#Concatenate everything having "ID: [number]" in one line 
		$(grep -w "Id: $cur_session" $file_to_process | tac | xargs >> ${file_to_process%.*}"_all_sessions.txt");
	done

	# Filter sessions with no "criteria" parameter
	$(grep "criteria"  ${file_to_process%.*}"_all_sessions.txt" > ${file_to_process%.*}"_decision_made.txt")

	# Sessions not ended with required string
	$(grep "[^m]$"  ${file_to_process%.*}"_all_sessions.txt" > ${file_to_process%.*}"_no_decision.txt")
fi
